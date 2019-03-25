//
// Created by grosso_a on 07/11/18.
//

#ifndef T_CPP_SPACEBATTLE_2018_SHIP_HPP
#define T_CPP_SPACEBATTLE_2018_SHIP_HPP


# include <list>
# include <string>
# include <stdint-gcc.h>
#include <Conf/Engine.hpp>
#include <memory>

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
            //!
            //! @class Ship
            //!
            class Ship
            {
            public:
                enum ShipPartStatus {
                    GOOD,
                    DESTROYED
                };

                /**
                 * @class ShipPart
                 * @brief Store one part of the ship.
                 */
                class ShipPart {
                private:
                    uint8_t         _coordinate;
                    ShipPartStatus  _status;

                public:

                    ShipPart(uint8_t coord)
                    {
                        this->_status = ShipPartStatus::GOOD;
                        this->_coordinate = coord;
                    }

                    /**
                     * @brief Destroy ship part
                     */
                    void            shoot() {
                        this->_status = ShipPartStatus::DESTROYED;
                    }

                    /**
                     * @brief Get the ship part coordinates.
                     * @return coordinates of the ship part.
                     */
                    uint8_t         coordinate()
                    {
                        return this->_coordinate;
                    }

                    /**
                     * @brief Get the status of the part.
                     * @return status.
                     */
                    ShipPartStatus  status()
                    {
                        return this->_status;
                    }
                };

            private:
                std::list<std::shared_ptr<ShipPart>>     _parts;

                /**
                 * @brief Check if the ship is horizontal.
                 * @return True if horizontal else False.
                 */
                bool is_horizontal();

                /**
                 * @brief Check if the ship is vertical.
                 * @return True if vertical else False.
                 */
                bool is_vertical();

                /**
                 * @brief Check if the ship has part duplicated.
                 * @return True if the ship has duplicated parts else False.
                 */
                bool has_duplicate();

                /**
                 * @brief Check if each part of the ship is in the board.
                 * @return True if each pate are valid else False.
                 */
                bool valid_coord();


            public:
                Ship(std::initializer_list<size_t>);

                /**
                 * @brief Get the ship size.
                 * @return ship size.
                 */
                unsigned long                            size();

                /**
                 * @brief Get all parts of the ship.
                 * @return ship parts.
                 */
                std::list<std::shared_ptr<ShipPart>>     &parts();

                /**
                 * @brief Check if the ship is valid.
                 * @return True if the ship is valid else False.
                 */
                bool                                     validate();

                /**
                 * @brief Check if the ship is destroyed.
                 * @return True if the ship is destroyed else False.
                 */
                bool                                     destroyed();

                /**
                 * @brief Print the ship.
                 * @return ship is pretty.
                 */
                std::string                              print();
            };
        }
    }
}

#endif //T_CPP_SPACEBATTLE_2018_SHIP_HPP
