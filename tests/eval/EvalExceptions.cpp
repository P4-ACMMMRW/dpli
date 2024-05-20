#include "TestingUtil.hpp"
#include "Value.hpp"

using namespace dplgrammar;

EVAL_EXCEPTION_TEST("assign_leftside_exception.dpl") {
    dplutil::TestingUtil::testEvalException("assign_leftside_exception.dpl");
}

EVAL_EXCEPTION_TEST("assign_unequal_column_exception.dpl") {
    dplutil::TestingUtil::testEvalException("assign_unequal_column_exception.dpl");
}

EVAL_EXCEPTION_TEST("filter_column_exception.dpl") {
    dplutil::TestingUtil::testEvalException("filter_column_exception.dpl");
}

EVAL_EXCEPTION_TEST("header_not_in_table_exception.dpl") {
    dplutil::TestingUtil::testEvalException("header_not_in_table_exception.dpl");
}

EVAL_EXCEPTION_TEST("header_not_on_table_exception.dpl") {
    dplutil::TestingUtil::testEvalException("header_not_on_table_exception.dpl");
}

EVAL_EXCEPTION_TEST("index_string_exception.dpl") {
    dplutil::TestingUtil::testEvalException("index_string_exception.dpl");
}

EVAL_EXCEPTION_TEST("index_not_integer_exception.dpl") {
    dplutil::TestingUtil::testEvalException("index_not_integer_exception.dpl");
}

EVAL_EXCEPTION_TEST("index_out_of_range_exception.dpl") {
    dplutil::TestingUtil::testEvalException("index_out_of_range_exception.dpl");
}

EVAL_EXCEPTION_TEST("string_out_of_range_exception.dpl") {
    dplutil::TestingUtil::testEvalException("string_out_of_range_exception.dpl");
}

EVAL_EXCEPTION_TEST("column_out_of_range_exception.dpl") {
    dplutil::TestingUtil::testEvalException("column_out_of_range_exception.dpl");
}

EVAL_EXCEPTION_TEST("index_not_indexable_exception.dpl") {
    dplutil::TestingUtil::testEvalException("index_not_indexable_exception.dpl");
}

EVAL_EXCEPTION_TEST("intersection_not_same_header_exception.dpl") {
    dplutil::TestingUtil::testEvalException("intersection_not_same_header_exception.dpl");
}

EVAL_EXCEPTION_TEST("intersection_not_on_tables_exception.dpl") {
    dplutil::TestingUtil::testEvalException("intersection_not_on_tables_exception.dpl");
}

EVAL_EXCEPTION_TEST("intersection_table_not_same_size_exception.dpl") {
    dplutil::TestingUtil::testEvalException("intersection_table_not_same_size_exception.dpl");
}

EVAL_EXCEPTION_TEST("procedure_call_undefined_exception.dpl") {
    dplutil::TestingUtil::testEvalException("procedure_call_undefined_exception.dpl");
}

EVAL_EXCEPTION_TEST("procedure_call_incorrect_param_amount_exception.dpl") {
    dplutil::TestingUtil::testEvalException("procedure_call_incorrect_param_amount_exception.dpl");
}

EVAL_EXCEPTION_TEST("return_not_in_function_exception.dpl") {
    dplutil::TestingUtil::testEvalException("return_not_in_function_exception.dpl");
}

EVAL_EXCEPTION_TEST("table_header_not_string_exception.dpl") {
    dplutil::TestingUtil::testEvalException("table_header_not_string_exception.dpl");
}

EVAL_EXCEPTION_TEST("table_value_not_list_exception.dpl") {
    dplutil::TestingUtil::testEvalException("table_value_not_list_exception.dpl");
}

EVAL_EXCEPTION_TEST("table_column_not_same_size_exception.dpl") {
    dplutil::TestingUtil::testEvalException("table_column_not_same_size_exception.dpl");
}

EVAL_EXCEPTION_TEST("union_not_on_tables_exception.dpl") {
    dplutil::TestingUtil::testEvalException("union_not_on_tables_exception.dpl");
}
