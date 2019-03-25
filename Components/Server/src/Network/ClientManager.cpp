//!
//! @file ClientManager.cpp
//! @author jbruel
//! @date 02/11/18
//!

#include "Network/ClientManager.hpp"

namespace spcbttl
{
namespace server
{
namespace net
{

    void    ClientManager::stopAll()
    {
        std::for_each(std::begin(mClients), std::end(mClients), [](auto &client) { client->stop(); });
        mClients.clear();
    }

    void ClientManager::foreach(OnForeachClientFunc onForeach)
    {
        if (onForeach == nullptr)
            return;

        for (const sckcpp::ClientPtr &it : mClients)
            onForeach(it);
    }


}
}
}