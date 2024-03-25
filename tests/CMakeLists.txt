include(AddSnitch)

file(GLOB_RECURSE TEST_SOURCES "*.cpp")
add_executable(unit_tests ${TEST_SOURCES})

target_include_directories(unit_tests PRIVATE ${PROJECT_SOURCE_DIR}/include/tests)
target_link_libraries(unit_tests PRIVATE dpllib snitch::snitch)