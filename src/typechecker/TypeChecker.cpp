#include <cassert>
#include <stdexcept>
#include <any>

#include <TypeChecker.hpp>


using namespace dplsrc;
SymbolTable vtable;

std::any TypeChecker::visitAssignstm(AssignNode *node) {
    //Get the type of the assigned variable
    auto dataType = std::any_cast<SymbolType>(visit(node->dataType()));

    //Update type of symbol table entry
    Symbol *varEntry = vtable.lookup(node->varName);
    assert(varEntry != nullptr);
    varEntry->type = dataType;

    node->setEvaluatedSymbolType(dataType);
    //error because visitor isnt in this branch
    return ExprResult(dataType, varEntry);
}

std::any visitArthexpr(ArthExprNode *node) {
    //checks if at least one operator is applied
    if (node-> children.size() == 1)
        return visit(node->operands().front());
    
    //checks the types of the 2 operands and the operator
    auto lefthand = std::any_cast<ExprResult>(visit(node->operands().at(0)));
    auto righthand = std::any_cast<ExprResult>(visit(node->operands().at(1)));

    //Addition


    //Substraction

    
    //multiplication

    
    //division




}

std::any visitCompexpr(CompExprNode *node) {

}

std::any visitFiltering(FilterNode *node) {

}

std::any visitIndex(IndexNode *node) {

}

std::any visitNotexpr(NotNode *node) {

}

std::any visitUnaryexpr(UnaryExprNode *node) {

}

std::any visitWhilestm(WhileNode *node) {

}
