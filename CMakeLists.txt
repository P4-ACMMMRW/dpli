cmake_minimum_required(VERSION 3.7 FATAL_ERROR)
project(dpl)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 17)

# For Visual C++ compilers only
set(ANTLR4_WITH_STATIC_CRT OFF)

add_definitions(-DANTLR4CPP_STATIC)

include(ExternalAntlr4Cpp)
include_directories(${ANTLR4_INCLUDE_DIRS})

set(ANTLR_EXECUTABLE ${PROJECT_SOURCE_DIR}/lib/antlr/antlr-4.13.1-complete.jar)

find_package(ANTLR REQUIRED)

# ANTLR targets
antlr_target(DplLexer grammar/DplLexer.g4 LEXER
             PACKAGE dplgrammar
             OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/antlr4cpp_generated_src/DplLexer/grammar)
antlr_target(DplParser grammar/DplParser.g4 PARSER
             PACKAGE dplgrammar
             DEPENDS_ANTLR DplLexer
             OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/antlr4cpp_generated_src/DplParser/grammar
             COMPILE_FLAGS -lib ${ANTLR_DplLexer_OUTPUT_DIR})

message(STATUS "ANTLR_DplLexer_OUTPUT_DIR: ${ANTLR_DplLexer_OUTPUT_DIR}")
message(STATUS "ANTLR_DplParser_OUTPUT_DIR: ${ANTLR_DplParser_OUTPUT_DIR}")

# Include generated files in project environment
include_directories(${ANTLR_DplLexer_OUTPUT_DIR})
include_directories(${ANTLR_DplParser_OUTPUT_DIR})

# Add generated grammar binary target
add_executable(dplc src/Main.cpp
               ${ANTLR_DplLexer_CXX_OUTPUTS}
               ${ANTLR_DplParser_CXX_OUTPUTS})
target_link_libraries(dplc antlr4_static)