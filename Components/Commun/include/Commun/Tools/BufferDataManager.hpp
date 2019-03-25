//!
//! @file Commun/Tools/BufferDataManager.hpp
//! @author jbruel
//! @date 10/11/18
//!

#ifndef SPACEBATTLE_COMMUN_TOOLS_BUFFERDATEMANAGER_HPP
# define SPACEBATTLE_COMMUN_TOOLS_BUFFERDATEMANAGER_HPP

# include "Commun/Tools/Singleton.hpp"
# include <list>
# include <mutex>
# include <condition_variable>

//!
//! @namespace spcbttl
//!
namespace spcbttl
{
//!
//! @namespace commun
//!
namespace commun
{
//!
//! @namespace tool
//!
namespace tool
{

    //!
    //! @class BufferDataManager
    //! @tparam T
    //! @brief Generic buffer data manager.
    //!
    template <class T>
    class   BufferDataManager : public Singleton<BufferDataManager<T>>
    {
        friend class Singleton<BufferDataManager<T>>; //!< Allow current class to become singleton.

    private:
        std::list<T>                    mQueue; //!< Intern date queue.
        mutable std::mutex              mLock; //!< Motex locker.
        mutable std::condition_variable mCondVar; //!< Condition variable.

    public:
        //!
        //! @brief Default constructor
        //!
        BufferDataManager<T>() = default;

    private:
        //!
        //! @brief Copy constructor
        //! @param manager Generic buffer data manager.
        //!
        BufferDataManager<T>(const BufferDataManager<T> &manager);
        //!
        //! @brief Equal overload operator
        //! @param bufferDataManager Generic buffer data manager.
        //!
        BufferDataManager<T> &operator=(const BufferDataManager<T> &bufferDataManager);
        //!
        //! @brief Destructor.
        //!
        ~BufferDataManager<T>() = default;

    public:
        //!
        //! @brief Check if the buffer is currently empty.
        //! @return State.
        //!
        inline bool empty() const
        {
            return (mQueue.empty());
        }

        //!
        //! @brief Give buffer size.
        //! @return Current buffer size.
        //!
        inline size_t size() const
        {
            return (mQueue.size());
        }

    public:
        //!
        //! @brief Add a element at the end of the buffer.
        //! @param element Pushed element.
        //!
        void    push_back(const T &element);

        //!
        //! @brief Supprime un élément au debut du buffer
        //! @param wait element Removed element.
        //!
        const T  pop_front(int wait = 1000);

    public:
        //!
        //! @brief Clear buffer.
        //!
        void    clear();

    public:
        //!
        //! @brief Extract the first element without pop it.
        //! @return wait First element.
        //!
        const T front(int wait = 1000) const;
        //!
        //! @brief Extract last element.
        //! @return Last queue element.
        //!
        const T back(int wait = 1000) const;
        //!
        //! @brief Extract all buffer variables.
        //! @return Complet buffer.
        //!
        inline const std::list<T>   get() const { return (mQueue); }

    public:
        //!
        //! @brief Reverse buffer stack order.
        //!
        void    reverse();
    };

}
}
}

# include "Commun/Tools/BufferDataManager.cpp"


#endif //SPACEBATTLE_COMMUN_TOOLS_BUFFERDATEMANAGER_HPP
