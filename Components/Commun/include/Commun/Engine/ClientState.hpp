//!
//! @file ClientState.hpp
//! @author jbruel
//! @date 27/11/18
//!

#ifndef SPACEBATTLE_COMMUN_ENGINE_CLIENTSTATE_HPP
# define SPACEBATTLE_COMMUN_ENGINE_CLIENTSTATE_HPP

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
//! @namespace engine
//!
namespace engine
{

    //!
    //! @enum ClientState
    //! @brief Define client state.
    //!
    enum    ClientState
    {
        PLAYER,
        VIEWER
    };

}
}
}

MSGPACK_ADD_ENUM(spcbttl::commun::engine::ClientState);

#endif //SPACEBATTLE_COMMUN_ENGINE_CLIENTSTATE_HPP
