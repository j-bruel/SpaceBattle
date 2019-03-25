//!
//! @file Network/PacketManager.hpp
//! @author jbruel
//! @date 07/11/18
//!

#ifndef SPACEBATTLE_COMMUN_NETWORK_PACKETMANAGER_HPP
# define SPACEBATTLE_COMMUN_NETWORK_PACKETMANAGER_HPP

# include "Commun/Network/Packet.hpp"
# include "Commun/Tools/BufferDataManager.hpp"
# include "Commun/Network/Requests/RequestLoader.hpp"
# include <sckcpp/TcpClientSocket.hpp>
# include <functional>

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
    //! @class PacketManager
    //! @brief Packet manager
    //!
    class   PacketManager
    {
    private:
        bool                            mHeaderReceived; //!< Allow to know if the current packet is a body or header.
        Packet                          mPacket; //!< Current packet header.
        req::RequestLoader              mReqLoader; //!< Requests loader.
        tool::BufferDataManager<std::shared_ptr<Packet>> &mBuffer; //!< Buffer manager.

    public:
        //!
        //! @brief Default constructor
        //! @warning Not avaialble
        //!
        PacketManager();
        //!
        //! @brief Copy constructor
        //! @warning Not avaialble
        //!
        PacketManager(PacketManager &packetManager) = delete;
        //!
        //! @brief Equal operator overload
        //! @return PacketManager copy
        //! @warning Not available.
        //!
        PacketManager   &operator=(const PacketManager &) = delete;
        //!
        //! @brief Destructor
        //!
        ~PacketManager() = default;

    public:
        //!
        //! @brief Main packet handling function.
        //! @param obj Packet in unknow type.
        //! @param clientSocket Client information.
        //!
        void    packetReceived(msgpack::object &obj, sckcpp::tcp::ClientSocket &clientSocket);

    private:
        //!
        //! @brief Tell if the current packet is a header.
        //! @return State.
        //!
        inline bool isHeader() const { return (!mHeaderReceived); }
        //!
        //! @brief Load packet header.
        //! @param obj Packet in unknow type.
        //! @param clientSocket Client information.
        //!
        void        loadPacketHeader(msgpack::object &obj, sckcpp::tcp::ClientSocket &clientSocket);
        //!
        //! @brief Load packet body.
        //! @param obj Packet in unknow type.
        //! @param clientSocket Client information.
        //!
        void        loadPacketBody(msgpack::object &obj, sckcpp::tcp::ClientSocket &clientSocket);

    private:
        //!
        //! @brief add log for invalid packet.
        //! @param clientSocket Client information.
        //! @param exceptionCause Exception cause.
        //!
        void    invalidPacketReceived(sckcpp::tcp::ClientSocket &clientSocket, const std::string &exceptionCause) const;
        //!
        //! @brief Update AUTHENTICATE_REQ into SAUTHENTICATE_REQ
        //! @param clientSocket Player.
        //!
        void    transformAuthIntoSAuthReq(sckcpp::tcp::ClientSocket &clientSocket);

    };

}
}
}

#endif //SPACEBATTLE_COMMUN_NETWORK_PACKETMANAGER_HPP
