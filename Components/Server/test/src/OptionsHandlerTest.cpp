//!
//! @file OptionsHandlerTest.cpp
//! @author jbruel
//! @date 01/11/18
//!

#include "Conf/OptionsHandler.hpp"
#include <gtest/gtest.h>
#include <Commun/Exception/HelpException.hpp>

//!
//! @test Check all default arguments values.
//!
TEST (OptionsHandler, defaultArgumentsValues)
{
    spcbttl::server::conf::OptionsHandler   optionsHandler;
    const char * const                      argv[] = { "spacebattle-server" };

    optionsHandler.loadBinaryArguments(1, argv);
    EXPECT_TRUE(optionsHandler.getLogFilePath().empty());
    EXPECT_STRCASEEQ(optionsHandler.getHostAddress().c_str(), "127.0.0.1");
    EXPECT_EQ(optionsHandler.getPort(), static_cast<size_t>(4242));
    EXPECT_TRUE(optionsHandler.getVerboseMode());
}

//!
//! @test With --log correctly set.
//!
TEST (OptionsHandler, logFilePathArgument)
{
    spcbttl::server::conf::OptionsHandler   optionsHandler;
    const char * const                      argv[] = { "spacebattle-server", "--log", "./MyLogFile" };

    optionsHandler.loadBinaryArguments(3, argv);
    EXPECT_STRCASEEQ(optionsHandler.getLogFilePath().c_str(), "./MyLogFile");
}

//!
//! @test With -l correctly set.
//!
TEST (OptionsHandler, logFilePathShortArgument)
{
    spcbttl::server::conf::OptionsHandler   optionsHandler;
    const char * const                      argv[] = { "spacebattle-server", "-l", "./MyLogFile" };

    optionsHandler.loadBinaryArguments(3, argv);
    EXPECT_STRCASEEQ(optionsHandler.getLogFilePath().c_str(), "./MyLogFile");
}

//!
//! @test With --ip correctly set.
//!
TEST (OptionsHandler, serverIPArgument)
{
    spcbttl::server::conf::OptionsHandler   optionsHandler;
    const char * const                      argv[] = { "spacebattle-server", "--ip", "189.87.78.3" };

    optionsHandler.loadBinaryArguments(3, argv);
    EXPECT_STRCASEEQ(optionsHandler.getHostAddress().c_str(), "189.87.78.3");
}

//!
//! @test With --port correctly set.
//!
TEST (OptionsHandler, portArgument)
{
    spcbttl::server::conf::OptionsHandler   optionsHandler;
    const char * const                      argv[] = { "spacebattle-server", "--port", "9868" };

    optionsHandler.loadBinaryArguments(3, argv);
    EXPECT_EQ(optionsHandler.getPort(), static_cast<size_t>(9868));
}

//!
//! @test With -p correctly set.
//!
TEST (OptionsHandler, portShortArgument)
{
    spcbttl::server::conf::OptionsHandler   optionsHandler;
    const char * const                      argv[] = { "spacebattle-server", "-p", "9868" };

    optionsHandler.loadBinaryArguments(3, argv);
    EXPECT_EQ(optionsHandler.getPort(), static_cast<size_t>(9868));
}

//!
//! @test With invalid port.
//!
TEST (OptionsHandler, invalidPortArgument)
{
    spcbttl::server::conf::OptionsHandler   optionsHandler;
    const char * const                      argv[] = { "spacebattle-server", "--port", "dkfhdijfhn" };

    try {
        optionsHandler.loadBinaryArguments(3, argv);
    }
    catch (boost::program_options::error &e) {
        EXPECT_TRUE(true);
        return ;
    }
    EXPECT_TRUE(false);
}

//!
//! @test With --verbose correctly set.
//!
TEST (OptionsHandler, verboseArgument)
{
    spcbttl::server::conf::OptionsHandler   optionsHandler;
    const char * const                      argv[] = { "spacebattle-server", "--verbose", "false" };

    optionsHandler.loadBinaryArguments(3, argv);
    EXPECT_FALSE(optionsHandler.getVerboseMode());
}

//!
//! @test With -v correctly set.
//!
TEST (OptionsHandler, verboseShortArgument)
{
    spcbttl::server::conf::OptionsHandler   optionsHandler;
    const char * const                      argv[] = { "spacebattle-server", "-v", "false" };

    optionsHandler.loadBinaryArguments(3, argv);
    EXPECT_FALSE(optionsHandler.getVerboseMode());
}

//!
//! @test With invalid verbose mode.
//!
TEST (OptionsHandler, invalidVerboseModeArgument)
{
    spcbttl::server::conf::OptionsHandler   optionsHandler;
    const char * const                      argv[] = { "spacebattle-server", "--verbose", "dkfhdijfhn" };

    try {
        optionsHandler.loadBinaryArguments(3, argv);
    }
    catch (boost::program_options::error &e) {
        EXPECT_TRUE(true);
        return ;
    }
    EXPECT_TRUE(false);
}

//!
//! @test With -h correctly set.
//!
TEST (OptionsHandler, helpShortArgument)
{
    spcbttl::server::conf::OptionsHandler   optionsHandler;
    const char * const                      argv[] = { "spacebattle-server", "-h" };
    std::string                             outStdout;
    std::string                             outStderr;

    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();
    try {
        optionsHandler.loadBinaryArguments(2, argv);
    }
    catch (spcbttl::HelpException &) {
        outStdout = testing::internal::GetCapturedStdout();
        outStderr = testing::internal::GetCapturedStderr();
        EXPECT_FALSE(outStdout.empty());
        EXPECT_TRUE(outStderr.empty());
        return ;
    }
    EXPECT_TRUE(false);
}

//!
//! @test With --help correctly set.
//!
TEST (OptionsHandler, helpArgument)
{
    spcbttl::server::conf::OptionsHandler   optionsHandler;
    const char * const                      argv[] = { "spacebattle-server", "--help" };
    std::string                             outStdout;
    std::string                             outStderr;

    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();
    try {
        optionsHandler.loadBinaryArguments(2, argv);
    }
    catch (spcbttl::HelpException &) {
        outStdout = testing::internal::GetCapturedStdout();
        outStderr = testing::internal::GetCapturedStderr();
        EXPECT_FALSE(outStdout.empty());
        EXPECT_TRUE(outStderr.empty());
        return ;
    }
    EXPECT_TRUE(false);
}
