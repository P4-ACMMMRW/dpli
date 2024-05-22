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

    REQUIRE((!valBool) == false);
    REQUIRE((!valInt) == false);
    REQUIRE((!valFloat) == false);


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

     REQUIRE((!str1) == false);

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

    REQUIRE((!l1) == false);    
    REQUIRE((!l2) == false);
    REQUIRE((!l3) == false);

    Value l4 = std::make_shared<std::vector<std::shared_ptr<Value>>>();
    l4.get<Value::LIST>()->emplace_back(std::make_shared<Value>(1));
    l4.get<Value::LIST>()->emplace_back(std::make_shared<Value>(10));

    Value l5 = std::make_shared<std::vector<std::shared_ptr<Value>>>();
    l5.get<Value::LIST>()->emplace_back(std::make_shared<Value>(10));
    l5.get<Value::LIST>()->emplace_back(std::make_shared<Value>(1));

    Value l6 = std::make_shared<std::vector<std::shared_ptr<Value>>>();
    l6.get<Value::LIST>()->emplace_back(std::make_shared<Value>(1));

    Value l7 = std::make_shared<std::vector<std::shared_ptr<Value>>>();

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

    REQUIRE((!l4) == false);    
    REQUIRE((!l5) == false);
    REQUIRE((!l6) == false);
    REQUIRE((!l7) == true);    

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
    Value tab1 = std::make_shared<std::pair<std::vector<Value::STR>, std::unordered_map<Value::STR, Value::COLUMN>>>();
    tab1.get<Value::TABLE>()->second.insert({"col", col1.get<Value::COLUMN>()});

    Value tab2 = std::make_shared<std::pair<std::vector<Value::STR>, std::unordered_map<Value::STR, Value::COLUMN>>>();
    tab2.get<Value::TABLE>()->second.insert({"col", col2.get<Value::COLUMN>()});

    Value tab3 = std::make_shared<std::pair<std::vector<Value::STR>, std::unordered_map<Value::STR, Value::COLUMN>>>();
    tab3.get<Value::TABLE>()->second.insert({"col", col3.get<Value::COLUMN>()});

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

    Value tab4 = std::make_shared<std::pair<std::vector<Value::STR>, std::unordered_map<Value::STR, Value::COLUMN>>>();
    REQUIRE(tab1 != tab4);

    Value tab5 = std::make_shared<std::pair<std::vector<Value::STR>, std::unordered_map<Value::STR, Value::COLUMN>>>();
    tab5.get<Value::TABLE>()->second.insert({"diff_key", col1.get<Value::COLUMN>()});

    REQUIRE(tab1 != tab5);
    REQUIRE(tab4 < tab1);
    
}


VALUE_TEST("Logical values") { 
    // Numeric
    Value valFloat = 1.0;
    Value valInt = 1;
    Value valBool = true;

    REQUIRE((valFloat && valInt) == valInt);
    REQUIRE((valFloat && valBool) == valBool);
    REQUIRE((valInt && valFloat) == valFloat);
    REQUIRE((valInt && valBool) == valBool);
    REQUIRE((valBool && valInt) == valInt);
    REQUIRE((valBool && valFloat) == valFloat);

    REQUIRE((valFloat || valInt) == valFloat);
    REQUIRE((valFloat || valBool) == valFloat);
    REQUIRE((valInt || valFloat) == valInt);
    REQUIRE((valInt || valBool) == valInt);
    REQUIRE((valBool || valInt) == valBool);
    REQUIRE((valBool || valFloat) == valBool);
    // Strings
    Value str1 = "";
    Value str2 = "abc";
    REQUIRE((str1 && str2) == str1);
    REQUIRE((str2 && str1) == str1);
    REQUIRE((str2 || str1) == str2);
    REQUIRE((str1 || str2) == str2);

    // NoneType
    Value n1 = Value(nullptr);
    Value n2 = Value(nullptr);

    REQUIRE((n1 && n2) == n2);
    REQUIRE((n1 || n2) == n1);

    // List
    Value l1 = std::make_shared<std::vector<std::shared_ptr<Value>>>();
    l1.get<Value::LIST>()->emplace_back(std::make_shared<Value>("a"));
    l1.get<Value::LIST>()->emplace_back(std::make_shared<Value>(1));

    Value l2 = std::make_shared<std::vector<std::shared_ptr<Value>>>();
    l2.get<Value::LIST>()->emplace_back(std::make_shared<Value>(1));
    l2.get<Value::LIST>()->emplace_back(std::make_shared<Value>("a"));

    Value l3 = std::make_shared<std::vector<std::shared_ptr<Value>>>();

    REQUIRE((l1 && l2) == l2);
    REQUIRE((l1 && l3) == l3);
    REQUIRE((l2 && l1) == l1);
    REQUIRE((l2 && l3) == l3);
    REQUIRE((l3 && l1) == l3);
    REQUIRE((l3 && l2) == l3);

    REQUIRE((l1 || l2) == l1);
    REQUIRE((l1 || l3) == l1);
    REQUIRE((l2 || l1) == l2);
    REQUIRE((l2 || l3) == l2);
    REQUIRE((l3 || l1) == l1);
    REQUIRE((l3 || l2) == l2);

    // Columns
    Value col1 = std::make_shared<Value::COL_STRUCT>();
    col1.get<Value::COLUMN>()->data = l1.get<Value::LIST>();

    Value col2 = std::make_shared<Value::COL_STRUCT>();
    col2.get<Value::COLUMN>()->data = l2.get<Value::LIST>();

    Value col3 = std::make_shared<Value::COL_STRUCT>();
    col3.get<Value::COLUMN>()->data = l3.get<Value::LIST>();

    REQUIRE((col1 && col2) == col2);
    REQUIRE((col1 && col3) == col3);
    REQUIRE((col2 && col1) == col1);
    REQUIRE((col2 && col3) == col3);
    REQUIRE((col3 && col1) == col3);
    REQUIRE((col3 && col2) == col3);

    REQUIRE((col1 || col2) == col1);
    REQUIRE((col1 || col3) == col1);
    REQUIRE((col2 || col1) == col2);
    REQUIRE((col2 || col3) == col2);
    REQUIRE((col3 || col1) == col1);
    REQUIRE((col3 || col2) == col2);

    // Tables
    Value tab1 = std::make_shared<std::pair<std::vector<Value::STR>, std::unordered_map<Value::STR, Value::COLUMN>>>();
    tab1.get<Value::TABLE>()->second.insert({"col", col1.get<Value::COLUMN>()});

    Value tab2 = std::make_shared<std::pair<std::vector<Value::STR>, std::unordered_map<Value::STR, Value::COLUMN>>>();
    tab2.get<Value::TABLE>()->second.insert({"col", col2.get<Value::COLUMN>()});

    Value tab3 = std::make_shared<std::pair<std::vector<Value::STR>, std::unordered_map<Value::STR, Value::COLUMN>>>();

    REQUIRE((tab1 && tab2) == tab2);
    REQUIRE((tab1 && tab3) == tab3);
    REQUIRE((tab2 && tab1) == tab1);
    REQUIRE((tab2 && tab3) == tab3);
    REQUIRE((tab3 && tab1) == tab3);
    REQUIRE((tab3 && tab2) == tab3);

    REQUIRE((tab1 || tab2) == tab1);
    REQUIRE((tab1 || tab3) == tab1);
    REQUIRE((tab2 || tab1) == tab2);
    REQUIRE((tab2 || tab3) == tab2);
    REQUIRE((tab3 || tab1) == tab1);
    REQUIRE((tab3 || tab2) == tab2);
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

    REQUIRE(Value(5) - Value(3) == Value(2));

    REQUIRE(valFloat - valInt == 0.0);
    REQUIRE(valFloat - valBool == 0.0);
    REQUIRE(valInt - valFloat == 0.0);
    REQUIRE(valInt - valBool == 0);
    REQUIRE(valBool - valInt == 0);
    REQUIRE(valBool - valFloat == 0.0);

    REQUIRE(valFloat * valInt == 1.0);
    REQUIRE(valFloat * valBool == 1.0);
    REQUIRE(valInt * valFloat == 1.0);
    REQUIRE(valInt * valBool == 1);
    REQUIRE(valBool * valInt == 1);
    REQUIRE(valBool * valFloat == 1.0);

    
    REQUIRE(Value(6) / Value(3) == Value(2));

    REQUIRE(valFloat / valInt == 1.0);
    REQUIRE(valFloat / valBool == 1.0);
    REQUIRE(valInt / valFloat == 1.0);
    REQUIRE(valInt / valBool == 1);
    REQUIRE(valBool / valInt == 1);
    REQUIRE(valBool / valFloat == 1.0);


    REQUIRE(Value(9) % Value(4) == Value(1));

    REQUIRE(valFloat % valInt == 0.0);
    REQUIRE(valFloat % valBool == 0.0);
    REQUIRE(valInt % valFloat == 0.0);
    REQUIRE(valInt % valBool == 0);
    REQUIRE(valBool % valInt == 0);
    REQUIRE(valBool % valFloat == 0.0);

    
    REQUIRE(Value(3).pow(Value(3)) == Value(27));

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
    Value str2 = "";

    REQUIRE(str1 + str1 == "abcabc");
    REQUIRE(str1 * 2 == "abcabc");

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


    REQUIRE(l1 * Value(2) == lRes1);
    REQUIRE(l1 * Value(2) != lRes2);
    
    REQUIRE(Value(2) * l1 == lRes1);
    REQUIRE(Value(2) * l1 != lRes2);


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
    colListRes1.get<Value::LIST>()->emplace_back(std::make_shared<Value>("aa"));
    colListRes1.get<Value::LIST>()->emplace_back(std::make_shared<Value>(2));
    colRes1.get<Value::COLUMN>()->data = colListRes1.get<Value::LIST>();

    REQUIRE(col1 + col3 == colListRes1);
    REQUIRE(col3 + col3 == colListRes1);
    REQUIRE(col1 + col1 == colListRes1);

    Value colRes2 = std::make_shared<Value::COL_STRUCT>();
    Value colListRes2 = std::make_shared<std::vector<std::shared_ptr<Value>>>();
    colListRes2.get<Value::LIST>()->emplace_back(std::make_shared<Value>("a"));
    colListRes2.get<Value::LIST>()->emplace_back(std::make_shared<Value>("a"));

    REQUIRE(col1 * col2 == colListRes2);
    REQUIRE(col2 * col1 == colListRes2);

    Value col4 = std::make_shared<Value::COL_STRUCT>();
    col4.get<Value::COLUMN>()->data = l4.get<Value::LIST>();

    Value col5 = std::make_shared<Value::COL_STRUCT>();
    col5.get<Value::COLUMN>()->data = l5.get<Value::LIST>();

    Value col6 = std::make_shared<Value::COL_STRUCT>();
    col6.get<Value::COLUMN>()->data = l6.get<Value::LIST>();

    Value colListRes3 = std::make_shared<std::vector<std::shared_ptr<Value>>>();
    colListRes3.get<Value::LIST>()->emplace_back(std::make_shared<Value>(11));
    colListRes3.get<Value::LIST>()->emplace_back(std::make_shared<Value>(11));

    REQUIRE(col4 + col5 == colListRes3);

    Value colListRes4 = std::make_shared<std::vector<std::shared_ptr<Value>>>();
    colListRes4.get<Value::LIST>()->emplace_back(std::make_shared<Value>(2));

    REQUIRE(col6 + col6 == colListRes4);

    Value colListRes5 = std::make_shared<std::vector<std::shared_ptr<Value>>>();
    colListRes5.get<Value::LIST>()->emplace_back(std::make_shared<Value>(10));
    colListRes5.get<Value::LIST>()->emplace_back(std::make_shared<Value>(10));

    REQUIRE(col4 * col5 == colListRes5);

    REQUIRE(col6 * valInt == l6);
    REQUIRE(valInt * col6 == l6);
    
    REQUIRE(Value(2) * col6 == colListRes4);
    REQUIRE(col6 * Value(2) == colListRes4);

    Value colRes6 = std::make_shared<Value::COL_STRUCT>();
    Value colListRes6 = std::make_shared<std::vector<std::shared_ptr<Value>>>();
    colListRes6.get<Value::LIST>()->emplace_back(std::make_shared<Value>(-1));
    colRes6.get<Value::COLUMN>()->data = colListRes1.get<Value::LIST>();

    REQUIRE(-col6  == colListRes6);

    // Exceptions
        // FLOAT
    REQUIRE_THROWS_AS(valFloat / Value(0), dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(valFloat % Value(0), dplsrc::RuntimeException);

    REQUIRE_THROWS_AS(valFloat + str1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(valFloat - str1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(valFloat * str1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(valFloat / str1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(valFloat % str1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(valFloat.pow(str1), dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(valFloat + l1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(valFloat - l1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(valFloat * l1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(valFloat / l1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(valFloat % l1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(valFloat.pow(l1), dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(valFloat + col1, dplsrc::RuntimeException);
    REQUIRE_NOTHROW(valFloat + col4);
    REQUIRE_THROWS_AS(valFloat - col1, dplsrc::RuntimeException);
    REQUIRE_NOTHROW(valFloat - col4);
    REQUIRE_THROWS_AS(valFloat * col1, dplsrc::RuntimeException);
    REQUIRE_NOTHROW(valFloat * col4);
    REQUIRE_THROWS_AS(valFloat / col1, dplsrc::RuntimeException);
    REQUIRE_NOTHROW(valFloat / col4);
    REQUIRE_THROWS_AS(valFloat % col1, dplsrc::RuntimeException);
    REQUIRE_NOTHROW(valFloat % col4);
    REQUIRE_THROWS_AS(valFloat.pow(col1), dplsrc::RuntimeException);
    REQUIRE_NOTHROW(valFloat.pow(col4));

        // INT
        
    REQUIRE_THROWS_AS(valInt / Value(0), dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(valInt % Value(0), dplsrc::RuntimeException);

    REQUIRE_THROWS_AS(valInt + str1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(valInt - str1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(valInt / str1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(valInt % str1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(valInt.pow(str1), dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(valInt + l1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(valInt - l1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(valInt / l1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(valInt % l1, dplsrc::RuntimeException);

        // BOOL
    
    REQUIRE_THROWS_AS(valBool / Value(0), dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(valBool % Value(0), dplsrc::RuntimeException);

    REQUIRE_THROWS_AS(valBool + str1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(valBool - str1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(valBool / str1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(valBool % str1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(valBool.pow(str1), dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(valBool + l1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(valBool - l1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(valBool / l1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(valBool % l1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(valBool.pow(l1), dplsrc::RuntimeException);

        // STR
    REQUIRE_THROWS_AS(str1 + valFloat, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(str1 - valFloat, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(str1 * valFloat, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(str1 / valFloat, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(str1 % valFloat, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(str1.pow(valFloat), dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(str1 + valInt, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(str1 - valInt, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(str1 / valInt, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(str1 % valInt, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(str1.pow(valInt), dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(str1 + valBool, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(str1 - valBool, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(str1 / valBool, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(str1 % valBool, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(str1.pow(valBool), dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(str1 + l1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(str1 - l1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(str1 * l1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(str1 / l1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(str1 % l1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(str1.pow(l1), dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(str1 + col1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(str1 - col1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(str1 * col1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(str1 / col1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(str1 % col1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(str1.pow(col1), dplsrc::RuntimeException);

    REQUIRE_THROWS_AS(-str1, dplsrc::RuntimeException);

        // LIST
    REQUIRE_THROWS_AS(l1 + valFloat, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(l1 - valFloat, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(l1 * valFloat, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(l1 / valFloat, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(l1 % valFloat, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(l1.pow(valFloat), dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(l1 + valInt, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(l1 - valInt, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(l1 / valInt, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(l1 % valInt, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(l1.pow(valInt), dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(l1 + valBool, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(l1 - valBool, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(l1 / valBool, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(l1 % valBool, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(l1.pow(valBool), dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(l1 + str1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(l1 - str1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(l1 * str1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(l1 / str1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(l1 % str1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(l1.pow(str1), dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(l1 + col1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(l1 - col1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(l1 * col1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(l1 / col1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(l1 % col1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(l1.pow(col1), dplsrc::RuntimeException);

    REQUIRE_THROWS_AS(-l1, dplsrc::RuntimeException);

    // Column
    
    Value lEmpty = std::make_shared<std::vector<std::shared_ptr<Value>>>();
    Value colEmpty = std::make_shared<Value::COL_STRUCT>();
    colEmpty.get<Value::COLUMN>()->data = lEmpty.get<Value::LIST>();
    
    REQUIRE_THROWS_AS(!col1, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(col1 + colEmpty, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(colEmpty + col1 , dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(col1 - colEmpty, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(colEmpty - col1 , dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(col1 * colEmpty, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(colEmpty * col1 , dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(col1 / colEmpty, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(colEmpty / col1 , dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(col1 % colEmpty, dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(colEmpty % col1 , dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(col1.pow(colEmpty), dplsrc::RuntimeException);
    REQUIRE_THROWS_AS(colEmpty.pow(col1) , dplsrc::RuntimeException);

}