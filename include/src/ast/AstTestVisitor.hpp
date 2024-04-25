#ifndef ASTTESTVISITOR_HPP
#define ASTTESTVISITOR_HPP

#include <AstVisitor.hpp>

class AstTestVisitor : public AstVisitor {
   public:
    void visit(const std::shared_ptr<AndExprNode> &node) override {
        std::cout << "Visiting " << node->getText() << '\n';
        AstVisitor::visit(node);
    };
    void visit(const std::shared_ptr<AssignNode> &node) override {
        std::cout << "Visiting " << node->getText() << '\n';
        AstVisitor::visit(node);
    };
    void visit(const std::shared_ptr<ColumnNode> &node) {
        std::cout << "Visiting " << node->getText() << '\n';
        AstVisitor::visit(node);
    };
    void visit(const std::shared_ptr<DivExprNode> &node) override {
        std::cout << "Visiting " << node->getText() << '\n';
        AstVisitor::visit(node);
    };
    void visit(const std::shared_ptr<ElseNode> &node) override {
        std::cout << "Visiting " << node->getText() << '\n';
        AstVisitor::visit(node);
    };
    void visit(const std::shared_ptr<EqualExprNode> &node) override {
        std::cout << "Visiting " << node->getText() << '\n';
        AstVisitor::visit(node);
    };
    void visit(const std::shared_ptr<ExpoExprNode> &node) override {
        std::cout << "Visiting " << node->getText() << '\n';
        AstVisitor::visit(node);
    };
    void visit(const std::shared_ptr<FilterNode> &node) override {
        std::cout << "Visiting " << node->getText() << '\n';
        AstVisitor::visit(node);
    };
    void visit(const std::shared_ptr<GreaterEqualExprNode> &node) override {
        std::cout << "Visiting " << node->getText() << '\n';
        AstVisitor::visit(node);
    };
    void visit(const std::shared_ptr<GreaterExprNode> &node) override {
        AstVisitor::visit(node);
        std::cout << "Visiting " << node->getText() << '\n';
    };
    void visit(const std::shared_ptr<HeaderIndexNode> &node) override {
        std::cout << "Visiting " << node->getText() << '\n';
        AstVisitor::visit(node);
    };
    void visit(const std::shared_ptr<IfNode> &node) override {
        std::cout << "Visiting " << node->getText() << '\n';
        AstVisitor::visit(node);
    };
    void visit(const std::shared_ptr<IndexNode> &node) override {
        std::cout << "Visiting " << node->getText() << '\n';
        AstVisitor::visit(node);
    };
    void visit(const std::shared_ptr<LeafNode> &node) override {
        std::cout << "Visiting " << node->getText() << '\n';
        AstVisitor::visit(node);
    };
    void visit(const std::shared_ptr<LessEqualExprNode> &node) override {
        std::cout << "Visiting " << node->getText() << '\n';
        AstVisitor::visit(node);
    };
    void visit(const std::shared_ptr<LessExprNode> &node) override {
        std::cout << "Visiting " << node->getText() << '\n';
        AstVisitor::visit(node);
    };
    void visit(const std::shared_ptr<ListNode> &node) override {
        std::cout << "Visiting " << node->getText() << '\n';
        AstVisitor::visit(node);
    };
    void visit(const std::shared_ptr<MinusExprNode> &node) override {
        std::cout << "Visiting " << node->getText() << '\n';
        AstVisitor::visit(node);
    };
    void visit(const std::shared_ptr<MinusNode> &node) override {
        std::cout << "Visiting " << node->getText() << '\n';
        AstVisitor::visit(node);
    };
    void visit(const std::shared_ptr<ModExprNode> &node) override {
        std::cout << "Visiting " << node->getText() << '\n';
        AstVisitor::visit(node);
    };
    void visit(const std::shared_ptr<MultExprNode> &node) override {
        std::cout << "Visiting " << node->getText() << '\n';
        AstVisitor::visit(node);
    };
    void visit(const std::shared_ptr<NotNode> &node) override {
        std::cout << "Visiting " << node->getText() << '\n';
        AstVisitor::visit(node);
    };
    void visit(const std::shared_ptr<OrExprNode> &node) override {
        std::cout << "Visiting " << node->getText() << '\n';
        AstVisitor::visit(node);
    };
    void visit(const std::shared_ptr<ParNode> &node) override {
        std::cout << "Visiting " << node->getText() << '\n';
        AstVisitor::visit(node);
    };
    void visit(const std::shared_ptr<PlusExprNode> &node) override {
        std::cout << "Visiting " << node->getText() << '\n';
        AstVisitor::visit(node);
    };
    void visit(const std::shared_ptr<PlusNode> &node) override {
        std::cout << "Visiting " << node->getText() << '\n';
        AstVisitor::visit(node);
    };
    void visit(const std::shared_ptr<ProcCallNode> &node) override {
        std::cout << "Visiting " << node->getText() << '\n';
        AstVisitor::visit(node);
    };
    void visit(const std::shared_ptr<ProcDecNode> &node) override {
        std::cout << "Visiting " << node->getText() << '\n';
        AstVisitor::visit(node);
    };
    void visit(const std::shared_ptr<ProgNode> &node) override {
        std::cout << "Visiting " << node->getText() << '\n';
        AstVisitor::visit(node);
    };
    void visit(const std::shared_ptr<ReturnNode> &node) override {
        std::cout << "Visiting " << node->getText() << '\n';
        AstVisitor::visit(node);
    };
    void visit(const std::shared_ptr<TableNode> &node) override {
        std::cout << "Visiting " << node->getText() << '\n';
        AstVisitor::visit(node);
    };
    void visit(const std::shared_ptr<UnaryExprNode> &node) override {
        std::cout << "Visiting " << node->getText() << '\n';
        AstVisitor::visit(node);
    };
    void visit(const std::shared_ptr<WhileNode> &node) override {
        std::cout << "Visiting " << node->getText() << '\n';
        AstVisitor::visit(node);
    };
};

#endif