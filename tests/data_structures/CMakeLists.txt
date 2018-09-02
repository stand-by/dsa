cmake_minimum_required(VERSION 2.8)

project("dsa_test_data_structures")

file(GLOB TEST_DS_SRC "./*.cpp" "./*.hpp")

add_executable(test_data_structures ${TEST_DS_SRC})
target_link_libraries(test_data_structures dsa ${Boost_LIBRARIES})

install(TARGETS test_data_structures DESTINATION .)
