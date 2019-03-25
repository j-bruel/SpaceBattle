//
// Created by grosso_a on 12/11/18.
//

#ifndef T_CPP_SPACEBATTLE_2018_ROOMMANAGER_HPP
#define T_CPP_SPACEBATTLE_2018_ROOMMANAGER_HPP


#include <array>
#include <memory>
#include <boost/thread/thread.hpp>
#include "Engine/Room/Room.hpp"
#include "Engine/Room/Player.hpp"
#include "Network/BattleAPI.hpp"
#include <Commun/Network/Requests/AuthenticateReq.hpp>
#include <Commun/Network/Requests/AuthenticateResp.hpp>
#include <Commun/Network/Requests/CreateRoomReq.hpp>
#include <Commun/Network/Requests/CreateRoomResp.hpp>
#include <Commun/Network/Requests/GetRoomListResp.hpp>
#include <Commun/Network/Requests/JoinRoomReq.hpp>
#include <Commun/Network/Requests/JoinRoomResp.hpp>
#include <Commun/Network/Requests/ViewRoomReq.hpp>
#include <Commun/Network/Requests/ViewRoomResp.hpp>
#include <Commun/Network/Requests/ExitRoomReq.hpp>
#include <Commun/Network/Requests/SendChatMsgReq.hpp>
#include <Commun/Network/Requests/BroadcastChatMsgResp.hpp>
#include <Commun/Network/Requests/LobbyStateUpdateResp.hpp>

namespace spcbttl
{
    //!
    //! @namespace server
    //!
    namespace server
    {
        //!
        //! @namespace engine
        //!
        namespace engine
        {
            #define MAX_ROOM_MANAGER_COMMAND 25

            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            class Room;

            /**
             * @class RoomManager
             * @brief Manage all roms, and players in server.
             * @tparam MAX_ROOMS
             * @tparam MAX_PLAYERS
             */
            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            class RoomManager: public ACommander<MAX_ROOM_MANAGER_COMMAND, RoomManager<MAX_ROOMS, MAX_PLAYERS>, std::shared_ptr<commun::net::Packet>>
            {
            public:
                typedef std::shared_ptr<commun::net::Packet>                           SPacket;
                typedef RoomManager<MAX_ROOMS, MAX_PLAYERS>                            TRoomManager;
                typedef Room<MAX_ROOMS, MAX_PLAYERS>                                   TRoom;
                typedef std::shared_ptr<TRoom>                                         RoomPtr;
                typedef std::shared_ptr<Player>                                        PlayerPtr;
                typedef std::tuple<PlayerPtr, Player::Status , RoomPtr>                PlayerInfo;
                typedef ACommander<MAX_ROOM_MANAGER_COMMAND, TRoomManager, SPacket>    TCommander;
                typedef std::function<void (TRoomManager &, TCommander&, SPacket)>     TCommand;

            private:
                std::list<RoomPtr>                                      _rooms;
                std::array<PlayerInfo, MAX_PLAYERS>                     _players;
                boost::shared_mutex                                     _lock;
                std::chrono::time_point<std::chrono::system_clock>      _last_check;
                net::BattleAPI                                          _api;

                /**
                 * @brief In case of the packet command is not valid.
                 * @param id
                 */
                virtual void notExist(unsigned int id, SPacket);


                /**
                 * @brief Check if new check is required.
                 * @return True if new check is required else False.
                 */
                bool time_to_check();

                /**
                 * @brief Apply checks in all rooms of the server.
                 * Destroy it if is need, and detect the game end.
                 */
                void check_rooms();

                /**
                 * @brief Load new room in server.
                 * @param room Room to insert in server.
                 */
                void build_room(RoomPtr room);


                /**
                 * @brief Destroy room in case of end game.
                 * @param room Room to destroy.
                 * @param player Player Loose the game.
                 */
                void destroy_room(RoomPtr room, PlayerPtr player);

                /**
                 * @brief Destroy room in case of error.
                 * @param room Room to destroy.
                 */
                void destroy_room_error(RoomPtr room);

                /**
                 * @brief Broadcast lobby state update to all player in room.
                 * @param room Selected Room.
                 */
                void notify_room_players(RoomPtr room);

                /**
                 * @brief Attach player to room.
                 * @param room Room received player.
                 * @param player Player to attach.
                 */
                void attach_player_room(RoomPtr room, PlayerPtr player);

                /**
                 * @brief Attach viewer to room.
                 * @param room Room received viewer.
                 * @param player Viewer to attach.
                 */
                void attach_viewer_room(RoomPtr room, PlayerPtr player);

                /**
                 * @brief Detach viwer of room.
                 * @param room Selected Room.
                 * @param player Viewer to remove.
                 */
                void detach_viewer_room(RoomPtr room, PlayerPtr player);

                /**
                 * @brief Load player in server.
                 * @param id Player id
                 * @param name Player name
                 * @param socket Player socket
                 */
                void add_player(unsigned int id, const std::string &name, sckcpp::tcp::ClientSocket &socket);

                /**
                 * @brief Reset player of server.
                 * @param playerinfo Player info ro reset.
                 */
                void reset_player(PlayerInfo &playerinfo);

                /**
                 * @brief Remove player from server.
                 * @param playerinfo Player info to remove.
                 */
                void del_player(PlayerInfo &playerinfo);


                /**
                 * @brief Check if player is authenticated.
                 * @param clientId Player id to check.
                 * @param fct_name Function name in error case.
                 * @return True if player authenticated else False.
                 */
                bool is_authenticated(unsigned int clientId, const std::string &fct_name);

                /**
                 * @brief Set player alive.
                 */
                void players_alive();

                /**
                 * @brief Find player with name.
                 * @param name player name.
                 * @return player array iterator.
                 */
                typename std::array<PlayerInfo, MAX_PLAYERS>::iterator   find_player(const std::string name)
                {
                    return std::find_if(_players.begin(), _players.end(), [&](PlayerInfo const &player) {
                        if (std::get<0>(player) != nullptr) {
                            return std::get<0>(player)->get_name() == name;
                        } else {
                            return false;
                        }
                    });
                }

                /**
                 * @brief Find room with name.
                 * @param name room name.
                 * @return room list iterator.
                 */
                typename std::list<RoomPtr>::iterator   find_room(const std::string name)
                {
                    return std::find_if(_rooms.begin(), _rooms.end(), [&](RoomPtr const &room) {
                        return room->name() == name;
                    });
                }

                /**
                 * @brief All commands related to specific room.
                 */
                void room_commands(TCommander &, SPacket);

                /**
                 * @brief KEEP_ALIVE_REQ
                 */
                void keep_alive(TCommander &, SPacket);

                /**
                 * @brief AUTHENTICATE_REQ
                 */
                void authenticate(TCommander &, SPacket);

                /**
                 * @brief GET_ROOM_LIST_REQ
                 */
                void get_room_list(TCommander &, SPacket);

                /**
                 * @brief CREATE_ROOM_REQ
                 */
                void create_room(TCommander &, SPacket);

                /**
                 * @brief JOIN_ROOM_REQ
                 */
                void join_room(TCommander &, SPacket);

                /**
                 * @brief VIEW_ROOM_REQ
                 */
                void view_room(TCommander &, SPacket);

                /**
                 * @brief EXIT_ROOM_REQ
                 */
                void exit_room(TCommander &, SPacket);

                /**
                 * @brief SEND_CHAT_MSG_REQ
                 */
                void send_chat_msg(TCommander &, SPacket);

            public:
                RoomManager();
                ~RoomManager();

                /**
                 * @brief Execute placket from packet dispatcher.
                 * @param packet packet to execute.
                 */
                void execute(SPacket packet);

                /**
                 * @brief Checks executed each second.
                 */
                void checks();
            };
        }
    }
}

#include <Engine/RoomManager/RoomManager.cpp>

#endif //T_CPP_SPACEBATTLE_2018_ROOMMANAGER_HPP
