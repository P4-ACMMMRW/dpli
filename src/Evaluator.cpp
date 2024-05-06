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
}

void Evaluator::visit(const std::shared_ptr<AssignNode> &node) {
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    std::shared_ptr<LeafNode> leafNode = std::dynamic_pointer_cast<LeafNode>(leftNode);
    std::shared_ptr<IndexNode> indexNode = std::dynamic_pointer_cast<IndexNode>(leftNode);

    bool isLeaf = leafNode != nullptr;
    bool isIndexing = indexNode != nullptr;

    // If left is not a leaf or index node, throw error
    // Also if left is a leaf node but not an identifier, throw error
    bool error = (!isLeaf && !isIndexing) || (isLeaf && !leafNode->getIsIdentifier());
    if (error) {
        // TODO: move to error handler at some point
        throw std::runtime_error("Error: left side of assignment must be a stored reference\n");
    }

    // Compute type of right node
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    // If indexing
    if (isIndexing) {
        indexNode->accept(shared_from_this());
        // Identifier node is always the leftmost node, so we can find it by traversing left nodes until we reach a leaf node
        std::shared_ptr<AstNode> identifierNode = indexNode->getLeftNode();
        while (std::dynamic_pointer_cast<IndexNode>(identifierNode) != nullptr) {
            identifierNode = std::dynamic_pointer_cast<IndexNode>(identifierNode)->getLeftNode();
        }

        Variable *var = vtable.lookup(identifierNode->getText());
        Value val = var->getVal();

        // Store indices in a temporary vector
        std::vector<Value> indices;
        while (indexNode != nullptr) {
            if (indexNode->getRightNode()->getVal().is<Value::INT>()) {
                indices.emplace_back(indexNode->getRightNode()->getVal().get<Value::INT>());
            } else if (indexNode->getRightNode()->getVal().is<Value::STR>()) {
                indices.emplace_back(indexNode->getRightNode()->getVal().get<Value::STR>());
            }

            indexNode = std::dynamic_pointer_cast<IndexNode>(indexNode->getLeftNode());
        }
        
        // Get the pointer to the innermost list or column
        Value::LIST list = nullptr;
        Value::INT lastIndex = 0;
        for (int i = indices.size() - 1; i >= 0; --i) {
            if (val.is<Value::LIST>()) {
                Value::INT index = indices[i].get<Value::INT>();
                list = val.getMut<Value::LIST>();

                if (index < 0 || static_cast<size_t>(index) >= list->size()) {
                    throw std::runtime_error("Error: index out of range\n");
                }

                lastIndex = index;
                val = *(*list)[index];
            } else if (val.is<Value::COLUMN>()) {
                Value::INT index = indices[i].get<Value::INT>();
                list = val.getMut<Value::COLUMN>()->data;
      
                if (index < 0 || static_cast<size_t>(index) >= list->size()) {
                    throw std::runtime_error("Error: index out of range\n");
                }

                lastIndex = index;
                val = *(*list)[index];
            } else if (val.is<Value::TABLE>()) {
                // Tables index by header name
                Value::TABLE table = val.get<Value::TABLE>();
                Value::STR header = indices[i].get<Value::STR>();

                try {
                    val = table->at(header);
                } catch (const std::out_of_range &e) {
                    throw std::runtime_error("Error: header not found in table\n");
                }
            } else {
                throw std::runtime_error("Error: index assignment not allowed for this type\n");
            }
        }
        
        // Assign value to innermost list
        if (val.is<Value::COLUMN>()) {
            Value::COLUMN col = val.getMut<Value::COLUMN>();

            if (rightNode->getVal().is<Value::LIST>()) {
                // Check size of right node matches size of column
                if (col->data->size() != rightNode->getVal().get<Value::LIST>()->size()) {
                    throw std::runtime_error("Error: size of right side of assignment does not match size of column\n");
                }

                for (size_t i = 0; i < col->data->size(); ++i) {
                    *(*col->data)[i] = *(*rightNode->getVal().get<Value::LIST>())[i];
                }
            } else {
                for (size_t i = 0; i < col->data->size(); ++i) {
                    *(*col->data)[i] = rightNode->getVal();
                }
            }
        } else {
            *(*list)[lastIndex] = rightNode->getVal();
        }
    } else {
        vtable.bind(Variable(leftNode->getText(), rightNode->getVal()));
    }
}

void Evaluator::visit(const std::shared_ptr<ColumnNode> &node) {
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    std::shared_ptr<AstNode> rightNode = node->getRightNode();

    leftNode->accept(shared_from_this());
    rightNode->accept(shared_from_this());
}

void Evaluator::visit(const std::shared_ptr<DivExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    if (!(isNumeric(leftNode->getType()) && isNumeric(rightNode->getType()))) {
        // TODO: move to error handler at some point
        throw std::runtime_error("Cannot divide with the types");
    }

    // Divide with 0 check
    if (rightNode->getType() == Type::INT) {
        if (rightNode->getVal().get<int>() == 0) {
            throw std::runtime_error("Cannot divide with 0");
        }
    } else if (rightNode->getType() == Type::FLOAT) {
        if (rightNode->getVal().get<double>() == 0) {
            throw std::runtime_error("Cannot divide with 0");
        }
    } else if (rightNode->getVal().get<bool>() == 0) {
        throw std::runtime_error("Cannot divide with 0");
    }

    // Evaluates the value of the expression
    switch (leftNode->getType()) {
        case Type::INT:
            if (rightNode->getType() == Type::BOOL) {
                node->setVal(static_cast<double>(leftNode->getVal().get<int>()) /
                             rightNode->getVal().get<bool>());
            } else if (rightNode->getType() == Type::INT) {
                node->setVal(static_cast<double>(leftNode->getVal().get<int>()) /
                             rightNode->getVal().get<int>());
            } else {
                node->setVal(static_cast<double>(leftNode->getVal().get<int>()) /
                             rightNode->getVal().get<double>());
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
                node->setVal(static_cast<double>(leftNode->getVal().get<bool>()) /
                             rightNode->getVal().get<bool>());
            } else if (rightNode->getType() == Type::INT) {
                node->setVal(static_cast<double>(leftNode->getVal().get<bool>()) /
                             rightNode->getVal().get<int>());
            } else {
                node->setVal(static_cast<double>(leftNode->getVal().get<bool>()) /
                             rightNode->getVal().get<double>());
            }
            break;
        default:
            throw std::runtime_error("Error: Couldn't convert string to value of nodes");
            break;
    }

    // Always sets type to float fo division
    node->setType(Type::FLOAT);
}

void Evaluator::visit(const std::shared_ptr<ElseNode> &node) {}

void Evaluator::visit(const std::shared_ptr<EqualExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    if (!(isNumeric(leftNode->getType()) && isNumeric(rightNode->getType())) ||
        (leftNode->getType() == Type::STR && rightNode->getType() == Type::STR)) {
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
}

void Evaluator::visit(const std::shared_ptr<ExpoExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    if (!((leftNode->getType() == Type::FLOAT || leftNode->getType() == Type::INT ||
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
                node->setVal(
                    std::pow(leftNode->getVal().get<int>(), rightNode->getVal().get<bool>()));
                node->setType(Type::INT);
            } else if (rightNode->getType() == Type::INT) {
                if (rightNode->getVal().get<int>() >= 0) {
                    node->setVal((int)round(
                        std::pow(leftNode->getVal().get<int>(), rightNode->getVal().get<int>())));
                    node->setType(Type::INT);
                } else {
                    node->setVal(
                        std::pow(leftNode->getVal().get<int>(), rightNode->getVal().get<int>()));
                    node->setType(Type::FLOAT);
                }
            } else {
                node->setVal(
                    std::pow(leftNode->getVal().get<int>(), rightNode->getVal().get<double>()));
                node->setType(Type::FLOAT);
            }
            break;
        case Type::FLOAT:
            node->setType(Type::FLOAT);
            if (rightNode->getType() == Type::BOOL) {
                node->setVal(
                    std::pow(leftNode->getVal().get<double>(), rightNode->getVal().get<bool>()));
            } else if (rightNode->getType() == Type::INT) {
                node->setVal(
                    std::pow(leftNode->getVal().get<double>(), rightNode->getVal().get<int>()));
            } else {
                node->setVal(
                    std::pow(leftNode->getVal().get<double>(), rightNode->getVal().get<double>()));
            }
            break;
        case Type::BOOL:
            if (rightNode->getType() == Type::BOOL) {
                node->setVal(
                    std::pow(leftNode->getVal().get<bool>(), rightNode->getVal().get<bool>()));
                node->setType(Type::INT);
            } else if (rightNode->getType() == Type::INT) {
                node->setVal(
                    std::pow(leftNode->getVal().get<bool>(), rightNode->getVal().get<int>()));
                node->setType(Type::INT);
            } else {
                node->setVal(
                    std::pow(leftNode->getVal().get<bool>(), rightNode->getVal().get<double>()));
                node->setType(Type::FLOAT);
            }
            break;
        default:
            throw std::runtime_error("Error: Couldn't convert string to value of nodes");
            break;
    }
}

void Evaluator::visit(const std::shared_ptr<FilterNode> &node) {
    std::shared_ptr<AstNode> identifierNode = node->getLeftNode();
    std::shared_ptr<AstNode> filterNode = node->getRightNode();

    identifierNode->accept(shared_from_this());
    filterNode->accept(shared_from_this());

    Value identifierVal = identifierNode->getVal();
    Value filterVal = filterNode->getVal();

    if (identifierVal.is<Value::LIST>()) {
        //? is it possible to use on list?
    } else if (identifierVal.is<Value::COLUMN>()) {
        Value::COLUMN col = identifierVal.get<Value::COLUMN>();

        // Map string to operator function
        std::map<std::string, std::function<bool(const Value&, const Value&)>> ops = {
            {"<", [](const Value& a, const Value& b) { return a < b; }},
            {">", [](const Value& a, const Value& b) { return a > b; }},
            {"==", [](const Value& a, const Value& b) { return a == b; }},
            {"!=", [](const Value& a, const Value& b) { return a != b; }},
            {">=", [](const Value& a, const Value& b) { return a >= b; }},
            {"<=", [](const Value& a, const Value& b) { return a <= b; }},
        };

        std::string op = node->getText();

        // Compute indices to keep
        std::vector<Value::INT> indicesToKeep;
        for (size_t i = 0; i < col->data->size(); ++i) {
            Value val = *(*col->data)[i];
            if (ops[op](val, filterVal)) indicesToKeep.push_back(i);
        }

        // Create new columns with filtered data and insert into new table
        Value::TABLE table = col->parent;
        Value::TABLE newTable = std::make_shared<std::unordered_map<Value::STR, Value::COLUMN>>();
        for (const std::pair<const Value::STR, Value::COLUMN> &entry : *table) {
            Value::LIST newData = std::make_shared<std::vector<std::shared_ptr<Value>>>();
            for (Value::INT index : indicesToKeep) {
                newData->emplace_back((*entry.second->data)[index]);
            }

            Value::COLUMN newCol = std::make_shared<Value::COL_STRUCT>();
            newCol->parent = newTable;
            newCol->header = entry.first;
            newCol->data = newData;
            newCol->size = newData->size();
            newTable->insert({entry.first, newCol});
        }

        node->setVal(newTable);
    } else {
        throw std::runtime_error("Error: filter operation not allowed for this type\n");
    }
}

void Evaluator::visit(const std::shared_ptr<GreaterEqualExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    if (!(isNumeric(leftNode->getType()) && isNumeric(rightNode->getType()))) {
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
}

void Evaluator::visit(const std::shared_ptr<GreaterExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    if (!(isNumeric(leftNode->getType()) && isNumeric(rightNode->getType()))) {
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
}

void Evaluator::visit(const std::shared_ptr<HeaderIndexNode> &node) {
    std::shared_ptr<AstNode> identifierNode = node->getLeftNode();
    std::shared_ptr<AstNode> headerNode = node->getRightNode();

    identifierNode->accept(shared_from_this());
    headerNode->accept(shared_from_this());

    Value val = identifierNode->getVal();
    if (val.is<Value::TABLE>()) {
        Value::TABLE table = val.get<Value::TABLE>();
        Value::STR header = headerNode->getVal().get<Value::STR>();

        try {
            node->setVal(table->at(header));
        } catch (const std::out_of_range &e) {
            throw std::runtime_error("Error: header not found in table\n");
        }
    } else {
        throw std::runtime_error("Error: invalid index operation\n");
    }
}

void Evaluator::visit(const std::shared_ptr<IfNode> &node) {}

void Evaluator::visit(const std::shared_ptr<IndexNode> &node) {
    std::shared_ptr<AstNode> identifierNode = node->getLeftNode();
    std::shared_ptr<AstNode> indexNode = node->getRightNode();

    identifierNode->accept(shared_from_this());
    indexNode->accept(shared_from_this());

    if (!indexNode->getVal().is<Value::INT>()) {
        if (indexNode->getVal().is<Value::STR>()) {
            throw std::runtime_error("Error: index must be an integer. Did you forget '$' infront?\n");
        }

        throw std::runtime_error("Error: index must be an integer\n");
    }

    Value::INT index = indexNode->getVal().get<Value::INT>();

    Value val = identifierNode->getVal();
    if (val.is<Value::STR>()) {
        Value::STR str = val.get<Value::STR>();

        if (index < 0 || static_cast<size_t>(index) >= str.size()) {
            throw std::runtime_error("Error: index out of range\n");
        }

        node->setVal(Value::STR{str[index]});
    } else if (val.is<Value::LIST>()) {
        Value::LIST list = val.get<Value::LIST>();

        if (index < 0 || static_cast<size_t>(index) >= list->size()) {
            throw std::runtime_error("Error: index out of range\n");
        }

        node->setVal(*(*list)[index]);
    } else if (val.is<Value::COLUMN>()) {
        Value::COLUMN col = val.get<Value::COLUMN>();

        if (index < 0 || static_cast<size_t>(index) >= col->data->size()) {
            throw std::runtime_error("Error: index out of range\n");
        }

        node->setVal(*(*col->data)[index]);
    } else {
        throw std::runtime_error("Error: invalid index operation\n");
    }
}

void Evaluator::visit(const std::shared_ptr<IntersectionExprNode> &node) {}

void Evaluator::visit(const std::shared_ptr<LeafNode> &node) {
    if (node->getText() == "<EOF>") return;

    if (node->getIsIdentifier()) {
        try {
            Variable *var = vtable.lookup(node->getText());
            node->setVal(var->getVal());
        } catch (const std::out_of_range &e) {
            throw std::runtime_error("Error: undefined variable \"" + node->getText() + "\"\n");
        }
    } else {
        Value val = node->getVal();

        if (val.is<Value::STR>()) {
            // If string we have to remove quotes from value
            std::string text = node->getText();
            node->setVal(text.substr(1, text.size() - 2));
        } else if (val.is<Value::INT>()) {
            node->setVal(std::stol(node->getText()));
        } else if (val.is<Value::FLOAT>()) {
            node->setVal(std::stod(node->getText()));
        } else if (val.is<Value::BOOL>()) {
            node->setVal(node->getText() == "True");
        } else {
            node->setVal(nullptr);
        }
    }
}

void Evaluator::visit(const std::shared_ptr<LessEqualExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    if (!(isNumeric(leftNode->getType()) && isNumeric(rightNode->getType()))) {
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
}

void Evaluator::visit(const std::shared_ptr<LessExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    if (!(isNumeric(leftNode->getType()) && isNumeric(rightNode->getType()))) {
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
}

void Evaluator::visit(const std::shared_ptr<ListNode> &node) {
    std::vector<std::shared_ptr<AstNode>> childNodes = node->getChildNodeList();

    Value::LIST values = std::make_shared<std::vector<std::shared_ptr<Value>>>();
    for (size_t i = 0; i < childNodes.size(); ++i) {
        childNodes[i]->accept(shared_from_this());
        values->emplace_back(std::make_shared<Value>(childNodes[i]->getVal()));
    }

    node->setVal(values);
}

void Evaluator::visit(const std::shared_ptr<MinusExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    if (!(isNumeric(leftNode->getType()) && isNumeric(rightNode->getType()))) {
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
}

void Evaluator::visit(const std::shared_ptr<ModExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    if (!(isNumeric(leftNode->getType()) && isNumeric(rightNode->getType()))) {
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
}

void Evaluator::visit(const std::shared_ptr<MultExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    if (!((isNumeric(leftNode->getType()) && isNumeric(rightNode->getType())) ||
          (leftNode->getType() == Type::INT && rightNode->getType() == Type::STR) ||
          (leftNode->getType() == Type::STR && rightNode->getType() == Type::INT) ||
          (leftNode->getType() == Type::STR && rightNode->getType() == Type::BOOL) ||
          (leftNode->getType() == Type::BOOL && rightNode->getType() == Type::STR))) {
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
            } else if (rightNode->getType() == Type::FLOAT) {
                node->setVal(leftNode->getVal().get<int>() * rightNode->getVal().get<double>());
                node->setType(Type::FLOAT);
            } else {
                node->setType(Type::STR);
                node->setVal("");
                for (size_t i = 0; i < leftNode->getVal().get<int>(); i++)
                    node->setVal(node->getVal().get<std::string>() +
                                 rightNode->getVal().get<std::string>());
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
            } else if (rightNode->getType() == Type::FLOAT) {
                node->setVal(leftNode->getVal().get<bool>() * rightNode->getVal().get<double>());
                node->setType(Type::FLOAT);
            } else {
                node->setType(Type::STR);
                node->setVal("");
                for (size_t i = 0; i < leftNode->getVal().get<bool>(); i++)
                    node->setVal(node->getVal().get<std::string>() +
                                 rightNode->getVal().get<std::string>());
            }
            break;
        case Type::STR:
            node->setType(Type::STR);
            node->setVal("");
            if (rightNode->getType() == Type::INT) {
                for (size_t i = 0; i < rightNode->getVal().get<int>(); i++)
                node->setVal(node->getVal().get<std::string>() +
                             leftNode->getVal().get<std::string>());
            } else {
                for (size_t i = 0; i < rightNode->getVal().get<bool>(); i++)
                    node->setVal(node->getVal().get<std::string>() +
                        leftNode->getVal().get<std::string>());
            }
            break;
        default:
            throw std::runtime_error("Error: Couldn't convert string to value of nodes");
            break;
    }
}

void Evaluator::visit(const std::shared_ptr<NotEqualExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    if (!((leftNode->getType() == Type::FLOAT || leftNode->getType() == Type::INT ||
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
}

void Evaluator::visit(const std::shared_ptr<NotNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> childNode = node->getChildNode();
    childNode->accept(shared_from_this());

    if (!(isNumeric(childNode->getType()))) {
        // TODO: move to error handler at some point
        throw std::runtime_error("Cannot negate the used type");
    }

    // Evaluates the value of the expression
    switch (childNode->getType()) {
        case Type::INT:
            if (childNode->getVal().get<int>() != 0)
                node->setVal(0);
            else
                node->setVal(1);
            break;
        case Type::FLOAT:
            if (childNode->getVal().get<double>() != 0)
                node->setVal(0);
            else
                node->setVal(1);
            break;
        case Type::BOOL:
            if (childNode->getVal().get<bool>() != 0)
                node->setVal(0);
            else
                node->setVal(1);
            break;
        default:
            throw std::runtime_error("Couldn't evaluate negation");
            break;
    }
    if (childNode->getVal().get<bool>() == 1)
        childNode->setVal(0);
    else
        childNode->setVal(1);

    // Always sets the type to bool for comparisons
    node->setType(Type::BOOL);
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
}

void Evaluator::visit(const std::shared_ptr<ParNode> &node) {
    std::shared_ptr<AstNode> childNode = node->getChildNode();
    childNode->accept(shared_from_this());
    node->setVal(childNode->getVal());
}

void Evaluator::visit(const std::shared_ptr<PlusExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    if (!((isNumeric(leftNode->getType()) && isNumeric(rightNode->getType())) ||
          (leftNode->getType() == Type::STR && rightNode->getType() == Type::STR))) {
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
            if (childNode->getVal().get<int>() == 69) {
                throw std::runtime_error(
                    "Why would you ever use this kind of operator without lambda functions?!?");
            }
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
        vtable.bind(Variable(proc->getParams()[i], argNodes[i]->getVal()));
    }

    // If procedure written in cpp execute it and return
    if (proc->isBuiltinProcedure()) {
        node->setVal(proc->getProc()(argNodes));
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
    std::vector<std::shared_ptr<AstNode>> childNodes = node->getChildNodeList();
    for (size_t i = 0; i < childNodes.size(); ++i) {
        childNodes[i]->accept(shared_from_this());
    }
}

void Evaluator::visit(const std::shared_ptr<ReturnNode> &node) {
    std::shared_ptr<AstNode> childNode = node->getChildNode();
    childNode->accept(shared_from_this());
    node->setVal(childNode->getVal());
}

void Evaluator::visit(const std::shared_ptr<TableNode> &node) {
    Value::TABLE table = std::make_shared<std::unordered_map<Value::STR, Value::COLUMN>>();
    std::vector<std::shared_ptr<AstNode>> childNodes = node->getChildNodeList();

    long size = 0;
    bool sizeSet = false;
    for (std::shared_ptr<AstNode> &child : childNodes) {
        std::shared_ptr<ColumnNode> columnNode = std::dynamic_pointer_cast<ColumnNode>(child);
        columnNode->accept(shared_from_this());

        if (!columnNode->getLeftNode()->getVal().is<Value::STR>()) {
            throw std::runtime_error("Error: table key must be a string\n");
        }

        Value::STR header = columnNode->getLeftNode()->getVal().get<Value::STR>();

        if (!columnNode->getRightNode()->getVal().is<Value::LIST>()) {
            throw std::runtime_error("Error: table value must be a list\n");
        }

        Value::LIST val = columnNode->getRightNode()->getVal().get<Value::LIST>();

        Value::COLUMN col = std::make_shared<Value::COL_STRUCT>();
        col->parent = table;
        col->header = header;
        col->data = val;

        if (!sizeSet) {
            sizeSet = true;
            size = val->size();
            col->size = size;
        } else if (val->size() != static_cast<size_t>(size)) {
            throw std::runtime_error("Error: all columns in a table must have the same size\n");
        }

        table->insert({header, col});
    }

    node->setVal(table);
}

void Evaluator::visit(const std::shared_ptr<UnionExprNode> &node) {}

void Evaluator::visit(const std::shared_ptr<WhileNode> &node) {}

void Evaluator::initPtable() {
    Procedure::ProcType print1 = [](std::vector<std::shared_ptr<AstNode>> arg) {
        std::cout << arg[0]->getVal().toString() << '\n';
        return nullptr;
    };

    Procedure::ProcType input0 = []([[maybe_unused]] std::vector<std::shared_ptr<AstNode>> arg) {
        std::string inputStr;
        std::getline(std::cin, inputStr);
        return inputStr;
    };

    Procedure::ProcType input1 = [input0](std::vector<std::shared_ptr<AstNode>> arg) {
        std::cout << arg[0]->getVal().toString();
        return input0(arg);
    };

    Procedure::ProcType type1 = [](std::vector<std::shared_ptr<AstNode>> arg) {
        return arg[0]->getVal().toTypeString();
    };

    Procedure::ProcType str1 = [](std::vector<std::shared_ptr<AstNode>> arg) {
        return arg[0]->getVal().toString();
    };

    Procedure::ProcType len1 = [](std::vector<std::shared_ptr<AstNode>> arg) {
        Value val = arg[0]->getVal();

        if (val.is<Value::STR>()) {
            return static_cast<Value::INT>(val.get<Value::STR>().size());
        } else if (val.is<Value::LIST>()) {
            return static_cast<Value::INT>(val.get<Value::LIST>()->size());
        } else if (val.is<Value::TABLE>()) {
            return static_cast<Value::INT>(val.get<Value::TABLE>()->size());
        } else if (val.is<Value::COLUMN>()) {
            return static_cast<Value::INT>(val.get<Value::COLUMN>()->data->size());
        }

        throw std::runtime_error("Error: len() called with invalid type");
    };

    ptable.bind(Procedure("print", {"msg"}, print1));
    ptable.bind(Procedure("input", {}, input0));
    ptable.bind(Procedure("input", {"msg"}, input1));
    ptable.bind(Procedure("type", {"x"}, type1));
    ptable.bind(Procedure("str", {"x"}, str1));
    ptable.bind(Procedure("len", {"x"}, len1));
}
