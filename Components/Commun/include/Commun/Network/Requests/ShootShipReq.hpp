//!
//! @file ShootShipReq.hpp
//! @author jbruel
//! @date 19/11/18
//!

#ifndef SPACEBATTLE_SERVER_SHOOTSHIPREQ_HPP
# define SPACEBATTLE_SERVER_SHOOTSHIPREQ_HPP

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
    //! @class ShootShipReq
    //! @brief Shoot ship request.
    //!
    class   ShootShipReq : public IRequest
    {
    private:
        size_t  mPos; //!< Shoot position.

    public:
        MSGPACK_DEFINE(mPos);

    public:
        //!
        //! @brief Default constructor.
        //!
        ShootShipReq() = default;
        //!
        //! @brief Copy constructor.
        //! @param shootShipReq Shoot request.
        //!
        ShootShipReq(const ShootShipReq &shootShipReq) : IRequest(shootShipReq), mPos(shootShipReq.mPos) { }
        //!
        //! @brief Equal operator overload.
        //! @param shootShipReq Shoot request.
        //! @return Request copy.
        //!
        ShootShipReq    &operator=(const ShootShipReq &shootShipReq)
        {
            mPos = shootShipReq.mPos;
            return ((*this));
        }
        //!
        //! @brief Destructor.
        //!
        ~ShootShipReq() override = default;

    public:
        //!
        //! @brief Extract request type.
        //! @return Request type.
        //!
        inline Type getType() const override { return (Type::SHOOT_SHIP_REQ); }

    public:
        //!
        //! @brief Set shoot position.
        //! @param shootPos Shoot position.
        //!
        inline void     setShootPos(size_t shootPos) { mPos = shootPos; }
        //!
        //! @brief Extract shoot position.
        //! @return Shoot position.
        //!
        inline size_t   getShootPos() const { return (mPos); }
    };

}
}
}
}

#endif //SPACEBATTLE_SERVER_SHOOTSHIPREQ_HPP
