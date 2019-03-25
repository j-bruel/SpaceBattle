//!
//! @file Subject.hpp
//! @author jbruel
//! @date 12/11/18
//!

#ifndef SPACEBATTLE_CLIENT_TOOLS_SUBJECT_HPP
# define SPACEBATTLE_CLIENT_TOOLS_SUBJECT_HPP

#include <vector>
#include <algorithm>
#include <mutex>
#include "Tools/Observer.hpp"

//!
//! @namespace spcbttl
//!
namespace spcbttl
{
//!
//! @namespace client
//!
namespace client
{
//!
//! @namespace tool
//!
namespace tool
{
    //!
    //! @class Subject
    //! @brief Templated subject.
    //!
    template <class T>
    class   Subject
    {
    private:
        std::vector<Observer<T> *>  mObservers; //!< Observers classes.
        std::mutex                  mMutex; //!< Multi-threads safe.

    public:
        //!
        //! @brief Constructor
        //!
        Subject() = default;
        //!
        //! @brief Copy constructor.
        //! @warning Not available.
        //!
        Subject(const Subject &) {}
        //!
        //! @brief Equal operator overload.
        //! @warning Not available.
        //!
        Subject &operator=(const Subject &) = default;
        //!
        //! @brief Destructor.
        //!
        virtual ~Subject() = default;

    public:
        //!
        //! @brief Attach a subject to a observer.
        //! @param observer Observer class.
        //!
        void    attach(Observer<T> *observer)
        {
            mMutex.lock();
            mObservers.push_back(observer);
            mMutex.unlock();
        }
        //!
        //! @brief Notify all observers.
        //!
        void        notify()
        {
            mMutex.lock();
            for (size_t i = 0; i < mObservers.size(); ++i)
                (mObservers[i])->update(static_cast<T *>(this));
            mMutex.unlock();
        }
    };
}
}
}


#endif //SPACEBATTLE_CLIENT_TOOLS_SUBJECT_HPP
