//!
//! @file SpaceBattle.cpp
//! @author jbruel
//! @date 01/11/18
//!

#include "Network/Server.hpp"
#include "Core/SpaceBattle.hpp"
#include "Commun/Exception/CoreException.hpp"
#include "Commun/Tools/Log/Idx.hpp"
#include "Commun/Tools/Log/Initializer.hpp"
#include <plog/Log.h>
#include <iostream>
#include <algorithm>
namespace spcbttl
{
namespace server
{
namespace core
{
    SpaceBattle::SpaceBattle():
        mPacketDispatcher(server::engine::PacketDispatcher::TPacketQueue::Instance(), mRoomManager, std::thread::hardware_concurrency())
    {
    }

    void    SpaceBattle::init(int argc, const char * const *argv)
    {
        initOptionsApp(argc, argv);
        initLog();
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Server IP Address : " << mOptionsHandler.getHostAddress();
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Server port : " << mOptionsHandler.getPort();
    }

    void    SpaceBattle::run()
    {
        try {
            net::Server server(mOptionsHandler.getHostAddress(), mOptionsHandler.getPort());

            mPacketDispatcher.start();
            server.run();
            mPacketDispatcher.stop();
        }
        catch (boost::system::system_error &e) {
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::fatal) << e.what();
        }
    }

    void    SpaceBattle::initOptionsApp(int argc, const char * const *argv)
    {
        try {
            mOptionsHandler.loadBinaryArguments(argc, argv);
        }
        catch (boost::program_options::error &e) {
            mOptionsHandler.showHelp(argv[0]);
            throw CoreException(e.what());
        }
    }

    void    SpaceBattle::initLog()
    {
        if (!mOptionsHandler.getVerboseMode())
            return ;
        commun::tool::log::initialize(mOptionsHandler.getLogFilePath(), plog::verbose, plog::verbose);
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Space Battle application as been launch.";
        if (mOptionsHandler.getLogFilePath().empty())
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::warning) << "No log output file as been set. No logging will be available.";
        else
            LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Log output file is " << mOptionsHandler.getLogFilePath();
    }

}
}
}
