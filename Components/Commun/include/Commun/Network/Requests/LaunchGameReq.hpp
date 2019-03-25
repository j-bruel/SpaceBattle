//!
//! @file LaunchGameReq.hpp
//! @author jbruel
//! @date 03/11/18
//!

#ifndef SPACEBATTLE_SERVER_LAUNCHGAMEREQ_HPP
# define SPACEBATTLE_SERVER_LAUNCHGAMEREQ_HPP

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
    //! @class LaunchGameReq
    //! @brief Launch game request.
    //!
    class   LaunchGameReq : public IRequest
    {
    public:
        MSGPACK_DEFINE();

    public:
        //!
        //! @brief Default constructor.
        //!
        LaunchGameReq() = default;
        //!
        //! @brief Copy constructor.
        //! @param launchGameReq Launch game request.
        //!
        LaunchGameReq(const LaunchGameReq &launchGameReq) = default;
        //!
        //! @brief Equal operator overload.
        //! @param launchGameReq Launch gasme request.
        //! @return Request copy.
        //!
        LaunchGameReq    &operator=(const LaunchGameReq &launchGameReq) = default;
        //!
        //! @brief Destructor.
        //!
        ~LaunchGameReq() override = default;

    public:
        //!
        //! @brief Extract request type.
        //! @return Request type.
        //!
        inline Type getType() const override { return (Type::LAUNCH_GAME_REQ); }
    };

}
}
}
}

#endif //SPACEBATTLE_SERVER_KEEPALIVEREQ_HPP
