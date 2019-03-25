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
            void RoomManager<MAX_ROOMS, MAX_PLAYERS>::authenticate(TCommander &, SPacket packet)
            {
                boost::unique_lock<boost::shared_mutex>                         lock(this->_lock);
                std::shared_ptr<spcbttl::commun::net::req::SAuthenticateReq>    body;
                unsigned short                                                  client_id;

                body = std::dynamic_pointer_cast<spcbttl::commun::net::req::SAuthenticateReq>(packet->mPacketBody);
                if (find_player(body->getPlayerName()) != _players.end()) {
                    LOG_(commun::tool::log::IN_CONSOLE, plog::error) << "RoomManager: authenticate Failed. User name already exist.";
                    _api.authResp(body->getPlayer(), (unsigned int)0,
                                  std::string(body->getPlayerName()),
                                  commun::net::req::State::ERROR_ALREADY_AUTH_STATE);
                    return;
                }
                LOG_(commun::tool::log::IN_CONSOLE, plog::debug) << "RoomManager: authenticate";
                for (client_id=0; client_id < MAX_PLAYERS; client_id++) {
                    if (std::get<1>(_players[client_id]) == Player::Status::UNREGISTRED) {
                        break;
                    }
                }
                if (client_id != MAX_PLAYERS) {
                    this->add_player(client_id, body->getPlayerName(), body->getPlayer());
                    LOG_(commun::tool::log::IN_CONSOLE, plog::debug) << "RoomManager: authenticated with id " << client_id << " .";
                    _api.authResp(body->getPlayer(), client_id,
                                  std::string(body->getPlayerName()),
                                  commun::net::req::State::NO_STATE);
                } else {
                    LOG_(commun::tool::log::IN_CONSOLE, plog::error) << "RoomManager: authenticate Failed. No user Available";
                    _api.authResp(body->getPlayer(), (unsigned int)0,
                                  std::string(body->getPlayerName()),
                                  commun::net::req::State::ERROR_MAX_CLIENT_NB_EXCEEDED_STATE);
                }
            }
        }
    }
}