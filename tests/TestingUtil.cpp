#include <TestingUtil.hpp>

using namespace dplutil;

void TestVisitor::printTokens(int ruleIndex) {
    std::string name = parser->getRuleNames()[ruleIndex];
    name[0] = std::toupper(static_cast<unsigned char>(name[0]));
    std::cout << "DplParser::Rule" << name << ",\n";
}

void TestVisitor::testNode(antlr4::ParserRuleContext *ctx) {
    INFO(std::to_string(ctx->getRuleIndex()) + " != " + std::to_string(expectedTreeNodes[0]) + '\n');
    REQUIRE(static_cast<int>(ctx->getRuleIndex()) == static_cast<int>(expectedTreeNodes[0]));
    expectedTreeNodes.erase(expectedTreeNodes.begin());
}

antlrcpp::Any TestVisitor::visitChildren(antlr4::tree::ParseTree *tree) {
    for (size_t i = 0; i < tree->children.size(); ++i) {
        antlr4::ParserRuleContext* ctx = dynamic_cast<antlr4::ParserRuleContext*>(tree->children[i]);
        if (ctx) {
            testNode(ctx);
        }

        tree->children[i]->accept(this);
    }

    return nullptr;
}


void TestingUtil::testTokens(std::string testFileName, std::vector<size_t> expectedTokenTypes) {
    std::string filePath = std::filesystem::path(std::string{exampleLocation} + testFileName).string();

    if (!std::filesystem::exists(filePath)) {
        FAIL("File does not exist: " + filePath);
    }

    std::ifstream file{filePath};
    if (!file.is_open()) {
        FAIL("Failed to open file: " + filePath);
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

void TestingUtil::testParser(std::string testFileName, std::vector<size_t> expectedTreeNodes) {
    std::string filePath = std::filesystem::path(std::string{exampleLocation} + testFileName).string();

    if (!std::filesystem::exists(filePath)) {
        FAIL("File does not exist: " + filePath);
    }

    std::ifstream file{filePath};
    if (!file.is_open()) {
        FAIL("Failed to open file: " + filePath);
    }

    antlr4::ANTLRInputStream input(file);

    dplgrammar::DplLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);

    tokens.fill();

    dplgrammar::DplParser parser(&tokens);

    TestVisitor visitor(&parser, expectedTreeNodes);
    antlr4::tree::ParseTree* tree = parser.prog();
    visitor.visit(tree);
}

void TestingUtil::testAst(std::string testFileName, std::vector<size_t> expectedTreeNodes) {
    std::string filePath = std::filesystem::path(std::string{exampleLocation} + testFileName).string();

    if (!std::filesystem::exists(filePath)) {
        FAIL("File does not exist: " + filePath);
    }

    std::ifstream file{filePath};
    if (!file.is_open()) {
        FAIL("Failed to open file: " + filePath);
    }

    antlr4::ANTLRInputStream input(file);

    dplgrammar::DplLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);

    tokens.fill();

    dplgrammar::DplParser parser(&tokens);

    dplgrammar::DplParser::ProgContext* tree = parser.prog();

    AstBuilder builder{&parser, &lexer};
    builder.visit(tree);

    std::shared_ptr<AstNode> root = builder.getRoot();

    std::shared_ptr<AstTestVisitor> visitor = std::make_shared<AstTestVisitor>(expectedTreeNodes, &parser, &lexer);

    root->accept(visitor);
}
