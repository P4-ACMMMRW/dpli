#include "TestingUtil.hpp"
#include "Value.hpp"

using namespace dplutil;
using namespace dplsrc;

VALUE_TEST("compare values") {
    // Numeric
    Value valFloat = 1.0;
    Value valInt = 1;
    Value valBool = true;

    REQUIRE(valFloat == valInt);
    REQUIRE(valFloat == valBool);
    REQUIRE(valInt == valFloat);
    REQUIRE(valInt == valBool);
    REQUIRE(valBool == valInt);
    REQUIRE(valBool == valFloat);

    REQUIRE(!(valFloat != valInt));
    REQUIRE(!(valFloat != valBool));
    REQUIRE(!(valInt != valFloat));
    REQUIRE(!(valInt != valBool));
    REQUIRE(!(valBool != valInt));
    REQUIRE(!(valBool != valFloat));

    REQUIRE(valFloat <= valInt);
    REQUIRE(valFloat <= valBool);
    REQUIRE(valInt <= valFloat);
    REQUIRE(valInt <= valBool);
    REQUIRE(valBool <= valInt);
    REQUIRE(valBool <= valFloat);

    REQUIRE(valFloat >= valInt);
    REQUIRE(valFloat >= valBool);
    REQUIRE(valInt >= valFloat);
    REQUIRE(valInt >= valBool);
    REQUIRE(valBool >= valInt);
    REQUIRE(valBool >= valFloat);

    REQUIRE(!(valFloat < valInt));
    REQUIRE(!(valFloat < valBool));
    REQUIRE(!(valInt < valFloat));
    REQUIRE(!(valInt < valBool));
    REQUIRE(!(valBool < valInt));
    REQUIRE(!(valBool < valFloat));

    REQUIRE(!(valFloat > valInt));
    REQUIRE(!(valFloat > valBool));
    REQUIRE(!(valInt > valFloat));
    REQUIRE(!(valInt > valBool));
    REQUIRE(!(valBool > valInt));
    REQUIRE(!(valBool > valFloat));

    // Strings
    Value str1 = "abc";
    Value str2 = "abc";
    Value str3 = "cba";

    REQUIRE(str1 == str2);
    REQUIRE(str1 != str3);
    REQUIRE(str1 <= str2);
    REQUIRE(str1 >= str2);
    REQUIRE(!(str1 < str2));
    REQUIRE(!(str1 > str2));
    REQUIRE(!(valInt < str1));

    // NoneType
    Value n1 = nullptr;
    Value n2 = nullptr;

    REQUIRE(n1 == n2);
    REQUIRE(!(n1 != n2));
    REQUIRE(n1 <= n2);
    REQUIRE(n1 >= n2);
    REQUIRE(!(n1 < n2));
    REQUIRE(!(n1 > n2));

    // List
    Value l1 = std::make_shared<std::vector<std::shared_ptr<Value>>>();
    l1.get<Value::LIST>()->emplace_back(std::make_shared<Value>("a"));
    l1.get<Value::LIST>()->emplace_back(std::make_shared<Value>(1));

    Value l2 = std::make_shared<std::vector<std::shared_ptr<Value>>>();
    l2.get<Value::LIST>()->emplace_back(std::make_shared<Value>(1));
    l2.get<Value::LIST>()->emplace_back(std::make_shared<Value>("a"));

    Value l3 = std::make_shared<std::vector<std::shared_ptr<Value>>>();
    l3.get<Value::LIST>()->emplace_back(std::make_shared<Value>("a"));
    l3.get<Value::LIST>()->emplace_back(std::make_shared<Value>(1));

    REQUIRE(!(l1 == l2));
    REQUIRE(l1 == l3);
    REQUIRE(!(l2 == l1));
    REQUIRE(!(l2 == l3));
    REQUIRE(l3 == l1);
    REQUIRE(!(l3 == l2));

    REQUIRE(l1 != l2);
    REQUIRE(!(l1 != l3));
    REQUIRE(l2 != l1);
    REQUIRE(l2 != l3);
    REQUIRE(!(l3 != l1));
    REQUIRE(l3 != l2);

    Value l4 = std::make_shared<std::vector<std::shared_ptr<Value>>>();
    l4.get<Value::LIST>()->emplace_back(std::make_shared<Value>(1));
    l4.get<Value::LIST>()->emplace_back(std::make_shared<Value>(10));

    Value l5 = std::make_shared<std::vector<std::shared_ptr<Value>>>();
    l5.get<Value::LIST>()->emplace_back(std::make_shared<Value>(10));
    l5.get<Value::LIST>()->emplace_back(std::make_shared<Value>(1));

    Value l6 = std::make_shared<std::vector<std::shared_ptr<Value>>>();
    l6.get<Value::LIST>()->emplace_back(std::make_shared<Value>(1));

    REQUIRE(l4 < l5);
    REQUIRE(!(l4 < l6));
    REQUIRE(!(l5 < l4));
    REQUIRE(!(l5 < l6));
    REQUIRE(l6 < l4);
    REQUIRE(l6 < l5);

    REQUIRE(!(l4 > l5));
    REQUIRE(l4 > l6);
    REQUIRE(l5 > l4);
    REQUIRE(l5 > l6);
    REQUIRE(!(l6 > l4));
    REQUIRE(!(l6 > l5));

    // Columns
    Value col1 = std::make_shared<Value::COL_STRUCT>();
    col1.get<Value::COLUMN>()->data = l1.get<Value::LIST>();

    Value col2 = std::make_shared<Value::COL_STRUCT>();
    col2.get<Value::COLUMN>()->data = l2.get<Value::LIST>();

    Value col3 = std::make_shared<Value::COL_STRUCT>();
    col3.get<Value::COLUMN>()->data = l3.get<Value::LIST>();

    REQUIRE(!(col1 == col2));
    REQUIRE(col1 == col3);
    REQUIRE(!(col2 == col1));
    REQUIRE(!(col2 == col3));
    REQUIRE(col3 == col1);
    REQUIRE(!(col3 == col2));

    REQUIRE(col1 != col2);
    REQUIRE(!(col1 != col3));
    REQUIRE(col2 != col1);
    REQUIRE(col2 != col3);
    REQUIRE(!(col3 != col1));
    REQUIRE(col3 != col2);

    Value col4 = std::make_shared<Value::COL_STRUCT>();
    std::cout << l4.toString() << '\n';
    col4.get<Value::COLUMN>()->data = l4.get<Value::LIST>();

    Value col5 = std::make_shared<Value::COL_STRUCT>();
    col5.get<Value::COLUMN>()->data = l5.get<Value::LIST>();

    Value col6 = std::make_shared<Value::COL_STRUCT>();
    col6.get<Value::COLUMN>()->data = l6.get<Value::LIST>();

    REQUIRE(col4 < col5);
    REQUIRE(!(col4 < col6));
    REQUIRE(!(col5 < col4));
    REQUIRE(!(col5 < col6));
    REQUIRE(col6 < col4);
    REQUIRE(col6 < col5);

    REQUIRE(!(col4 > col5));
    REQUIRE(col4 > col6);
    REQUIRE(col5 > col4);
    REQUIRE(col5 > col6);
    REQUIRE(!(col6 > col4));
    REQUIRE(!(col6 > col5));

    // Tables
    Value tab1 = std::make_shared<std::map<Value::STR, Value::COLUMN>>();
    tab1.get<Value::TABLE>()->insert({"col", col1.get<Value::COLUMN>()});

    Value tab2 = std::make_shared<std::map<Value::STR, Value::COLUMN>>();
    tab2.get<Value::TABLE>()->insert({"col", col2.get<Value::COLUMN>()});

    Value tab3 = std::make_shared<std::map<Value::STR, Value::COLUMN>>();
    tab3.get<Value::TABLE>()->insert({"col", col3.get<Value::COLUMN>()});

    REQUIRE(!(tab1 == tab2));
    REQUIRE(tab1 == tab3);
    REQUIRE(!(tab2 == tab1));
    REQUIRE(!(tab2 == tab3));
    REQUIRE(tab3 == tab1);
    REQUIRE(!(tab3 == tab2));

    REQUIRE(tab1 != tab2);
    REQUIRE(!(tab1 != tab3));
    REQUIRE(tab2 != tab1);
    REQUIRE(tab2 != tab3);
    REQUIRE(!(tab3 != tab1));
    REQUIRE(tab3 != tab2);

    Value tab4 = std::make_shared<std::map<Value::STR, Value::COLUMN>>();
    REQUIRE(tab1 != tab4);

    Value tab5 = std::make_shared<std::map<Value::STR, Value::COLUMN>>();
    tab5.get<Value::TABLE>()->insert({"diff_key", col1.get<Value::COLUMN>()});

    REQUIRE(tab1 != tab5);
    REQUIRE(tab4 < tab1);
    REQUIRE(tab1 < tab2);
}

VALUE_TEST("Arthrimetic values") {
     // Numeric
    Value valFloat = 1.0;
    Value valInt = 1;
    Value valBool = true;


    REQUIRE(valFloat + valInt == 2.0);
    REQUIRE(valFloat + valBool == 2.0);
    REQUIRE(valInt + valFloat == 2.0);
    REQUIRE(valInt + valBool == 2);
    REQUIRE(valBool + valInt == 2);
    REQUIRE(valBool + valFloat == 2.0);

    REQUIRE(valFloat - valInt == 0.0);
    REQUIRE(valFloat - valBool == 0.0);
    REQUIRE(valInt - valFloat == 0.0);
    REQUIRE(valInt - valBool == 0);
    REQUIRE(valBool - valInt == 0);
    REQUIRE(valBool - valFloat == 0.0);

    REQUIRE(valFloat * valInt == 1.0);
    REQUIRE(valFloat * valBool == 1.0);
    REQUIRE(valInt * valFloat == 1.0);
    REQUIRE(valInt * valBool== 1);
    REQUIRE(valBool * valInt == 1);
    REQUIRE(valBool * valFloat == 1.0);

    REQUIRE(valFloat / valInt == 1.0);
    REQUIRE(valFloat / valBool == 1.0);
    REQUIRE(valInt / valFloat == 1.0);
    REQUIRE(valInt / valBool == 1);
    REQUIRE(valBool / valInt == 1);
    REQUIRE(valBool / valFloat == 1.0);

    REQUIRE(valFloat % valInt == 0.0);
    REQUIRE(valFloat % valBool == 0.0);
    REQUIRE(valInt % valFloat == 0.0);
    REQUIRE(valInt % valBool == 0);
    REQUIRE(valBool % valInt == 0);
    REQUIRE(valBool % valFloat == 0.0);

    REQUIRE(valFloat.pow(valInt) == 1.0);
    REQUIRE(valFloat.pow(valBool) == 1.0);
    REQUIRE(valInt.pow(valFloat) == 1.0);
    REQUIRE(valInt.pow(valBool) == 1);
    REQUIRE(valBool.pow(valInt) == 1);
    REQUIRE(valBool.pow(valFloat) == 1.0);

    REQUIRE(-valInt == -1.0);
    REQUIRE(-valBool == -1.0);
    REQUIRE(-valFloat == -1.0);

    // Strings
    Value str1 = "abc";

    REQUIRE(str1 + str1 == "abcabc");
    REQUIRE(str1 * 2 == "abcabc");

    // NoneType
 
    // List
    Value l1 = std::make_shared<std::vector<std::shared_ptr<Value>>>();
    l1.get<Value::LIST>()->emplace_back(std::make_shared<Value>("a"));
    l1.get<Value::LIST>()->emplace_back(std::make_shared<Value>(1));

    Value l2 = std::make_shared<std::vector<std::shared_ptr<Value>>>();
    l2.get<Value::LIST>()->emplace_back(std::make_shared<Value>(1));
    l2.get<Value::LIST>()->emplace_back(std::make_shared<Value>("a"));

    Value l3 = std::make_shared<std::vector<std::shared_ptr<Value>>>();
    l3.get<Value::LIST>()->emplace_back(std::make_shared<Value>("a"));
    l3.get<Value::LIST>()->emplace_back(std::make_shared<Value>(1));

    Value lRes1 = std::make_shared<std::vector<std::shared_ptr<Value>>>();
    lRes1.get<Value::LIST>()->emplace_back(std::make_shared<Value>("a"));
    lRes1.get<Value::LIST>()->emplace_back(std::make_shared<Value>(1));
    lRes1.get<Value::LIST>()->emplace_back(std::make_shared<Value>("a"));
    lRes1.get<Value::LIST>()->emplace_back(std::make_shared<Value>(1));

    Value lRes2 = std::make_shared<std::vector<std::shared_ptr<Value>>>();
    lRes2.get<Value::LIST>()->emplace_back(std::make_shared<Value>("a"));
    lRes2.get<Value::LIST>()->emplace_back(std::make_shared<Value>(1));
    lRes2.get<Value::LIST>()->emplace_back(std::make_shared<Value>(1));
    lRes2.get<Value::LIST>()->emplace_back(std::make_shared<Value>("a"));
   
    REQUIRE(l1 + l2 != lRes1);
    REQUIRE(l1 + l2 == lRes2);
    REQUIRE(l1 + l3 != lRes2);
    REQUIRE(l1 + l3 == lRes1);


    REQUIRE(l1 * 2 == lRes1);
    REQUIRE(l1 * 2 != lRes2);


    Value l4 = std::make_shared<std::vector<std::shared_ptr<Value>>>();
    l4.get<Value::LIST>()->emplace_back(std::make_shared<Value>(1));
    l4.get<Value::LIST>()->emplace_back(std::make_shared<Value>(10));

    Value l5 = std::make_shared<std::vector<std::shared_ptr<Value>>>();
    l5.get<Value::LIST>()->emplace_back(std::make_shared<Value>(10));
    l5.get<Value::LIST>()->emplace_back(std::make_shared<Value>(1));

    Value l6 = std::make_shared<std::vector<std::shared_ptr<Value>>>();
    l6.get<Value::LIST>()->emplace_back(std::make_shared<Value>(1));

 

    // Columns
    Value col1 = std::make_shared<Value::COL_STRUCT>();
    col1.get<Value::COLUMN>()->data = l1.get<Value::LIST>();

    Value col2 = std::make_shared<Value::COL_STRUCT>();
    col2.get<Value::COLUMN>()->data = l2.get<Value::LIST>();

    Value col3 = std::make_shared<Value::COL_STRUCT>();
    col3.get<Value::COLUMN>()->data = l3.get<Value::LIST>();
    
    Value colRes1 = std::make_shared<Value::COL_STRUCT>();
    Value colListRes1 = std::make_shared<std::vector<std::shared_ptr<Value>>>();
    l5.get<Value::LIST>()->emplace_back(std::make_shared<Value>(10));
    l5.get<Value::LIST>()->emplace_back(std::make_shared<Value>(1));

    colRes1.get<Value::COLUMN>()->data = l3.get<Value::LIST>();

    //REQUIRE(col1 + col3);
    //REQUIRE(col3 + col3);
    //REQUIRE(col1 + col1);

    //REQUIRE(col1 * col2);
    //REQUIRE(col2 * col1);

    Value col4 = std::make_shared<Value::COL_STRUCT>();
    col4.get<Value::COLUMN>()->data = l4.get<Value::LIST>();

    Value col5 = std::make_shared<Value::COL_STRUCT>();
    col5.get<Value::COLUMN>()->data = l5.get<Value::LIST>();

    Value col6 = std::make_shared<Value::COL_STRUCT>();
    col6.get<Value::COLUMN>()->data = l6.get<Value::LIST>();

    //REQUIRE(col4 + col5);
    //REQUIRE(col6 + col6);

    //REQUIRE(col4 * col5);
    //REQUIRE(col6 * col6);
}