cmake_minimum_required(VERSION 2.8)

project("dsa")

file(GLOB DS_SRC "./data_structures/*.cpp" "./data_structures/*.hpp")
file(GLOB ALG_SRC "./algorithms/*.cpp" "./algorithms/*.hpp")

add_library(dsa STATIC ${DS_SRC} ${ALG_SRC})
