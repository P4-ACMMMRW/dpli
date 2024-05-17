#include "TestingUtil.hpp"
#include "Value.hpp"

using namespace dplgrammar;

EVAL_TEST("continue.dpl") {
    std::vector<std::pair<std::string, dplsrc::Value>> expectedVarVec;
    std::vector<std::string> expectedOutputLines;

    expectedOutputLines.push_back("1");
    expectedOutputLines.push_back("3");
    expectedOutputLines.push_back("5");
    expectedOutputLines.push_back("7");
    expectedOutputLines.push_back("9");

    expectedVarVec.push_back(std::make_pair("i", dplsrc::Value(10)));

    dplutil::TestingUtil::testEval("continue.dpl", expectedVarVec, expectedOutputLines);
}