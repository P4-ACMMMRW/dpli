include(AddCatch2)

file(GLOB_RECURSE TEST_SOURCES "*.cpp")
add_executable(unit_tests ${TEST_SOURCES})

target_include_directories(unit_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(unit_tests PRIVATE dpllib Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(unit_tests)