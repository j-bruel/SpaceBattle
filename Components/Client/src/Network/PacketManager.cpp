//!
//! @file PacketManager.cpp
//! @author jbruel
//! @date 07/11/18
//!

#include "Network/PacketManager.hpp"
#include "Commun/Tools/Log/Idx.hpp"
#include <plog/Log.h>

namespace spcbttl
{
namespace client
{
namespace net
{

    PacketManager::PacketManager() : mHeaderReceived(false), mPacket(), mReqLoader(), mBuffer(tool::BufferDataManager<std::shared_ptr<commun::net::Packet>>::Instance())
    {

    }

    void    PacketManager::packetReceived(msgpack::object &obj, sckcpp::tcp::ClientSocket &clientSocket)
    {
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "A packet as been received (" << clientSocket.getInfo() << ").";
        if (isHeader())
            loadPacketHeader(obj, clientSocket);
        else
            loadPacketBody(obj, clientSocket);
    }

    void    PacketManager::loadPacketHeader(msgpack::object &obj, sckcpp::tcp::ClientSocket &clientSocket)
    {
        if (mHeaderReceived)
            return ;
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "Loading packet header (" << clientSocket.getInfo() << ").";
        try {
            mPacket.mPacketHeader = obj.as<commun::net::PacketHeader>();
        }
        catch (msgpack::v1::type_error &e) {
            invalidPacketReceived(clientSocket, e.what());
            mHeaderReceived = false;
            return ;
        }
        if (mPacket.mPacketHeader.mCmdType == spcbttl::commun::net::req::Type::NONE)
        {
            invalidPacketReceived(clientSocket, "None request type received.");
            mHeaderReceived = false;
            return ;
        }
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Packet header loaded (" << clientSocket.getInfo() << ").";
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Client ID : " <<  mPacket.mPacketHeader.mClientId << " (" << clientSocket.getInfo() << ").";
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Command type : " << mPacket.mPacketHeader.mCmdType << " (" << clientSocket.getInfo() << ").";
        mHeaderReceived = true;
    }

    void    PacketManager::loadPacketBody(msgpack::object &obj, sckcpp::tcp::ClientSocket &clientSocket)
    {
        if (!mHeaderReceived || mPacket.mPacketHeader.mCmdType == spcbttl::commun::net::req::Type::NONE)
            return ;
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::debug) << "Loading packet body (" << clientSocket.getInfo() << ").";
        try {
            mPacket.mPacketBody = mReqLoader.load(mPacket.mPacketHeader.mCmdType, obj);
            mBuffer.push_back(std::make_shared<commun::net::Packet>(mPacket));
        }
        catch (msgpack::v1::type_error &e) {
            invalidPacketReceived(clientSocket, e.what());
            mHeaderReceived = false;
            return ;
        }
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "A complete packet loaded (" << clientSocket.getInfo() << ").";
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Packet type : " << mPacket.mPacketHeader.mCmdType << " (" << clientSocket.getInfo() << ").";
        mHeaderReceived = false;
    }

    void    PacketManager::invalidPacketReceived(sckcpp::tcp::ClientSocket &clientSocket, const std::string &exceptionCause) const
    {
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::error) << "Error while reading packet from : " << clientSocket.getInfo() << ".";
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::error) << "The received packet is probably not a header.";
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::error) << "The first packet must be a header, see SpaceBattle RFC.";
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::error) << "Error: " << exceptionCause;
    }

}
}
}