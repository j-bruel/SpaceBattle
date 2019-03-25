//!
//! @file Room/State.hpp
//! @author jbruel
//! @date 12/11/18
//!

#ifndef SPACEBATTLE_CLIENT_STATE_HPP
# define SPACEBATTLE_CLIENT_STATE_HPP

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
//! @namespace room
//!
namespace room
{

    //!
    //! @enum State
    //!
    enum class  State
    {
        NEW,
        WAITING_FOR_PLAYER,
        WAITING_FOR_LAUNCH,
        IN_PROFRESS,
        FINISH,
        NONE
    };

}
}
}

MSGPACK_ADD_ENUM(spcbttl::commun::room::State);

#endif //SPACEBATTLE_CLIENT_STATE_HPP
