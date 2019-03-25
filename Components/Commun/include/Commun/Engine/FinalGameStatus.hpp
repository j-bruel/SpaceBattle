//!
//! @file FinalGameStatus.hpp
//! @author jbruel
//! @date 12/11/18
//!

#ifndef SPACEBATTLE_CLIENT_FINAL_GAME_STATUS_HPP
# define SPACEBATTLE_CLIENT_FINAL_GAME_STATUS_HPP

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
    //! @enum FinalGameStatus
    //! @brief Define final game status.
    //!
    enum    FinalGameStatus
    {
        WIN,
        LOOSE,
        ERROR
    };

}
}
}

MSGPACK_ADD_ENUM(spcbttl::commun::engine::FinalGameStatus);

#endif //SPACEBATTLE_CLIENT_FINAL_GAME_STATUS_HPP
