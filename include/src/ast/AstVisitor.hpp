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

class AstVisitor : public std::enable_shared_from_this<AstVisitor> {
   public:
    virtual void visit(std::shared_ptr<ArthExprNode> node) = 0;

    virtual void visit(std::shared_ptr<AssignNode> node) = 0;

    virtual void visit(std::shared_ptr<ColumnNode> node) = 0;

    virtual void visit(std::shared_ptr<CompExprNode> node) = 0;

    virtual void visit(std::shared_ptr<ElseNode> node) = 0;

    virtual void visit(std::shared_ptr<FilterNode> node) = 0;

    virtual void visit(std::shared_ptr<HeaderIndexNode> node) = 0;

    virtual void visit(std::shared_ptr<IfNode> node) = 0;

    virtual void visit(std::shared_ptr<IndexNode> node) = 0;

    virtual void visit(std::shared_ptr<JuncExprNode> node) = 0;

    virtual void visit(std::shared_ptr<LeafNode> node) = 0;

    virtual void visit(std::shared_ptr<ListNode> node) = 0;

    virtual void visit(std::shared_ptr<NotNode> node) = 0;

    virtual void visit(std::shared_ptr<ParNode> node) = 0;

    virtual void visit(std::shared_ptr<ProcCallNode> node) = 0;

    virtual void visit(std::shared_ptr<ProcDecNode> node) = 0;

    virtual void visit(std::shared_ptr<ProgNode> node) = 0;

    virtual void visit(std::shared_ptr<ReturnNode> node) = 0;

    virtual void visit(std::shared_ptr<TableNode> node) = 0;

    virtual void visit(std::shared_ptr<UnaryExprNode> node) = 0;

    virtual void visit(std::shared_ptr<WhileNode> node) = 0;
};

#endif