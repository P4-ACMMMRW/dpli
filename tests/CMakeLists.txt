include(AddCatch2)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /MT")
endif()

file(GLOB_RECURSE TEST_SOURCES "*.cpp")
add_executable(unit_tests ${TEST_SOURCES})

target_include_directories(unit_tests PRIVATE ${PROJECT_SOURCE_DIR}/include/tests)
target_link_libraries(unit_tests PRIVATE dpllib Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(unit_tests)