//!
//! @file Network/Requests/State.hpp
//! @author jbruel
//! @date 13/11/18
//!

#ifndef SPACEBATTLE_CLIENT_REQUEST_STATE_HPP
# define SPACEBATTLE_CLIENT_REQUEST_STATE_HPP

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
    //! @enum State
    //! @brief Request state.
    //!
    enum   State
    {
        ERROR_ALREADY_AUTH_STATE = 100,
        ERROR_NOT_AUTH_STATE = 101,
        ERROR_MAX_ROOM_NB_EXCEEDED_STATE = 102,
        ERROR_PLAYER_ALREADY_IN_ROOM_STATE = 103,
        ERROR_ROOM_ALREADY_EXIST_STATE = 104,
        ERROR_INVALID_ROOM_NAME_STATE = 105,
        ERROR_MAX_ROOM_PLAYER_EXCEEDED_STATE = 107,
        ERROR_ROOM_DOES_NOT_EXIST_STATE = 109,
        ERROR_GAME_ALREADY_RUNNING_STATE = 110,
        ERROR_MAX_ROOM_VIEWER_EXCEEDED_STATE = 112,
        ERROR_PLAYER_NOT_IN_ROOM_STATE = 115,
        ERROR_INVALID_POSITION_STATE = 118,
        ERROR_INVALID_SHIP_STATE = 119,
        ERROR_MAX_CLIENT_NB_EXCEEDED_STATE = 120,
        ERROR_VIEW_NOT_ALLOW = 121,
        ERROR_NOT_PLAYER_TURN = 122,
        NO_STATE = 999
    };

}
}
}
}

MSGPACK_ADD_ENUM(spcbttl::commun::net::req::State);


#endif //SPACEBATTLE_CLIENT_REQUEST_STATE_HPP
