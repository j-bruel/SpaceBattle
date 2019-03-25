//!
//! @file Server.cpp
//! @author jbruel
//! @date 02/11/18
//!

#include "Network/Server.hpp"
#include "Commun/Tools/Log/Idx.hpp"
#include <plog/Log.h>

namespace spcbttl
{
namespace server
{
namespace net
{

    Server::Server(const std::string &ip, size_t port) : mIos(), mServerSocket(mIos)
    {
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::verbose) << "Creating a server instance.";
        setupAcceptor(ip, port);
        setupCallbacks();
    }

    Server::~Server()
    {
        mServerSocket.stop();
        mClientManager.stopAll();
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Server stopped.";
    }

    void    Server::run()
    {
        mServerSocket.asyncAccept();
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::verbose) << "Enable asynchrone.";
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::verbose) << "Running server.";
        mServerSocket.run();
    }

    void    Server::stop()
    {
        mServerSocket.stop();
        notifyClientsServerDisconnect();
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Server stopped.";
    }

    void    Server::setupAcceptor(const std::string &ip, size_t port)
    {
        mServerSocket.bind(ip, static_cast<unsigned short>(port));
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "Binding ip : " << ip << " port : " << port;
        mServerSocket.enableReUseAddress();
        mServerSocket.listen();
    }

    void    Server::setupCallbacks()
    {
        mServerSocket.setOnClientAcceptedCallback([=](sckcpp::ClientPtr client) {

            client->setOnStopClientCallback([=](sckcpp::ClientPtr c){

                LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::warning) << "A client : " << client->getInfo() << " as been disconnected.";
                mClientManager.remove(c);
            });
            client->start();
            mClientManager.add(client);
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "A client as been accepted : "<< client->getInfo();
        });
    }

    void    Server::notifyClientsServerDisconnect()
    {
        mClientManager.foreach([=](sckcpp::ClientPtr client){

            client->sendServerDisconnectRequest();
        });
    }

}
}
}