//
// Created by grosso_a on 07/11/18.
//

# include "Engine/Room/Battlefield.hpp"

namespace spcbttl
{
    namespace server
    {
        namespace engine
        {
            Battlefield::Battlefield():
                _game_started(false)
            {

            }

            void Battlefield::game_start()
            {
                boost::unique_lock<boost::shared_mutex>  lock(this->_lock);
                _game_started = true;
            }

            bool Battlefield::has_ship(std::shared_ptr<Player> player)
            {
                boost::shared_lock<boost::shared_mutex>     lock(this->_lock);
                unsigned short                              playerID = player_allowed(player);

                if (playerID == 2) {
                    return false;
                }
                for (const std::pair<std::shared_ptr<Ship>, std::shared_ptr<Player>> &ship : _ships) {
                    if (ship.second == player) {
                        return true;
                    }
                }
                return false;
            }

            unsigned short Battlefield::player_allowed(std::shared_ptr<Player> player)
            {
                unsigned short                              playerID;

                for (playerID=0; playerID <= 1; playerID++) {
                    if (_players[playerID] == player) {
                        return playerID;
                    }
                }
                return 2;
            }


            bool Battlefield::set_players(std::shared_ptr<Player> player1, std::shared_ptr<Player> player2)
            {
                boost::unique_lock<boost::shared_mutex>    lock(this->_lock);
                if (_game_started) {
                    return false;
                }
                if (_players[0] == nullptr) {
                    _players[0] = std::move(player1);
                } else {
                    return false;
                }
                if (_players[1] == nullptr) {
                    _players[1] = std::move(player2);
                } else {
                    return false;
                }
                return true;
            }

            bool Battlefield::set_ship(std::shared_ptr<Player> player, std::shared_ptr<Ship> ship)
            {
                boost::unique_lock<boost::shared_mutex>     lock(this->_lock);
                unsigned short                              playerID = player_allowed(player);

                if (playerID == 2 || !_game_started || !ship->validate()) {
                    return false;
                }
                for (const std::shared_ptr<Ship::ShipPart> &part : ship->parts()) {
                    if (_board[part->coordinate()].shippart[playerID] == nullptr) {
                        _board[part->coordinate()].shippart[playerID] = part;
                        _board[part->coordinate()].ship[playerID] = ship;
                    } else {
                        return false;
                    }
                }
                _ships.push_back(std::make_pair(ship, player));
                return true;
            }

            void Battlefield::clear_ship(std::shared_ptr<Player> player)
            {
                boost::unique_lock<boost::shared_mutex> lock(this->_lock);
                unsigned short                          playerID = player_allowed(std::move(player));

                if (playerID == 2 || _game_started) {
                    return;
                }
                _ships.remove_if([&](const std::pair<std::shared_ptr<Ship>, std::shared_ptr<Player>> &pair)
                    {
                        if (pair.second == player) {
                            for (const std::shared_ptr<Ship::ShipPart> &part : pair.first->parts()) {
                                if (_board[part->coordinate()].shippart[playerID] != nullptr) {
                                    _board[part->coordinate()].shippart[playerID] = nullptr;
                                    _board[part->coordinate()].ship[playerID] = nullptr;
                                }
                            }
                            return true;
                        } else {
                            return false;
                        }
                    });
            }

            bool Battlefield::is_started()
            {
                boost::shared_lock<boost::shared_mutex>  lock(this->_lock);
                return _game_started;
            }

            commun::engine::ShootState Battlefield::shoot(std::shared_ptr<Player> player, uint8_t pos)
            {
                boost::unique_lock<boost::shared_mutex> lock(this->_lock);
                unsigned short                          playerID = player_allowed(std::move(player));

                if (playerID == 2 || !_game_started || pos >= (GAME_BOARD_SIZE * GAME_BOARD_SIZE)) {
                    return commun::engine::ShootState::FAILED;
                } else {
                    if (_board[pos].shippart[playerID] == nullptr
                        || _board[pos].shippart[playerID]->status() == Ship::ShipPartStatus::DESTROYED) {
                        return commun::engine::ShootState::FAILED;
                    } else if (_board[pos].shippart[playerID]->status() == Ship::ShipPartStatus::GOOD){
                        _board[pos].shippart[playerID]->shoot();
                        if (_board[pos].ship[playerID]->destroyed()) {
                            return commun::engine::ShootState::SUNK_TOUCHDOWN;
                        } else {
                            return commun::engine::ShootState::IMPACTED;
                        }
                    }
                }
                return commun::engine::ShootState::FAILED;
            }

            unsigned short Battlefield::ship_not_destroyed(std::shared_ptr<Player> player)
            {
                boost::shared_lock<boost::shared_mutex>  lock(this->_lock);
                unsigned short                           value = 0;

                for (const std::pair<std::shared_ptr<Ship>, std::shared_ptr<Player>> &ship : _ships) {
                    if (!ship.first->destroyed() && ship.second == player) {
                        value++;
                    }
                }
                return value;
            }
        }
    }
}
