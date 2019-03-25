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
//! @test Check send chat message in general with Player not authenticated
//!
TEST (SendChatMsgTest, General_No_Auth)
{
    std::string                     outStdout;
    std::string                     outStderr;
    spcbttl::commun::net::Packet    packet;
    boost::asio::io_service         service;
    sckcpp::tcp::ClientSocket       socket(service);


    initLogger();
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();
    spcbttl::server::engine::RoomManager<1, 2>    rmm;
    //Send message 'Hello World !' with id 0 in general
    packet.setHeader(spcbttl::commun::net::req::SEND_CHAT_MSG_REQ, 0);
    packet.mPacketBody = std::make_shared<spcbttl::commun::net::req::SendChatMsgReq>();
    std::dynamic_pointer_cast<spcbttl::commun::net::req::SendChatMsgReq>(packet.mPacketBody)->setChanelType(spcbttl::commun::engine::GENERAL);
    std::dynamic_pointer_cast<spcbttl::commun::net::req::SendChatMsgReq>(packet.mPacketBody)->setMessage(std::string("Hello World !"));
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet));

    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStdout.find("RoomManager: send_message") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: send_chat_msg Failed. Player not authenticated.") != std::string::npos);
    EXPECT_TRUE(outStderr.empty());
}

//!
//! @test Check send chat message in general
//!
TEST (SendChatMsgTest, General)
{
    std::string                     outStdout;
    std::string                     outStderr;
    spcbttl::commun::net::Packet    packet1;
    spcbttl::commun::net::Packet    packet2;
    spcbttl::commun::net::Packet    packet3;
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
    //Send message 'Hello World !' with id 0 in general
    packet3.setHeader(spcbttl::commun::net::req::SEND_CHAT_MSG_REQ, 0);
    packet3.mPacketBody = std::make_shared<spcbttl::commun::net::req::SendChatMsgReq>();
    std::dynamic_pointer_cast<spcbttl::commun::net::req::SendChatMsgReq>(packet3.mPacketBody)->setChanelType(spcbttl::commun::engine::GENERAL);
    std::dynamic_pointer_cast<spcbttl::commun::net::req::SendChatMsgReq>(packet3.mPacketBody)->setMessage(std::string("Hello World !"));
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet3));
    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStdout.find("RoomManager: authenticate") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticated with id 0 .") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticate") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticated with id 1 .") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: send_message") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: send_chat_message player :0 send message :Hello World !") != std::string::npos);
    EXPECT_TRUE(outStderr.empty());
}


//!
//! @test Check send chat message in room with No room Joined
//!
TEST (SendChatMsgTest, Room_No_Room)
{
    std::string                     outStdout;
    std::string                     outStderr;
    spcbttl::commun::net::Packet    packet1;
    spcbttl::commun::net::Packet    packet2;
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
    //Send message 'Hello World !' with id 0 in general
    packet2.setHeader(spcbttl::commun::net::req::SEND_CHAT_MSG_REQ, 0);
    packet2.mPacketBody = std::make_shared<spcbttl::commun::net::req::SendChatMsgReq>();
    std::dynamic_pointer_cast<spcbttl::commun::net::req::SendChatMsgReq>(packet2.mPacketBody)->setChanelType(spcbttl::commun::engine::ChanelType::GAME);
    std::dynamic_pointer_cast<spcbttl::commun::net::req::SendChatMsgReq>(packet2.mPacketBody)->setMessage(std::string("Hello World !"));
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet2));
    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStdout.find("RoomManager: authenticate") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticated with id 0 .") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: send_message") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: Player not in room") != std::string::npos);
    EXPECT_TRUE(outStderr.empty());
}


//!
//! @test Check send chat message in room
//!
TEST (SendChatMsgTest, Room)
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
    //user_id 0 try join Room 0
    packet5.setHeader(spcbttl::commun::net::req::JOIN_ROOM_REQ, 0);
    packet5.mPacketBody = std::make_shared<spcbttl::commun::net::req::JoinRoomReq>();
    std::dynamic_pointer_cast<spcbttl::commun::net::req::JoinRoomReq>(packet5.mPacketBody)->setRoomName(std::string("Room 0"));
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet5));
    //user_id 0 try join Room 0
    packet6.setHeader(spcbttl::commun::net::req::JOIN_ROOM_REQ, 1);
    packet6.mPacketBody = std::make_shared<spcbttl::commun::net::req::JoinRoomReq>();
    std::dynamic_pointer_cast<spcbttl::commun::net::req::JoinRoomReq>(packet6.mPacketBody)->setRoomName(std::string("Room 0"));
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet6));
    //user_id 2 try view Room 0
    packet7.setHeader(spcbttl::commun::net::req::VIEW_ROOM_REQ, 2);
    packet7.mPacketBody = std::make_shared<spcbttl::commun::net::req::ViewRoomReq>();
    std::dynamic_pointer_cast<spcbttl::commun::net::req::ViewRoomReq>(packet7.mPacketBody)->setRoomName(std::string("Room 0"));
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet7));
    //Send message 'Hello World !' with id 0 in general
    packet8.setHeader(spcbttl::commun::net::req::SEND_CHAT_MSG_REQ, 0);
    packet8.mPacketBody = std::make_shared<spcbttl::commun::net::req::SendChatMsgReq>();
    std::dynamic_pointer_cast<spcbttl::commun::net::req::SendChatMsgReq>(packet8.mPacketBody)->setChanelType(spcbttl::commun::engine::ChanelType::GAME);
    std::dynamic_pointer_cast<spcbttl::commun::net::req::SendChatMsgReq>(packet8.mPacketBody)->setMessage(std::string("Hello World !"));
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet8));
    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStdout.find("RoomManager: authenticate") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticated with id 0 .") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticate") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticated with id 1 .") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticate") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticated with id 2 .") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: create_room name:Room 0 allow_viewers:1 time_limit:3") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: join_room name:Room 0 player:0") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: join_room name:Room 0 player:1") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: view_room name:Room 0 player:2") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: send_message") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Room: send_message") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Room: send_chat_message player :1 send message :Hello World !") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Room: send_chat_message player :2 send message :Hello World !") != std::string::npos);
    EXPECT_TRUE(outStderr.empty());
}