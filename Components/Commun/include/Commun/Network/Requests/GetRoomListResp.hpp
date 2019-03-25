//!
//! @file GetRoomListResp.hpp
//! @author jbruel
//! @date 03/11/18
//!

#ifndef SPACEBATTLE_SERVER_GETROOMLISTRESP_HPP
# define SPACEBATTLE_SERVER_GETROOMLISTRESP_HPP

# include "IRequest.hpp"
# include "Commun/Room/State.hpp"
# include <string>
# include <map>

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
    //! @class GetRoomListResp
    //! @brief Get room list response.
    //!
    class   GetRoomListResp : public IRequest
    {
    private:
        std::map<std::string, room::State>  mRoomsState;

    public:
        MSGPACK_DEFINE(mRoomsState);

    public:
        //!
        //! @brief Default constructor.
        //!
        GetRoomListResp() = default;
        //!
        //! @brief Copy constructor.
        //! @param getRoomListResp Authenticate request.
        //!
        GetRoomListResp(const GetRoomListResp &getRoomListResp) : IRequest(getRoomListResp) { mRoomsState = getRoomListResp.mRoomsState; }
        //!
        //! @brief Equal operator overload.
        //! @param getRoomListResp Get room list request.
        //! @return Request copy.
        //!
        GetRoomListResp    &operator=(const GetRoomListResp &getRoomListResp)
        {
            mRoomsState = getRoomListResp.mRoomsState;
            return ((*this));
        }
        //!
        //! @brief Destructor.
        //!
        ~GetRoomListResp() override = default;

    public:
        //!
        //! @brief Extract request type.
        //! @return Request type.
        //!
        inline Type getType() const override { return (Type::GET_ROOM_LIST_RESP); }

    public:
        //!
        //! @brief Add a room state.
        //! @param roomName Room name.
        //! @param state Room state.
        //!
        inline void                                     addRoomState(const std::string &roomName, room::State state) { mRoomsState[roomName] = state; }
        //!
        //! @brief Extract player name.
        //! @param roomName Room name.
        //! @return Player name.
        //!
        inline room::State                              getRoomState(const std::string &roomName) const { return (mRoomsState.at(roomName)); }
        //!
        //! @brief Extract rooms.
        //! @return All rooms and states.
        //!
        inline const std::map<std::string, room::State> getRooms() const { return (mRoomsState); }
    };

}
}
}
}

#endif //SPACEBATTLE_SERVER_GETROOMLISTRESP_HPP
