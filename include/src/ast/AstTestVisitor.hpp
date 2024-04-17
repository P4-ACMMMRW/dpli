#ifndef ASTTESTVISITOR_HPP
#define ASTTESTVISITOR_HPP

#include <AstVisitor.hpp>

class AstTestVisitor : public AstVisitor {
   public:
    void visit(std::shared_ptr<AndExprNode> node) override {
        AstVisitor::visit(node);
        std::cout << "Visiting " << node->getText() << '\n';
    };
    void visit(std::shared_ptr<AssignNode> node) override {
        AstVisitor::visit(node);
        std::cout << "Visiting " << node->getText() << '\n';
    };
    void visit(std::shared_ptr<ColumnNode> node) {
        AstVisitor::visit(node);
        std::cout << "Visiting " << node->getText() << '\n';
    };
    void visit(std::shared_ptr<DivExprNode> node) override{
        AstVisitor::visit(node);
        std::cout << "Visiting " << node->getText() << '\n';
    };
    void visit(std::shared_ptr<ElseNode> node) override{
        AstVisitor::visit(node);
        std::cout << "Visiting " << node->getText() << '\n';
    };
    void visit(std::shared_ptr<EqualExprNode> node) override{
        AstVisitor::visit(node);
        std::cout << "Visiting " << node->getText() << '\n';
    };
    void visit(std::shared_ptr<ExpoExprNode> node) override{
        AstVisitor::visit(node);
        std::cout << "Visiting " << node->getText() << '\n';
    };
    void visit(std::shared_ptr<FilterNode> node) override{
        AstVisitor::visit(node);
        std::cout << "Visiting " << node->getText() << '\n';
    };
    void visit(std::shared_ptr<GreaterEqualExprNode> node) override{
        AstVisitor::visit(node);
        std::cout << "Visiting " << node->getText() << '\n';
    };
    void visit(std::shared_ptr<GreaterExprNode> node) override{
        AstVisitor::visit(node);
        std::cout << "Visiting " << node->getText() << '\n';
    };
    void visit(std::shared_ptr<HeaderIndexNode> node) override{
        AstVisitor::visit(node);
        std::cout << "Visiting " << node->getText() << '\n';
    };
    void visit(std::shared_ptr<IfNode> node) override{
        AstVisitor::visit(node);
        std::cout << "Visiting " << node->getText() << '\n';
    };
    void visit(std::shared_ptr<IndexNode> node) override{
        AstVisitor::visit(node);
        std::cout << "Visiting " << node->getText() << '\n';
    };
    void visit(std::shared_ptr<LeafNode> node) override{
        AstVisitor::visit(node);
        std::cout << "Visiting " << node->getText() << '\n';
    };
    void visit(std::shared_ptr<LessEqualExprNode> node) override{
        AstVisitor::visit(node);
        std::cout << "Visiting " << node->getText() << '\n';
    };
    void visit(std::shared_ptr<LessExprNode> node) override{
        AstVisitor::visit(node);
        std::cout << "Visiting " << node->getText() << '\n';
    };
    void visit(std::shared_ptr<ListNode> node) override{
        AstVisitor::visit(node);
        std::cout << "Visiting " << node->getText() << '\n';
    };
    void visit(std::shared_ptr<MinusExprNode> node) override{
        AstVisitor::visit(node);
        std::cout << "Visiting " << node->getText() << '\n';
    };
    void visit(std::shared_ptr<MinusNode> node) override{
        AstVisitor::visit(node);
        std::cout << "Visiting " << node->getText() << '\n';
    };
    void visit(std::shared_ptr<ModExprNode> node) override{
        AstVisitor::visit(node);
        std::cout << "Visiting " << node->getText() << '\n';
    };
    void visit(std::shared_ptr<MultExprNode> node) override{
        AstVisitor::visit(node);
        std::cout << "Visiting " << node->getText() << '\n';
    };
    void visit(std::shared_ptr<NotNode> node) override{
        AstVisitor::visit(node);
        std::cout << "Visiting " << node->getText() << '\n';
    };
    void visit(std::shared_ptr<OrExprNode> node) override{
        AstVisitor::visit(node);
        std::cout << "Visiting " << node->getText() << '\n';
    };
    void visit(std::shared_ptr<ParNode> node) override{
        AstVisitor::visit(node);
        std::cout << "Visiting " << node->getText() << '\n';
    };
    void visit(std::shared_ptr<PlusExprNode> node) override{
        AstVisitor::visit(node);
        std::cout << "Visiting " << node->getText() << '\n';
    };
    void visit(std::shared_ptr<PlusNode> node) override{
        AstVisitor::visit(node);
        std::cout << "Visiting " << node->getText() << '\n';
    };
    void visit(std::shared_ptr<ProcCallNode> node) override{
        AstVisitor::visit(node);
        std::cout << "Visiting " << node->getText() << '\n';
    };
    void visit(std::shared_ptr<ProcDecNode> node) override{
        AstVisitor::visit(node);
        std::cout << "Visiting " << node->getText() << '\n';
    };
    void visit(std::shared_ptr<ProgNode> node) override{
        AstVisitor::visit(node);
        std::cout << "Visiting " << node->getText() << '\n';
    };
    void visit(std::shared_ptr<ReturnNode> node) override{
        AstVisitor::visit(node);
        std::cout << "Visiting " << node->getText() << '\n';
    };
    void visit(std::shared_ptr<TableNode> node) override{
        AstVisitor::visit(node);
        std::cout << "Visiting " << node->getText() << '\n';
    };
    void visit(std::shared_ptr<UnaryExprNode> node) override{
        AstVisitor::visit(node);
        std::cout << "Visiting " << node->getText() << '\n';
    };
    void visit(std::shared_ptr<WhileNode> node) override{
        AstVisitor::visit(node);
        std::cout << "Visiting " << node->getText() << '\n';
    };
};

#endif