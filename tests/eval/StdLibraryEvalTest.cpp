#include <TestingUtil.hpp>
#include <Value.hpp>

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
    expectedOutputLines.push_back("'width': [1, 2, 3]");
    expectedOutputLines.push_back("{ 'area': [None, 10, None], 'height': [4, 5, 6], 'width': [1, 2, 3] }");
    
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
    expectedOutputLines.push_back("3");

    expectedOutputLines.push_back("3");
    expectedOutputLines.push_back("2");
    expectedOutputLines.push_back("2");
    expectedOutputLines.push_back("2");
    expectedOutputLines.push_back("2");
    expectedOutputLines.push_back("2");
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
    //               LIST 1
    //

    dplsrc::Value::LIST list1 = std::make_shared<std::vector<std::shared_ptr<dplsrc::Value>>>();
    list1->push_back(std::make_shared<dplsrc::Value>(1));
    list1->push_back(std::make_shared<dplsrc::Value>(2)); 

    expectedVarVec.push_back({"t1", table1});
    expectedVarVec.push_back({"l1", list1});

    dplutil::TestingUtil::testEval("std_library.dpl", expectedVarVec, expectedOutputLines);
}