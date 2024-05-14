#include <TestingUtil.hpp>
#include <Value.hpp>

using namespace dplgrammar;

EVAL_TEST("gcd.dpl") {
    std::vector<std::pair<std::string, dplsrc::Value>> expectedVarVec;
    std::vector<std::string> expectedOutputLines;

    expectedOutputLines.push_back("5");

    dplutil::TestingUtil::testEval("gcd.dpl", expectedVarVec, expectedOutputLines);
}