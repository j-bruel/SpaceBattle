//!
//! @file Idx.hpp
//! @author jbruel
//! @date 01/11/18
//!

#ifndef SPACEBATTLE_SERVER_TOOLS_LOG_IDX_HPP
# define SPACEBATTLE_SERVER_TOOLS_LOG_IDX_HPP

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
//! @namespace tool
//!
namespace tool
{
//!
//! @namespace log
//!
namespace log
{

    //!
    //! @enum Idx
    //! @brief Log index, tell witch output log use.
    //!
    enum    Idx
    {
        IN_FILE,
        IN_CONSOLE,
        IN_FILE_AND_CONSOLE
    };

}
}
}
}

#endif //SPACEBATTLE_SERVER_TOOLS_LOG_IDX_HPP
