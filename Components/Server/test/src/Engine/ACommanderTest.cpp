//
// Created by grosso_a on 12/11/18.
//


# include <gtest/gtest.h>
# include <Engine/ACommanderTest.hpp>
# include "Commun/UTWorkDirectory.hpp"
# include "Commun/Tools/Log/Initializer.hpp"
# include <plog/Log.h>
# include <fstream>
# include "Engine/Logger.hpp"

//!
//! @test ACommander initialisation
//!
TEST (ACommander, Init)
{
    std::string outStdout;
    std::string outStderr;

    initLogger();
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();
    spcbttl::server::engine::ACommanderTest  commander;
    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStdout.find("ACommander: command id:1 is already set.") != std::string::npos);
    EXPECT_TRUE(outStderr.empty());
}

//!
//! @test ACommander invalid command
//!
TEST (ACommander, InvalidCommand)
{
    std::string outStdout;
    std::string outStderr;

    initLogger();
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();
    spcbttl::server::engine::ACommanderTest  commander;
    commander.execute(10,  std::make_shared<int>(10));
    commander.execute(2, std::make_shared<int>(10));
    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStdout.find("ACommander: command id:1 is already set.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("ACommander: command id:10 is invalid.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("ACommander: command id:2 is invalid.") != std::string::npos);
    EXPECT_TRUE(outStderr.empty());
}

//!
//! @test ACommander exec command
//!
TEST (ACommander, ExecCommand)
{
    std::string outStdout;
    std::string outStderr;

    initLogger();
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();
    spcbttl::server::engine::ACommanderTest  commander;
    commander.execute(0, std::make_shared<int>(42));
    commander.execute(1, std::make_shared<int>(0));
    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStdout.find("ACommander: command id:1 is already set.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("ACommanderTest: command id:0 param:42") != std::string::npos);
    EXPECT_TRUE(outStdout.find("ACommanderTest: command id:1 param:0") != std::string::npos);
    EXPECT_TRUE(outStderr.empty());
}