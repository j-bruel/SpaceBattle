//!
//! @file ConfException.hpp
//! @author jbruel
//! @date 01/11/18
//!

#ifndef SPACEBATTLE_COMMUN_EXCEPTION_BUFFERDATAMANAGEREXCEPTION_HPP
# define SPACEBATTLE_COMMUN_EXCEPTION_BUFFERDATAMANAGEREXCEPTION_HPP

# include "Commun/Exception/IException.hpp"

//!
//! @namespace spcbttl
//!
namespace spcbttl
{
    //!
    //! @class BufferDataManagerException
    //! @brief BufferDataManager exception.
    //!
    class   BufferDataManagerException : public IException
    {
    public:
        //!
        //! @brief Default constructor.
        //! @param msg Exception message.
        //!
        explicit BufferDataManagerException(const std::string &msg) : IException(msg) { }
    };
}



#endif //SPACEBATTLE_COMMUN_EXCEPTION_BUFFERDATAMANAGEREXCEPTION_HPP
