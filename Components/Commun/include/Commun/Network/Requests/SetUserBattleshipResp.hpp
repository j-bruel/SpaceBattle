//!
//! @file SetUserBattleshipResp.hpp
//! @author jbruel
//! @date 19/11/18
//!

#ifndef SPACEBATTLE_SERVER_SETUSERBATTLESHIPRESP_HPP
# define SPACEBATTLE_SERVER_SETUSERBATTLESHIPRESP_HPP

# include "IRequest.hpp"
# include "Commun/Network/Requests/State.hpp"
# include "Commun/Engine/Ships.hpp"
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
    //! @class SetUserBattleshipResp
    //! @brief SetUserBattleship request.
    //!
    class   SetUserBattleshipResp : public IRequest
    {
    private:
        engine::Ships   mShips; //!< Ships
        State           mState; //!< Actual state.
        unsigned short  mDestClientId; //!< Dest client ID.

    public:
        MSGPACK_DEFINE(mShips, mState, mDestClientId);

    public:
        //!
        //! @brief Default constructor.
        //!
        SetUserBattleshipResp() = default;
        //!
        //! @brief Copy constructor.
        //! @param setUserBattleshipResp SetUserBattleship response.
        //!
        SetUserBattleshipResp(const SetUserBattleshipResp &setUserBattleshipResp) : IRequest(setUserBattleshipResp), mShips(setUserBattleshipResp.mShips),
                                                                                    mState(setUserBattleshipResp.mState), mDestClientId(setUserBattleshipResp.mDestClientId) { }
        //!
        //! @brief Equal operator overload.
        //! @param setUserBattleshipResp SetUserBattleship response.
        //! @return Request copy.
        //!
        SetUserBattleshipResp    &operator=(const SetUserBattleshipResp &setUserBattleshipResp)
        {
            mShips = setUserBattleshipResp.mShips;
            mState = setUserBattleshipResp.mState;
            mDestClientId = setUserBattleshipResp.mDestClientId;
            return ((*this));
        }
        //!
        //! @brief Destructor.
        //!
        ~SetUserBattleshipResp() override = default;

    public:
        //!
        //! @brief Extract request type.
        //! @return Request type.
        //!
        inline Type getType() const override { return (Type::SET_USER_BATTLESHIP_RESP); }

    public:
        //!
        //! @brief Set player name.
        //! @param ships Ships
        //!
        inline void                 setShips(const engine::Ships &ships) { mShips = ships; }
        //!
        //! @brief Extract ships.
        //! @return Ships.
        //!
        inline const engine::Ships &getShips() const { return (mShips); }
        //!
        //! @brief Set player name.
        //! @param id Dest client ID.
        //!
        inline void                 setDestClientID(unsigned short id) { mDestClientId = id; }
        //!
        //! @brief Extract client ID.
        //! @return dest client ID..
        //!
        inline unsigned short       getDestClientID() const { return (mDestClientId); }
        //!
        //! @brief Set state.
        //! @param state Current state.
        //!
        inline void                 setState(State state) { mState = state; }
        //!
        //! @brief Extract current state.
        //! @return State.
        //!
        inline State                getState() const { return (mState); }
    };

}
}
}
}

#endif //SPACEBATTLE_SERVER_SETUSERBATTLESHIPRESP_HPP
