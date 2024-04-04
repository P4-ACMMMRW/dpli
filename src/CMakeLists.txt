add_library(dpllib STATIC ${ANTLR_DplLexer_CXX_OUTPUTS} ${ANTLR_DplParser_CXX_OUTPUTS})
target_include_directories(dpllib PUBLIC ${ANTLR_DplLexer_OUTPUT_DIR} ${ANTLR_DplParser_OUTPUT_DIR} ${PROJECT_SOURCE_DIR}/lib/argz ${PROJECT_SOURCE_DIR}/include/src)

target_link_libraries(dpllib PUBLIC antlr4_static)
