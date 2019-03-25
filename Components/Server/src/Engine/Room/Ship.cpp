//
// Created by grosso_a on 07/11/18.
//

#include <algorithm>
# include "Engine/Room/Ship.hpp"

namespace spcbttl
{
    namespace server
    {
        namespace engine
        {

            Ship::Ship(std::initializer_list<size_t> parts)
            {
                for (size_t coord : parts) {
                    this->_parts.push_back(std::make_shared<ShipPart>(ShipPart((uint8_t)coord)));
                }
            }

            unsigned long  Ship::size()
            {
                return this->_parts.size();
            }

            std::list<std::shared_ptr<Ship::ShipPart>>    &Ship::parts()
            {
                return this->_parts;
            }

            bool Ship::is_horizontal()
            {
                unsigned int y = _parts.front()->coordinate() / GAME_BOARD_SIZE;
                int curentX = -1;

                _parts.sort([](const std::shared_ptr<ShipPart> &partLeft,
                               const std::shared_ptr<ShipPart> &partRight) {
                    return ((partLeft->coordinate() % GAME_BOARD_SIZE) < (partRight->coordinate() % GAME_BOARD_SIZE));
                });
                for (const std::shared_ptr<ShipPart> &part : _parts) {
                    if ((part->coordinate() / GAME_BOARD_SIZE) != y) {
                        return false;
                    }
                    if (curentX == -1) {
                        curentX = part->coordinate() % GAME_BOARD_SIZE;
                    } else if (curentX + 1 != (part->coordinate() % GAME_BOARD_SIZE)) {
                        return false;
                    } else {
                        curentX++;
                    }
                }
                return true;
            }

            bool Ship::is_vertical()
            {
                unsigned int x = _parts.front()->coordinate() % GAME_BOARD_SIZE;
                int currenY = -1;

                _parts.sort([](const std::shared_ptr<ShipPart> &partLeft,
                               const std::shared_ptr<ShipPart> &partRight) {
                    return ((partLeft->coordinate() / GAME_BOARD_SIZE) < (partRight->coordinate() / GAME_BOARD_SIZE));
                });
                for (const std::shared_ptr<ShipPart> &part : _parts) {
                    if ((part->coordinate() % GAME_BOARD_SIZE) != x) {
                        return false;
                    }
                    if (currenY == -1) {
                        currenY = part->coordinate() / GAME_BOARD_SIZE;
                    } else if (currenY + 1 != part->coordinate() / GAME_BOARD_SIZE) {
                        return false;
                    } else {
                        currenY++;
                    }
                }
                return true;
            }

            bool Ship::has_duplicate()
            {
                int current = -1;
                _parts.sort([](const std::shared_ptr<ShipPart> &partLeft,
                               const std::shared_ptr<ShipPart> &partRight) {
                    return (partLeft->coordinate()  < partRight->coordinate());
                });
                for (const std::shared_ptr<ShipPart> &part : _parts) {
                    if (current == -1) {
                        current = part->coordinate();
                    } else if (current == part->coordinate()) {
                        return true;
                    } else {
                        current = part->coordinate();
                    }
                }
                return false;
            }

            bool Ship::valid_coord()
            {
                for (const std::shared_ptr<ShipPart> &part : _parts) {
                    if (part->coordinate() >= GAME_BOARD_SIZE*GAME_BOARD_SIZE) {
                        return false;
                    }
                }
                return true;
            }

            bool Ship::validate()
            {
                return (!_parts.empty()
                    && this->valid_coord()
                    && !this->has_duplicate()
                    && (this->is_horizontal() || this->is_vertical()));
            }

            bool Ship::destroyed()
            {
                for (const std::shared_ptr<ShipPart> &part : _parts) {
                    if (part->status() == ShipPartStatus::GOOD) {
                        return false;
                    }
                }
                return true;
            }

            std::string Ship::print() {
                std::string msg;

                msg += std::string("size:") + std::to_string(this->size()) + std::string(" { ");
                for (const std::shared_ptr<ShipPart> &part : _parts) {
                    msg += std::to_string(part->coordinate()) + std::string(", ");
                }
                msg += std::string("}");
                return msg;
            }

        }
    }
}
