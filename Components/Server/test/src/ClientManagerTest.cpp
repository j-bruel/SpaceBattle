//!
//! @file ClientManagerTest.cpp
//! @author jbruel
//! @date 04/11/18
//!

#include "Network/ClientManager.hpp"
#include "sckcpp/ClientHelper.hpp"
#include <gtest/gtest.h>

//!
//! @test Simple count call with a empty manager
//!
TEST (ClientManger, countEmpty)
{
    spcbttl::server::net::ClientManager clientManager;

    EXPECT_EQ(clientManager.count(), static_cast<size_t>(0));
}

//!
//! @test Simple count test.
//!
TEST (ClientManger, count)
{
    boost::asio::io_service             ioService;
    sckcpp::ClientPtr                   clientPtr1 = sckcpp::helper::createClient(ioService);
    sckcpp::ClientPtr                   clientPtr2 = sckcpp::helper::createClient(ioService);
    sckcpp::ClientPtr                   clientPtr3 = sckcpp::helper::createClient(ioService);
    sckcpp::ClientPtr                   clientPtr4 = sckcpp::helper::createClient(ioService);
    spcbttl::server::net::ClientManager clientManager;

    clientManager.add(clientPtr1);
    clientManager.add(clientPtr2);
    clientManager.add(clientPtr3);
    clientManager.add(clientPtr4);
    EXPECT_EQ(clientManager.count(), static_cast<size_t>(4));
}

//!
//! @test Check if get clients return all clients handle.
//!
TEST (ClientManger, getClients)
{
    boost::asio::io_service ioService;
    sckcpp::ClientPtr                   clientPtr1 = sckcpp::helper::createClient(ioService);
    sckcpp::ClientPtr                   clientPtr2 = sckcpp::helper::createClient(ioService);
    spcbttl::server::net::ClientManager clientManager;

    clientManager.add(clientPtr1);
    clientManager.add(clientPtr2);

    const std::set<sckcpp::ClientPtr>           clients = clientManager.getClients();
    std::set<sckcpp::ClientPtr>::const_iterator it = clients.begin();

    for (size_t i = 0; i < clients.size(); ++i)
        EXPECT_TRUE(*it == clientPtr2 || *it == clientPtr1);
}

//!
//! @test Simple add test.
//!
TEST (ClientManger, add)
{
    boost::asio::io_service ioService;
    sckcpp::ClientPtr                   clientPtr1 = sckcpp::helper::createClient(ioService);
    sckcpp::ClientPtr                   clientPtr2 = sckcpp::helper::createClient(ioService);
    sckcpp::ClientPtr                   clientPtr3 = sckcpp::helper::createClient(ioService);
    sckcpp::ClientPtr                   clientPtr4 = sckcpp::helper::createClient(ioService);
    spcbttl::server::net::ClientManager clientManager;

    EXPECT_EQ(clientManager.count(), static_cast<size_t>(0));
    clientManager.add(clientPtr1);
    EXPECT_EQ(clientManager.count(), static_cast<size_t>(1));
    clientManager.add(clientPtr2);
    clientManager.add(clientPtr3);
    EXPECT_EQ(clientManager.count(), static_cast<size_t>(3));
    clientManager.add(clientPtr4);
    EXPECT_EQ(clientManager.count(), static_cast<size_t>(4));
}

//!
//! @test Simple remove test.
//!
TEST (ClientManger, remove)
{
    boost::asio::io_service ioService;
    sckcpp::ClientPtr                   clientPtr1 = sckcpp::helper::createClient(ioService);
    sckcpp::ClientPtr                   clientPtr2 = sckcpp::helper::createClient(ioService);
    sckcpp::ClientPtr                   clientPtr3 = sckcpp::helper::createClient(ioService);
    sckcpp::ClientPtr                   clientPtr4 = sckcpp::helper::createClient(ioService);
    spcbttl::server::net::ClientManager clientManager;

    EXPECT_EQ(clientManager.count(), static_cast<size_t>(0));
    clientManager.add(clientPtr1);
    EXPECT_EQ(clientManager.count(), static_cast<size_t>(1));
    clientManager.add(clientPtr2);
    clientManager.add(clientPtr3);
    EXPECT_EQ(clientManager.count(), static_cast<size_t>(3));
    clientManager.remove(clientPtr2);
    EXPECT_EQ(clientManager.count(), static_cast<size_t>(2));
    clientManager.add(clientPtr4);
    EXPECT_EQ(clientManager.count(), static_cast<size_t>(3));

    const std::set<sckcpp::ClientPtr>           clients = clientManager.getClients();
    std::set<sckcpp::ClientPtr>::const_iterator it = clients.begin();

    for (size_t i = 0; i < clients.size(); ++i)
    {
        EXPECT_NE(*it, clientPtr2);
        ++it;
    }

}

//!
//! @test Foreach callback function test.
//!
TEST (ClientManger, foreach)
{
    boost::asio::io_service             ioService;
    sckcpp::ClientPtr                   clientPtr1 = sckcpp::helper::createClient(ioService);
    sckcpp::ClientPtr                   clientPtr2 = sckcpp::helper::createClient(ioService);
    sckcpp::ClientPtr                   clientPtr3 = sckcpp::helper::createClient(ioService);
    sckcpp::ClientPtr                   clientPtr4 = sckcpp::helper::createClient(ioService);
    spcbttl::server::net::ClientManager clientManager;
    std::string                         outStdout;
    std::string                         outStderr;

    clientManager.add(clientPtr1);
    clientManager.add(clientPtr2);
    clientManager.add(clientPtr3);
    clientManager.add(clientPtr4);
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();
    clientManager.foreach([=](boost::shared_ptr<sckcpp::Client>){
        std::cout << "TEST!" << std::endl;
    });
    outStdout = testing::internal::GetCapturedStdout();
    outStderr = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(outStderr.empty());
    EXPECT_STRCASEEQ(outStdout.c_str(), "TEST!\nTEST!\nTEST!\nTEST!\n");
}