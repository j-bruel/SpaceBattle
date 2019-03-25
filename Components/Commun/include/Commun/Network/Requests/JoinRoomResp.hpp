//!
//! @file JoinRoomResp.hpp
//! @author jbruel
//! @date 19/11/18
//!

#ifndef SPACEBATTLE_SERVER_JOINROOMRESP_HPP
# define SPACEBATTLE_SERVER_JOINROOMRESP_HPP

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
    //! @class JoinRoomResp
    //! @brief Join room response.
    //!
    class   JoinRoomResp : public IRequest
    {
    private:
        std::string         mRoomName; //!< Room name.
        engine::TimeLimit   mLimitTime; //!< Game limit time.
        bool                mIsViewerAllow; //!< Tell if viewer is allow.
        State               mRoomState; //!< Current room state.

    public:
        MSGPACK_DEFINE(mRoomName, mLimitTime, mIsViewerAllow, mRoomState);

    public:
        //!
        //! @brief Default constructor.
        //!
        JoinRoomResp() = default;
        //!
        //! @brief Copy constructor.
        //! @param joinRoomResp Create Room request.
        //!
        JoinRoomResp(const JoinRoomResp &joinRoomResp) :    IRequest(joinRoomResp), mRoomName(joinRoomResp.mRoomName),
                                                            mLimitTime(joinRoomResp.mLimitTime), mIsViewerAllow(joinRoomResp.mIsViewerAllow),
                                                            mRoomState(joinRoomResp.mRoomState) { }
        //!
        //! @brief Equal operator overload.
        //! @param joinRoomResp Create room request.
        //! @return Request copy.
        //!
        JoinRoomResp    &operator=(const JoinRoomResp &joinRoomResp)
        {
            mRoomName = joinRoomResp.mRoomName;
            mLimitTime = joinRoomResp.mLimitTime;
            mIsViewerAllow = joinRoomResp.mIsViewerAllow;
            mRoomState = joinRoomResp.mRoomState;
            return ((*this));
        }
        //!
        //! @brief Destructor.
        //!
        ~JoinRoomResp() override = default;

    public:
        //!
        //! @brief Extract request type.
        //! @return Request type.
        //!
        inline Type getType() const override { return (Type::JOIN_ROOM_RESP); }

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

#endif //SPACEBATTLE_SERVER_JOINROOMRESP_HPP
