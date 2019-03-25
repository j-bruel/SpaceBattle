//!
//! @file ExitRoomReq.hpp
//! @author jbruel
//! @date 19/11/18
//!

#ifndef SPACEBATTLE_SERVER_EXISTROOMREQ_HPP
# define SPACEBATTLE_SERVER_EXISTROOMREQ_HPP

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
    //! @class ExitRoomReq
    //! @brief Exit Room request.
    //!
    class   ExitRoomReq : public IRequest
    {
    private:
        std::string mRoomName; //!< Room name

    public:
        MSGPACK_DEFINE(mRoomName);

    public:
        //!
        //! @brief Default constructor.
        //!
        ExitRoomReq() = default;
        //!
        //! @brief Copy constructor.
        //! @param exitRoomReq Exit room request.
        //!
        ExitRoomReq(const ExitRoomReq &exitRoomReq) : IRequest(exitRoomReq), mRoomName(exitRoomReq.mRoomName) { }
        //!
        //! @brief Equal operator overload.
        //! @param exitRoomReq Exit room request.
        //! @return Request copy.
        //!
        ExitRoomReq    &operator=(const ExitRoomReq &exitRoomReq)
        {
            mRoomName = exitRoomReq.mRoomName;
            return ((*this));
        }
        //!
        //! @brief Destructor.
        //!
        ~ExitRoomReq() override = default;

    public:
        //!
        //! @brief Extract request type.
        //! @return Request type.
        //!
        inline Type getType() const override { return (Type::EXIT_ROOM_REQ); }

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

#endif //SPACEBATTLE_SERVER_EXISTROOMREQ_HPP
