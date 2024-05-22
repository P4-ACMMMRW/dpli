#include "TestingUtil.hpp"
#include "Value.hpp"

using namespace dplgrammar;

EVAL_TEST("replace_with.dpl") {
    std::vector<std::pair<std::string, dplsrc::Value>> expectedVarVec;
    std::vector<std::string> expectedOutputLines;

    expectedOutputLines.push_back("{ \'width\': [1, 3], \'height\': [4, 6], \'area\': [4, 18] }");

    //                      
    //               TABLE 1
    //
    dplsrc::Value::TABLE table1 = std::make_shared<std::pair<std::vector<dplsrc::Value::STR>, std::unordered_map<dplsrc::Value::STR, dplsrc::Value::COLUMN>>>();

    dplsrc::Value::COLUMN columnT1Area = std::make_shared<dplsrc::Value::COL_STRUCT>();
    dplsrc::Value::LIST listT1Area = std::make_shared<std::vector<std::shared_ptr<dplsrc::Value>>>();

    listT1Area->push_back(std::make_shared<dplsrc::Value>(4));
    listT1Area->push_back(std::make_shared<dplsrc::Value>(10)); 
    listT1Area->push_back(std::make_shared<dplsrc::Value>(18)); 

    columnT1Area->parent = table1;
    columnT1Area->header = "area";
    columnT1Area->data = listT1Area;

    table1->second.insert({"area", columnT1Area});

    dplsrc::Value::COLUMN columnT1Height = std::make_shared<dplsrc::Value::COL_STRUCT>();
    dplsrc::Value::LIST listT1Height = std::make_shared<std::vector<std::shared_ptr<dplsrc::Value>>>();

    listT1Height->push_back(std::make_shared<dplsrc::Value>(4));
    listT1Height->push_back(std::make_shared<dplsrc::Value>(5)); 
    listT1Height->push_back(std::make_shared<dplsrc::Value>(6)); 

    columnT1Height->parent = table1;
    columnT1Height->header = "height";
    columnT1Height->data = listT1Height;

    table1->second.insert({"height", columnT1Height});

    dplsrc::Value::COLUMN columnT1Width = std::make_shared<dplsrc::Value::COL_STRUCT>();
    dplsrc::Value::LIST listT1Width = std::make_shared<std::vector<std::shared_ptr<dplsrc::Value>>>();

    listT1Width->push_back(std::make_shared<dplsrc::Value>(1));
    listT1Width->push_back(std::make_shared<dplsrc::Value>(2)); 
    listT1Width->push_back(std::make_shared<dplsrc::Value>(3)); 
    
    columnT1Width->parent = table1;
    columnT1Width->header = "width";
    columnT1Width->data = listT1Width;

    table1->second.insert({"width", columnT1Width});

    //                      
    //               TABLE 2
    //
    dplsrc::Value::TABLE table2 = std::make_shared<std::pair<std::vector<dplsrc::Value::STR>, std::unordered_map<dplsrc::Value::STR, dplsrc::Value::COLUMN>>>();

    dplsrc::Value::COLUMN columnT2Area = std::make_shared<dplsrc::Value::COL_STRUCT>();
    dplsrc::Value::LIST listT2Area = std::make_shared<std::vector<std::shared_ptr<dplsrc::Value>>>();

    listT2Area->push_back(std::make_shared<dplsrc::Value>(4));
    listT2Area->push_back(std::make_shared<dplsrc::Value>(18)); 

    columnT2Area->parent = table2;
    columnT2Area->header = "area";
    columnT2Area->data = listT2Area;

    table2->second.insert({"area", columnT2Area});

    dplsrc::Value::COLUMN columnT2Height = std::make_shared<dplsrc::Value::COL_STRUCT>();
    dplsrc::Value::LIST listT2Height = std::make_shared<std::vector<std::shared_ptr<dplsrc::Value>>>();

    listT2Height->push_back(std::make_shared<dplsrc::Value>(4));
    listT2Height->push_back(std::make_shared<dplsrc::Value>(6)); 

    columnT2Height->parent = table2;
    columnT2Height->header = "height";
    columnT2Height->data = listT2Height;

    table2->second.insert({"height", columnT2Height});

    dplsrc::Value::COLUMN columnT2Width = std::make_shared<dplsrc::Value::COL_STRUCT>();
    dplsrc::Value::LIST listT2Width = std::make_shared<std::vector<std::shared_ptr<dplsrc::Value>>>();

    listT2Width->push_back(std::make_shared<dplsrc::Value>(1));
    listT2Width->push_back(std::make_shared<dplsrc::Value>(3)); 
    
    columnT2Width->parent = table2;
    columnT2Width->header = "width";
    columnT2Width->data = listT2Width;

    table2->second.insert({"width", columnT2Width});

    //                      
    //               TABLE 3
    //
    dplsrc::Value::COLUMN columnT3Area = std::make_shared<dplsrc::Value::COL_STRUCT>();
    dplsrc::Value::LIST listT3Area = std::make_shared<std::vector<std::shared_ptr<dplsrc::Value>>>();

    columnT3Area->parent = table1;
    columnT3Area->header = "area";
    columnT3Area->data = listT3Area;

    expectedVarVec.push_back({"t1", dplsrc::Value(table1)});
    expectedVarVec.push_back({"t2", dplsrc::Value(table2)});
    expectedVarVec.push_back({"t3", dplsrc::Value(columnT3Area)});

    dplutil::TestingUtil::testEval("replace_with.dpl", expectedVarVec, expectedOutputLines);
}