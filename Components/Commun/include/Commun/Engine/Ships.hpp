//!
//! @file Ships.hpp
//! @author jbruel
//! @date 19/11/18
//!

#ifndef SPACEBATTLE_CLIENT_SHIPS_HPP
# define SPACEBATTLE_CLIENT_SHIPS_HPP

# include <msgpack.hpp>
# include <cstddef>
# include <utility>
# include <array>

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
//! @namespace engine
//!
namespace engine
{

    //!
    //! @namespace Ship
    //!
    namespace Ship
    {
        using Destroyer = size_t; //!< Destroyer ship type.
        using Submarine = std::array<size_t, 2>; //!< Submarine ship type.
        using Cruiser = std::array<size_t, 3>; //!< Cruiser ship type.
        using Battleship = std::array<size_t, 4>; //!< Battleship ship type.
        using Carrier = std::array<size_t, 5>; //!< Carrier ship type.
    }

    //!
    //! @struct Ships
    //! @brief Define all ships in the game.
    //!
    struct  Ships
    {
        Ship::Destroyer   mDestroyer; //!< Destroyer ship type.
        Ship::Submarine   mSubmarine; //!< Submarine ship type.
        Ship::Cruiser     mCruiser1; //!< First cruiser ship type.
        Ship::Cruiser     mCruiser2; //!< Second cruiser ship type.
        Ship::Battleship  mBattleship; //!< Battleship ship type.
        Ship::Carrier     mCarrier; //!< Carrier ship type.

        MSGPACK_DEFINE(mDestroyer, mSubmarine, mCruiser1, mCruiser2, mBattleship, mCarrier);
    };

}
}
}

#endif //SPACEBATTLE_CLIENT_SHIPS_HPP
