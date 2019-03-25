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
//! @test Get list of rooms
//!
TEST (GetRoomList, two_room)
{
    std::string                                                     outStdout;
    std::string                                                     outStderr;
    spcbttl::commun::net::Packet                                    packet1;
    spcbttl::commun::net::Packet                                    packet2;
    spcbttl::commun::net::Packet                                    packet3;
    spcbttl::commun::net::Packet                                    packet4;
    std::shared_ptr<spcbttl::commun::net::req::SAuthenticateReq>    body_authenticate;
    std::shared_ptr<spcbttl::commun::net::req::CreateRoomReq>       body_createroom;
    boost::asio::io_service                                         service;
    sckcpp::tcp::ClientSocket                                       socket(service);

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
    //Create room :Marvin1 with viewer and no time limit
    body_createroom->setRoomName(std::string("Marvin1"));
    body_createroom->setIsViewerAllow(true);
    body_createroom->setLimitType(spcbttl::commun::engine::TimeLimit::NO_LIMIT);
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody2 = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_createroom);
    packet2.set(spcbttl::commun::net::req::CREATE_ROOM_REQ, 0, tbody2);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet2));
    //Create room :Marvin2 with viewer and no time limit
    body_createroom->setRoomName(std::string("Marvin2"));
    body_createroom->setIsViewerAllow(true);
    body_createroom->setLimitType(spcbttl::commun::engine::TimeLimit::NO_LIMIT);
    std::shared_ptr<spcbttl::commun::net::req::IRequest> tbody3 = std::dynamic_pointer_cast<spcbttl::commun::net::req::IRequest>(body_createroom);
    packet3.set(spcbttl::commun::net::req::CREATE_ROOM_REQ, 0, tbody2);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet3));
    //list room
    packet4.setHeader(spcbttl::commun::net::req::GET_ROOM_LIST_REQ, 0);
    rmm.execute(std::make_shared<spcbttl::commun::net::Packet>(packet4));
    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStdout.find("RoomManager: authenticate") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: authenticated with id 0 .") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: create_room name:Marvin1 allow_viewers:1 time_limit:3") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: create_room name:Marvin2 allow_viewers:1 time_limit:3") != std::string::npos);
    EXPECT_TRUE(outStdout.find("RoomManager: get_room_list") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Room name :Marvin1 status :0") != std::string::npos);
    EXPECT_TRUE(outStdout.find("Room name :Marvin2 status :0") != std::string::npos);
    EXPECT_TRUE(outStderr.empty());
}
