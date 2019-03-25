//!
//! @file BufferDataManager.cpp
//! @author jbruel
//! @date 11/11/18
//!

#include "Commun/Tools/BufferDataManager.hpp"
#include "Commun/Exception/BufferDataManagerException.hpp"
#include "Commun/Tools/Log/Idx.hpp"
#include <plog/Log.h>

namespace spcbttl
{
namespace client
{
namespace tool
{

    template <class T>
    BufferDataManager<T>::BufferDataManager(const BufferDataManager<T> &manager) : Subject<BufferDataManager<T>>(manager)
    {
        if (this == &manager)
            return ;
        mQueue = manager.mQueue;
    }

    template <class T>
    BufferDataManager<T>    &BufferDataManager<T>::operator=(const BufferDataManager<T> &bufferDataManager)
    {
        mQueue = bufferDataManager.mQueue;
        mLock = bufferDataManager.mLock;
        return (*this);
    }

    template <class T>
    void    BufferDataManager<T>::push_back(const T &element)
    {
        mLock.lock();
        mQueue.push_back(element);
        mLock.unlock();
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "A packet as been push on the packet stack.";
        Subject<BufferDataManager<T>>::notify();
    }

    template <class T>
    const T  BufferDataManager<T>::pop_front()
    {
        mLock.lock();

        const T frontElement = mQueue.front();

        mQueue.pop_front();
        mLock.unlock();
        LOG_(commun::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "A packet as been pop on the packet stack.";
        return (frontElement);
    }

    template <class T>
    void    BufferDataManager<T>::clear()
    {
        std::unique_lock<std::mutex> lock(mLock);

        mLock.lock();
        mQueue.clear();
        mLock.unlock();
    }

    template <class T>
    const T BufferDataManager<T>::front() const
    {
        mLock.lock();

        const T frontElement = mQueue.front();

        mLock.unlock();
        return (frontElement);
    }

    template <class T>
    const T BufferDataManager<T>::back() const
    {
        mLock.lock();

        const T backElement = mQueue.back();

        mLock.unlock();
        return (backElement);
    }

    template <class T>
    void    BufferDataManager<T>::reverse()
    {
        mLock.lock();
        mQueue.reverse();
        mLock.unlock();
    }

}
}
}