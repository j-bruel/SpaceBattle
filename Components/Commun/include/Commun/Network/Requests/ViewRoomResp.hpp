//!
//! @file ViewRoomResp.hpp
//! @author jbruel
//! @date 19/11/18
//!

#ifndef SPACEBATTLE_SERVER_VIEWROOMRESP_HPP
# define SPACEBATTLE_SERVER_VIEWROOMRESP_HPP

# include "Commun/Network/Requests/IRequest.hpp"
# include "Commun/Engine/TimeLimit.hpp"
# include "Commun/Network/Requests/State.hpp"
# include <string>

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
    //! @class ViewRoomResp
    //! @brief View room response.
    //!
    class   ViewRoomResp : public IRequest
    {
    private:
        std::string         mRoomName; //!< Room name.
        State               mRoomState; //!< Current room state.

    public:
        MSGPACK_DEFINE(mRoomName, mRoomState);

    public:
        //!
        //! @brief Default constructor.
        //!
        ViewRoomResp() = default;
        //!
        //! @brief Copy constructor.
        //! @param viewRoomResp View Room request.
        //!
        ViewRoomResp(const ViewRoomResp &viewRoomResp) :    IRequest(viewRoomResp), mRoomName(viewRoomResp.mRoomName),
                                                            mRoomState(viewRoomResp.mRoomState) { }
        //!
        //! @brief Equal operator overload.
        //! @param viewRoomResp Create room response.
        //! @return Request copy.
        //!
        ViewRoomResp    &operator=(const ViewRoomResp &viewRoomResp)
        {
            mRoomName = viewRoomResp.mRoomName;
            mRoomState = viewRoomResp.mRoomState;
            return ((*this));
        }
        //!
        //! @brief Destructor.
        //!
        ~ViewRoomResp() override = default;

    public:
        //!
        //! @brief Extract request type.
        //! @return Request type.
        //!
        inline Type getType() const override { return (Type::VIEW_ROOM_RESP); }

    public:
        //!
        //! @brief Set room name.
        //! @param roomName Room name.
        //!
        inline void                 setRoomName(const std::string &roomName) { mRoomName = roomName; }
        //!
        //! @brief Extract room name.
        //! @return Room name.
        //!
        inline const std::string    &getRoomName() const { return (mRoomName); }
        //!
        //! @brief Set room state.
        //! @param roomState Room state.
        //!
        inline void                 setRoomState(State roomState) { mRoomState = roomState; }
        //!
        //! @brief Extract room state.
        //! @return Room State.
        //!
        inline State                getRoomState() const { return (mRoomState); }
    };

}
}
}
}

#endif //SPACEBATTLE_SERVER_VIEWROOMRESP_HPP
