cmake_minimum_required(VERSION 2.8)

# properties
project("dsa")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -g")
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_LIST_DIR}/bin")

# dependencies
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost 1.67.0 COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

include_directories("dsa")

# main project
file(GLOB DS_SRC "dsa/data_structures/*.cpp" "dsa/data_structures/*.hpp")
file(GLOB ALG_SRC "dsa/algorithms/*.cpp" "dsa/algorithms/*.hpp")
add_library(dsa STATIC ${DS_SRC} ${ALG_SRC})
# todo: add_subdirectory(proj_lib)

# tests
file(GLOB TEST_SRC "./tests/*.cpp" "./tests/*.hpp")
add_executable(tests ${TEST_SRC})
target_link_libraries(tests dsa ${Boost_LIBRARIES})

# output
install(TARGETS tests DESTINATION .)
