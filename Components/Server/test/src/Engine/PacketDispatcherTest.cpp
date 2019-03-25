//!
//! @file ship.cpp
//! @author agrosso
//! @date 07/11/12
//!

# include "Commun/UTWorkDirectory.hpp"
# include "Commun/Tools/Log/Initializer.hpp"
# include <plog/Log.h>
# include <fstream>
# include <gtest/gtest.h>
# include <Engine/PacketDispatcher.hpp>
# include <Engine/RoomManager/RoomManager.hpp>
# include <Engine/Room/Room.hpp>
# include "Engine/Logger.hpp"

//!
//! @test Check Stalckers (threads) creation and destruction
//!
TEST (PacketDispatcher, Stalckers)
{
    std::string outStdout;
    std::string outStderr;

    initLogger();
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();
    spcbttl::server::engine::PacketDispatcher::TRoomManager rm;
    spcbttl::server::engine::PacketDispatcher::TPacketQueue &queue = spcbttl::server::engine::PacketDispatcher::TPacketQueue::Instance();
    spcbttl::server::engine::PacketDispatcher               dispatcher(queue, rm, 10);
    ASSERT_TRUE(queue.empty());
    dispatcher.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    dispatcher.stop();
    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStdout.find("Start PacketDispatcher with 10 threads.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 0 start.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 1 start.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 2 start.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 3 start.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 4 start.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 5 start.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 6 start.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 7 start.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 8 start.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 9 start.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 0 stop.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 1 stop.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 2 stop.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 3 stop.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 4 stop.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 5 stop.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 6 stop.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 7 stop.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 8 stop.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 9 stop.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stop PacketDispatcher.") != std::string::npos);
    EXPECT_TRUE(outStderr.empty());
}




//!
//! @test Check Packet with invalid command
//!
TEST (PacketDispatcher, InvalidPacket)
{
    std::string                     outStdout;
    std::string                     outStderr;
    spcbttl::commun::net::Packet    packet1;
    spcbttl::commun::net::Packet    packet2;

    packet1.setHeader((spcbttl::commun::net::req::Type)2, 0);
    packet2.setHeader((spcbttl::commun::net::req::Type)40, 0);
    initLogger();
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();
    spcbttl::server::engine::PacketDispatcher::TRoomManager rm;
    spcbttl::server::engine::PacketDispatcher::TPacketQueue &queue = spcbttl::server::engine::PacketDispatcher::TPacketQueue::Instance();
    spcbttl::server::engine::PacketDispatcher               dispatcher(queue, rm, 10);
    ASSERT_TRUE(queue.empty());
    dispatcher.start();
    queue.push_back(std::make_shared<spcbttl::commun::net::Packet>(packet1));
    queue.push_back(std::make_shared<spcbttl::commun::net::Packet>(packet2));
    dispatcher.stop();
    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStdout.find("Start PacketDispatcher with 10 threads.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 0 start.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 1 start.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 2 start.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 3 start.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 4 start.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 5 start.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 6 start.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 7 start.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 8 start.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 9 start.") != std::string::npos);

    EXPECT_TRUE(outStdout.find("RoomManager: command id:2 is invalid.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: command id:40 is invalid.") != std::string::npos);


    EXPECT_TRUE(outStdout.find("Stalker 0 stop.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 1 stop.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 2 stop.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 3 stop.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 4 stop.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 5 stop.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 6 stop.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 7 stop.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 8 stop.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 9 stop.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stop PacketDispatcher.") != std::string::npos);
    EXPECT_TRUE(outStderr.empty());
}

//!
//! @test Check packet with valid command
//!
TEST (PacketDispatcher, ValidPacket)
{
    std::string outStdout;
    std::string outStderr;
    spcbttl::commun::net::Packet packet1;
    spcbttl::commun::net::Packet packet2;
    spcbttl::commun::net::Packet packet3;
    spcbttl::commun::net::Packet packet4;
    boost::asio::io_service      service;
    sckcpp::tcp::ClientSocket    socket(service);

    packet1.setHeader((spcbttl::commun::net::req::Type)1, 0);
    packet1.mPacketBody = std::make_shared<spcbttl::commun::net::req::SAuthenticateReq>(socket);
    std::dynamic_pointer_cast<spcbttl::commun::net::req::SAuthenticateReq>(packet1.mPacketBody)->setPlayerName("Test1");

    packet2.setHeader((spcbttl::commun::net::req::Type)3, 0);

    packet3.setHeader((spcbttl::commun::net::req::Type)1, 0);
    packet3.mPacketBody = std::make_shared<spcbttl::commun::net::req::SAuthenticateReq>(socket);
    std::dynamic_pointer_cast<spcbttl::commun::net::req::SAuthenticateReq>(packet3.mPacketBody)->setPlayerName("Test2");

    packet4.setHeader((spcbttl::commun::net::req::Type)3, 1);

    initLogger();
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();
    spcbttl::server::engine::PacketDispatcher::TRoomManager rm;
    spcbttl::server::engine::PacketDispatcher::TPacketQueue &queue = spcbttl::server::engine::PacketDispatcher::TPacketQueue::Instance();
    spcbttl::server::engine::PacketDispatcher               dispatcher(queue, rm, 10);
    ASSERT_TRUE(queue.empty());
    dispatcher.start();
    queue.push_back(std::make_shared<spcbttl::commun::net::Packet>(packet1));
    queue.push_back(std::make_shared<spcbttl::commun::net::Packet>(packet2));
    queue.push_back(std::make_shared<spcbttl::commun::net::Packet>(packet3));
    queue.push_back(std::make_shared<spcbttl::commun::net::Packet>(packet4));
    dispatcher.stop();
    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStdout.find("Start PacketDispatcher with 10 threads.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 0 start.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 1 start.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 2 start.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 3 start.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 4 start.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 5 start.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 6 start.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 7 start.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 8 start.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 9 start.") != std::string::npos);

    EXPECT_TRUE(outStdout.find("RoomManager: authenticate") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: get_room_list") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticate") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: get_room_list") != std::string::npos);


    EXPECT_TRUE(outStdout.find("Stalker 0 stop.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 1 stop.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 2 stop.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 3 stop.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 4 stop.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 5 stop.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 6 stop.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 7 stop.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 8 stop.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stalker 9 stop.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Stop PacketDispatcher.") != std::string::npos);
    EXPECT_TRUE(outStderr.empty());
}