//
// Created by grosso_a on 18/11/18.
//

#include "Engine/Room/Room.hpp"

namespace spcbttl
{
    namespace server
    {
        namespace engine
        {
            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            Room<MAX_ROOMS, MAX_PLAYERS>::Room(TRoomManager &manager, std::shared_ptr<spcbttl::commun::net::req::CreateRoomReq> request):
                TCommander(*this),
                _manager(manager),
                _current_player(0),
                _state(commun::room::State::NEW),
                _allow_viewers(request->isViewerAllow()),
                _name(std::string(request->getRoomName())),
                _time_limit(request->getLimitType())
            {
                this->set_command(commun::net::req::Type::LAUNCH_GAME_REQ, new TCommand(&Room::launch_game));
                this->set_command(commun::net::req::Type::SET_USER_BATTLESHIP_REQ, new TCommand(&Room::set_user_battleship));
                this->set_command(commun::net::req::Type::SEND_CHAT_MSG_REQ, new TCommand(&Room::send_chat_msg));
                this->set_command(commun::net::req::Type::SHOOT_SHIP_REQ, new TCommand(&Room::shoot_ship));
                _players[0] = nullptr;
                _players[1] = nullptr;
                this->_start_time = std::chrono::system_clock::now();
            }

            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            unsigned short  Room<MAX_ROOMS, MAX_PLAYERS>::which_player(unsigned short id)
            {
                for (unsigned short playerId = 0; playerId < 2; playerId++) {
                    if (this->_players[playerId] != nullptr && this->_players[playerId]->id() == id) {
                        return playerId;
                    }
                }
                return 2;
            }

            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            std::shared_ptr<Ship> Room<MAX_ROOMS, MAX_PLAYERS>::load_Destroyer(const commun::engine::Ship::Destroyer &destroyer)
            {
                return std::make_shared<Ship>(Ship({destroyer}));

            }

            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            std::shared_ptr<Ship> Room<MAX_ROOMS, MAX_PLAYERS>::load_Submarine(const commun::engine::Ship::Submarine &submarine)
            {
                return std::make_shared<Ship>(Ship({submarine[0], submarine[1]}));

            }

            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            std::shared_ptr<Ship> Room<MAX_ROOMS, MAX_PLAYERS>::load_Cruiser(const commun::engine::Ship::Cruiser &cruiser)
            {
                return std::make_shared<Ship>(Ship({cruiser[0], cruiser[1], cruiser[2]}));
            }

            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            std::shared_ptr<Ship> Room<MAX_ROOMS, MAX_PLAYERS>::load_Battleship(const commun::engine::Ship::Battleship &battleship)
            {
                return std::make_shared<Ship>(Ship({battleship[0], battleship[1], battleship[2], battleship[3]}));
            }

            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            std::shared_ptr<Ship> Room<MAX_ROOMS, MAX_PLAYERS>::load_Carrier(const commun::engine::Ship::Carrier &carrier)
            {
                return std::make_shared<Ship>(Ship({carrier[0], carrier[1], carrier[2], carrier[3], carrier[4]}));
            }


            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            void Room<MAX_ROOMS, MAX_PLAYERS>::execute(PacketPtr packet)
            {
                this->exec_command(packet->mPacketHeader.mCmdType, packet);
            }

            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            void Room<MAX_ROOMS, MAX_PLAYERS>::notExist(unsigned int, PacketPtr)
            {

            }

            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            void Room<MAX_ROOMS, MAX_PLAYERS>::set_user_battleship(TCommander &, PacketPtr packet)
            {
                boost::unique_lock<boost::shared_mutex>                             lock(this->_lock);
                std::shared_ptr<spcbttl::commun::net::req::SetUserBattleshipReq>    body;
                unsigned short                                                      playerID;
                std::shared_ptr<Ship>                                               ship_1_1;
                std::shared_ptr<Ship>                                               ship_1_2;
                std::shared_ptr<Ship>                                               ship_1_3;
                std::shared_ptr<Ship>                                               ship_2_3;
                std::shared_ptr<Ship>                                               ship_1_4;
                std::shared_ptr<Ship>                                               ship_1_5;

                LOG_(commun::tool::log::IN_CONSOLE, plog::debug) << "Room: set_user_battleship";
                playerID = this->which_player(packet->mPacketHeader.mClientId);
                if (playerID == 2) {
                    LOG_(commun::tool::log::IN_CONSOLE, plog::error) << "Room: set_user_battleship Failed. Player invalid.";
                    return;
                }
                if (!_battlefield.is_started() || _state != commun::room::State::IN_PROFRESS) {
                    LOG_(commun::tool::log::IN_CONSOLE, plog::error) << "Room: set_user_battleship Failed. Game not launched.";
                    return;
                }
                PlayerPtr player = _players[playerID];
                if (_battlefield.has_ship(player) > 0) {
                    LOG_(commun::tool::log::IN_CONSOLE, plog::error) << "Room: set_user_battleship Failed. Player already set his ship.";
                    return;
                }
                body = std::dynamic_pointer_cast<spcbttl::commun::net::req::SetUserBattleshipReq>(packet->mPacketBody);
                ship_1_1 = load_Destroyer(body->getShips().mDestroyer);
                ship_1_2 = load_Submarine(body->getShips().mSubmarine);
                ship_1_3 = load_Cruiser(body->getShips().mCruiser1);
                ship_2_3 = load_Cruiser(body->getShips().mCruiser2);
                ship_1_4 = load_Battleship(body->getShips().mBattleship);
                ship_1_5 = load_Carrier(body->getShips().mCarrier);
                if (!this->_battlefield.set_ship(player, ship_1_1)
                    || !this->_battlefield.set_ship(player, ship_1_2)
                    || !this->_battlefield.set_ship(player, ship_1_3)
                    || !this->_battlefield.set_ship(player, ship_2_3)
                    || !this->_battlefield.set_ship(player, ship_1_4)
                    || !this->_battlefield.set_ship(player, ship_1_5)) {
                    this->_battlefield.clear_ship(player);
                    LOG_(commun::tool::log::IN_CONSOLE, plog::error) << "Room: set_user_battleship Failed. Ship position is invalid.";
                    _api.setUserBattleshipResp(player->socket(), packet->mPacketHeader.mClientId, body->getShips(), commun::net::req::ERROR_INVALID_SHIP_STATE, player->id());
                } else {
                    LOG_(commun::tool::log::IN_CONSOLE, plog::debug) << "Room: set_user_battleship." << std::endl
                                                                     << " Ship_1_1 position is " << ship_1_1->print() << std::endl
                                                                     << " Ship_1_2 position is " << ship_1_2->print() << std::endl
                                                                     << " Ship_1_3 position is " << ship_1_3->print() << std::endl
                                                                     << " Ship_2_3 position is " << ship_2_3->print() << std::endl
                                                                     << " Ship_1_4 position is " << ship_1_4->print() << std::endl
                                                                     << " Ship_1_5 position is " << ship_1_5->print();
                    _api.setUserBattleshipResp(player->socket(), packet->mPacketHeader.mClientId, body->getShips(), commun::net::req::NO_STATE, player->id());
                    for (PlayerPtr viewer : _viewers) {
                        _api.setUserBattleshipResp(viewer->socket(), viewer->id(), body->getShips(), commun::net::req::NO_STATE, player->id());
                    }
                    if (_battlefield.has_ship(_players[0]) && _battlefield.has_ship(_players[1])) {
                        this->start_game();
                    }
                }
            }

            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            void Room<MAX_ROOMS, MAX_PLAYERS>::send_chat_msg(TCommander &, PacketPtr packet)
            {
                boost::shared_lock<boost::shared_mutex>                                                     lock(this->_lock);
                std::shared_ptr<spcbttl::commun::net::req::SendChatMsgReq>                                  body;
                std::vector<std::pair<std::reference_wrapper<sckcpp::tcp::ClientSocket>, unsigned short>>   clients;
                unsigned short                                                                              playerID;

                LOG_(commun::tool::log::IN_CONSOLE, plog::debug) << "Room: send_message";
                body = std::dynamic_pointer_cast<spcbttl::commun::net::req::SendChatMsgReq>(packet->mPacketBody);
                playerID = this->which_player(packet->mPacketHeader.mClientId);
                if (playerID == 2) {
                    LOG_(commun::tool::log::IN_CONSOLE, plog::error) << "Room: send_chat_msg Failed. Viewers messages not allowed.";
                    return;
                }
                for (unsigned short id=0; id < 2; id++) {
                    if (_players[id] != nullptr) {
                        clients.push_back(std::make_pair<std::reference_wrapper<sckcpp::tcp::ClientSocket>, unsigned short>(
                                _players[id]->socket(), _players[id]->id()));
                        LOG_(commun::tool::log::IN_CONSOLE, plog::debug)
                                    << "Room: send_chat_message player :" << _players[id]->id()
                                    << " send message :" << body->getMessage();
                    }
                }
                for (const PlayerPtr &viewer : _viewers) {
                    clients.push_back(std::make_pair<std::reference_wrapper<sckcpp::tcp::ClientSocket>, unsigned short>(
                            viewer->socket(), viewer->id()));
                    LOG_(commun::tool::log::IN_CONSOLE, plog::debug)
                                << "Room: send_chat_message player :" << viewer->id()
                                << " send message :" << body->getMessage();
                }
                _api.broadcastChatMsgResp(clients, body->getChanelType(), std::string(body->getMessage()), _players[playerID]->get_name());
            }

            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            void Room<MAX_ROOMS, MAX_PLAYERS>::shoot_ship(TCommander &, PacketPtr packet)
            {
                boost::unique_lock<boost::shared_mutex>                     lock(this->_lock);
                std::shared_ptr<spcbttl::commun::net::req::ShootShipReq>    body;
                unsigned short                                              playerID;

                LOG_(commun::tool::log::IN_CONSOLE, plog::debug) << "Room: shoot_ship";
                playerID = this->which_player(packet->mPacketHeader.mClientId);
                if (playerID == 2) {
                    LOG_(commun::tool::log::IN_CONSOLE, plog::error) << "Room: shoot_ship Failed. Player invalid.";
                    return;
                }
                if (playerID != _current_player) {
                    LOG_(commun::tool::log::IN_CONSOLE, plog::error) << "Room: shoot_ship Failed. Not your turn.";
                    return;
                }
                if (this->_state != commun::room::State::IN_PROFRESS) {
                    LOG_(commun::tool::log::IN_CONSOLE, plog::error) << "Room: shoot_ship Failed. Game not started.";
                    return;
                }
                PlayerPtr shooter = _players[playerID];
                PlayerPtr target = _players[((playerID + 1) % 2)];
                body = std::dynamic_pointer_cast<spcbttl::commun::net::req::ShootShipReq>(packet->mPacketBody);
                commun::engine::ShootState state = this->_battlefield.shoot(target, (uint8_t)body->getShootPos());
                LOG_(commun::tool::log::IN_CONSOLE, plog::debug) << "Room: shoot_ship Done."
                                                                 << " player :" << shooter->id()
                                                                 << " case :" << (unsigned short)body->getShootPos()
                                                                 << " status :" << state;
                for (unsigned short id=0; id < 2; id++) {
                    _api.shootShipResp(_players[id]->socket(), _players[id]->id(), state, body->getShootPos(), target->id());
                }
                for (const PlayerPtr &viewer : _viewers) {
                    _api.shootShipResp(viewer->socket(), viewer->id(), state, body->getShootPos(), target->id());
                }
                if (_battlefield.ship_not_destroyed(target) > 0) {
                    this->next_player();
                    LOG_(commun::tool::log::IN_CONSOLE, plog::debug) << "Room: Player "<< _players[_current_player]->id() << " turn.";
                    _api.yourTurnToPlayReq(_players[_current_player]->socket(), _players[_current_player]->id());
                } else {
                    LOG_(commun::tool::log::IN_CONSOLE, plog::debug) << "Room: Player "<< shooter->id() << " win.";
                    LOG_(commun::tool::log::IN_CONSOLE, plog::debug) << "Room: Player "<< target->id() << " loose.";
                    _state = commun::room::State::FINISH;
                }
            }


            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            void Room<MAX_ROOMS, MAX_PLAYERS>::launch_game(TCommander &, PacketPtr packet)
            {
                boost::unique_lock<boost::shared_mutex>                         lock(this->_lock);
                unsigned short                                                  playerID;

                LOG_(commun::tool::log::IN_CONSOLE, plog::debug) << "Room: launch_game";
                playerID = this->which_player(packet->mPacketHeader.mClientId);
                if (playerID == 2) {
                    LOG_(commun::tool::log::IN_CONSOLE, plog::error) << "Room: launch_game Failed. Player invalid.";
                    return;
                }
                if (!this->full_player() || _state == commun::room::State::WAITING_FOR_PLAYER) {
                    LOG_(commun::tool::log::IN_CONSOLE, plog::error) << "Room: launch_game Failed. Missing player.";
                    return;
                }
                PlayerPtr player = _players[playerID];
                if (_battlefield.is_started() || _state == commun::room::State::IN_PROFRESS) {
                    LOG_(commun::tool::log::IN_CONSOLE, plog::error) << "Room: launch_game Failed. Game already running.";
                    _api.launchGameResp(player->socket(), player->id(), commun::net::req::ERROR_GAME_ALREADY_RUNNING_STATE);
                    return;
                }
                player->ready();
                if (!_players[0]->is_ready() || !_players[1]->is_ready()) {
                    LOG_(commun::tool::log::IN_CONSOLE, plog::warning) << "Room: launch_game. Player "
                                                                       << player->id() <<" is ready. Waiting second player.";
                    _api.launchGameResp(player->socket(), player->id(), commun::net::req::NO_STATE);
                    return;
                } else {
                    _battlefield.set_players(_players[0], _players[1]);
                    _battlefield.game_start();
                    _state = commun::room::State::IN_PROFRESS;
                    LOG_(commun::tool::log::IN_CONSOLE, plog::debug) << "Room: launch_game. Game launched.";
                    _api.launchGameResp(player->socket(), player->id(), commun::net::req::NO_STATE);
                    for (PlayerPtr player : _players) {
                        _api.gameReadyToLaunchReq(player->socket(), player->id());
                    }
                    for (PlayerPtr player : _viewers) {
                        _api.gameReadyToLaunchReq(player->socket(), player->id());
                    }
                }
            }

            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            void Room<MAX_ROOMS, MAX_PLAYERS>::add_player(PlayerPtr player)
            {
                if (!this->full_player()) {
                    this->_lock.lock();
                    _players[_current_player] = player;
                    _current_player = (_current_player + 1) % 2;
                    this->_lock.unlock();
                    if (this->full_player()) {
                        _state = commun::room::State::WAITING_FOR_LAUNCH;
                    } else {
                        _state = commun::room::State::WAITING_FOR_PLAYER;
                    }
                }
            }

            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            void Room<MAX_ROOMS, MAX_PLAYERS>::add_viewer(PlayerPtr viewer)
            {
                boost::unique_lock<boost::shared_mutex> lock(this->_lock);
                _viewers.push_back(viewer);
            }

            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            bool Room<MAX_ROOMS, MAX_PLAYERS>::full_player()
            {
                for (auto player : _players) {
                    if (player == nullptr) {
                        return false;
                    }
                }
                return true;
            }

            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            bool Room<MAX_ROOMS, MAX_PLAYERS>::full_viewer()
            {
                return _viewers.size() >= MAX_VIEWER;
            }

            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            void Room<MAX_ROOMS, MAX_PLAYERS>::start_game()
            {
                this->_start_time = std::chrono::system_clock::now();
                LOG_(commun::tool::log::IN_CONSOLE, plog::debug) << "Room: Game Started.";
                LOG_(commun::tool::log::IN_CONSOLE, plog::debug) << "Room: Player "<< _players[_current_player]->id() << " turn.";
                _api.yourTurnToPlayReq(_players[_current_player]->socket(), _players[_current_player]->id());
            }

            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            void Room<MAX_ROOMS, MAX_PLAYERS>::del_viewer(PlayerPtr viewer)
            {
                boost::unique_lock<boost::shared_mutex> lock(this->_lock);
                _viewers.remove(viewer);
            }

            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            commun::room::State Room<MAX_ROOMS, MAX_PLAYERS>::status()
            {
                boost::shared_lock<boost::shared_mutex> lock(this->_lock);
                return _state;
            }

            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            const std::string  &Room<MAX_ROOMS, MAX_PLAYERS>::name()
            {
                boost::shared_lock<boost::shared_mutex> lock(this->_lock);
                return _name;
            }

            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            bool  Room<MAX_ROOMS, MAX_PLAYERS>::allow_viewers()
            {
                boost::shared_lock<boost::shared_mutex> lock(this->_lock);
                return _allow_viewers;
            }

            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            commun::engine::TimeLimit Room<MAX_ROOMS, MAX_PLAYERS>::time_limit()
            {
                boost::shared_lock<boost::shared_mutex> lock(this->_lock);
                return _time_limit;
            }

            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            std::chrono::time_point<std::chrono::system_clock> Room<MAX_ROOMS, MAX_PLAYERS>::start_time()
            {
                boost::shared_lock<boost::shared_mutex> lock(this->_lock);
                if (_state == commun::room::State::IN_PROFRESS) {
                    return this->_start_time;
                } else {
                    return std::chrono::system_clock::now();
                }
            }


            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            void Room<MAX_ROOMS, MAX_PLAYERS>::next_player()
            {
                _current_player = (_current_player + 1) % 2;
            }

            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            std::list<std::shared_ptr<Player>> Room<MAX_ROOMS, MAX_PLAYERS>::players()
            {
                boost::shared_lock<boost::shared_mutex> lock(this->_lock);
                std::list<PlayerPtr> pl;

                if (_players[0]) {
                    pl.push_back(_players[0]);
                }
                if (_players[1]) {
                    pl.push_back(_players[1]);
                }
                return pl;
            }

            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            std::list<std::shared_ptr<Player>> Room<MAX_ROOMS, MAX_PLAYERS>::viewers()
            {
                boost::shared_lock<boost::shared_mutex> lock(this->_lock);
                return _viewers;
            }

            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            std::shared_ptr<Player>  Room<MAX_ROOMS, MAX_PLAYERS>::getLooser()
            {
                if (_battlefield.ship_not_destroyed(_players[0]) <= 0) {
                    return _players[0];
                } else {
                    return _players[1];
                }
            }

        }
    }
}
