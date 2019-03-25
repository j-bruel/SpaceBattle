//!
//! @file BattleAPI.cpp
//! @author jbruel
//! @date 20/11/18
//!

#include "Network/BattleAPI.hpp"
#include "Commun/Network/Requests/Requests.hpp"
#include <utility>
#include <plog/Log.h>

namespace spcbttl
{
namespace client
{
namespace net
{

    void    BattleAPI::keepAliveReq()
    {
        commun::net::req::KeepAliveReq  keepAliveReq;
        msgpack::sbuffer                sbBody;

        sendHeaderPacket(commun::net::req::Type::KEEP_ALIVE_REQ, mId);
        msgpack::pack(sbBody, keepAliveReq);

        const std::string   clientInfo = mClientSocket.getInfo();

        mClientSocket.write(sbBody.data(), sbBody.size());/*, [=](size_t) {
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send keep alive request body to " << clientInfo << ".";
        });*/
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send keep alive request body to " << clientInfo << ".";
    }

    void    BattleAPI::authReq(const std::string &playerName)
    {
        commun::net::req::AuthenticateReq   authenticateReqauth;
        msgpack::sbuffer                    sbBody;

        sendHeaderPacket(commun::net::req::Type::AUTHENTICATE_REQ, mId);
        authenticateReqauth.setPlayerName(playerName);
        msgpack::pack(sbBody, authenticateReqauth);

        const std::string   clientInfo = mClientSocket.getInfo();

        mClientSocket.write(sbBody.data(), sbBody.size());/*, [=](size_t) {
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send authenticate request body to " << clientInfo << " with " << playerName << " has player name.";
        });*/
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send authenticate request body to " << clientInfo << " with " << playerName << " has player name.";
    }

    void    BattleAPI::getRoomListReq()
    {
        commun::net::req::GetRoomListReq    roomListReq;
        msgpack::sbuffer                    sbBody;

        sendHeaderPacket(commun::net::req::Type::GET_ROOM_LIST_REQ, mId);
        msgpack::pack(sbBody, roomListReq);

        const std::string   clientInfo = mClientSocket.getInfo();

        mClientSocket.write(sbBody.data(), sbBody.size());/*, [=](size_t) {
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send get room list request body to " << clientInfo << ".";
        });*/
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send get room list request body to " << clientInfo << ".";
    }

    void    BattleAPI::createRoomReq(const std::string &roomName, commun::engine::TimeLimit timeLimit, bool isViewerAllow)
    {
        commun::net::req::CreateRoomReq roomReq;
        msgpack::sbuffer                sbBody;

        sendHeaderPacket(commun::net::req::Type::CREATE_ROOM_REQ, mId);
        roomReq.setRoomName(roomName);
        roomReq.setLimitType(timeLimit);
        roomReq.setIsViewerAllow(isViewerAllow);
        msgpack::pack(sbBody, roomReq);

        const std::string   clientInfo = mClientSocket.getInfo();

        mClientSocket.write(sbBody.data(), sbBody.size());/*, [=](size_t) {
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send create room request body to " << clientInfo << " with room name : " << roomName << ", time limit : " << timeLimit << " and is viewer allow : " << isViewerAllow;
        });*/
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send create room request body to " << clientInfo << " with room name : " << roomName << ", time limit : " << timeLimit << " and is viewer allow : " << isViewerAllow;
    }

    void    BattleAPI::joinRoomReq(const std::string &roomName)
    {
        commun::net::req::JoinRoomReq   roomReq;
        msgpack::sbuffer                sbBody;

        sendHeaderPacket(commun::net::req::Type::JOIN_ROOM_REQ, mId);
        roomReq.setRoomName(roomName);
        msgpack::pack(sbBody, roomReq);

        const std::string   clientInfo = mClientSocket.getInfo();

        mClientSocket.write(sbBody.data(), sbBody.size());/*, [=](size_t) {
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send join room request body to " << clientInfo << " with room name : " << roomName;
        });*/
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send join room request body to " << clientInfo << " with room name : " << roomName;
    }

    void    BattleAPI::viewRoomReq(const std::string &roomName)
    {
        commun::net::req::ViewRoomReq   roomReq;
        msgpack::sbuffer                sbBody;

        sendHeaderPacket(commun::net::req::Type::VIEW_ROOM_REQ, mId);
        roomReq.setRoomName(roomName);
        msgpack::pack(sbBody, roomReq);

        const std::string   clientInfo = mClientSocket.getInfo();

        mClientSocket.write(sbBody.data(), sbBody.size());/*, [=](size_t) {
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send view room request body to " << clientInfo << " with room name : " << roomName;
        });*/
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send view room request body to " << clientInfo << " with room name : " << roomName;
    }

    void    BattleAPI::exitRoomReq(const std::string &roomName)
    {
        commun::net::req::ExitRoomReq   roomReq;
        msgpack::sbuffer                sbBody;

        sendHeaderPacket(commun::net::req::Type::EXIT_ROOM_REQ, mId);
        roomReq.setRoomName(roomName);
        msgpack::pack(sbBody, roomReq);

        const std::string   clientInfo = mClientSocket.getInfo();

        mClientSocket.write(sbBody.data(), sbBody.size());/*, [=](size_t) {
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send exit room request body to " << clientInfo << " with room name : " << roomName;
        });*/
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send exit room request body to " << clientInfo << " with room name : " << roomName;
    }

    void    BattleAPI::launchGameReq()
    {
        commun::net::req::LaunchGameReq gameReq;
        msgpack::sbuffer                sbBody;

        sendHeaderPacket(commun::net::req::Type::LAUNCH_GAME_REQ, mId);
        msgpack::pack(sbBody, gameReq);

        const std::string   clientInfo = mClientSocket.getInfo();

        mClientSocket.write(sbBody.data(), sbBody.size());/*, [=](size_t) {
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send launch game request body to " << clientInfo << ".";
        });*/
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send launch game request body to " << clientInfo << ".";

    }

    void    BattleAPI::setUserBattleshipReq(const commun::engine::Ships &ships)
    {
        commun::net::req::SetUserBattleshipReq  userBattleshipReq;
        msgpack::sbuffer                        sbBody;

        sendHeaderPacket(commun::net::req::Type::SET_USER_BATTLESHIP_REQ, mId);
        userBattleshipReq.setShips(ships);
        msgpack::pack(sbBody, userBattleshipReq);

        const std::string   clientInfo = mClientSocket.getInfo();

        mClientSocket.write(sbBody.data(), sbBody.size());/*, [=](size_t) {
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send set user battle ship request body to " << clientInfo << ".";
        });*/
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send set user battle ship request body to " << clientInfo << ".";
    }

    void    BattleAPI::sendChatMsgReq(commun::engine::ChanelType chanelType, const std::string &msg)
    {
        commun::net::req::SendChatMsgReq    chatMsgReq;
        msgpack::sbuffer                    sbBody;

        sendHeaderPacket(commun::net::req::Type::SEND_CHAT_MSG_REQ, mId);
        chatMsgReq.setChanelType(chanelType);
        chatMsgReq.setMessage(msg);
        msgpack::pack(sbBody, chatMsgReq);

        const std::string   clientInfo = mClientSocket.getInfo();

        mClientSocket.write(sbBody.data(), sbBody.size());/*, [=](size_t) {
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send send chat msg request body to " << clientInfo
                                                             << " with chanel type : " << chatMsgReq.getChanelType() << " and message : "
                                                             << chatMsgReq.getMessage() << "." <<std::endl;
        });*/
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send send chat msg request body to " << clientInfo
                                                                 << " with chanel type : " << chatMsgReq.getChanelType() << " and message : "
                                                                 << chatMsgReq.getMessage() << "." <<std::endl;
    }

    void    BattleAPI::shootShipReq(size_t pos)
    {
        commun::net::req::ShootShipReq  shipReq;
        msgpack::sbuffer                sbBody;
    
        sendHeaderPacket(commun::net::req::Type::SHOOT_SHIP_REQ, mId);
        shipReq.setShootPos(pos);
        msgpack::pack(sbBody, shipReq);

        const std::string   clientInfo = mClientSocket.getInfo();

        mClientSocket.write(sbBody.data(), sbBody.size());/*, [=](size_t) {
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send shoot ship request body to " << clientInfo
                                                             << " with position : " << shipReq.getShootPos() << ".";
        });*/
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send shoot ship request body to " << clientInfo
                                                                 << " with position : " << shipReq.getShootPos() << ".";
    }

    void    BattleAPI::gameReadyToLaunchReq()
    {
        commun::net::req::GameReadyToLaunchReq  readyToLaunchReq;
        msgpack::sbuffer                        sbBody;

        sendHeaderPacket(commun::net::req::Type::GAME_READY_TO_LAUNCH_REQ, mId);
        msgpack::pack(sbBody, readyToLaunchReq);

        const std::string   clientInfo = mClientSocket.getInfo();

        mClientSocket.write(sbBody.data(), sbBody.size());/*, [=](size_t) {
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send game ready to launch request body to " << clientInfo << ".";
        });*/
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send game ready to launch request body to " << clientInfo << ".";
    }

    void    BattleAPI::yourTurnToPlayReq()
    {
        commun::net::req::YourTurnToPlayReq turnToPlayReq;
        msgpack::sbuffer                    sbBody;

        sendHeaderPacket(commun::net::req::Type::YOUR_TURN_TO_PLAY_REQ, mId);
        msgpack::pack(sbBody, turnToPlayReq);

        const std::string   clientInfo = mClientSocket.getInfo();

        mClientSocket.write(sbBody.data(), sbBody.size());/*, [=](size_t) {
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send your turn to play request body to " << clientInfo << ".";
        });*/
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send your turn to play request body to " << clientInfo << ".";
    }

    void    BattleAPI::endGameStatusReq(commun::engine::FinalGameStatus finalGameStatus)
    {
        commun::net::req::EndGameStatusReq  gameStatusReq;
        msgpack::sbuffer                    sbBody;

        sendHeaderPacket(commun::net::req::Type::END_GAME_STATUS_REQ, mId);
        gameStatusReq.setFinalGameStatus(finalGameStatus);
        msgpack::pack(sbBody, gameStatusReq);

        const std::string   clientInfo = mClientSocket.getInfo();

        mClientSocket.write(sbBody.data(), sbBody.size());/*, [=](size_t) {
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send end game status request body to " << clientInfo
                                                             << " with final game status : " << gameStatusReq.getFinalGameStatus() << ".";
        });*/
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send end game status request body to " << clientInfo
                                                                 << " with final game status : " << gameStatusReq.getFinalGameStatus() << ".";
    }

    void    BattleAPI::sendHeaderPacket(commun::net::req::Type type, unsigned short clientId)
    {
        commun::net::PacketHeader   header;
        msgpack::sbuffer            sb;

        header.mCmdType = type;
        header.mClientId = clientId;
        msgpack::pack(sb, header);

        const std::string   clientInfo = mClientSocket.getInfo();

        mClientSocket.write(sb.data(), sb.size());/*, [=](size_t) {
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send header (type : " << type << ") to " << clientInfo << ".";
        });*/
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Send header (type : " << type << ") to " << clientInfo << ".";
    }

}
}
}