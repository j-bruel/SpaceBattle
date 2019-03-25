//
// Created by grosso_a on 07/11/18.
//

#ifndef T_CPP_SPACEBATTLE_2018_PLAYER_HPP
#define T_CPP_SPACEBATTLE_2018_PLAYER_HPP

#include <mutex>
#include "Ship.hpp"
#include <Commun/Network/Requests/AuthenticateReq.hpp>
#include <sckcpp/Client.hpp>
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
            /**
             * @class Player
             * @brief The object replesent a player on each state of the game.
             */
            class Player
            {
            public:
                /**
                 * Store the player status:
                 * UNREGISTRED : Player not authenticated.
                 * REGISTRED : Player authenticated but not in room.
                 * VIEWER : Player as join room in VIEWER mode.
                 * PLAYER : Player as join room in PLAYER mode.
                 */
                enum Status {
                    UNREGISTRED,
                    REGISTRED,
                    VIEWER,
                    PLAYER,
                };

            private:
                const unsigned short                                _id;
                const std::string                                   _name;
                sckcpp::tcp::ClientSocket                           &_socket;
                Status                                              _status;
                std::mutex                                          _lock;
                unsigned int                                        _alive_count;
                bool                                                _ready;

            public:
                /**
                 * @brief Constructor of Player object
                 * @param id Player id
                 * @param name Player
                 * @param socket Network socket
                 */
                Player(unsigned short id, const std::string &name, sckcpp::tcp::ClientSocket &socket);

                /**
                 * @brief Check if player in room.
                 * @return
                 */
                bool in_room();

                /**
                 * @brief Get the player id.
                 * @return player id
                 */
                unsigned short id();

                /**
                 * @brief Get the player network socket
                 * @return network socket
                 */
                sckcpp::tcp::ClientSocket &socket();

                /**
                 * @brief Change the player status (UNREGISTRED, REGISTRED, VIEWER, PLAYER).
                 * @param status The new player status.
                 */
                void set_status(Status status);

                /**
                 * @brief Get teh player status
                 * @return player status
                 */
                Status get_status();

                /**
                 * @brief Set player is alive.
                 */
                void alive();

                /**
                 * @brief Set player is ready to play.
                 */
                void ready();

                /**
                 * @brief Check if player is ready
                 * @return True if player is ready else False.
                 */
                bool is_ready();

                /**
                 * @brief Check if player is alive.
                 * @return True if player is alive else False.
                 */
                bool is_alive();

                /**
                 * @brief Get the player name
                 * @return player name
                 */
                const std::string &get_name();
            };
        }
    }
}

#endif //T_CPP_SPACEBATTLE_2018_PLAYER_HPP
