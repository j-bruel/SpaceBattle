//
// Created by brd6 on 26/09/17.
//

#ifndef SCKCPP_CLIENT_HPP
#define SCKCPP_CLIENT_HPP

#include <boost/make_shared.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>
#include <unordered_map>
#include "ClientSocket.hpp"
#include "Commun/Network/PacketManager.hpp"

namespace sckcpp
{
    class Client : public boost::enable_shared_from_this<Client>, private boost::noncopyable
    {
    private:
        tcp::ClientSocket   mSocket;
        bool                mIsFirstConnection;
        bool                mIsAuthenticate;
        bool                mIsStopped;

    private:
        ::spcbttl::commun::net::PacketManager mPacketManager;

    private:
        std::size_t const window_size = 1;
        msgpack::unpacker unp;

    private:
        std::function<void(boost::shared_ptr<Client> client)> mOnStopClient;

    public:
        explicit Client(boost::asio::io_service& ios);

        //! Return the boost socket instance
        //! \return
        boost::asio::ip::tcp::socket &getSocket();

        //! Start the client
        void start();

        //! Stop the client
        void stop();

        //! Set the on stop client callback
        //! \param onStopClient
        void setOnStopClientCallback(std::function<void(boost::shared_ptr<Client> client)> onStopClient);

        //! Send command
        //! \param msg
        void sendCommand(std::string const &msg);

        tcp::ClientSocket   &getClientSocket() { return (mSocket); }

        //! Return info about the client
        //! \return
        std::string getInfo();

        //! Send a request to notify server disconnection
        void sendServerDisconnectRequest();
        bool    isStop() const { return  (mIsStopped); }

    private:
        //! Read loop
        void processReadLoop();
    };

    using OnStopClientFunc = std::function<void(boost::shared_ptr<Client> client)>;
    using ClientPtr = boost::shared_ptr<Client>;

}

#endif //SCKCPP_CLIENT_HPP
