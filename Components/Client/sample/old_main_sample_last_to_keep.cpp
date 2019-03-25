#include <Commun/Network/PacketHeader.hpp>
#include <Commun/Network/Requests/AuthenticateReq.hpp>
#include <Network/BattleAPI.hpp>
#include "Network/Client.hpp"
#include <Commun/Tools/Log/Initializer.hpp>
#include "Exemple.hpp"


#include <Tools/BufferDataManager.hpp>

static void    initLog()
{
    spcbttl::commun::tool::log::initialize("./client.log", plog::verbose, plog::verbose);
    LOG_(spcbttl::commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "Space Battle application as been launch.";
}

int     main()
{
    spcbttl::client::tool::BufferDataManager<int> &buffer(spcbttl::client::tool::BufferDataManager<int>::Instance());
    spcbttl::client::Exemple    ex;
    initLog();

    spcbttl::client::net::Client        client;
    sckcpp::tcp::ClientSocket           &clientSocket = client.connect("127.0.0.1", 4242);
    spcbttl::client::net::BattleAPI     battleAPI(clientSocket);

    buffer.attach(ex);
    battleAPI.authReq("Coucou");
    buffer.push_back(2);

    std::thread t([&]() {
        client.run();
    });

    return (EXIT_SUCCESS);
}