include(AddCatch2)

file(GLOB_RECURSE TEST_SOURCES "*.cpp")
add_executable(dpli_tests ${TEST_SOURCES})

target_include_directories(dpli_tests PRIVATE ${PROJECT_SOURCE_DIR}/include/tests)
target_link_libraries(dpli_tests PRIVATE dpllib Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(dpli_tests)