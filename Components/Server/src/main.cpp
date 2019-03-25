//!
//! @file src/main.cpp
//! @author bruel_a
//! @date 22/10/18
//!

#include <Commun/Exception/HelpException.hpp>
#include "Core/SpaceBattle.hpp"
#include <iostream>

int     main(int argc, const char * const *argv)
{
    spcbttl::server::core::SpaceBattle  spaceBattle;

    try {
        spaceBattle.init(argc, argv);
        spaceBattle.run();
    }
    catch (spcbttl::HelpException &) {
        return (EXIT_SUCCESS);
    }
    catch (spcbttl::IException &e) {
        std::cerr << e.what() << std::endl;
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}