##
## Cmake minimun version
##
cmake_minimum_required(VERSION 3.8.1)

##
## Projet Name
##
project(spacebattle-server)

##
## C++ Stantard compilation
##
set(CMAKE_CXX_STANDARD 14)

##
## Binary / Library location
##
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

##
## Flags
##
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG} -g3  -W -Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra")

##
## Cmake variables
##
set(SPACEBATTLE_OPENLIBS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../OpenLibs/")
set(SPACEBATTLE_BOOST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../OpenLibs/boost/boost_1_68_0")
set(SPACEBATTLE_SCKCPP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../OpenLibs/sckcpp")
set(SPACEBATTLE_GTEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../OpenLibs/googletest/googletest")
set(SPACEBATTLE_MSGPACK_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../OpenLibs/msgpack")
set(SPACEBATTLE_PLOG_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../OpenLibs/plog")
set(SPACEBATTLE_COMMUN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../Commun/")

##
## Headers included
##
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${SPACEBATTLE_SCKCPP_DIR}/include)
include_directories(${SPACEBATTLE_BOOST_DIR})
include_directories(${SPACEBATTLE_PLOG_DIR}/include)
include_directories(${SPACEBATTLE_MSGPACK_DIR}/include)
include_directories(${SPACEBATTLE_COMMUN_DIR}/test/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/test/include)
include_directories(${SPACEBATTLE_COMMUN_DIR}/include)
include_directories(${SPACEBATTLE_COMMUN_DIR}/test/include)

##
## Sources files
##
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ${SPACEBATTLE_COMMUN_DIR}/src/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp ${SPACEBATTLE_COMMUN_DIR}/include/*.hpp)

##
## Create binary / Link
##
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${INCLUDE_FILES})
target_link_libraries(${PROJECT_NAME}   pthread
                                        ${SPACEBATTLE_BOOST_DIR}/stage/lib/libboost_date_time.so
                                        ${SPACEBATTLE_BOOST_DIR}/stage/lib/libboost_regex.so
                                        ${SPACEBATTLE_BOOST_DIR}/stage/lib/libboost_serialization.so
                                        ${SPACEBATTLE_BOOST_DIR}/stage/lib/libboost_system.so
                                        ${SPACEBATTLE_BOOST_DIR}/stage/lib/libboost_thread.so
                                        ${SPACEBATTLE_BOOST_DIR}/stage/lib/libboost_wserialization.so
                                        ${SPACEBATTLE_BOOST_DIR}/stage/lib/libboost_program_options.so
                                        ${SPACEBATTLE_SCKCPP_DIR}/build/libsckcpp.a)

##
## Testing with gtests
##
enable_testing()

##
## GTests path variables
##
set(GTESTS_ROOT "${SPACEBATTLE_GTEST_DIR}")
set(GTESTS_INCLUDEDIR "${SPACEBATTLE_GTEST_DIR}/include")
set(GTESTS_LIBRARYDIR "${SPACEBATTLE_GTEST_DIR}/build")

##
## Add GTests headers
##
include_directories(${GTESTS_INCLUDEDIR})

##
## Enable testing
##
enable_testing()

##
## Sources files
##
file(GLOB_RECURSE SOURCE_TESTS_FILES    ${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp
                                        ${CMAKE_CURRENT_SOURCE_DIR}/test/*.hpp
                                        ${SPACEBATTLE_COMMUN_DIR}/test/src/*.cpp
                                        ${SPACEBATTLE_COMMUN_DIR}/test/include/*.hpp)
file(GLOB_RECURSE SOURCES_BINARY_FILES  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ${SPACEBATTLE_COMMUN_DIR}/src/*.cpp)
list(REMOVE_ITEM SOURCES_BINARY_FILES   ${CMAKE_SOURCE_DIR}/src/main.cpp)
list(FILTER SOURCES_BINARY_FILES EXCLUDE REGEX ".*src/main.cpp$")

##
## Create binary / Link
##
add_executable(${PROJECT_NAME}-ut           ${SOURCES_BINARY_FILES}
                                            ${SOURCE_TESTS_FILES})
target_link_libraries(${PROJECT_NAME}-ut    ${GTESTS_LIBRARYDIR}/libgtest.a
                                            ${GTESTS_LIBRARYDIR}/libgtest_main.a
                                            pthread
                                            ${SPACEBATTLE_BOOST_DIR}/stage/lib/libboost_date_time.so
                                            ${SPACEBATTLE_BOOST_DIR}/stage/lib/libboost_regex.so
                                            ${SPACEBATTLE_BOOST_DIR}/stage/lib/libboost_serialization.so
                                            ${SPACEBATTLE_BOOST_DIR}/stage/lib/libboost_system.so
                                            ${SPACEBATTLE_BOOST_DIR}/stage/lib/libboost_thread.so
                                            ${SPACEBATTLE_BOOST_DIR}/stage/lib/libboost_wserialization.so
                                            ${SPACEBATTLE_BOOST_DIR}/stage/lib/libboost_program_options.so
                                            ${SPACEBATTLE_SCKCPP_DIR}/build/libsckcpp.a)
