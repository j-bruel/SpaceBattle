//!
//! @file CoreException.hpp
//! @author jbruel
//! @date 01/11/18
//!

#ifndef SPACEBATTLE_SERVER_COREEXCEPTION_HPP
# define SPACEBATTLE_SERVER_COREEXCEPTION_HPP

# include "Commun/Exception/IException.hpp"

//!
//! @namespace spcbttl
//!
namespace spcbttl
{
    //!
    //! @class CoreException
    //! @brief Core exception.
    //!
    class   CoreException : public IException
    {
    public:
        //!
        //! @brief Default constructor.
        //! @param msg Exception message.
        //!
        explicit CoreException(const std::string &msg) : IException(msg) { }
    };
}



#endif //SPACEBATTLE_SERVER_COREEXCEPTION_HPP
