//!
//! @file main.cpp
//! @author bruel_a
//! @date 27/10/18
//!

#include "Commun/UTWorkDirectory.hpp"
#include <string>
#include <gtest/gtest.h>

int main(int argc, char **argv)
{
    system(std::string(std::string("mkdir ") + UTWorkDirectory).c_str());

    testing::InitGoogleTest(&argc, argv);

    int ret = RUN_ALL_TESTS();

    system(std::string(std::string("rm -rf ") + UTWorkDirectory).c_str());
    return (ret);
}