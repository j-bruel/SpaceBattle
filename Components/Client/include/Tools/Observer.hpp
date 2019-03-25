//!
//! @file Observer.hpp
//! @author jbruel
//! @date 12/11/18
//!

#ifndef SPACEBATTLE_CLIENT_TOOLS_OBSERVER_HPP
# define SPACEBATTLE_CLIENT_TOOLS_OBSERVER_HPP

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
    //! @class Observer
    //! @brief Pattern observer
    //!
    template <class T>
    class Observer
    {
    public:
        //!
        //! @brief Constructor
        //!
        Observer() = default;
        //!
        //! @brief Copy constructor.
        //! @warning Not available.
        //!
        Observer(const Observer &) = delete;
        //!
        //! @brief Equal operator overload.
        //! @warning Not available.
        //!
        Observer &operator=(const Observer &) = delete;
        //!
        //! @brief Destructor.
        //!
        virtual ~Observer() = default;

    public:
        //!
        //! @brief Callback.
        //! @param subject Called subject.
        //!
        virtual void    update(T *subject) = 0;
    };

}
}
}

#endif //SPACEBATTLE_CLIENT_TOOLS_OBSERVER_HPP
