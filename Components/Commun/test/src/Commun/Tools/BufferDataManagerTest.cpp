//!
//! @file BufferDataManagerTest.cpp
//! @authors agrosso jbruel
//! @date 07/11/12
//!

#include <gtest/gtest.h>
#include <thread>
#include "Commun/Tools/BufferDataManager.hpp"

//!
//! @test Check id monothread function works
//!
TEST (BufferDataManager, SimpleUsage)
{
    spcbttl::commun::tool::BufferDataManager<int>   &buffer = spcbttl::commun::tool::BufferDataManager<int>::Instance();

    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();
    ASSERT_EQ(buffer.size(), static_cast<size_t>(0));
    buffer.push_back(10);
    ASSERT_EQ(buffer.size(), static_cast<size_t>(1));
    ASSERT_EQ(buffer.back(), 10);
    ASSERT_EQ(buffer.size(), static_cast<size_t>(1));
    ASSERT_EQ(buffer.pop_front(), 10);
    ASSERT_EQ(buffer.size(), static_cast<size_t>(0));
    testing::internal::GetCapturedStdout();
    testing::internal::GetCapturedStderr();
}

//!
//! @test Check if BufferDataManager is protected to multithread access
//!
TEST (BufferDataManager, MultiThread)
{
    spcbttl::commun::tool::BufferDataManager<int>   &buffer = spcbttl::commun::tool::BufferDataManager<int>::Instance();

    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();
    ASSERT_EQ(buffer.size(), static_cast<size_t>(0));
    ASSERT_THROW(buffer.pop_front(), spcbttl::BufferDataManagerException);
    std::thread([&buffer] {
        ASSERT_THROW(buffer.pop_front(), spcbttl::BufferDataManagerException);
    }).join();
    buffer.push_back(10);
    std::thread([&buffer] {
        ASSERT_EQ(buffer.pop_front(), 10);
    }).join();
    std::thread a([&buffer] {
        ASSERT_EQ(buffer.pop_front(), 10);
    });
    buffer.push_back(10);
    a.join();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::thread b([&buffer] {
        ASSERT_EQ(buffer.pop_front(10000), 10);
    });
    std::this_thread::sleep_for(std::chrono::seconds(3));
    buffer.push_back(10);
    b.join();
    testing::internal::GetCapturedStdout();
    testing::internal::GetCapturedStderr();
}
