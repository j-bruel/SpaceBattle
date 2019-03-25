//!
//! @file IException.hpp
//! @author jbruel
//! @date 01/11/18
//!

#ifndef SPACEBATTLE_SERVER_IEXCEPTION_HPP
# define SPACEBATTLE_SERVER_IEXCEPTION_HPP

# include <exception>
# include <string>

//!
//! @namespace spcbttl
//!
namespace spcbttl
{
    //!
    //! @class IException
    //! @brief Exception interface.
    //!
    class   IException : public std::exception
    {
    private:
        std::string     mMsg; //!< Message link to the exception.

    public:
        //!
        //! @brief Default constructor.
        //! @param msg Exception message.
        //!
        explicit IException(const std::string &msg) : mMsg(msg) {}

    public:
        //!
        //! @brief Extract exception message.
        //! @return Exception message.
        //!
        inline const char   *what() const noexcept override {return (mMsg.c_str());}
    };
}


#endif //SPACEBATTLE_SERVER_IEXCEPTION_HPP
