//!
//! @file ShootShipResp.hpp
//! @author jbruel
//! @date 19/11/18
//!

#ifndef SPACEBATTLE_SERVER_SHOOTSHIPRESP_HPP
# define SPACEBATTLE_SERVER_SHOOTSHIPRESP_HPP

# include "IRequest.hpp"
# include <string>
# include <Commun/Engine/Chanel.hpp>
# include <Commun/Engine/ShootState.hpp>

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
    //! @class ShootShipResp
    //! @brief Send shoot state.
    //!
    class   ShootShipResp : public IRequest
    {
    private:
        engine::ShootState  mShootState;
        size_t              mPos;
        size_t              mClientId;

    public:
        MSGPACK_DEFINE(mShootState, mPos, mClientId);

    public:
        //!
        //! @brief Default constructor.
        //!
        ShootShipResp() = default;
        //!
        //! @brief Copy constructor.
        //! @param shootShipResp Send shoot state.
        //!
        ShootShipResp(const ShootShipResp &shootShipResp) :  IRequest(shootShipResp), mShootState(shootShipResp.mShootState),
                                                             mPos(shootShipResp.mPos), mClientId(shootShipResp.mClientId) { }
        //!
        //! @brief Equal operator overload.
        //! @param shootShipResp Send shoot state.
        //! @return Request copy.
        //!
        ShootShipResp    &operator=(const ShootShipResp &shootShipResp)
        {
            mShootState = shootShipResp.mShootState;
            mPos = shootShipResp.mPos;
            mClientId = shootShipResp.mClientId;
            return ((*this));
        }
        //!
        //! @brief Destructor.
        //!
        ~ShootShipResp() override = default;

    public:
        //!
        //! @brief Extract request type.
        //! @return Request type.
        //!
        inline Type getType() const override { return (Type::SHOOT_SHIP_RESP); }

    public:
        //!
        //! @brief Set shoot state.
        //! @param shootState Shoot state.
        //!
        inline void                 setShootState(const engine::ShootState &shootState) { mShootState = shootState; }
        //!
        //! @brief Extract current shoot state.
        //! @return Shoot state.
        //!
        inline engine::ShootState   getShootState() const { return (mShootState); }
        //!
        //! @brief Set shoot pos.
        //! @param shootPos Shoot pos.
        //!
        inline void                 setShootPos(size_t shootPos) { mPos = shootPos; }
        //!
        //! @brief Extract shoot pos.
        //! @return Shoot pos.
        //!
        inline size_t               getShootPos() const { return (mPos); }
        //!
        //! @brief Set shoot client id.
        //! @param clientId Client ID.
        //!
        inline void                 setShootClientId(size_t clientId) { mClientId = clientId; }
        //!
        //! @brief Extract shoot client ID.
        //! @return Client ID.
        //!
        inline size_t               getShootClientId() const { return (mClientId); }
    };

}
}
}
}

#endif //SPACEBATTLE_SERVER_SHOOTSHIPRESP_HPP
