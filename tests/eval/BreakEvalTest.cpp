#include <TestingUtil.hpp>
#include <Value.hpp>

using namespace dplgrammar;

EVAL_TEST("break.dpl") {
    std::vector<std::pair<std::string, dplsrc::Value>> expectedVarVec;

    expectedVarVec.push_back(std::make_pair("i", dplsrc::Value(10)));

    dplutil::TestingUtil::testEval("break.dpl", expectedVarVec);
}