//!
//! @file ConfException.hpp
//! @author jbruel
//! @date 01/11/18
//!

#ifndef SPACEBATTLE_SERVER_CONFEXCEPTION_HPP
# define SPACEBATTLE_SERVER_CONFEXCEPTION_HPP

# include "Commun/Exception/IException.hpp"

//!
//! @namespace spcbttl
//!
namespace spcbttl
{
    //!
    //! @class ConfException
    //! @brief Conf exception.
    //!
    class   ConfException : public IException
    {
    public:
        //!
        //! @brief Default constructor.
        //! @param msg Exception message.
        //!
        explicit ConfException(const std::string &msg) : IException(msg) { }
    };
}



#endif //SPACEBATTLE_SERVER_CONFEXCEPTION_HPP
