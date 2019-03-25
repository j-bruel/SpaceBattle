//!
//! @file IRequest.hpp
//! @author jbruel
//! @date 03/11/18
//!

#ifndef SPACEBATTLE_SERVER_IREQUEST_HPP
# define SPACEBATTLE_SERVER_IREQUEST_HPP

# include "Commun/Network/Requests/Type.hpp"
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
//! @namespace net
//!
namespace net
{
//!
//! @namespace req
//!
namespace req
{
    //!
    //! @interface IRequest
    //! @brief Request interface.
    //!
    class   IRequest
    {
    public:
        //!
        //! @brief Default constructor.
        //!
        IRequest() = default;
        //!
        //! @brief Copy constructor.
        //!
        IRequest(const IRequest &) = default;
        //!
        //! @brief Equal operator overload.
        //! @return Request copy.
        //!
        IRequest    &operator=(const IRequest &) = default;
        //!
        //! @brief Destructor.
        //!
        virtual ~IRequest() = default;

    public:
        //!
        //! @brief Extract request type.
        //! @return Request type.
        //!
        virtual Type    getType() const = 0;
    };

}
}
}
}

#endif //SPACEBATTLE_SERVER_IREQUEST_HPP
