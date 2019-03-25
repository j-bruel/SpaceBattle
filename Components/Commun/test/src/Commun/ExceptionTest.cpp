//!
//! @file ExceptionTest.cpp
//! @author jbruel
//! @date 01/11/18
//!

#include "Commun/Exception/ConfException.hpp"
#include "Commun/Exception/CoreException.hpp"
#include "Commun/Exception/HelpException.hpp"
#include "Commun/Exception/BufferDataManagerException.hpp"
#include <gtest/gtest.h>

//!
 //! @test Conf exception
 //!
TEST (Exception, conf)
{
    try {
        throw spcbttl::ConfException("Conf exception test.");
    }
    catch (spcbttl::IException &e) {
        EXPECT_STRCASEEQ(e.what(), "Conf exception test.");
        return ;
    }
    FAIL() << "IException excepted.";
}

//!
//! @test Core exception
//!
TEST (Exception, core)
{
    try {
        throw spcbttl::CoreException("Core exception test.");
    }
    catch (spcbttl::IException &e) {
        EXPECT_STRCASEEQ(e.what(), "Core exception test.");
        return ;
    }
    FAIL() << "IException excepted.";
}

//!
//! @test Help exception
//!
TEST (Exception, help)
{
    try {
        throw spcbttl::HelpException("Help exception test.");
    }
    catch (spcbttl::IException &e) {
        EXPECT_STRCASEEQ(e.what(), "Help exception test.");
        return ;
    }
    FAIL() << "IException excepted.";
}

//!
//! @test Buffer Data Manager exception
//!
TEST (Exception, bufferDataManager)
{
    try {
        throw spcbttl::BufferDataManagerException("BufferDataManager exception test.");
    }
    catch (spcbttl::IException &e) {
        EXPECT_STRCASEEQ(e.what(), "BufferDataManager exception test.");
        return ;
    }
    EXPECT_TRUE(false);
}