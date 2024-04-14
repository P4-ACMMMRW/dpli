#ifndef ASTTESTVISITOR_HPP
#define ASTTESTVISITOR_HPP

#include <AstVisitor.hpp>

class AstTestVisitor : public AstVisitor {
   public:
    void visit(std::shared_ptr<ArthExprNode> node) override;

    void visit(std::shared_ptr<AssignNode> node) override;

    void visit(std::shared_ptr<ColumnNode> node) override;

    void visit(std::shared_ptr<CompExprNode> node) override;

    void visit(std::shared_ptr<ElseNode> node) override;

    void visit(std::shared_ptr<FilterNode> node) override;

    void visit(std::shared_ptr<HeaderIndexNode> node) override;

    void visit(std::shared_ptr<IfNode> node) override;

    void visit(std::shared_ptr<IndexNode> node) override;

    void visit(std::shared_ptr<JuncExprNode> node) override;

    void visit(std::shared_ptr<LeafNode> node) override;

    void visit(std::shared_ptr<ListNode> node) override;

    void visit(std::shared_ptr<NotNode> node) override;

    void visit(std::shared_ptr<ParNode> node) override;

    void visit(std::shared_ptr<ProcCallNode> node) override;

    void visit(std::shared_ptr<ProcDecNode> node) override;

    void visit(std::shared_ptr<ProgNode> node) override;

    void visit(std::shared_ptr<ReturnNode> node) override;

    void visit(std::shared_ptr<TableNode> node) override;

    void visit(std::shared_ptr<UnaryExprNode> node) override;

    void visit(std::shared_ptr<WhileNode> node) override;
};

#endif