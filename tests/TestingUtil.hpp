#ifndef TEST_HPP
#define TEST_HPP

#include <catch2/catch_test_macros.hpp>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <antlr4-runtime.h>
#include <DplLexer.h>
#include <DplParser.h>

#include <DplParserBaseVisitor.h>


#define LEXER_TEST(name) TEST_CASE(name, "[lexer]")
#define PARSER_TEST(name) TEST_CASE(name, "[parser]")


class TestVisitor : public dplgrammar::DplParserBaseVisitor {
public:
    virtual antlrcpp::Any visitProg(dplgrammar::DplParser::ProgContext *node) override {
        std::cout << node->getText() + "\n" << std::endl;
        // Visit the children of the node.
        return visitChildren(node);
    }

    virtual std::any visitStm(dplgrammar::DplParser::StmContext *node) override {
        std::cout << "Stm " + node->getText() + "\n" << std::endl;
        return visitChildren(node);
    }

    virtual std::any visitCtrlstm(dplgrammar::DplParser::CtrlstmContext *node) override {
        std::cout << "Ctrlstm " + node->getText() + "\n" << std::endl;
        return visitChildren(node);
    }

    virtual std::any visitLoopstm(dplgrammar::DplParser::LoopstmContext *node) override {
        std::cout << "Loopstm " + node->getText() + "\n" << std::endl;
        return visitChildren(node);
    }

    virtual std::any visitFlowstm(dplgrammar::DplParser::FlowstmContext *node) override {
        std::cout << "Flowstm " + node->getText() + "\n" << std::endl;
        return visitChildren(node);
    }

    virtual std::any visitAssignstm(dplgrammar::DplParser::AssignstmContext *node) override {
        
        std::cout << "Assignstm " + node->getText() + "\n" << std::endl;
        return visitChildren(node);
    }

    virtual std::any visitExpr(dplgrammar::DplParser::ExprContext *node) override {
        return visitChildren(node);
    }

    virtual std::any visitArthexpr(dplgrammar::DplParser::ArthexprContext *node) override {
        return visitChildren(node);
    }

    virtual std::any visitBoolexpr(dplgrammar::DplParser::BoolexprContext *node) override {
        return visitChildren(node);
    }

    virtual std::any visitUnaryexpr(dplgrammar::DplParser::UnaryexprContext *node) override {
        return visitChildren(node);
    }

    virtual std::any visitTable(dplgrammar::DplParser::TableContext *node) override {
        return visitChildren(node);
    }

    virtual std::any visitTabledec(dplgrammar::DplParser::TabledecContext *node) override {
        return visitChildren(node);
    }

    virtual std::any visitTablecall(dplgrammar::DplParser::TablecallContext *node) override {
        return visitChildren(node);
    }

    virtual std::any visitList(dplgrammar::DplParser::ListContext *node) override {
        return visitChildren(node);
    }

    virtual std::any visitListdec(dplgrammar::DplParser::ListdecContext *node) override {
        return visitChildren(node);
    }

    virtual std::any visitListcall(dplgrammar::DplParser::ListcallContext *node) override {
        return visitChildren(node);
    }

    virtual std::any visitProcdec(dplgrammar::DplParser::ProcdecContext *node) override {
        return visitChildren(node);
    }

    virtual std::any visitProccall(dplgrammar::DplParser::ProccallContext *node) override {
        return visitChildren(node);
    }

    virtual std::any visitArgs(dplgrammar::DplParser::ArgsContext *node) override {
        return visitChildren(node);
    }

    virtual std::any visitParams(dplgrammar::DplParser::ParamsContext *node) override {
        return visitChildren(node);
    }

    virtual std::any visitCompareopr(dplgrammar::DplParser::CompareoprContext *node) override {
        return visitChildren(node);
    }

    virtual std::any visitJunctionopr(dplgrammar::DplParser::JunctionoprContext *node) override {
        return visitChildren(node);
    }

    virtual std::any visitLiteral(dplgrammar::DplParser::LiteralContext *node) override {
        return visitChildren(node);
    }

    // Override other visit methods as needed...
};


namespace util {
    class TestingUtil {
        public:
            static void testTokens(std::string testFileName, std::vector<size_t> expectedTokenTypes) {
                const std::string exampleLocation = "../../docs/examples/";

                std::string filePath = exampleLocation + testFileName;

                if (!std::filesystem::exists(filePath)) {
                    std::cerr << "File does not exist: " << filePath << '\n';
                    exit(EXIT_FAILURE);
                }

                std::ifstream file = std::ifstream(filePath);
                if (!file.is_open()) {
                    std::cerr << "Failed to open file: " << filePath;
                    FAIL();
                }

                antlr4::ANTLRInputStream input(file);

                dplgrammar::DplLexer lexer(&input);
                antlr4::CommonTokenStream tokens(&lexer);

                tokens.fill();

                size_t tokensSize = tokens.size() - 1;
                INFO("Token stream mismatch");

                for (size_t i = 0; i < tokensSize; ++i) {
                    INFO(i);
                    REQUIRE(tokens.get(i)->getType() == expectedTokenTypes[i]);
                }
            }
        public: 
            static void testParser(std::string testFileName, std::vector<int> expectedTreeNodes) {
                const std::string exampleLocation = "../docs/examples/";

                std::string filePath = exampleLocation + testFileName;

                if (!std::filesystem::exists(filePath)) {
                    std::cerr << "File does not exist: " << filePath << '\n';
                    exit(EXIT_FAILURE);
                }

                std::ifstream file = std::ifstream(filePath);
                if (!file.is_open()) {
                    std::cerr << "Failed to open file: " << filePath;
                    FAIL();
                }

                antlr4::ANTLRInputStream input(file);

                dplgrammar::DplLexer lexer(&input);
                antlr4::CommonTokenStream tokens(&lexer);

                tokens.fill();

                dplgrammar::DplParser parser(&tokens);
                antlr4::tree::ParseTree* tree = parser.prog();

                TestVisitor visitor;
                visitor.visit(tree);
            }
    };
}

#endif
