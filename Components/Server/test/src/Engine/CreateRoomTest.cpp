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
//! @test No authenticated user try to create a room
//!
TEST (CreateRoom, auth_required)
{
    std::string                                                 outStdout;
    std::string                                                 outStderr;
    spcbttl::commun::net::Packet                                packet1;
    std::shared_ptr<spcbttl::commun::net::req::CreateRoomReq>   body;

    initLogger();
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();
    spcbttl::server::engine::RoomManager<1, 2>    rmm;

    //Create room :Asteb612 with viewer and no time limit
    body = std::make_shared<spcbttl::commun::net::req::CreateRoomReq>();
    body->setRoomName(std::string("Asteb612"));
    body->setIsViewerAllow(true);
    body->setLimitType(spcbttl::commun::engine::TimeLimit::NO_LIMIT);
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body);
    packet1.set(spcbttl::commun::net::req::CREATE_ROOM_REQ, 0, tbody);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet1));

    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStdout.find("RoomManager: create_room Failed. Player not authenticated.") != std::string::npos);
    EXPECT_TRUE(outStderr.empty());
}

//!
//! @test Create a new room
//!
TEST (CreateRoom, new_room)
{
    std::string                                                     outStdout;
    std::string                                                     outStderr;
    spcbttl::commun::net::Packet                                    packet1;
    spcbttl::commun::net::Packet                                    packet2;
    std::shared_ptr<spcbttl::commun::net::req::SAuthenticateReq>    body_authenticate;
    std::shared_ptr<spcbttl::commun::net::req::CreateRoomReq>       body_createroom;
    boost::asio::io_service                                         service;
    sckcpp::tcp::ClientSocket                                       socket(service);

    initLogger();
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();
    spcbttl::server::engine::RoomManager<1, 2>    rmm;
    body_authenticate = std::make_shared<spcbttl::commun::net::req::SAuthenticateReq>(socket);
    body_createroom = std::make_shared<spcbttl::commun::net::req::CreateRoomReq>();
    //Asteb612 authenticate with id 0
    body_authenticate->setPlayerName(std::string("Asteb612"));
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody_auth = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_authenticate);
    packet1.set(spcbttl::commun::net::req::AUTHENTICATE_REQ, 0, tbody_auth);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet1));
    //Create room :Asteb612 with viewer and no time limit
    body_createroom->setRoomName(std::string("Asteb612"));
    body_createroom->setIsViewerAllow(true);
    body_createroom->setLimitType(spcbttl::commun::engine::TimeLimit::NO_LIMIT);
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_createroom);
    packet2.set(spcbttl::commun::net::req::CREATE_ROOM_REQ, 0, tbody);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet2));

    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStdout.find("RoomManager: authenticate") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticated with id 0 .") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: create_room name:Asteb612 allow_viewers:1 time_limit:3") != std::string::npos);
    EXPECT_TRUE(outStderr.empty());
}

//!
//! @test Check max room number
//!
TEST (CreateRoom, max_room)
{
    std::string                                                     outStdout;
    std::string                                                     outStderr;
    spcbttl::commun::net::Packet                                    packet1;
    spcbttl::commun::net::Packet                                    packet2;
    spcbttl::commun::net::Packet                                    packet3;
    std::shared_ptr<spcbttl::commun::net::req::SAuthenticateReq>    body_authenticate;
    std::shared_ptr<spcbttl::commun::net::req::CreateRoomReq>       body_createroom;
    boost::asio::io_service                                         service;
    sckcpp::tcp::ClientSocket                                       socket(service);

    initLogger();
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();
    spcbttl::server::engine::RoomManager<1, 2>    rmm;
    body_authenticate = std::make_shared<spcbttl::commun::net::req::SAuthenticateReq>(socket);
    body_createroom = std::make_shared<spcbttl::commun::net::req::CreateRoomReq>();
    //Asteb612 authenticate with id 0
    body_authenticate->setPlayerName(std::string("Asteb612"));
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody_auth = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_authenticate);
    packet1.set(spcbttl::commun::net::req::AUTHENTICATE_REQ, 0, tbody_auth);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet1));
    //Create room :Asteb612 with viewer and no time limit
    body_createroom->setRoomName(std::string("Asteb612"));
    body_createroom->setIsViewerAllow(true);
    body_createroom->setLimitType(spcbttl::commun::engine::TimeLimit::NO_LIMIT);
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody_createroom = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_createroom);
    packet2.set(spcbttl::commun::net::req::CREATE_ROOM_REQ, 0, tbody_createroom);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet2));
    //Create room :Asteb612 with viewer and no time limit
    packet3.set(spcbttl::commun::net::req::CREATE_ROOM_REQ, 0, tbody_createroom);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet3));
    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStdout.find("RoomManager: authenticate") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticated with id 0 .") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: create_room name:Asteb612 allow_viewers:1 time_limit:3") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: create_room Failed. No Room available.") != std::string::npos);
    EXPECT_TRUE(outStderr.empty());
}

//!
//! @test Check create room with too short or too long name
//!
TEST (CreateRoom, invalid_name)
{
    std::string                                                     outStdout;
    std::string                                                     outStderr;
    spcbttl::commun::net::Packet                                    packet1;
    spcbttl::commun::net::Packet                                    packet2;
    spcbttl::commun::net::Packet                                    packet3;
    std::shared_ptr<spcbttl::commun::net::req::SAuthenticateReq>    body_authenticate;
    std::shared_ptr<spcbttl::commun::net::req::CreateRoomReq>       body_createroom;
    boost::asio::io_service                                         service;
    sckcpp::tcp::ClientSocket                                       socket(service);

    initLogger();
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();
    spcbttl::server::engine::RoomManager<1, 2>    rmm;
    body_authenticate = std::make_shared<spcbttl::commun::net::req::SAuthenticateReq>(socket);
    body_createroom = std::make_shared<spcbttl::commun::net::req::CreateRoomReq>();
    //Asteb612 authenticate with id 0
    body_authenticate->setPlayerName(std::string("Asteb612"));
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody_auth = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_authenticate);
    packet1.set(spcbttl::commun::net::req::AUTHENTICATE_REQ, 0, tbody_auth);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet1));
    //Create room :42 with viewer and no time limit
    body_createroom->setRoomName(std::string("42"));
    body_createroom->setIsViewerAllow(true);
    body_createroom->setLimitType(spcbttl::commun::engine::TimeLimit::NO_LIMIT);
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody2 = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_createroom);
    packet2.set(spcbttl::commun::net::req::CREATE_ROOM_REQ, 0, tbody2);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet2));
    //Create room :qwertyuiopasdfghjk with viewer and no time limit
    body_createroom->setRoomName(std::string("qwertyuiopasdfghjk"));
    body_createroom->setIsViewerAllow(true);
    body_createroom->setLimitType(spcbttl::commun::engine::TimeLimit::NO_LIMIT);
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody3 = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_createroom);
    packet3.set(spcbttl::commun::net::req::CREATE_ROOM_REQ, 0, tbody2);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet3));
    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStdout.find("RoomManager: authenticate") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticated with id 0 .") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: create_room Failed. Invalid name.") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: create_room Failed. Invalid name.") != std::string::npos);
    EXPECT_TRUE(outStderr.empty());
}


//!
//! @test Try create room already created
//!
TEST (CreateRoom, rom_already_exist)
{
    std::string                                                  outStdout;
    std::string                                                  outStderr;
    spcbttl::commun::net::Packet                                 packet1;
    spcbttl::commun::net::Packet                                 packet2;
    spcbttl::commun::net::Packet                                 packet3;
    std::shared_ptr<spcbttl::commun::net::req::SAuthenticateReq> body_authenticate;
    std::shared_ptr<spcbttl::commun::net::req::CreateRoomReq>    body_createroom;
    boost::asio::io_service                                      service;
    sckcpp::tcp::ClientSocket                                    socket(service);

    initLogger();
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();
    spcbttl::server::engine::RoomManager<2, 4>    rmm;
    body_authenticate = std::make_shared<spcbttl::commun::net::req::SAuthenticateReq>(socket);
    body_createroom = std::make_shared<spcbttl::commun::net::req::CreateRoomReq>();
    //Asteb612 authenticate with id 0
    body_authenticate->setPlayerName(std::string("Asteb612"));
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody_auth = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_authenticate);
    packet1.set(spcbttl::commun::net::req::AUTHENTICATE_REQ, 0, tbody_auth);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet1));
    //Create room :Marvin with viewer and no time limit
    body_createroom->setRoomName(std::string("Marvin"));
    body_createroom->setIsViewerAllow(true);
    body_createroom->setLimitType(spcbttl::commun::engine::TimeLimit::NO_LIMIT);
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody2 = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_createroom);
    packet2.set(spcbttl::commun::net::req::CREATE_ROOM_REQ, 0, tbody2);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet2));
    //Create room :Marvin with viewer and no time limit
    body_createroom->setRoomName(std::string("Marvin"));
    body_createroom->setIsViewerAllow(true);
    body_createroom->setLimitType(spcbttl::commun::engine::TimeLimit::NO_LIMIT);
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody3 = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_createroom);
    packet3.set(spcbttl::commun::net::req::CREATE_ROOM_REQ, 0, tbody2);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet3));
    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStdout.find("RoomManager: authenticate") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticated with id 0 .") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: create_room name:Marvin allow_viewers:1 time_limit:3") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: create_room Failed. Room name already exist.") != std::string::npos);
    EXPECT_TRUE(outStderr.empty());
}
