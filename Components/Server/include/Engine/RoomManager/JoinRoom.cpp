//
// Created by grosso_a on 29/11/18.
//
#include <Engine/RoomManager/RoomManager.hpp>
#include <Commun/Network/Requests/SAuthenticateReq.hpp>
#include <utility>

namespace spcbttl
{
    namespace server
    {
        namespace engine
        {
            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            void RoomManager<MAX_ROOMS, MAX_PLAYERS>::join_room(TCommander &, SPacket packet)
            {
                boost::unique_lock<boost::shared_mutex>                     lock(this->_lock);
                std::shared_ptr<spcbttl::commun::net::req::JoinRoomReq>     body;
                typename std::list<RoomPtr>::iterator                       room;


                LOG_(commun::tool::log::IN_CONSOLE, plog::debug) << "RoomManager: join_room";
                PlayerPtr player = std::get<0>(_players[packet->mPacketHeader.mClientId]);
                body = std::dynamic_pointer_cast<spcbttl::commun::net::req::JoinRoomReq>(packet->mPacketBody);
                if (!this->is_authenticated(packet->mPacketHeader.mClientId, "join_room")) {
                    return;
                }
                if (std::get<2>(_players[packet->mPacketHeader.mClientId]) != nullptr) {
                    LOG_(commun::tool::log::IN_CONSOLE, plog::error) << "RoomManager: join_room Failed. Player already in room.";
                    _api.joinRoomResp(player->socket(), packet->mPacketHeader.mClientId, "", commun::engine::TimeLimit::NO_LIMIT,
                                      true, commun::net::req::State::ERROR_PLAYER_ALREADY_IN_ROOM_STATE);
                    return;
                }
                room = find_room(body->getRoomName());
                if (room == _rooms.end()) {
                    LOG_(commun::tool::log::IN_CONSOLE, plog::error) << "RoomManager: join_room Failed. Room not not exist.";
                    _api.joinRoomResp(player->socket(), packet->mPacketHeader.mClientId, "", commun::engine::TimeLimit::NO_LIMIT,
                                      true, commun::net::req::State::ERROR_ROOM_DOES_NOT_EXIST_STATE);
                    return;
                }
                if ((*room)->full_player()) {
                    LOG_(commun::tool::log::IN_CONSOLE, plog::error) << "RoomManager: join_room Failed. Room is full.";
                    _api.joinRoomResp(player->socket(), packet->mPacketHeader.mClientId,
                                      (*room)->name(), (*room)->time_limit(), (*room)->allow_viewers(),
                                      commun::net::req::State::ERROR_MAX_ROOM_PLAYER_EXCEEDED_STATE);
                    return;
                }
                if ((*room)->status() != spcbttl::commun::room::State::WAITING_FOR_PLAYER
                    && (*room)->status() != spcbttl::commun::room::State::NEW) {
                    LOG_(commun::tool::log::IN_CONSOLE, plog::error) << "RoomManager: join_room Failed. Room is locked.";
                    //TODO send error packet
                    return;
                }
                this->attach_player_room(*room, player);
                _api.joinRoomResp(player->socket(), packet->mPacketHeader.mClientId,
                                  (*room)->name(), (*room)->time_limit(), (*room)->allow_viewers(),
                                  commun::net::req::State::NO_STATE);
                LOG_(commun::tool::log::IN_CONSOLE, plog::debug)
                            << "RoomManager: join_room name:" << body->getRoomName()
                            << " player:" << int(packet->mPacketHeader.mClientId);
                this->notify_room_players(*room);
            }
       }
    }
}

