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
            void RoomManager<MAX_ROOMS, MAX_PLAYERS>::view_room(TCommander &, SPacket packet)
            {
                boost::shared_lock<boost::shared_mutex>                     lock(this->_lock);
                std::shared_ptr<spcbttl::commun::net::req::ViewRoomReq>     body;
                typename std::list<RoomPtr>::iterator                       room;


                LOG_(commun::tool::log::IN_CONSOLE, plog::debug) << "RoomManager: view_room";
                PlayerPtr player = std::get<0>(_players[packet->mPacketHeader.mClientId]);
                body = std::dynamic_pointer_cast<spcbttl::commun::net::req::ViewRoomReq>(packet->mPacketBody);
                if (std::get<1>(_players[packet->mPacketHeader.mClientId]) == Player::Status::UNREGISTRED) {
                    LOG_(commun::tool::log::IN_CONSOLE, plog::error) << "RoomManager: view_room Failed. Player not authenticated.";
                    return;
                }
                if (std::get<2>(_players[packet->mPacketHeader.mClientId]) != nullptr) {
                    LOG_(commun::tool::log::IN_CONSOLE, plog::error) << "RoomManager: view_room Failed. Player already in room.";
                    _api.viewRoomResp(player->socket(), packet->mPacketHeader.mClientId,
                                      std::string(body->getRoomName()), commun::net::req::State::ERROR_PLAYER_ALREADY_IN_ROOM_STATE);
                    return;
                }
                room = find_room(body->getRoomName());
                if (room == _rooms.end()) {
                    LOG_(commun::tool::log::IN_CONSOLE, plog::error) << "RoomManager: view_room Failed. Room not not exist.";
                    _api.viewRoomResp(player->socket(), packet->mPacketHeader.mClientId,
                                      std::string(body->getRoomName()), commun::net::req::State::ERROR_ROOM_DOES_NOT_EXIST_STATE);
                    return;
                }
                if ((*room)->full_viewer()) {
                    LOG_(commun::tool::log::IN_CONSOLE, plog::error) << "RoomManager: view_room Failed. Room is full.";
                    _api.viewRoomResp(player->socket(), packet->mPacketHeader.mClientId,
                                      std::string(body->getRoomName()), commun::net::req::State::ERROR_MAX_ROOM_VIEWER_EXCEEDED_STATE);
                    return;
                }
                if (!(*room)->allow_viewers()) {
                    LOG_(commun::tool::log::IN_CONSOLE, plog::error) << "RoomManager: view_room Failed. Room not allow viewers.";
                    _api.viewRoomResp(player->socket(), packet->mPacketHeader.mClientId,
                                      std::string(body->getRoomName()), commun::net::req::State::ERROR_VIEW_NOT_ALLOW);
                    return;
                }
                if ((*room)->status() == spcbttl::commun::room::State::IN_PROFRESS
                    || (*room)->status() == spcbttl::commun::room::State::FINISH) {
                    LOG_(commun::tool::log::IN_CONSOLE, plog::error) << "RoomManager: view_room Failed. Room is locked.";
                    //TODO send error packet
                    return;
                }
                this->attach_viewer_room(*room, player);
                _api.viewRoomResp(player->socket(), packet->mPacketHeader.mClientId,
                                  std::string(body->getRoomName()), commun::net::req::State::NO_STATE);
                LOG_(commun::tool::log::IN_CONSOLE, plog::debug)
                            << "RoomManager: view_room name:" << body->getRoomName()
                            << " player:" << int(packet->mPacketHeader.mClientId);
                this->notify_room_players(*room);
            }
       }
    }
}

