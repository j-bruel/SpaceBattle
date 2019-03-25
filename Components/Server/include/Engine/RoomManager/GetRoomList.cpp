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
            void RoomManager<MAX_ROOMS, MAX_PLAYERS>::get_room_list(TCommander &, SPacket packet)
            {
                boost::shared_lock<boost::shared_mutex>                     lock(this->_lock);
                std::map<std::string, commun::room::State>                  rooms;


                LOG_(commun::tool::log::IN_CONSOLE, plog::debug) << "RoomManager: get_room_list";
                PlayerPtr player = std::get<0>(_players[packet->mPacketHeader.mClientId]);
                if (std::get<1>(_players[packet->mPacketHeader.mClientId]) == Player::Status::UNREGISTRED) {
                    LOG_(commun::tool::log::IN_CONSOLE, plog::error) << "RoomManager: get_room_list Failed. Player not authenticated.";
                    return;
                }
                for (RoomPtr room : _rooms) {
                    LOG_(commun::tool::log::IN_CONSOLE, plog::warning)
                                << "Room name :" <<  room->name()
                                << " status :" << int(room->status());
                    rooms.insert(std::make_pair(std::string(room->name()), room->status()));
                }
                _api.getRoomListResp(player->socket(), packet->mPacketHeader.mCmdType, rooms);
            }
        }
    }
}
