//!
//! @file BattleAPI.hpp
//! @author jbruel
//! @date 20/11/18
//!

#ifndef SPACEBATTLE_CLIENT_NETWORK_BATTLEAPI_HPP
# define SPACEBATTLE_CLIENT_NETWORK_BATTLEAPI_HPP

# include "Commun/Network/Requests/State.hpp"
# include "Commun/Room/State.hpp"
# include "Commun/Engine/TimeLimit.hpp"
# include "Commun/Engine/Ships.hpp"
# include "Commun/Engine/Chanel.hpp"
# include "Commun/Engine/ShootState.hpp"
# include "Commun/Engine/FinalGameStatus.hpp"
# include <sckcpp/Client.hpp>

//! @namespace spcbttl
//!
namespace spcbttl
{
//!
//! @namespace client
//!
namespace client
{
//!
//! @namespace net
//!
namespace net
{

    //!
    //! @class BattleAPI
    //! @brief API for BattleSpace game.
    //!
    class BattleAPI
    {
    private:
        sckcpp::tcp::ClientSocket   &mClientSocket; //!< Client socket.
        unsigned short              mId; //!< Client ID.

    public:
        //!
        //! @brief Constructor
        //!
        BattleAPI(sckcpp::tcp::ClientSocket &clientSocket) : mClientSocket(clientSocket), mId(0) {}
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
        inline void setID(unsigned short id) { mId = id; }

    public:
        //!
        //! @brief Send KEEP_ALIVE_REQ.
        //!
        void    keepAliveReq();
        //!
        //! @brief Send AUTHENTICATE_REQ.
        //! @param playerName Player name.
        //!
        void    authReq(const std::string &playerName);
        //!
        //! @brief Send GET_ROOM_LIST_REQ.
        //!
        void    getRoomListReq();
        //!
        //! @brief Send CREATE_ROOM_REQ.
        //! @param roomName Room name.
        //! @param timeLimit Time limit.
        //! @param isViewerAllow Tell is viewer is allow.
        //!
        void    createRoomReq(const std::string &roomName, commun::engine::TimeLimit timeLimit, bool isViewerAllow);
        //!
        //! @brief Send JOIN_ROOM_REQ.
        //! @param roomName Room name.
        //!
        void    joinRoomReq(const std::string &roomName);
        //!
        //! @brief Send VIEW_ROOM_REQ.
        //! @param roomName Room name.
        //!
        void    viewRoomReq(const std::string &roomName);
        //!
        //! @brief Send EXIT_ROOM_REQ.
        //! @param roomName Room name.
        //!
        void    exitRoomReq(const std::string &roomName);
        //!
        //! @brief Send LAUNCH_GAME_REQ.
        //!
        void    launchGameReq();
        //!
        //! @brief Send SET_USER_BATTLE_SHIP_REQ.
        //! @param ships Ships informations
        //!
        void    setUserBattleshipReq(const commun::engine::Ships &ships);
        //!
        //! @brief Send SEND_CHAT_MSG_REQ.
        //! @param chanelType Chanel type.
        //! @param msg Message.
        //!
        void    sendChatMsgReq(commun::engine::ChanelType chanelType, const std::string &msg);
        //!
        //! @brief Send SHOOT_SHIP_REQ.
        //! @param pos Shoot pos.
        //!
        void    shootShipReq(size_t pos);
        //!
        //! @brief Send GAME_READY_TO_LAUNCH_REQ.
        //!
        void    gameReadyToLaunchReq();
        //!
        //! @brief Send YOUR_TURN_TO_PLAY_REQ.
        //!
        void    yourTurnToPlayReq();
        //!
        //! @brief Send END_GAME_STATUS_REQ.
        //! @param finalGameStatus Final game status.
        //!
        void    endGameStatusReq(commun::engine::FinalGameStatus finalGameStatus);

    private:
        //!
        //! @brief Send to client the packet header.
        //! @param type Request type.
        //! @param clientId Client ID.
        //!
        void    sendHeaderPacket(commun::net::req::Type type, unsigned short clientId);
    };

}
}
}

#endif //SPACEBATTLE_CLIENT_NETWORK_BATTLEAPI_HPP
