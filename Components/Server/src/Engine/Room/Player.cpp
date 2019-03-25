//
// Created by grosso_a on 07/11/18.
//

# include "Engine/Room/Player.hpp"

namespace spcbttl
{
    namespace server
    {
        namespace engine
        {
            Player::Player(unsigned short id, const std::string &name, sckcpp::tcp::ClientSocket &socket):
                    _id(id),
                    _name(name),
                    _socket(socket),
                    _alive_count(0),
                    _ready(false)
            {
            }

            bool Player::in_room() {
                return (_status == VIEWER || _status == PLAYER);
            }

            unsigned short Player::id() {
                return this->_id;
            }

            sckcpp::tcp::ClientSocket &Player::socket() {
                return  _socket;
            }

            void Player::set_status(Status status) {
                std::unique_lock<std::mutex> lock(this->_lock);
                _status = status;
            }

            Player::Status Player::get_status() {
                return _status;
            }

            void Player::alive() {
                std::unique_lock<std::mutex> lock(this->_lock);
                this->_alive_count = 0;
            }

            void Player::ready() {
                std::unique_lock<std::mutex> lock(this->_lock);
                this->_ready = true;
            }

            bool Player::is_ready() {
                return _ready;
            }

            bool Player::is_alive() {
                std::unique_lock<std::mutex> lock(this->_lock);
                if (_alive_count >= ALIVE_COUNT) {
                    return false;
                } else {
                    _alive_count += 1;
                    return true;
                }
            }

            const std::string &Player::get_name()
            {
                std::unique_lock<std::mutex> lock(this->_lock);
                return _name;
            }
        }
    }
}
