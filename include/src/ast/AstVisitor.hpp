#ifndef ASTVISITOR_HPP
#define ASTVISITOR_HPP

#include <memory>

// Forward declaration to avoid circular dependencies
class AstNode;
class ArthExprNode;
class AssignNode;
class ColumnNode;
class CompExprNode;
class ElseNode;
class FilterNode;
class HeaderIndexNode;
class IfNode;
class IndexNode;
class JuncExprNode;
class LeafNode;
class ListNode;
class NotNode;
class ParNode;
class ProcCallNode;
class ProcDecNode;
class ProgNode;
class ReturnNode;
class TableNode;
class UnaryExprNode;
class WhileNode;

class AstVisitor : public std::enable_shared_from_this<AstVisitor> {
   public:
    // Rule of five
    AstVisitor() = default;
    virtual ~AstVisitor() = default;
    AstVisitor(const AstVisitor& other) = delete;
    AstVisitor& operator=(const AstVisitor& other) = delete;
    AstVisitor(AstVisitor&& other) = default;
    AstVisitor& operator=(AstVisitor&& other) = default;

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