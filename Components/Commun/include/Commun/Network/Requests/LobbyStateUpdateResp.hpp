//!
//! @file LobbyStateUpdateResp.hpp
//! @author jbruel
//! @date 03/11/18
//!

#ifndef SPACEBATTLE_SERVER_LOBBYSTATEUPDATERESP_HPP
# define SPACEBATTLE_SERVER_LOBBYSTATEUPDATERESP_HPP

# include "IRequest.hpp"
# include "Commun/Engine/ClientState.hpp"
# include <string>
# include <map>

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
    //! @class LobbyStateUpdateResp
    //! @brief Get current lobby state update.
    //!
    class   LobbyStateUpdateResp : public IRequest
    {
    private:
        std::map<std::string, engine::ClientState>  mPlayersState;

    public:
        MSGPACK_DEFINE(mPlayersState);

    public:
        //!
        //! @brief Default constructor.
        //!
        LobbyStateUpdateResp() = default;
        //!
        //! @brief Copy constructor.
        //! @param lobbyStateUpdateResp Get current lobby state update.
        //!
        LobbyStateUpdateResp(const LobbyStateUpdateResp &lobbyStateUpdateResp) : IRequest(lobbyStateUpdateResp) { mPlayersState = lobbyStateUpdateResp.mPlayersState; }
        //!
        //! @brief Equal operator overload.
        //! @param lobbyStateUpdateResp Get current lobby state update.
        //! @return Request copy.
        //!
        LobbyStateUpdateResp    &operator=(const LobbyStateUpdateResp &lobbyStateUpdateResp)
        {
            mPlayersState = lobbyStateUpdateResp.mPlayersState;
            return ((*this));
        }
        //!
        //! @brief Destructor.
        //!
        ~LobbyStateUpdateResp() override = default;

    public:
        //!
        //! @brief Extract request type.
        //! @return Request type.
        //!
        inline Type getType() const override { return (Type::LOBBY_STATE_UPDATE_RESP); }

    public:
        //!
        //! @brief Add a player state.
        //! @param playerName Player name.
        //! @param state Player state.
        //!
        inline void                                             addPlayerState(const std::string &playerName, engine::ClientState state) { mPlayersState[playerName] = state; }
        //!
        //! @brief Extract player name.
        //! @param playerName Player name.
        //! @return Player state.
        //!
        inline engine::ClientState                              getPlayerState(const std::string &playerName) const { return (mPlayersState.at(playerName)); }
        //!
        //! @brief Extract rooms.
        //! @return All rooms and states.
        //!
        inline const std::map<std::string, engine::ClientState> getPlayers() const { return (mPlayersState); }
    };

}
}
}
}

#endif //SPACEBATTLE_SERVER_LOBBYSTATEUPDATERESP_HPP
