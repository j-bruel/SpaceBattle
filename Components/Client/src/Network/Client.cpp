//!
//! @file Client.cpp
//! @author jbruel
//! @date 25/11/18
//!

#include "Network/Client.hpp"
#include "Commun/Exception/NetworkException.hpp"
#include <Commun/Tools/Log/Idx.hpp>
#include <plog/Log.h>
#include <plog/Severity.h>

namespace spcbttl
{
namespace client
{
namespace net
{

    sckcpp::tcp::ClientSocket   &Client::connect(const std::string &ip, unsigned short port)
    {
        mClientSocket.forceConnectionStatusHas(true);
        mUnp.reserve_buffer(mWindowSize);
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::verbose) << "Try server connexion.";
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Server IP : " << ip;
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Server port : " << port;

        try {
            mClientSocket.connect(ip, port);/*, [&]() {
                LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Connect to the server.";
                onConnect();
            });*/
        }
        catch (boost::system::system_error &e) {
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::fatal) << "Impossible to connect to the server.";
            throw spcbttl::NetworkException(e.what());
        }
        return (mClientSocket);
    }

    void    Client::run()
    {
        start();
        mClientSocket.run();
    }

    void Client::stop() {
        mClientSocket.close();
        mIOService.stop();
    }

    void    Client::processReadLoop()
    {
        mClientSocket.asyncRead(mUnp.buffer(), mWindowSize, [&](size_t bytes_transferred) {
            mUnp.buffer_consumed(bytes_transferred);
            msgpack::object_handle oh;
            while (mUnp.next(oh)) {
                msgpack::object obj = oh.get();
                mPacketManager.packetReceived(obj, mClientSocket);
            }
            processReadLoop();
        });
    }

}
}
}