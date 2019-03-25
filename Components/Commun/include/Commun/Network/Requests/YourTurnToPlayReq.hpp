//!
//! @file YourTurnToPlayReq.hpp
//! @author jbruel
//! @date 03/11/18
//!

#ifndef SPACEBATTLE_COMMUN_NETWORK_REQUESTS_YOUR_TURN_TO_PLAY_REQ_HPP
# define SPACEBATTLE_COMMUN_NETWORK_REQUESTS_YOUR_TURN_TO_PLAY_REQ_HPP

# include "IRequest.hpp"

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
    //! @class YourTurnToPlayReq
    //! @brief Your turn to play request.
    //!
    class   YourTurnToPlayReq : public IRequest
    {
    public:
        MSGPACK_DEFINE();

    public:
        //!
        //! @brief Default constructor.
        //!
        YourTurnToPlayReq() = default;
        //!
        //! @brief Copy constructor.
        //! @param yourTurnToPlayReq Game ready to launch request.
        //!
        YourTurnToPlayReq(const YourTurnToPlayReq &yourTurnToPlayReq) = default;
        //!
        //! @brief Equal operator overload.
        //! @param yourTurnToPlayReq Game ready to launch request.
        //! @return YourTurnToPlayReq copy.
        //!
        YourTurnToPlayReq    &operator=(const YourTurnToPlayReq &yourTurnToPlayReq) = default;
        //!
        //! @brief Destructor.
        //!
        ~YourTurnToPlayReq() override = default;

    public:
        //!
        //! @brief Extract request type.
        //! @return Request type.
        //!
        inline Type getType() const override { return (Type::YOUR_TURN_TO_PLAY_REQ); }
    };

}
}
}
}

#endif //SPACEBATTLE_COMMUN_NETWORK_REQUESTS_YOUR_TURN_TO_PLAY_REQ_HPP
