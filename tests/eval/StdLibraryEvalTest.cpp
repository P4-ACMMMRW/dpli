#include "TestingUtil.hpp"
#include "Value.hpp"

using namespace dplgrammar;

EVAL_TEST("std_library.dpl") {
    std::vector<std::pair<std::string, dplsrc::Value>> expectedVarVec;
    std::vector<std::string> expectedOutputLines;

    expectedOutputLines.push_back("int");
    expectedOutputLines.push_back("float");
    expectedOutputLines.push_back("bool");
    expectedOutputLines.push_back("str");
    expectedOutputLines.push_back("list");
    expectedOutputLines.push_back("column");
    expectedOutputLines.push_back("table");
    
    expectedOutputLines.push_back("2");
    expectedOutputLines.push_back("2.2");
    expectedOutputLines.push_back("True");
    expectedOutputLines.push_back("str");
    expectedOutputLines.push_back("[1, 2]");
    expectedOutputLines.push_back("'test1': [1, 2, 3]");
    expectedOutputLines.push_back("{ 'test1': [1, 2, 3], 'test2': [4.0, 5.0, 6.0], 'test3': ['12', '10', '11'], 'test4': [True, False, False], 'test5': [None, None, None] }");
    
    expectedOutputLines.push_back("2");
    expectedOutputLines.push_back("2");
    expectedOutputLines.push_back("1");
    expectedOutputLines.push_back("2");

    expectedOutputLines.push_back("2.0");
    expectedOutputLines.push_back("2.2");
    expectedOutputLines.push_back("1.0");
    expectedOutputLines.push_back("2.0");

    expectedOutputLines.push_back("3");
    expectedOutputLines.push_back("2");
    expectedOutputLines.push_back("3");
    expectedOutputLines.push_back("5");

    expectedOutputLines.push_back("3");
    expectedOutputLines.push_back("2");
    expectedOutputLines.push_back("2");
    expectedOutputLines.push_back("2");
    expectedOutputLines.push_back("2");
    expectedOutputLines.push_back("2");

    expectedOutputLines.push_back("[1, 2]");
    
    expectedOutputLines.push_back("{ 'test1': [1, 2, 3], 'test2': [4.0, 5.0, 6.0], 'test3': ['12', '10', '11'], 'test4': [True, False, False], 'test5': [None, None, None] }");
    expectedOutputLines.push_back("{ 'test1': [1, 2, 3], 'test2': [4.0, 5.0, 6.0], 'test3': ['12', '10', '11'], 'test4': [True, False, False], 'test5': [None, None, None] }");
    
    expectedOutputLines.push_back("{ 'test1': ['1', '2', '3'], 'test2': ['4.0', '5.0', '6.0'], 'test3': ['12', '10', '11'], 'test4': ['True', 'False', 'False'], 'test5': ['None', 'None', 'None'] }");
    expectedOutputLines.push_back("{ 'test1': ['1', '2', '3'], 'test2': ['4.0', '5.0', '6.0'], 'test3': ['12', '10', '11'], 'test4': ['True', 'False', 'False'], 'test5': ['None', 'None', 'None'] }");
    

    //                      
    //               TABLE 1
    //
    dplsrc::Value::TABLE table1 = std::make_shared<std::pair<std::vector<dplsrc::Value::STR>, std::unordered_map<dplsrc::Value::STR, dplsrc::Value::COLUMN>>>();

    dplsrc::Value::COLUMN columnT1Test1= std::make_shared<dplsrc::Value::COL_STRUCT>();
    dplsrc::Value::LIST listT1Test1 = std::make_shared<std::vector<std::shared_ptr<dplsrc::Value>>>();

    listT1Test1->push_back(std::make_shared<dplsrc::Value>(1));
    listT1Test1->push_back(std::make_shared<dplsrc::Value>(2)); 
    listT1Test1->push_back(std::make_shared<dplsrc::Value>(3)); 

    columnT1Test1->parent = table1;
    columnT1Test1->header = "test1";
    columnT1Test1->data = listT1Test1;

    table1->second.insert({"test1", columnT1Test1});

    dplsrc::Value::COLUMN columnT1Test2 = std::make_shared<dplsrc::Value::COL_STRUCT>();
    dplsrc::Value::LIST listT1Test2 = std::make_shared<std::vector<std::shared_ptr<dplsrc::Value>>>();

    listT1Test2->push_back(std::make_shared<dplsrc::Value>(4.0));
    listT1Test2->push_back(std::make_shared<dplsrc::Value>(5.0)); 
    listT1Test2->push_back(std::make_shared<dplsrc::Value>(6.0)); 

    columnT1Test2->parent = table1;
    columnT1Test2->header = "test2";
    columnT1Test2->data = listT1Test2;

    table1->second.insert({"test2", columnT1Test2});

    dplsrc::Value::COLUMN columnT1Test3 = std::make_shared<dplsrc::Value::COL_STRUCT>();
    dplsrc::Value::LIST listT1Test3 = std::make_shared<std::vector<std::shared_ptr<dplsrc::Value>>>();

    listT1Test3->push_back(std::make_shared<dplsrc::Value>("12"));
    listT1Test3->push_back(std::make_shared<dplsrc::Value>("10")); 
    listT1Test3->push_back(std::make_shared<dplsrc::Value>("11")); 
    
    columnT1Test3->parent = table1;
    columnT1Test3->header = "test3";
    columnT1Test3->data = listT1Test3;

    table1->second.insert({"test3", columnT1Test3});

    dplsrc::Value::COLUMN columnT1Test4 = std::make_shared<dplsrc::Value::COL_STRUCT>();
    dplsrc::Value::LIST listT1Test4 = std::make_shared<std::vector<std::shared_ptr<dplsrc::Value>>>();

    listT1Test4->push_back(std::make_shared<dplsrc::Value>(true));
    listT1Test4->push_back(std::make_shared<dplsrc::Value>(false)); 
    listT1Test4->push_back(std::make_shared<dplsrc::Value>(false)); 
    
    columnT1Test4->parent = table1;
    columnT1Test4->header = "test4";
    columnT1Test4->data = listT1Test4;

    table1->second.insert({"test4", columnT1Test4});

    dplsrc::Value::COLUMN columnT1Test5 = std::make_shared<dplsrc::Value::COL_STRUCT>();
    dplsrc::Value::LIST listT1Test5 = std::make_shared<std::vector<std::shared_ptr<dplsrc::Value>>>();

    listT1Test5->push_back(std::make_shared<dplsrc::Value>(nullptr));
    listT1Test5->push_back(std::make_shared<dplsrc::Value>(nullptr)); 
    listT1Test5->push_back(std::make_shared<dplsrc::Value>(nullptr)); 
    
    columnT1Test5->parent = table1;
    columnT1Test5->header = "test5";
    columnT1Test5->data = listT1Test5;

    table1->second.insert({"test5", columnT1Test5});

     
    //                      
    //               LIST 1
    //

    dplsrc::Value::LIST list1 = std::make_shared<std::vector<std::shared_ptr<dplsrc::Value>>>();
    list1->push_back(std::make_shared<dplsrc::Value>(1));
    list1->push_back(std::make_shared<dplsrc::Value>(2)); 

    expectedVarVec.push_back({"t1", table1});
    expectedVarVec.push_back({"l1", list1});

    dplutil::TestingUtil::testEval("std_library.dpl", expectedVarVec, expectedOutputLines);
}