//!
//! @file SAuthenticateReq.hpp
//! @author jbruel
//! @date 03/11/18
//!

#ifndef SPACEBATTLE_COMMUN_NETWORK_REQUESTS_SAUTHENTICATEREQ_HPP
# define SPACEBATTLE_COMMUN_NETWORK_REQUESTS_SAUTHENTICATEREQ_HPP

# include "Commun/Network/Requests/IRequest.hpp"
# include <sckcpp/Client.hpp>
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
    //! @class SAuthenticateReq
    //! @brief Authenticate request.
    //!
    class   SAuthenticateReq : public IRequest
    {
    private:
        std::string                 mPlayerName; //!< Player name
        sckcpp::tcp::ClientSocket   &mPlayer; //!< Player.

    public:
        //!
        //! @brief Default constructor.
        //!
        SAuthenticateReq(sckcpp::tcp::ClientSocket &client) : mPlayerName(std::string()), mPlayer(client) { }
        //!
        //! @brief Copy constructor.
        //! @param authenticateReq Authenticate request.
        //! @param client Client socket.
        //!
        SAuthenticateReq(const SAuthenticateReq &authenticateReq, sckcpp::tcp::ClientSocket &client) :  IRequest(authenticateReq),
                                                                                                        mPlayerName(authenticateReq.mPlayerName),
                                                                                                        mPlayer(client) { }
        //!
        //! @brief Equal operator overload.
        //! @param authenticateReq Authenticate request.
        //! @return Request copy.
        //!
        SAuthenticateReq    &operator=(const SAuthenticateReq &authenticateReq)
        {
            mPlayerName = authenticateReq.mPlayerName;
            return ((*this));
        }
        //!
        //! @brief Destructor.
        //!
        ~SAuthenticateReq() override = default;

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

    public:
        //!
        //! @brief Get player client socket.
        //! @return Player
        //!
        inline sckcpp::tcp::ClientSocket    &getPlayer() const { return (mPlayer); }
    };

}
}
}
}

#endif //SPACEBATTLE_COMMUN_NETWORK_REQUESTS_SAUTHENTICATEREQ_HPP
