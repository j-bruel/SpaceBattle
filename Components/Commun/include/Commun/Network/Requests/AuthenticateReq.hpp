//!
//! @file AuthenticateReq.hpp
//! @author jbruel
//! @date 03/11/18
//!

#ifndef SPACEBATTLE_SERVER_AUTHENTICATEREQ_HPP
# define SPACEBATTLE_SERVER_AUTHENTICATEREQ_HPP

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
    //! @class AuthenticateReq
    //! @brief Authenticate request.
    //!
    class   AuthenticateReq : public IRequest
    {
    private:
        std::string mPlayerName; //!< Player name

    public:
        MSGPACK_DEFINE(mPlayerName);

    public:
        //!
        //! @brief Default constructor.
        //!
        AuthenticateReq() = default;
        //!
        //! @brief Copy constructor.
        //! @param authenticateReq Authenticate request.
        //!
        AuthenticateReq(const AuthenticateReq &authenticateReq) : IRequest(authenticateReq), mPlayerName(authenticateReq.mPlayerName) { }
        //!
        //! @brief Equal operator overload.
        //! @param authenticateReq Authenticate request.
        //! @return Request copy.
        //!
        AuthenticateReq    &operator=(const AuthenticateReq &authenticateReq)
        {
            mPlayerName = authenticateReq.mPlayerName;
            return ((*this));
        }
        //!
        //! @brief Destructor.
        //!
        ~AuthenticateReq() override = default;

    public:
        //!
        //! @brief Extract request type.
        //! @return Request type.
        //!
        inline Type getType() const override { return (Type::AUTHENTICATE_REQ); }

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
    };

}
}
}
}

#endif //SPACEBATTLE_SERVER_AUTHENTICATEREQ_HPP
