//!
//! @file JoinRoomReq.hpp
//! @author jbruel
//! @date 19/11/18
//!

#ifndef SPACEBATTLE_SERVER_JOINROOMREQ_HPP
# define SPACEBATTLE_SERVER_JOINROOMREQ_HPP

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
    //! @class JoinRoomReq
    //! @brief Join Room request.
    //!
    class   JoinRoomReq : public IRequest
    {
    private:
        std::string mRoomName; //!< Room name

    public:
        MSGPACK_DEFINE(mRoomName);

    public:
        //!
        //! @brief Default constructor.
        //!
        JoinRoomReq() = default;
        //!
        //! @brief Copy constructor.
        //! @param joinRoomReq Join room request.
        //!
        JoinRoomReq(const JoinRoomReq &joinRoomReq) : IRequest(joinRoomReq), mRoomName(joinRoomReq.mRoomName) { }
        //!
        //! @brief Equal operator overload.
        //! @param joinRoomReq Join room request.
        //! @return Request copy.
        //!
        JoinRoomReq    &operator=(const JoinRoomReq &joinRoomReq)
        {
            mRoomName = joinRoomReq.mRoomName;
            return ((*this));
        }
        //!
        //! @brief Destructor.
        //!
        ~JoinRoomReq() override = default;

    public:
        //!
        //! @brief Extract request type.
        //! @return Request type.
        //!
        inline Type getType() const override { return (Type::JOIN_ROOM_REQ); }

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

#endif //SPACEBATTLE_SERVER_JOINROOMREQ_HPP
