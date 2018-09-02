cmake_minimum_required(VERSION 2.8)

project("dsa_test_algorithms")

file(GLOB TEST_ALG_SRC "./*.cpp" "./*.hpp")

add_executable(test_algorithms ${TEST_ALG_SRC})
target_link_libraries(test_algorithms dsa ${Boost_LIBRARIES})

install(TARGETS test_algorithms DESTINATION .)
