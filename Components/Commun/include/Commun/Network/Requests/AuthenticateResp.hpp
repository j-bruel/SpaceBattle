//!
//! @file AuthenticateResp.hpp
//! @author jbruel
//! @date 03/11/18
//!

#ifndef SPACEBATTLE_SERVER_AUTHENTICATERESP_HPP
# define SPACEBATTLE_SERVER_AUTHENTICATERESP_HPP

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
    //! @class AuthenticateResp
    //! @brief Authenticate response.
    //!
    class   AuthenticateResp : public IRequest
    {
    private:
        std::string mPlayerName; //!< Player name.
        State       mState; //!< Actual state.

    public:
        MSGPACK_DEFINE(mPlayerName, mState);

    public:
        //!
        //! @brief Default constructor.
        //!
        AuthenticateResp() = default;
        //!
        //! @brief Copy constructor.
        //! @param authenticateResp Authenticate response.
        //!
        AuthenticateResp(const AuthenticateResp &authenticateResp) :    IRequest(authenticateResp), mPlayerName(authenticateResp.mPlayerName),
                                                                        mState(authenticateResp.mState) { }
        //!
        //! @brief Equal operator overload.
        //! @param authenticateResp Authenticate response.
        //! @return Request copy.
        //!
        AuthenticateResp    &operator=(const AuthenticateResp &authenticateResp)
        {
            mPlayerName = authenticateResp.mPlayerName;
            mState = authenticateResp.mState;
            return ((*this));
        }
        //!
        //! @brief Destructor.
        //!
        ~AuthenticateResp() override = default;

    public:
        //!
        //! @brief Extract request type.
        //! @return Request type.
        //!
        inline Type getType() const override { return (Type::AUTHENTICATE_RESP); }

    public:
        //!
        //! @brief Set player name.
        //! @param playerName Player name.
        //!
        inline void                 setPlayerName(const std::string &playerName) { mPlayerName = playerName; }
        //!
        //! @brief Extract player name.
        //! @return Player name.
        //!
        inline const std::string    &getPlayerName() const { return (mPlayerName); }
        //!
        //! @brief Set state.
        //! @param state Current state.
        //!
        inline void                 setState(State state) { mState = state; }
        //!
        //! @brief Extract current state.
        //! @return State.
        //!
        inline State                getRoomState() const { return (mState); }
    };

}
}
}
}

#endif //SPACEBATTLE_SERVER_AUTHENTICATERESP_HPP
