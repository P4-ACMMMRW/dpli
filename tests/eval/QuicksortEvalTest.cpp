#include <TestingUtil.hpp>
#include <Value.hpp>

using namespace dplgrammar;

EVAL_TEST("quicksort.dpl") {
    std::vector<std::pair<std::string, dplsrc::Value>> expectedVarVec;

    dplsrc::Value::LIST list = std::make_shared<std::vector<std::shared_ptr<dplsrc::Value>>>();

    list->push_back(std::make_shared<dplsrc::Value>(1));
    list->push_back(std::make_shared<dplsrc::Value>(1)); 
    list->push_back(std::make_shared<dplsrc::Value>(2));
    list->push_back(std::make_shared<dplsrc::Value>(3));
    list->push_back(std::make_shared<dplsrc::Value>(3));
    list->push_back(std::make_shared<dplsrc::Value>(4));
    list->push_back(std::make_shared<dplsrc::Value>(5));
    list->push_back(std::make_shared<dplsrc::Value>(5));
    list->push_back(std::make_shared<dplsrc::Value>(5));
    list->push_back(std::make_shared<dplsrc::Value>(6));
    list->push_back(std::make_shared<dplsrc::Value>(9));

    expectedVarVec.push_back(std::make_pair("A", list));

    dplutil::TestingUtil::testEval("quicksort.dpl", expectedVarVec);
}