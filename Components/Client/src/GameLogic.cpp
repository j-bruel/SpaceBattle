#include <GameLogic.hh>
#include <exception>
#include <pthread.h>

namespace spcbttl
{

namespace client
{

bool isRunning;

struct Context
{
    spcbttl::client::net::Client *network;
    std::shared_ptr<IGameUI> graphics;
    sckcpp::tcp::ClientSocket *clientSocket;
};

static void *runClient(void *context)
{
    Context *appContext = (Context *)context;
    
    try
    {
        appContext->network->run();
    }
    catch (std::exception &e)
    {
        std::cout << "Gracefully exiting..." << std::endl;
        exit(-1);
    }
    return NULL;
}

static void *runKeepAlive(void *buffer)
{
    while (isRunning)
    {
        ((net::BattleAPI *)buffer)->keepAliveReq();
        sleep(2);
    }
    return NULL;
}

GameLogic::GameLogic(Urho3D::Context *context) : _gameGraphic(new GameGraphics(context)),
                                                 _gameUI(new GameUI(context)), _context(context),
                                                 _buffer(tool::BufferDataManager<std::shared_ptr<commun::net::Packet>>::Instance())
{

    // Callback called to notify progress during the graphics loading process
    _gameLoadingHandler.connect([this](int value, std::string state) {
        this->_gameUI->setLoadingScreenValue(0.1 * value, state);
        _context->GetSubsystem<Engine>()->RunFrame();
    });

    // Callback called when the player connect to a server
    _connectServerHandler.connect([this](std::string username, std::string ip, int port) {
        try
        {
            if (!_isAuthFailed)
            {
                sckcpp::tcp::ClientSocket &clientSocket = _client.connect(ip, port);

                _clientSocket = &clientSocket;
                _battleAPI = new net::BattleAPI(clientSocket);

                _buffer.attach(this);

                Context *appContext = new Context();
                appContext->graphics = _gameUI;
                appContext->network = &_client;
                appContext->clientSocket = &clientSocket;

                // Start receiving packets
                networkThread = std::thread(runClient, appContext);

                usleep(500);
            }

            _battleAPI->authReq(username);
        }
        catch (std::exception &e)
        {
            _gameUI->openNotification(std::string("Could not connect to server! (Server is not up ?)"));
        }
    });

    // Callback called when the player joins a room
    _joinRoomHandler.connect([this](std::string roomName) {
        _battleAPI->joinRoomReq(roomName);
    });

    // Callback called when the player validates the game creation process
    _gameCreateGameHandler.connect([this](std::string roomName, spcbttl::commun::engine::TimeLimit timeLimit, bool areSpectatorsAllowed) {
        _battleAPI->createRoomReq(roomName, timeLimit, areSpectatorsAllowed);
    });

    // Callback called when a ship is being placed by the player
    _placeShipHandler.connect([this](std::vector<std::vector<BoardCase>> board, std::vector<IShip *> ships) {
        commun::engine::Ships shipsToSend;

        for (IShip *ship : ships)
        {
            int cur = 0;
            for (int y = 0; y < (int) board.size(); ++y)
            {
                for (int x = 0; x < (int) board[y].size(); ++x)
                {
                    if (board[y][x].ship == ship)
                    {
                        if (board[y][x].ship->getType() == IShip::ONE_SLOT)
                        {
                            shipsToSend.mDestroyer = (y * 10) + x;
                        }
                        else if (board[y][x].ship->getType() == IShip::TWO_SLOTS)
                        {
                            shipsToSend.mSubmarine[cur] = (y * 10) + x;
                        }
                        else if (board[y][x].ship->getType() == IShip::THREE_SLOTS)
                        {
                            shipsToSend.mCruiser1[cur] = (y * 10) + x;
                        }
                        else if (board[y][x].ship->getType() == IShip::THREE_SLOTS_2)
                        {
                            shipsToSend.mCruiser2[cur] = (y * 10) + x;
                        }
                        else if (board[y][x].ship->getType() == IShip::FOUR_SLOTS)
                        {
                            shipsToSend.mBattleship[cur] = (y * 10) + x;
                        }
                        else if (board[y][x].ship->getType() == IShip::FIVE_SLOTS)
                        {
                            shipsToSend.mCarrier[cur] = (y * 10) + x;
                        }

                        if (board[y][x].ship)
                            cur++;
                    }
                }
            }
        }

        _battleAPI->setUserBattleshipReq(shipsToSend);
    });

    // Refresh rooms list
    _refreshRoomsListHandler.connect([this]() {
        _battleAPI->getRoomListReq();
    });

    // Callback called when a player selects an opponent's board case to shoot on
    _shootHandler.connect([this](uint pos) {
        _battleAPI->shootShipReq(pos);
    });

    _chatHandler.connect([this](std::string message, int channel) {
        _battleAPI->sendChatMsgReq((commun::engine::ChanelType)channel, message);
    });

    _exitRoomHandler.connect([this]() {
        _battleAPI->exitRoomReq(_roomName);
    });

    _readyHandler.connect([this]() {
        _battleAPI->launchGameReq();
    });

    _spectacteGameHandler.connect([this](std::string name) {
        _battleAPI->viewRoomReq(name);
    });

    _gameGraphic->setProgressNotifySig(_gameLoadingHandler);
    _gameGraphic->setPlaceShipHandler(_placeShipHandler);
    _gameGraphic->setShootHandler(_shootHandler);
    _gameUI->setConnectServerHandler(_connectServerHandler);
    _gameUI->setJoinGameHandler(_joinRoomHandler);
    _gameUI->setCreateGameHandler(_gameCreateGameHandler);
    _gameUI->setRefreshRoomsListHandler(_refreshRoomsListHandler);
    _gameUI->setChatHandler(_chatHandler);
    _gameUI->setExitRoomHandler(_exitRoomHandler);
    _gameUI->setSpectacteGameHandler(_spectacteGameHandler);
    _gameUI->setReadyHandler(_readyHandler);
}

void GameLogic::joinGame()
{
    this->_gameUI->hideUI();
    this->_gameUI->showLoadingScreen();
    this->_gameUI->hideUI();
    this->_gameUI->showWaitingScreen();
    this->_gameUI->showRoomChat();
}

void GameLogic::startGame()
{
    this->_gameUI->hideUI();
    this->_gameUI->showRoomChat();
    this->_gameGraphic->start(_isSpectator);

    this->_gameGraphic->getOpponentGameBoard()->showGrid();
    this->_gameGraphic->getPlayerGameboard()->showGrid();
}

void GameLogic::init()
{
    this->_gameUI->init();

    this->_gameUI->showLoadingScreen();
    this->_gameGraphic->init();

    this->_gameUI->hideUI();
    this->_gameGraphic->getOpponentGameBoard()->hideGrid();
    this->_gameGraphic->getPlayerGameboard()->hideGrid();

    this->_gameUI->showConnectServerMenu();

    isRunning = true;
}

void GameLogic::stop()
{
    try
    {
        isRunning = false;

        keepAliveThread.join();

        if (_clientSocket)
            _clientSocket->close();
        _client.stop();

        networkThread.join();
    }
    catch (std::exception &e)
    {
    }
}

// COMMAND DISPATCHER

void GameLogic::update(tool::BufferDataManager<std::shared_ptr<commun::net::Packet>> *buffer)
{
    std::shared_ptr<commun::net::Packet> currentPacket = buffer->pop_front();

    switch (currentPacket->mPacketHeader.mCmdType)
    {
    case commun::net::req::AUTHENTICATE_RESP:
        onAuthenticateResponse(currentPacket);
        break;
    case commun::net::req::GET_ROOM_LIST_RESP:
        onRoomListResponse(currentPacket);
        break;
    case commun::net::req::CREATE_ROOM_RESP:
        onCreateRoomResponse(currentPacket);
        break;
    case commun::net::req::JOIN_ROOM_RESP:
        onJoinRoomResponse(currentPacket);
        break;
    case commun::net::req::LAUNCH_GAME_RESP:
        onLaunchGameResponse(currentPacket);
        break;
    case commun::net::req::GAME_READY_TO_LAUNCH_REQ:
        onGameStartResponse(currentPacket);
        break;
    case commun::net::req::YOUR_TURN_TO_PLAY_REQ:
        onPlayersTurnResponse(currentPacket);
        break;
    case commun::net::req::SHOOT_SHIP_RESP:
        onShootShipResponse(currentPacket);
        break;
    case commun::net::req::BROADCAST_CHAT_MSG_REQ:
        onChatResponse(currentPacket);
        break;
    case commun::net::req::VIEW_ROOM_RESP:
        onViewRomResponse(currentPacket);
        break;
    case commun::net::req::SET_USER_BATTLESHIP_RESP:
        onPlaceShipResponse(currentPacket);
        break;
    case commun::net::req::LOBBY_STATE_UPDATE_RESP:
        onLobbyStateResponse(currentPacket);
        break;
    case commun::net::req::END_GAME_STATUS_REQ:
        onEndGameResponse(currentPacket);
        break;
    }
}

void GameLogic::onPlaceShipResponse(std::shared_ptr<commun::net::Packet> command)
{
    std::shared_ptr<commun::net::req::SetUserBattleshipResp> resp =
        std::dynamic_pointer_cast<commun::net::req::SetUserBattleshipResp>(command->mPacketBody);

    if (resp->getState() == commun::net::req::NO_STATE)
    {
        _players.push_back(std::pair<int, std::string>(resp->getDestClientID(), ""));
        std::string whichBoard;
        if (_players.size() == 1)
        {
            _players[0].second = "myboard";
            whichBoard = "myboard";
        }
        else if (_players.size() == 2)
        {
            _players[1].second = "opponentboard";
            whichBoard = "opponentboard";
        }

        _gameGraphic->placeShip(whichBoard, resp->getShips().mDestroyer % 10, resp->getShips().mDestroyer / 10, IShip::RIGHT, IShip::ONE_SLOT, false);

        this->simulateBoard(std::vector<size_t>(resp->getShips().mSubmarine.begin(), resp->getShips().mSubmarine.end()),
                            whichBoard, IShip::TWO_SLOTS);
        this->simulateBoard(std::vector<size_t>(resp->getShips().mCruiser1.begin(), resp->getShips().mCruiser1.end()),
                            whichBoard, IShip::THREE_SLOTS);
        this->simulateBoard(std::vector<size_t>(resp->getShips().mCruiser2.begin(), resp->getShips().mCruiser2.end()),
                            whichBoard, IShip::THREE_SLOTS_2);
        this->simulateBoard(std::vector<size_t>(resp->getShips().mBattleship.begin(), resp->getShips().mBattleship.end()),
                            whichBoard, IShip::FOUR_SLOTS);
        this->simulateBoard(std::vector<size_t>(resp->getShips().mCarrier.begin(), resp->getShips().mCarrier.end()),
                            whichBoard, IShip::FIVE_SLOTS);
    }
}

void GameLogic::simulateBoard(std::vector<size_t> ship, std::string whichBoard, IShip::ShipType type)
{
    std::vector<std::vector<int>> _tmpBoard;

    for (int i = 0; i < 10; ++i)
    {
        _tmpBoard.push_back(std::vector<int>());
        for (int b = 0; b < 10; ++b)
            _tmpBoard[i].push_back(0);
    }
    for (int i = 0; i < ship.size(); ++i)
    {
        _tmpBoard[ship[i] / 10][ship[i] % 10] = 1;
    }

    int firstCaseX = ship[0] % 10;
    int firstCaseY = ship[0] / 10;
    int secondCaseX = ship[1] % 10;
    int secondCaseY = ship[1] / 10;
    IShip::ShipDirection direction;

    if (firstCaseX != secondCaseX)
    {
        direction = IShip::RIGHT;
    }
    else if (firstCaseY != secondCaseY)
    {
        direction = IShip::BOTTOM;
    }

    int shipOriginX, shipOriginY;

    for (int y = 0; y < _tmpBoard.size(); ++y)
    {
        for (int x = 0; x < _tmpBoard[y].size(); ++x)
        {
            if (_tmpBoard[y][x])
            {
                shipOriginX = x;
                shipOriginY = y;
                goto stop;
            }
        }
    }

stop:
    _gameGraphic->placeShip(whichBoard, shipOriginX, shipOriginY, direction, type, false);
}

void GameLogic::onGameStartResponse(std::shared_ptr<commun::net::Packet> command)
{
    std::shared_ptr<commun::net::req::GameReadyToLaunchReq> resp =
        std::dynamic_pointer_cast<commun::net::req::GameReadyToLaunchReq>(command->mPacketBody);

    this->startGame();
}

void GameLogic::onPlayersTurnResponse(std::shared_ptr<commun::net::Packet> command)
{
    std::shared_ptr<commun::net::req::GameReadyToLaunchReq> resp =
        std::dynamic_pointer_cast<commun::net::req::GameReadyToLaunchReq>(command->mPacketBody);

    this->_gameGraphic->startShootingPhase();
}

void GameLogic::onLobbyStateResponse(std::shared_ptr<commun::net::Packet> command)
{
    std::shared_ptr<commun::net::req::LobbyStateUpdateResp> resp =
        std::dynamic_pointer_cast<commun::net::req::LobbyStateUpdateResp>(command->mPacketBody);
    auto players = resp->getPlayers();
    this->_gameUI->clearPlayersList();
    for (auto it = players.begin(); it != players.end(); it++)
    {
        if (resp->getPlayerState(it->first) == spcbttl::commun::engine::PLAYER)
            _gameUI->addPlayer(it->first);
        else
            _gameUI->addSpectator(it->first);
    }
}

void GameLogic::onAuthenticateResponse(std::shared_ptr<commun::net::Packet> command)
{
    std::shared_ptr<commun::net::req::AuthenticateResp> resp =
        std::dynamic_pointer_cast<commun::net::req::AuthenticateResp>(command->mPacketBody);
    if (resp->getRoomState() == commun::net::req::NO_STATE)
    {
        _battleAPI->setID(command->mPacketHeader.mClientId);
        _clientId = command->mPacketHeader.mClientId;

        keepAliveThread = std::thread(runKeepAlive, _battleAPI);

        _gameUI->hideUI();
        _gameUI->showMainMenu();
        _gameUI->showGeneralChat();

        _playerName = resp->getPlayerName();

        _battleAPI->getRoomListReq();
    }
    else if (resp->getRoomState() == commun::net::req::ERROR_ALREADY_AUTH_STATE)
    {
        _gameUI->openNotification("Username not available!");
    }
    else if (resp->getRoomState() == commun::net::req::ERROR_MAX_CLIENT_NB_EXCEEDED_STATE)
    {
        _gameUI->openNotification("Too much clients on the server!");
    }

    if (resp->getRoomState() != commun::net::req::NO_STATE)
    {
        _isAuthFailed = true;
    }
}

void GameLogic::onEndGameResponse(std::shared_ptr<commun::net::Packet> command)
{
    std::shared_ptr<commun::net::req::EndGameStatusReq> resp =
        std::dynamic_pointer_cast<commun::net::req::EndGameStatusReq>(command->mPacketBody);

    if (resp->getFinalGameStatus() == spcbttl::commun::engine::WIN)
    {
        _gameUI->showText("YOU WON!");
    }
    else if (resp->getFinalGameStatus() == spcbttl::commun::engine::LOOSE)
    {
        _gameUI->showText("YOU LOST!");
    }

    sleep(3);

    _gameGraphic->reset();
    _gameUI->hideUI();
    _gameUI->showMainMenu();
    _gameUI->showGeneralChat();
}

void GameLogic::onViewRomResponse(std::shared_ptr<commun::net::Packet> command)
{
    std::shared_ptr<commun::net::req::ViewRoomResp> resp =
        std::dynamic_pointer_cast<commun::net::req::ViewRoomResp>(command->mPacketBody);
    if (resp->getRoomState() == commun::net::req::NO_STATE)
    {
        _roomName = resp->getRoomName();
        _isSpectator = true;

        joinGame();
        _gameUI->setPlayerReady();
    }
}

void GameLogic::onCreateRoomResponse(std::shared_ptr<commun::net::Packet> command)
{
    std::shared_ptr<commun::net::req::CreateRoomResp> resp =
        std::dynamic_pointer_cast<commun::net::req::CreateRoomResp>(command->mPacketBody);
    if (resp->getRoomState() == commun::net::req::NO_STATE)
    {
        _battleAPI->joinRoomReq(resp->getRoomName());
    }
    else if (resp->getRoomState() == commun::net::req::ERROR_INVALID_ROOM_NAME_STATE)
    {
        _gameUI->openNotification("Invalid room name! (Room name needs to be 3 characters long at least and 10 at most)");
    }
    else if (resp->getRoomState() == commun::net::req::ERROR_ROOM_ALREADY_EXIST_STATE)
    {
        _gameUI->openNotification("A room with that name already exists!");
    }
    else if (resp->getRoomState() == commun::net::req::ERROR_MAX_ROOM_NB_EXCEEDED_STATE)
    {
        _gameUI->openNotification("Max room exceeded on the server!");
    }
}

void GameLogic::onJoinRoomResponse(std::shared_ptr<commun::net::Packet> command)
{
    std::shared_ptr<commun::net::req::JoinRoomResp> resp =
        std::dynamic_pointer_cast<commun::net::req::JoinRoomResp>(command->mPacketBody);
    if (resp->getRoomState() == commun::net::req::NO_STATE)
    {
        _roomName = resp->getRoomName();
        joinGame();
    }
    else if (resp->getRoomState() == commun::net::req::ERROR_MAX_ROOM_PLAYER_EXCEEDED_STATE)
    {
        _gameUI->openNotification("Too much players in the room!");
    }
    else if (resp->getRoomState() == commun::net::req::ERROR_GAME_ALREADY_RUNNING_STATE)
    {
        _gameUI->openNotification("The game has already started!");
    }
    else if (resp->getRoomState() == commun::net::req::ERROR_MAX_ROOM_NB_EXCEEDED_STATE)
    {
        _gameUI->openNotification("Max room exceeded on the server!");
    }
}

void GameLogic::onLaunchGameResponse(std::shared_ptr<commun::net::Packet> command)
{
    std::shared_ptr<commun::net::req::LaunchGameResp> resp =
        std::dynamic_pointer_cast<commun::net::req::LaunchGameResp>(command->mPacketBody);
    if (resp->getRoomState() == commun::net::req::NO_STATE)
    {
        _gameUI->setPlayerReady();
    }
}

void GameLogic::onRoomListResponse(std::shared_ptr<commun::net::Packet> command)
{
    std::shared_ptr<commun::net::req::GetRoomListResp> resp =
        std::dynamic_pointer_cast<commun::net::req::GetRoomListResp>(command->mPacketBody);
    auto rooms = resp->getRooms();
    this->_gameUI->clearRooms();
    for (auto it = rooms.begin(); it != rooms.end(); it++)
    {
        int playersConnected = 0;
        if (it->second == spcbttl::commun::room::State::IN_PROFRESS || it->second == spcbttl::commun::room::State::WAITING_FOR_LAUNCH)
            playersConnected = 2;
        else if (it->second == spcbttl::commun::room::State::WAITING_FOR_PLAYER)
            playersConnected = 1;
        this->_gameUI->addRoom(it->first, playersConnected);
    }
}

void GameLogic::onShootShipResponse(std::shared_ptr<commun::net::Packet> command)
{
    std::shared_ptr<commun::net::req::ShootShipResp> resp =
        std::dynamic_pointer_cast<commun::net::req::ShootShipResp>(command->mPacketBody);
    spcbttl::commun::engine::ShootState state = resp->getShootState();

    if (!_isSpectator)
    {
        if (_clientId != resp->getShootClientId())
        {
            if (state == spcbttl::commun::engine::IMPACTED || state == spcbttl::commun::engine::SUNK_TOUCHDOWN)
                _gameGraphic->setOpponentBoardImpact(resp->getShootPos() % 10, resp->getShootPos() / 10, IGameBoard::SHIP);
            else
                _gameGraphic->setOpponentBoardImpact(resp->getShootPos() % 10, resp->getShootPos() / 10, IGameBoard::WATER);
        }
        else
        {
            if (state == spcbttl::commun::engine::IMPACTED || state == spcbttl::commun::engine::SUNK_TOUCHDOWN)
                _gameGraphic->setMyBoardImpact(resp->getShootPos() % 10, resp->getShootPos() / 10, IGameBoard::SHIP);
            else
                _gameGraphic->setMyBoardImpact(resp->getShootPos() % 10, resp->getShootPos() / 10, IGameBoard::WATER);
        }
    }
    else
    {
        for (int i = 0; i < _players.size(); ++i)
        {
            if (_players[i].first == resp->getShootClientId() && _players[i].second == "opponentboard")
            {
                if (state == spcbttl::commun::engine::IMPACTED || state == spcbttl::commun::engine::SUNK_TOUCHDOWN)
                    _gameGraphic->setOpponentBoardImpact(resp->getShootPos() % 10, resp->getShootPos() / 10, IGameBoard::SHIP);
                else
                    _gameGraphic->setOpponentBoardImpact(resp->getShootPos() % 10, resp->getShootPos() / 10, IGameBoard::WATER);
            }
            else if (_players[i].first == resp->getShootClientId())
            {
                if (state == spcbttl::commun::engine::IMPACTED || state == spcbttl::commun::engine::SUNK_TOUCHDOWN)
                    _gameGraphic->setMyBoardImpact(resp->getShootPos() % 10, resp->getShootPos() / 10, IGameBoard::SHIP);
                else
                    _gameGraphic->setMyBoardImpact(resp->getShootPos() % 10, resp->getShootPos() / 10, IGameBoard::WATER);
            }
        }
    }
}

void GameLogic::onChatResponse(std::shared_ptr<commun::net::Packet> command)
{
    std::shared_ptr<commun::net::req::BroadcastChatMsgResp> resp =
        std::dynamic_pointer_cast<commun::net::req::BroadcastChatMsgResp>(command->mPacketBody);

    _gameUI->addChatMessage("", resp->getMessage(), (bool)resp->getChanelType());
}

} // namespace client
} // namespace spcbttl
