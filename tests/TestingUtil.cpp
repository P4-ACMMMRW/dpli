#include "TestingUtil.hpp"

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

void TestingUtil::testEval(std::string testFileName, 
                           std::vector<std::pair<std::string, dplsrc::Value>> expectedVarVec,
                           std::vector<std::string> expectedOutputLines) {

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

    std::shared_ptr<AstNode> root;
    try {
        root = builder.getRoot();
    } catch (const dplsrc::DplException &e) {
        std::cerr << e.what() << '\n';
    }

    std::shared_ptr<dplsrc::Evaluator> evaluator;

    try {
        std::freopen("../../testOutput.txt", "w", stdout);
        evaluator = std::make_shared<dplsrc::Evaluator>();
        root->accept(evaluator);
        std::fclose(stdout);
    } catch (const dplsrc::DplException &e) {
        std::fclose(stdout);
        std::cerr << e.what() << '\n';
        FAIL("Evaluator failed to evaluate");
    }

    dplsrc::VariableTable varTable = evaluator->getVtable();
    size_t expectedVarSize = expectedVarVec.size();

    if (expectedVarSize != varTable.size()) {
        FAIL("Variable table doesn't have the correct amount of variables");
    }

    for (size_t i = 0; i < expectedVarSize; ++i) {
        dplsrc::Variable* acutalVariable = varTable.lookup(expectedVarVec[i].first);

        dplsrc::Value actualValue = acutalVariable->getVal(); 
        dplsrc::Value expectedVal  = expectedVarVec[i].second;

        if (actualValue != expectedVal) {
            FAIL("Variable " + acutalVariable->getId() + 
                 " is of type: "  + actualValue.toTypeString() + 
                 " and value:          " + actualValue.toString() + 

                 "\nNot the expected type: " + expectedVal.toTypeString() + 
                 " and expected value: " + expectedVal.toString());
        }
    }

    std::ifstream printFile("../../testOutput.txt");
    std::string line;
    std::vector<std::string> lines;

    while (std::getline(printFile, line)) {
        lines.push_back(line);
    }

    printFile.close();
    std::remove("../../testOutput.txt");

    if (lines.size() != expectedOutputLines.size()) {
        FAIL("Printed output doesn't have the correct amount of lines");
        for (std::string l : lines) {
            std::cout << l << '\n';
        }
    }

    for (size_t i = 0; i < lines.size(); ++i) {
        if (lines[i] != expectedOutputLines[i]) {
            FAIL("Printed output " + lines[i] + "doesn't match expected output" + expectedOutputLines[i]);
        }
    }

}

void TestingUtil::testEvalException(std::string testFileName) {

    std::string filePath = std::filesystem::path(std::string{exceptionExampleLocation} + testFileName).string();

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

    std::shared_ptr<AstNode> root;
    try {
        root = builder.getRoot();
    } catch (const dplsrc::DplException &e) {
        std::cerr << e.what() << '\n';
    }

    std::shared_ptr<dplsrc::Evaluator> evaluator;

    try {
        evaluator = std::make_shared<dplsrc::Evaluator>();
        REQUIRE_THROWS_AS(root->accept(evaluator), dplsrc::RuntimeException);
    } catch (const dplsrc::DplException &e) {
        std::cerr << e.what() << '\n';
        FAIL("Evaluator failed to evaluate");
    }
}
