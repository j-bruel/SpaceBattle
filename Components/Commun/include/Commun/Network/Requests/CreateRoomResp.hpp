//!
//! @file CreateRoomResp.hpp
//! @author jbruel
//! @date 03/11/18
//!

#ifndef SPACEBATTLE_SERVER_CREATEROOMRESP_HPP
# define SPACEBATTLE_SERVER_CREATEROOMRESP_HPP

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
    //! @class CreateRoomResp
    //! @brief Create room response.
    //!
    class   CreateRoomResp : public IRequest
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
        CreateRoomResp() = default;
        //!
        //! @brief Copy constructor.
        //! @param createRoomResp Create Room request.
        //!
        CreateRoomResp(const CreateRoomResp &createRoomResp) :  IRequest(createRoomResp), mRoomName(createRoomResp.mRoomName),
                                                                mLimitTime(createRoomResp.mLimitTime), mIsViewerAllow(createRoomResp.mIsViewerAllow),
                                                                mRoomState(createRoomResp.mRoomState) { }
        //!
        //! @brief Equal operator overload.
        //! @param createRoomResp Create room request.
        //! @return Request copy.
        //!
        CreateRoomResp    &operator=(const CreateRoomResp &createRoomResp)
        {
            mRoomName = createRoomResp.mRoomName;
            mLimitTime = createRoomResp.mLimitTime;
            mIsViewerAllow = createRoomResp.mIsViewerAllow;
            mRoomState = createRoomResp.mRoomState;
            return ((*this));
        }
        //!
        //! @brief Destructor.
        //!
        ~CreateRoomResp() override = default;

    public:
        //!
        //! @brief Extract request type.
        //! @return Request type.
        //!
        inline Type getType() const override { return (Type::CREATE_ROOM_RESP); }

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

#endif //SPACEBATTLE_SERVER_CREATEROOMRESP_HPP
