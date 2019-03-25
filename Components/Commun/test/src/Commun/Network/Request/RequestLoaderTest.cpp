//!
//! @file RequestLoaderTest.cpp
//! @author jbruel
//! @date 13/11/18
//!

#include <gtest/gtest.h>
#include "Commun/Network/Requests/Requests.hpp"
#include "Commun/Network/Requests/RequestLoader.hpp"

//!
//! @test Checking KeepAliveReq (pack, unpack, load in RequestLoader, set and get).
//!
TEST (RequestLoader, keepAliveReq)
{
    spcbttl::commun::net::req::RequestLoader    requestLoader;
    spcbttl::commun::net::req::KeepAliveReq     inKeepAliveReq;
    msgpack::sbuffer                            sb;

    msgpack::pack(sb, inKeepAliveReq);

    msgpack::object_handle  oh = msgpack::unpack(sb.data(), sb.size());
    msgpack::object         obj = oh.get();

    const std::shared_ptr<spcbttl::commun::net::req::IRequest>    req(requestLoader.load(spcbttl::commun::net::req::Type::KEEP_ALIVE_REQ, obj));

    EXPECT_EQ(req->getType(), spcbttl::commun::net::req::Type::KEEP_ALIVE_REQ);

    spcbttl::commun::net::req::KeepAliveReq     *outKeepAliveReq = reinterpret_cast<spcbttl::commun::net::req::KeepAliveReq *>(req.get());

    EXPECT_EQ(outKeepAliveReq->getType(), spcbttl::commun::net::req::Type::KEEP_ALIVE_REQ);
}

//!
//! @test Checking AuthenticateReq (pack, unpack, load in RequestLoader, set and get).
//!
TEST (RequestLoader, authenticateReq)
{
    spcbttl::commun::net::req::RequestLoader    requestLoader;
    spcbttl::commun::net::req::AuthenticateReq  inAuthenticateReq;
    msgpack::sbuffer                            sb;


    inAuthenticateReq.setPlayerName("Player test name.");
    msgpack::pack(sb, inAuthenticateReq);

    msgpack::object_handle  oh = msgpack::unpack(sb.data(), sb.size());
    msgpack::object         obj = oh.get();

    const std::shared_ptr<spcbttl::commun::net::req::IRequest>    req = requestLoader.load(spcbttl::commun::net::req::Type::AUTHENTICATE_REQ, obj);

    EXPECT_EQ(req->getType(), spcbttl::commun::net::req::Type::AUTHENTICATE_REQ);

    spcbttl::commun::net::req::AuthenticateReq  *outAuthenticateReq(reinterpret_cast<spcbttl::commun::net::req::AuthenticateReq *>(req.get()));

    EXPECT_EQ(outAuthenticateReq->getType(), spcbttl::commun::net::req::Type::AUTHENTICATE_REQ);
    EXPECT_STRCASEEQ(outAuthenticateReq->getPlayerName().c_str(), "Player test name.");
}

//!
//! @test Checking authenticateResp (pack, unpack, load in RequestLoader, set and get).
//!
TEST (RequestLoader, authenticateResp)
{
    spcbttl::commun::net::req::RequestLoader    requestLoader;
    spcbttl::commun::net::req::AuthenticateResp inAuthenticateResp;
    msgpack::sbuffer                            sb;


    inAuthenticateResp.setPlayerName("Player test name.");
    inAuthenticateResp.setState(spcbttl::commun::net::req::State::ERROR_ALREADY_AUTH_STATE);
    msgpack::pack(sb, inAuthenticateResp);

    msgpack::object_handle  oh = msgpack::unpack(sb.data(), sb.size());
    msgpack::object         obj = oh.get();

    const std::shared_ptr<spcbttl::commun::net::req::IRequest>    req = requestLoader.load(spcbttl::commun::net::req::Type::AUTHENTICATE_RESP, obj);

    EXPECT_EQ(req->getType(), spcbttl::commun::net::req::Type::AUTHENTICATE_RESP);

    spcbttl::commun::net::req::AuthenticateResp  *outAuthenticateResp(reinterpret_cast<spcbttl::commun::net::req::AuthenticateResp *>(req.get()));

    EXPECT_EQ(outAuthenticateResp->getType(), spcbttl::commun::net::req::Type::AUTHENTICATE_RESP);
    EXPECT_STRCASEEQ(outAuthenticateResp->getPlayerName().c_str(), "Player test name.");
    EXPECT_EQ(outAuthenticateResp->getRoomState(), spcbttl::commun::net::req::State::ERROR_ALREADY_AUTH_STATE);
}

//!
//! @test Checking createRoomReq (pack, unpack, load in RequestLoader, set and get).
//!
TEST (RequestLoader, createRoomReq)
{
    spcbttl::commun::net::req::RequestLoader    requestLoader;
    spcbttl::commun::net::req::CreateRoomReq    inCreateRoomReq;
    msgpack::sbuffer                            sb;

    inCreateRoomReq.setIsViewerAllow(true);
    inCreateRoomReq.setLimitType(spcbttl::commun::engine::TimeLimit::FOURTEEN_MIN);
    inCreateRoomReq.setRoomName("My room name.");
    msgpack::pack(sb, inCreateRoomReq);

    msgpack::object_handle  oh = msgpack::unpack(sb.data(), sb.size());
    msgpack::object         obj = oh.get();

    const std::shared_ptr<spcbttl::commun::net::req::IRequest>    req = requestLoader.load(spcbttl::commun::net::req::Type::CREATE_ROOM_REQ, obj);

    EXPECT_EQ(req->getType(), spcbttl::commun::net::req::Type::CREATE_ROOM_REQ);

    spcbttl::commun::net::req::CreateRoomReq  *outCreateRoomReq(reinterpret_cast<spcbttl::commun::net::req::CreateRoomReq *>(req.get()));

    EXPECT_EQ(outCreateRoomReq->getType(), spcbttl::commun::net::req::Type::CREATE_ROOM_REQ);
    EXPECT_STRCASEEQ(outCreateRoomReq->getRoomName().c_str(), "My room name.");
    EXPECT_EQ(outCreateRoomReq->getLimitType(), spcbttl::commun::engine::TimeLimit::FOURTEEN_MIN);
    EXPECT_TRUE(outCreateRoomReq->isViewerAllow());
}

//!
//! @test Checking createRoomResp (pack, unpack, load in RequestLoader, set and get).
//!
TEST (RequestLoader, createRoomResp)
{
    spcbttl::commun::net::req::RequestLoader    requestLoader;
    spcbttl::commun::net::req::CreateRoomResp   inCreateRoomResp;
    msgpack::sbuffer                            sb;

    inCreateRoomResp.setIsViewerAllow(true);
    inCreateRoomResp.setLimitType(spcbttl::commun::engine::TimeLimit::FOURTEEN_MIN);
    inCreateRoomResp.setRoomName("My room name.");
    inCreateRoomResp.setRoomState(spcbttl::commun::net::req::State::ERROR_INVALID_POSITION_STATE);
    msgpack::pack(sb, inCreateRoomResp);

    msgpack::object_handle  oh = msgpack::unpack(sb.data(), sb.size());
    msgpack::object         obj = oh.get();

    const std::shared_ptr<spcbttl::commun::net::req::IRequest>    req = requestLoader.load(spcbttl::commun::net::req::Type::CREATE_ROOM_RESP, obj);

    EXPECT_EQ(req->getType(), spcbttl::commun::net::req::Type::CREATE_ROOM_RESP);

    spcbttl::commun::net::req::CreateRoomResp  *outCreateRoomResp(reinterpret_cast<spcbttl::commun::net::req::CreateRoomResp *>(req.get()));

    EXPECT_EQ(outCreateRoomResp->getType(), spcbttl::commun::net::req::Type::CREATE_ROOM_RESP);
    EXPECT_STRCASEEQ(outCreateRoomResp->getRoomName().c_str(), "My room name.");
    EXPECT_EQ(outCreateRoomResp->getLimitType(), spcbttl::commun::engine::TimeLimit::FOURTEEN_MIN);
    EXPECT_TRUE(outCreateRoomResp->isViewerAllow());
    EXPECT_EQ(outCreateRoomResp->getRoomState(), spcbttl::commun::net::req::State::ERROR_INVALID_POSITION_STATE);
}

//!
//! @test Checking getRoomListReq (pack, unpack, load in RequestLoader, set and get).
//!
TEST (RequestLoader, getRoomListReq)
{
    spcbttl::commun::net::req::RequestLoader    requestLoader;
    spcbttl::commun::net::req::GetRoomListReq   inGetRoomListReq;
    msgpack::sbuffer                            sb;

    msgpack::pack(sb, inGetRoomListReq);

    msgpack::object_handle  oh = msgpack::unpack(sb.data(), sb.size());
    msgpack::object         obj = oh.get();

    const std::shared_ptr<spcbttl::commun::net::req::IRequest>    req(requestLoader.load(spcbttl::commun::net::req::Type::GET_ROOM_LIST_REQ, obj));

    EXPECT_EQ(req->getType(), spcbttl::commun::net::req::Type::GET_ROOM_LIST_REQ);

    spcbttl::commun::net::req::GetRoomListReq     *outGetRoomListReq = reinterpret_cast<spcbttl::commun::net::req::GetRoomListReq *>(req.get());

    EXPECT_EQ(outGetRoomListReq->getType(), spcbttl::commun::net::req::Type::GET_ROOM_LIST_REQ);
}

//!
//! @test Checking getRoomListResp (pack, unpack, load in RequestLoader, set and get).
//!
TEST (RequestLoader, getRoomListResp)
{
    spcbttl::commun::net::req::RequestLoader    requestLoader;
    spcbttl::commun::net::req::GetRoomListResp  inGetRoomListResp;
    msgpack::sbuffer                            sb;

    inGetRoomListResp.addRoomState("room1", spcbttl::commun::room::State::FINISH);
    inGetRoomListResp.addRoomState("room2", spcbttl::commun::room::State::IN_PROFRESS);
    inGetRoomListResp.addRoomState("room3", spcbttl::commun::room::State::NONE);
    inGetRoomListResp.addRoomState("room4", spcbttl::commun::room::State::NEW);
    msgpack::pack(sb, inGetRoomListResp);

    msgpack::object_handle  oh = msgpack::unpack(sb.data(), sb.size());
    msgpack::object         obj = oh.get();

    const std::shared_ptr<spcbttl::commun::net::req::IRequest>    req(requestLoader.load(spcbttl::commun::net::req::Type::GET_ROOM_LIST_RESP, obj));

    EXPECT_EQ(req->getType(), spcbttl::commun::net::req::Type::GET_ROOM_LIST_RESP);

    spcbttl::commun::net::req::GetRoomListResp                  *outGetRoomListResp = reinterpret_cast<spcbttl::commun::net::req::GetRoomListResp *>(req.get());
    const std::map<std::string, spcbttl::commun::room::State>   rooms = outGetRoomListResp->getRooms();

    EXPECT_EQ(outGetRoomListResp->getType(), spcbttl::commun::net::req::Type::GET_ROOM_LIST_RESP);
    EXPECT_EQ(rooms.size(), static_cast<size_t >(4));
    EXPECT_EQ(rooms.at("room1"), spcbttl::commun::room::State::FINISH);
    EXPECT_EQ(rooms.at("room2"), spcbttl::commun::room::State::IN_PROFRESS);
    EXPECT_EQ(rooms.at("room3"), spcbttl::commun::room::State::NONE);
    EXPECT_EQ(rooms.at("room4"), spcbttl::commun::room::State::NEW);
}

//!
//! @test Checking joinRoomReq (pack, unpack, load in RequestLoader, set and get).
//!
TEST (RequestLoader, joinRoomReq)
{
    spcbttl::commun::net::req::RequestLoader    requestLoader;
    spcbttl::commun::net::req::JoinRoomReq      inJoinRoomReq;
    msgpack::sbuffer                            sb;

    inJoinRoomReq.setRoomName("My room name.");
    msgpack::pack(sb, inJoinRoomReq);

    msgpack::object_handle  oh = msgpack::unpack(sb.data(), sb.size());
    msgpack::object         obj = oh.get();

    const std::shared_ptr<spcbttl::commun::net::req::IRequest>    req = requestLoader.load(spcbttl::commun::net::req::Type::JOIN_ROOM_REQ, obj);

    EXPECT_EQ(req->getType(), spcbttl::commun::net::req::Type::JOIN_ROOM_REQ);

    spcbttl::commun::net::req::JoinRoomReq  *outJoinRoomReq(reinterpret_cast<spcbttl::commun::net::req::JoinRoomReq *>(req.get()));

    EXPECT_EQ(outJoinRoomReq->getType(), spcbttl::commun::net::req::Type::JOIN_ROOM_REQ);
    EXPECT_STRCASEEQ(outJoinRoomReq->getRoomName().c_str(), "My room name.");
}

//!
//! @test Checking joinRoomResp (pack, unpack, load in RequestLoader, set and get).
//!
TEST (RequestLoader, joinRoomResp)
{
    spcbttl::commun::net::req::RequestLoader    requestLoader;
    spcbttl::commun::net::req::JoinRoomResp     inJoinRoomResp;
    msgpack::sbuffer                            sb;

    inJoinRoomResp.setIsViewerAllow(true);
    inJoinRoomResp.setLimitType(spcbttl::commun::engine::TimeLimit::FOURTEEN_MIN);
    inJoinRoomResp.setRoomName("My room name.");
    inJoinRoomResp.setRoomState(spcbttl::commun::net::req::State::ERROR_INVALID_POSITION_STATE);
    msgpack::pack(sb, inJoinRoomResp);

    msgpack::object_handle  oh = msgpack::unpack(sb.data(), sb.size());
    msgpack::object         obj = oh.get();

    const std::shared_ptr<spcbttl::commun::net::req::IRequest>    req = requestLoader.load(spcbttl::commun::net::req::Type::JOIN_ROOM_RESP, obj);

    EXPECT_EQ(req->getType(), spcbttl::commun::net::req::Type::JOIN_ROOM_RESP);

    spcbttl::commun::net::req::JoinRoomResp  *outJoinRoomResp(reinterpret_cast<spcbttl::commun::net::req::JoinRoomResp *>(req.get()));

    EXPECT_EQ(outJoinRoomResp->getType(), spcbttl::commun::net::req::Type::JOIN_ROOM_RESP);
    EXPECT_STRCASEEQ(outJoinRoomResp->getRoomName().c_str(), "My room name.");
    EXPECT_EQ(outJoinRoomResp->getLimitType(), spcbttl::commun::engine::TimeLimit::FOURTEEN_MIN);
    EXPECT_TRUE(outJoinRoomResp->isViewerAllow());
    EXPECT_EQ(outJoinRoomResp->getRoomState(), spcbttl::commun::net::req::State::ERROR_INVALID_POSITION_STATE);
}

//!
//! @test Checking viewRoomReq (pack, unpack, load in RequestLoader, set and get).
//!
TEST (RequestLoader, viewRoomReq)
{
    spcbttl::commun::net::req::RequestLoader    requestLoader;
    spcbttl::commun::net::req::ViewRoomReq      inViewRoomReq;
    msgpack::sbuffer                            sb;

    inViewRoomReq.setRoomName("My room name.");
    msgpack::pack(sb, inViewRoomReq);

    msgpack::object_handle  oh = msgpack::unpack(sb.data(), sb.size());
    msgpack::object         obj = oh.get();

    const std::shared_ptr<spcbttl::commun::net::req::IRequest>    req = requestLoader.load(spcbttl::commun::net::req::Type::VIEW_ROOM_REQ, obj);

    EXPECT_EQ(req->getType(), spcbttl::commun::net::req::Type::VIEW_ROOM_REQ);

    spcbttl::commun::net::req::ViewRoomReq  *outViewRoomReq(reinterpret_cast<spcbttl::commun::net::req::ViewRoomReq *>(req.get()));

    EXPECT_EQ(outViewRoomReq->getType(), spcbttl::commun::net::req::Type::VIEW_ROOM_REQ);
    EXPECT_STRCASEEQ(outViewRoomReq->getRoomName().c_str(), "My room name.");
}

//!
//! @test Checking viewRoomResp (pack, unpack, load in RequestLoader, set and get).
//!
TEST (RequestLoader, viewRoomResp)
{
    spcbttl::commun::net::req::RequestLoader    requestLoader;
    spcbttl::commun::net::req::ViewRoomResp     inViewRoomResp;
    msgpack::sbuffer                            sb;

    inViewRoomResp.setRoomName("My room name.");
    inViewRoomResp.setRoomState(spcbttl::commun::net::req::State::ERROR_INVALID_POSITION_STATE);
    msgpack::pack(sb, inViewRoomResp);

    msgpack::object_handle  oh = msgpack::unpack(sb.data(), sb.size());
    msgpack::object         obj = oh.get();

    const std::shared_ptr<spcbttl::commun::net::req::IRequest>    req = requestLoader.load(spcbttl::commun::net::req::Type::VIEW_ROOM_RESP, obj);

    EXPECT_EQ(req->getType(), spcbttl::commun::net::req::Type::VIEW_ROOM_RESP);

    spcbttl::commun::net::req::ViewRoomResp  *outViewRoomResp(reinterpret_cast<spcbttl::commun::net::req::ViewRoomResp *>(req.get()));

    EXPECT_EQ(outViewRoomResp->getType(), spcbttl::commun::net::req::Type::VIEW_ROOM_RESP);
    EXPECT_STRCASEEQ(outViewRoomResp->getRoomName().c_str(), "My room name.");
    EXPECT_EQ(outViewRoomResp->getRoomState(), spcbttl::commun::net::req::State::ERROR_INVALID_POSITION_STATE);
}

//!
//! @test Checking exitRoomReq (pack, unpack, load in RequestLoader, set and get).
//!
TEST (RequestLoader, exitRoomReq)
{
    spcbttl::commun::net::req::RequestLoader    requestLoader;
    spcbttl::commun::net::req::ExitRoomReq      inExitRoomReq;
    msgpack::sbuffer                            sb;

    inExitRoomReq.setRoomName("My room name.");
    msgpack::pack(sb, inExitRoomReq);

    msgpack::object_handle  oh = msgpack::unpack(sb.data(), sb.size());
    msgpack::object         obj = oh.get();

    const std::shared_ptr<spcbttl::commun::net::req::IRequest>    req = requestLoader.load(spcbttl::commun::net::req::Type::EXIT_ROOM_REQ, obj);

    EXPECT_EQ(req->getType(), spcbttl::commun::net::req::Type::EXIT_ROOM_REQ);

    spcbttl::commun::net::req::ExitRoomReq  *outExitRoomReq(reinterpret_cast<spcbttl::commun::net::req::ExitRoomReq *>(req.get()));

    EXPECT_EQ(outExitRoomReq->getType(), spcbttl::commun::net::req::Type::EXIT_ROOM_REQ);
    EXPECT_STRCASEEQ(outExitRoomReq->getRoomName().c_str(), "My room name.");
}

//!
//! @test Checking launchGameReq (pack, unpack, load in RequestLoader, set and get).
//!
TEST (RequestLoader, launchGameReq)
{
    spcbttl::commun::net::req::RequestLoader    requestLoader;
    spcbttl::commun::net::req::LaunchGameReq    inLaunchGameReq;
    msgpack::sbuffer                            sb;

    msgpack::pack(sb, inLaunchGameReq);

    msgpack::object_handle  oh = msgpack::unpack(sb.data(), sb.size());
    msgpack::object         obj = oh.get();

    const std::shared_ptr<spcbttl::commun::net::req::IRequest>    req(requestLoader.load(spcbttl::commun::net::req::Type::LAUNCH_GAME_REQ, obj));

    EXPECT_EQ(req->getType(), spcbttl::commun::net::req::Type::LAUNCH_GAME_REQ);

    spcbttl::commun::net::req::LaunchGameReq     *outLaunchGameReq = reinterpret_cast<spcbttl::commun::net::req::LaunchGameReq *>(req.get());

    EXPECT_EQ(outLaunchGameReq->getType(), spcbttl::commun::net::req::Type::LAUNCH_GAME_REQ);
}

//!
//! @test Checking launchGameResp (pack, unpack, load in RequestLoader, set and get).
//!
TEST (RequestLoader, launchGameResp)
{
    spcbttl::commun::net::req::RequestLoader    requestLoader;
    spcbttl::commun::net::req::LaunchGameResp   inLaunchGameResp;
    msgpack::sbuffer                            sb;

    inLaunchGameResp.setState(spcbttl::commun::net::req::State::ERROR_INVALID_POSITION_STATE);
    msgpack::pack(sb, inLaunchGameResp);

    msgpack::object_handle  oh = msgpack::unpack(sb.data(), sb.size());
    msgpack::object         obj = oh.get();

    const std::shared_ptr<spcbttl::commun::net::req::IRequest>    req = requestLoader.load(spcbttl::commun::net::req::Type::LAUNCH_GAME_RESP, obj);

    EXPECT_EQ(req->getType(), spcbttl::commun::net::req::Type::LAUNCH_GAME_RESP);

    spcbttl::commun::net::req::LaunchGameResp  *outLaunchGameResp(reinterpret_cast<spcbttl::commun::net::req::LaunchGameResp *>(req.get()));

    EXPECT_EQ(outLaunchGameResp->getType(), spcbttl::commun::net::req::Type::LAUNCH_GAME_RESP);
    EXPECT_EQ(outLaunchGameResp->getRoomState(), spcbttl::commun::net::req::State::ERROR_INVALID_POSITION_STATE);
}

//!
//! @test Checking getLobbyStateUpdateResp (pack, unpack, load in RequestLoader, set and get).
//!
TEST (RequestLoader, getLobbyStateUpdateResp)
{
    spcbttl::commun::net::req::RequestLoader        requestLoader;
    spcbttl::commun::net::req::LobbyStateUpdateResp inLobbyStateUpdateResp;
    msgpack::sbuffer                                sb;

    inLobbyStateUpdateResp.addPlayerState("player1", spcbttl::commun::engine::ClientState::PLAYER);
    inLobbyStateUpdateResp.addPlayerState("player2", spcbttl::commun::engine::ClientState::VIEWER);
    inLobbyStateUpdateResp.addPlayerState("player3", spcbttl::commun::engine::ClientState::PLAYER);
    inLobbyStateUpdateResp.addPlayerState("player4", spcbttl::commun::engine::ClientState::PLAYER);
    msgpack::pack(sb, inLobbyStateUpdateResp);

    msgpack::object_handle  oh = msgpack::unpack(sb.data(), sb.size());
    msgpack::object         obj = oh.get();

    const std::shared_ptr<spcbttl::commun::net::req::IRequest>    req(requestLoader.load(spcbttl::commun::net::req::Type::LOBBY_STATE_UPDATE_RESP, obj));

    EXPECT_EQ(req->getType(), spcbttl::commun::net::req::Type::LOBBY_STATE_UPDATE_RESP);

    spcbttl::commun::net::req::LobbyStateUpdateResp             *outLobbyStateUpdateResp = reinterpret_cast<spcbttl::commun::net::req::LobbyStateUpdateResp *>(req.get());
    const std::map<std::string, spcbttl::commun::engine::ClientState>   rooms = outLobbyStateUpdateResp->getPlayers();

    EXPECT_EQ(outLobbyStateUpdateResp->getType(), spcbttl::commun::net::req::Type::LOBBY_STATE_UPDATE_RESP);
    EXPECT_EQ(rooms.size(), static_cast<size_t >(4));
    EXPECT_EQ(rooms.at("player1"), spcbttl::commun::engine::ClientState::PLAYER);
    EXPECT_EQ(rooms.at("player2"), spcbttl::commun::engine::ClientState::VIEWER);
    EXPECT_EQ(rooms.at("player3"), spcbttl::commun::engine::ClientState::PLAYER);
    EXPECT_EQ(rooms.at("player4"), spcbttl::commun::engine::ClientState::PLAYER);
}

//!
//! @test Checking SetUserBattleshipReq (pack, unpack, load in RequestLoader, set and get).
//!
TEST (RequestLoader, setUserBattleShipReq)
{
    spcbttl::commun::net::req::RequestLoader        requestLoader;
    spcbttl::commun::net::req::SetUserBattleshipReq inSetUserBattleShipReq;
    msgpack::sbuffer                                sb;
    spcbttl::commun::engine::Ships                  inShips;
    spcbttl::commun::engine::Ships                  outShip;

    inShips.mDestroyer = 2;
    inShips.mSubmarine = spcbttl::commun::engine::Ship::Submarine({2, 4});
    inShips.mCruiser1 = spcbttl::commun::engine::Ship::Cruiser({2, 4, 1});
    inShips.mCruiser2 = spcbttl::commun::engine::Ship::Cruiser({10, 78, 3});
    inShips.mBattleship = spcbttl::commun::engine::Ship::Battleship({39, 98, 4, 3});
    inShips.mCarrier = spcbttl::commun::engine::Ship::Carrier({2, 4, 7, 98, 3});
    inSetUserBattleShipReq.setShips(inShips);
    msgpack::pack(sb, inSetUserBattleShipReq);

    msgpack::object_handle  oh = msgpack::unpack(sb.data(), sb.size());
    msgpack::object         obj = oh.get();

    const std::shared_ptr<spcbttl::commun::net::req::IRequest>    req(requestLoader.load(spcbttl::commun::net::req::Type::SET_USER_BATTLESHIP_REQ, obj));

    EXPECT_EQ(req->getType(), spcbttl::commun::net::req::Type::SET_USER_BATTLESHIP_REQ);

    spcbttl::commun::net::req::SetUserBattleshipReq     *outSetUserBattleShipReq = reinterpret_cast<spcbttl::commun::net::req::SetUserBattleshipReq *>(req.get());

    outShip = outSetUserBattleShipReq->getShips();
    EXPECT_EQ(outSetUserBattleShipReq->getType(), spcbttl::commun::net::req::Type::SET_USER_BATTLESHIP_REQ);
    EXPECT_EQ(outShip.mDestroyer, static_cast<size_t>(2));
    EXPECT_EQ(outShip.mSubmarine[0], static_cast<size_t>(2));
    EXPECT_EQ(outShip.mSubmarine[1], static_cast<size_t>(4));
    EXPECT_EQ(outShip.mCruiser1[0], static_cast<size_t>(2));
    EXPECT_EQ(outShip.mCruiser1[1], static_cast<size_t>(4));
    EXPECT_EQ(outShip.mCruiser1[2], static_cast<size_t>(1));
    EXPECT_EQ(outShip.mCruiser2[0], static_cast<size_t>(10));
    EXPECT_EQ(outShip.mCruiser2[1], static_cast<size_t>(78));
    EXPECT_EQ(outShip.mCruiser2[2], static_cast<size_t>(3));
    EXPECT_EQ(outShip.mBattleship[0], static_cast<size_t>(39));
    EXPECT_EQ(outShip.mBattleship[1], static_cast<size_t>(98));
    EXPECT_EQ(outShip.mBattleship[2], static_cast<size_t>(4));
    EXPECT_EQ(outShip.mBattleship[3], static_cast<size_t>(3));
    EXPECT_EQ(outShip.mCarrier[0], static_cast<size_t>(2));
    EXPECT_EQ(outShip.mCarrier[1], static_cast<size_t>(4));
    EXPECT_EQ(outShip.mCarrier[2], static_cast<size_t>(7));
    EXPECT_EQ(outShip.mCarrier[3], static_cast<size_t>(98));
    EXPECT_EQ(outShip.mCarrier[4], static_cast<size_t>(3));
}

//!
//! @test Checking SetUserBattleshipResp (pack, unpack, load in RequestLoader, set and get).
//!
TEST (RequestLoader, SetUserBattleshipResp)
{
    spcbttl::commun::net::req::RequestLoader            requestLoader;
    spcbttl::commun::net::req::SetUserBattleshipResp    inSetUserBattleShipResp;
    msgpack::sbuffer                                    sb;
    spcbttl::commun::engine::Ships                      inShips;
    spcbttl::commun::engine::Ships                      outShip;
    unsigned short                                      id = 10;

    inShips.mDestroyer = 2;
    inShips.mSubmarine = spcbttl::commun::engine::Ship::Submarine({2, 4});
    inShips.mCruiser1 = spcbttl::commun::engine::Ship::Cruiser({2, 4, 1});
    inShips.mCruiser2 = spcbttl::commun::engine::Ship::Cruiser({10, 78, 3});
    inShips.mBattleship = spcbttl::commun::engine::Ship::Battleship({39, 98, 4, 3});
    inShips.mCarrier = spcbttl::commun::engine::Ship::Carrier({2, 4, 7, 98, 3});
    inSetUserBattleShipResp.setShips(inShips);
    inSetUserBattleShipResp.setState(spcbttl::commun::net::req::State::ERROR_ALREADY_AUTH_STATE);
    inSetUserBattleShipResp.setDestClientID(id);
    msgpack::pack(sb, inSetUserBattleShipResp);

    msgpack::object_handle  oh = msgpack::unpack(sb.data(), sb.size());
    msgpack::object         obj = oh.get();

    const std::shared_ptr<spcbttl::commun::net::req::IRequest>    req(requestLoader.load(spcbttl::commun::net::req::Type::SET_USER_BATTLESHIP_RESP, obj));

    EXPECT_EQ(req->getType(), spcbttl::commun::net::req::Type::SET_USER_BATTLESHIP_RESP);

    spcbttl::commun::net::req::SetUserBattleshipResp     *outSetUserBattleShipResp = reinterpret_cast<spcbttl::commun::net::req::SetUserBattleshipResp *>(req.get());

    outShip = outSetUserBattleShipResp->getShips();
    EXPECT_EQ(outSetUserBattleShipResp->getType(), spcbttl::commun::net::req::Type::SET_USER_BATTLESHIP_RESP);
    EXPECT_EQ(outSetUserBattleShipResp->getState(), spcbttl::commun::net::req::State::ERROR_ALREADY_AUTH_STATE);
    EXPECT_EQ(outSetUserBattleShipResp->getDestClientID(), id);
    EXPECT_EQ(outShip.mDestroyer, static_cast<size_t>(2));
    EXPECT_EQ(outShip.mSubmarine[0], static_cast<size_t>(2));
    EXPECT_EQ(outShip.mSubmarine[1], static_cast<size_t>(4));
    EXPECT_EQ(outShip.mCruiser1[0], static_cast<size_t>(2));
    EXPECT_EQ(outShip.mCruiser1[1], static_cast<size_t>(4));
    EXPECT_EQ(outShip.mCruiser1[2], static_cast<size_t>(1));
    EXPECT_EQ(outShip.mCruiser2[0], static_cast<size_t>(10));
    EXPECT_EQ(outShip.mCruiser2[1], static_cast<size_t>(78));
    EXPECT_EQ(outShip.mCruiser2[2], static_cast<size_t>(3));
    EXPECT_EQ(outShip.mBattleship[0], static_cast<size_t>(39));
    EXPECT_EQ(outShip.mBattleship[1], static_cast<size_t>(98));
    EXPECT_EQ(outShip.mBattleship[2], static_cast<size_t>(4));
    EXPECT_EQ(outShip.mBattleship[3], static_cast<size_t>(3));
    EXPECT_EQ(outShip.mCarrier[0], static_cast<size_t>(2));
    EXPECT_EQ(outShip.mCarrier[1], static_cast<size_t>(4));
    EXPECT_EQ(outShip.mCarrier[2], static_cast<size_t>(7));
    EXPECT_EQ(outShip.mCarrier[3], static_cast<size_t>(98));
    EXPECT_EQ(outShip.mCarrier[4], static_cast<size_t>(3));
}

//!
//! @test Checking sendChatMsgReq (pack, unpack, load in RequestLoader, set and get).
//!
TEST (RequestLoader, sendChatMsgReq)
{
    spcbttl::commun::net::req::RequestLoader    requestLoader;
    spcbttl::commun::net::req::SendChatMsgReq   inSendChatMsgReq;
    msgpack::sbuffer                            sb;

    inSendChatMsgReq.setChanelType(spcbttl::commun::engine::ChanelType::GAME);
    inSendChatMsgReq.setMessage("My message ...");
    msgpack::pack(sb, inSendChatMsgReq);

    msgpack::object_handle  oh = msgpack::unpack(sb.data(), sb.size());
    msgpack::object         obj = oh.get();

    const std::shared_ptr<spcbttl::commun::net::req::IRequest>    req(requestLoader.load(spcbttl::commun::net::req::Type::SEND_CHAT_MSG_REQ, obj));

    EXPECT_EQ(req->getType(), spcbttl::commun::net::req::Type::SEND_CHAT_MSG_REQ);

    spcbttl::commun::net::req::SendChatMsgReq     *outSendChatMsgReq = reinterpret_cast<spcbttl::commun::net::req::SendChatMsgReq *>(req.get());

    EXPECT_EQ(outSendChatMsgReq->getType(), spcbttl::commun::net::req::Type::SEND_CHAT_MSG_REQ);
    EXPECT_EQ(outSendChatMsgReq->getChanelType(), spcbttl::commun::engine::ChanelType::GAME);
    EXPECT_STRCASEEQ(outSendChatMsgReq->getMessage().c_str(), "My message ...");
}

//!
//! @test Checking broadcastChatMsgResp (pack, unpack, load in RequestLoader, set and get).
//!
TEST (RequestLoader, broadcastChatMsgResp)
{
    spcbttl::commun::net::req::RequestLoader        requestLoader;
    spcbttl::commun::net::req::BroadcastChatMsgResp inBroadcastChatMsgResp;
    msgpack::sbuffer                                sb;

    inBroadcastChatMsgResp.setChanelType(spcbttl::commun::engine::ChanelType::GENERAL);
    inBroadcastChatMsgResp.setMessage("My message ...");
    msgpack::pack(sb, inBroadcastChatMsgResp);

    msgpack::object_handle  oh = msgpack::unpack(sb.data(), sb.size());
    msgpack::object         obj = oh.get();

    const std::shared_ptr<spcbttl::commun::net::req::IRequest>    req(requestLoader.load(spcbttl::commun::net::req::Type::BROADCAST_CHAT_MSG_REQ, obj));

    EXPECT_EQ(req->getType(), spcbttl::commun::net::req::Type::BROADCAST_CHAT_MSG_REQ);

    spcbttl::commun::net::req::BroadcastChatMsgResp     *outBroadcastChatMsgResp = reinterpret_cast<spcbttl::commun::net::req::BroadcastChatMsgResp *>(req.get());

    EXPECT_EQ(outBroadcastChatMsgResp->getType(), spcbttl::commun::net::req::Type::BROADCAST_CHAT_MSG_REQ);
    EXPECT_EQ(outBroadcastChatMsgResp->getChanelType(), spcbttl::commun::engine::ChanelType::GENERAL);
    EXPECT_STRCASEEQ(outBroadcastChatMsgResp->getMessage().c_str(), "My message ...");
}

//!
//! @test Checking shootShipReq (pack, unpack, load in RequestLoader, set and get).
//!
TEST (RequestLoader, shootShipReq)
{
    spcbttl::commun::net::req::RequestLoader    requestLoader;
    spcbttl::commun::net::req::ShootShipReq     inShootShipReq;
    msgpack::sbuffer                            sb;

    inShootShipReq.setShootPos(3);
    msgpack::pack(sb, inShootShipReq);

    msgpack::object_handle  oh = msgpack::unpack(sb.data(), sb.size());
    msgpack::object         obj = oh.get();

    const std::shared_ptr<spcbttl::commun::net::req::IRequest>    req(requestLoader.load(spcbttl::commun::net::req::Type::SHOOT_SHIP_REQ, obj));

    EXPECT_EQ(req->getType(), spcbttl::commun::net::req::Type::SHOOT_SHIP_REQ);

    spcbttl::commun::net::req::ShootShipReq     *outBroadcastChatMsgResp = reinterpret_cast<spcbttl::commun::net::req::ShootShipReq *>(req.get());

    EXPECT_EQ(outBroadcastChatMsgResp->getType(), spcbttl::commun::net::req::Type::SHOOT_SHIP_REQ);
    EXPECT_EQ(outBroadcastChatMsgResp->getShootPos(), static_cast<size_t>(3));
}

//!
//! @test Checking shootShipResp (pack, unpack, load in RequestLoader, set and get).
//!
TEST (RequestLoader, shootShipResp)
{
    spcbttl::commun::net::req::RequestLoader    requestLoader;
    spcbttl::commun::net::req::ShootShipResp    inShootShipResp;
    msgpack::sbuffer                            sb;

    inShootShipResp.setShootPos(4);
    inShootShipResp.setShootClientId(10);
    inShootShipResp.setShootState(spcbttl::commun::engine::ShootState::IMPACTED);
    msgpack::pack(sb, inShootShipResp);

    msgpack::object_handle  oh = msgpack::unpack(sb.data(), sb.size());
    msgpack::object         obj = oh.get();

    const std::shared_ptr<spcbttl::commun::net::req::IRequest>    req(requestLoader.load(spcbttl::commun::net::req::Type::SHOOT_SHIP_RESP, obj));

    EXPECT_EQ(req->getType(), spcbttl::commun::net::req::Type::SHOOT_SHIP_RESP);

    spcbttl::commun::net::req::ShootShipResp     *outShootShipResp = reinterpret_cast<spcbttl::commun::net::req::ShootShipResp *>(req.get());

    EXPECT_EQ(outShootShipResp->getType(), spcbttl::commun::net::req::Type::SHOOT_SHIP_RESP);
    EXPECT_EQ(outShootShipResp->getShootPos(), static_cast<size_t>(4));
    EXPECT_EQ(outShootShipResp->getShootClientId(), static_cast<size_t>(10));
    EXPECT_EQ(outShootShipResp->getShootState(), spcbttl::commun::engine::ShootState::IMPACTED);
}

//!
//! @test Checking endGameStatusReq (pack, unpack, load in RequestLoader, set and get).
//!
TEST (RequestLoader, endGameStatusReq)
{
    spcbttl::commun::net::req::RequestLoader    requestLoader;
    spcbttl::commun::net::req::EndGameStatusReq inEndGameStatusReq;
    msgpack::sbuffer                            sb;

    inEndGameStatusReq.setFinalGameStatus(spcbttl::commun::engine::FinalGameStatus::LOOSE);
    msgpack::pack(sb, inEndGameStatusReq);

    msgpack::object_handle  oh = msgpack::unpack(sb.data(), sb.size());
    msgpack::object         obj = oh.get();

    const std::shared_ptr<spcbttl::commun::net::req::IRequest>    req(requestLoader.load(spcbttl::commun::net::req::Type::END_GAME_STATUS_REQ, obj));

    EXPECT_EQ(req->getType(), spcbttl::commun::net::req::Type::END_GAME_STATUS_REQ);

    spcbttl::commun::net::req::EndGameStatusReq     *outEndGameStatusReq = reinterpret_cast<spcbttl::commun::net::req::EndGameStatusReq *>(req.get());

    EXPECT_EQ(outEndGameStatusReq->getType(), spcbttl::commun::net::req::Type::END_GAME_STATUS_REQ);
    EXPECT_EQ(outEndGameStatusReq->getFinalGameStatus(), spcbttl::commun::engine::FinalGameStatus::LOOSE);
}

//!
//! @test Checking gameReadyToLaunchReq (pack, unpack, load in RequestLoader, set and get).
//!
TEST (RequestLoader, gameReadyToLaunchReq)
{
    spcbttl::commun::net::req::RequestLoader        requestLoader;
    spcbttl::commun::net::req::GameReadyToLaunchReq inGameReadyToLaunchReq;
    msgpack::sbuffer                                sb;

    msgpack::pack(sb, inGameReadyToLaunchReq);

    msgpack::object_handle  oh = msgpack::unpack(sb.data(), sb.size());
    msgpack::object         obj = oh.get();

    const std::shared_ptr<spcbttl::commun::net::req::IRequest>    req(requestLoader.load(spcbttl::commun::net::req::Type::GAME_READY_TO_LAUNCH_REQ, obj));

    EXPECT_EQ(req->getType(), spcbttl::commun::net::req::Type::GAME_READY_TO_LAUNCH_REQ);

    spcbttl::commun::net::req::GameReadyToLaunchReq     *outGameReadyToLaunch = reinterpret_cast<spcbttl::commun::net::req::GameReadyToLaunchReq *>(req.get());

    EXPECT_EQ(outGameReadyToLaunch->getType(), spcbttl::commun::net::req::Type::GAME_READY_TO_LAUNCH_REQ);
}

//!
//! @test Checking yourTurnToPlayerReq (pack, unpack, load in RequestLoader, set and get).
//!
TEST (RequestLoader, yourTurnToPlayerReq)
{
    spcbttl::commun::net::req::RequestLoader        requestLoader;
    spcbttl::commun::net::req::YourTurnToPlayReq    inYourTurnToPlayReq;
    msgpack::sbuffer                                sb;

    msgpack::pack(sb, inYourTurnToPlayReq);

    msgpack::object_handle  oh = msgpack::unpack(sb.data(), sb.size());
    msgpack::object         obj = oh.get();

    const std::shared_ptr<spcbttl::commun::net::req::IRequest>    req(requestLoader.load(spcbttl::commun::net::req::Type::YOUR_TURN_TO_PLAY_REQ, obj));

    EXPECT_EQ(req->getType(), spcbttl::commun::net::req::Type::YOUR_TURN_TO_PLAY_REQ);

    spcbttl::commun::net::req::YourTurnToPlayReq     *outYourTurnToPlayReq = reinterpret_cast<spcbttl::commun::net::req::YourTurnToPlayReq *>(req.get());

    EXPECT_EQ(outYourTurnToPlayReq->getType(), spcbttl::commun::net::req::Type::YOUR_TURN_TO_PLAY_REQ);
}

//!
//! @test Give bad type to loader.
//!
TEST (RequestLoader, badType)
{
    spcbttl::commun::net::req::RequestLoader    requestLoader;
    spcbttl::commun::net::req::KeepAliveReq     inKeepAliveReq;
    msgpack::sbuffer                            sb;

    msgpack::pack(sb, inKeepAliveReq);

    msgpack::object_handle  oh = msgpack::unpack(sb.data(), sb.size());
    msgpack::object         obj = oh.get();

    const std::shared_ptr<spcbttl::commun::net::req::IRequest>    req(requestLoader.load(spcbttl::commun::net::req::Type::CREATE_ROOM_REQ, obj));

    EXPECT_EQ(req->getType(), spcbttl::commun::net::req::Type::CREATE_ROOM_REQ);
}
