#include "TestingUtil.hpp"
#include "VariableTable.hpp"
#include "Variable.hpp"
#include "Procedure.hpp"
#include "ProcedureTable.hpp"
#include "InternalException.hpp"

using namespace dplutil;
using namespace dplsrc;

SYMBOL_TABLE_TEST("variable table") {
    // Bind and lookup test
    VariableTable vtable;
    Variable x = Variable("x", 1);

    vtable.bind(x);

    Variable *x2 = vtable.lookup("x");
    REQUIRE(x2 != nullptr);
    REQUIRE(x2->getId() == "x");
    REQUIRE(x2->getVal().is<Value::INT>());
    REQUIRE(x2->getVal().get<Value::INT>() == 1);

    x2->setVal("str");
    vtable.bind(*x2);

    Variable *x3 = vtable.lookup("x");
    REQUIRE(x3->getVal().is<Value::STR>());
    REQUIRE(x3->getVal().get<Value::STR>() == "str");
    
    // Test scoping
    VariableTable::Scope scope;
    scope.insert({"x", *x3});

    Procedure proc = Procedure("", {""}, {std::make_shared<LeafNode>(nullptr)}, scope);

    vtable.enterScope(proc.getScope());
    Variable y = Variable("y", 10);
    vtable.bind(y);

    REQUIRE(vtable.lookup("x") != nullptr);
    REQUIRE(vtable.lookup("y") != nullptr);

    vtable.exitScope();

    REQUIRE(vtable.lookup("x") != nullptr);
    REQUIRE_THROWS_AS(vtable.lookup("y"), std::out_of_range);
    REQUIRE_THROWS_AS(vtable.exitScope(), InternalException);
}

SYMBOL_TABLE_TEST("procedure table") {
    VariableTable::Scope scope;
    Procedure proc = Procedure("proc", {"x"}, {std::make_shared<LeafNode>(nullptr)}, scope);
    REQUIRE(proc.isBuiltinProcedure() == false);
    REQUIRE(proc.getArity() == 1);

    ProcedureTable ptable;
    ptable.bind(proc);

    Procedure *proc2 = ptable.lookup("proc", proc.getArity());

    REQUIRE_THROWS_AS(ptable.lookup("proc", 2), std::out_of_range);
    REQUIRE(proc2->isBuiltinProcedure() == proc.isBuiltinProcedure());
    REQUIRE(proc2->getArity() == proc.getArity());
    REQUIRE(proc2->getId() == proc.getId());
}
