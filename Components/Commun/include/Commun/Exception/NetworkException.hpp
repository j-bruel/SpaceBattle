//!
//! @file NetworkException.hpp
//! @author jbruel
//! @date 01/11/18
//!

#ifndef SPACEBATTLE_SERVER_NETWORKEXCEPTION_HPP
# define SPACEBATTLE_SERVER_NETWORKEXCEPTION_HPP

# include "Commun/Exception/IException.hpp"

//!
//! @namespace spcbttl
//!
namespace spcbttl
{
    //!
    //! @class NetworkException
    //! @brief Network exception.
    //!
    class   NetworkException : public IException
    {
    public:
        //!
        //! @brief Default constructor.
        //! @param msg Exception message.
        //!
        explicit NetworkException(const std::string &msg) : IException(msg) { }
    };
}



#endif //SPACEBATTLE_SERVER_NETWORKEXCEPTION_HPP
