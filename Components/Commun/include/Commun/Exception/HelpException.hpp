//!
//! @file HelpException.hpp
//! @author jbruel
//! @date 01/11/18
//!

#ifndef SPACEBATTLE_SERVER_HELPEXCEPTION_HPP
# define SPACEBATTLE_SERVER_HELPEXCEPTION_HPP

# include "Commun/Exception/IException.hpp"

//!
//! @namespace spcbttl
//!
namespace spcbttl
{
    //!
    //! @class HelpException
    //! @brief Help exception.
    //!
    class   HelpException : public IException
    {
    public:
        //!
        //! @brief Default constructor.
        //! @param msg Exception message.
        //!
        explicit HelpException(const std::string &msg) : IException(msg) { }
    };
}



#endif //SPACEBATTLE_SERVER_HELPEXCEPTION_HPP
