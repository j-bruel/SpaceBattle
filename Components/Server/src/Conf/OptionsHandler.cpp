//!
//! @file OptionsHandler.cpp
//! @author jbruel
//! @date 01/11/2018
//!

#include "Conf/OptionsHandler.hpp"
#include "Commun/Exception/HelpException.hpp"
#include <iostream>

namespace spcbttl
{
namespace server
{
namespace conf
{
    OptionsHandler::OptionsHandler() :  mLogFilePath(std::string()), mPort(0), mAddress(std::string()), mVerbose(true),
                                        mCmdlineOptions("Space Battle - Application configuration ", HelpMinSizeLine, HelpMaxSizeLine)
    {
        mCmdlineOptions.add_options()
                ("help,h", "Displays help/usage.")
                ("ip", boost::program_options::value<std::string>(&mAddress)->default_value("127.0.0.1"), "Server IP address.")
	            ("port,p", boost::program_options::value<size_t>(&mPort)->default_value(4242), "The server port.")
                ("verbose,v", boost::program_options::value<bool>(&mVerbose)->default_value(true), "Enable logging (true or false).")
                ("log,l", boost::program_options::value<std::string>(&mLogFilePath), "Output log file.");
    }

    void    OptionsHandler::loadBinaryArguments(int argc, const char * const *argv)
    {
        boost::program_options::variables_map   vm;

        boost::program_options::store(boost::program_options::parse_command_line(argc, argv, mCmdlineOptions), vm);
        boost::program_options::notify(vm);
        if (vm.count("help"))
        {
            showHelp(argv[0]);
            throw HelpException("");
        }
    }

    void    OptionsHandler::showHelp(const char *appName) const
    {
        std::cout << "SpaceBattle is server game application." << std::endl << std::endl;
        std::cout << "usage: " << appName << " --ip <...> --port <...> [--log <...>]"  << std::endl << std::endl;
        std::cout << mCmdlineOptions << std::endl << std::endl;
    }

}
}
}
