include(AddCatch2)

file(GLOB_RECURSE TEST_SOURCES "*.cpp")
add_executable(unit_tests ${TEST_SOURCES})

target_include_directories(unit_tests PRIVATE ${PROJECT_SOURCE_DIR}/include/tests)
target_link_libraries(unit_tests PRIVATE dpllib Catch2::Catch2WithMain)

set_property(TARGET unit_tests PROPERTY CXX_STANDARD 17)

include(CTest)
include(Catch)
catch_discover_tests(unit_tests)