//!
//! @file ViewRoomReq.hpp
//! @author jbruel
//! @date 19/11/18
//!

#ifndef SPACEBATTLE_SERVER_VIEWROOMREQ_HPP
# define SPACEBATTLE_SERVER_VIEWROOMREQ_HPP

# include "IRequest.hpp"
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
    //! @class ViewRoomReq
    //! @brief View Room request.
    //!
    class   ViewRoomReq : public IRequest
    {
    private:
        std::string mRoomName; //!< Room name

    public:
        MSGPACK_DEFINE(mRoomName);

    public:
        //!
        //! @brief Default constructor.
        //!
        ViewRoomReq() = default;
        //!
        //! @brief Copy constructor.
        //! @param viewRoomReq View room request.
        //!
        ViewRoomReq(const ViewRoomReq &viewRoomReq) : IRequest(viewRoomReq), mRoomName(viewRoomReq.mRoomName) { }
        //!
        //! @brief Equal operator overload.
        //! @param viewRoomReq View room request.
        //! @return Request copy.
        //!
        ViewRoomReq    &operator=(const ViewRoomReq &viewRoomReq)
        {
            mRoomName = viewRoomReq.mRoomName;
            return ((*this));
        }
        //!
        //! @brief Destructor.
        //!
        ~ViewRoomReq() override = default;

    public:
        //!
        //! @brief Extract request type.
        //! @return Request type.
        //!
        inline Type getType() const override { return (Type::VIEW_ROOM_REQ); }

    public:
        //!
        //! @brief Set room name.
        //! @param roomName room name.
        //!
        inline void                 setRoomName(const std::string &roomName) { mRoomName = roomName; }
        //!
        //! @brief Extract room name.
        //! @return Room name.
        //!
        inline const std::string    &getRoomName() const { return (mRoomName); }
    };

}
}
}
}

#endif //SPACEBATTLE_SERVER_VIEWROOMREQ_HPP
