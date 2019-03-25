//!
//! @file Commun/Tools/BufferDataManager.cpp
//! @author jbruel
//! @date 11/11/18
//!

#include "Commun/Tools/BufferDataManager.hpp"
#include "Commun/Exception/BufferDataManagerException.hpp"
#include "Commun/Tools/Log/Idx.hpp"
#include <plog/Log.h>

namespace spcbttl
{
namespace commun
{
namespace tool
{

    template <class T>
    BufferDataManager<T>::BufferDataManager(const BufferDataManager<T> &manager)
    {
        if (this == &manager)
            return ;
        mQueue = manager.mQueue;
    }

    template <class T>
    BufferDataManager<T>    &BufferDataManager<T>::operator=(const BufferDataManager<T> &bufferDataManager)
    {
        mQueue = bufferDataManager.mQueue;

        return (*this);
    }

    template <class T>
    void    BufferDataManager<T>::push_back(const T &element)
    {
        std::unique_lock<std::mutex>    lock(mLock);

        mQueue.push_back(element);
        mCondVar.notify_one();
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::info) << "A packet as been push on the packet stack.";
    }

    template <class T>
    const T  BufferDataManager<T>::pop_front(int wait)
    {
        std::unique_lock<std::mutex> lock(mLock);
        auto                         next = std::chrono::system_clock::now() + std::chrono::milliseconds(wait);

        while (empty())
        {
            if (mCondVar.wait_until(lock, next) == std::cv_status::timeout)
                throw BufferDataManagerException("Empty queue.");
        }

        const T  frontElement = mQueue.front();

        mQueue.pop_front();
        LOG_(tool::log::IN_FILE_AND_CONSOLE, plog::info) << "A packet as been pop on the packet stack.";
        return (frontElement);
    }

    template <class T>
    void    BufferDataManager<T>::clear()
    {
        std::unique_lock<std::mutex> lock(mLock);

        mQueue.clear();
    }

    template <class T>
    const T BufferDataManager<T>::front(int wait) const
    {
        std::unique_lock<std::mutex> lock(mLock);
        auto                         next = std::chrono::system_clock::now() + std::chrono::milliseconds(wait);

        while (this->empty())
        {
            if(mCondVar.wait_until(lock, next) == std::cv_status::timeout)
                throw BufferDataManagerException("Empty queue.");
        }
        return (mQueue.front());
    }

    template <class T>
    const T BufferDataManager<T>::back(int wait) const
    {
        std::unique_lock<std::mutex> lock(mLock);
        auto                         next = std::chrono::system_clock::now() + std::chrono::milliseconds(wait);

        while (this->empty())
        {
            if(this->mCondVar.wait_until(lock, next) == std::cv_status::timeout)
                throw BufferDataManagerException("Empty queue.");
        }
        return (mQueue.back());
    }

    template <class T>
    void    BufferDataManager<T>::reverse()
    {
        std::unique_lock<std::mutex> lock(mLock);

        mQueue.reverse();
    }

}
}
}