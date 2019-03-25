//!
//! @file LogTest.cpp
//! @author jbruel
//! @date 01/11/12
//!

#include "Commun/UTWorkDirectory.hpp"
#include "Commun/Tools/Log/Initializer.hpp"
#include <plog/Log.h>
#include <fstream>
#include <gtest/gtest.h>

//!
//! @static
//! @bref Init logger.
//!
static void initLogger()
{
    static bool isInit = false;

    if (!isInit)
    {
        spcbttl::commun::tool::log::initialize(std::string(UTWorkDirectory) + "/utLog", plog::debug, plog::debug);
        isInit = true;
    }
}

//!
//! @static
//! @fn static const std::string readFile(const std::string &filePath)
//! @brief Read a file and return his content.
//! @param filePath File to read.
//! @return Content file.
//!
static const std::string    readFile(const std::string &filePath)
{
    std::ifstream   ifs(filePath.c_str());
    std::string     str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

    return (str);
}

 //!
 //! @test Simple log on console.
 //!
TEST (Log, simpleLogOnConsole)
{
    std::string outStdout;
    std::string outStderr;

    initLogger();
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();
    LOG_(spcbttl::commun::tool::log::IN_CONSOLE, plog::warning) << "simpleLogOnConsole test.";
    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStderr.empty());
    EXPECT_NE(outStdout.find("simpleLogOnConsole test"), std::string::npos);
}

//!
//! @test Multi log on console.
//!
TEST (Log, multiLogOnConsole)
{
    std::string outStdout;
    std::string outStderr;

    initLogger();
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();
    LOG_(spcbttl::commun::tool::log::IN_CONSOLE, plog::warning) << "multiLogOnConsole.0 test.";
    LOG_(spcbttl::commun::tool::log::IN_CONSOLE, plog::warning) << "multiLogOnConsole.1 test.";
    LOG_(spcbttl::commun::tool::log::IN_CONSOLE, plog::warning) << "multiLogOnConsole.2 test.";
    LOG_(spcbttl::commun::tool::log::IN_CONSOLE, plog::warning) << "multiLogOnConsole.3 test.";
    LOG_(spcbttl::commun::tool::log::IN_CONSOLE, plog::warning) << "multiLogOnConsole.4 test.";
    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStderr.empty());
    EXPECT_NE(outStdout.find("multiLogOnConsole.0 test"), std::string::npos);
    EXPECT_NE(outStdout.find("multiLogOnConsole.1 test"), std::string::npos);
    EXPECT_NE(outStdout.find("multiLogOnConsole.2 test"), std::string::npos);
    EXPECT_NE(outStdout.find("multiLogOnConsole.3 test"), std::string::npos);
    EXPECT_NE(outStdout.find("multiLogOnConsole.4 test"), std::string::npos);
}

//!
//! @test Multi log on console.
//!
TEST (Log, multiLogOnConsoleWithDiffSeverity)
{
    std::string outStdout;
    std::string outStderr;

    initLogger();
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();
    LOG_(spcbttl::commun::tool::log::IN_CONSOLE, plog::fatal) << "multiLogOnConsoleWithDiffSeverity.0 test.";
    LOG_(spcbttl::commun::tool::log::IN_CONSOLE, plog::warning) << "multiLogOnConsoleWithDiffSeverity.1 test.";
    LOG_(spcbttl::commun::tool::log::IN_CONSOLE, plog::warning) << "multiLogOnConsoleWithDiffSeverity.2 test.";
    LOG_(spcbttl::commun::tool::log::IN_CONSOLE, plog::fatal) << "multiLogOnConsoleWithDiffSeverity.3 test.";
    LOG_(spcbttl::commun::tool::log::IN_CONSOLE, plog::error) << "multiLogOnConsoleWithDiffSeverity.4 test.";
    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStderr.empty());
    EXPECT_NE(outStdout.find("multiLogOnConsoleWithDiffSeverity.0 test"), std::string::npos);
    EXPECT_NE(outStdout.find("multiLogOnConsoleWithDiffSeverity.1 test"), std::string::npos);
    EXPECT_NE(outStdout.find("multiLogOnConsoleWithDiffSeverity.2 test"), std::string::npos);
    EXPECT_NE(outStdout.find("multiLogOnConsoleWithDiffSeverity.3 test"), std::string::npos);
    EXPECT_NE(outStdout.find("multiLogOnConsoleWithDiffSeverity.4 test"), std::string::npos);
}

//!
//! @test Multi log on console with locked severity.
//!
TEST (Log, multiLogOnConsoleWithLockedSeverity)
{
    std::string outStdout;
    std::string outStderr;

    initLogger();
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();
    LOG_(spcbttl::commun::tool::log::IN_CONSOLE, plog::verbose) << "multiLogOnConsoleWithLockedSeverity.0 test.";
    LOG_(spcbttl::commun::tool::log::IN_CONSOLE, plog::warning) << "multiLogOnConsoleWithLockedSeverity.1 test.";
    LOG_(spcbttl::commun::tool::log::IN_CONSOLE, plog::verbose) << "multiLogOnConsoleWithLockedSeverity.2 test.";
    LOG_(spcbttl::commun::tool::log::IN_CONSOLE, plog::fatal) << "multiLogOnConsoleWithLockedSeverity.3 test.";
    LOG_(spcbttl::commun::tool::log::IN_CONSOLE, plog::error) << "multiLogOnConsoleWithLockedSeverity.4 test.";
    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStderr.empty());
    EXPECT_EQ(outStdout.find("multiLogOnConsoleWithLockedSeverity.0 test"), std::string::npos);
    EXPECT_NE(outStdout.find("multiLogOnConsoleWithLockedSeverity.1 test"), std::string::npos);
    EXPECT_EQ(outStdout.find("multiLogOnConsoleWithLockedSeverity.2 test"), std::string::npos);
    EXPECT_NE(outStdout.find("multiLogOnConsoleWithLockedSeverity.3 test"), std::string::npos);
    EXPECT_NE(outStdout.find("multiLogOnConsoleWithLockedSeverity.4 test"), std::string::npos);
}

//!
//! @test Empty msg.
//!
TEST (Log, emptyMessageOnConsole)
{
    std::string outStdout;
    std::string outStderr;

    initLogger();
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();
    LOG_(spcbttl::commun::tool::log::IN_CONSOLE, plog::warning) << "";
    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStderr.empty());
    EXPECT_FALSE(outStdout.empty());
}

//!
//! @test False severity.
//!
TEST (Log, falseSeverityOnConsole)
{
    std::string outStdout;
    std::string outStderr;

    initLogger();
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();
    LOG_(spcbttl::commun::tool::log::IN_CONSOLE, static_cast<plog::Severity>(845)) << "falseSeverityOnConsole";
    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStderr.empty());
    EXPECT_TRUE(outStdout.empty());
}

//!
//! @test Simple log on file.
//!
TEST (Log, simpleLogOnFile)
{
    initLogger();
    system(std::string(std::string("echo -n "" > ") + UTWorkDirectory + "/utLog").c_str());
    LOG_(spcbttl::commun::tool::log::IN_FILE, plog::warning) << "simpleLogOnFile test.";
    EXPECT_NE(readFile(std::string(UTWorkDirectory) + "/utLog").find("simpleLogOnFile test"), std::string::npos);
}

//!
//! @test Multi log on file.
//!
TEST (Log, multiLogOnFile)
{
    std::string content;

    initLogger();
    system(std::string(std::string("echo -n "" > ") + UTWorkDirectory + "/utLog").c_str());
    LOG_(spcbttl::commun::tool::log::IN_FILE, plog::warning) << "multiLogOnFile.0 test.";
    LOG_(spcbttl::commun::tool::log::IN_FILE, plog::warning) << "multiLogOnFile.1 test.";
    LOG_(spcbttl::commun::tool::log::IN_FILE, plog::warning) << "multiLogOnFile.2 test.";
    LOG_(spcbttl::commun::tool::log::IN_FILE, plog::warning) << "multiLogOnFile.3 test.";
    LOG_(spcbttl::commun::tool::log::IN_FILE, plog::warning) << "multiLogOnFile.4 test.";
    content = readFile(std::string(UTWorkDirectory) + "/utLog");
    EXPECT_NE(content.find("multiLogOnFile.0 test"), std::string::npos);
    EXPECT_NE(content.find("multiLogOnFile.1 test"), std::string::npos);
    EXPECT_NE(content.find("multiLogOnFile.2 test"), std::string::npos);
    EXPECT_NE(content.find("multiLogOnFile.3 test"), std::string::npos);
    EXPECT_NE(content.find("multiLogOnFile.4 test"), std::string::npos);
}

//!
//! @test Multi log on file.
//!
TEST (Log, multiLogOnFileWithDiffSeverity)
{
    std::string content;

    initLogger();
    system(std::string(std::string("echo -n "" > ") + UTWorkDirectory + "/utLog").c_str());
    LOG_(spcbttl::commun::tool::log::IN_FILE, plog::fatal) << "multiLogOnFileWithDiffSeverity.0 test.";
    LOG_(spcbttl::commun::tool::log::IN_FILE, plog::warning) << "multiLogOnFileWithDiffSeverity.1 test.";
    LOG_(spcbttl::commun::tool::log::IN_FILE, plog::warning) << "multiLogOnFileWithDiffSeverity.2 test.";
    LOG_(spcbttl::commun::tool::log::IN_FILE, plog::fatal) << "multiLogOnFileWithDiffSeverity.3 test.";
    LOG_(spcbttl::commun::tool::log::IN_FILE, plog::error) << "multiLogOnFileWithDiffSeverity.4 test.";
    content = readFile(std::string(UTWorkDirectory) + "/utLog");
    EXPECT_NE(content.find("multiLogOnFileWithDiffSeverity.0 test"), std::string::npos);
    EXPECT_NE(content.find("multiLogOnFileWithDiffSeverity.1 test"), std::string::npos);
    EXPECT_NE(content.find("multiLogOnFileWithDiffSeverity.2 test"), std::string::npos);
    EXPECT_NE(content.find("multiLogOnFileWithDiffSeverity.3 test"), std::string::npos);
    EXPECT_NE(content.find("multiLogOnFileWithDiffSeverity.4 test"), std::string::npos);
}

//!
//! @test Multi log on file with locked severity.
//!
TEST (Log, multiLogOnFileWithLockedSeverity)
{
    std::string content;

    initLogger();
    system(std::string(std::string("echo -n "" > ") + UTWorkDirectory + "/utLog").c_str());
    LOG_(spcbttl::commun::tool::log::IN_FILE, plog::verbose) << "multiLogOnFileWithLockedSeverity.0 test.";
    LOG_(spcbttl::commun::tool::log::IN_FILE, plog::warning) << "multiLogOnFileWithLockedSeverity.1 test.";
    LOG_(spcbttl::commun::tool::log::IN_FILE, plog::verbose) << "multiLogOnFileWithLockedSeverity.2 test.";
    LOG_(spcbttl::commun::tool::log::IN_FILE, plog::fatal) << "multiLogOnFileWithLockedSeverity.3 test.";
    LOG_(spcbttl::commun::tool::log::IN_FILE, plog::error) << "multiLogOnFileWithLockedSeverity.4 test.";
    content = readFile(std::string(UTWorkDirectory) + "/utLog");
    EXPECT_EQ(content.find("multiLogOnFileWithLockedSeverity.0 test"), std::string::npos);
    EXPECT_NE(content.find("multiLogOnFileWithLockedSeverity.1 test"), std::string::npos);
    EXPECT_EQ(content.find("multiLogOnFileWithLockedSeverity.2 test"), std::string::npos);
    EXPECT_NE(content.find("multiLogOnFileWithLockedSeverity.3 test"), std::string::npos);
    EXPECT_NE(content.find("multiLogOnFileWithLockedSeverity.4 test"), std::string::npos);
}

//!
//! @test Empty msg.
//!
TEST (Log, emptyMessageOnFile)
{
    std::string content;

    initLogger();
    system(std::string(std::string("echo -n "" > ") + UTWorkDirectory + "/utLog").c_str());
    LOG_(spcbttl::commun::tool::log::IN_FILE, plog::warning) << "";
    content = readFile(std::string(UTWorkDirectory) + "/utLog");
    EXPECT_FALSE(content.empty());
}

//!
//! @test False severity.
//!
TEST (Log, falseSeverityOnFile)
{
    std::string content;

    initLogger();
    system(std::string(std::string("echo -n "" > ") + UTWorkDirectory + "/utLog").c_str());
    LOG_(spcbttl::commun::tool::log::IN_FILE, static_cast<plog::Severity>(845)) << "falseSeverityOnFile";
    content = readFile(std::string(UTWorkDirectory) + "/utLog");
    EXPECT_TRUE(content.empty());
}
