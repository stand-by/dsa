cmake_minimum_required(VERSION 2.8)

# properties
project("dsa")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -g")
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_LIST_DIR}/bin")

# dependencies
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost 1.67.0 COMPONENTS system filesystem unit_test_framework graph REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

include_directories("dsa")

# main project
add_subdirectory(dsa)

# tests
add_subdirectory(tests/data_structures)
add_subdirectory(tests/algorithms)
