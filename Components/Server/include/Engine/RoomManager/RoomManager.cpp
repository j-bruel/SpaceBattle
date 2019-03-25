//
// Created by grosso_a on 12/11/18.
//

#include <Engine/RoomManager/RoomManager.hpp>
#include <Commun/Network/Requests/SAuthenticateReq.hpp>
#include <utility>
#include <ctime>

#include <Engine/RoomManager/SendChatMsg.cpp>
#include <Engine/RoomManager/ViewRoom.cpp>
#include <Engine/RoomManager/JoinRoom.cpp>
#include <Engine/RoomManager/GetRoomList.cpp>
#include <Engine/RoomManager/ExitRoom.cpp>
#include <Engine/RoomManager/CreateRoom.cpp>
#include <Engine/RoomManager/Authenticate.cpp>

namespace spcbttl
{
    namespace server
    {
        namespace engine
        {
            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            RoomManager<MAX_ROOMS, MAX_PLAYERS>::RoomManager():
                ACommander<MAX_ROOM_MANAGER_COMMAND, RoomManager<MAX_ROOMS, MAX_PLAYERS>, std::shared_ptr<commun::net::Packet>>(*this)
            {
                this->set_command(commun::net::req::KEEP_ALIVE_REQ, new TCommand(&RoomManager::keep_alive));
                this->set_command(commun::net::req::AUTHENTICATE_REQ, new TCommand(&RoomManager::authenticate));
                this->set_command(commun::net::req::GET_ROOM_LIST_REQ, new TCommand(&RoomManager::get_room_list));
                this->set_command(commun::net::req::CREATE_ROOM_REQ, new TCommand(&RoomManager::create_room));
                this->set_command(commun::net::req::JOIN_ROOM_REQ, new TCommand(&RoomManager::join_room));
                this->set_command(commun::net::req::VIEW_ROOM_REQ, new TCommand(&RoomManager::view_room));
                this->set_command(commun::net::req::EXIT_ROOM_REQ, new TCommand(&RoomManager::exit_room));
                this->set_command(commun::net::req::SEND_CHAT_MSG_REQ, new TCommand(&RoomManager::send_chat_msg));

                this->set_command(commun::net::req::LAUNCH_GAME_REQ, new TCommand(&RoomManager::room_commands));
                this->set_command(commun::net::req::SET_USER_BATTLESHIP_REQ, new TCommand(&RoomManager::room_commands));
                this->set_command(commun::net::req::SHOOT_SHIP_REQ, new TCommand(&RoomManager::room_commands));
                for (unsigned short it=0; it < MAX_PLAYERS; it++) {
                    _players[it] = std::make_tuple(nullptr, Player::Status::UNREGISTRED, nullptr);
                }
                this->_last_check = std::chrono::system_clock::now();
            }

            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            RoomManager<MAX_ROOMS, MAX_PLAYERS>::~RoomManager()
            {
                while (!this->_rooms.empty()) {
                    this->_rooms.pop_back();
                }
                for (unsigned short it=0; it < MAX_PLAYERS; it++) {
                    if (std::get<0>(_players[it]) != nullptr) {
                        std::get<0>(_players[it]) = nullptr;
                    }
                }
            }

            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            void RoomManager<MAX_ROOMS, MAX_PLAYERS>::build_room(RoomPtr room)
            {
                _rooms.push_back(room);
            }

            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            void RoomManager<MAX_ROOMS, MAX_PLAYERS>::destroy_room(RoomPtr room, PlayerPtr playerLoose)
            {
                for (PlayerPtr player : room->players()) {
                    if (player->id() == playerLoose->id()) {
                        LOG_(commun::tool::log::IN_CONSOLE, plog::debug) << "RoomManager: Player :" << player->id() << " loose.";
                        _api.endGameStatusReq(player->socket(), player->id(), commun::engine::FinalGameStatus::LOOSE);
                    } else {
                        LOG_(commun::tool::log::IN_CONSOLE, plog::debug) << "RoomManager: Player :" << player->id() << " win.";
                        _api.endGameStatusReq(player->socket(), player->id(), commun::engine::FinalGameStatus::WIN);
                    }
                    this->reset_player(_players[player->id()]);
                }
                for (PlayerPtr viewer : room->viewers()) {
                    _api.endGameStatusReq(viewer->socket(), viewer->id(), commun::engine::FinalGameStatus::ERROR);
                    this->detach_viewer_room(room, viewer);
                }
                LOG_(commun::tool::log::IN_CONSOLE, plog::debug) << "RoomManager: Destroy room :" << room->name() << " .";
                this->_rooms.remove(room);
            }

            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            void RoomManager<MAX_ROOMS, MAX_PLAYERS>::destroy_room_error(RoomPtr room)
            {
                for (PlayerPtr player : room->players()) {
                    _api.endGameStatusReq(player->socket(), player->id(), commun::engine::FinalGameStatus::ERROR);
                    this->reset_player(_players[player->id()]);
                }
                for (PlayerPtr viewer : room->viewers()) {
                    _api.endGameStatusReq(viewer->socket(), viewer->id(), commun::engine::FinalGameStatus::ERROR);
                    this->detach_viewer_room(room, viewer);
                }
                LOG_(commun::tool::log::IN_CONSOLE, plog::debug) << "RoomManager: Destroy room :" << room->name() << " .";
                this->_rooms.remove(room);
            }

            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            void RoomManager<MAX_ROOMS, MAX_PLAYERS>::attach_player_room(RoomPtr room, PlayerPtr player)
            {
                player->set_status(Player::Status::PLAYER);
                room->add_player(player);
                std::get<1>(_players[player->id()]) = Player::Status::PLAYER;
                std::get<2>(_players[player->id()]) = room;
            }

            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            void RoomManager<MAX_ROOMS, MAX_PLAYERS>::attach_viewer_room(RoomPtr room, PlayerPtr player)
            {
                player->set_status(Player::Status::VIEWER);
                room->add_viewer(player);
                std::get<1>(_players[player->id()]) = Player::Status::VIEWER;
                std::get<2>(_players[player->id()]) = room;
            }

            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            void RoomManager<MAX_ROOMS, MAX_PLAYERS>::detach_viewer_room(RoomPtr room, PlayerPtr player)
            {
                room->del_viewer(player);
                this->reset_player(_players[player->id()]);
            }

            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            void RoomManager<MAX_ROOMS, MAX_PLAYERS>::add_player(unsigned int id, const std::string &name, sckcpp::tcp::ClientSocket &socket)
            {
                std::get<0>(_players[id]) = std::make_shared<Player>(id, name, socket);
                std::get<1>(_players[id]) = Player::Status::REGISTRED;
            }

            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            void RoomManager<MAX_ROOMS, MAX_PLAYERS>::reset_player(PlayerInfo &playerinfo)
            {
                std::get<0>(playerinfo)->set_status(Player::Status::REGISTRED);
                std::get<1>(playerinfo) = Player::Status::REGISTRED;
                std::get<2>(playerinfo) = nullptr;
            }

            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            void RoomManager<MAX_ROOMS, MAX_PLAYERS>::del_player(PlayerInfo &playerinfo)
            {
                std::get<0>(playerinfo) = nullptr;
                std::get<1>(playerinfo) = Player::Status::UNREGISTRED;
                std::get<2>(playerinfo) = nullptr;
            }

            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            void RoomManager<MAX_ROOMS, MAX_PLAYERS>::notify_room_players(RoomPtr room)
            {
                std::list<PlayerPtr>                                        players_viewers = room->players();

                players_viewers.merge(room->viewers());
                std::map<std::string, commun::engine::ClientState>  clients;
                for (PlayerPtr player: players_viewers) {
                    if (player->get_status() == Player::Status::PLAYER) {
                        clients[player->get_name()] = commun::engine::ClientState::PLAYER;
                    } else {
                        clients[player->get_name()] = commun::engine::ClientState::VIEWER;
                    }
                }
                for (PlayerPtr player: players_viewers)
                    _api.lobbyStateUpdateResp(player->socket(), player->id(), clients);
            }


            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            void RoomManager<MAX_ROOMS, MAX_PLAYERS>::notExist(unsigned int id, SPacket)
            {
                LOG_(commun::tool::log::IN_CONSOLE, plog::error)
                        << "RoomManager: command id:" << (unsigned int)(id) << " is invalid.";
            }

            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            void RoomManager<MAX_ROOMS, MAX_PLAYERS>::room_commands(TCommander &, SPacket packet)
            {
                boost::shared_lock<boost::shared_mutex> lock(this->_lock);
                if (!this->is_authenticated(packet->mPacketHeader.mClientId, "room commands")) {
                    return;
                }
                if (!std::get<0>(_players[packet->mPacketHeader.mClientId])->in_room()) {
                    LOG_(commun::tool::log::IN_CONSOLE, plog::error)
                                << "Player "<< int(packet->mPacketHeader.mClientId) << " not in room.";
                } else {
                    LOG_(commun::tool::log::IN_CONSOLE, plog::debug)
                                << "RoomManager: command id:" << int(packet->mPacketHeader.mCmdType)
                                << " is redirected to room.";
                    std::get<2>(_players[packet->mPacketHeader.mClientId])->execute(packet);
                }
            }


            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            void RoomManager<MAX_ROOMS, MAX_PLAYERS>::keep_alive(TCommander &, SPacket packet)
            {
                boost::shared_lock<boost::shared_mutex>  lock(this->_lock);
                LOG_(commun::tool::log::IN_CONSOLE, plog::debug) << "RoomManager: call keep_alive";
                if (this->is_authenticated(packet->mPacketHeader.mClientId, "keep_alive"))
                {
                    std::get<0>(_players[packet->mPacketHeader.mClientId])->alive();
                    LOG_(commun::tool::log::IN_CONSOLE, plog::debug)
                        << "RoomManager: keep_alive ok. Player " << packet->mPacketHeader.mClientId << " is alive.";
                }
            }

            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            bool RoomManager<MAX_ROOMS, MAX_PLAYERS>::is_authenticated(unsigned int clientId, const std::string &fct_name)
            {
                if (std::get<1>(_players[clientId]) == Player::Status::UNREGISTRED) {
                    LOG_(commun::tool::log::IN_CONSOLE, plog::error)
                                << "RoomManager: " << fct_name << " Failed. Player not authenticated.";
                    return false;
                }
                return true;
            }


            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            void RoomManager<MAX_ROOMS, MAX_PLAYERS>::execute(SPacket packet)
            {
                this->exec_command(packet->mPacketHeader.mCmdType, packet);
            }

            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            void RoomManager<MAX_ROOMS, MAX_PLAYERS>::players_alive()
            {
                for (unsigned short id = 0; id < MAX_PLAYERS; id++) {
                    PlayerInfo  &playerinfo = _players[id];
                    PlayerPtr   player = std::get<0>(playerinfo);
                    if (player != nullptr && !player->is_alive()) {
                        if (std::get<2>(playerinfo) != nullptr && player->get_status() == Player::PLAYER) {
                            if (std::get<2>(playerinfo)->status() == commun::room::State::IN_PROFRESS
                            || std::get<2>(playerinfo)->status() == commun::room::State::FINISH) {
                                this->destroy_room(std::get<2>(playerinfo), player);
                            } else {
                                this->destroy_room_error(std::get<2>(playerinfo));
                            }
                        } else if (std::get<2>(playerinfo) != nullptr) {
                            this->detach_viewer_room(std::get<2>(playerinfo), player);
                        }
                        LOG_(commun::tool::log::IN_CONSOLE, plog::debug)
                                    << "RoomManager: player name:" << player->get_name() << " is dead.";
                        _api.endGameStatusReq(player->socket(), id, commun::engine::FinalGameStatus::LOOSE);
                        this->del_player(playerinfo);
                    }
                }
            }

            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            bool RoomManager<MAX_ROOMS, MAX_PLAYERS>::time_to_check()
            {
                return std::chrono::system_clock::now() - this->_last_check > std::chrono::seconds(1);
            }

            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            void RoomManager<MAX_ROOMS, MAX_PLAYERS>::check_rooms()
            {
                for (RoomPtr room : _rooms)
                {
                    switch (room->time_limit()) {
                        case commun::engine::TimeLimit::NO_LIMIT:
                            break;
                        case commun::engine::TimeLimit::FORTY_FILE_MIN:
                            if (std::chrono::system_clock::now() >= (room->start_time() + std::chrono::minutes(45))) {
                                this->destroy_room_error(room);
                                return;
                            }
                            break;
                        case commun::engine::TimeLimit::THIRTY_MIN:
                            if (std::chrono::system_clock::now() >= (room->start_time() + std::chrono::minutes(30))) {
                                this->destroy_room_error(room);
                                return;
                            }
                            break;
                        case commun::engine::TimeLimit::FOURTEEN_MIN:
                            if (std::chrono::system_clock::now() >= (room->start_time() + std::chrono::minutes(15))) {
                                this->destroy_room_error(room);
                                return;
                            }
                            break;
                    };
                    if (room->status() == commun::room::State::FINISH) {
                        this->destroy_room(room, room->getLooser());
                        return;
                    }
                }
            }

            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            void RoomManager<MAX_ROOMS, MAX_PLAYERS>::checks()
            {
                boost::unique_lock<boost::shared_mutex>  lock(this->_lock);
                if (this->time_to_check()) {
                    this->_last_check = std::chrono::system_clock::now();
                    this->check_rooms();
                    this->players_alive();
                }
            }
        }
    }
}
