//!
//! @file IRequest.hpp
//! @author jbruel
//! @date 03/11/18
//!

#ifndef SPACEBATTLE_SERVER_PACKETHEADER_HPP
# define SPACEBATTLE_SERVER_PACKETHEADER_HPP

# include <msgpack.hpp>
# include <cstdint>
#include <Commun/Network/Requests/Type.hpp>

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
    //! @struct PacketHeader
    //! @brief Packet Header
    //!
    struct  PacketHeader
    {
        req::Type       mCmdType; //!< Command Type.
        unsigned short  mClientId; //!< Client ID.

    public:
        MSGPACK_DEFINE(mCmdType, mClientId);

        //!
        //! @brief Default constructor
        //!
        PacketHeader() : mCmdType(req::Type::NONE), mClientId(0) {}

        //!
        //! @brief Initialize all packet informations header
        //! @param cmdType Command type
        //! @param clientId Client ID
        //!
        void    set(req::Type cmdType, unsigned short clientId)
        {
            mCmdType = cmdType;
            mClientId = clientId;
        }
        //!
        //! @brief Reset data in header
        //!
        void    reset()
        {
            mCmdType = req::Type::NONE;
            mClientId = 0;
        }
    };

}
}
}

#endif //SPACEBATTLE_SERVER_PACKETHEADER_HPP
