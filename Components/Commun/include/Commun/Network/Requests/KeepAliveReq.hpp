//!
//! @file KeepAliveReq.hpp
//! @author jbruel
//! @date 03/11/18
//!

#ifndef SPACEBATTLE_SERVER_KEEPALIVEREQ_HPP
# define SPACEBATTLE_SERVER_KEEPALIVEREQ_HPP

# include "IRequest.hpp"
# include <string>

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
    //! @class KeepAliveReq
    //! @brief Keep alive request.
    //!
    class   KeepAliveReq : public IRequest
    {
    public:
        MSGPACK_DEFINE();

    public:
        //!
        //! @brief Default constructor.
        //!
        KeepAliveReq() = default;
        //!
        //! @brief Copy constructor.
        //! @param keepAliveReq Keep alive request.
        //!
        KeepAliveReq(const KeepAliveReq &keepAliveReq) = default;
        //!
        //! @brief Equal operator overload.
        //! @param keepAliveReq Keep Alive request.
        //! @return Request copy.
        //!
        KeepAliveReq    &operator=(const KeepAliveReq &keepAliveReq) = default;
        //!
        //! @brief Destructor.
        //!
        ~KeepAliveReq() override = default;

    public:
        //!
        //! @brief Extract request type.
        //! @return Request type.
        //!
        inline Type getType() const override { return (Type::KEEP_ALIVE_REQ); }
    };

}
}
}
}

#endif //SPACEBATTLE_SERVER_KEEPALIVEREQ_HPP
