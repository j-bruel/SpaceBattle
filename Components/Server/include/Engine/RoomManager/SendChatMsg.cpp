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
            void RoomManager<MAX_ROOMS, MAX_PLAYERS>::send_chat_msg(TCommander &, SPacket packet)
            {
                boost::shared_lock<boost::shared_mutex>                         lock(this->_lock);
                std::shared_ptr<spcbttl::commun::net::req::SendChatMsgReq>      body;
                RoomPtr                                                         room;

                LOG_(commun::tool::log::IN_CONSOLE, plog::debug) << "RoomManager: send_message";
                body = std::dynamic_pointer_cast<spcbttl::commun::net::req::SendChatMsgReq>(packet->mPacketBody);
                if (std::get<1>(_players[packet->mPacketHeader.mClientId]) == Player::Status::UNREGISTRED) {
                    LOG_(commun::tool::log::IN_CONSOLE, plog::error) << "RoomManager: send_chat_msg Failed. Player not authenticated.";
                    return;
                }
                if (body->getChanelType() == commun::engine::ChanelType::GENERAL) {
                    std::vector<std::pair<std::reference_wrapper<sckcpp::tcp::ClientSocket>, unsigned short>> playersList;

                    for (unsigned short id=0; id < MAX_PLAYERS; id++) {
                        if (std::get<1>(_players[id]) != Player::Status::UNREGISTRED) {
                            LOG_(commun::tool::log::IN_CONSOLE, plog::debug)
                                        << "RoomManager: send_chat_message player :" << id
                                        << " send message :" << std::string(body->getMessage());
                            playersList.push_back(std::make_pair(std::reference_wrapper<sckcpp::tcp::ClientSocket>(
                                    std::get<0>(_players[id])->socket()), id));
                        }
                    }
                    _api.broadcastChatMsgResp(playersList, body->getChanelType(), std::string(body->getMessage()),
                            std::get<0>(_players[packet->mPacketHeader.mClientId])->get_name());

                } else {
                    room = std::get<2>(_players[packet->mPacketHeader.mClientId]);
                    if (!room) {
                        LOG_(commun::tool::log::IN_CONSOLE, plog::debug) << "RoomManager: Player not in room";
                    } else {
                        room->execute(packet);
                    }
                }
            }
        }
    }
}