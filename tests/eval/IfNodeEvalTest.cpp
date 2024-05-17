#include "TestingUtil.hpp"
#include "Value.hpp"

using namespace dplgrammar;

EVAL_TEST("if_node.dpl") {
    std::vector<std::pair<std::string, dplsrc::Value>> expectedVarVec;
    std::vector<std::string> expectedOutputLines;

    expectedOutputLines.push_back("int_works 1");
    expectedOutputLines.push_back("int_works 2");

    expectedOutputLines.push_back("float_works 1");
    expectedOutputLines.push_back("float_works 2");

    expectedOutputLines.push_back("bool_works 1");
    expectedOutputLines.push_back("bool_works 2");

    expectedOutputLines.push_back("str_works 1");
    expectedOutputLines.push_back("str_works 2");

    expectedOutputLines.push_back("list_works 1");
    expectedOutputLines.push_back("list_works 2");
   
    expectedOutputLines.push_back("column_works 1");
    expectedOutputLines.push_back("column_works 2");

    expectedOutputLines.push_back("table_works 1");
    expectedOutputLines.push_back("table_works 2");

    //                      
    //               TABLE 1
    //
    dplsrc::Value::TABLE table1 = std::make_shared<std::map<std::string, dplsrc::Value::COLUMN>>();

    dplsrc::Value::COLUMN columnT1Area = std::make_shared<dplsrc::Value::COL_STRUCT>();
    dplsrc::Value::LIST listT1Area = std::make_shared<std::vector<std::shared_ptr<dplsrc::Value>>>();

    listT1Area->push_back(std::make_shared<dplsrc::Value>(nullptr));
    listT1Area->push_back(std::make_shared<dplsrc::Value>(10)); 
    listT1Area->push_back(std::make_shared<dplsrc::Value>(nullptr)); 

    columnT1Area->parent = table1;
    columnT1Area->header = "area";
    columnT1Area->data = listT1Area;

    table1->insert({"area", columnT1Area});

    dplsrc::Value::COLUMN columnT1Height = std::make_shared<dplsrc::Value::COL_STRUCT>();
    dplsrc::Value::LIST listT1Height = std::make_shared<std::vector<std::shared_ptr<dplsrc::Value>>>();

    listT1Height->push_back(std::make_shared<dplsrc::Value>(4));
    listT1Height->push_back(std::make_shared<dplsrc::Value>(5)); 
    listT1Height->push_back(std::make_shared<dplsrc::Value>(6)); 

    columnT1Height->parent = table1;
    columnT1Height->header = "height";
    columnT1Height->data = listT1Height;

    table1->insert({"height", columnT1Height});

    dplsrc::Value::COLUMN columnT1Width = std::make_shared<dplsrc::Value::COL_STRUCT>();
    dplsrc::Value::LIST listT1Width = std::make_shared<std::vector<std::shared_ptr<dplsrc::Value>>>();

    listT1Width->push_back(std::make_shared<dplsrc::Value>(1));
    listT1Width->push_back(std::make_shared<dplsrc::Value>(2)); 
    listT1Width->push_back(std::make_shared<dplsrc::Value>(3)); 
    
    columnT1Width->parent = table1;
    columnT1Width->header = "width";
    columnT1Width->data = listT1Width;

    table1->insert({"width", columnT1Width});


    //                      
    //               TABLE 2
    //

    dplsrc::Value::TABLE table2 = std::make_shared<std::map<std::string, dplsrc::Value::COLUMN>>();


    //                      
    //               TABLE 3
    //
    dplsrc::Value::TABLE table3 = std::make_shared<std::map<std::string, dplsrc::Value::COLUMN>>();

    dplsrc::Value::COLUMN columnT3Area = std::make_shared<dplsrc::Value::COL_STRUCT>();
    dplsrc::Value::LIST listT3Area = std::make_shared<std::vector<std::shared_ptr<dplsrc::Value>>>();

    columnT3Area->parent = table3;
    columnT3Area->header = "test";
    columnT3Area->data = listT3Area;

    table3->insert({"test", columnT3Area});

    expectedVarVec.push_back({"t1", table1});
    expectedVarVec.push_back({"t2", table2});
    expectedVarVec.push_back({"t3", table3});

    dplutil::TestingUtil::testEval("if_node.dpl", expectedVarVec, expectedOutputLines);
}