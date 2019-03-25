//!
//! @file Types.cpp
//! @author jbruel
//! @date 13/11/18
//!

#include "Commun/Network/Requests/State.hpp"
#include "Commun/Network/Requests/Requests.hpp"
#include <gtest/gtest.h>

//!
//! @test Requests types checks.
//!
TEST (RequestType, commandType)
{
    EXPECT_EQ(spcbttl::commun::net::req::Type::NONE, 99);
    EXPECT_EQ(spcbttl::commun::net::req::Type::KEEP_ALIVE_REQ, 0);
    EXPECT_EQ(spcbttl::commun::net::req::Type::AUTHENTICATE_REQ, 1);
    EXPECT_EQ(spcbttl::commun::net::req::Type::AUTHENTICATE_RESP, 2);
    EXPECT_EQ(spcbttl::commun::net::req::Type::GET_ROOM_LIST_REQ, 3);
    EXPECT_EQ(spcbttl::commun::net::req::Type::GET_ROOM_LIST_RESP, 4);
    EXPECT_EQ(spcbttl::commun::net::req::Type::CREATE_ROOM_REQ, 5);
    EXPECT_EQ(spcbttl::commun::net::req::Type::CREATE_ROOM_RESP, 6);
    EXPECT_EQ(spcbttl::commun::net::req::Type::JOIN_ROOM_REQ, 7);
    EXPECT_EQ(spcbttl::commun::net::req::Type::JOIN_ROOM_RESP, 8);
    EXPECT_EQ(spcbttl::commun::net::req::Type::VIEW_ROOM_REQ, 9);
    EXPECT_EQ(spcbttl::commun::net::req::Type::VIEW_ROOM_RESP, 10);
    EXPECT_EQ(spcbttl::commun::net::req::Type::EXIT_ROOM_REQ, 11);
    EXPECT_EQ(spcbttl::commun::net::req::Type::LAUNCH_GAME_REQ, 12);
    EXPECT_EQ(spcbttl::commun::net::req::Type::LAUNCH_GAME_RESP, 13);
    EXPECT_EQ(spcbttl::commun::net::req::Type::LOBBY_STATE_UPDATE_RESP, 14);
    EXPECT_EQ(spcbttl::commun::net::req::Type::SET_USER_BATTLESHIP_REQ, 20);
    EXPECT_EQ(spcbttl::commun::net::req::Type::SET_USER_BATTLESHIP_RESP, 21);
    EXPECT_EQ(spcbttl::commun::net::req::Type::SEND_CHAT_MSG_REQ, 22);
    EXPECT_EQ(spcbttl::commun::net::req::Type::BROADCAST_CHAT_MSG_REQ, 23);
    EXPECT_EQ(spcbttl::commun::net::req::Type::SHOOT_SHIP_REQ, 24);
    EXPECT_EQ(spcbttl::commun::net::req::Type::SHOOT_SHIP_RESP, 25);
    EXPECT_EQ(spcbttl::commun::net::req::Type::SHOOT_STATE_RESP, 26);
    EXPECT_EQ(spcbttl::commun::net::req::Type::END_GAME_STATUS_REQ, 27);
}

//!
//! @test Request state.
//!
TEST (RequestType, states)
{
    EXPECT_EQ(spcbttl::commun::net::req::State::NO_STATE, static_cast<spcbttl::commun::net::req::State>(999));
    EXPECT_EQ(spcbttl::commun::net::req::State::ERROR_ALREADY_AUTH_STATE, static_cast<spcbttl::commun::net::req::State>(100));
    EXPECT_EQ(spcbttl::commun::net::req::State::ERROR_NOT_AUTH_STATE, static_cast<spcbttl::commun::net::req::State>(101));
    EXPECT_EQ(spcbttl::commun::net::req::State::ERROR_MAX_ROOM_NB_EXCEEDED_STATE, static_cast<spcbttl::commun::net::req::State>(102));
    EXPECT_EQ(spcbttl::commun::net::req::State::ERROR_PLAYER_ALREADY_IN_ROOM_STATE, static_cast<spcbttl::commun::net::req::State>(103));
    EXPECT_EQ(spcbttl::commun::net::req::State::ERROR_ROOM_ALREADY_EXIST_STATE, static_cast<spcbttl::commun::net::req::State>(104));
    EXPECT_EQ(spcbttl::commun::net::req::State::ERROR_INVALID_ROOM_NAME_STATE, static_cast<spcbttl::commun::net::req::State>(105));
    EXPECT_EQ(spcbttl::commun::net::req::State::ERROR_MAX_ROOM_PLAYER_EXCEEDED_STATE, static_cast<spcbttl::commun::net::req::State>(107));
    EXPECT_EQ(spcbttl::commun::net::req::State::ERROR_PLAYER_ALREADY_IN_ROOM_STATE, static_cast<spcbttl::commun::net::req::State>(103));
    EXPECT_EQ(spcbttl::commun::net::req::State::ERROR_ROOM_DOES_NOT_EXIST_STATE, static_cast<spcbttl::commun::net::req::State>(109));
    EXPECT_EQ(spcbttl::commun::net::req::State::ERROR_GAME_ALREADY_RUNNING_STATE, static_cast<spcbttl::commun::net::req::State>(110));
    EXPECT_EQ(spcbttl::commun::net::req::State::ERROR_MAX_ROOM_VIEWER_EXCEEDED_STATE, static_cast<spcbttl::commun::net::req::State>(112));
    EXPECT_EQ(spcbttl::commun::net::req::State::ERROR_ROOM_DOES_NOT_EXIST_STATE, static_cast<spcbttl::commun::net::req::State>(109));
    EXPECT_EQ(spcbttl::commun::net::req::State::ERROR_NOT_AUTH_STATE, static_cast<spcbttl::commun::net::req::State>(101));
    EXPECT_EQ(spcbttl::commun::net::req::State::ERROR_PLAYER_NOT_IN_ROOM_STATE, static_cast<spcbttl::commun::net::req::State>(115));
    EXPECT_EQ(spcbttl::commun::net::req::State::ERROR_GAME_ALREADY_RUNNING_STATE, static_cast<spcbttl::commun::net::req::State>(110));
    EXPECT_EQ(spcbttl::commun::net::req::State::ERROR_NOT_AUTH_STATE, static_cast<spcbttl::commun::net::req::State>(101));
    EXPECT_EQ(spcbttl::commun::net::req::State::ERROR_PLAYER_NOT_IN_ROOM_STATE, static_cast<spcbttl::commun::net::req::State>(115));
    EXPECT_EQ(spcbttl::commun::net::req::State::ERROR_GAME_ALREADY_RUNNING_STATE, static_cast<spcbttl::commun::net::req::State>(110));
    EXPECT_EQ(spcbttl::commun::net::req::State::ERROR_INVALID_SHIP_STATE, static_cast<spcbttl::commun::net::req::State>(119));
    EXPECT_EQ(spcbttl::commun::net::req::State::ERROR_INVALID_POSITION_STATE, static_cast<spcbttl::commun::net::req::State>(118));
}

//!
//! @test Requests types checks.
//!
TEST (RequestType, requestAssignedType)
{
    spcbttl::commun::net::req::KeepAliveReq     keepAliveReq;
    spcbttl::commun::net::req::AuthenticateReq  authenticateReq;
    spcbttl::commun::net::req::AuthenticateResp authenticateResp;
    spcbttl::commun::net::req::CreateRoomReq    createRoomReq;
    spcbttl::commun::net::req::CreateRoomResp   createRoomResp;
    spcbttl::commun::net::req::GetRoomListReq   getRoomListReq;
    spcbttl::commun::net::req::GetRoomListResp  getRoomListResp;

    EXPECT_EQ(spcbttl::commun::net::req::Type::KEEP_ALIVE_REQ, keepAliveReq.getType());
    EXPECT_EQ(spcbttl::commun::net::req::Type::AUTHENTICATE_REQ, authenticateReq.getType());
    EXPECT_EQ(spcbttl::commun::net::req::Type::AUTHENTICATE_RESP, authenticateResp.getType());
    EXPECT_EQ(spcbttl::commun::net::req::Type::GET_ROOM_LIST_REQ, getRoomListReq.getType());
    EXPECT_EQ(spcbttl::commun::net::req::Type::GET_ROOM_LIST_RESP, getRoomListResp.getType());
    EXPECT_EQ(spcbttl::commun::net::req::Type::CREATE_ROOM_REQ, createRoomReq.getType());
    EXPECT_EQ(spcbttl::commun::net::req::Type::CREATE_ROOM_RESP, createRoomResp.getType());
}