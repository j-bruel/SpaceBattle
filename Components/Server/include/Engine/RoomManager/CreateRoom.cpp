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
            void RoomManager<MAX_ROOMS, MAX_PLAYERS>::create_room(TCommander &, SPacket packet)
            {
                boost::unique_lock<boost::shared_mutex>                     lock(this->_lock);
                std::shared_ptr<spcbttl::commun::net::req::CreateRoomReq>   body;
                std::shared_ptr<spcbttl::commun::net::req::CreateRoomResp>  resp;


                PlayerPtr player = std::get<0>(_players[packet->mPacketHeader.mClientId]);
                body = std::dynamic_pointer_cast<spcbttl::commun::net::req::CreateRoomReq>(packet->mPacketBody);
                if (!this->is_authenticated(packet->mPacketHeader.mClientId, "create_room")) {
                    return;
                }
                if (_rooms.size() >= MAX_ROOMS) {
                    LOG_(commun::tool::log::IN_CONSOLE, plog::error) << "RoomManager: create_room Failed. No Room available.";
                    _api.createRoomResp(player->socket(), packet->mPacketHeader.mClientId,
                                        std::string(body->getRoomName()),
                                        body->getLimitType(),
                                        body->isViewerAllow(),
                                        commun::net::req::State::ERROR_MAX_ROOM_NB_EXCEEDED_STATE);
                    return;
                }
                if (body->getRoomName().size() < 3 || body->getRoomName().size() > 10) {
                    LOG_(commun::tool::log::IN_CONSOLE, plog::error) << "RoomManager: create_room Failed. Invalid name.";
                    _api.createRoomResp(player->socket(), packet->mPacketHeader.mClientId,
                                        std::string(body->getRoomName()),
                                        body->getLimitType(),
                                        body->isViewerAllow(),
                                        commun::net::req::State::ERROR_INVALID_ROOM_NAME_STATE);
                    return;
                }
                if (std::find_if(_rooms.begin(), _rooms.end(),
                                 [&](RoomPtr const &room) { return room->name() == body->getRoomName();}) != _rooms.end()) {
                    LOG_(commun::tool::log::IN_CONSOLE, plog::error) << "RoomManager: create_room Failed. Room name already exist.";
                    _api.createRoomResp(player->socket(), packet->mPacketHeader.mClientId,
                                        std::string(body->getRoomName()),
                                        body->getLimitType(),
                                        body->isViewerAllow(),
                                        commun::net::req::State::ERROR_ROOM_ALREADY_EXIST_STATE);
                    return;
                }
                LOG_(commun::tool::log::IN_CONSOLE, plog::debug)
                            << "RoomManager: create_room name:" << body->getRoomName()
                            << " allow_viewers:" << body->isViewerAllow()
                            << " time_limit:" << int(body->getLimitType());
                this->build_room(std::make_shared<TRoom>(*this, body));
                _api.createRoomResp(player->socket(), packet->mPacketHeader.mClientId,
                                    std::string(body->getRoomName()),
                                    body->getLimitType(),
                                    body->isViewerAllow(),
                                    commun::net::req::State::NO_STATE);
            }
        }
    }
}
