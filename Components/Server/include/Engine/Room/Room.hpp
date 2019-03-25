//
// Created by grosso_a on 07/11/18.
//

#ifndef T_CPP_SPACEBATTLE_2018_ROOM_HPP
#define T_CPP_SPACEBATTLE_2018_ROOM_HPP

#include <mutex>
#include <plog/Log.h>
#include <Commun/Tools/Log/Idx.hpp>
#include <boost/thread/thread.hpp>
#include "Network/BattleAPI.hpp"
#include "Engine/ACommander.hpp"
#include "Commun/Network/Packet.hpp"
#include <Commun/Network/Requests/CreateRoomReq.hpp>
#include <Commun/Network/Requests/SetUserBattleshipReq.hpp>
#include <Commun/Network/Requests/SetUserBattleshipResp.hpp>
#include <Commun/Network/Requests/SendChatMsgReq.hpp>
#include <Commun/Network/Requests/BroadcastChatMsgResp.hpp>
#include <Commun/Network/Requests/ShootShipReq.hpp>
#include <Commun/Network/Requests/ShootShipResp.hpp>
#include <Commun/Network/Requests/LaunchGameReq.hpp>
#include <Commun/Network/Requests/LaunchGameResp.hpp>
#include <Commun/Engine/ShootState.hpp>
#include <Commun/Engine/FinalGameStatus.hpp>
#include <Commun/Room/State.hpp>
#include "Player.hpp"
#include "Battlefield.hpp"
#include <Conf/Engine.hpp>

//!
//! @namespace spcbttl
//!
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
            #define MAX_ROOM_COMMAND 25

            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            class RoomManager;

            /**
             * @class Room
             * @brief Manage Player, Ships, Battlefield
             * @tparam MAX_ROOMS Max number of rooms authorized
             * @tparam MAX_PLAYERS Max number of player authorized
             */
            template <unsigned int MAX_ROOMS, unsigned int MAX_PLAYERS>
            class Room: public ACommander<MAX_ROOM_COMMAND, Room<MAX_ROOMS, MAX_PLAYERS>, std::shared_ptr<commun::net::Packet>>
            {
            private:
                typedef std::shared_ptr<commun::net::Packet>                                PacketPtr;
                typedef std::shared_ptr<Player>                                             PlayerPtr;
                typedef Room<MAX_ROOMS, MAX_PLAYERS>                                        TRoom;
                typedef ACommander<MAX_ROOM_COMMAND, TRoom, PacketPtr>                      TCommander;
                typedef RoomManager<MAX_ROOMS, MAX_PLAYERS>                                 TRoomManager;
                typedef std::function<void (TRoom &, TCommander&, PacketPtr)>               TCommand;

                TRoomManager                                            &_manager;
                boost::shared_mutex                                     _lock;
                Battlefield                                             _battlefield;
                std::array<PlayerPtr, 2>                                _players;
                std::list<PlayerPtr>                                    _viewers;
                unsigned int                                            _current_player;
                commun::room::State                                     _state;
                bool                                                    _allow_viewers;
                const std::string                                       _name;
                const commun::engine::TimeLimit                         _time_limit;
                net::BattleAPI                                          _api;
                std::chrono::time_point<std::chrono::system_clock>      _start_time;


                /**
                 * @brief Callback in case of invalid command
                 */
                virtual void notExist(unsigned int, PacketPtr);

                /**
                 * @brief Convert destroyer packet format to internal ship
                 * @param destroyer Packet destroyer
                 * @return internal ship
                 */
                std::shared_ptr<Ship> load_Destroyer(const commun::engine::Ship::Destroyer &destroyer);

                /**
                 * @brief Convert submarine packet format to internal ship
                 * @param submarine Packet submarine
                 * @return internal ship
                 */
                std::shared_ptr<Ship> load_Submarine(const commun::engine::Ship::Submarine &submarine);

                /**
                 * @brief Convert cruiser packet format to internal ship
                 * @param crusier Packet cruiser
                 * @return internal ship
                 */
                std::shared_ptr<Ship> load_Cruiser(const commun::engine::Ship::Cruiser &crusier);

                /**
                 * @brief Convert battleship packet format to internal ship
                 * @param battleship Packet battleship
                 * @return internal ship
                 */
                std::shared_ptr<Ship> load_Battleship(const commun::engine::Ship::Battleship &battleship);

                /**
                 * @brief Convert carrier packet format to internal ship
                 * @param carrier Packet carrier
                 * @return internal ship
                 */
                std::shared_ptr<Ship> load_Carrier(const commun::engine::Ship::Carrier &carrier);

                /**
                 * @brief SET_USER_BATTLESHIP_REQ
                 * @param packet Packet from network
                 */
                void set_user_battleship(TCommander &, PacketPtr packet);

                /**
                 * @brief SEND_CHAT_MSG_REQ
                 * @param packet Packet from network
                 */
                void send_chat_msg(TCommander &, PacketPtr packet);

                /**
                 * @brief SHOOT_SHIP_REQ
                 * @param packet Packet from network
                 */
                void shoot_ship(TCommander &, PacketPtr packet);

                /**
                 * @brief LAUNCH_GAME_REQ
                 * @param packet Packet from network
                 */
                void launch_game(TCommander &, PacketPtr packet);

                /**
                 * @brief Switch to next player
                 */
                void            next_player();

                /**
                 * @brief Start the game
                 */
                void            start_game();

                /**
                 * @brief Convert global client id to player1 or player2 or 2 in case of invalid player.
                 * @return Local player id.
                 */
                unsigned short  which_player(unsigned short id);

            public:
                Room(TRoomManager &, std::shared_ptr<spcbttl::commun::net::req::CreateRoomReq>);

                /**
                 * @brief Execute a packet from the room manager.
                 */
                void execute(PacketPtr);

                /**
                 * @brief Add player to room
                 * @param player Player to add
                 */
                void add_player(PlayerPtr player);

                /**
                 * @brief Add viewer to room
                 * @param viewer Viewer to add
                 */
                void add_viewer(PlayerPtr viewer);

                /**
                 * @brief Remove viewer.
                 * @param viewer Viewer to remove
                 */
                void del_viewer(PlayerPtr viewer);

                /**
                 * @brief Check if all player joined
                 * @return True if all player joined else False
                 */
                bool full_player();

                /**
                 * @brief Check if room is full of viewer.
                 * @return True if room is full of viewer else False.
                 */
                bool full_viewer();

                /**
                 * @brief Get the room status (NEW, WAITING_FOR_PLAYER, WAITING_FOR_LAUNCH, IN_PROFRESS, FINISH, NONE)
                 * @return The room status
                 */
                commun::room::State             status();

                /**
                 * @brief Get the room name.
                 * @return The room name.
                 */
                const std::string               &name();

                /**
                 * @brief Check if room allow viwers.
                 * @return
                 */
                bool                            allow_viewers();

                /**
                 * @brief Get the time limit of the room.
                 * @return time limit (FOURTEEN_MIN, THIRTY_MIN, FORTY_FILE_MIN, NO_LIMIT)
                 */
                commun::engine::TimeLimit                           time_limit();

                /**
                 * @brief Get the startup time.
                 * @return Startup time
                 */
                std::chrono::time_point<std::chrono::system_clock>  start_time();

                /**
                 * @brief Get the player list.
                 * @return player list
                 */
                std::list<PlayerPtr>            players();

                /**
                 * @brief Get the viewer list.
                 * @return viwer list.
                 */
                std::list<PlayerPtr>            viewers();

                /**
                 * @brief Get the player loose the game.
                 * @return Looser.
                 */
                PlayerPtr                       getLooser();
           };
        }
    }
}

#include "Engine/Room/Room.cpp"

#endif //T_CPP_SPACEBATTLE_2018_ROOM_HPP
