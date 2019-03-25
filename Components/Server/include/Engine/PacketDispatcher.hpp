//
// Created by grosso_a on 12/11/18.
//

#ifndef T_CPP_SPACEBATTLE_2018_PACKETDISPATCHER_HPP
#define T_CPP_SPACEBATTLE_2018_PACKETDISPATCHER_HPP


#include <thread>
#include <future>
#include <plog/Log.h>
#include <Commun/Tools/Log/Idx.hpp>
#include "Commun/Tools/BufferDataManager.hpp"
#include "Commun/Exception/BufferDataManagerException.hpp"
#include "Engine/Room/Room.hpp"
#include "Commun/Network/Packet.hpp"
#include "Engine/RoomManager/RoomManager.hpp"

namespace spcbttl
{
    //!
    //! @namespace commun
    //!
    namespace server
    {
        //!
        //! @namespace engine
        //!
        namespace engine
        {
            /**
             * @brief The packet dispatcher as multiple threads (ThreadPool). These threads get packet from a queue
             * and call the RoomManager::execute function.
             */
            class PacketDispatcher
            {
            public:
                typedef commun::tool::BufferDataManager<std::shared_ptr<commun::net::Packet>>   TPacketQueue;
                typedef RoomManager<MAX_ROOM, MAX_PLAYER>                                       TRoomManager;

            private:
                TPacketQueue                        &_queue;
                std::list<std::thread>              _workers;
                bool                                _run;
                std::mutex                          _lock;
                unsigned int                        _size;
                TRoomManager                        &_rooms;

                /**
                 * @brief A worker loop. The name is stalker because there are looking in the queue :-p.
                 */
                void stalker(unsigned int);

            public:

                /**
                 * @brief Packet dispatcher constructor.
                 * @param queue : This queue are used by worker to get network packets.
                 * @param rooms : The room manager is used to dispatch packet to specific room.
                 * @param pool_size : The number of workers in thread pool.
                 */
                PacketDispatcher(TPacketQueue &queue, TRoomManager &rooms, unsigned int pool_size);

                /**
                 * @brief Check if the packet dispatcher is running.
                 * @return True if dispatcher is running else False.
                 */
                bool isRunning();


                /**
                 * @brief Start all workers.
                 */
                void start();


                /**
                 * @brief Stop all workers. Warning: Check if queue is empty before stop !
                 */
                void stop();
            };
        }
    }
}

#endif //T_CPP_SPACEBATTLE_2018_PACKETDISPATCHER_HPP
