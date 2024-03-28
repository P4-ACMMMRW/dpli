#ifndef ASTVISITOR_HPP
#define ASTVISITOR_HPP

#include <DplParserBaseVisitor.h>

using namespace antlr4;
using namespace dplgrammar;


class AstNode {
public:
    AstNode(AstNode *parent) : parent(parent) {}
    AstNode() {}
    int rule;
    AstNode* parent;
    std::string text;
    std::vector<AstNode*> children;
    

    void print(std::string indent = "", std::string prefix = "") {
        //std::cout << indent << prefix << ruleName << "   (" + text +")" << "\n";
        std::cout << indent << prefix << text << "\n";

        // Use a new level of indentation for the children
        std::string childIndent = indent + (prefix.empty() ? "" : (prefix == "└── " ? "    " : "│   "));

        for (size_t i = 0; i < children.size(); ++i) {
            // For the last child, we want to print a different prefix
            if (i == children.size() - 1) {
                children[i]->print(childIndent, "└── ");
            } else {
                children[i]->print(childIndent, "├── ");
            }
        }
    }
};

class AstVisitor : public DplParserBaseVisitor {
private:
    DplParser* parser; // Add a parser member
    DplLexer* lexer; // Add a lexer member
    AstNode* root;
    AstNode* currentNode;
public:
    AstVisitor(DplParser* parser, DplLexer* lexer) : parser(parser), lexer(lexer),  root(nullptr), currentNode(nullptr) {}
    
    virtual antlrcpp::Any visitProg(DplParser::ProgContext *parseNode) override {

        AstNode* newNode = new AstNode();
        newNode->rule = parseNode->getRuleIndex();
        newNode->text = parser->getRuleNames()[newNode->rule];

        root = newNode;
        currentNode = newNode;

        return visitChildren(parseNode);
    }

    virtual antlrcpp::Any visitAssignstm(DplParser::AssignstmContext *parseNode) override {
        AstNode* newNode = new AstNode(currentNode);
        newNode->rule = parseNode->getRuleIndex();
        newNode->text = parseNode->children[1]->getText();

        currentNode->children.push_back(newNode);
        AstNode* oldNode = currentNode;
        currentNode = newNode;

        AstNode* leftNode = getTerminalLeafNode(parseNode->children[0]);
        AstNode* rightNode = getTerminalLeafNode(parseNode->children[2]);

        if (leftNode != nullptr)  currentNode->children.push_back(leftNode);
        if (rightNode != nullptr) currentNode->children.push_back(rightNode);

        visitChildren(parseNode);

        currentNode = oldNode;

        return nullptr;
    }

    virtual antlrcpp::Any visitLoopstm(DplParser::LoopstmContext *parseNode) override {
        AstNode* newNode = new AstNode(currentNode);
        newNode->rule = parseNode->getRuleIndex();
        newNode->text = parseNode->children[0]->getText();

        currentNode->children.push_back(newNode);
        AstNode* oldNode = currentNode;
        currentNode = newNode;

        AstNode* condNode = getTerminalLeafNode(parseNode->children[1]);
        AstNode* stmNode = getTerminalLeafNode(parseNode->children[3]);

        if (condNode != nullptr)  currentNode->children.push_back(condNode);
        if (stmNode != nullptr) currentNode->children.push_back(stmNode);

        visitChildren(parseNode);

        currentNode = oldNode;

        return nullptr;
    }

    virtual antlrcpp::Any visitCtrlstm(DplParser::CtrlstmContext *parseNode) override {
        AstNode* newNode = new AstNode(currentNode);
        newNode->rule = parseNode->getRuleIndex();
        newNode->text = parseNode->children[0]->getText();

        currentNode->children.push_back(newNode);
        AstNode* oldNode = currentNode;
        currentNode = newNode;

        AstNode* condNode = getTerminalLeafNode(parseNode->children[1]);
        AstNode* stmNode = getTerminalLeafNode(parseNode->children[3]);

        if (condNode != nullptr)  currentNode->children.push_back(condNode);
        if (stmNode != nullptr) currentNode->children.push_back(stmNode);

        visitChildren(parseNode);

        currentNode = oldNode;

        return nullptr;
    }

    virtual antlrcpp::Any visitExpr(DplParser::ExprContext *parseNode) override {
        if (parseNode->boolexpr() == nullptr && parseNode->arthexpr() == nullptr) return visitChildren(parseNode);

        if (parseNode->arthexpr() != nullptr) {
            std::cout << "is arth" << "\n";

        }

        AstNode *newNode = new AstNode(currentNode);
        antlr4::ParserRuleContext *childParseNode = dynamic_cast<antlr4::ParserRuleContext*>(parseNode->children[1]); 
        newNode->rule = childParseNode->getRuleIndex(); 
        newNode->text = childParseNode->children[0]->getText();
        currentNode->children.push_back(newNode);

        AstNode* oldNode = currentNode;
        currentNode = newNode;

        AstNode* leftNode = getTerminalLeafNode(parseNode->children[0]);       // this is child of the expr
        if (leftNode != nullptr) currentNode->children.push_back(leftNode);

        visitChildren(parseNode);

        AstNode* rightNode = getTerminalLeafNode(childParseNode->children[1]); // keep in mind this is for the boolexpr
        if (rightNode != nullptr) currentNode->children.push_back(rightNode);

        currentNode = oldNode;

        return nullptr;
    }

    virtual antlrcpp::Any visitFlowstm(DplParser::FlowstmContext *parseNode) override {
        AstNode* newNode = new AstNode(currentNode);
        newNode->rule = parseNode->getRuleIndex();
        newNode->text = parseNode->children[0]->getText();

        currentNode->children.push_back(newNode);
        AstNode* oldNode = currentNode;
        currentNode = newNode;

        if (parseNode->children.size() == 2) {
            AstNode* condNode = getTerminalLeafNode(parseNode->children[1]);
            if (condNode != nullptr)  currentNode->children.push_back(condNode);
        }

        visitChildren(parseNode);

        currentNode = oldNode;

        return nullptr;
    }

    virtual antlrcpp::Any visitProccall(DplParser::ProccallContext *parseNode) override {
        AstNode* newNode = new AstNode(currentNode);
        newNode->rule = parseNode->getRuleIndex();
        newNode->text = parseNode->children[0]->getText();
        

        currentNode->children.push_back(newNode);
        AstNode* oldNode = currentNode;
        currentNode = newNode;

        for (size_t i = 2; i < parseNode->children.size() - 1; i++) {
            AstNode* childNode = getTerminalLeafNode(parseNode->children[i]);
            if (childNode != nullptr) currentNode->children.push_back(childNode);
        }

        visitChildren(parseNode);

        currentNode = oldNode;

        return nullptr;
    }

    AstNode* getTerminalLeafNode(tree::ParseTree* childParseNode) {
        while (childParseNode->children.size() == 1) {
            childParseNode = childParseNode->children[0];
        }
        if (childParseNode->children.size() > 1) return nullptr;

        tree::TerminalNode* parseLeafNode = dynamic_cast<antlr4::tree::TerminalNode*>(childParseNode);

        AstNode* leafNode = new AstNode();
        leafNode->rule = parseLeafNode->getSymbol()->getType();
        leafNode->text = parseLeafNode->getText();
        return leafNode;
    }

    // what if  1 -> 2
    tree::ParseTree* getTerminalNode(tree::ParseTree* parseNode) {
        tree::ParseTree* newParseNode = parseNode;
        while (newParseNode->children.size() == 1) {
            newParseNode = newParseNode->children[0];
        }
        if (newParseNode->children.size() > 1) return parseNode;
        
        return newParseNode;
    }

    AstNode* getRoot() {
        return root;
    }
};

#endif