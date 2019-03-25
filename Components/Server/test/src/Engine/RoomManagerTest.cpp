//
// Created by grosso_a on 13/11/18.
//


# include "Commun/UTWorkDirectory.hpp"
# include "Commun/Tools/Log/Initializer.hpp"
# include <plog/Log.h>
# include <fstream>
# include <gtest/gtest.h>
# include <Engine/RoomManager/RoomManager.hpp>
# include <thread>
#include <Engine/PacketDispatcher.hpp>
# include "Engine/Logger.hpp"

//!
//! @test Check object consructor
//!
TEST (RoomManager, Init)
{
    initLogger();
    spcbttl::server::engine::RoomManager<100, 50>    rmm;
}


//!
//! @test Detect un manager commands
//!
TEST (RoomManager, InvalidCommand)
{
    std::string                     outStdout;
    std::string                     outStderr;
    spcbttl::commun::net::Packet    packet1;
    spcbttl::commun::net::Packet    packet2;

    initLogger();
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();
    spcbttl::server::engine::RoomManager<100, 50>    rmm;

    packet1.setHeader((spcbttl::commun::net::req::Type)40, 0);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet1));
    packet2.setHeader((spcbttl::commun::net::req::Type)2, 0);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet2));
    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStdout.find("RoomManager: command id:40 is invalid.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: command id:2 is invalid.") != std::string::npos);
    EXPECT_TRUE(outStderr.empty());
}


//!
//! @test Check if player without keep alive is correctly destroyed.
//!
TEST (RoomManager, KeepAlive)
{
    std::string                     outStdout;
    std::string                     outStderr;
    spcbttl::commun::net::Packet    packet1;
    boost::asio::io_service         service;
    sckcpp::tcp::ClientSocket       socket(service);

    initLogger();
    spcbttl::server::engine::PacketDispatcher::TRoomManager rm;
    spcbttl::server::engine::PacketDispatcher::TPacketQueue &queue = spcbttl::server::engine::PacketDispatcher::TPacketQueue::Instance();
    spcbttl::server::engine::PacketDispatcher               dispatcher(queue, rm, 10);
    ASSERT_TRUE(queue.empty());

    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();
    //Test1 authenticate with id 0
    packet1.setHeader(spcbttl::commun::net::req::AUTHENTICATE_REQ, 0);
    packet1.mPacketBody = std::make_shared<spcbttl::commun::net::req::SAuthenticateReq>(socket);
    std::dynamic_pointer_cast<spcbttl::commun::net::req::SAuthenticateReq>(packet1.mPacketBody)->setPlayerName("Test1");
    dispatcher.start();
    queue.push_back(std::make_shared<spcbttl::commun::net::Packet>(packet1));
    std::this_thread::sleep_for(std::chrono::seconds(15));
    dispatcher.stop();
    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStdout.find("RoomManager: authenticate") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticated with id 0 .") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: player name:Test1 is dead.") != std::string::npos);
    EXPECT_TRUE(outStderr.empty());
}