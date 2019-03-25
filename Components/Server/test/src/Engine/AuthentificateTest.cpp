//
// Created by grosso_a on 25/11/18.
//

# include "Commun/UTWorkDirectory.hpp"
# include "Commun/Tools/Log/Initializer.hpp"
# include <plog/Log.h>
# include <fstream>
# include <gtest/gtest.h>
# include <Engine/RoomManager/RoomManager.hpp>
# include <thread>
# include "Engine/Logger.hpp"

//!
//! @test Check authenticate two users
//!
TEST (Authenticate, Two_User)
{
    std::string                     outStdout;
    std::string                     outStderr;
    spcbttl::commun::net::Packet    packet1;
    spcbttl::commun::net::Packet    packet2;
    spcbttl::commun::net::Packet    packet3;
    spcbttl::commun::net::Packet    packet4;
    boost::asio::io_service         service;
    sckcpp::tcp::ClientSocket       socket(service);


    initLogger();
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();
    spcbttl::server::engine::RoomManager<1, 2>    rmm;
    //Test1 authenticate with id 0
    packet1.setHeader(spcbttl::commun::net::req::AUTHENTICATE_REQ, 0);
    packet1.mPacketBody = std::make_shared<spcbttl::commun::net::req::SAuthenticateReq>(socket);
    std::dynamic_pointer_cast<spcbttl::commun::net::req::SAuthenticateReq>(packet1.mPacketBody)->setPlayerName("Test1");
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet1));
    //Test2 authenticate with id 1
    packet2.setHeader(spcbttl::commun::net::req::AUTHENTICATE_REQ, 0);
    packet2.mPacketBody = std::make_shared<spcbttl::commun::net::req::SAuthenticateReq>(socket);
    std::dynamic_pointer_cast<spcbttl::commun::net::req::SAuthenticateReq>(packet2.mPacketBody)->setPlayerName("Test2");
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet2));

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStdout.find("RoomManager: authenticate") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticated with id 0 .") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticate") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticated with id 1 .") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticate") != std::string::npos);
    EXPECT_TRUE(outStderr.empty());
}

//!
//! @test Check number user limit
//!
TEST (Authenticate, Max_User)
{
    std::string                     outStdout;
    std::string                     outStderr;
    spcbttl::commun::net::Packet    packet1;
    spcbttl::commun::net::Packet    packet2;
    spcbttl::commun::net::Packet    packet3;
    spcbttl::commun::net::Packet    packet4;
    boost::asio::io_service         service;
    sckcpp::tcp::ClientSocket       socket(service);


    initLogger();
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();
    spcbttl::server::engine::RoomManager<1, 2>    rmm;
    //Test1 authenticate with id 0
    packet1.setHeader(spcbttl::commun::net::req::AUTHENTICATE_REQ, 0);
    packet1.mPacketBody = std::make_shared<spcbttl::commun::net::req::SAuthenticateReq>(socket);
    std::dynamic_pointer_cast<spcbttl::commun::net::req::SAuthenticateReq>(packet1.mPacketBody)->setPlayerName("Test1");
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet1));
    //Test2 authenticate with id 1
    packet2.setHeader(spcbttl::commun::net::req::AUTHENTICATE_REQ, 0);
    packet2.mPacketBody = std::make_shared<spcbttl::commun::net::req::SAuthenticateReq>(socket);
    std::dynamic_pointer_cast<spcbttl::commun::net::req::SAuthenticateReq>(packet2.mPacketBody)->setPlayerName("Test2");
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet2));
    //Test3 authenticate with id 2
    packet3.setHeader(spcbttl::commun::net::req::AUTHENTICATE_REQ, 0);
    packet3.mPacketBody = std::make_shared<spcbttl::commun::net::req::SAuthenticateReq>(socket);
    std::dynamic_pointer_cast<spcbttl::commun::net::req::SAuthenticateReq>(packet3.mPacketBody)->setPlayerName("Test3");
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet3));

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStdout.find("RoomManager: authenticate") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticated with id 0 .") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticate") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticated with id 1 .") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticate") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticate Failed. No user Available") != std::string::npos);
    EXPECT_TRUE(outStderr.empty());
}

//!
//! @test Check authenticate user already authenticated
//!
TEST (Authenticate, User_Already_Exist)
{
    std::string                     outStdout;
    std::string                     outStderr;
    spcbttl::commun::net::Packet    packet1;
    spcbttl::commun::net::Packet    packet2;
    spcbttl::commun::net::Packet    packet3;
    spcbttl::commun::net::Packet    packet4;
    boost::asio::io_service         service;
    sckcpp::tcp::ClientSocket       socket(service);


    initLogger();
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();
    spcbttl::server::engine::RoomManager<1, 2>    rmm;
    //Test1 authenticate with id 0
    packet1.setHeader(spcbttl::commun::net::req::AUTHENTICATE_REQ, 0);
    packet1.mPacketBody = std::make_shared<spcbttl::commun::net::req::SAuthenticateReq>(socket);
    std::dynamic_pointer_cast<spcbttl::commun::net::req::SAuthenticateReq>(packet1.mPacketBody)->setPlayerName("Test1");
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet1));
    //Test1 authenticate with id 0
    packet2.setHeader(spcbttl::commun::net::req::AUTHENTICATE_REQ, 0);
    packet2.mPacketBody = std::make_shared<spcbttl::commun::net::req::SAuthenticateReq>(socket);
    std::dynamic_pointer_cast<spcbttl::commun::net::req::SAuthenticateReq>(packet2.mPacketBody)->setPlayerName("Test1");
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet2));

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStdout.find("RoomManager: authenticate") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticated with id 0 .") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticate") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticate Failed. User name already exist.") != std::string::npos);
    EXPECT_TRUE(outStderr.empty());
}
