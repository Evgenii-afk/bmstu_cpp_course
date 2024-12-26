cmake_minimum_required(VERSION 3.10)
project(StringTest)

set(CMAKE_CXX_STANDARD 11)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(StringTest homework_2.cpp StringTest.cpp)

target_link_libraries(StringTest ${GTEST_LIBRARIES} pthread)