//
// Created by brd6 on 26/09/17.
//

#include <iostream>
#include <tuple>
#include <boost/make_shared.hpp>
#include "sckcpp/Client.hpp"

namespace sckcpp
{
  Client::Client(boost::asio::io_service& ios) :
	  mSocket(ios),
      mIsFirstConnection(false),
      mIsAuthenticate(false),
	  mIsStopped(false),
      mOnStopClient(nullptr),
      unp(),
      mPacketManager()
{
    mSocket.setOnDisconnectCallback(
	    [=]() {

	      stop();

	    });
  }

    void Client::start()
    {
        mIsFirstConnection = true;
        mSocket.forceConnectionStatusHas(true);
        mIsAuthenticate = true;
        unp.reserve_buffer(window_size);
        processReadLoop();
    }

    void Client::stop()
    {
        if (mIsStopped)
            return;
        mSocket.close();
        mIsStopped = true;
        if (mOnStopClient != nullptr)
            mOnStopClient(shared_from_this());
    }

    boost::asio::ip::tcp::socket &Client::getSocket() { return mSocket.getSocket(); }

    void Client::processReadLoop()
    {
        mSocket.asyncRead(unp.buffer(), window_size, [&](size_t bytes_transferred) {
            unp.buffer_consumed(bytes_transferred);

            msgpack::object_handle  oh;

            while (unp.next(oh))
            {
                msgpack::object obj = oh.get();

                mPacketManager.packetReceived(obj, mSocket);
            }
            processReadLoop();
        });
    }

    void Client::setOnStopClientCallback(OnStopClientFunc onStopClient)
    {
        mOnStopClient = onStopClient;
    }

    void Client::sendCommand(std::string const &msg)
    {
        if (!mIsAuthenticate)
            return;
        if (!mSocket.isConnected())
          return ;
        mSocket.asyncWrite(msg.c_str(), msg.size());
    }

    std::string Client::getInfo()
    {
        return mSocket.getInfo();
    }

    void Client::sendServerDisconnectRequest()
    {
        if (!mIsAuthenticate)
            return;
    }

}
