//!
//! @file RequestLoader.cpp
//! @author jbruel
//! @date 12/11/18
//!

#include "Commun/Network/Requests/RequestLoader.hpp"
#include "Commun/Network/Requests/Requests.hpp"
#include "Commun/Exception/NetworkException.hpp"
#include <Commun/Tools/Log/Idx.hpp>
#include <plog/Log.h>

namespace spcbttl
{
namespace commun
{
namespace net
{
namespace req
{

    const std::shared_ptr<IRequest> RequestLoader::load(Type requestType, msgpack::object &obj) const
    {
        if (mRequestsFunctionsLoader.count(requestType) < 1)
            throw spcbttl::NetworkException("A not handling type has been try to be loaded : " + std::to_string(requestType));
        return (mRequestsFunctionsLoader.at(requestType)(obj));
    }

    const std::shared_ptr<IRequest> RequestLoader::makeKeepAliveReq(msgpack::object &obj)
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "A Keep alive request is loading.";
        return (std::make_shared<KeepAliveReq>(obj.as<KeepAliveReq>()));
    }

    const std::shared_ptr<IRequest> RequestLoader::makeAuthenticateReq(msgpack::object &obj)
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "A Authenticate request is loading.";
        return (std::make_shared<AuthenticateReq>(obj.as<AuthenticateReq>()));
    }

    const std::shared_ptr<IRequest> RequestLoader::makeAuthenticateResp(msgpack::object &obj)
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "A Authenticate response is loading.";
        return (std::make_shared<AuthenticateResp>(obj.as<AuthenticateResp>()));
    }

    const std::shared_ptr<IRequest> RequestLoader::makeGetRoomListReq(msgpack::object &obj)
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "A Get Room List request is loading.";
        return (std::make_shared<GetRoomListReq>(obj.as<GetRoomListReq>()));
    }

    const std::shared_ptr<IRequest> RequestLoader::makeGetRoomListResp(msgpack::object &obj)
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "A Get Room List response is loading.";
        return (std::make_shared<GetRoomListResp>(obj.as<GetRoomListResp>()));
    }

    const std::shared_ptr<IRequest> RequestLoader::makeCreateRoomReq(msgpack::object &obj)
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "A Create Room request is loading.";
        return (std::make_shared<CreateRoomReq>(obj.as<CreateRoomReq>()));
    }

    const std::shared_ptr<IRequest> RequestLoader::makeCreateRoomResp(msgpack::object &obj)
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "A Create Room response request is loading.";
        return (std::make_shared<CreateRoomResp>(obj.as<CreateRoomResp>()));
    }

    const std::shared_ptr<IRequest> RequestLoader::makeJoinRoomReq(msgpack::object &obj)
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "A Join Room request is loading.";
        return (std::make_shared<JoinRoomReq>(obj.as<JoinRoomReq>()));
    }

    const std::shared_ptr<IRequest> RequestLoader::makeJoinRoomResp(msgpack::object &obj)
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "A Join Room response is loading.";
        return (std::make_shared<JoinRoomResp>(obj.as<JoinRoomResp>()));
    }

    const std::shared_ptr<IRequest> RequestLoader::makeViewRoomReq(msgpack::object &obj)
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "A View room request is loading.";
        return (std::make_shared<ViewRoomReq>(obj.as<ViewRoomReq>()));
    }

    const std::shared_ptr<IRequest> RequestLoader::makeViewRoomResp(msgpack::object &obj)
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "A View room response is loading.";
        return (std::make_shared<ViewRoomResp>(obj.as<ViewRoomResp>()));
    }

    const std::shared_ptr<IRequest> RequestLoader::makeExitRoomReq(msgpack::object &obj)
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "A Exist Room request is loading.";
        return (std::make_shared<ExitRoomReq>(obj.as<ExitRoomReq>()));
    }

    const std::shared_ptr<IRequest> RequestLoader::makeLaunchGameReq(msgpack::object &obj)
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "A Launch Game request is loading.";
        return (std::make_shared<LaunchGameReq>(obj.as<LaunchGameReq>()));
    }

    const std::shared_ptr<IRequest> RequestLoader::makeLaunchGameResp(msgpack::object &obj)
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "A Launch Game response is loading.";
        return (std::make_shared<LaunchGameResp>(obj.as<LaunchGameResp>()));
    }

    const std::shared_ptr<IRequest> RequestLoader::makeLobbyStateUpdateResp(msgpack::object &obj)
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "A Lobby State Update response is loading.";
        return (std::make_shared<LobbyStateUpdateResp>(obj.as<LobbyStateUpdateResp>()));
    }

    const std::shared_ptr<IRequest> RequestLoader::makeSetUserBattleshipReq(msgpack::object &obj)
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "A Set User Battleship request is loading.";
        return (std::make_shared<SetUserBattleshipReq>(obj.as<SetUserBattleshipReq>()));
    }

    const std::shared_ptr<IRequest> RequestLoader::makeSetUserBattleshipResp(msgpack::object &obj)
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "A Set User Battleship response is loading.";
        return (std::make_shared<SetUserBattleshipResp>(obj.as<SetUserBattleshipResp>()));
    }

    const std::shared_ptr<IRequest> RequestLoader::makeSendChatMsgReq(msgpack::object &obj)
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "A Send Chat Message request is loading.";
        return (std::make_shared<SendChatMsgReq>(obj.as<SendChatMsgReq>()));
    }

    const std::shared_ptr<IRequest> RequestLoader::makeBroadcastChatMsgReq(msgpack::object &obj)
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "A Broadcast Chat Message request is loading.";
        return (std::make_shared<BroadcastChatMsgResp>(obj.as<BroadcastChatMsgResp>()));
    }

    const std::shared_ptr<IRequest> RequestLoader::makeShootShipReq(msgpack::object &obj)
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "A Shoot Ship request is loading.";
        return (std::make_shared<ShootShipReq>(obj.as<ShootShipReq>()));
    }

    const std::shared_ptr<IRequest> RequestLoader::makeShootShipResp(msgpack::object &obj)
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "A Shoot Ship response is loading.";
        return (std::make_shared<ShootShipResp>(obj.as<ShootShipResp>()));
    }

    const std::shared_ptr<IRequest> RequestLoader::makeGameReadyToLaunchReq(msgpack::object &obj)
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "A Game Ready To Launch request is loading.";
        return (std::make_shared<GameReadyToLaunchReq>(obj.as<GameReadyToLaunchReq>()));
    }

    const std::shared_ptr<IRequest> RequestLoader::makeYourTurnToPlayReq(msgpack::object &obj)
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "A Your Turn To Play request is loading.";
        return (std::make_shared<YourTurnToPlayReq>(obj.as<YourTurnToPlayReq>()));
    }

    const std::shared_ptr<IRequest> RequestLoader::makeEndGameStatusReq(msgpack::object &obj)
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "A End Game Status request is loading.";
        return (std::make_shared<EndGameStatusReq>(obj.as<EndGameStatusReq>()));
    }

    const std::shared_ptr<IRequest> RequestLoader::makeNone(msgpack::object &)
    {
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::error) << "A none request has been try to be loaded.";
        throw spcbttl::NetworkException("A None request has been catch by the request loader.");
    }

}
}
}
}