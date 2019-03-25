//!
//! @file RequestLoader.hpp
//! @author jbruel
//! @date 12/11/18
//!

#ifndef SPACEBATTLE_CLIENT_REQUESTLOADER_HPP
# define SPACEBATTLE_CLIENT_REQUESTLOADER_HPP

# include "Commun/Network/Requests/IRequest.hpp"
# include <functional>

//!
//! @namespace spcbttl
//!
namespace spcbttl
{
//!
//! @namespace commun
//!
namespace commun
{
//!
//! @namespace net
//!
namespace net
{
//!
//! @namespace req
//!
namespace req
{

    //!
    //! @class RequestLoader
    //! @brief Request loader.
    //!
    class   RequestLoader
    {
    private:
        const std::unordered_map<Type, std::function<const std::shared_ptr<IRequest> (msgpack::object &)>>    mRequestsFunctionsLoader = {
                { Type::KEEP_ALIVE_REQ, std::bind(makeKeepAliveReq, std::placeholders::_1) },
                { Type::AUTHENTICATE_REQ, std::bind(makeAuthenticateReq, std::placeholders::_1) },
                { Type::AUTHENTICATE_RESP, std::bind(makeAuthenticateResp, std::placeholders::_1) },
                { Type::GET_ROOM_LIST_REQ, std::bind(makeGetRoomListReq, std::placeholders::_1) },
                { Type::GET_ROOM_LIST_RESP, std::bind(makeGetRoomListResp, std::placeholders::_1) },
                { Type::CREATE_ROOM_REQ, std::bind(makeCreateRoomReq, std::placeholders::_1) },
                { Type::CREATE_ROOM_RESP, std::bind(makeCreateRoomResp, std::placeholders::_1) },
                { Type::JOIN_ROOM_REQ, std::bind(makeJoinRoomReq, std::placeholders::_1) },
                { Type::JOIN_ROOM_RESP, std::bind(makeJoinRoomResp, std::placeholders::_1) },
                { Type::VIEW_ROOM_REQ, std::bind(makeViewRoomReq, std::placeholders::_1) },
                { Type::VIEW_ROOM_RESP, std::bind(makeViewRoomResp, std::placeholders::_1) },
                { Type::EXIT_ROOM_REQ, std::bind(makeExitRoomReq, std::placeholders::_1) },
                { Type::LAUNCH_GAME_REQ, std::bind(makeLaunchGameReq, std::placeholders::_1) },
                { Type::LAUNCH_GAME_RESP, std::bind(makeLaunchGameResp, std::placeholders::_1) },
                { Type::LOBBY_STATE_UPDATE_RESP, std::bind(makeLobbyStateUpdateResp, std::placeholders::_1) },
                { Type::SET_USER_BATTLESHIP_REQ, std::bind(makeSetUserBattleshipReq, std::placeholders::_1) },
                { Type::SET_USER_BATTLESHIP_RESP, std::bind(makeSetUserBattleshipResp, std::placeholders::_1) },
                { Type::SEND_CHAT_MSG_REQ, std::bind(makeSendChatMsgReq, std::placeholders::_1) },
                { Type::BROADCAST_CHAT_MSG_REQ, std::bind(makeBroadcastChatMsgReq, std::placeholders::_1) },
                { Type::SHOOT_SHIP_REQ, std::bind(makeShootShipReq, std::placeholders::_1) },
                { Type::SHOOT_SHIP_RESP, std::bind(makeShootShipResp, std::placeholders::_1) },
                { Type::GAME_READY_TO_LAUNCH_REQ, std::bind(makeGameReadyToLaunchReq, std::placeholders::_1) },
                { Type::YOUR_TURN_TO_PLAY_REQ, std::bind(makeYourTurnToPlayReq, std::placeholders::_1) },
                { Type::END_GAME_STATUS_REQ, std::bind(makeEndGameStatusReq, std::placeholders::_1) },
                { Type::NONE, std::bind(makeNone, std::placeholders::_1) }

        };

    public:
        //!
        //! @brief Default constructor.
        //!
        RequestLoader() = default;
        //!
        //! @brief Copy constructor.
        //! @warning Not available.
        //!
        RequestLoader(const RequestLoader &) = delete;
        //!
        //! @brief Equal operator overload.
        //! @return RequestLoader copy.
        //! @warning Not available.
        //!
        RequestLoader   &operator=(const RequestLoader &) = delete;
        //!
        //! @brief Destructor
        //!
        ~RequestLoader() = default;

    public:
        //!
        //! @brief Load a request.
        //! @param requestType Request type to load.
        //! @param obj Object to load into a request.
        //! @return Pointer on request interface.
        //!
        const std::shared_ptr<IRequest>     load(Type requestType, msgpack::object &obj) const;

    private:
        //!
        //! @static
        //! @brief Create corresponding request.
        //! @param obj Serialized packet.
        //! @return Request interface.
        //!
        static const std::shared_ptr<IRequest>   makeKeepAliveReq(msgpack::object &obj);
        //!
        //! @static
        //! @brief Create corresponding request.
        //! @param obj Serialized packet.
        //! @return Request interface.
        //!
        static const std::shared_ptr<IRequest>   makeAuthenticateReq(msgpack::object &obj);
        //!
        //! @static
        //! @brief Create corresponding request.
        //! @param obj Serialized packet.
        //! @return Request interface.
        //!
        static const std::shared_ptr<IRequest>   makeAuthenticateResp(msgpack::object &obj);
        //!
        //! @static
        //! @brief Create corresponding request.
        //! @param obj Serialized packet.
        //! @return Request interface.
        //!
        static const std::shared_ptr<IRequest>   makeGetRoomListReq(msgpack::object &obj);
        //!
        //! @static
        //! @brief Create corresponding request.
        //! @param obj Serialized packet.
        //! @return Request interface.
        //!
        static const std::shared_ptr<IRequest>   makeGetRoomListResp(msgpack::object &obj);
        //!
        //! @static
        //! @brief Create corresponding request.
        //! @param obj Serialized packet.
        //! @return Request interface.
        //!
        static const std::shared_ptr<IRequest>   makeCreateRoomReq(msgpack::object &obj);
        //!
        //! @static
        //! @brief Create corresponding request.
        //! @param obj Serialized packet.
        //! @return Request interface.
        //!
        static const std::shared_ptr<IRequest>   makeCreateRoomResp(msgpack::object &obj);
        //!
        //! @static
        //! @brief Create corresponding request.
        //! @param obj Serialized packet.
        //! @return Request interface.
        //!
        static const std::shared_ptr<IRequest>   makeJoinRoomReq(msgpack::object &obj);
        //!
        //! @static
        //! @brief Create corresponding request.
        //! @param obj Serialized packet.
        //! @return Request interface.
        //!
        static const std::shared_ptr<IRequest>   makeJoinRoomResp(msgpack::object &obj);
        //!
        //! @static
        //! @brief Create corresponding request.
        //! @param obj Serialized packet.
        //! @return Request interface.
        //!
        static const std::shared_ptr<IRequest>   makeViewRoomReq(msgpack::object &obj);
        //!
        //! @static
        //! @brief Create corresponding request.
        //! @param obj Serialized packet.
        //! @return Request interface.
        //!
        static const std::shared_ptr<IRequest>   makeViewRoomResp(msgpack::object &obj);
        //!
        //! @static
        //! @brief Create corresponding request.
        //! @param obj Serialized packet.
        //! @return Request interface.
        //!
        static const std::shared_ptr<IRequest>   makeExitRoomReq(msgpack::object &obj);
        //!
        //! @static
        //! @brief Create corresponding request.
        //! @param obj Serialized packet.
        //! @return Request interface.
        //!
        static const std::shared_ptr<IRequest>   makeLaunchGameReq(msgpack::object &obj);
        //!
        //! @static
        //! @brief Create corresponding request.
        //! @param obj Serialized packet.
        //! @return Request interface.
        //!
        static const std::shared_ptr<IRequest>   makeLaunchGameResp(msgpack::object &obj);
        //!
        //! @static
        //! @brief Create corresponding request.
        //! @param obj Serialized packet.
        //! @return Request interface.
        //!
        static const std::shared_ptr<IRequest>   makeLobbyStateUpdateResp(msgpack::object &obj);
        //!
        //! @static
        //! @brief Create corresponding request.
        //! @param obj Serialized packet.
        //! @return Request interface.
        //!
        static const std::shared_ptr<IRequest>   makeSetUserBattleshipReq(msgpack::object &obj);
        //!
        //! @static
        //! @brief Create corresponding request.
        //! @param obj Serialized packet.
        //! @return Request interface.
        //!
        static const std::shared_ptr<IRequest>   makeSetUserBattleshipResp(msgpack::object &obj);
        //!
        //! @static
        //! @brief Create corresponding request.
        //! @param obj Serialized packet.
        //! @return Request interface.
        //!
        static const std::shared_ptr<IRequest>   makeSendChatMsgReq(msgpack::object &obj);
        //!
        //! @static
        //! @brief Create corresponding request.
        //! @param obj Serialized packet.
        //! @return Request interface.
        //!
        static const std::shared_ptr<IRequest>   makeBroadcastChatMsgReq(msgpack::object &obj);
        //!
        //! @static
        //! @brief Create corresponding request.
        //! @param obj Serialized packet.
        //! @return Request interface.
        //!
        static const std::shared_ptr<IRequest>   makeShootShipReq(msgpack::object &obj);
        //!
        //! @static
        //! @brief Create corresponding request.
        //! @param obj Serialized packet.
        //! @return Request interface.
        //!
        static const std::shared_ptr<IRequest>   makeShootShipResp(msgpack::object &obj);
        //!
        //! @static
        //! @brief Create corresponding request.
        //! @param obj Serialized packet.
        //! @return Request interface.
        //!
        static const std::shared_ptr<IRequest>   makeGameReadyToLaunchReq(msgpack::object &obj);
        //!
        //! @static
        //! @brief Create corresponding request.
        //! @param obj Serialized packet.
        //! @return Request interface.
        //!
        static const std::shared_ptr<IRequest>   makeYourTurnToPlayReq(msgpack::object &obj);
        //!
        //! @static
        //! @brief Create corresponding request.
        //! @param obj Serialized packet.
        //! @return Request interface.
        //!
        static const std::shared_ptr<IRequest>   makeEndGameStatusReq(msgpack::object &obj);
        //!
        //! @static
        //! @brief When none type is given.
        //! @return Request interface.
        //!
        static const std::shared_ptr<IRequest>   makeNone(msgpack::object &);
    };

}
}
}
}

#endif //SPACEBATTLE_CLIENT_REQUESTLOADER_HPP
