#include <iostream>
#include <sckcpp/TcpClientSocket.hpp>
#include <msgpack.hpp>
#include <Commun/Network/Packet.hpp>
#include "Commun/Network/Requests/AuthenticateReq.hpp"
#include <memory>
#include "Commun/Tools/BufferDataManager.hpp"
#include "Commun/Engine/Ships.hpp"
class   NetTest
{
private:
    boost::asio::io_service                         mIOService;
    sckcpp::tcp::ClientSocket                       mClientSocket;
    std::tuple<int, bool, std::string, long int>    mTuple;

public:
    NetTest() : mIOService(), mClientSocket(mIOService), mTuple(std::make_tuple(42, false, "hello world", 12.3456)) {}

public:
    void    run()
    {
        msgpack::sbuffer    sb;
        msgpack::sbuffer    sbBody;
        spcbttl::commun::net::Packet    packet;
        spcbttl::commun::net::req::AuthenticateReq auth;
//        spcbttl::commun::net::req::AuthenticateReq   authenticateReq;

//        authenticateReq.setPlayerName("TestName");
        packet.mPacketHeader.mCmdType = spcbttl::commun::net::req::Type::AUTHENTICATE_REQ;
        packet.mPacketHeader.mClientId = 3;
        auth.setPlayerName("Player test.");
        packet.mPacketBody = std::make_shared<spcbttl::commun::net::req::AuthenticateReq>(auth);
//        spcbttl::commun::net::req::IRequest   *request = new spcbttl::commun::net::req::AuthenticateReq(authenticateReq);

//        msgpack::pack(sb, mTuple);
        msgpack::pack(sb, packet.mPacketHeader);
        msgpack::pack(sbBody, auth);
        mClientSocket.forceConnectionStatusHas(true);
        mClientSocket.asyncConnect("127.0.0.1", 4242, [=]() {
            std::cout << "Client: I'm connected to the server." << std::endl;
        });
        mClientSocket.asyncWrite(sb.data(), sb.size(), [&](size_t) {
            std::cout << "Client: Try to write a AUTH header to the server, size : " << sb.size() << std::endl;
        });
        mClientSocket.asyncWrite(sbBody.data(), sbBody.size(), [&](size_t) {
            std::cout << "Client: Try to write a AUTH body to the server, size : " << sbBody.size() << std::endl;
        });
        mClientSocket.asyncWrite(sb.data(), sb.size(), [&](size_t) {
            std::cout << "Client: Try to write a AUTH header to the server, size : " << sb.size() << std::endl;
        });
        mClientSocket.asyncWrite(sbBody.data(), sbBody.size(), [&](size_t) {
            std::cout << "Client: Try to write a AUTH body to the server, size : " << sbBody.size() << std::endl;
        });
        mClientSocket.asyncWrite(sb.data(), sb.size(), [&](size_t) {
            std::cout << "Client: Try to write a AUTH header to the server, size : " << sb.size() << std::endl;
        });
        mClientSocket.asyncWrite(sbBody.data(), sbBody.size(), [&](size_t) {
            std::cout << "Client: Try to write a AUTH body to the server, size : " << sbBody.size() << std::endl;
        });
        start();
        mClientSocket.run();
    }

private:
    void    processReadLoop()
    {
        char    *test = (char *)malloc(100);

        memset(test, 0, 100);
        std::cout << "ASYNCHR read ..." << std::endl;
        mClientSocket.asyncRead(test, 5, [=](size_t size) {
            std::cout << "SIZE: " << size << std::endl;
            std::cout << "Client: Received a package from the server : " << test << std::endl;
            processReadLoop();
        });
    }

    inline void start() { processReadLoop(); }

};

int     main()
{
    NetTest net;

    net.run();
    return (EXIT_SUCCESS);

}