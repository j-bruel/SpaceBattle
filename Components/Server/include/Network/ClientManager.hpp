//!
//! @file ClientManager.hpp
//! @author jbruel
//! @date 02/11/18
//!

#ifndef SPACEBATTLE_SERVER_CLIENTMANAGER_HPP
# define SPACEBATTLE_SERVER_CLIENTMANAGER_HPP

# include <sckcpp/Client.hpp>
# include <set>

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
    //! @class ClientManager
    //! @brief Clients manager.
    //!
    class   ClientManager
    {
    private:
        std::set<sckcpp::ClientPtr> mClients; //!< All clients handle.

    public:
        using OnForeachClientFunc = std::function<void(boost::shared_ptr<sckcpp::Client> client)>;

    public:
        //!
        //! @brief Default constructor.
        //!
        ClientManager() = default;
        //!
        //! @brief Copy constructor.
        //! @warning Not available.
        //!
        ClientManager(const ClientManager &) = delete;
        //!
        //! @brief Equal overload operator.
        //! @warning Not available.
        //! @return Clients manager
        //!
        ClientManager   &operator=(const ClientManager &) = delete;
        //!
        //! @brief Destructor.
        //!
        ~ClientManager() = default;

    public:
        //!
        //! @brief Add new client.
        //! @param client New client
        //!
        inline void add(sckcpp::ClientPtr &client) { mClients.insert(client); }
        //!
        //! @brief Remove a client.
        //! @param client Removed client
        //!
        inline void remove(sckcpp::ClientPtr &client) { mClients.erase(client); }
        //!
        //! @brief Stop a client.
        //! @param client
        //!
        void        stop(sckcpp::ClientPtr &client) { client->stop(); }
        //!
        //! @brief Stop all client.
        //!
        void        stopAll();
        //!
        //! @brief Apply a function on all clients
        //! @param onForeach Function that will be call for all clients available.
        //!
        void        foreach(OnForeachClientFunc onForeach);
        //!
        //! @brief Extract all clients handle.
        //! @return All clients.
        //!
        const std::set<sckcpp::ClientPtr>   &getClients() const { return (mClients); }
        //!
        //! @brief Compute client handle number.
        //! @return Number client handle.
        //!
        size_t  count() const { return (mClients.size()); }
    };

}
}
}
#endif //SPACEBATTLE_SERVER_CLIENTMANAGER_HPP
