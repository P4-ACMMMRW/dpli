cmake_minimum_required(VERSION 3.7 FATAL_ERROR)
project(dpl)

enable_testing()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)


add_executable(dpli Main.cpp)
target_link_libraries(dpli PRIVATE dpllib)

add_subdirectory(tests)
