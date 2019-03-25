//
// Created by grosso_a on 26/11/18.
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
//! @test Try to launch game with invalid player.
//!
TEST (LaunchGame, Player_Invalid)
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
    spcbttl::server::engine::RoomManager<1, 5>    rmm;
    //Test1 authenticate with id 0
    packet1.setHeader(spcbttl::commun::net::req::AUTHENTICATE_REQ, 0);
    packet1.mPacketBody = std::make_shared<spcbttl::commun::net::req::SAuthenticateReq>(socket);
    std::dynamic_pointer_cast<spcbttl::commun::net::req::SAuthenticateReq>(packet1.mPacketBody)->setPlayerName("Test1");
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet1));
    //user_id 0 create Room 0
    packet2.setHeader(spcbttl::commun::net::req::CREATE_ROOM_REQ, 0);
    packet2.mPacketBody = std::make_shared<spcbttl::commun::net::req::CreateRoomReq>();
    std::dynamic_pointer_cast<spcbttl::commun::net::req::CreateRoomReq>(packet2.mPacketBody)->setRoomName(std::string("Room 0"));
    std::dynamic_pointer_cast<spcbttl::commun::net::req::CreateRoomReq>(packet2.mPacketBody)->setIsViewerAllow(true);
    std::dynamic_pointer_cast<spcbttl::commun::net::req::CreateRoomReq>(packet2.mPacketBody)->setLimitType(spcbttl::commun::engine::TimeLimit::NO_LIMIT);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet2));
    //user_id 0 wiew Room 0
    packet3.setHeader(spcbttl::commun::net::req::VIEW_ROOM_REQ, 0);
    packet3.mPacketBody = std::make_shared<spcbttl::commun::net::req::ViewRoomReq>();
    std::dynamic_pointer_cast<spcbttl::commun::net::req::ViewRoomReq>(packet3.mPacketBody)->setRoomName(std::string("Room 0"));
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet3));
    //user_id 0 launch_game
    packet4.setHeader(spcbttl::commun::net::req::LAUNCH_GAME_REQ, 0);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet4));
    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStdout.find("RoomManager: authenticate") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticated with id 0 .") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: create_room name:Room 0 allow_viewers:1 time_limit:3") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: view_room name:Room 0 player:0") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: command id:12 is redirected to room.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Room: launch_game") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Room: launch_game Failed. Player invalid.") != std::string::npos);
}

//!
//! @test Try to launch game with only one player joined
//!
TEST (LaunchGame, Missing_Player)
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
    spcbttl::server::engine::RoomManager<1, 5>    rmm;
    //Test1 authenticate with id 0
    packet1.setHeader(spcbttl::commun::net::req::AUTHENTICATE_REQ, 0);
    packet1.mPacketBody = std::make_shared<spcbttl::commun::net::req::SAuthenticateReq>(socket);
    std::dynamic_pointer_cast<spcbttl::commun::net::req::SAuthenticateReq>(packet1.mPacketBody)->setPlayerName("Test1");
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet1));
    //user_id 0 create Room 0
    packet2.setHeader(spcbttl::commun::net::req::CREATE_ROOM_REQ, 0);
    packet2.mPacketBody = std::make_shared<spcbttl::commun::net::req::CreateRoomReq>();
    std::dynamic_pointer_cast<spcbttl::commun::net::req::CreateRoomReq>(packet2.mPacketBody)->setRoomName(std::string("Room 0"));
    std::dynamic_pointer_cast<spcbttl::commun::net::req::CreateRoomReq>(packet2.mPacketBody)->setIsViewerAllow(true);
    std::dynamic_pointer_cast<spcbttl::commun::net::req::CreateRoomReq>(packet2.mPacketBody)->setLimitType(spcbttl::commun::engine::TimeLimit::NO_LIMIT);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet2));
    //user_id 0 join Room 0
    packet3.setHeader(spcbttl::commun::net::req::JOIN_ROOM_REQ, 0);
    packet3.mPacketBody = std::make_shared<spcbttl::commun::net::req::JoinRoomReq>();
    std::dynamic_pointer_cast<spcbttl::commun::net::req::JoinRoomReq>(packet3.mPacketBody)->setRoomName(std::string("Room 0"));
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet3));
    //user_id 0 launch_game
    packet4.setHeader(spcbttl::commun::net::req::LAUNCH_GAME_REQ, 0);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet4));
    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStdout.find("RoomManager: authenticate") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticated with id 0 .") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: create_room name:Room 0 allow_viewers:1 time_limit:3") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: join_room name:Room 0 player:0") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: command id:12 is redirected to room.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Room: launch_game") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Room: launch_game Failed. Missing player.") != std::string::npos);
}


//!
//! @test Launch game with two player
//!
TEST (LaunchGame, Game_Launched)
{
    std::string                     outStdout;
    std::string                     outStderr;
    spcbttl::commun::net::Packet    packet1;
    spcbttl::commun::net::Packet    packet2;
    spcbttl::commun::net::Packet    packet3;
    spcbttl::commun::net::Packet    packet4;
    spcbttl::commun::net::Packet    packet5;
    spcbttl::commun::net::Packet    packet6;
    spcbttl::commun::net::Packet    packet7;
    boost::asio::io_service         service;
    sckcpp::tcp::ClientSocket       socket(service);


    initLogger();
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();
    spcbttl::server::engine::RoomManager<1, 5>    rmm;
    //Test1 authenticate with id 0
    packet1.setHeader(spcbttl::commun::net::req::AUTHENTICATE_REQ, 0);
    packet1.mPacketBody = std::make_shared<spcbttl::commun::net::req::SAuthenticateReq>(socket);
    std::dynamic_pointer_cast<spcbttl::commun::net::req::SAuthenticateReq>(packet1.mPacketBody)->setPlayerName("Test1");
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet1));
    //Test2 authenticate with id 1
    packet2.setHeader(spcbttl::commun::net::req::AUTHENTICATE_REQ, 0);
    packet2.mPacketBody = std::make_shared<spcbttl::commun::net::req::SAuthenticateReq>(socket);
    std::dynamic_pointer_cast<spcbttl::commun::net::req::SAuthenticateReq>(packet1.mPacketBody)->setPlayerName("Test2");
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet2));
    //user_id 0 create Room 0
    packet3.setHeader(spcbttl::commun::net::req::CREATE_ROOM_REQ, 0);
    packet3.mPacketBody = std::make_shared<spcbttl::commun::net::req::CreateRoomReq>();
    std::dynamic_pointer_cast<spcbttl::commun::net::req::CreateRoomReq>(packet3.mPacketBody)->setRoomName(std::string("Room 0"));
    std::dynamic_pointer_cast<spcbttl::commun::net::req::CreateRoomReq>(packet3.mPacketBody)->setIsViewerAllow(true);
    std::dynamic_pointer_cast<spcbttl::commun::net::req::CreateRoomReq>(packet3.mPacketBody)->setLimitType(spcbttl::commun::engine::TimeLimit::NO_LIMIT);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet3));
    //user_id 0 join Room 0
    packet4.setHeader(spcbttl::commun::net::req::JOIN_ROOM_REQ, 0);
    packet4.mPacketBody = std::make_shared<spcbttl::commun::net::req::JoinRoomReq>();
    std::dynamic_pointer_cast<spcbttl::commun::net::req::JoinRoomReq>(packet4.mPacketBody)->setRoomName(std::string("Room 0"));
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet4));
    //user_id 1 join Room 0
    packet5.setHeader(spcbttl::commun::net::req::JOIN_ROOM_REQ, 1);
    packet5.mPacketBody = std::make_shared<spcbttl::commun::net::req::JoinRoomReq>();
    std::dynamic_pointer_cast<spcbttl::commun::net::req::JoinRoomReq>(packet5.mPacketBody)->setRoomName(std::string("Room 0"));
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet5));
    //user_id 0 launch_game
    packet6.setHeader(spcbttl::commun::net::req::LAUNCH_GAME_REQ, 0);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet6));
    //user_id 0 launch_game
    packet7.setHeader(spcbttl::commun::net::req::LAUNCH_GAME_REQ, 1);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet7));
    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStdout.find("RoomManager: authenticate") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticated with id 0 .") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticate") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticated with id 1 .") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: create_room name:Room 0 allow_viewers:1 time_limit:3") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: join_room name:Room 0 player:0") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: join_room name:Room 0 player:1") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: command id:12 is redirected to room.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Room: launch_game") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Room: launch_game. Player 0 is ready. Waiting second player.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: command id:12 is redirected to room.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Room: launch_game") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Room: launch_game. Game launched.") != std::string::npos);
}

//!
//! @test Try launch game already launched
//!
TEST (LaunchGame, Already_Running)
{
    std::string                     outStdout;
    std::string                     outStderr;
    spcbttl::commun::net::Packet    packet1;
    spcbttl::commun::net::Packet    packet2;
    spcbttl::commun::net::Packet    packet3;
    spcbttl::commun::net::Packet    packet4;
    spcbttl::commun::net::Packet    packet5;
    spcbttl::commun::net::Packet    packet6;
    spcbttl::commun::net::Packet    packet7;
    spcbttl::commun::net::Packet    packet8;
    boost::asio::io_service         service;
    sckcpp::tcp::ClientSocket       socket(service);


    initLogger();
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();
    spcbttl::server::engine::RoomManager<1, 5>    rmm;
    //Test1 authenticate with id 0
    packet1.setHeader(spcbttl::commun::net::req::AUTHENTICATE_REQ, 0);
    packet1.mPacketBody = std::make_shared<spcbttl::commun::net::req::SAuthenticateReq>(socket);
    std::dynamic_pointer_cast<spcbttl::commun::net::req::SAuthenticateReq>(packet1.mPacketBody)->setPlayerName("Test1");
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet1));
    //Test2 authenticate with id 1
    packet2.setHeader(spcbttl::commun::net::req::AUTHENTICATE_REQ, 0);
    packet2.mPacketBody = std::make_shared<spcbttl::commun::net::req::SAuthenticateReq>(socket);
    std::dynamic_pointer_cast<spcbttl::commun::net::req::SAuthenticateReq>(packet1.mPacketBody)->setPlayerName("Test2");
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet2));
    //user_id 0 create Room 0
    packet3.setHeader(spcbttl::commun::net::req::CREATE_ROOM_REQ, 0);
    packet3.mPacketBody = std::make_shared<spcbttl::commun::net::req::CreateRoomReq>();
    std::dynamic_pointer_cast<spcbttl::commun::net::req::CreateRoomReq>(packet3.mPacketBody)->setRoomName(std::string("Room 0"));
    std::dynamic_pointer_cast<spcbttl::commun::net::req::CreateRoomReq>(packet3.mPacketBody)->setIsViewerAllow(true);
    std::dynamic_pointer_cast<spcbttl::commun::net::req::CreateRoomReq>(packet3.mPacketBody)->setLimitType(spcbttl::commun::engine::TimeLimit::NO_LIMIT);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet3));
    //user_id 0 join Room 0
    packet4.setHeader(spcbttl::commun::net::req::JOIN_ROOM_REQ, 0);
    packet4.mPacketBody = std::make_shared<spcbttl::commun::net::req::JoinRoomReq>();
    std::dynamic_pointer_cast<spcbttl::commun::net::req::JoinRoomReq>(packet4.mPacketBody)->setRoomName(std::string("Room 0"));
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet4));
    //user_id 1 join Room 0
    packet5.setHeader(spcbttl::commun::net::req::JOIN_ROOM_REQ, 1);
    packet5.mPacketBody = std::make_shared<spcbttl::commun::net::req::JoinRoomReq>();
    std::dynamic_pointer_cast<spcbttl::commun::net::req::JoinRoomReq>(packet5.mPacketBody)->setRoomName(std::string("Room 0"));
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet5));
    //user_id 0 launch_game
    packet6.setHeader(spcbttl::commun::net::req::LAUNCH_GAME_REQ, 0);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet6));
    //user_id 1 launch_game
    packet7.setHeader(spcbttl::commun::net::req::LAUNCH_GAME_REQ, 1);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet7));
    //user_id 0 launch_game
    packet8.setHeader(spcbttl::commun::net::req::LAUNCH_GAME_REQ, 1);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet8));
    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStdout.find("RoomManager: authenticate") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticated with id 0 .") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticate") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticated with id 1 .") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: create_room name:Room 0 allow_viewers:1 time_limit:3") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: join_room name:Room 0 player:0") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: join_room name:Room 0 player:1") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: command id:12 is redirected to room.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Room: launch_game") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Room: launch_game. Player 0 is ready. Waiting second player.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: command id:12 is redirected to room.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Room: launch_game") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Room: launch_game. Game launched.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: command id:12 is redirected to room.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Room: launch_game") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Room: launch_game Failed. Game already running.") != std::string::npos);
}