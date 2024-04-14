#include <DplParserBaseVisitor.h>

#include <IfNode.hpp>

void IfNode::addChild(std::shared_ptr<AstNode> node) {
    if (condNode == nullptr) {
        condNode = std::move(node);
    } else if (node->getRule() == dplgrammar::DplParser::RuleElsestm) {
        elseNode = std::move(node);
    } else {
        bodyNodes.push_back(std::move(node));
    }
}

void IfNode::print(std::string indent = "", std::string prefix = "") {
    std::cout << indent << prefix << AstNode::getText() << "\n";

    // Use a new level of indentation for the children
    std::string childIndent = indent + (prefix.empty() ? "" : (prefix == "└── " ? "    " : "│   "));

    // Print the condition node, if it exists
    if (condNode != nullptr) {
        condNode->print(childIndent, "├── Condition: ");
    }

    // Print each if statement node
    for (size_t i = 0; i < bodyNodes.size(); ++i) {
        // For the last if statement node, we want to print a different prefix
        std::string bodyPrefix =
            (i == bodyNodes.size() - 1 && elseNode == nullptr) ? "└── " : "├── ";
        bodyNodes[i]->print(childIndent, bodyPrefix);
    }

    // Print the else node, if it exists
    if (elseNode != nullptr) {
        elseNode->print(childIndent, "└── ");
    }
}
void IfNode::accept(std::shared_ptr<AstVisitor> visitor) { visitor->visit(std::static_pointer_cast<IfNode>(shared_from_this())); };