//
// Created by grosso_a on 17/11/18.
//

#include <Engine/PacketDispatcher.hpp>

namespace spcbttl
{
    namespace server
    {
        namespace engine
        {
            PacketDispatcher::PacketDispatcher(TPacketQueue &queue, TRoomManager &rooms, unsigned int pool_size):
                _queue(queue),
                _rooms(rooms)
            {
                //TODO pool_size
//                if (pool_size < 2) {
//                    _size = 2;
//                } else {
                    _size = pool_size;
//                }
            }


            void PacketDispatcher::stalker(unsigned int id)
            {
                LOG_(commun::tool::log::IN_CONSOLE, plog::warning) << "Stalker " << id << " start.";
                while (this->isRunning())
                {
                    try
                    {
                        std::shared_ptr<commun::net::Packet>     packet = _queue.pop_front(1000);
                        LOG_(commun::tool::log::IN_CONSOLE, plog::warning)
                                    << "Stalker execute packet {cmd_type:" << int(packet->mPacketHeader.mCmdType)
                                    << " client_id:" << int(packet->mPacketHeader.mClientId) << "}";
                        _rooms.execute(packet);
                        _rooms.checks();
                    } catch (BufferDataManagerException&) {
                        _rooms.checks();
                    }
                }
                LOG_(commun::tool::log::IN_CONSOLE, plog::warning) << "Stalker " << id << " stop.";
            }

            bool PacketDispatcher::isRunning()
            {
                std::unique_lock<std::mutex> lock(this->_lock);
                return this->_run;
            }

            void PacketDispatcher::start()
            {
                LOG_(commun::tool::log::IN_CONSOLE, plog::warning) << "Start PacketDispatcher with " << _size << " threads.";
                this->_lock.lock();
                _run = true;
                for (unsigned int i=0; i < _size; i++)
                    _workers.push_back(std::thread(&PacketDispatcher::stalker, this, i));
                this->_lock.unlock();
            }

            void PacketDispatcher::stop()
            {
                this->_lock.lock();
                this->_run = false;
                this->_lock.unlock();
                for (std::thread &th : _workers)
                    th.join();
                _workers.clear();
                LOG_(commun::tool::log::IN_CONSOLE, plog::warning) << "Stop PacketDispatcher.";
            }
        }
    }
}
