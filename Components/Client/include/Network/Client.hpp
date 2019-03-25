//!
//! @file Client.hpp
//! @author jbruel
//! @date 25/11/18
//!

#ifndef SPACEBATTLE_CLIENT_NETWORK_CLIENT_HPP
# define SPACEBATTLE_CLIENT_NETWORK_CLIENT_HPP

# include <sckcpp/ClientSocket.hpp>
# include "Network/PacketManager.hpp"
# include <boost/asio/io_service.hpp>
# include <msgpack.hpp>

//!
//! @namespace spcbttl
//!
namespace spcbttl
{
//!
//! @namespace server
//!
namespace client
{
//!
//! @namespace net
//!
namespace net
{

    //!
    //! @class Client
    //! @brief Client class.
    //!
    class   Client
    {
    private:
        boost::asio::io_service     mIOService; //!< boost IO service.
        sckcpp::tcp::ClientSocket   mClientSocket; //!< Client instance.
        PacketManager               mPacketManager;

    private:
        const std::size_t mWindowSize = 1;
        msgpack::unpacker mUnp;

    public:
        //!
        //! @brief Constructor.
        //!
        Client() :  mIOService(), mClientSocket(mIOService), mPacketManager(), mUnp() {}
        //!
        //! @brief Copy constructor.
        //! @warning Not available.
        //!
        Client(const Client &) = delete;
        //!
        //! @brief Equal overload operator
        //! @warning Not available.
        //!
        Client  &operator=(const Client &) = delete;
        //!
        //! @brief Destructor.
        //!
        ~Client() = default;

    public:
        //!
        //! @brief Connect to the server.
        //! @param ip Server IP.
        //! @param port Server port.
        //! @return Client instance.
        //!
        sckcpp::tcp::ClientSocket   &connect(const std::string &ip, unsigned short port);
        //!
        //! @brief Run reading process.
        //! @warning connect function must be call before.
        //! @warning Need a full process.
        //!

        void                        run();
        void                        stop();

    private:
        //!
        //! @brief Read loop for server request.
        //!
        void        processReadLoop();

        //!
        //! @brief Start client read.
        //!
        inline void start() { processReadLoop(); }
    };

}
}
}
#endif //SPACEBATTLE_CLIENT_NETWORK_CLIENT_HPP
