#ifndef ASTTESTVISITOR_HPP
#define ASTTESTVISITOR_HPP

#include <AstVisitor.hpp>

class AstTestVisitor : public AstVisitor {
   public:
    void visit(ArthExprNode* node) override;

    void visit(AssignNode* node) override;

    void visit(ColumnNode* node) override;

    void visit(CompExprNode* node) override;

    void visit(ElseNode* node) override;

    void visit(FilterNode* node) override;

    void visit(HeaderIndexNode* node) override;

    void visit(IfNode* node) override;

    void visit(IndexNode* node) override;

    void visit(JuncExprNode* node) override;

    void visit(LeafNode* node) override;

    void visit(ListNode* node) override;

    void visit(NotNode* node) override;

    void visit(ParNode* node) override;

    void visit(ProcCallNode* node) override;

    void visit(ProcDecNode* node) override;

    void visit(ProgNode* node) override;

    void visit(ReturnNode* node) override;

    void visit(TableNode* node) override;

    void visit(UnaryExprNode* node) override;

    void visit(WhileNode* node) override;
};

#endif