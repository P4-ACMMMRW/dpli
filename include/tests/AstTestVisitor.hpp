#ifndef ASTTESTVISITOR_HPP
#define ASTTESTVISITOR_HPP

#include <catch2/catch_test_macros.hpp>
#include <utility>

#include "AstBuilder.hpp"
#include "AstNode.hpp"
#include "AstVisitor.hpp"

class AstTestVisitor : public AstVisitor {
   public:
    AstTestVisitor(std::vector<size_t> expectedTreeNodes, dplgrammar::DplParser *parser,
                   dplgrammar::DplLexer *lexer)
        : parser(parser), lexer(lexer), expectedTreeNodes(std::move(expectedTreeNodes)) {}

    void visit(const std::shared_ptr<AndExprNode> &node) override {
        std::shared_ptr<AstNode> astNode = std::dynamic_pointer_cast<AstNode>(node);
        test(astNode);
        AstVisitor::visit(node);
    };

    void visit(const std::shared_ptr<AssignNode> &node) override {
        std::shared_ptr<AstNode> astNode = std::dynamic_pointer_cast<AstNode>(node);
        test(astNode);
        AstVisitor::visit(node);
    };

    void visit(const std::shared_ptr<BreakNode> &node) override {
        std::shared_ptr<AstNode> astNode = std::dynamic_pointer_cast<AstNode>(node);
        test(astNode);
        AstVisitor::visit(node);
    };

    void visit(const std::shared_ptr<ColumnNode> &node) override {
        std::shared_ptr<AstNode> astNode = std::dynamic_pointer_cast<AstNode>(node);
        test(astNode);
        AstVisitor::visit(node);
    };

    void visit(const std::shared_ptr<ContinueNode> &node) override {
        std::shared_ptr<AstNode> astNode = std::dynamic_pointer_cast<AstNode>(node);
        test(astNode);
        AstVisitor::visit(node);
    };

    void visit(const std::shared_ptr<DivExprNode> &node) override {
        std::shared_ptr<AstNode> astNode = std::dynamic_pointer_cast<AstNode>(node);
        test(astNode);
        AstVisitor::visit(node);
    };

    void visit(const std::shared_ptr<ElseNode> &node) override {
        std::shared_ptr<AstNode> astNode = std::dynamic_pointer_cast<AstNode>(node);
        test(astNode);
        AstVisitor::visit(node);
    };

    void visit(const std::shared_ptr<EqualExprNode> &node) override {
        std::shared_ptr<AstNode> astNode = std::dynamic_pointer_cast<AstNode>(node);
        test(astNode);
        AstVisitor::visit(node);
    };

    void visit(const std::shared_ptr<ExpoExprNode> &node) override {
        std::shared_ptr<AstNode> astNode = std::dynamic_pointer_cast<AstNode>(node);
        test(astNode);
        AstVisitor::visit(node);
    };

    void visit(const std::shared_ptr<FilterNode> &node) override {
        std::shared_ptr<AstNode> astNode = std::dynamic_pointer_cast<AstNode>(node);
        test(astNode);
        AstVisitor::visit(node);
    };

    void visit(const std::shared_ptr<GreaterEqualExprNode> &node) override {
        std::shared_ptr<AstNode> astNode = std::dynamic_pointer_cast<AstNode>(node);
        test(astNode);
        AstVisitor::visit(node);
    };

    void visit(const std::shared_ptr<GreaterExprNode> &node) override {
        std::shared_ptr<AstNode> astNode = std::dynamic_pointer_cast<AstNode>(node);
        test(astNode);
        AstVisitor::visit(node);
    };

    void visit(const std::shared_ptr<HeaderIndexNode> &node) override {
        std::shared_ptr<AstNode> astNode = std::dynamic_pointer_cast<AstNode>(node);
        test(astNode);
        AstVisitor::visit(node);
    };

    void visit(const std::shared_ptr<IfNode> &node) override {
        std::shared_ptr<AstNode> astNode = std::dynamic_pointer_cast<AstNode>(node);
        test(astNode);
        AstVisitor::visit(node);
    };

    void visit(const std::shared_ptr<IndexNode> &node) override {
        std::shared_ptr<AstNode> astNode = std::dynamic_pointer_cast<AstNode>(node);
        test(astNode);
        AstVisitor::visit(node);
    };

    void visit(const std::shared_ptr<IntersectionExprNode> &node) override {
        std::shared_ptr<AstNode> astNode = std::dynamic_pointer_cast<AstNode>(node);
        test(astNode);
        AstVisitor::visit(node);
    };

    void visit(const std::shared_ptr<LeafNode> &node) override {
        std::shared_ptr<AstNode> astNode = std::dynamic_pointer_cast<AstNode>(node);
        test(astNode);
        AstVisitor::visit(node);
    };

    void visit(const std::shared_ptr<LessEqualExprNode> &node) override {
        std::shared_ptr<AstNode> astNode = std::dynamic_pointer_cast<AstNode>(node);
        test(astNode);
        AstVisitor::visit(node);
    };

    void visit(const std::shared_ptr<LessExprNode> &node) override {
        std::shared_ptr<AstNode> astNode = std::dynamic_pointer_cast<AstNode>(node);
        test(astNode);
        AstVisitor::visit(node);
    };

    void visit(const std::shared_ptr<ListNode> &node) override {
        std::shared_ptr<AstNode> astNode = std::dynamic_pointer_cast<AstNode>(node);
        test(astNode);
        AstVisitor::visit(node);
    };

    void visit(const std::shared_ptr<MinusExprNode> &node) override {
        std::shared_ptr<AstNode> astNode = std::dynamic_pointer_cast<AstNode>(node);
        test(astNode);
        AstVisitor::visit(node);
    };

    void visit(const std::shared_ptr<MinusNode> &node) override {
        std::shared_ptr<AstNode> astNode = std::dynamic_pointer_cast<AstNode>(node);
        test(astNode);
        AstVisitor::visit(node);
    };

    void visit(const std::shared_ptr<ModExprNode> &node) override {
        std::shared_ptr<AstNode> astNode = std::dynamic_pointer_cast<AstNode>(node);
        test(astNode);
        AstVisitor::visit(node);
    };

    void visit(const std::shared_ptr<MultExprNode> &node) override {
        std::shared_ptr<AstNode> astNode = std::dynamic_pointer_cast<AstNode>(node);
        test(astNode);
        AstVisitor::visit(node);
    };

    void visit(const std::shared_ptr<NotEqualExprNode> &node) override {
        std::shared_ptr<AstNode> astNode = std::dynamic_pointer_cast<AstNode>(node);
        test(astNode);
        AstVisitor::visit(node);
    }

    void visit(const std::shared_ptr<NotNode> &node) override {
        std::shared_ptr<AstNode> astNode = std::dynamic_pointer_cast<AstNode>(node);
        test(astNode);
        AstVisitor::visit(node);
    };

    void visit(const std::shared_ptr<OrExprNode> &node) override {
        std::shared_ptr<AstNode> astNode = std::dynamic_pointer_cast<AstNode>(node);
        test(astNode);
        AstVisitor::visit(node);
    };

    void visit(const std::shared_ptr<ParNode> &node) override {
        std::shared_ptr<AstNode> astNode = std::dynamic_pointer_cast<AstNode>(node);
        test(astNode);
        AstVisitor::visit(node);
    };

    void visit(const std::shared_ptr<PlusExprNode> &node) override {
        std::shared_ptr<AstNode> astNode = std::dynamic_pointer_cast<AstNode>(node);
        test(astNode);
        AstVisitor::visit(node);
    };

    void visit(const std::shared_ptr<PlusNode> &node) override {
        std::shared_ptr<AstNode> astNode = std::dynamic_pointer_cast<AstNode>(node);
        test(astNode);
        AstVisitor::visit(node);
    };

    void visit(const std::shared_ptr<ProcCallNode> &node) override {
        std::shared_ptr<AstNode> astNode = std::dynamic_pointer_cast<AstNode>(node);
        test(astNode);
        AstVisitor::visit(node);
    };

    void visit(const std::shared_ptr<ProcDecNode> &node) override {
        std::shared_ptr<AstNode> astNode = std::dynamic_pointer_cast<AstNode>(node);
        test(astNode);
        AstVisitor::visit(node);
    };

    void visit(const std::shared_ptr<ProgNode> &node) override {
        std::shared_ptr<AstNode> astNode = std::dynamic_pointer_cast<AstNode>(node);
        test(astNode);
        AstVisitor::visit(node);
    };

    void visit(const std::shared_ptr<ReturnNode> &node) override {
        std::shared_ptr<AstNode> astNode = std::dynamic_pointer_cast<AstNode>(node);
        test(astNode);
        AstVisitor::visit(node);
    };

    void visit(const std::shared_ptr<TableNode> &node) override {
        std::shared_ptr<AstNode> astNode = std::dynamic_pointer_cast<AstNode>(node);
        test(astNode);
        AstVisitor::visit(node);
    };

    void visit(const std::shared_ptr<UnionExprNode> &node) override {
        std::shared_ptr<AstNode> astNode = std::dynamic_pointer_cast<AstNode>(node);
        test(astNode);
        AstVisitor::visit(node);
    };

    void visit(const std::shared_ptr<WhileNode> &node) override {
        std::shared_ptr<AstNode> astNode = std::dynamic_pointer_cast<AstNode>(node);
        test(astNode);
        AstVisitor::visit(node);
    };

   private:
    dplgrammar::DplParser *parser;
    dplgrammar::DplLexer *lexer;
    std::vector<size_t> expectedTreeNodes;
    size_t index = 0;

    void test(const std::shared_ptr<AstNode> &node) {
        if (index >= expectedTreeNodes.size()) {
            return;
        }
        std::shared_ptr<LeafNode> leafNode = std::dynamic_pointer_cast<LeafNode>(node);
        std::cout << "Expected: " << expectedTreeNodes[index] << " Actual: " << node->getRule()
                  << std::endl;
        REQUIRE(node->getRule() == expectedTreeNodes[index]);
        index++;
    }

    void printRule(const std::shared_ptr<AstNode> &node) {
        std::shared_ptr<LeafNode> leafNode = std::dynamic_pointer_cast<LeafNode>(node);
        std::string enumType;
        std::string name;
        if (leafNode != nullptr) {
            enumType = "DplLexer::";
            name = lexer->getRuleNames()[node->getRule()];
        } else {
            enumType = "DplParser::Rule";
            name = parser->getRuleNames()[node->getRule()];
        }
        name[0] = std::toupper(static_cast<unsigned char>(name[0]));
        std::cout << enumType << name << ",\n";
    }
};

#endif