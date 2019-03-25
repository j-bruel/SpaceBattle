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
//! @test Try view room with user not authenticated
//!
TEST (ViewRoom, user_not_authenticated)
{
    std::string                                                     outStdout;
    std::string                                                     outStderr;
    spcbttl::commun::net::Packet                                    packet1;
    spcbttl::commun::net::Packet                                    packet2;
    spcbttl::commun::net::Packet                                    packet3;
    spcbttl::server::engine::RoomManager<1, 2>                      rmm;
    std::shared_ptr<spcbttl::commun::net::req::ViewRoomReq>         body_viewroom;
    std::shared_ptr<spcbttl::commun::net::req::CreateRoomReq>       body_createroom;
    std::shared_ptr<spcbttl::commun::net::req::SAuthenticateReq>    body_authenticate;
    boost::asio::io_service                                         service;
    sckcpp::tcp::ClientSocket                                       socket(service);


    initLogger();
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();
    body_createroom = std::make_shared<spcbttl::commun::net::req::CreateRoomReq>();
    body_authenticate = std::make_shared<spcbttl::commun::net::req::SAuthenticateReq>(socket);
    body_viewroom= std::make_shared<spcbttl::commun::net::req::ViewRoomReq>();
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
    body_viewroom->setRoomName(std::string("Room 0"));
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody_joinroom = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_viewroom);
    packet3.set(spcbttl::commun::net::req::VIEW_ROOM_REQ, 1, tbody_joinroom);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet3));

    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStdout.find("RoomManager: authenticate") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticated with id 0 .") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: create_room name:Room 0 allow_viewers:1 time_limit:3") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: view_room Failed. Player not authenticated.") != std::string::npos);
    EXPECT_TRUE(outStderr.empty());
}


//!
//! @test Try view room not exist
//!
TEST (ViewRoom, room_not_exist)
{
    std::string                                                     outStdout;
    std::string                                                     outStderr;
    spcbttl::commun::net::Packet                                    packet1;
    spcbttl::commun::net::Packet                                    packet2;
    spcbttl::server::engine::RoomManager<1, 2>                      rmm;
    std::shared_ptr<spcbttl::commun::net::req::ViewRoomReq>         body_viewroom;
    std::shared_ptr<spcbttl::commun::net::req::SAuthenticateReq>    body_authenticate;
    boost::asio::io_service                                         service;
    sckcpp::tcp::ClientSocket                                       socket(service);

    initLogger();
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();
    body_authenticate = std::make_shared<spcbttl::commun::net::req::SAuthenticateReq>(socket);
    body_viewroom = std::make_shared<spcbttl::commun::net::req::ViewRoomReq>();
    //Asteb612 authenticate with id 0
    body_authenticate->setPlayerName(std::string("Asteb612"));
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody_auth = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_authenticate);
    packet1.set(spcbttl::commun::net::req::AUTHENTICATE_REQ, 0, tbody_auth);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet1));
    //user_id 0 try join Room 0
    body_viewroom->setRoomName(std::string("Room 0"));
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody_joinroom = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_viewroom);
    packet2.set(spcbttl::commun::net::req::VIEW_ROOM_REQ, 0, tbody_joinroom);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet2));

    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStdout.find("RoomManager: authenticate") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticated with id 0 .") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: view_room Failed. Room not not exist.") != std::string::npos);
    EXPECT_TRUE(outStderr.empty());
}

//!
//! @test View room
//!
TEST (ViewRoom, has_join_room)
{
    std::string                                                     outStdout;
    std::string                                                     outStderr;
    spcbttl::commun::net::Packet                                    packet1;
    spcbttl::commun::net::Packet                                    packet2;
    spcbttl::commun::net::Packet                                    packet3;
    spcbttl::server::engine::RoomManager<1, 2>                      rmm;
    std::shared_ptr<spcbttl::commun::net::req::ViewRoomReq>         body_viewroom;
    std::shared_ptr<spcbttl::commun::net::req::SAuthenticateReq>    body_authenticate;
    std::shared_ptr<spcbttl::commun::net::req::CreateRoomReq>       body_createroom;
    boost::asio::io_service                                         service;
    sckcpp::tcp::ClientSocket                                       socket(service);

    initLogger();
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();

    body_authenticate = std::make_shared<spcbttl::commun::net::req::SAuthenticateReq>(socket);
    body_createroom = std::make_shared<spcbttl::commun::net::req::CreateRoomReq>();
    body_viewroom = std::make_shared<spcbttl::commun::net::req::ViewRoomReq>();
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
    body_viewroom->setRoomName(std::string("Room 0"));
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody_joinroom = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_viewroom);
    packet3.set(spcbttl::commun::net::req::VIEW_ROOM_REQ, 0, tbody_joinroom);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet3));

    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStdout.find("RoomManager: authenticate") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticated with id 0 .") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: create_room name:Room 0 allow_viewers:1 time_limit:3") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: view_room name:Room 0 player:0") != std::string::npos);
    EXPECT_TRUE(outStderr.empty());
}


//!
//! @test Try join room with user already in room
//!
TEST (ViewRoom, user_already_in_room)
{
    std::string                                                     outStdout;
    std::string                                                     outStderr;
    spcbttl::commun::net::Packet                                    packet1;
    spcbttl::commun::net::Packet                                    packet2;
    spcbttl::commun::net::Packet                                    packet3;
    spcbttl::commun::net::Packet                                    packet4;
    spcbttl::commun::net::Packet                                    packet5;
    spcbttl::server::engine::RoomManager<5, 10>                     rmm;
    std::shared_ptr<spcbttl::commun::net::req::ViewRoomReq>         body_viewroom;
    std::shared_ptr<spcbttl::commun::net::req::SAuthenticateReq>    body_authenticate;
    std::shared_ptr<spcbttl::commun::net::req::CreateRoomReq>       body_createroom;
    boost::asio::io_service                                         service;
    sckcpp::tcp::ClientSocket                                       socket(service);

    initLogger();
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();

    body_authenticate = std::make_shared<spcbttl::commun::net::req::SAuthenticateReq>(socket);
    body_createroom = std::make_shared<spcbttl::commun::net::req::CreateRoomReq>();
    body_viewroom= std::make_shared<spcbttl::commun::net::req::ViewRoomReq>();
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
    body_viewroom->setRoomName(std::string("Room 0"));
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody_joinroom = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_viewroom);
    packet4.set(spcbttl::commun::net::req::VIEW_ROOM_REQ, 0, tbody_joinroom);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet4));
    //user_id 0 try join Room 1
    body_viewroom->setRoomName(std::string("Room 1"));
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody_joinroom2 = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_viewroom);
    packet5.set(spcbttl::commun::net::req::VIEW_ROOM_REQ, 0, tbody_joinroom2);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet5));

    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStdout.find("RoomManager: authenticate") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticated with id 0 .") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: create_room name:Room 0 allow_viewers:1 time_limit:3") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: create_room name:Room 1 allow_viewers:1 time_limit:3") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: view_room name:Room 0 player:0") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: view_room Failed. Player already in room.") != std::string::npos);
    EXPECT_TRUE(outStderr.empty());
}

//!
//! @test Try join room full
//!
TEST (ViewRoom, room_is_full)
{
    std::string                                                     outStdout;
    std::string                                                     outStderr;
    spcbttl::commun::net::Packet                                    packet1;
    spcbttl::commun::net::Packet                                    packet2;
    spcbttl::commun::net::Packet                                    packet3;
    spcbttl::server::engine::RoomManager<1, 100>                    rmm;
    std::shared_ptr<spcbttl::commun::net::req::ViewRoomReq>         body_viewroom;
    std::shared_ptr<spcbttl::commun::net::req::SAuthenticateReq>    body_authenticate;
    std::shared_ptr<spcbttl::commun::net::req::CreateRoomReq>       body_createroom;
    boost::asio::io_service                                         service;
    sckcpp::tcp::ClientSocket                                       socket(service);

    initLogger();
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();

    body_authenticate = std::make_shared<spcbttl::commun::net::req::SAuthenticateReq>(socket);
    body_createroom = std::make_shared<spcbttl::commun::net::req::CreateRoomReq>();
    body_viewroom = std::make_shared<spcbttl::commun::net::req::ViewRoomReq>();
    //Asteb612 authenticate with id 0
    body_authenticate->setPlayerName(std::string("Asteb612_0"));
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
    body_viewroom->setRoomName(std::string("Room 0"));
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody_joinroom = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_viewroom);
    packet3.set(spcbttl::commun::net::req::VIEW_ROOM_REQ, 0, tbody_joinroom);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet3));
    for (unsigned int id = 1; id <= MAX_VIEWER; id++) {
        //Asteb612 authenticate with id
        body_authenticate->setPlayerName(std::string("Asteb612_")+std::to_string(id));
        std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody_auth = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_authenticate);
        packet1.set(spcbttl::commun::net::req::AUTHENTICATE_REQ, 0, tbody_auth);
        rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet1));
        //user_id id try join Room 0
        body_viewroom->setRoomName(std::string("Room 0"));
        std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody_joinroom = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_viewroom);
        packet3.set(spcbttl::commun::net::req::VIEW_ROOM_REQ, id, tbody_joinroom);
        rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet3));
    }

    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStdout.find("RoomManager: authenticate") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticated with id 0 .") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: create_room name:Room 0 allow_viewers:1 time_limit:3") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: view_room name:Room 0 player:0") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: view_room name:Room 0 player:1") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: view_room name:Room 0 player:2") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: view_room name:Room 0 player:3") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: view_room name:Room 0 player:4") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: view_room name:Room 0 player:5") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: view_room name:Room 0 player:6") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: view_room name:Room 0 player:7") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: view_room name:Room 0 player:8") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: view_room name:Room 0 player:9") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: view_room Failed. Room is full.") != std::string::npos);
    EXPECT_TRUE(outStderr.empty());
}

//!
//! @test Try join room was not allow viewer
//!
TEST (ViewRoom, room_not_allow_view)
{
    std::string                                                     outStdout;
    std::string                                                     outStderr;
    spcbttl::commun::net::Packet                                    packet1;
    spcbttl::commun::net::Packet                                    packet2;
    spcbttl::commun::net::Packet                                    packet3;
    spcbttl::server::engine::RoomManager<1, 2>                      rmm;
    std::shared_ptr<spcbttl::commun::net::req::ViewRoomReq>         body_viewroom;
    std::shared_ptr<spcbttl::commun::net::req::SAuthenticateReq>    body_authenticate;
    std::shared_ptr<spcbttl::commun::net::req::CreateRoomReq>       body_createroom;
    boost::asio::io_service                                         service;
    sckcpp::tcp::ClientSocket                                       socket(service);

    initLogger();
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();

    body_authenticate = std::make_shared<spcbttl::commun::net::req::SAuthenticateReq>(socket);
    body_createroom = std::make_shared<spcbttl::commun::net::req::CreateRoomReq>();
    body_viewroom = std::make_shared<spcbttl::commun::net::req::ViewRoomReq>();
    //Asteb612 authenticate with id 0
    body_authenticate->setPlayerName(std::string("Asteb612"));
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody_auth = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_authenticate);
    packet1.set(spcbttl::commun::net::req::AUTHENTICATE_REQ, 0, tbody_auth);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet1));
    //user_id 0 create Room 0
    body_createroom->setRoomName(std::string("Room 0"));
    body_createroom->setIsViewerAllow(false);
    body_createroom->setLimitType(spcbttl::commun::engine::TimeLimit::NO_LIMIT);
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody_createroom = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_createroom);
    packet2.set(spcbttl::commun::net::req::CREATE_ROOM_REQ, 0, tbody_createroom);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet2));
    //user_id 0 try join Room 0
    body_viewroom->setRoomName(std::string("Room 0"));
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody_joinroom = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_viewroom);
    packet3.set(spcbttl::commun::net::req::VIEW_ROOM_REQ, 0, tbody_joinroom);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet3));

    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStdout.find("RoomManager: authenticate") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticated with id 0 .") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: create_room name:Room 0 allow_viewers:0 time_limit:3") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: view_room Failed. Room not allow viewers.") != std::string::npos);
    EXPECT_TRUE(outStderr.empty());
}

//!
//! @test Exit viewed room
//!
TEST (ViewRoom, exit_room)
{
    std::string                                                     outStdout;
    std::string                                                     outStderr;
    spcbttl::commun::net::Packet                                    packet1;
    spcbttl::commun::net::Packet                                    packet2;
    spcbttl::commun::net::Packet                                    packet3;
    spcbttl::commun::net::Packet                                    packet4;
    spcbttl::server::engine::RoomManager<1, 2>                      rmm;
    std::shared_ptr<spcbttl::commun::net::req::ViewRoomReq>         body_viewroom;
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
    body_viewroom = std::make_shared<spcbttl::commun::net::req::ViewRoomReq>();
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
    body_viewroom->setRoomName(std::string("Room 0"));
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody_joinroom = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_viewroom);
    packet3.set(spcbttl::commun::net::req::VIEW_ROOM_REQ, 0, tbody_joinroom);
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
    EXPECT_TRUE(outStdout.find("RoomManager: view_room name:Room 0 player:0") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: exit_room name:Room 0 player:0") != std::string::npos);
    EXPECT_TRUE(outStderr.empty());
}
