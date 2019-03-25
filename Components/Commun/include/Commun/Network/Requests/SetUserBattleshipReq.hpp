//!
//! @file SetUserBattleshipReq.hpp
//! @author jbruel
//! @date 19/11/18
//!

#ifndef SPACEBATTLE_SERVER_SETUSERBATTLESHIPREQ_HPP
# define SPACEBATTLE_SERVER_SETUSERBATTLESHIPREQ_HPP

# include "IRequest.hpp"
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
    //! @class SetUserBattleshipReq
    //! @brief SetUserBattleship request.
    //!
    class   SetUserBattleshipReq : public IRequest
    {
    private:
        engine::Ships   mShips; //!< Ships

    public:
        MSGPACK_DEFINE(mShips);

    public:
        //!
        //! @brief Default constructor.
        //!
        SetUserBattleshipReq() = default;
        //!
        //! @brief Copy constructor.
        //! @param setUserBattleshipReq SetUserBattleship request.
        //!
        SetUserBattleshipReq(const SetUserBattleshipReq &setUserBattleshipReq) : IRequest(setUserBattleshipReq), mShips(setUserBattleshipReq.mShips) { }
        //!
        //! @brief Equal operator overload.
        //! @param setUserBattleshipReq SetUserBattleship request.
        //! @return Request copy.
        //!
        SetUserBattleshipReq    &operator=(const SetUserBattleshipReq &setUserBattleshipReq)
        {
            mShips = setUserBattleshipReq.mShips;
            return ((*this));
        }
        //!
        //! @brief Destructor.
        //!
        ~SetUserBattleshipReq() override = default;

    public:
        //!
        //! @brief Extract request type.
        //! @return Request type.
        //!
        inline Type getType() const override { return (Type::SET_USER_BATTLESHIP_REQ); }

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
        inline const engine::Ships  &getShips() const { return (mShips); }
    };

}
}
}
}

#endif //SPACEBATTLE_SERVER_SETUSERBATTLESHIPREQ_HPP
