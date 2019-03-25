//!
//! @file SendChatMsgReq.hpp
//! @author jbruel
//! @date 19/11/18
//!

#ifndef SPACEBATTLE_SERVER_SENDCHATMSGREQ_HPP
# define SPACEBATTLE_SERVER_SENDCHATMSGREQ_HPP

# include "IRequest.hpp"
# include <string>
#include <Commun/Engine/Chanel.hpp>

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
    //! @class SendChatMsgReq
    //! @brief Send chat msg request.
    //!
    class   SendChatMsgReq : public IRequest
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
        SendChatMsgReq() = default;
        //!
        //! @brief Copy constructor.
        //! @param sendChatMsgReq Send chat msg request.
        //!
        SendChatMsgReq(const SendChatMsgReq &sendChatMsgReq) :  IRequest(sendChatMsgReq), mChanelType(sendChatMsgReq.mChanelType),
                                                                mMsg(sendChatMsgReq.mMsg) { }
        //!
        //! @brief Equal operator overload.
        //! @param sendChatMsgReq Send chat msg request.
        //! @return Request copy.
        //!
        SendChatMsgReq    &operator=(const SendChatMsgReq &sendChatMsgReq)
        {
            mChanelType = sendChatMsgReq.mChanelType;
            mMsg = sendChatMsgReq.mMsg;
            return ((*this));
        }
        //!
        //! @brief Destructor.
        //!
        ~SendChatMsgReq() override = default;

    public:
        //!
        //! @brief Extract request type.
        //! @return Request type.
        //!
        inline Type getType() const override { return (Type::SEND_CHAT_MSG_REQ); }

    public:
        //!
        //! @brief Set chanel type.
        //! @param chanelType Chanel type.
        //!
        inline void                 setChanelType(const engine::ChanelType &chanelType) { mChanelType = chanelType; }
        //!
        //! @brief Extract chanel type.
        //! @return Chanel type.
        //!
        const engine::ChanelType   &getChanelType() const { return (mChanelType); }
        //!
        //! @brief Set message.
        //! @param msg Message.
        //!
        inline void                 setMessage(const std::string &msg) { mMsg = msg; }
        //!
        //! @brief Extract message.
        //! @return Message
        //!
        inline const std::string    &getMessage() const { return (mMsg); }
    };

}
}
}
}

#endif //SPACEBATTLE_SERVER_SENDCHATMSGREQ_HPP
