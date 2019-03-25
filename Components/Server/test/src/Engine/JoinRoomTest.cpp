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
//! @test Try join room with user not authenticated
//!
TEST (JoinRoom, user_not_authenticated)
{
    std::string                                                     outStdout;
    std::string                                                     outStderr;
    spcbttl::commun::net::Packet                                    packet1;
    spcbttl::commun::net::Packet                                    packet2;
    spcbttl::commun::net::Packet                                    packet3;
    spcbttl::server::engine::RoomManager<1, 2>                      rmm;
    std::shared_ptr<spcbttl::commun::net::req::ViewRoomReq>         body_joinroom;
    std::shared_ptr<spcbttl::commun::net::req::CreateRoomReq>       body_createroom;
    std::shared_ptr<spcbttl::commun::net::req::SAuthenticateReq>    body_authenticate;
    boost::asio::io_service                                         service;
    sckcpp::tcp::ClientSocket                                       socket(service);

    initLogger();
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();
    body_createroom = std::make_shared<spcbttl::commun::net::req::CreateRoomReq>();
    body_authenticate = std::make_shared<spcbttl::commun::net::req::SAuthenticateReq>(socket);
    body_joinroom= std::make_shared<spcbttl::commun::net::req::ViewRoomReq>();
    //Asteb612 authenticate with id 0
    body_authenticate->setPlayerName(std::string("Asteb612"));
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody_auth = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_authenticate);
    packet1.set(spcbttl::commun::net::req::AUTHENTICATE_REQ, 0, tbody_auth);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet1));
    //user_id 0 create Room 0
    body_createroom->setRoomName(std::string("Room 0"));
    body_createroom->setIsViewerAllow(true);
    body_createroom->setLimitType(spcbttl::commun::engine::TimeLimit::NO_LIMIT);
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody_createroom = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_createroom);
    packet2.set(spcbttl::commun::net::req::CREATE_ROOM_REQ, 0, tbody_createroom);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet2));
    //user_id 1 try join Room 0
    body_joinroom->setRoomName(std::string("Room 0"));
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody_joinroom = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_joinroom);
    packet3.set(spcbttl::commun::net::req::JOIN_ROOM_REQ, 1, tbody_joinroom);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet3));

    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStdout.find("RoomManager: authenticate") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticated with id 0 .") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: create_room name:Room 0 allow_viewers:1 time_limit:3") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: join_room Failed. Player not authenticated.") != std::string::npos);
    EXPECT_TRUE(outStderr.empty());
}


//!
//! @test Try join room not exist
//!
TEST (JoinRoom, room_not_exist)
{
    std::string                                                     outStdout;
    std::string                                                     outStderr;
    spcbttl::commun::net::Packet                                    packet1;
    spcbttl::commun::net::Packet                                    packet2;
    spcbttl::server::engine::RoomManager<1, 2>                      rmm;
    std::shared_ptr<spcbttl::commun::net::req::JoinRoomReq>         body_joinroom;
    std::shared_ptr<spcbttl::commun::net::req::SAuthenticateReq>    body_authenticate;
    boost::asio::io_service                                         service;
    sckcpp::tcp::ClientSocket                                       socket(service);

    initLogger();
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();
    body_authenticate = std::make_shared<spcbttl::commun::net::req::SAuthenticateReq>(socket);
    body_joinroom= std::make_shared<spcbttl::commun::net::req::JoinRoomReq>();
    //Asteb612 authenticate with id 0
    body_authenticate->setPlayerName(std::string("Asteb612"));
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody_auth = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_authenticate);
    packet1.set(spcbttl::commun::net::req::AUTHENTICATE_REQ, 0, tbody_auth);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet1));
    //user_id 0 try join Room 0
    body_joinroom->setRoomName(std::string("Room 0"));
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody_joinroom = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_joinroom);
    packet2.set(spcbttl::commun::net::req::JOIN_ROOM_REQ, 0, tbody_joinroom);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet2));

    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStdout.find("RoomManager: authenticate") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticated with id 0 .") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: join_room Failed. Room not not exist.") != std::string::npos);
    EXPECT_TRUE(outStderr.empty());
}

//!
//! @test Join room
//!
TEST (JoinRoom, has_join_room)
{
    std::string                                                     outStdout;
    std::string                                                     outStderr;
    spcbttl::commun::net::Packet                                    packet1;
    spcbttl::commun::net::Packet                                    packet2;
    spcbttl::commun::net::Packet                                    packet3;
    spcbttl::server::engine::RoomManager<1, 2>                      rmm;
    std::shared_ptr<spcbttl::commun::net::req::JoinRoomReq>         body_joinroom;
    std::shared_ptr<spcbttl::commun::net::req::SAuthenticateReq>    body_authenticate;
    std::shared_ptr<spcbttl::commun::net::req::CreateRoomReq>       body_createroom;
    boost::asio::io_service                                         service;
    sckcpp::tcp::ClientSocket                                       socket(service);

    initLogger();
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();

    body_authenticate = std::make_shared<spcbttl::commun::net::req::SAuthenticateReq>(socket);
    body_createroom = std::make_shared<spcbttl::commun::net::req::CreateRoomReq>();
    body_joinroom= std::make_shared<spcbttl::commun::net::req::JoinRoomReq>();
    //Asteb612 authenticate with id 0
    body_authenticate->setPlayerName(std::string("Asteb612"));
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody_auth = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_authenticate);
    packet1.set(spcbttl::commun::net::req::AUTHENTICATE_REQ, 0, tbody_auth);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet1));
    //user_id 0 create Room 0
    body_createroom->setRoomName(std::string("Room 0"));
    body_createroom->setIsViewerAllow(true);
    body_createroom->setLimitType(spcbttl::commun::engine::TimeLimit::NO_LIMIT);
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody_createroom = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_createroom);
    packet2.set(spcbttl::commun::net::req::CREATE_ROOM_REQ, 0, tbody_createroom);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet2));
    //user_id 0 try join Room 0
    body_joinroom->setRoomName(std::string("Room 0"));
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody_joinroom = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_joinroom);
    packet3.set(spcbttl::commun::net::req::JOIN_ROOM_REQ, 0, tbody_joinroom);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet3));

    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStdout.find("RoomManager: authenticate") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticated with id 0 .") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: create_room name:Room 0 allow_viewers:1 time_limit:3") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: join_room name:Room 0 player:0") != std::string::npos);
    EXPECT_TRUE(outStderr.empty());
}


//!
//! @test Try join room with user already in room
//!
TEST (JoinRoom, user_already_in_room)
{
    std::string                                                     outStdout;
    std::string                                                     outStderr;
    spcbttl::commun::net::Packet                                    packet1;
    spcbttl::commun::net::Packet                                    packet2;
    spcbttl::commun::net::Packet                                    packet3;
    spcbttl::commun::net::Packet                                    packet4;
    spcbttl::commun::net::Packet                                    packet5;
    spcbttl::server::engine::RoomManager<2, 4>                      rmm;
    std::shared_ptr<spcbttl::commun::net::req::JoinRoomReq>         body_joinroom;
    std::shared_ptr<spcbttl::commun::net::req::SAuthenticateReq>    body_authenticate;
    std::shared_ptr<spcbttl::commun::net::req::CreateRoomReq>       body_createroom;
    boost::asio::io_service                                         service;
    sckcpp::tcp::ClientSocket                                       socket(service);

    initLogger();
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();

    body_authenticate = std::make_shared<spcbttl::commun::net::req::SAuthenticateReq>(socket);
    body_createroom = std::make_shared<spcbttl::commun::net::req::CreateRoomReq>();
    body_joinroom= std::make_shared<spcbttl::commun::net::req::JoinRoomReq>();
    //Asteb612 authenticate with id 0
    body_authenticate->setPlayerName(std::string("Asteb612"));
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody_auth = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_authenticate);
    packet1.set(spcbttl::commun::net::req::AUTHENTICATE_REQ, 0, tbody_auth);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet1));
    //user_id 0 create Room 0
    body_createroom->setRoomName(std::string("Room 0"));
    body_createroom->setIsViewerAllow(true);
    body_createroom->setLimitType(spcbttl::commun::engine::TimeLimit::NO_LIMIT);
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody_createroom = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_createroom);
    packet2.set(spcbttl::commun::net::req::CREATE_ROOM_REQ, 0, tbody_createroom);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet2));
    //user_id 0 create Room 1
    body_createroom->setRoomName(std::string("Room 1"));
    body_createroom->setIsViewerAllow(true);
    body_createroom->setLimitType(spcbttl::commun::engine::TimeLimit::NO_LIMIT);
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody_createroom2 = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_createroom);
    packet3.set(spcbttl::commun::net::req::CREATE_ROOM_REQ, 0, tbody_createroom2);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet3));
    //user_id 0 try join Room 0
    body_joinroom->setRoomName(std::string("Room 0"));
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody_joinroom = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_joinroom);
    packet4.set(spcbttl::commun::net::req::JOIN_ROOM_REQ, 0, tbody_joinroom);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet4));
    //user_id 0 try join Room 1
    body_joinroom->setRoomName(std::string("Room 1"));
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody_joinroom2 = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_joinroom);
    packet5.set(spcbttl::commun::net::req::JOIN_ROOM_REQ, 0, tbody_joinroom2);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet5));

    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStdout.find("RoomManager: authenticate") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticated with id 0 .") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: create_room name:Room 0 allow_viewers:1 time_limit:3") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: create_room name:Room 1 allow_viewers:1 time_limit:3") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: join_room name:Room 0 player:0") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: join_room Failed. Player already in room.") != std::string::npos);
    EXPECT_TRUE(outStderr.empty());
}

//!
//! @test Try join room full
//!
TEST (JoinRoom, room_is_full)
{
    std::string                                                     outStdout;
    std::string                                                     outStderr;
    spcbttl::commun::net::Packet                                    packet1;
    spcbttl::commun::net::Packet                                    packet2;
    spcbttl::commun::net::Packet                                    packet3;
    spcbttl::commun::net::Packet                                    packet4;
    spcbttl::commun::net::Packet                                    packet5;
    spcbttl::commun::net::Packet                                    packet6;
    spcbttl::commun::net::Packet                                    packet7;
    spcbttl::server::engine::RoomManager<1, 5>                      rmm;
    std::shared_ptr<spcbttl::commun::net::req::JoinRoomReq>         body_joinroom;
    std::shared_ptr<spcbttl::commun::net::req::SAuthenticateReq>    body_authenticate;
    std::shared_ptr<spcbttl::commun::net::req::CreateRoomReq>       body_createroom;
    boost::asio::io_service                                         service;
    sckcpp::tcp::ClientSocket                                       socket(service);

    initLogger();
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();

    body_authenticate = std::make_shared<spcbttl::commun::net::req::SAuthenticateReq>(socket);
    body_createroom = std::make_shared<spcbttl::commun::net::req::CreateRoomReq>();
    body_joinroom= std::make_shared<spcbttl::commun::net::req::JoinRoomReq>();
    //Asteb612 authenticate with id 0
    body_authenticate->setPlayerName(std::string("Asteb612"));
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody_auth = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_authenticate);
    packet1.set(spcbttl::commun::net::req::AUTHENTICATE_REQ, 0, tbody_auth);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet1));
    //Asteb613 authenticate with id 1
    body_authenticate->setPlayerName(std::string("Asteb613"));
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody_auth2 = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_authenticate);
    packet2.set(spcbttl::commun::net::req::AUTHENTICATE_REQ, 0, tbody_auth2);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet2));
    //Asteb614 authenticate with id 2
    body_authenticate->setPlayerName(std::string("Asteb614"));
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody_auth3 = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_authenticate);
    packet3.set(spcbttl::commun::net::req::AUTHENTICATE_REQ, 0, tbody_auth3);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet3));
    //user_id 0 create Room 0
    body_createroom->setRoomName(std::string("Room 0"));
    body_createroom->setIsViewerAllow(true);
    body_createroom->setLimitType(spcbttl::commun::engine::TimeLimit::NO_LIMIT);
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody_createroom = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_createroom);
    packet4.set(spcbttl::commun::net::req::CREATE_ROOM_REQ, 0, tbody_createroom);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet4));
    //user_id 0 try join Room 0
    body_joinroom->setRoomName(std::string("Room 0"));
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody_joinroom = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_joinroom);
    packet5.set(spcbttl::commun::net::req::JOIN_ROOM_REQ, 0, tbody_joinroom);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet5));
    //user_id 1 try join Room 0
    body_joinroom->setRoomName(std::string("Room 0"));
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody_joinroom2 = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_joinroom);
    packet6.set(spcbttl::commun::net::req::JOIN_ROOM_REQ, 1, tbody_joinroom2);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet6));
    //user_id 2 try join Room 0
    body_joinroom->setRoomName(std::string("Room 0"));
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody_joinroom3 = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_joinroom);
    packet7.set(spcbttl::commun::net::req::JOIN_ROOM_REQ, 2, tbody_joinroom3);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet7));

    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStdout.find("RoomManager: authenticate") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticated with id 0 .") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticated with id 1 .") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticated with id 2 .") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: create_room name:Room 0 allow_viewers:1 time_limit:3") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: join_room name:Room 0 player:0") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: join_room name:Room 0 player:1") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: join_room Failed. Room is full.") != std::string::npos);
    EXPECT_TRUE(outStderr.empty());
}

//!
//! @test Exit joined room
//!
TEST (JoinRoom, exit_room)
{
    std::string                                                     outStdout;
    std::string                                                     outStderr;
    spcbttl::commun::net::Packet                                    packet1;
    spcbttl::commun::net::Packet                                    packet2;
    spcbttl::commun::net::Packet                                    packet3;
    spcbttl::commun::net::Packet                                    packet4;
    spcbttl::server::engine::RoomManager<1, 2>                      rmm;
    std::shared_ptr<spcbttl::commun::net::req::JoinRoomReq>         body_joinroom;
    std::shared_ptr<spcbttl::commun::net::req::SAuthenticateReq>    body_authenticate;
    std::shared_ptr<spcbttl::commun::net::req::CreateRoomReq>       body_createroom;
    std::shared_ptr<spcbttl::commun::net::req::ExitRoomReq>         body_exitroom;
    boost::asio::io_service                                         service;
    sckcpp::tcp::ClientSocket                                       socket(service);

    initLogger();
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();

    body_authenticate = std::make_shared<spcbttl::commun::net::req::SAuthenticateReq>(socket);
    body_createroom = std::make_shared<spcbttl::commun::net::req::CreateRoomReq>();
    body_joinroom = std::make_shared<spcbttl::commun::net::req::JoinRoomReq>();
    body_exitroom = std::make_shared<spcbttl::commun::net::req::ExitRoomReq>();
    //Asteb612 authenticate with id 0
    body_authenticate->setPlayerName(std::string("Asteb612"));
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody_auth = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_authenticate);
    packet1.set(spcbttl::commun::net::req::AUTHENTICATE_REQ, 0, tbody_auth);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet1));
    //user_id 0 create Room 0
    body_createroom->setRoomName(std::string("Room 0"));
    body_createroom->setIsViewerAllow(true);
    body_createroom->setLimitType(spcbttl::commun::engine::TimeLimit::NO_LIMIT);
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody_createroom = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_createroom);
    packet2.set(spcbttl::commun::net::req::CREATE_ROOM_REQ, 0, tbody_createroom);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet2));
    //user_id 0 join Room 0
    body_joinroom->setRoomName(std::string("Room 0"));
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody_joinroom = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_joinroom);
    packet3.set(spcbttl::commun::net::req::JOIN_ROOM_REQ, 0, tbody_joinroom);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet3));
    //user_id 0 exit Room 0
    body_exitroom->setRoomName(std::string("Room 0"));
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody_exitroom = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_exitroom);
    packet4.set(spcbttl::commun::net::req::EXIT_ROOM_REQ, 0, tbody_exitroom);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet4));

    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStdout.find("RoomManager: authenticate") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticated with id 0 .") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: create_room name:Room 0 allow_viewers:1 time_limit:3") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: join_room name:Room 0 player:0") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: exit_room name:Room 0 player:0") != std::string::npos);
    EXPECT_TRUE(outStderr.empty());
}