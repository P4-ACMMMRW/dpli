# For Visual C++ compilers only
if(MSVC)
    set(ANTLR4_WITH_STATIC_CRT OFF)
else()
    add_definitions(-DANTLR4CPP_STATIC)
endif()

include(ExternalAntlr4Cpp)

set(ANTLR_EXECUTABLE ${PROJECT_SOURCE_DIR}/lib/antlr/antlr-4.13.1-complete.jar)

find_package(ANTLR REQUIRED)

# ANTLR targets
antlr_target(DplLexer ../grammar/DplLexer.g4 LEXER
             PACKAGE dplgrammar
             OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/antlr4cpp_generated_src/DplLexer/grammar)
antlr_target(DplParser ../grammar/DplParser.g4 PARSER
             PACKAGE dplgrammar
             DEPENDS_ANTLR DplLexer
             OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/antlr4cpp_generated_src/DplParser/grammar
             COMPILE_FLAGS -lib ${ANTLR_DplLexer_OUTPUT_DIR} -visitor)

message(STATUS "ANTLR_DplLexer_OUTPUT_DIR: ${ANTLR_DplLexer_OUTPUT_DIR}")
message(STATUS "ANTLR_DplParser_OUTPUT_DIR: ${ANTLR_DplParser_OUTPUT_DIR}")

add_library(dpllib ${ANTLR_DplLexer_CXX_OUTPUTS} ${ANTLR_DplParser_CXX_OUTPUTS})
target_include_directories(dpllib INTERFACE ${ANTLR_DplLexer_OUTPUT_DIR} ${ANTLR_DplParser_OUTPUT_DIR} ${PROJECT_SOURCE_DIR}/lib/argz ${PROJECT_SOURCE_DIR}/include/src)
target_link_libraries(dpllib antlr4_static)