//!
//! @file Singleton.hpp
//! @author jbruel
//! @date 10/11/18
//!

#ifndef SPACEBATTLE_COMMUN_TOOLS_SINGLETON_HPP
# define SPACEBATTLE_COMMUN_TOOLS_SINGLETON_HPP

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
    //! @class Singleton
    //! @param T
    //! @brief Singleton patern abstract
    //!
    template <class T>
    class Singleton
    {
    public:
        //!
        //! @brief Get instance
        //! @return T instance
        //!
        static T &Instance();

    protected:
        static T mInstance; //!< Static call singleton

    private:
        //!
        //! @brief Equal operator overload
        //! @return T
        //!
        T   &operator=(const T&) { }
    };

    template<class T>
    T Singleton<T>::mInstance = T();

    template<class T>
    T &Singleton<T>::Instance() { return (mInstance); }

}
}
}

#endif //SPACEBATTLE_COMMUN_TOOLS_SINGLETON_HPP
