#include <TestingUtil.hpp>
#include <Value.hpp>

using namespace dplgrammar;

EVAL_TEST("gcd.dpl") {
    std::vector<std::pair<std::string, dplsrc::Value>> expectedVarVec;


    dplutil::TestingUtil::testEval("gcd.dpl", expectedVarVec);
}