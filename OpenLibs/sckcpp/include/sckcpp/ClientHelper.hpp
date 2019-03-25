//!
//! @file ClientHelper.hpp
//! @author jbruel
//! @date 11/11/18
//!

#ifndef SCKCPP_CLIENTHELPER_HPP
#define SCKCPP_CLIENTHELPER_HPP

#include "sckcpp/Client.hpp"

namespace sckcpp
{

    namespace helper
    {
        //! Helper for create new client
        //! \param io_service
        //! \return
        static ClientPtr createClient(boost::asio::io_service &io_service)
        {
            return boost::make_shared<Client>(io_service);
        }
    }
}

#endif //SCKCPP_CLIENTHELPER_HPP
