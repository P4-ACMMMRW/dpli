#include <TestingUtil.hpp>
#include <Value.hpp>

using namespace dplgrammar;

EVAL_TEST("math.dpl") {
    std::vector<std::pair<std::string, dplsrc::Value>> expectedVarVec;

    expectedVarVec.push_back(std::make_pair("i", dplsrc::Value(0)));
    expectedVarVec.push_back(std::make_pair("z", dplsrc::Value(5.0)));
    expectedVarVec.push_back(std::make_pair("y", dplsrc::Value(6)));
    expectedVarVec.push_back(std::make_pair("x", dplsrc::Value(8)));

    dplutil::TestingUtil::testEval("math.dpl", expectedVarVec);
}