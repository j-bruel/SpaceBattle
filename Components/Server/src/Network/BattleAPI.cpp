//!
//! @file Network/BattleAPI.cpp
//! @author jbruel
//! @date 20/11/18
//!

#include "Network/BattleAPI.hpp"
#include "Commun/Network/Requests/Requests.hpp"
#include <utility>

namespace spcbttl
{
namespace server
{
namespace net
{

    void    BattleAPI::keepAliveReq(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id)
    {
        commun::net::req::KeepAliveReq  keepAliveReq;
        msgpack::sbuffer                sbBody;

        sendHeaderPacket(clientSocket, commun::net::req::Type::KEEP_ALIVE_REQ, id);
        msgpack::pack(sbBody, keepAliveReq);

        const std::string   clientInfo = clientSocket.getInfo();

        clientSocket.write(sbBody.data(), sbBody.size());/*, [=](size_t) {
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send keep alive request body to " << clientInfo << "." << std::endl;
        });*/
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send keep alive request body to " << clientInfo << "." << std::endl;
    }

    void    BattleAPI::authReq(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id, const std::string &playerName)
    {
        commun::net::req::AuthenticateReq   authenticateReqauth;
        msgpack::sbuffer                    sbBody;

        sendHeaderPacket(clientSocket, commun::net::req::Type::AUTHENTICATE_REQ, id);
        authenticateReqauth.setPlayerName(playerName);
        msgpack::pack(sbBody, authenticateReqauth);

        const std::string   clientInfo = clientSocket.getInfo();

        clientSocket.write(sbBody.data(), sbBody.size());/*, [=](size_t) {
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send authenticate request body to " << clientInfo << " with " << playerName << " has player name." << std::endl;
        });*/
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send authenticate request body to " << clientInfo << " with " << playerName << " has player name." << std::endl;
    }

    void    BattleAPI::authResp(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id, const std::string &playerName, commun::net::req::State state)
    {
        commun::net::req::AuthenticateResp  authenticateResp;
        msgpack::sbuffer                    sbBody;

        sendHeaderPacket(clientSocket, commun::net::req::Type::AUTHENTICATE_RESP, id);
        authenticateResp.setPlayerName(playerName);
        authenticateResp.setState(state);
        msgpack::pack(sbBody, authenticateResp);

        const std::string   clientInfo = clientSocket.getInfo();

        clientSocket.write(sbBody.data(), sbBody.size());/*, [=](size_t) {
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send authenticate response body to " << clientInfo << " with player name : " << playerName << " and state : " << state << std::endl;
        });*/
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send authenticate response body to " << clientInfo << " with player name : " << playerName << " and state : " << state << std::endl;
    }

    void    BattleAPI::getRoomListReq(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id)
    {
        commun::net::req::GetRoomListReq    roomListReq;
        msgpack::sbuffer                    sbBody;

        sendHeaderPacket(clientSocket, commun::net::req::Type::GET_ROOM_LIST_REQ, id);
        msgpack::pack(sbBody, roomListReq);

        const std::string   clientInfo = clientSocket.getInfo();

        clientSocket.write(sbBody.data(), sbBody.size());/*, [=](size_t) {
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send get room list request body to " << clientInfo << "." << std::endl;
        });*/
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send get room list request body to " << clientInfo << "." << std::endl;
    }

    void    BattleAPI::getRoomListResp(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id, const std::map<std::string, commun::room::State> &rooms)
    {
        commun::net::req::GetRoomListResp   roomListResp;
        msgpack::sbuffer                    sbBody;

        sendHeaderPacket(clientSocket, commun::net::req::Type::GET_ROOM_LIST_RESP, id);
        for (std::pair<std::string, commun::room::State> room : rooms)
            roomListResp.addRoomState(room.first, room.second);
        msgpack::pack(sbBody, roomListResp);

        const std::string   clientInfo = clientSocket.getInfo();

        clientSocket.write(sbBody.data(), sbBody.size());/*, [=](size_t) {
//            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send get room list response body to " << clientInfo << " with " << rooms.size() << " rooms." << std::endl;
        });*/
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send get room list response body to " << clientInfo << " with " << rooms.size() << " rooms." << std::endl;
    }

    void    BattleAPI::createRoomReq(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id, const std::string &roomName, commun::engine::TimeLimit timeLimit, bool isViewerAllow)
    {
        commun::net::req::CreateRoomReq roomReq;
        msgpack::sbuffer                sbBody;

        sendHeaderPacket(clientSocket, commun::net::req::Type::CREATE_ROOM_REQ, id);
        roomReq.setRoomName(roomName);
        roomReq.setLimitType(timeLimit);
        roomReq.setIsViewerAllow(isViewerAllow);
        msgpack::pack(sbBody, roomReq);

        const std::string   clientInfo = clientSocket.getInfo();

        clientSocket.write(sbBody.data(), sbBody.size());/*, [=](size_t) {
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send create room request body to " << clientInfo << " with room name : " << roomName << ", time limit : " << timeLimit << " and is viewer allow : " << isViewerAllow << std::endl;
        });*/
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send create room request body to " << clientInfo << " with room name : " << roomName << ", time limit : " << timeLimit << " and is viewer allow : " << isViewerAllow << std::endl;
    }

    void    BattleAPI::createRoomResp(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id, const std::string &roomName, commun::engine::TimeLimit timeLimit, bool isViewerAllow, commun::net::req::State state)
    {
        commun::net::req::CreateRoomResp    roomResp;
        msgpack::sbuffer                    sbBody;

        sendHeaderPacket(clientSocket, commun::net::req::Type::CREATE_ROOM_RESP, id);
        roomResp.setRoomName(roomName);
        roomResp.setLimitType(timeLimit);
        roomResp.setIsViewerAllow(isViewerAllow);
        roomResp.setRoomState(state);
        msgpack::pack(sbBody, roomResp);

        const std::string   clientInfo = clientSocket.getInfo();

        clientSocket.write(sbBody.data(), sbBody.size());/*, [=](size_t) {
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send create room response body to " << clientInfo << " with room name : " << roomName << ", time limit : " << timeLimit << ", is viewer allow : " << isViewerAllow << " and state : " << state << std::endl;
        });*/
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send create room response body to " << clientInfo << " with room name : " << roomName << ", time limit : " << timeLimit << ", is viewer allow : " << isViewerAllow << " and state : " << state << std::endl;
    }

    void    BattleAPI::joinRoomReq(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id, const std::string &roomName)
    {
        commun::net::req::JoinRoomReq   roomReq;
        msgpack::sbuffer                sbBody;

        sendHeaderPacket(clientSocket, commun::net::req::Type::JOIN_ROOM_REQ, id);
        roomReq.setRoomName(roomName);
        msgpack::pack(sbBody, roomReq);

        const std::string   clientInfo = clientSocket.getInfo();

        clientSocket.write(sbBody.data(), sbBody.size());/*, [=](size_t) {
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send join room request body to " << clientInfo << " with room name : " << roomName << std::endl;
        });*/
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send join room request body to " << clientInfo << " with room name : " << roomName << std::endl;
    }

    void    BattleAPI::joinRoomResp(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id, const std::string &roomName, commun::engine::TimeLimit timeLimit, bool isViewerAllow, commun::net::req::State state)
    {
        commun::net::req::JoinRoomResp  roomResp;
        msgpack::sbuffer                sbBody;

        sendHeaderPacket(clientSocket, commun::net::req::Type::JOIN_ROOM_RESP, id);
        roomResp.setRoomName(roomName);
        roomResp.setLimitType(timeLimit);
        roomResp.setIsViewerAllow(isViewerAllow);
        roomResp.setRoomState(state);
        msgpack::pack(sbBody, roomResp);

        const std::string   clientInfo = clientSocket.getInfo();

        clientSocket.write(sbBody.data(), sbBody.size());/*, [=](size_t) {
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send keep alive request body to " << clientInfo<< " with room name : " << roomName << ", time limit : " << timeLimit << ", is viewer allow : " << isViewerAllow << " and state : " << state << std::endl;
        });*/
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send keep alive request body to " << clientInfo<< " with room name : " << roomName << ", time limit : " << timeLimit << ", is viewer allow : " << isViewerAllow << " and state : " << state << std::endl;
    }

    void    BattleAPI::viewRoomReq(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id, const std::string &roomName)
    {
        commun::net::req::ViewRoomReq   roomReq;
        msgpack::sbuffer                sbBody;

        sendHeaderPacket(clientSocket, commun::net::req::Type::VIEW_ROOM_REQ, id);
        roomReq.setRoomName(roomName);
        msgpack::pack(sbBody, roomReq);

        const std::string   clientInfo = clientSocket.getInfo();

        clientSocket.write(sbBody.data(), sbBody.size());/*, [=](size_t) {
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send view room request body to " << clientInfo << " with room name : " << roomName << std::endl;
        });*/
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send view room request body to " << clientInfo << " with room name : " << roomName << std::endl;
    }

    void    BattleAPI::viewRoomResp(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id, const std::string &roomName, commun::net::req::State roomState)
    {
        commun::net::req::ViewRoomResp  roomResp;
        msgpack::sbuffer                sbBody;

        sendHeaderPacket(clientSocket, commun::net::req::Type::VIEW_ROOM_RESP, id);
        roomResp.setRoomName(roomName);
        roomResp.setRoomState(roomState);
        msgpack::pack(sbBody, roomResp);

        const std::string   clientInfo = clientSocket.getInfo();

        clientSocket.write(sbBody.data(), sbBody.size());/*, [=](size_t) {
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send view room response body to " << clientInfo << " with room name : " << roomName << " and room state : " << roomState << std::endl;
        });*/
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send view room response body to " << clientInfo << " with room name : " << roomName << " and room state : " << roomState << std::endl;
    }

    void    BattleAPI::exitRoomReq(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id, const std::string &roomName)
    {
        commun::net::req::ExitRoomReq   roomReq;
        msgpack::sbuffer                sbBody;

        sendHeaderPacket(clientSocket, commun::net::req::Type::EXIT_ROOM_REQ, id);
        roomReq.setRoomName(roomName);
        msgpack::pack(sbBody, roomReq);

        const std::string   clientInfo = clientSocket.getInfo();

        clientSocket.write(sbBody.data(), sbBody.size());/*, [=](size_t) {
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send exit room request body to " << clientInfo << " with room name : " << roomName << std::endl;
        });*/
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send exit room request body to " << clientInfo << " with room name : " << roomName << std::endl;
    }

    void    BattleAPI::launchGameReq(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id)
    {
        commun::net::req::LaunchGameReq gameReq;
        msgpack::sbuffer                sbBody;

        sendHeaderPacket(clientSocket, commun::net::req::Type::LAUNCH_GAME_REQ, id);
        msgpack::pack(sbBody, gameReq);

        const std::string   clientInfo = clientSocket.getInfo();

        clientSocket.write(sbBody.data(), sbBody.size());/*, [=](size_t) {
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send launch game request body to " << clientInfo << "." << std::endl;
        });*/
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send launch game request body to " << clientInfo << "." << std::endl;
    }

    void    BattleAPI::launchGameResp(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id, commun::net::req::State state)
    {
        commun::net::req::LaunchGameResp    gameResp;
        msgpack::sbuffer                    sbBody;

        sendHeaderPacket(clientSocket, commun::net::req::Type::LAUNCH_GAME_RESP, id);
        gameResp.setState(state);
        msgpack::pack(sbBody, gameResp);

        const std::string   clientInfo = clientSocket.getInfo();

        clientSocket.write(sbBody.data(), sbBody.size());/*, [=](size_t) {
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send launch game response body to " << clientInfo << " with state : " << state << "." << std::endl;
        });*/
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send launch game response body to " << clientInfo << " with state : " << state << "." << std::endl;
    }

    void    BattleAPI::lobbyStateUpdateResp(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id, const std::map<std::string, commun::engine::ClientState > &clients)
    {
        commun::net::req::LobbyStateUpdateResp  stateUpdateResp;
        msgpack::sbuffer                        sbBody;

        sendHeaderPacket(clientSocket, commun::net::req::Type::LOBBY_STATE_UPDATE_RESP, id);
        for (std::pair<std::string, commun::engine::ClientState > client : clients)
            stateUpdateResp.addPlayerState(client.first, client.second);
        msgpack::pack(sbBody, stateUpdateResp);

        const std::string   clientInfo = clientSocket.getInfo();

        clientSocket.write(sbBody.data(), sbBody.size());/*, [=](size_t) {
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send lobby state update response body to " << clientInfo << " with " << clients.size() << " room." << std::endl;
        });*/
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send lobby state update response body to " << clientInfo << " with " << clients.size() << " room." << std::endl;
    }

    void    BattleAPI::setUserBattleshipReq(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id, const commun::engine::Ships &ships)
    {
        commun::net::req::SetUserBattleshipReq  userBattleshipReq;
        msgpack::sbuffer                        sbBody;

        sendHeaderPacket(clientSocket, commun::net::req::Type::SET_USER_BATTLESHIP_REQ, id);
        userBattleshipReq.setShips(ships);
        msgpack::pack(sbBody, userBattleshipReq);

        const std::string   clientInfo = clientSocket.getInfo();

        clientSocket.write(sbBody.data(), sbBody.size());/*, [=](size_t) {
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send set user battle ship request body to " << clientInfo << "." << std::endl;
        });*/
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send set user battle ship request body to " << clientInfo << "." << std::endl;
    }

    void    BattleAPI::setUserBattleshipResp(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id, const commun::engine::Ships &ships, commun::net::req::State state, unsigned short destClient)
    {
        commun::net::req::SetUserBattleshipResp userBattleshipResp;
        msgpack::sbuffer                        sbBody;

        sendHeaderPacket(clientSocket, commun::net::req::Type::SET_USER_BATTLESHIP_RESP, id);
        userBattleshipResp.setShips(ships);
        userBattleshipResp.setState(state);
        userBattleshipResp.setDestClientID(destClient);
        msgpack::pack(sbBody, userBattleshipResp);

        const std::string   clientInfo = clientSocket.getInfo();

        clientSocket.write(sbBody.data(), sbBody.size());/*, [=](size_t) {
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send set user battle ship response body to " << clientInfo
                                                             << " with state : " << userBattleshipResp.getState() << "." << std::endl;
        });*/
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send set user battle ship response body to " << clientInfo
                                                                 << " with state : " << userBattleshipResp.getState() << " and dest client ID : "
                                                                 << destClient << "." << std::endl;
    }

    void    BattleAPI::sendChatMsgReq(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id, commun::engine::ChanelType chanelType, const std::string &msg)
    {
        commun::net::req::SendChatMsgReq    chatMsgReq;
        msgpack::sbuffer                    sbBody;

        sendHeaderPacket(clientSocket, commun::net::req::Type::SEND_CHAT_MSG_REQ, id);
        chatMsgReq.setChanelType(chanelType);
        chatMsgReq.setMessage(msg);
        msgpack::pack(sbBody, chatMsgReq);

        const std::string   clientInfo = clientSocket.getInfo();

        clientSocket.write(sbBody.data(), sbBody.size());/*, [=](size_t) {
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send send chat msg request body to " << clientInfo
                                                             << " with chanel type : " << chatMsgReq.getChanelType() << " and message : "
                                                             << chatMsgReq.getMessage() << "." <<std::endl;
        });*/
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send send chat msg request body to " << clientInfo
                                                                 << " with chanel type : " << chatMsgReq.getChanelType() << " and message : "
                                                                 << chatMsgReq.getMessage() << "." <<std::endl;
    }

    void    BattleAPI::broadcastChatMsgResp(std::vector<std::pair<std::reference_wrapper<sckcpp::tcp::ClientSocket>, unsigned short>> &players, commun::engine::ChanelType chanelType, const std::string &msg, const std::string &playerName)
    {
        commun::net::req::BroadcastChatMsgResp  chatMsgResp;
        msgpack::sbuffer                        sbBody;

        chatMsgResp.setChanelType(chanelType);
        chatMsgResp.setMessage(playerName + ": " + msg);
        msgpack::pack(sbBody, chatMsgResp);

        std::string   clientInfo;

        for (std::pair<std::reference_wrapper<sckcpp::tcp::ClientSocket>, unsigned short> client : players)
        {
            clientInfo = client.first.get().getInfo();
            sendHeaderPacket(client.first.get(), commun::net::req::Type::BROADCAST_CHAT_MSG_REQ, client.second);
            client.first.get().write(sbBody.data(), sbBody.size());/*, [=](size_t) {
                LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send broadcast chat msg request body to " << clientInfo
                                                                         << " with chanel type : " << chatMsgResp.getChanelType() << " and message : "
                                                                         << chatMsgResp.getMessage() << "." <<std::endl;
            });*/
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send broadcast chat msg request body to " << clientInfo
                                                                     << " with chanel type : " << chatMsgResp.getChanelType() << " and message : "
                                                                     << playerName << ": " << chatMsgResp.getMessage() << "." <<std::endl;
        }
    }

    void    BattleAPI::shootShipReq(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id, size_t pos)
    {
        commun::net::req::ShootShipReq  shipReq;
        msgpack::sbuffer                sbBody;

        sendHeaderPacket(clientSocket, commun::net::req::Type::SHOOT_SHIP_REQ, id);
        shipReq.setShootPos(pos);
        msgpack::pack(sbBody, shipReq);

        const std::string   clientInfo = clientSocket.getInfo();

        clientSocket.write(sbBody.data(), sbBody.size());/*, [=](size_t) {
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send shoot ship request body to " << clientInfo
                                                             << " with position : " << shipReq.getShootPos() << "." << std::endl;
        });*/
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send shoot ship request body to " << clientInfo
                                                                 << " with position : " << shipReq.getShootPos() << "." << std::endl;
    }

    void    BattleAPI::shootShipResp(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id, commun::engine::ShootState shootState, size_t pos, unsigned short clientId)
    {
        commun::net::req::ShootShipResp shipResp;
        msgpack::sbuffer                sbBody;

        sendHeaderPacket(clientSocket, commun::net::req::Type::SHOOT_SHIP_RESP, id);
        shipResp.setShootPos(pos);
        shipResp.setShootState(shootState);
        shipResp.setShootClientId(clientId);
        msgpack::pack(sbBody, shipResp);

        const std::string   clientInfo = clientSocket.getInfo();

        clientSocket.write(sbBody.data(), sbBody.size());/*, [=](size_t) {
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send shoot ship response body to " << clientInfo
                                                             << " with shoot state : " << shipResp.getShootState()
                                                             << ", shoot position : " << shipResp.getShootPos()
                                                             << " and client Id : " << shipResp.getShootClientId() << "." << std::endl;
        });*/
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send shoot ship response body to " << clientInfo
                                                                 << " with shoot state : " << shipResp.getShootState()
                                                                 << ", shoot position : " << shipResp.getShootPos()
                                                                 << " and client Id : " << shipResp.getShootClientId() << "." << std::endl;
    }

    void    BattleAPI::gameReadyToLaunchReq(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id)
    {
        commun::net::req::GameReadyToLaunchReq  readyToLaunchReq;
        msgpack::sbuffer                        sbBody;

        sendHeaderPacket(clientSocket, commun::net::req::Type::GAME_READY_TO_LAUNCH_REQ, id);
        msgpack::pack(sbBody, readyToLaunchReq);

        const std::string   clientInfo = clientSocket.getInfo();

        clientSocket.write(sbBody.data(), sbBody.size());/*, [=](size_t) {
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send game ready to launch request body to " << clientInfo << ".";
        });*/
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send game ready to launch request body to " << clientInfo << ".";
    }

    void    BattleAPI::yourTurnToPlayReq(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id)
    {
        commun::net::req::YourTurnToPlayReq turnToPlayReq;
        msgpack::sbuffer                    sbBody;

        sendHeaderPacket(clientSocket, commun::net::req::Type::YOUR_TURN_TO_PLAY_REQ, id);
        msgpack::pack(sbBody, turnToPlayReq);

        const std::string   clientInfo = clientSocket.getInfo();

        clientSocket.write(sbBody.data(), sbBody.size());/*, [=](size_t) {
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send your turn to play request body to " << clientInfo << ".";
        });*/
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send your turn to play request body to " << clientInfo << ".";
    }


    void    BattleAPI::endGameStatusReq(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id, commun::engine::FinalGameStatus finalGameStatus)
    {
        commun::net::req::EndGameStatusReq  gameStatusReq;
        msgpack::sbuffer                    sbBody;

        sendHeaderPacket(clientSocket, commun::net::req::Type::END_GAME_STATUS_REQ, id);
        gameStatusReq.setFinalGameStatus(finalGameStatus);
        msgpack::pack(sbBody, gameStatusReq);

        const std::string   clientInfo = clientSocket.getInfo();

        clientSocket.write(sbBody.data(), sbBody.size());/*, [=](size_t) {
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send end game status request body to " << clientInfo
                                                             << " with final game status : " << gameStatusReq.getFinalGameStatus() << "." << std::endl;
        });*/
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send end game status request body to " << clientInfo
                                                                 << " with final game status : " << gameStatusReq.getFinalGameStatus() << "." << std::endl;
    }

    void    BattleAPI::sendHeaderPacket(sckcpp::tcp::ClientSocket &clientDest, commun::net::req::Type type, unsigned short clientId)
    {
        commun::net::PacketHeader   header;
        msgpack::sbuffer            sb;

        header.mCmdType = type;
        header.mClientId = clientId;
        msgpack::pack(sb, header);

        const std::string   clientInfo = clientDest.getInfo();

        clientDest.write(sb.data(), sb.size());/*, [=](size_t) {
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send header (type : " << type << ") to " << clientInfo << "." << std::endl;
        });*/
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send header (type : " << type << ") to " << clientInfo << "." << std::endl;
    }

}
}
}