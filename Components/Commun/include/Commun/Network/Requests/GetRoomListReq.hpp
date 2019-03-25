//!
//! @file GetRoomListReq.hpp
//! @author jbruel
//! @date 03/11/18
//!

#ifndef SPACEBATTLE_SERVER_GETROOMLISTREQ_HPP
# define SPACEBATTLE_SERVER_GETROOMLISTREQ_HPP

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
    //! @class GetRoomListReq
    //! @brief Get room list request.
    //!
    class   GetRoomListReq : public IRequest
    {
    public:
        MSGPACK_DEFINE();

    public:
        //!
        //! @brief Default constructor.
        //!
        GetRoomListReq() = default;
        //!
        //! @brief Copy constructor.
        //! @param getRoomListReq get room list request.
        //!
        GetRoomListReq(const GetRoomListReq &getRoomListReq) : IRequest(getRoomListReq) { }
        //!
        //! @brief Equal operator overload.
        //! @param authenticateReq get room list request.
        //! @return Request copy.
        //!
        GetRoomListReq    &operator=(const GetRoomListReq &authenticateReq) = default;
        //!
        //! @brief Destructor.
        //!
        ~GetRoomListReq() override = default;

    public:
        //!
        //! @brief Extract request type.
        //! @return Request type.
        //!
        inline Type getType() const override { return (Type::GET_ROOM_LIST_REQ); }
    };

}
}
}
}

#endif //SPACEBATTLE_SERVER_GETROOMLISTREQ_HPP
