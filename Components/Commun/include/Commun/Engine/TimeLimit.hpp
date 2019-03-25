//!
//! @file Engine/TimeLimit.hpp
//! @author jbruel
//! @date 12/11/18
//!

#ifndef SPACEBATTLE_CLIENT_TIMELIMIT_HPP
# define SPACEBATTLE_CLIENT_TIMELIMIT_HPP

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
    //! @enum TimeLimit
    //! @brief Define game time limit.
    //!
    enum    TimeLimit
    {
        FOURTEEN_MIN,
        THIRTY_MIN,
        FORTY_FILE_MIN,
        NO_LIMIT
    };

}
}
}

MSGPACK_ADD_ENUM(spcbttl::commun::engine::TimeLimit);

#endif //SPACEBATTLE_CLIENT_TIMELIMIT_HPP
