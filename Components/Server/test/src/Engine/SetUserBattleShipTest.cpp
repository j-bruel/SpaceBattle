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
//! @test Try set ship with invalid player
//!
TEST (SetUserBattleship, Invalid_Player)
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
    spcbttl::commun::net::Packet    packet9;
    spcbttl::commun::net::Packet    packet10;
    spcbttl::commun::net::Packet    packet11;
    boost::asio::io_service         service;
    sckcpp::tcp::ClientSocket       socket(service);
    spcbttl::commun::engine::Ships  ships;


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
    std::dynamic_pointer_cast<spcbttl::commun::net::req::SAuthenticateReq>(packet2.mPacketBody)->setPlayerName("Test2");
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet2));
    //Test3 authenticate with id 2
    packet3.setHeader(spcbttl::commun::net::req::AUTHENTICATE_REQ, 0);
    packet3.mPacketBody = std::make_shared<spcbttl::commun::net::req::SAuthenticateReq>(socket);
    std::dynamic_pointer_cast<spcbttl::commun::net::req::SAuthenticateReq>(packet3.mPacketBody)->setPlayerName("Test3");
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet3));
    //user_id 0 create Room 0
    packet4.setHeader(spcbttl::commun::net::req::CREATE_ROOM_REQ, 0);
    packet4.mPacketBody = std::make_shared<spcbttl::commun::net::req::CreateRoomReq>();
    std::dynamic_pointer_cast<spcbttl::commun::net::req::CreateRoomReq>(packet4.mPacketBody)->setRoomName(std::string("Room 0"));
    std::dynamic_pointer_cast<spcbttl::commun::net::req::CreateRoomReq>(packet4.mPacketBody)->setIsViewerAllow(true);
    std::dynamic_pointer_cast<spcbttl::commun::net::req::CreateRoomReq>(packet4.mPacketBody)->setLimitType(spcbttl::commun::engine::TimeLimit::NO_LIMIT);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet4));
    //user_id 0 join Room 0
    packet6.setHeader(spcbttl::commun::net::req::JOIN_ROOM_REQ, 0);
    packet6.mPacketBody = std::make_shared<spcbttl::commun::net::req::JoinRoomReq>();
    std::dynamic_pointer_cast<spcbttl::commun::net::req::JoinRoomReq>(packet6.mPacketBody)->setRoomName(std::string("Room 0"));
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet6));
    //user_id 2 view Room 0
    packet7.setHeader(spcbttl::commun::net::req::VIEW_ROOM_REQ, 2);
    packet7.mPacketBody = std::make_shared<spcbttl::commun::net::req::ViewRoomReq>();
    std::dynamic_pointer_cast<spcbttl::commun::net::req::ViewRoomReq>(packet7.mPacketBody)->setRoomName(std::string("Room 0"));
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet7));
    //user_id 1 join Room 0
    packet8.setHeader(spcbttl::commun::net::req::JOIN_ROOM_REQ, 1);
    packet8.mPacketBody = std::make_shared<spcbttl::commun::net::req::JoinRoomReq>();
    std::dynamic_pointer_cast<spcbttl::commun::net::req::JoinRoomReq>(packet8.mPacketBody)->setRoomName(std::string("Room 0"));
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet8));
    //user_id 0 launch_game
    packet9.setHeader(spcbttl::commun::net::req::LAUNCH_GAME_REQ, 0);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet9));
    //user_id 0 launch_game
    packet10.setHeader(spcbttl::commun::net::req::LAUNCH_GAME_REQ, 1);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet10));
    //Set battleship with invalid user
    packet11.setHeader(spcbttl::commun::net::req::SET_USER_BATTLESHIP_REQ, 2);
    packet11.mPacketBody = std::make_shared<spcbttl::commun::net::req::SetUserBattleshipReq>();
    ships.mDestroyer = 10;
    ships.mSubmarine = {10, 11};
    ships.mCruiser1 = {10, 11, 14};
    ships.mCruiser2 = {19, 20, 21};
    ships.mBattleship = {0,1,2,3};
    ships.mCarrier = {4,5,6,7,8};
    std::dynamic_pointer_cast<spcbttl::commun::net::req::SetUserBattleshipReq>(packet11.mPacketBody)->setShips(ships);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet11));
    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStdout.find("RoomManager: authenticate") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticated with id 0 .") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticate") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticated with id 1 .") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: create_room name:Room 0 allow_viewers:1 time_limit:3") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: join_room name:Room 0 player:0") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: join_room name:Room 0 player:1") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: view_room name:Room 0 player:2") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: command id:12 is redirected to room.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Room: launch_game") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Room: launch_game. Player 0 is ready. Waiting second player.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: command id:12 is redirected to room.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Room: launch_game") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Room: launch_game. Game launched.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: command id:20 is redirected to room.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Room: set_user_battleship") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Room: set_user_battleship Failed. Player invalid.") != std::string::npos);
    EXPECT_TRUE(outStderr.empty());
}

//!
//! @test Try set ship with discontinuous position.
//!
TEST (SetUserBattleship, InvalidPosition_Discontinuous)
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
    spcbttl::commun::engine::Ships  ships;


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
    //Set battleship with invalid position
    packet8.setHeader(spcbttl::commun::net::req::SET_USER_BATTLESHIP_REQ, 0);
    packet8.mPacketBody = std::make_shared<spcbttl::commun::net::req::SetUserBattleshipReq>();
    ships.mDestroyer = 10;
    ships.mSubmarine = {13, 14};
    ships.mCruiser1 = {37, 57, 67};
    ships.mCruiser2 = {41, 42, 43};
    ships.mBattleship = {19,29,39,49};
    ships.mCarrier = {70,71,72,73,74};
    std::dynamic_pointer_cast<spcbttl::commun::net::req::SetUserBattleshipReq>(packet8.mPacketBody)->setShips(ships);
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
    EXPECT_TRUE(outStdout.find("RoomManager: command id:20 is redirected to room.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Room: set_user_battleship") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Room: set_user_battleship Failed. Ship position is invalid.") != std::string::npos);
    EXPECT_TRUE(outStderr.empty());
}

//!
//! @test Try set ship with diagonal position.
//!
TEST (SetUserBattleship, InvalidPosition_Diagonal)
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
    spcbttl::commun::engine::Ships  ships;


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
    //Set battleship with invalid position
    packet8.setHeader(spcbttl::commun::net::req::SET_USER_BATTLESHIP_REQ, 0);
    packet8.mPacketBody = std::make_shared<spcbttl::commun::net::req::SetUserBattleshipReq>();
    ships.mDestroyer = 60;
    ships.mSubmarine = {11, 12};
    ships.mCruiser1 = {31, 42, 53};
    ships.mCruiser2 = {25, 35, 45};
    ships.mBattleship = {81,82,83,84};
    ships.mCarrier = {4,5,6,7,8};
    std::dynamic_pointer_cast<spcbttl::commun::net::req::SetUserBattleshipReq>(packet8.mPacketBody)->setShips(ships);
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
    EXPECT_TRUE(outStdout.find("RoomManager: command id:20 is redirected to room.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Room: set_user_battleship") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Room: set_user_battleship Failed. Ship position is invalid.") != std::string::npos);
    EXPECT_TRUE(outStderr.empty());
}

//!
//! @test Try set ship outer of grid.
//!
TEST (SetUserBattleship, InvalidPosition_Out)
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
    spcbttl::commun::engine::Ships  ships;


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
    //Set battleship with invalid position
    packet8.setHeader(spcbttl::commun::net::req::SET_USER_BATTLESHIP_REQ, 0);
    packet8.mPacketBody = std::make_shared<spcbttl::commun::net::req::SetUserBattleshipReq>();
    ships.mDestroyer = 11;
    ships.mSubmarine = {80, 103};
    ships.mCruiser1 = {15, 25, 35};
    ships.mCruiser2 = {16, 26, 36};
    ships.mBattleship = {51,52,53,54};
    ships.mCarrier = {74,75,76,77,78};
    std::dynamic_pointer_cast<spcbttl::commun::net::req::SetUserBattleshipReq>(packet8.mPacketBody)->setShips(ships);
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
    EXPECT_TRUE(outStdout.find("RoomManager: command id:20 is redirected to room.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Room: set_user_battleship") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Room: set_user_battleship Failed. Ship position is invalid.") != std::string::npos);
    EXPECT_TRUE(outStderr.empty());
    EXPECT_TRUE(outStderr.empty());
}

//!
//! @test Set valid ships.
//!
TEST (SetUserBattleship, ValidShips)
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
    spcbttl::commun::engine::Ships  ships;


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
    //Set battleship with invalid position
    packet8.setHeader(spcbttl::commun::net::req::SET_USER_BATTLESHIP_REQ, 0);
    packet8.mPacketBody = std::make_shared<spcbttl::commun::net::req::SetUserBattleshipReq>();
    ships.mDestroyer = 11;
    ships.mSubmarine = {80, 81};
    ships.mCruiser1 = {15, 25, 35};
    ships.mCruiser2 = {16, 26, 36};
    ships.mBattleship = {51,52,53,54};
    ships.mCarrier = {74,75,76,77,78};
    std::dynamic_pointer_cast<spcbttl::commun::net::req::SetUserBattleshipReq>(packet8.mPacketBody)->setShips(ships);
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
    EXPECT_TRUE(outStdout.find("RoomManager: command id:20 is redirected to room.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Room: set_user_battleship") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Room: set_user_battleship.\n"\
        " Ship_1_1 position is size:1 { 11, }\n"\
        " Ship_1_2 position is size:2 { 80, 81, }\n"\
        " Ship_1_3 position is size:3 { 15, 25, 35, }\n"\
        " Ship_2_3 position is size:3 { 16, 26, 36, }\n"\
        " Ship_1_4 position is size:4 { 51, 52, 53, 54, }\n"\
        " Ship_1_5 position is size:5 { 74, 75, 76, 77, 78, }") != std::string::npos);
    EXPECT_TRUE(outStderr.empty());
    EXPECT_TRUE(outStderr.empty());
}
