
#include <regex>
#include <iostream>
#include <graphic/utils/UrhoGraphicsHeaders.hh>
#include <ui/GameUI.hh>

using namespace Urho3D;

GameUI::GameUI(Urho3D::Context *context) : AUrhoGameUI(context) {}

GameUI::~GameUI() {}

void GameUI::init()
{
    _resources = _context->GetSubsystem<ResourceCache>();
    _ui = _context->GetSubsystem<UI>();

    _context->GetSubsystem<Input>()->SetMouseVisible(true);

    // Set general style of the UI
    auto *style = _resources->GetResource<XMLFile>("ui_style.xml");
    _ui->GetRoot()->SetDefaultStyle(style);

    // Load components
    this->loadConnectServerMenu();
    this->loadMainMenu();
    this->loadCreateGameMenu();
    this->loadWaitingRoomMenu();
    this->loadRoomChat();
    this->loadGeneralChat();
    this->loadLoadingScreen();

    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(GameUI, update));
    SubscribeToEvent("sendNotificationEvent", URHO3D_HANDLER(GameUI, sendNotificationHandler));
    SubscribeToEvent("ShowTextEvent", URHO3D_HANDLER(GameUI, showText));
}

void GameUI::update(StringHash eventType, VariantMap &eventData)
{
    while (_sharedBuffer.size())
    {
        boost::optional<std::pair<StringHash, VariantMap>> event = _sharedBuffer.pop();
        if (event)
        {
            SendEvent((*event).first, (*event).second);
        }
    }
}

void GameUI::loadWaitingRoomMenu()
{
    _waitingMenuLayout = _ui->LoadLayout(_resources->GetResource<XMLFile>("menu/waiting_players.xml"));

    auto *exitButton = _waitingMenuLayout->GetChildStaticCast<Button>("ExitButton", true);
    auto *readyButton = _waitingMenuLayout->GetChildStaticCast<Button>("ReadyButton", true);
    
    SubscribeToEvent(exitButton, E_RELEASED, URHO3D_HANDLER(GameUI, exitRoomHandler));
    SubscribeToEvent(readyButton, E_RELEASED, URHO3D_HANDLER(GameUI, readyHandler));

    SubscribeToEvent("AddSpectatorEvent", URHO3D_HANDLER(GameUI, addSpectator));
    SubscribeToEvent("AddPlayerEvent", URHO3D_HANDLER(GameUI, addPlayer));
    SubscribeToEvent("PlayerReadyEvent", URHO3D_HANDLER(GameUI, setPlayerReady));
}

void GameUI::loadMainMenu()
{
    _mainMenuLayout = _ui->LoadLayout(_resources->GetResource<XMLFile>("menu/main.xml"));

    auto *createGameButton = _mainMenuLayout->GetChildStaticCast<Button>("CreateGameButton", true);
    auto *joinGameButton = _mainMenuLayout->GetChildStaticCast<Button>("JoinGameButton", true);
    auto *spectateButton = _mainMenuLayout->GetChildStaticCast<Button>("SpectateButton", true);
    auto *refreshButton = _mainMenuLayout->GetChildStaticCast<Button>("RefreshGamesList", true);
    auto *gamesList = _mainMenuLayout->GetChildStaticCast<ListView>("GamesList", true);

    gamesList->SetHighlightMode(HM_FOCUS);

    SubscribeToEvent(joinGameButton, E_RELEASED, URHO3D_HANDLER(GameUI, joinGameHandler));
    SubscribeToEvent(createGameButton, E_RELEASED, URHO3D_HANDLER(GameUI, createGameMenuHandler));
    SubscribeToEvent(spectateButton, E_RELEASED, URHO3D_HANDLER(GameUI, spectateGameHandler));
    SubscribeToEvent(refreshButton, E_RELEASED, URHO3D_HANDLER(GameUI, refreshRoomsHandler));

    SubscribeToEvent("newRoomCreatedEvent", URHO3D_HANDLER(GameUI, addRoom));
}

void GameUI::sendNotificationHandler(StringHash eventType, VariantMap &eventData)
{
    String message = eventData["message"].GetString();

    new MessageBox(_context, message);
}

void GameUI::loadConnectServerMenu()
{
    _connectServerLayout = _ui->LoadLayout(_resources->GetResource<XMLFile>("menu/connect_server.xml"));

    auto *ConnectButton = _connectServerLayout->GetChildStaticCast<Button>("ConnectButton", true);
    SubscribeToEvent(ConnectButton, E_RELEASED, URHO3D_HANDLER(GameUI, connectServerHandler));
}

void GameUI::loadCreateGameMenu()
{
    _createGameMenuLayout = _ui->LoadLayout(_resources->GetResource<XMLFile>("menu/create_game.xml"));

    auto *createGameValidateButton = _createGameMenuLayout->GetChildStaticCast<Button>("CreateGameValidateButton", true);
    auto *backButton = _createGameMenuLayout->GetChildStaticCast<Button>("BackButton", true);

    SubscribeToEvent(createGameValidateButton, E_RELEASED, URHO3D_HANDLER(GameUI, createGameHandler));
    SubscribeToEvent(backButton, E_RELEASED, URHO3D_HANDLER(GameUI, goBackHandler));
}

void GameUI::loadRoomChat()
{
    _roomChatLayout = _ui->LoadLayout(_resources->GetResource<XMLFile>("chat_room.xml"));

    auto *sendButton = _roomChatLayout->GetChildStaticCast<Button>("SendButton", true);

    SubscribeToEvent(sendButton, E_RELEASED, URHO3D_HANDLER(GameUI, sendChatHandler));
    SubscribeToEvent("ChatReceivedEvent", URHO3D_HANDLER(GameUI, addChatMessage));
}

void GameUI::loadGeneralChat()
{
    _generalChatLayout = _ui->LoadLayout(_resources->GetResource<XMLFile>("chat_general.xml"));

    auto *sendButton = _generalChatLayout->GetChildStaticCast<Button>("SendButton", true);

    SubscribeToEvent(sendButton, E_RELEASED, URHO3D_HANDLER(GameUI, sendChatHandler));
    SubscribeToEvent("ChatReceivedEvent", URHO3D_HANDLER(GameUI, addChatMessage));
}

void GameUI::loadLoadingScreen()
{
    _loadingLayout = _ui->LoadLayout(_resources->GetResource<XMLFile>("loading.xml"));
}

void GameUI::showConnectServerMenu()
{
    _currentLayout = _connectServerLayout;
    _ui->GetRoot()->AddChild(_connectServerLayout);
}

void GameUI::showMainMenu()
{
    _currentLayout = _mainMenuLayout;
    _ui->GetRoot()->AddChild(_mainMenuLayout);
}

void GameUI::showCreateGameMenu()
{
    _currentLayout = _createGameMenuLayout;
    _ui->GetRoot()->AddChild(_currentLayout);
}

void GameUI::showRoomChat()
{
    _currentLayout = _roomChatLayout;

    _ui->GetRoot()->AddChild(_currentLayout);
}

void GameUI::showGeneralChat()
{
    _currentLayout = _generalChatLayout;

    _ui->GetRoot()->AddChild(_currentLayout);
}

void GameUI::showLoadingScreen()
{
    _currentLayout = _loadingLayout;
    _ui->GetRoot()->AddChild(_currentLayout);
}

void GameUI::showWaitingScreen()
{
    _currentLayout = _waitingMenuLayout;
    _ui->GetRoot()->AddChild(_currentLayout);

    auto *readyButton = _waitingMenuLayout->GetChildStaticCast<Button>("ReadyButton", true);

    SubscribeToEvent(readyButton, E_RELEASED, URHO3D_HANDLER(GameUI, readyHandler));
    readyButton->SetEnabled(true);
}

void GameUI::addRoom(std::string roomName, int playersConnected)
{
    VariantMap params;
    params["name"] = String(roomName.c_str());
    params["players"] = playersConnected;

    _sharedBuffer.push(std::pair<StringHash, VariantMap>("newRoomCreatedEvent", params));
}

void GameUI::addRoom(StringHash eventType, VariantMap &eventData)
{
    String roomName = eventData["name"].GetString();
    int players = eventData["players"].GetInt();

    auto *gamesList = _mainMenuLayout->GetChildStaticCast<ListView>("GamesList", true);

    Text *newRoomEntry = new Text(_context);
    newRoomEntry->SetStyle("FileSelectorListText");
    newRoomEntry->SetText(roomName);
    newRoomEntry->SetName(roomName);

    Text *playersConnected = new Text(_context);
    playersConnected->SetText(String(players) + String("/2"));
    playersConnected->SetHorizontalAlignment(HA_RIGHT);
    playersConnected->SetStyleAuto();
    newRoomEntry->AddChild(playersConnected);

    gamesList->AddItem(newRoomEntry);
}

void GameUI::showText(std::string message)
{
    VariantMap params;
    params["message"] = String(message.c_str());

    _sharedBuffer.push(std::pair<StringHash, VariantMap>("ShowTextEvent", params));
}

void GameUI::showText(StringHash eventType, VariantMap &params)
{
    String message = params["message"].GetString();

    Text *newText = new Text(_context);
    newText->SetText(String(message));
    newText->SetVerticalAlignment(VA_CENTER);
    newText->SetHorizontalAlignment(HA_CENTER);
    newText->SetFontSize(80);
    newText->SetFont(_resources->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 80);
    newText->SetColor(Color(0.0f, 1.0f, 0.0f));

    _ui->GetRoot()->AddChild(newText);
}

void GameUI::addChatMessage(std::string player, std::string message, bool channel)
{
    VariantMap params;
    params["message"] = String(message.c_str());
    params["type"] = channel;

    _sharedBuffer.push(std::pair<StringHash, VariantMap>("ChatReceivedEvent", params));
}

void GameUI::addSpectator(std::string name)
{
    VariantMap params;

    params["spectatorName"] = String(name.c_str());
    _sharedBuffer.push(std::pair<StringHash, VariantMap>("AddSpectatorEvent", params));
}

void GameUI::addPlayer(std::string name)
{
    VariantMap params;

    params["playerName"] = String(name.c_str());
    _sharedBuffer.push(std::pair<StringHash, VariantMap>("AddPlayerEvent", params));
}

void GameUI::setPlayerReady()
{
    _sharedBuffer.push(std::pair<StringHash, VariantMap>("PlayerReadyEvent", VariantMap()));
}

void GameUI::setPlayerReady(StringHash eventType, VariantMap &eventData)
{
    auto *readyButton = _waitingMenuLayout->GetChildStaticCast<Text>("ReadyButton", true);

    readyButton->SetEnabled(false);
}

void GameUI::setLoadingScreenValue(float value, std::string &state)
{
    auto *progressBar = _loadingLayout->GetChildStaticCast<ProgressBar>("LoadingProgressBar", true);
    auto *progressBarLabel = _loadingLayout->GetChildStaticCast<Text>("LoadingStateText", true);
    
    progressBar->SetValue(value);
    progressBarLabel->SetText(String(state.c_str()));
    progressBarLabel->SetTextEffect(TE_STROKE);
}

void GameUI::clearRooms()
{
    auto *gamesList = _mainMenuLayout->GetChildStaticCast<ListView>("GamesList", true);

    gamesList->RemoveAllItems();
}

void GameUI::clearPlayersList()
{
    auto *playersList = _waitingMenuLayout->GetChildStaticCast<ListView>("PlayersList", true);
    auto *spectatorsList = _waitingMenuLayout->GetChildStaticCast<ListView>("SpectatorsList", true);

    playersList->RemoveAllItems();
    spectatorsList->RemoveAllItems();
}

void GameUI::hideUI()
{
    this->_ui->Clear();

    auto *readyButton = _waitingMenuLayout->GetChildStaticCast<Text>("ReadyButton", true);

    UnsubscribeFromEvent(readyButton, "Released");
}

// HANDLERS

void GameUI::addChatMessage(StringHash eventType, VariantMap &eventData)
{
    String message = eventData["message"].GetString();
    bool channel = eventData["type"].GetBool();

    auto *chatList = _currentLayout->GetChildStaticCast<ListView>("ChatList", true);

    Text *newChatEntry = new Text(_context);
    newChatEntry->SetText(message);
    newChatEntry->SetStyleAuto();
    chatList->AddItem(newChatEntry);
}

void GameUI::addSpectator(StringHash eventType, VariantMap &eventData)
{
    auto *spectatorsList = _waitingMenuLayout->GetChildStaticCast<ListView>("SpectatorsList", true);

    String name = eventData["spectatorName"].GetString();

    Text *newSpectator = new Text(_context);
    newSpectator->SetText(name);
    newSpectator->SetStyleAuto();
    spectatorsList->AddItem(newSpectator);
}

void GameUI::addPlayer(StringHash eventType, VariantMap &eventData)
{
    std::cout << "ADD PLAYER" << std::endl;

    auto *playersList = _waitingMenuLayout->GetChildStaticCast<ListView>("PlayersList", true);

    String name = eventData["playerName"].GetString();

    Text *newPlayer = new Text(_context);
    newPlayer->SetStyle("FileSelectorListText");
    newPlayer->SetText(name);
    playersList->AddItem(newPlayer);
}

void GameUI::readyHandler(StringHash eventType, VariantMap &eventData)
{
    _readyHandler();
}

void GameUI::exitRoomHandler(StringHash eventType, VariantMap &eventData)
{
    _exitRoomHandler();
}

void GameUI::refreshRoomsHandler(StringHash eventType, VariantMap &eventData)
{
    _refreshRoomsListHandler();
}

void GameUI::connectServerHandler(StringHash eventType, VariantMap &eventData)
{
    auto *serverLineEdit = _connectServerLayout->GetChildStaticCast<LineEdit>("ServerLineEdit", true);
    auto *usernameLineEdit = _connectServerLayout->GetChildStaticCast<LineEdit>("UsernameLineEdit", true);
    auto *portLineEdit = _connectServerLayout->GetChildStaticCast<LineEdit>("PortLineEdit", true);

    if (serverLineEdit->GetText().Empty() || portLineEdit->GetText().Empty() || usernameLineEdit->GetText().Empty())
        openNotification("Invalid values!");
    else if (!std::regex_match(usernameLineEdit->GetText().CString(), std::regex("(\\w)*")))
        openNotification("Username must contain alphanumeric characters only!");
    else
        this->_connectServerHandler(usernameLineEdit->GetText().CString(), serverLineEdit->GetText().CString(), ToInt(portLineEdit->GetText()));
}

void GameUI::createGameMenuHandler(StringHash eventType, VariantMap &eventData)
{
    this->hideUI();
    this->showCreateGameMenu();
    this->showGeneralChat();
}

void GameUI::createGameHandler(StringHash eventType, VariantMap &eventData)
{
    auto *roomNameLineEdit = _createGameMenuLayout->GetChildStaticCast<LineEdit>("RoomNameLineEdit", true);
    auto *gameLimitDropDown = _createGameMenuLayout->GetChildStaticCast<DropDownList>("GameLimitDropDown", true);
    auto *AllowSpectateDropDown = _createGameMenuLayout->GetChildStaticCast<DropDownList>("AllowSpectateDropDown", true);

    int selection = AllowSpectateDropDown->GetSelection();
    bool allowSpectators = (bool)AllowSpectateDropDown->GetSelection();
    spcbttl::commun::engine::TimeLimit gameLimit = (spcbttl::commun::engine::TimeLimit)gameLimitDropDown->GetSelection();
    if (roomNameLineEdit->GetText().Empty())
        openNotification("Invalid values!");
    else
        this->_createGameHandler(roomNameLineEdit->GetText().CString(), gameLimit, allowSpectators);
}

void GameUI::joinGameHandler(StringHash eventType, VariantMap &eventData)
{
    auto *gamesList = _mainMenuLayout->GetChildStaticCast<ListView>("GamesList", true);

    UIElement *selectedItem = gamesList->GetSelectedItem();
    if (selectedItem)
    {
        this->_joinGameHandler(selectedItem->GetName().CString());
    }
}

void GameUI::spectateGameHandler(StringHash eventType, VariantMap &eventData)
{
    auto *gamesList = _mainMenuLayout->GetChildStaticCast<ListView>("GamesList", true);

    UIElement *selectedItem = gamesList->GetSelectedItem();
    if (selectedItem)
    {
        this->_spectateGameHandler(selectedItem->GetName().CString());
    }
}

void GameUI::goBackHandler(StringHash eventType, VariantMap &eventData)
{
    this->hideUI();
    this->showMainMenu();
    this->showGeneralChat();
}

void GameUI::sendChatHandler(StringHash eventType, VariantMap &eventData)
{
    auto *chatLineEdit = _currentLayout->GetChildStaticCast<LineEdit>("ChatLineEdit", true);
    auto *channelDropDown = _currentLayout->GetChildStaticCast<DropDownList>("ChannelDropDown", true);

    if (!chatLineEdit->GetText().Empty())
    {
        auto *selectedChannel = channelDropDown->GetSelectedItem();
        this->_chatHandler(chatLineEdit->GetText().CString(), (selectedChannel->GetName() == "general" ? 1 : 0));
        chatLineEdit->SetText("");
    }
}
