cmake_minimum_required(VERSION 3.7 FATAL_ERROR)
project(dpl)

enable_testing()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 20)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif()

add_subdirectory(src)

add_executable(dpli Main.cpp)
target_include_directories(dpli PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(dpli PRIVATE dpllib)

add_subdirectory(tests)
