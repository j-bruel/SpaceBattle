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
            void RoomManager<MAX_ROOMS, MAX_PLAYERS>::exit_room(TCommander &, SPacket packet)
            {
                boost::unique_lock<boost::shared_mutex> lock(this->_lock);
                std::shared_ptr<spcbttl::commun::net::req::ExitRoomReq>     body;
                typename std::list<RoomPtr>::iterator                       room;


                LOG_(commun::tool::log::IN_CONSOLE, plog::debug) << "RoomManager: exit_room";
                body = std::dynamic_pointer_cast<spcbttl::commun::net::req::ExitRoomReq>(packet->mPacketBody);
                room = find_room(body->getRoomName());
                if (room != _rooms.end()) {
                    PlayerPtr player = std::get<0>(_players[packet->mPacketHeader.mClientId]);
                    if (player->get_status() == Player::PLAYER) {
                        this->destroy_room(*room, player);
                    } else {
                        (*room)->del_viewer(player);
                        this->notify_room_players(*room);
                    }
                    this->reset_player(_players[packet->mPacketHeader.mClientId]);
                    LOG_(commun::tool::log::IN_CONSOLE, plog::debug)
                                << "RoomManager: exit_room name:" << body->getRoomName()
                                << " player:" << int(packet->mPacketHeader.mClientId);
                }
            }
       }
    }
}

