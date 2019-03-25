//!
//! @file Chanel.hpp
//! @author jbruel
//! @date 19/11/18
//!

#ifndef SPACEBATTLE_CLIENT_CHANEL_HPP
# define SPACEBATTLE_CLIENT_CHANEL_HPP

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
    //! @enum ChanelType
    //! @brief Define chanel type.
    //!
    enum    ChanelType
    {
        GAME,
        GENERAL,
        NONE
    };

}
}
}

MSGPACK_ADD_ENUM(spcbttl::commun::engine::ChanelType);

#endif //SPACEBATTLE_CLIENT_CHANEL_HPP
