//!
//! @file ShootState.hpp
//! @author jbruel
//! @date 19/11/18
//!

#ifndef SPACEBATTLE_CLIENT_SHOOTSTATE_HPP
#define SPACEBATTLE_CLIENT_SHOOTSTATE_HPP

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
    //! @enum ShootState
    //! @brief Define current shoot state.
    //!
    enum    ShootState
    {
        IMPACTED,
        SUNK_TOUCHDOWN,
        FAILED
    };

}
}
}

MSGPACK_ADD_ENUM(spcbttl::commun::engine::ShootState);

#endif //SPACEBATTLE_CLIENT_SHOOTSTATE_HPP
