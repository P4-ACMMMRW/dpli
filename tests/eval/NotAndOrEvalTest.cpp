#include <TestingUtil.hpp>
#include <Value.hpp>

using namespace dplgrammar;

EVAL_TEST("not_and_or.dpl") {
    std::vector<std::pair<std::string, dplsrc::Value>> expectedVarVec;
    std::vector<std::string> expectedOutputLines;

    expectedOutputLines.push_back("test");

    expectedVarVec.push_back(std::make_pair("x", dplsrc::Value(false)));

    dplutil::TestingUtil::testEval("not_and_or.dpl", expectedVarVec, expectedOutputLines);
}