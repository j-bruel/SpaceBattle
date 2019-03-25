#include <mutex>
#include <queue>
#include <boost/optional.hpp>

#ifndef CONCURRENTQUEUE_HPP_
#define CONCURRENTQUEUE_HPP_

namespace spcbttl
{
namespace client
{
namespace tool
{

template <class T>
class ConcurrentQueue
{

  public:
    ConcurrentQueue() = default;
    ~ConcurrentQueue() = default;

    void push(T item)
    {
        _mutex.lock();
        _queue.push(item);
        _mutex.unlock();
    }

    boost::optional<T> pop() 
    {
        if (_mutex.try_lock())
        {
            T item = _queue.front();
            _queue.pop();
            _mutex.unlock();
            return boost::optional<T>(item);
        }
        return boost::optional<T>();
    }

    uint size()
    {
        return _queue.size();
    }

  private:
    std::mutex _mutex;
    std::queue<T> _queue;

};
}
}
}

#endif /* CONCURRENTQUEUE_HPP_ */