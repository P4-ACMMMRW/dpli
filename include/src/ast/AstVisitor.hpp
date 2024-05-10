#ifndef ASTVISITOR_HPP
#define ASTVISITOR_HPP

#include <any>
#include <memory>

// Forward declaration to avoid circular dependencies
class AstNode;
class AndExprNode;
class AssignNode;
class ColumnNode;
class DivExprNode;
class ElseNode;
class EqualExprNode;
class ExpoExprNode;
class FilterNode;
class GreaterEqualExprNode;
class GreaterExprNode;
class HeaderIndexNode;
class IfNode;
class IndexNode;
class IntersectionExprNode;
class LeafNode;
class LessEqualExprNode;
class LessExprNode;
class ListNode;
class MinusExprNode;
class MinusNode;
class ModExprNode;
class MultExprNode;
class NotEqualExprNode;
class NotNode;
class OrExprNode;
class ParNode;
class PlusExprNode;
class PlusNode;
class ProcCallNode;
class ProcDecNode;
class ProgNode;
class ReturnNode;
class TableNode;
class UnionExprNode;
class WhileNode;

// Abstract
class BinaryNode;
class UnaryNode;
class UnaryNodeList;

class AstVisitor : public std::enable_shared_from_this<AstVisitor> {
   public:
    virtual ~AstVisitor() = default;
    
    virtual void visit(const std::shared_ptr<ProgNode> &node) = 0;
    virtual void visit(const std::shared_ptr<AndExprNode> &node) = 0;
    virtual void visit(const std::shared_ptr<AssignNode> &node) = 0;
    virtual void visit(const std::shared_ptr<ColumnNode> &node) = 0;
    virtual void visit(const std::shared_ptr<DivExprNode> &node) = 0;
    virtual void visit(const std::shared_ptr<ElseNode> &node) = 0;
    virtual void visit(const std::shared_ptr<EqualExprNode> &node) = 0;
    virtual void visit(const std::shared_ptr<ExpoExprNode> &node) = 0;
    virtual void visit(const std::shared_ptr<FilterNode> &node) = 0;
    virtual void visit(const std::shared_ptr<GreaterEqualExprNode> &node) = 0;
    virtual void visit(const std::shared_ptr<GreaterExprNode> &node) = 0;
    virtual void visit(const std::shared_ptr<HeaderIndexNode> &node) = 0;
    virtual void visit(const std::shared_ptr<IfNode> &node) = 0;
    virtual void visit(const std::shared_ptr<IndexNode> &node) = 0;
    virtual void visit(const std::shared_ptr<IntersectionExprNode> &node) = 0;
    virtual void visit(const std::shared_ptr<LeafNode> &node) = 0;
    virtual void visit(const std::shared_ptr<LessEqualExprNode> &node) = 0;
    virtual void visit(const std::shared_ptr<LessExprNode> &node) = 0;
    virtual void visit(const std::shared_ptr<ListNode> &node) = 0;
    virtual void visit(const std::shared_ptr<MinusExprNode> &node) = 0;
    virtual void visit(const std::shared_ptr<MinusNode> &node) = 0;
    virtual void visit(const std::shared_ptr<ModExprNode> &node) = 0;
    virtual void visit(const std::shared_ptr<MultExprNode> &node) = 0;
    virtual void visit(const std::shared_ptr<NotEqualExprNode> &node) = 0;
    virtual void visit(const std::shared_ptr<NotNode> &node) = 0;
    virtual void visit(const std::shared_ptr<OrExprNode> &node) = 0;
    virtual void visit(const std::shared_ptr<ParNode> &node) = 0;
    virtual void visit(const std::shared_ptr<PlusExprNode> &node) = 0;
    virtual void visit(const std::shared_ptr<PlusNode> &node) = 0;
    virtual void visit(const std::shared_ptr<ProcCallNode> &node) = 0;
    virtual void visit(const std::shared_ptr<ProcDecNode> &node) = 0;
    virtual void visit(const std::shared_ptr<ReturnNode> &node) = 0;
    virtual void visit(const std::shared_ptr<TableNode> &node) = 0;
    virtual void visit(const std::shared_ptr<UnionExprNode> &node) = 0;
    virtual void visit(const std::shared_ptr<WhileNode> &node) = 0;

   private:
    void visit(const std::shared_ptr<BinaryNode> &node);
    void visit(const std::shared_ptr<UnaryNode> &node);
    void visit(const std::shared_ptr<UnaryNodeList> &node);
};

#endif