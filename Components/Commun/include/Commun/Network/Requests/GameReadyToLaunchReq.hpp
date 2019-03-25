//!
//! @file GameReadyToLaunchReq.hpp
//! @author jbruel
//! @date 03/11/18
//!

#ifndef SPACEBATTLE_COMMUN_NETWORK_REQUESTS_GAME_READY_TO_LAUNCH_REQ_HPP
# define SPACEBATTLE_COMMUN_NETWORK_REQUESTS_GAME_READY_TO_LAUNCH_REQ_HPP

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
    //! @class GameReadyToLaunchReq
    //! @brief Game ready to launch request.
    //!
    class   GameReadyToLaunchReq : public IRequest
    {
    public:
        MSGPACK_DEFINE();

    public:
        //!
        //! @brief Default constructor.
        //!
        GameReadyToLaunchReq() = default;
        //!
        //! @brief Copy constructor.
        //! @param gameReadyToLaunchReq Game ready to launch request.
        //!
        GameReadyToLaunchReq(const GameReadyToLaunchReq &gameReadyToLaunchReq) = default;
        //!
        //! @brief Equal operator overload.
        //! @param gameReadyToLaunchReq Game ready to launch request.
        //! @return gameReadyToLaunchReq copy.
        //!
        GameReadyToLaunchReq    &operator=(const GameReadyToLaunchReq &gameReadyToLaunchReq) = default;
        //!
        //! @brief Destructor.
        //!
        ~GameReadyToLaunchReq() override = default;

    public:
        //!
        //! @brief Extract request type.
        //! @return Request type.
        //!
        inline Type getType() const override { return (Type::GAME_READY_TO_LAUNCH_REQ); }
    };

}
}
}
}

#endif //SPACEBATTLE_COMMUN_NETWORK_REQUESTS_GAME_READY_TO_LAUNCH_REQ_HPP
