//!
//! @file Network/BattleAPI.hpp
//! @author jbruel
//! @date 20/11/18
//!

#ifndef SPACEBATTLE_SERVER_NETWORK_BATTLEAPI_HPP
# define SPACEBATTLE_SERVER_NETWORK_BATTLEAPI_HPP

# include "Commun/Network/Requests/State.hpp"
# include "Commun/Room/State.hpp"
# include "Commun/Engine/TimeLimit.hpp"
# include "Commun/Engine/Ships.hpp"
# include "Commun/Engine/Chanel.hpp"
# include "Commun/Engine/ShootState.hpp"
# include "Commun/Engine/FinalGameStatus.hpp"
# include "Commun/Engine/ClientState.hpp"
# include <sckcpp/Client.hpp>

//! @namespace spcbttl
//!
namespace spcbttl
{
//!
//! @namespace server
//!
namespace server
{
//!
//! @namespace net
//!
namespace net
{

    //!
    //! @class BattleAPI
    //! @brief
    //!
    class BattleAPI
    {
    public:
        //!
        //! @brief Constructor
        //!
        BattleAPI() = default;
        //!
        //! @brief Copy constructor.
        //! @warning Not available.
        //!
        BattleAPI(const BattleAPI &) = delete;
        //!
        //! @brief Equal overload operator.
        //! @warning Not available.
        //!
        BattleAPI   &operator=(const BattleAPI &) = delete;
        //!
        //! @brief Destructor
        //!
        ~BattleAPI() = default;

    public:
        //!
        //! @brief Send KEEP_ALIVE_REQ.
        //! @param clientSocket Destination player (client).
        //! @param id Client ID.
        //!
        void    keepAliveReq(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id);
        //!
        //! @brief Send AUTHENTICATE_REQ.
        //! @param clientSocket Destination player (client).
        //! @param id Client ID.
        //! @param playerName Player name.
        //!
        void    authReq(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id, const std::string &playerName);
        //!
        //! @brief Send AUTHENTICATE_RESP.
        //! @param clientSocket Destination player (client).
        //! @param id Client ID.
        //! @param playerName Player name.
        //! @param state Request state.
        //!
        void    authResp(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id, const std::string &playerName, commun::net::req::State state);
        //!
        //! @brief Send GET_ROOM_LIST_REQ.
        //! @param clientSocket Destination player (client).
        //! @param id Client ID.
        //!
        void    getRoomListReq(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id);
        //!
        //! @brief Send GET_ROOM_LIST_RESP.
        //! @param clientSocket Destination player (client).
        //! @param id Client ID.
        //! @param rooms Rooms with name and state.
        //!
        void    getRoomListResp(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id, const std::map<std::string, commun::room::State> &rooms);
        //!
        //! @brief Send CREATE_ROOM_REQ.
        //! @param clientSocket Destination player (client).
        //! @param id Client ID.
        //! @param roomName Room name.
        //! @param timeLimit Time limit.
        //! @param isViewerAllow Tell is viewer is allow.
        //!
        void    createRoomReq(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id, const std::string &roomName, commun::engine::TimeLimit timeLimit, bool isViewerAllow);
        //!
        //! @brief Send CREATE_ROOM_RESP.
        //! @param clientSocket Destination player (client).
        //! @param id Client ID.
        //! @param roomName Room name.
        //! @param timeLimit Time limit.
        //! @param isViewerAllow Tell is viewer is allow.
        //! @param state Request state.
        //!
        void    createRoomResp(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id, const std::string &roomName, commun::engine::TimeLimit timeLimit, bool isViewerAllow, commun::net::req::State state);
        //!
        //! @brief Send JOIN_ROOM_REQ.
        //! @param clientSocket Destination player (client).
        //! @param id Client ID.
        //! @param roomName Room name.
        //!
        void    joinRoomReq(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id, const std::string &roomName);
        //!
        //! @brief Send JOIN_ROOM_RESP.
        //! @param clientSocket Destination player (client).
        //! @param id Client ID.
        //! @param roomName Room name.
        //! @param timeLimit Time limit.
        //! @param isViewerAllow Tell is viewer is allow.
        //! @param state Request state.
        //!
        void    joinRoomResp(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id, const std::string &roomName, commun::engine::TimeLimit timeLimit, bool isViewerAllow, commun::net::req::State state);
        //!
        //! @brief Send VIEW_ROOM_REQ.
        //! @param clientSocket Destination player (client).
        //! @param id Client ID.
        //! @param roomName Room name.
        //!
        void    viewRoomReq(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id, const std::string &roomName);
        //!
        //! @brief Send VIEW_ROOM_RESP.
        //! @param clientSocket Destination player (client).
        //! @param id Client ID.
        //! @param roomName Room name.
        //! @param roomState Room state.
        //!
        void    viewRoomResp(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id, const std::string &roomName, commun::net::req::State roomState);
        //!
        //! @brief Send EXIT_ROOM_REQ.
        //! @param clientSocket Destination player (client).
        //! @param id Client ID.
        //! @param roomName Room name.
        //!
        void    exitRoomReq(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id, const std::string &roomName);
        //!
        //! @brief Send LAUNCH_GAME_REQ.
        //! @param clientSocket Destination player (client).
        //! @param id Client ID.
        //!
        void    launchGameReq(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id);
        //!
        //! @brief Send LAUNCH_GAME_RESP.
        //! @param clientSocket Destination player (client).
        //! @param id Client ID.
        //! @param state Request state.
        //!
        void    launchGameResp(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id, commun::net::req::State state);
        //!
        //! @brief Send LOBBY_STATE_UPDATE_RESP.
        //! @param clientSocket Destination player (client).
        //! @param id Client ID.
        //! @param clients Rooms with name and state.
        //!
        void    lobbyStateUpdateResp(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id, const std::map<std::string, commun::engine::ClientState > &clients);
        //!
        //! @brief Send SET_USER_BATTLE_SHIP_REQ.
        //! @param clientSocket Destination player (client).
        //! @param id Client ID.
        //! @param ships Ships informations
        //!
        void    setUserBattleshipReq(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id, const commun::engine::Ships &ships);
        //!
        //! @brief Send SET_USER_BATTLE_SHIP_RESP.
        //! @param clientSocket Destination player (client).
        //! @param id Client ID.
        //! @param ships Ships informations
        //! @param state Request state.
        //! @param destClient Destination client battle ship update.
        //!
        void    setUserBattleshipResp(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id, const commun::engine::Ships &ships, commun::net::req::State state, unsigned short destClient);
        //!
        //! @brief Send SEND_CHAT_MSG_REQ.
        //! @param clientSocket Destination player (client).
        //! @param id Client ID.
        //! @param chanelType Chanel type.
        //! @param msg Message.
        //!
        void    sendChatMsgReq(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id, commun::engine::ChanelType chanelType, const std::string &msg);
        //!
        //! @brief Send BROADCAST_CHAT_MSG_RESP.
        //! @param players Destination players (clients).
        //! @param chanelType Chanel type.
        //! @param msg Message.
        //! @param playerName Player name.
        //!
        void    broadcastChatMsgResp(std::vector<std::pair<std::reference_wrapper<sckcpp::tcp::ClientSocket>, unsigned short>> &players, commun::engine::ChanelType chanelType, const std::string &msg, const std::string &playerName);
        //!
        //! @brief Send SHOOT_SHIP_REQ.
        //! @param clientSocket Destination player (client).
        //! @param id Client ID.
        //! @param pos Shoot pos.
        //!
        void    shootShipReq(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id, size_t pos);
        //!
        //! @brief Send SHOOT_SHIP_RESP.
        //! @param clientSocket Destination player (client).
        //! @param id Client ID.
        //! @param shootState Shoot state.
        //! @param pos Shoot pos.
        //! @param clientId Client ID.
        //!
        void    shootShipResp(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id, commun::engine::ShootState shootState, size_t pos, unsigned short clientId);
        //!
        //! @brief Send GAME_READY_TO_LAUNCH_REQ.
        //! @param clientSocket Destination player (client).
        //! @param id Client ID.
        //!
        void    gameReadyToLaunchReq(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id);
        //!
        //! @brief Send YOUR_TURN_TO_PLAY_REQ.
        //! @param clientSocket Destination player (client).
        //! @param id Client ID.
        //!
        void    yourTurnToPlayReq(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id);
        //!
        //! @brief Send END_GAME_STATUS_REQ.
        //! @param clientSocket Destination player (client).
        //! @param id Client ID.
        //! @param finalGameStatus Final game status.
        //!
        void    endGameStatusReq(sckcpp::tcp::ClientSocket &clientSocket, unsigned short id, commun::engine::FinalGameStatus finalGameStatus);

    private:
        //!
        //! @brief Send to client the packet header.
        //! @param clientDest Destination client.
        //! @param type Request type.
        //! @param clientId Client ID.
        //!
        void    sendHeaderPacket(sckcpp::tcp::ClientSocket &clientDest, commun::net::req::Type type, unsigned short clientId);
    };

}
}
}

#endif //SPACEBATTLE_SERVER_NETWORK_BATTLEAPI_HPP
