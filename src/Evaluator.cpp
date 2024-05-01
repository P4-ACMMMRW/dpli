#include "Evaluator.hpp"

#include <cmath>
#include <string>

using namespace dplsrc;

void Evaluator::visit(const std::shared_ptr<AndExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    if (leftNode->getType() != Type::BOOL || rightNode->getType() != Type::BOOL) {
        // TODO: move to error handler at some point
        throw std::runtime_error("Cannot compare the used types");
    }

    // Evaluates the value of the expression
    switch (leftNode->getType()) {
        case Type::BOOL:
            if (leftNode->getVal().get<bool>() == 1 && rightNode->getVal().get<bool>() == 1)
                node->setVal(1);
            else
                node->setVal(0);
            break;
        default:
            throw std::runtime_error("Error: Couldn't convert string to value of nodes");
            break;
    }

    // Always sets the type to bool for comparisons
    node->setType(Type::BOOL);

    // Binds to the vtable
    vtable.bind(Variable(node->getText(), node->getVal(), node->getType()));
}

void Evaluator::visit(const std::shared_ptr<AssignNode> &node) {
    // Assume left node is a leaf node
    std::shared_ptr<LeafNode> leftNode = std::dynamic_pointer_cast<LeafNode>(node->getLeftNode());

    if (!leftNode->getIsIdentifier()) {
        // TODO: move to error handler at some point
        throw std::runtime_error("Error: left side of assignment must be an identifier\n");
    }

    // Compute type of right node
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    vtable.bind(Variable(leftNode->getText(), rightNode->getVal(), rightNode->getType()));
}

void Evaluator::visit(const std::shared_ptr<ColumnNode> &node) {}

void Evaluator::visit(const std::shared_ptr<DivExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    if (leftNode->getType() != rightNode->getType() ||
        !((leftNode->getType() == Type::FLOAT || leftNode->getType() == Type::INT ||
           leftNode->getType() == Type::BOOL) &&
          (rightNode->getType() == Type::FLOAT || rightNode->getType() == Type::INT ||
           rightNode->getType() == Type::BOOL)) ||
        leftNode->getType() == Type::TABLE || rightNode->getType() == Type::TABLE ||
        leftNode->getType() == Type::NONETYPE || rightNode->getType() == Type::NONETYPE ||
        leftNode->getType() == Type::STR || rightNode->getType() == Type::STR) {
        // TODO: move to error handler at some point
        throw std::runtime_error("Cannot divide with the types");
    }

    // Divide with 0 check
    if (rightNode->getType() == Type::INT)
        if (rightNode->getVal().get<int>() == 0)
            throw std::runtime_error("Cannot divide with 0");
        else if (rightNode->getType() == Type::FLOAT)
            if (rightNode->getVal().get<double>() == 0)
                throw std::runtime_error("Cannot divide with 0");
            else if (rightNode->getVal().get<bool>() == 0)
                throw std::runtime_error("Cannot divide with 0");

    // Evaluates the value of the expression
    switch (leftNode->getType()) {
        case Type::INT:
            if (rightNode->getType() == Type::BOOL) {
                node->setVal(leftNode->getVal().get<int>() / rightNode->getVal().get<bool>());
            } else if (rightNode->getType() == Type::INT) {
                node->setVal(leftNode->getVal().get<int>() / rightNode->getVal().get<int>());
            } else {
                node->setVal(leftNode->getVal().get<int>() / rightNode->getVal().get<double>());
            }
            break;
        case Type::FLOAT:
            if (rightNode->getType() == Type::BOOL) {
                node->setVal(leftNode->getVal().get<double>() / rightNode->getVal().get<bool>());
            } else if (rightNode->getType() == Type::INT) {
                node->setVal(leftNode->getVal().get<double>() / rightNode->getVal().get<int>());
            } else {
                node->setVal(leftNode->getVal().get<double>() / rightNode->getVal().get<double>());
            }
            break;
        case Type::BOOL:
            if (rightNode->getType() == Type::BOOL) {
                node->setVal(leftNode->getVal().get<bool>() / rightNode->getVal().get<bool>());
            } else if (rightNode->getType() == Type::INT) {
                node->setVal(leftNode->getVal().get<bool>() / rightNode->getVal().get<int>());
            } else {
                node->setVal(leftNode->getVal().get<bool>() / rightNode->getVal().get<double>());
            }
            break;
        default:
            throw std::runtime_error("Error: Couldn't convert string to value of nodes");
            break;
    }

    // Always sets type to float fo division
    node->setType(Type::FLOAT);

    // Binds to the vtable
    vtable.bind(Variable(node->getText(), node->getVal(), node->getType()));
}

void Evaluator::visit(const std::shared_ptr<ElseNode> &node) {}

void Evaluator::visit(const std::shared_ptr<EqualExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    if (leftNode->getType() != rightNode->getType() ||
        !((leftNode->getType() == Type::FLOAT || leftNode->getType() == Type::INT ||
           leftNode->getType() == Type::BOOL) &&
          (rightNode->getType() == Type::FLOAT || rightNode->getType() == Type::INT ||
           rightNode->getType() == Type::BOOL)) ||
        leftNode->getType() == Type::TABLE || rightNode->getType() == Type::TABLE ||
        leftNode->getType() == Type::NONETYPE || rightNode->getType() == Type::NONETYPE) {
        // TODO: move to error handler at some point
        throw std::runtime_error("Cannot compare the used types");
    }

    // Evaluates the value of the expression
    switch (leftNode->getType()) {
        case Type::INT:
            if (rightNode->getType() == Type::BOOL) {
                node->setVal(leftNode->getVal().get<int>() == rightNode->getVal().get<bool>());
            } else if (rightNode->getType() == Type::INT) {
                node->setVal(leftNode->getVal().get<int>() == rightNode->getVal().get<int>());
            } else {
                node->setVal(leftNode->getVal().get<int>() == rightNode->getVal().get<double>());
            }
            break;
        case Type::FLOAT:
            node->setType(Type::FLOAT);
            if (rightNode->getType() == Type::BOOL) {
                node->setVal(leftNode->getVal().get<double>() == rightNode->getVal().get<bool>());
            } else if (rightNode->getType() == Type::INT) {
                node->setVal(leftNode->getVal().get<double>() == rightNode->getVal().get<int>());
            } else {
                node->setVal(leftNode->getVal().get<double>() == rightNode->getVal().get<double>());
            }
            break;
        case Type::BOOL:
            if (rightNode->getType() == Type::BOOL) {
                node->setVal(leftNode->getVal().get<bool>() == rightNode->getVal().get<bool>());
            } else if (rightNode->getType() == Type::INT) {
                node->setVal(leftNode->getVal().get<bool>() == rightNode->getVal().get<int>());
            } else {
                node->setVal(leftNode->getVal().get<bool>() == rightNode->getVal().get<double>());
            }
            break;
        case Type::STR:
            node->setVal(leftNode->getVal().get<std::string>() ==
                         rightNode->getVal().get<std::string>());
            break;
        default:
            throw std::runtime_error("Error: Couldn't convert string to value of nodes");
            break;
    }

    // Always sets the type to bool for comparisons
    node->setType(Type::BOOL);

    // Binds to the vtable
    vtable.bind(Variable(node->getText(), node->getVal(), node->getType()));
}

void Evaluator::visit(const std::shared_ptr<ExpoExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    if (leftNode->getType() != rightNode->getType() ||
        !((leftNode->getType() == Type::FLOAT || leftNode->getType() == Type::INT ||
           leftNode->getType() == Type::BOOL) &&
          (rightNode->getType() == Type::FLOAT || rightNode->getType() == Type::INT ||
           rightNode->getType() == Type::BOOL)) ||
        leftNode->getType() == Type::TABLE || rightNode->getType() == Type::TABLE ||
        leftNode->getType() == Type::NONETYPE || rightNode->getType() == Type::NONETYPE ||
        leftNode->getType() == Type::STR || rightNode->getType() == Type::STR) {
        // TODO: move to error handler at some point
        throw std::runtime_error("Cannot multiply with the used types");
    }

    // Evaluates the value of the expression
    // TODO: Support string mutliplication e.g. "Hello" * 3 = "HelloHelloHello"
    switch (leftNode->getType()) {
        case Type::INT:
            if (rightNode->getType() == Type::BOOL) {
                node->setVal(pow(leftNode->getVal().get<int>(), rightNode->getVal().get<bool>()));
                node->setType(Type::INT);
            } else if (rightNode->getType() == Type::INT) {
                node->setVal(pow(leftNode->getVal().get<int>(), rightNode->getVal().get<int>()));
                node->setType(Type::INT);
            } else {
                node->setVal(pow(leftNode->getVal().get<int>(), rightNode->getVal().get<double>()));
                node->setType(Type::FLOAT);
            }
            break;
        case Type::FLOAT:
            node->setType(Type::FLOAT);
            if (rightNode->getType() == Type::BOOL) {
                node->setVal(
                    pow(leftNode->getVal().get<double>(), rightNode->getVal().get<bool>()));
            } else if (rightNode->getType() == Type::INT) {
                node->setVal(pow(leftNode->getVal().get<double>(), rightNode->getVal().get<int>()));
            } else {
                node->setVal(
                    pow(leftNode->getVal().get<double>(), rightNode->getVal().get<double>()));
            }
            break;
        case Type::BOOL:
            if (rightNode->getType() == Type::BOOL) {
                node->setVal(pow(leftNode->getVal().get<bool>(), rightNode->getVal().get<bool>()));
                node->setType(Type::INT);
            } else if (rightNode->getType() == Type::INT) {
                node->setVal(pow(leftNode->getVal().get<bool>(), rightNode->getVal().get<int>()));
                node->setType(Type::INT);
            } else {
                node->setVal(
                    pow(leftNode->getVal().get<bool>(), rightNode->getVal().get<double>()));
                node->setType(Type::FLOAT);
            }
            break;
        default:
            throw std::runtime_error("Error: Couldn't convert string to value of nodes");
            break;
    }

    // Binds to the vtable
    vtable.bind(Variable(node->getText(), node->getVal(), node->getType()));
}

void Evaluator::visit(const std::shared_ptr<FilterNode> &node) {}

void Evaluator::visit(const std::shared_ptr<GreaterEqualExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    if (leftNode->getType() != rightNode->getType() ||
        !((leftNode->getType() == Type::FLOAT || leftNode->getType() == Type::INT ||
           leftNode->getType() == Type::BOOL) &&
          (rightNode->getType() == Type::FLOAT || rightNode->getType() == Type::INT ||
           rightNode->getType() == Type::BOOL)) ||
        leftNode->getType() == Type::TABLE || rightNode->getType() == Type::TABLE ||
        leftNode->getType() == Type::NONETYPE || rightNode->getType() == Type::NONETYPE ||
        leftNode->getType() == Type::STR || rightNode->getType() == Type::STR) {
        // TODO: move to error handler at some point
        throw std::runtime_error("Cannot compare the used types");
    }

    // Evaluates the value of the expression
    switch (leftNode->getType()) {
        case Type::INT:
            if (rightNode->getType() == Type::BOOL) {
                node->setVal(leftNode->getVal().get<int>() >= rightNode->getVal().get<bool>());
            } else if (rightNode->getType() == Type::INT) {
                node->setVal(leftNode->getVal().get<int>() >= rightNode->getVal().get<int>());
            } else {
                node->setVal(leftNode->getVal().get<int>() >= rightNode->getVal().get<double>());
            }
            break;
        case Type::FLOAT:
            node->setType(Type::FLOAT);
            if (rightNode->getType() == Type::BOOL) {
                node->setVal(leftNode->getVal().get<double>() >= rightNode->getVal().get<bool>());
            } else if (rightNode->getType() == Type::INT) {
                node->setVal(leftNode->getVal().get<double>() >= rightNode->getVal().get<int>());
            } else {
                node->setVal(leftNode->getVal().get<double>() >= rightNode->getVal().get<double>());
            }
            break;
        case Type::BOOL:
            if (rightNode->getType() == Type::BOOL) {
                node->setVal(leftNode->getVal().get<bool>() >= rightNode->getVal().get<bool>());
            } else if (rightNode->getType() == Type::INT) {
                node->setVal(leftNode->getVal().get<bool>() >= rightNode->getVal().get<int>());
            } else {
                node->setVal(leftNode->getVal().get<bool>() >= rightNode->getVal().get<double>());
            }
            break;
        default:
            throw std::runtime_error("Error: Couldn't convert string to value of nodes");
            break;
    }

    // Always sets the type to bool for comparisons
    node->setType(Type::BOOL);

    // Binds to the vtable
    vtable.bind(Variable(node->getText(), node->getVal(), node->getType()));
}

void Evaluator::visit(const std::shared_ptr<GreaterExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    if (leftNode->getType() != rightNode->getType() ||
        !((leftNode->getType() == Type::FLOAT || leftNode->getType() == Type::INT ||
           leftNode->getType() == Type::BOOL) &&
          (rightNode->getType() == Type::FLOAT || rightNode->getType() == Type::INT ||
           rightNode->getType() == Type::BOOL)) ||
        leftNode->getType() == Type::TABLE || rightNode->getType() == Type::TABLE ||
        leftNode->getType() == Type::NONETYPE || rightNode->getType() == Type::NONETYPE ||
        leftNode->getType() == Type::STR || rightNode->getType() == Type::STR) {
        // TODO: move to error handler at some point
        throw std::runtime_error("Cannot compare the used types");
    }

    // Evaluates the value of the expression
    switch (leftNode->getType()) {
        case Type::INT:
            if (rightNode->getType() == Type::BOOL) {
                node->setVal(leftNode->getVal().get<int>() > rightNode->getVal().get<bool>());
            } else if (rightNode->getType() == Type::INT) {
                node->setVal(leftNode->getVal().get<int>() > rightNode->getVal().get<int>());
            } else {
                node->setVal(leftNode->getVal().get<int>() > rightNode->getVal().get<double>());
            }
            break;
        case Type::FLOAT:
            node->setType(Type::FLOAT);
            if (rightNode->getType() == Type::BOOL) {
                node->setVal(leftNode->getVal().get<double>() > rightNode->getVal().get<bool>());
            } else if (rightNode->getType() == Type::INT) {
                node->setVal(leftNode->getVal().get<double>() > rightNode->getVal().get<int>());
            } else {
                node->setVal(leftNode->getVal().get<double>() > rightNode->getVal().get<double>());
            }
            break;
        case Type::BOOL:
            if (rightNode->getType() == Type::BOOL) {
                node->setVal(leftNode->getVal().get<bool>() > rightNode->getVal().get<bool>());
            } else if (rightNode->getType() == Type::INT) {
                node->setVal(leftNode->getVal().get<bool>() > rightNode->getVal().get<int>());
            } else {
                node->setVal(leftNode->getVal().get<bool>() > rightNode->getVal().get<double>());
            }
            break;
        default:
            throw std::runtime_error("Error: Couldn't convert string to value of nodes");
            break;
    }

    // Always sets the type to bool for comparisons
    node->setType(Type::BOOL);

    // Binds to the vtable
    vtable.bind(Variable(node->getText(), node->getVal(), node->getType()));
}

void Evaluator::visit(const std::shared_ptr<HeaderIndexNode> &node) {}

void Evaluator::visit(const std::shared_ptr<IfNode> &node) {}

void Evaluator::visit(const std::shared_ptr<IndexNode> &node) {
    std::shared_ptr<AstNode> identifierNode = node->getRightNode();
    std::shared_ptr<AstNode> indexNode = node->getLeftNode();

    identifierNode->accept(shared_from_this());
    indexNode->accept(shared_from_this());

    size_t index = indexNode->getVal().get<int>();
    switch (identifierNode->getType()) {
        case Type::STR: {
            std::string str = identifierNode->getVal().get<std::string>();
            node->setType(Type::STR);

            if (index < 0 || index >= str.size()) {
                throw std::runtime_error("Error: index out of range\n");
            }

            node->setVal(std::string{str[index]});
            break;
        }
        case Type::LIST: {
            Value::List list = identifierNode->getVal().get<Value::List>();
            // TODO: set element of individual types here

            if (index < 0 || index >= list.size()) {
                throw std::runtime_error("Error: index out of range\n");
            }

            node->setVal(list[index]);
            break;
        }
        default:
            throw std::runtime_error("Error: invalid index operation\n");
            break;
    }
}

void Evaluator::visit(const std::shared_ptr<LeafNode> &node) {
    if (node->getIsIdentifier()) {
        try {
            Variable *var = vtable.lookup(node->getText());
            node->setType(var->getType());
            node->setVal(var->getVal());
        } catch (const std::out_of_range &e) {
            throw std::runtime_error("Error: undefined variable \"" + node->getText() + "\"\n");
        }
    } else if (!node->getIsIdentifier()) {
        if (node->getType() == Type::STR) {
            // If string we have to remove quotes from value
            std::string text = node->getText();
            node->setVal(text.substr(1, text.size() - 2));
        } else {
            switch (node->getType()) {
                case Type::INT:
                    node->setVal(std::stoi(node->getText()));
                    break;
                case Type::FLOAT:
                    node->setVal(std::stod(node->getText()));
                    break;
                case Type::BOOL:
                    node->setVal(node->getText() == "True");
                    break;
                default:
                    node->setVal(node->getText());
            }
        }
    }

    if (node->getType() == Type::NONETYPE) {
        node->setVal(nullptr);
    }
}

void Evaluator::visit(const std::shared_ptr<LessEqualExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    if (leftNode->getType() != rightNode->getType() ||
        !((leftNode->getType() == Type::FLOAT || leftNode->getType() == Type::INT ||
           leftNode->getType() == Type::BOOL) &&
          (rightNode->getType() == Type::FLOAT || rightNode->getType() == Type::INT ||
           rightNode->getType() == Type::BOOL)) ||
        leftNode->getType() == Type::TABLE || rightNode->getType() == Type::TABLE ||
        leftNode->getType() == Type::NONETYPE || rightNode->getType() == Type::NONETYPE ||
        leftNode->getType() == Type::STR || rightNode->getType() == Type::STR) {
        // TODO: move to error handler at some point
        throw std::runtime_error("Cannot compare the used types");
    }

    // Evaluates the value of the expression
    switch (leftNode->getType()) {
        case Type::INT:
            if (rightNode->getType() == Type::BOOL) {
                node->setVal(leftNode->getVal().get<int>() <= rightNode->getVal().get<bool>());
            } else if (rightNode->getType() == Type::INT) {
                node->setVal(leftNode->getVal().get<int>() <= rightNode->getVal().get<int>());
            } else {
                node->setVal(leftNode->getVal().get<int>() <= rightNode->getVal().get<double>());
            }
            break;
        case Type::FLOAT:
            node->setType(Type::FLOAT);
            if (rightNode->getType() == Type::BOOL) {
                node->setVal(leftNode->getVal().get<double>() <= rightNode->getVal().get<bool>());
            } else if (rightNode->getType() == Type::INT) {
                node->setVal(leftNode->getVal().get<double>() <= rightNode->getVal().get<int>());
            } else {
                node->setVal(leftNode->getVal().get<double>() <= rightNode->getVal().get<double>());
            }
            break;
        case Type::BOOL:
            if (rightNode->getType() == Type::BOOL) {
                node->setVal(leftNode->getVal().get<bool>() <= rightNode->getVal().get<bool>());
            } else if (rightNode->getType() == Type::INT) {
                node->setVal(leftNode->getVal().get<bool>() <= rightNode->getVal().get<int>());
            } else {
                node->setVal(leftNode->getVal().get<bool>() <= rightNode->getVal().get<double>());
            }
            break;
        default:
            throw std::runtime_error("Error: Couldn't convert string to value of nodes");
            break;
    }

    // Always sets the type to bool for comparisons
    node->setType(Type::BOOL);

    // Binds to the vtable
    vtable.bind(Variable(node->getText(), node->getVal(), node->getType()));
}

void Evaluator::visit(const std::shared_ptr<LessExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    if (leftNode->getType() != rightNode->getType() ||
        !((leftNode->getType() == Type::FLOAT || leftNode->getType() == Type::INT ||
           leftNode->getType() == Type::BOOL) &&
          (rightNode->getType() == Type::FLOAT || rightNode->getType() == Type::INT ||
           rightNode->getType() == Type::BOOL)) ||
        leftNode->getType() == Type::TABLE || rightNode->getType() == Type::TABLE ||
        leftNode->getType() == Type::NONETYPE || rightNode->getType() == Type::NONETYPE ||
        leftNode->getType() == Type::STR || rightNode->getType() == Type::STR) {
        // TODO: move to error handler at some point
        throw std::runtime_error("Cannot compare the used types");
    }

    // Evaluates the value of the expression
    switch (leftNode->getType()) {
        case Type::INT:
            if (rightNode->getType() == Type::BOOL) {
                node->setVal(leftNode->getVal().get<int>() < rightNode->getVal().get<bool>());
            } else if (rightNode->getType() == Type::INT) {
                node->setVal(leftNode->getVal().get<int>() < rightNode->getVal().get<int>());
            } else {
                node->setVal(leftNode->getVal().get<int>() < rightNode->getVal().get<double>());
            }
            break;
        case Type::FLOAT:
            node->setType(Type::FLOAT);
            if (rightNode->getType() == Type::BOOL) {
                node->setVal(leftNode->getVal().get<double>() < rightNode->getVal().get<bool>());
            } else if (rightNode->getType() == Type::INT) {
                node->setVal(leftNode->getVal().get<double>() < rightNode->getVal().get<int>());
            } else {
                node->setVal(leftNode->getVal().get<double>() < rightNode->getVal().get<double>());
            }
            break;
        case Type::BOOL:
            if (rightNode->getType() == Type::BOOL) {
                node->setVal(leftNode->getVal().get<bool>() < rightNode->getVal().get<bool>());
            } else if (rightNode->getType() == Type::INT) {
                node->setVal(leftNode->getVal().get<bool>() < rightNode->getVal().get<int>());
            } else {
                node->setVal(leftNode->getVal().get<bool>() < rightNode->getVal().get<double>());
            }
            break;
        default:
            throw std::runtime_error("Error: Couldn't convert string to value of nodes");
            break;
    }

    // Always sets the type to bool for comparisons
    node->setType(Type::BOOL);

    // Binds to the vtable
    vtable.bind(Variable(node->getText(), node->getVal(), node->getType()));
}

void Evaluator::visit(const std::shared_ptr<ListNode> &node) {
    std::vector<std::shared_ptr<AstNode>> childNodes = node->getChildNodeList();
    std::vector<Value> values;
    std::vector<Type> types;
    for (size_t i = 0; i < childNodes.size(); ++i) {
        childNodes[i]->accept(shared_from_this());
        values.emplace_back(childNodes[i]->getVal());
        types.emplace_back(childNodes[i]->getType());
    }

    node->setType(Type::LIST);
    node->setTypes(types);
    node->setVal(values);
}

void Evaluator::visit(const std::shared_ptr<MinusExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    if (leftNode->getType() != rightNode->getType() ||
        !((leftNode->getType() == Type::FLOAT || leftNode->getType() == Type::INT ||
           leftNode->getType() == Type::BOOL) &&
          (rightNode->getType() == Type::FLOAT || rightNode->getType() == Type::INT ||
           rightNode->getType() == Type::BOOL)) ||
        leftNode->getType() == Type::TABLE || rightNode->getType() == Type::TABLE ||
        leftNode->getType() == Type::NONETYPE || rightNode->getType() == Type::NONETYPE ||
        leftNode->getType() == Type::STR || rightNode->getType() == Type::STR) {
        // TODO: move to error handler at some point
        throw std::runtime_error("Cannot do substraction with the used types");
    }

    // Evaluates the value of the expression
    switch (leftNode->getType()) {
        case Type::INT:
            if (rightNode->getType() == Type::BOOL) {
                node->setVal(leftNode->getVal().get<int>() - rightNode->getVal().get<bool>());
                node->setType(Type::INT);
            } else if (rightNode->getType() == Type::INT) {
                node->setVal(leftNode->getVal().get<int>() - rightNode->getVal().get<int>());
                node->setType(Type::INT);
            } else {
                node->setVal(leftNode->getVal().get<int>() - rightNode->getVal().get<double>());
                node->setType(Type::FLOAT);
            }
            break;
        case Type::FLOAT:
            node->setType(Type::FLOAT);
            if (rightNode->getType() == Type::BOOL) {
                node->setVal(leftNode->getVal().get<double>() - rightNode->getVal().get<bool>());
            } else if (rightNode->getType() == Type::INT) {
                node->setVal(leftNode->getVal().get<double>() - rightNode->getVal().get<int>());
            } else {
                node->setVal(leftNode->getVal().get<double>() - rightNode->getVal().get<double>());
            }
            break;
        case Type::BOOL:
            if (rightNode->getType() == Type::BOOL) {
                node->setVal(leftNode->getVal().get<bool>() - rightNode->getVal().get<bool>());
                node->setType(Type::INT);
            } else if (rightNode->getType() == Type::INT) {
                node->setVal(leftNode->getVal().get<bool>() - rightNode->getVal().get<int>());
                node->setType(Type::INT);
            } else {
                node->setVal(leftNode->getVal().get<bool>() - rightNode->getVal().get<double>());
                node->setType(Type::FLOAT);
            }
            break;
        default:
            throw std::runtime_error("Error: Couldn't convert string to value of nodes");
            break;
    }

    // Binds to the vtable
    vtable.bind(Variable(node->getText(), node->getVal(), node->getType()));
}

void Evaluator::visit(const std::shared_ptr<MinusNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> childNode = node->getChildNode();
    childNode->accept(shared_from_this());

    if (childNode->getType() == Type::STR || childNode->getType() == Type::LIST ||
        childNode->getType() == Type::NONETYPE || childNode->getType() == Type::TABLE) {
        // TODO: move to error handler at some point
        throw std::runtime_error("Cannot do substraction with the used type");
    }

    // Evaluates the value of the expression
    switch (childNode->getType()) {
        case Type::INT:
            node->setVal(-childNode->getVal().get<int>());
            node->setType(Type::INT);
            break;
        case Type::FLOAT:
            node->setVal(-childNode->getVal().get<double>());
            node->setType(Type::FLOAT);
            break;
        case Type::BOOL:
            node->setVal(-childNode->getVal().get<bool>());
            node->setType(Type::INT);
            break;
        default:
            throw std::runtime_error("Error: Couldn't convert string to value of nodes");
            break;
    }

    // Binds to the vtable
    vtable.bind(Variable(node->getText(), node->getVal(), node->getType()));
}

void Evaluator::visit(const std::shared_ptr<ModExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    if (leftNode->getType() != rightNode->getType() ||
        !((leftNode->getType() == Type::FLOAT || leftNode->getType() == Type::INT ||
           leftNode->getType() == Type::BOOL) &&
          (rightNode->getType() == Type::FLOAT || rightNode->getType() == Type::INT ||
           rightNode->getType() == Type::BOOL)) ||
        leftNode->getType() == Type::TABLE || rightNode->getType() == Type::TABLE ||
        leftNode->getType() == Type::NONETYPE || rightNode->getType() == Type::NONETYPE ||
        leftNode->getType() == Type::STR || rightNode->getType() == Type::STR) {
        // TODO: move to error handler at some point
        throw std::runtime_error("Cannot compare the used types");
    }

    // Evaluates the value of the expression
    switch (leftNode->getType()) {
        case Type::INT:
            if (rightNode->getType() == Type::BOOL) {
                node->setVal(leftNode->getVal().get<int>() % rightNode->getVal().get<bool>());
            } else if (rightNode->getType() == Type::INT) {
                node->setVal(leftNode->getVal().get<int>() % rightNode->getVal().get<int>());
            } else {
                node->setVal(
                    fmod(leftNode->getVal().get<int>(), rightNode->getVal().get<double>()));
            }
            break;
        case Type::FLOAT:
            node->setType(Type::FLOAT);
            if (rightNode->getType() == Type::BOOL) {
                node->setVal(
                    fmod(leftNode->getVal().get<double>(), rightNode->getVal().get<bool>()));
            } else if (rightNode->getType() == Type::INT) {
                node->setVal(
                    fmod(leftNode->getVal().get<double>(), rightNode->getVal().get<int>()));
            } else {
                node->setVal(
                    fmod(leftNode->getVal().get<double>(), rightNode->getVal().get<bool>()));
            }
            break;
        case Type::BOOL:
            if (rightNode->getType() == Type::BOOL) {
                node->setVal(leftNode->getVal().get<bool>() % rightNode->getVal().get<bool>());
            } else if (rightNode->getType() == Type::INT) {
                node->setVal(leftNode->getVal().get<bool>() % rightNode->getVal().get<int>());
            } else {
                node->setVal(
                    fmod(leftNode->getVal().get<bool>(), rightNode->getVal().get<double>()));
            }
            break;
        default:
            throw std::runtime_error("Error: Couldn't convert string to value of nodes");
            break;
    }

    // Always sets the type to bool for comparisons
    node->setType(Type::BOOL);

    // Binds to the vtable
    vtable.bind(Variable(node->getText(), node->getVal(), node->getType()));
}

void Evaluator::visit(const std::shared_ptr<MultExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    if (leftNode->getType() != rightNode->getType() ||
        !((leftNode->getType() == Type::FLOAT || leftNode->getType() == Type::INT ||
           leftNode->getType() == Type::BOOL) &&
          (rightNode->getType() == Type::FLOAT || rightNode->getType() == Type::INT ||
           rightNode->getType() == Type::BOOL)) ||
        leftNode->getType() == Type::TABLE || rightNode->getType() == Type::TABLE ||
        leftNode->getType() == Type::NONETYPE || rightNode->getType() == Type::NONETYPE ||
        leftNode->getType() == Type::STR || rightNode->getType() == Type::STR) {
        // TODO: move to error handler at some point
        throw std::runtime_error("Cannot multiply with the used types");
    }

    // Evaluates the value of the expression
    // TODO: Support string mutliplication e.g. "Hello" * 3 = "HelloHelloHello"
    switch (leftNode->getType()) {
        case Type::INT:
            if (rightNode->getType() == Type::BOOL) {
                node->setVal(leftNode->getVal().get<int>() * rightNode->getVal().get<bool>());
                node->setType(Type::INT);
            } else if (rightNode->getType() == Type::INT) {
                node->setVal(leftNode->getVal().get<int>() * rightNode->getVal().get<int>());
                node->setType(Type::INT);
            } else {
                node->setVal(leftNode->getVal().get<int>() * rightNode->getVal().get<double>());
                node->setType(Type::FLOAT);
            }
            break;
        case Type::FLOAT:
            node->setType(Type::FLOAT);
            if (rightNode->getType() == Type::BOOL) {
                node->setVal(leftNode->getVal().get<double>() * rightNode->getVal().get<bool>());
            } else if (rightNode->getType() == Type::INT) {
                node->setVal(leftNode->getVal().get<double>() * rightNode->getVal().get<int>());
            } else {
                node->setVal(leftNode->getVal().get<double>() * rightNode->getVal().get<double>());
            }
            break;
        case Type::BOOL:
            if (rightNode->getType() == Type::BOOL) {
                node->setVal(leftNode->getVal().get<bool>() * rightNode->getVal().get<bool>());
                node->setType(Type::INT);
            } else if (rightNode->getType() == Type::INT) {
                node->setVal(leftNode->getVal().get<bool>() * rightNode->getVal().get<int>());
                node->setType(Type::INT);
            } else {
                node->setVal(leftNode->getVal().get<bool>() * rightNode->getVal().get<double>());
                node->setType(Type::FLOAT);
            }
            break;
        default:
            throw std::runtime_error("Error: Couldn't convert string to value of nodes");
            break;
    }

    // Binds to the vtable
    vtable.bind(Variable(node->getText(), node->getVal(), node->getType()));
}

void Evaluator::visit(const std::shared_ptr<NotEqualExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    if (leftNode->getType() != rightNode->getType() ||
        !((leftNode->getType() == Type::FLOAT || leftNode->getType() == Type::INT ||
           leftNode->getType() == Type::BOOL) &&
          (rightNode->getType() == Type::FLOAT || rightNode->getType() == Type::INT ||
           rightNode->getType() == Type::BOOL)) ||
        leftNode->getType() == Type::TABLE || rightNode->getType() == Type::TABLE ||
        leftNode->getType() == Type::NONETYPE || rightNode->getType() == Type::NONETYPE ||
        leftNode->getType() == Type::STR || rightNode->getType() == Type::STR) {
        // TODO: move to error handler at some point
        throw std::runtime_error("Cannot compare the used types");
    }

    // Evaluates the value of the expression
    switch (leftNode->getType()) {
        case Type::INT:
            if (rightNode->getType() == Type::BOOL) {
                node->setVal(leftNode->getVal().get<int>() != rightNode->getVal().get<bool>());
            } else if (rightNode->getType() == Type::INT) {
                node->setVal(leftNode->getVal().get<int>() != rightNode->getVal().get<int>());
            } else {
                node->setVal(leftNode->getVal().get<int>() != rightNode->getVal().get<double>());
            }
            break;
        case Type::FLOAT:
            node->setType(Type::FLOAT);
            if (rightNode->getType() == Type::BOOL) {
                node->setVal(leftNode->getVal().get<double>() != rightNode->getVal().get<bool>());
            } else if (rightNode->getType() == Type::INT) {
                node->setVal(leftNode->getVal().get<double>() != rightNode->getVal().get<int>());
            } else {
                node->setVal(leftNode->getVal().get<double>() != rightNode->getVal().get<double>());
            }
            break;
        case Type::BOOL:
            if (rightNode->getType() == Type::BOOL) {
                node->setVal(leftNode->getVal().get<bool>() != rightNode->getVal().get<bool>());
            } else if (rightNode->getType() == Type::INT) {
                node->setVal(leftNode->getVal().get<bool>() != rightNode->getVal().get<int>());
            } else {
                node->setVal(leftNode->getVal().get<bool>() != rightNode->getVal().get<double>());
            }
            break;
        default:
            throw std::runtime_error("Error: Couldn't convert string to value of nodes");
            break;
    }

    // Always sets the type to bool for comparisons
    node->setType(Type::BOOL);

    // Binds to the vtable
    vtable.bind(Variable(node->getText(), node->getVal(), node->getType()));
}

void Evaluator::visit(const std::shared_ptr<NotNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> childNode = node->getChildNode();
    childNode->accept(shared_from_this());

    if (childNode->getType() != Type::BOOL) {
        // TODO: move to error handler at some point
        throw std::runtime_error("Cannot compare the used types");
    }

    // Evaluates the value of the expression
    if (childNode->getVal().get<bool>() == 1)
        childNode->setVal(0);
    else
        childNode->setVal(1);

    // Always sets the type to bool for comparisons
    node->setType(Type::BOOL);

    // Binds to the vtable
    vtable.bind(Variable(node->getText(), node->getVal(), node->getType()));
}

void Evaluator::visit(const std::shared_ptr<OrExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    if (leftNode->getType() != Type::BOOL || rightNode->getType() != Type::BOOL) {
        // TODO: move to error handler at some point
        throw std::runtime_error("Cannot compare the used types");
    }

    // Evaluates the value of the expression
    switch (leftNode->getType()) {
        case Type::BOOL:
            if (leftNode->getVal().get<bool>() == 1 || rightNode->getVal().get<bool>() == 1)
                node->setVal(1);
            else
                node->setVal(0);
            break;
        default:
            throw std::runtime_error("Error: Couldn't convert string to value of nodes");
            break;
    }

    // Always sets the type to bool for comparisons
    node->setType(Type::BOOL);

    // Binds to the vtable
    vtable.bind(Variable(node->getText(), node->getVal(), node->getType()));
}

void Evaluator::visit(const std::shared_ptr<ParNode> &node) {
    std::shared_ptr<AstNode> childNode = node->getChildNode();
    childNode->accept(shared_from_this());
    node->setType(childNode->getType());
    node->setVal(childNode->getVal());
}

void Evaluator::visit(const std::shared_ptr<PlusExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    if (leftNode->getType() != rightNode->getType() ||
        !((leftNode->getType() == Type::FLOAT || leftNode->getType() == Type::INT ||
           leftNode->getType() == Type::BOOL) &&
          (rightNode->getType() == Type::FLOAT || rightNode->getType() == Type::INT ||
           rightNode->getType() == Type::BOOL)) ||
        leftNode->getType() == Type::TABLE || rightNode->getType() == Type::TABLE ||
        leftNode->getType() == Type::NONETYPE || rightNode->getType() == Type::NONETYPE) {
        // TODO: move to error handler at some point
        throw std::runtime_error("Cannot do addition with the used types");
    }

    // Evaluates the value of the expression
    switch (leftNode->getType()) {
        case Type::INT:
            if (rightNode->getType() == Type::BOOL) {
                node->setVal(leftNode->getVal().get<int>() + rightNode->getVal().get<bool>());
                node->setType(Type::INT);
            } else if (rightNode->getType() == Type::INT) {
                node->setVal(leftNode->getVal().get<int>() + rightNode->getVal().get<int>());
                node->setType(Type::INT);
            } else {
                node->setVal(leftNode->getVal().get<int>() + rightNode->getVal().get<double>());
                node->setType(Type::FLOAT);
            }
            break;
        case Type::FLOAT:
            node->setType(Type::FLOAT);
            if (rightNode->getType() == Type::BOOL) {
                node->setVal(leftNode->getVal().get<double>() + rightNode->getVal().get<bool>());
            } else if (rightNode->getType() == Type::INT) {
                node->setVal(leftNode->getVal().get<double>() + rightNode->getVal().get<int>());
            } else {
                node->setVal(leftNode->getVal().get<double>() + rightNode->getVal().get<double>());
            }
            break;
        case Type::BOOL:
            if (rightNode->getType() == Type::BOOL) {
                node->setVal(leftNode->getVal().get<bool>() + rightNode->getVal().get<bool>());
                node->setType(Type::INT);
            } else if (rightNode->getType() == Type::INT) {
                node->setVal(leftNode->getVal().get<bool>() + rightNode->getVal().get<int>());
                node->setType(Type::INT);
            } else {
                node->setVal(leftNode->getVal().get<bool>() + rightNode->getVal().get<double>());
                node->setType(Type::FLOAT);
            }
            break;
        case Type::STR:
            node->setVal(leftNode->getVal().get<std::string>() +
                         rightNode->getVal().get<std::string>());
            node->setType(Type::STR);
            break;
        default:
            throw std::runtime_error("Error: Couldn't convert string to value of nodes");
            break;
    }

    // Binds to the vtable
    vtable.bind(Variable(node->getText(), node->getVal(), node->getType()));
}

void Evaluator::visit(const std::shared_ptr<PlusNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> childNode = node->getChildNode();
    childNode->accept(shared_from_this());

    if (childNode->getType() == Type::STR || childNode->getType() == Type::LIST ||
        childNode->getType() == Type::NONETYPE || childNode->getType() == Type::TABLE) {
        // TODO: move to error handler at some point
        throw std::runtime_error("Cannot use unary plus with the used type");
    }

    // Evaluates the value of the expression
    switch (childNode->getType()) {
        case Type::INT:
            if (childNode->getVal().get<int>() == 69)
                throw std::runtime_error(
                    "Why would you ever use this kind of operator without lambda functions?!?");
            node->setVal(childNode->getVal().get<int>());
            node->setType(Type::INT);
            break;
        case Type::FLOAT:
            node->setVal(childNode->getVal().get<double>());
            node->setType(Type::FLOAT);
            break;
        case Type::BOOL:
            node->setVal(childNode->getVal().get<bool>());
            node->setType(Type::BOOL);
            break;
        default:
            throw std::runtime_error("Error: Couldn't convert string to value of nodes");
            break;
    }

    // Binds to the vtable
    vtable.bind(Variable(node->getText(), node->getVal(), node->getType()));
}

void Evaluator::visit(const std::shared_ptr<ProcCallNode> &node) {
    std::shared_ptr<LeafNode> procNode = std::dynamic_pointer_cast<LeafNode>(node->getChildNode());

    Procedure *proc = nullptr;
    try {
        proc = ptable.lookup(procNode->getText(), node->getChildNodeList().size());

    } catch (const std::out_of_range &e) {
        throw std::runtime_error("Error: undefined procedure \"" + procNode->getText() + "\"\n");
    }

    // Check if amount of arguments is correct
    if (proc->getArity() != node->getChildNodeList().size()) {
        throw std::runtime_error("Error: procedure \"" + procNode->getText() +
                                 "\" called with incorrect number of arguments\n");
    }

    // Evaluate params
    std::vector<std::shared_ptr<AstNode>> argNodes = node->getChildNodeList();
    for (size_t i = 0; i < argNodes.size(); ++i) {
        argNodes[i]->accept(shared_from_this());
    }

    vtable.enterScope(proc->getScope());

    // Bind actual params to formal params
    for (size_t i = 0; i < argNodes.size(); ++i) {
        vtable.bind(Variable(proc->getParams()[i], argNodes[i]->getVal(), argNodes[i]->getType()));
    }

    // If procedure written in cpp execute it and return
    if (proc->isBuiltinProcedure()) {
        std::pair<Type, Value> result = proc->getProc()(argNodes);

        node->setType(result.first);
        node->setVal(result.second);

        vtable.exitScope();
        return;
    }

    // Evaluate body
    std::vector<std::shared_ptr<AstNode>> bodyNodes = proc->getBodyNodes();
    for (size_t i = 0; i < bodyNodes.size(); ++i) {
        bodyNodes[i]->accept(shared_from_this());
        std::shared_ptr<ReturnNode> returnNode =
            std::dynamic_pointer_cast<ReturnNode>(bodyNodes[i]);
        if (returnNode) {
            node->setVal(returnNode->getVal());
            node->setType(returnNode->getType());
            break;
        }
    }

    vtable.exitScope();
}

void Evaluator::visit(const std::shared_ptr<ProcDecNode> &node) {
    std::vector<std::shared_ptr<AstNode>> paramNodes = node->getParamNodes();
    std::vector<std::string> params;
    for (size_t i = 0; i < paramNodes.size(); ++i) {
        params.emplace_back(paramNodes[i]->getText());
    }

    std::vector<std::shared_ptr<AstNode>> bodyNodes = node->getBodyNodes();

    ptable.bind(Procedure(node->getNameNode()->getText(), params, bodyNodes, vtable.top()));
}

void Evaluator::visit(const std::shared_ptr<ProgNode> &node) {
    initPtable();

    std::vector<std::shared_ptr<AstNode>> childNodes = node->getChildNodeList();
    for (size_t i = 0; i < childNodes.size(); ++i) {
        childNodes[i]->accept(shared_from_this());
    }
}

void Evaluator::visit(const std::shared_ptr<ReturnNode> &node) {
    std::shared_ptr<AstNode> childNode = node->getChildNode();
    childNode->accept(shared_from_this());
    node->setVal(childNode->getVal());
    node->setType(childNode->getType());
}

void Evaluator::visit(const std::shared_ptr<TableNode> &node) {}

void Evaluator::visit(const std::shared_ptr<UnaryExprNode> &node) {}

void Evaluator::visit(const std::shared_ptr<WhileNode> &node) {}

void Evaluator::initPtable() {
    Procedure::ProcType print = [](std::vector<std::shared_ptr<AstNode>> arg) {
        std::cout << arg[0]->getVal().toString() << '\n';
        return std::pair(Type::NONETYPE, nullptr);
    };

    Procedure::ProcType input = [](std::vector<std::shared_ptr<AstNode>> arg) {
        std::cout << arg[0]->getVal().toString();
        std::string inputStr;
        std::getline(std::cin, inputStr);
        return std::pair(Type::STR, inputStr);
    };

    Procedure::ProcType type = [](std::vector<std::shared_ptr<AstNode>> arg) {
        return std::pair(Type::STR, TypeUtil::typeToString(arg[0]->getType()));
    };

    Procedure::ProcType str = [](std::vector<std::shared_ptr<AstNode>> arg) {
        return std::pair(Type::STR, arg[0]->getVal().toString());
    };

    ptable.bind(Procedure("print", {"msg"}, print));
    ptable.bind(Procedure("input", {"msg"}, input));
    ptable.bind(Procedure("type", {"x"}, type));
    ptable.bind(Procedure("str", {"x"}, str));
}
