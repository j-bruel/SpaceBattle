//
// Created by grosso_a on 07/11/18.
//

#ifndef T_CPP_SPACEBATTLE_2018_BATTLEFIELD_HPP
#define T_CPP_SPACEBATTLE_2018_BATTLEFIELD_HPP

#include <cstdint>
#include <boost/fusion/container/vector.hpp>
#include <boost/thread/thread.hpp>
#include <vector>
#include "Engine/Room/Player.hpp"
#include "Engine/Room/Ship.hpp"
#include <Conf/Engine.hpp>
#include <Commun/Engine/ShootState.hpp>

//!
//! @namespace spcbttl
//!
namespace spcbttl
{
    //!
    //! @namespace server
    //!
    namespace server
    {
        //!
        //! @namespace engine
        //!
        namespace engine
        {
            /**
             * @class Battlefield
             * @brief Battlefield store the game board and ships.
             *
             */
            class Battlefield
            {
            private:
                /**
                 * Store a Battle field case.
                 */
                struct Case {
                    std::shared_ptr<Ship::ShipPart>   shippart[2];
                    std::shared_ptr<Ship>             ship[2];
                };

                boost::shared_mutex                                                     _lock;
                std::array<Case, GAME_BOARD_SIZE*GAME_BOARD_SIZE>                       _board;
                std::list<std::pair<std::shared_ptr<Ship>, std::shared_ptr<Player>>>    _ships;
                std::shared_ptr<Player>                                                 _players[2];
                bool                                                                    _game_started;

                /**
                 * @brief Check if player is Player or viewer.
                 * @return 0 or 1 if is Player and 2 if Viewer
                 */
                unsigned short player_allowed(std::shared_ptr<Player>);

            public:
                Battlefield();

                /**
                 * @brief Start the game and lock set_ship.
                 */
                void game_start();

                /**
                 * @brief Check is the game is started.
                 * @return
                 */
                bool is_started();


                /**
                 * @brief Check if the player has ship setted on the battlefield.
                 * @param player The player to check.
                 * @return
                 */
                bool has_ship(std::shared_ptr<Player> player);

                /**
                 * @brief Set players.
                 * @param player1 The first player.
                 * @param player2 The second player.
                 * @return False if one player is null
                 */
                bool set_players(std::shared_ptr<Player> player1, std::shared_ptr<Player> player2);

                /**
                 * @brief Set ship of selected player and also check if the ship is valid.
                 * @param player The owner of the ship.
                 * @param ship The ship to set on the board.
                 * @return False if the ship is invalid, case are already used or if player is invalid.
                 */
                bool set_ship(std::shared_ptr<Player> player, std::shared_ptr<Ship> ship);


                /**
                 * @brief Remove all ship of selected player of the board
                 * @param player The selected player.
                 */
                void clear_ship(std::shared_ptr<Player> player);


                /**
                 * @brief Shoot ship of selected player.
                 * @param player The target player of the shoot.
                 * @param pos The case position to shoot.
                 * @return The shoot state (IMPACTED, SUNK_TOUCHDOWN, FAILED)
                 */
                commun::engine::ShootState shoot(std::shared_ptr<Player> player, uint8_t pos);

                /**
                 * @brief Count the number of ships not destroyer of selected player
                 * @param player The player selected.
                 * @return Number of intact ships.
                 */
                unsigned short ship_not_destroyed(std::shared_ptr<Player> player);
            };
        }
    }
}

#endif //T_CPP_SPACEBATTLE_2018_BATTLEFIELD_HPP
