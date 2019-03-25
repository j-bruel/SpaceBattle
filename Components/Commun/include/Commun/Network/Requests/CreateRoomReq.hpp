//!
//! @file CreateRoomReq.hpp
//! @author jbruel
//! @date 03/11/18
//!

#ifndef SPACEBATTLE_SERVER_CREATEROOMREQ_HPP
# define SPACEBATTLE_SERVER_CREATEROOMREQ_HPP

# include <string>
# include "IRequest.hpp"
# include "Commun/Engine/TimeLimit.hpp"

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
    //! @class CreateRoomReq
    //! @brief Create Room request.
    //!
    class   CreateRoomReq : public IRequest
    {
    private:
        std::string         mRoomName; //!< Room name.
        engine::TimeLimit   mLimitTime; //!< Game limit time.
        bool                mIsViewerAllow; //!< Tell is viewer is allow.

    public:
        MSGPACK_DEFINE(mRoomName, mLimitTime, mIsViewerAllow);

    public:
        //!
        //! @brief Default constructor.
        //!
        CreateRoomReq() = default;
        //!
        //! @brief Copy constructor.
        //! @param createRoomResp Create room request.
        //!
        CreateRoomReq(const CreateRoomReq &createRoomResp) :    IRequest(createRoomResp), mRoomName(createRoomResp.mRoomName),
                                                                mLimitTime(createRoomResp.mLimitTime),
                                                                mIsViewerAllow(createRoomResp.mIsViewerAllow) { }
        //!
        //! @brief Equal operator overload.
        //! @param createRoomResp Create room request.
        //! @return Request copy.
        //!
        CreateRoomReq    &operator=(const CreateRoomReq &createRoomResp)
        {
            mRoomName = createRoomResp.mRoomName;
            mLimitTime = createRoomResp.mLimitTime;
            mIsViewerAllow = createRoomResp.mIsViewerAllow;
            return ((*this));
        }
        //!
        //! @brief Destructor.
        //!
        ~CreateRoomReq() override = default;

    public:
        //!
        //! @brief Extract request type.
        //! @return Request type.
        //!
        inline Type getType() const override { return (Type::CREATE_ROOM_REQ); }

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
        //! @brief Set limit time..
        //! @param timeLimit Limit time.
        //!
        inline void                 setLimitType(engine::TimeLimit timeLimit) { mLimitTime = timeLimit; }
        //!
        //! @brief Extract time limit.
        //! @return Limit time.
        //!
        inline engine::TimeLimit    getLimitType() const { return (mLimitTime); }
        //!
        //! @brief Set is viewer allow.
        //! @param isViewerAllow is viewer allow.
        //!
        inline void                 setIsViewerAllow(bool isViewerAllow) { mIsViewerAllow = isViewerAllow; }
        //!
        //! @brief Extract is viewer allow.
        //! @return is viewer allow.
        //!
        inline bool                 isViewerAllow() const { return (mIsViewerAllow); }
    };

}
}
}
}

#endif //SPACEBATTLE_SERVER_CREATEROOMREQ_HPP
