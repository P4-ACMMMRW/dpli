#ifndef ASTVISITOR_HPP
#define ASTVISITOR_HPP

#include <memory>

class AstNode;          // Forward declaration
class ArthExprNode;     // Forward declaration
class AssignNode;       // Forward declaration
class ColumnNode;       // Forward declaration
class CompExprNode;     // Forward declaration
class ElseNode;         // Forward declaration
class FilterNode;       // Forward declaration
class HeaderIndexNode;  // Forward declaration
class IfNode;           // Forward declaration
class IndexNode;        // Forward declaration
class JuncExprNode;     // Forward declaration
class LeafNode;         // Forward declaration
class ListNode;         // Forward declaration
class NotNode;          // Forward declaration
class ParNode;          // Forward declaration
class ProcCallNode;     // Forward declaration
class ProcDecNode;      // Forward declaration
class ProgNode;         // Forward declaration
class ReturnNode;       // Forward declaration
class TableNode;        // Forward declaration
class UnaryExprNode;    // Forward declaration
class WhileNode;        // Forward declaration

class AstVisitor {
   public:
    virtual void visit(ArthExprNode* node) = 0;

    virtual void visit(AssignNode* node) = 0;

    virtual void visit(ColumnNode* node) = 0;

    virtual void visit(CompExprNode* node) = 0;

    virtual void visit(ElseNode* node) = 0;

    virtual void visit(FilterNode* node) = 0;

    virtual void visit(HeaderIndexNode* node) = 0;

    virtual void visit(IfNode* node) = 0;

    virtual void visit(IndexNode* node) = 0;

    virtual void visit(JuncExprNode* node) = 0;

    virtual void visit(LeafNode* node) = 0;

    virtual void visit(ListNode* node) = 0;

    virtual void visit(NotNode* node) = 0;

    virtual void visit(ParNode* node) = 0;

    virtual void visit(ProcCallNode* node) = 0;

    virtual void visit(ProcDecNode* node) = 0;

    virtual void visit(ProgNode* node) = 0;

    virtual void visit(ReturnNode* node) = 0;

    virtual void visit(TableNode* node) = 0;

    virtual void visit(UnaryExprNode* node) = 0;

    virtual void visit(WhileNode* node) = 0;
};

#endif