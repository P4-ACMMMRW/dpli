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
class UnaryExprNode;
class UnionExprNode;
class WhileNode;

// Abstract
class BinaryNode;
class UnaryNode;
class UnaryNodeList;

class AstVisitor : public std::enable_shared_from_this<AstVisitor> {
   public:
    virtual void visit(const std::shared_ptr<AndExprNode> &node);
    virtual void visit(const std::shared_ptr<AssignNode> &node);
    virtual void visit(const std::shared_ptr<ColumnNode> &node);
    virtual void visit(const std::shared_ptr<DivExprNode> &node);
    virtual void visit(const std::shared_ptr<ElseNode> &node);
    virtual void visit(const std::shared_ptr<EqualExprNode> &node);
    virtual void visit(const std::shared_ptr<ExpoExprNode> &node);
    virtual void visit(const std::shared_ptr<FilterNode> &node);
    virtual void visit(const std::shared_ptr<GreaterEqualExprNode> &node);
    virtual void visit(const std::shared_ptr<GreaterExprNode> &node);
    virtual void visit(const std::shared_ptr<HeaderIndexNode> &node);
    virtual void visit(const std::shared_ptr<IfNode> &node);
    virtual void visit(const std::shared_ptr<IndexNode> &node);
    virtual void visit(const std::shared_ptr<IntersectionExprNode> &node);
    virtual void visit(const std::shared_ptr<LeafNode> &node);
    virtual void visit(const std::shared_ptr<LessEqualExprNode> &node);
    virtual void visit(const std::shared_ptr<LessExprNode> &node);
    virtual void visit(const std::shared_ptr<ListNode> &node);
    virtual void visit(const std::shared_ptr<MinusExprNode> &node);
    virtual void visit(const std::shared_ptr<MinusNode> &node);
    virtual void visit(const std::shared_ptr<ModExprNode> &node);
    virtual void visit(const std::shared_ptr<MultExprNode> &node);
    virtual void visit(const std::shared_ptr<NotEqualExprNode> &node);
    virtual void visit(const std::shared_ptr<NotNode> &node);
    virtual void visit(const std::shared_ptr<OrExprNode> &node);
    virtual void visit(const std::shared_ptr<ParNode> &node);
    virtual void visit(const std::shared_ptr<PlusExprNode> &node);
    virtual void visit(const std::shared_ptr<PlusNode> &node);
    virtual void visit(const std::shared_ptr<ProcCallNode> &node);
    virtual void visit(const std::shared_ptr<ProcDecNode> &node);
    virtual void visit(const std::shared_ptr<ProgNode> &node);
    virtual void visit(const std::shared_ptr<ReturnNode> &node);
    virtual void visit(const std::shared_ptr<TableNode> &node);
    virtual void visit(const std::shared_ptr<UnaryExprNode> &node);
    virtual void visit(const std::shared_ptr<UnionExprNode> &node);
    virtual void visit(const std::shared_ptr<WhileNode> &node);

   private:
    void visit(const std::shared_ptr<BinaryNode> &node);
    void visit(const std::shared_ptr<UnaryNode> &node);
    void visit(const std::shared_ptr<UnaryNodeList> &node);
};

#endif