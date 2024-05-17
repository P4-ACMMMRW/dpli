#include <TestingUtil.hpp>
#include <Value.hpp>

using namespace dplgrammar;

EVAL_TEST("table_operation.dpl") {
    std::vector<std::pair<std::string, dplsrc::Value>> expectedVarVec;
    std::vector<std::string> expectedOutputLines;
    

    expectedOutputLines.push_back("{ \'area\': [None, 10, None, None, None, None], \'height\': [4, 5, 6, 7, 8, 6], \'width\': [1, 2, 3, 3, 4, 3] }");
    expectedOutputLines.push_back("{ \'area\': [None], \'height\': [6], \'width\': [3] }");

    expectedOutputLines.push_back("{ \'area\': [10, None], \'height\': [5, 6], \'width\': [2, 3] }");
    expectedOutputLines.push_back("{ \'area\': [None], \'height\': [4], \'width\': [1] }");
    expectedOutputLines.push_back("{ \'area\': [None], \'height\': [8], \'width\': [4] }");
    
    expectedOutputLines.push_back("{ \'area\': [None, 10], \'height\': [4, 5], \'width\': [1, 2] }");
    expectedOutputLines.push_back("{ \'area\': [None, None], \'height\': [7, 6], \'width\': [3, 3] }");
    

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

    dplsrc::Value::COLUMN columnT2Area = std::make_shared<dplsrc::Value::COL_STRUCT>();
    dplsrc::Value::LIST listT2Area = std::make_shared<std::vector<std::shared_ptr<dplsrc::Value>>>();

    listT2Area->push_back(std::make_shared<dplsrc::Value>(nullptr));
    listT2Area->push_back(std::make_shared<dplsrc::Value>(nullptr));
    listT2Area->push_back(std::make_shared<dplsrc::Value>(nullptr)); 

    columnT2Area->parent = table2;
    columnT2Area->header = "area";
    columnT2Area->data = listT2Area;

    table2->insert({"area", columnT2Area});

    dplsrc::Value::COLUMN columnT2Height = std::make_shared<dplsrc::Value::COL_STRUCT>();
    dplsrc::Value::LIST listT2Height = std::make_shared<std::vector<std::shared_ptr<dplsrc::Value>>>();

    listT2Height->push_back(std::make_shared<dplsrc::Value>(7));
    listT2Height->push_back(std::make_shared<dplsrc::Value>(8)); 
    listT2Height->push_back(std::make_shared<dplsrc::Value>(6)); 

    columnT2Height->parent = table2;
    columnT2Height->header = "height";
    columnT2Height->data = listT2Height;

    table2->insert({"height", columnT2Height});

    dplsrc::Value::COLUMN columnT2Width = std::make_shared<dplsrc::Value::COL_STRUCT>();
    dplsrc::Value::LIST listT2Width = std::make_shared<std::vector<std::shared_ptr<dplsrc::Value>>>();

    listT2Width->push_back(std::make_shared<dplsrc::Value>(3));
    listT2Width->push_back(std::make_shared<dplsrc::Value>(4));
    listT2Width->push_back(std::make_shared<dplsrc::Value>(3)); 
    
    columnT2Width->parent = table2;
    columnT2Width->header = "width";
    columnT2Width->data = listT2Width;

    table2->insert({"width", columnT2Width});

    //                      
    //               TABLE 3
    //
    dplsrc::Value::TABLE table3 = std::make_shared<std::map<std::string, dplsrc::Value::COLUMN>>();

    dplsrc::Value::COLUMN columnT3Area = std::make_shared<dplsrc::Value::COL_STRUCT>();
    dplsrc::Value::LIST listT3Area = std::make_shared<std::vector<std::shared_ptr<dplsrc::Value>>>();

    listT3Area->push_back(std::make_shared<dplsrc::Value>(nullptr));
    listT3Area->push_back(std::make_shared<dplsrc::Value>(10)); 
    listT3Area->push_back(std::make_shared<dplsrc::Value>(nullptr)); 
    listT3Area->push_back(std::make_shared<dplsrc::Value>(nullptr));
    listT3Area->push_back(std::make_shared<dplsrc::Value>(nullptr));
    listT3Area->push_back(std::make_shared<dplsrc::Value>(nullptr)); 

    columnT3Area->parent = table3;
    columnT3Area->header = "area";
    columnT3Area->data = listT3Area;

    table3->insert({"area", columnT3Area});

    dplsrc::Value::COLUMN columnT3Height = std::make_shared<dplsrc::Value::COL_STRUCT>();
    dplsrc::Value::LIST listT3Height = std::make_shared<std::vector<std::shared_ptr<dplsrc::Value>>>();

    listT3Height->push_back(std::make_shared<dplsrc::Value>(4));
    listT3Height->push_back(std::make_shared<dplsrc::Value>(5)); 
    listT3Height->push_back(std::make_shared<dplsrc::Value>(6)); 
    listT3Height->push_back(std::make_shared<dplsrc::Value>(7));
    listT3Height->push_back(std::make_shared<dplsrc::Value>(8)); 
    listT3Height->push_back(std::make_shared<dplsrc::Value>(6)); 

    columnT3Height->parent = table3;
    columnT3Height->header = "height";
    columnT3Height->data = listT3Height;

    table3->insert({"height", columnT3Height});

    dplsrc::Value::COLUMN columnT3Width = std::make_shared<dplsrc::Value::COL_STRUCT>();
    dplsrc::Value::LIST listT3Width = std::make_shared<std::vector<std::shared_ptr<dplsrc::Value>>>();

    listT3Width->push_back(std::make_shared<dplsrc::Value>(1));
    listT3Width->push_back(std::make_shared<dplsrc::Value>(2)); 
    listT3Width->push_back(std::make_shared<dplsrc::Value>(3)); 
    listT3Width->push_back(std::make_shared<dplsrc::Value>(3));
    listT3Width->push_back(std::make_shared<dplsrc::Value>(4));
    listT3Width->push_back(std::make_shared<dplsrc::Value>(3)); 
    
    columnT3Width->parent = table3;
    columnT3Width->header = "width";
    columnT3Width->data = listT3Width;

    table3->insert({"width", columnT3Width});

    //                      
    //               TABLE 4
    //
    dplsrc::Value::TABLE table4 = std::make_shared<std::map<std::string, dplsrc::Value::COLUMN>>();

    dplsrc::Value::COLUMN columnT4Area = std::make_shared<dplsrc::Value::COL_STRUCT>();
    dplsrc::Value::LIST listT4Area = std::make_shared<std::vector<std::shared_ptr<dplsrc::Value>>>();

    listT4Area->push_back(std::make_shared<dplsrc::Value>(nullptr)); 

    columnT4Area->parent = table4;
    columnT4Area->header = "area";
    columnT4Area->data = listT4Area;

    table4->insert({"area", columnT4Area});

    dplsrc::Value::COLUMN columnT4Height = std::make_shared<dplsrc::Value::COL_STRUCT>();
    dplsrc::Value::LIST listT4Height = std::make_shared<std::vector<std::shared_ptr<dplsrc::Value>>>();

    listT4Height->push_back(std::make_shared<dplsrc::Value>(6)); 

    columnT4Height->parent = table4;
    columnT4Height->header = "height";
    columnT4Height->data = listT4Height;

    table4->insert({"height", columnT4Height});

    dplsrc::Value::COLUMN columnT4Width = std::make_shared<dplsrc::Value::COL_STRUCT>();
    dplsrc::Value::LIST listT4Width = std::make_shared<std::vector<std::shared_ptr<dplsrc::Value>>>();

    listT4Width->push_back(std::make_shared<dplsrc::Value>(3)); 

    columnT4Width->parent = table4;
    columnT4Width->header = "width";
    columnT4Width->data = listT4Width;

    table4->insert({"width", columnT4Width});

    expectedVarVec.push_back({"t1", dplsrc::Value(table1)});
    expectedVarVec.push_back({"t2", dplsrc::Value(table2)});
    expectedVarVec.push_back({"t3", dplsrc::Value(table3)});
    expectedVarVec.push_back({"t4", dplsrc::Value(table4)});


    dplutil::TestingUtil::testEval("table_operation.dpl", expectedVarVec, expectedOutputLines);
}