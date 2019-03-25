//!
//! @file Packet.hpp
//! @author jbruel
//! @date 03/11/18
//!

#ifndef SPACEBATTLE_SERVER_PACKET_HPP
# define SPACEBATTLE_SERVER_PACKET_HPP

# include <boost/shared_ptr.hpp>
# include "Commun/Network/PacketHeader.hpp"
# include "Commun/Network/Requests/IRequest.hpp"

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
    //! @struct Packet
    //! @brief All informations for a packet
    //!
    struct Packet
    {
        PacketHeader                    mPacketHeader;
        std::shared_ptr<req::IRequest>   mPacketBody;

        Packet() : mPacketHeader(), mPacketBody(nullptr) { }

        //!
        //! @brief Initialize all packet informations header
        //! @param cmdType Command type
        //! @param clientId Client ID
        //!
        void    setHeader(req::Type cmdType, unsigned short clientId)
        {
            mPacketHeader.set(cmdType, clientId);
        }
        //!
        //! @brief Set packet
        //! @param cmdType Command type
        //! @param clientId Client ID
        //! @param packetBody Packet body.
        //!
        void    set(req::Type cmdType, unsigned short clientId, std::shared_ptr<req::IRequest> &packetBody)
        {
            mPacketHeader.set(cmdType, clientId);
            mPacketBody = packetBody;
        }
        //!
        //! @brief Reset data in header
        //!
        void    reset()
        {
            mPacketHeader.reset();
            mPacketBody = nullptr;
        }
    };


}
}
}


#endif //SPACEBATTLE_SERVER_PACKET_HPP
