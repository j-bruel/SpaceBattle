//
// Created by grosso_a on 11/11/18.
//

#ifndef T_CPP_SPACEBATTLE_2018_DISPATCHEREXCEPTION_HPP
#define T_CPP_SPACEBATTLE_2018_DISPATCHEREXCEPTION_HPP

# include "Commun/Exception/IException.hpp"

//!
//! @namespace spcbttl
//!
namespace spcbttl
{
    //!
    //! @class DispatcherException
    //! @brief Dispatcher exception.
    //!
    class   DispatcherException : public IException
    {
    public:
        //!
        //! @brief Default constructor.
        //! @param msg Exception message.
        //!
        explicit DispatcherException(const std::string &msg) : IException(msg) { }
    };
}

#endif //T_CPP_SPACEBATTLE_2018_DISPATCHEREXCEPTION_HPP
