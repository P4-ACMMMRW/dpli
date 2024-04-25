cmake_minimum_required(VERSION 3.7 FATAL_ERROR)
project(dpl)

enable_testing()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Can not be upgraded to C++20 because of a bug in github actions with chrono header
set(CMAKE_CXX_STANDARD 17)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(ANTLR4_WITH_STATIC_CRT ON)
add_definitions(-DANTLR4CPP_STATIC)

if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

include(ExternalAntlr4Cpp)

set(ANTLR_EXECUTABLE ${PROJECT_SOURCE_DIR}/lib/antlr/antlr-4.13.1-complete.jar)

find_package(ANTLR REQUIRED)

# ANTLR targets
antlr_target(DplLexer ${PROJECT_SOURCE_DIR}/grammar/DplLexer.g4 LEXER
             PACKAGE dplgrammar
             OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/antlr4cpp_generated_src/DplLexer/grammar)
antlr_target(DplParser ${PROJECT_SOURCE_DIR}/grammar/DplParser.g4 PARSER
             PACKAGE dplgrammar
             DEPENDS_ANTLR DplLexer
             OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/antlr4cpp_generated_src/DplParser/grammar
             COMPILE_FLAGS -lib ${ANTLR_DplLexer_OUTPUT_DIR} -visitor)

message(STATUS "ANTLR_DplLexer_OUTPUT_DIR: ${ANTLR_DplLexer_OUTPUT_DIR}")
message(STATUS "ANTLR_DplParser_OUTPUT_DIR: ${ANTLR_DplParser_OUTPUT_DIR}")

message(STATUS "ANTLR_DplLexer_CXX_OUTPUTS: ${ANTLR_DplLexer_CXX_OUTPUTS}")
message(STATUS "ANTLR_DplParser_CXX_OUTPUTS: ${ANTLR_DplParser_CXX_OUTPUTS}")

add_library(dpllib STATIC ${ANTLR_DplLexer_CXX_OUTPUTS} ${ANTLR_DplParser_CXX_OUTPUTS})
target_include_directories(dpllib PUBLIC ${ANTLR_DplLexer_OUTPUT_DIR} ${ANTLR_DplParser_OUTPUT_DIR} ${PROJECT_SOURCE_DIR}/lib/argz ${PROJECT_SOURCE_DIR}/include/src)

target_link_libraries(dpllib PUBLIC antlr4_static)

add_executable(dpli Main.cpp)

target_include_directories(dpli PRIVATE ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/include/src)

target_link_libraries(dpli PRIVATE dpllib antlr4_static)

add_subdirectory(tests)

# Strip debug symbols in Release mode
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_custom_command(TARGET dpli POST_BUILD COMMAND ${CMAKE_STRIP} $<TARGET_FILE:dpli>)
endif()