//!
//! @file Type.hpp
//! @author jbruel
//! @date 05/11/18
//!

#ifndef SPACEBATTLE_COMMUN_REQUESTS_TYPE_HPP
# define SPACEBATTLE_COMMUN_REQUESTS_TYPE_HPP

# include <msgpack.hpp>

//!
//! @namespace spcbttl
//!
namespace spcbttl
{
//!
//! @namespace commun
//!
namespace commun
{
//!
//! @namespace net
//!
namespace net
{
//!
//! @namespace req
//!
namespace req
{

    //!
    //! @enum Type
    //! @brief Request type description
    //!
    enum    Type
    {
        KEEP_ALIVE_REQ = 0,
        AUTHENTICATE_REQ = 1,
        AUTHENTICATE_RESP = 2,
        GET_ROOM_LIST_REQ = 3,
        GET_ROOM_LIST_RESP = 4,
        CREATE_ROOM_REQ = 5,
        CREATE_ROOM_RESP = 6,
        JOIN_ROOM_REQ = 7,
        JOIN_ROOM_RESP = 8,
        VIEW_ROOM_REQ = 9,
        VIEW_ROOM_RESP = 10,
        EXIT_ROOM_REQ = 11,
        LAUNCH_GAME_REQ = 12,
        LAUNCH_GAME_RESP = 13,
        LOBBY_STATE_UPDATE_RESP = 14,
        SET_USER_BATTLESHIP_REQ = 20,
        SET_USER_BATTLESHIP_RESP = 21,
        SEND_CHAT_MSG_REQ = 22,
        BROADCAST_CHAT_MSG_REQ = 23,
        SHOOT_SHIP_REQ = 24,
        SHOOT_SHIP_RESP = 25,
        SHOOT_STATE_RESP = 26,
        END_GAME_STATUS_REQ = 27,
        GAME_READY_TO_LAUNCH_REQ = 28,
        YOUR_TURN_TO_PLAY_REQ = 29,
        NONE = 99
    };
}
}
}
}

MSGPACK_ADD_ENUM(spcbttl::commun::net::req::Type);

#endif //SPACEBATTLE_COMMUN_REQUESTS_TYPE_HPP
