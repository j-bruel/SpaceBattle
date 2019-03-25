//!
//! @file BroadcastChatMsgResp.hpp
//! @author jbruel
//! @date 19/11/18
//!

#ifndef SPACEBATTLE_SERVER_BROADCASTCHARMSGRESP_HPP
# define SPACEBATTLE_SERVER_BROADCASTCHARMSGRESP_HPP

# include "IRequest.hpp"
# include <string>
# include <Commun/Engine/Chanel.hpp>

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
    //! @class BroadcastChatMsgResp
    //! @brief Broadcast message to clients.
    //!
    class   BroadcastChatMsgResp : public IRequest
    {
    private:
        engine::ChanelType  mChanelType; //!< Channel type.
        std::string         mMsg; //!< Player name.

    public:
        MSGPACK_DEFINE(mChanelType, mMsg);

    public:
        //!
        //! @brief Default constructor.
        //!
        BroadcastChatMsgResp() = default;
        //!
        //! @brief Copy constructor.
        //! @param broadcastChatMsgResp Broadcast message to clients.
        //!
        BroadcastChatMsgResp(const BroadcastChatMsgResp &broadcastChatMsgResp) :    IRequest(broadcastChatMsgResp), mChanelType(broadcastChatMsgResp.mChanelType),
                                                                                    mMsg(broadcastChatMsgResp.mMsg) { }
        //!
        //! @brief Equal operator overload.
        //! @param broadcastChatMsgResp Broadcast message to clients.
        //! @return Request copy.
        //!
        BroadcastChatMsgResp    &operator=(const BroadcastChatMsgResp &broadcastChatMsgResp)
        {
            mChanelType = broadcastChatMsgResp.mChanelType;
            mMsg = broadcastChatMsgResp.mMsg;
            return ((*this));
        }
        //!
        //! @brief Destructor.
        //!
        ~BroadcastChatMsgResp() override = default;

    public:
        //!
        //! @brief Extract request type.
        //! @return Request type.
        //!
        inline Type getType() const override { return (Type::BROADCAST_CHAT_MSG_REQ); }

    public:
        //!
        //! @brief Set chanel type.
        //! @param chanelType Chanel type.
        //!
        inline void                     setChanelType(const engine::ChanelType &chanelType) { mChanelType = chanelType; }
        //!
        //! @brief Extract chanel type.
        //! @return Chanel type.
        //!
        inline const engine::ChanelType &getChanelType() const { return (mChanelType); }
        //!
        //! @brief Set message.
        //! @param msg Message.
        //!
        inline void                     setMessage(const std::string &msg) { mMsg = msg; }
        //!
        //! @brief Extract message.
        //! @return Message
        //!
        inline const std::string        &getMessage() const { return (mMsg); }
    };

}
}
}
}

#endif //SPACEBATTLE_SERVER_BROADCASTCHARMSGRESP_HPP
