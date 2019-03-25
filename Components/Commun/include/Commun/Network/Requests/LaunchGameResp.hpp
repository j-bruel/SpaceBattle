//!
//! @file LaunchGameResp.hpp
//! @author jbruel
//! @date 03/11/18
//!

#ifndef SPACEBATTLE_SERVER_LAUNCHGAMERESP_HPP
# define SPACEBATTLE_SERVER_LAUNCHGAMERESP_HPP

# include "IRequest.hpp"
# include "Commun/Network/Requests/State.hpp"
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
    //! @class LaunchGameResp
    //! @brief Launch game response.
    //!
    class   LaunchGameResp : public IRequest
    {
    private:
        State       mState; //!< Actual state.

    public:
        MSGPACK_DEFINE(mState);

    public:
        //!
        //! @brief Default constructor.
        //!
        LaunchGameResp() = default;
        //!
        //! @brief Copy constructor.
        //! @param launchGameResp Launch game response.
        //!
        LaunchGameResp(const LaunchGameResp &launchGameResp) :  IRequest(launchGameResp), mState(launchGameResp.mState) { }
        //!
        //! @brief Equal operator overload.
        //! @param launchGameResp Launch game response.
        //! @return Request copy.
        //!
        LaunchGameResp    &operator=(const LaunchGameResp &launchGameResp)
        {
            mState = launchGameResp.mState;
            return ((*this));
        }
        //!
        //! @brief Destructor.
        //!
        ~LaunchGameResp() override = default;

    public:
        //!
        //! @brief Extract request type.
        //! @return Request type.
        //!
        inline Type getType() const override { return (Type::LAUNCH_GAME_RESP); }

    public:
        //!
        //! @brief Set state.
        //! @param state Current state.
        //!
        inline void         setState(State state) { mState = state; }
        //!
        //! @brief Extract current state.
        //! @return State.
        //!
        inline State        getRoomState() const { return (mState); }
    };

}
}
}
}

#endif //SPACEBATTLE_SERVER_AUTHENTICATERESP_HPP
