#include "TestingUtil.hpp"
#include "Value.hpp"

using namespace dplgrammar;

EVAL_TEST("break.dpl") {
    std::vector<std::pair<std::string, dplsrc::Value>> expectedVarVec;
    std::vector<std::string> expectedOutputLines;
    int i = 0;
    while (true) {
        i++;
        if (i == 10) break;
        expectedOutputLines.push_back("Loop until break!");
    }
    

    expectedVarVec.push_back(std::make_pair("i", dplsrc::Value(10)));

    dplutil::TestingUtil::testEval("break.dpl", expectedVarVec, expectedOutputLines);
}