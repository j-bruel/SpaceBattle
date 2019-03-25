//!
//! @file Server.hpp
//! @author jbruel
//! @date 02/11/18
//!

#ifndef SPACEBATTLE_SERVER_SERVER_HPP
# define SPACEBATTLE_SERVER_SERVER_HPP

# include "ClientManager.hpp"
# include <sckcpp/TcpServerSocket.hpp>

//!
//! @namespace spcbttl
//!
namespace spcbttl
{
//!
//! @namespace server
//!
namespace server
{
//!
//! @namespace net
//!
namespace net
{

    //!
    //! @class Server
    //! @brief Server main class
    //!
    class   Server
    {
    private:
        boost::asio::io_service     mIos; //!< boost asio server
        sckcpp::tcp::ServerSocket   mServerSocket; //!< Network instance.
        ClientManager               mClientManager; //!< Clients manager

    public:
        //!
        //! @brief Default constructor.
        //! @warning Not available.
        //!
        Server() = delete;
        //!
        //! @brief Constructor
        //! @param ip Server IP address.
        //! @param ip Server IP address.
        //! @param port Server port.
        //!
        explicit Server(const std::string &ip, size_t port);
        //!
        //! @brief Copy constructor.
        //! @warning Not available.
        //!
        Server(const Server &) = delete;
        //!
        //! @brief Equal operator overload.
        //! @return Server copy.
        //! @warning Not available.
        //!
        Server  &operator=(const Server &) = delete;
        //!
        //! @brief Destructor
        //!
        ~Server();

    public:
        //!
        //! @brief Run the server
        //!
        void    run();
        //!
        //! @brief Stop the server
        //!
        void    stop();

    private:
        //!
        //! @brief Setup the accept for new client
        //! @param ip Host IP address.
        //! @param port Server port.
        //!
        void    setupAcceptor(const std::string &ip, size_t port);
        //!
        //! @brief Setup all callbacks for the network
        //!
        void    setupCallbacks();
        //!
        //! @brief Notify clients that the server is disconnected
        //!
        void    notifyClientsServerDisconnect();
    };

}
}
}

#endif //SPACEBATTLE_SERVER_SERVER_HPP
