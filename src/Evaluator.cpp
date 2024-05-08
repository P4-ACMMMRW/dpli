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

    if (!isNumeric(leftNode->getVal()) || !isNumeric(rightNode->getVal())) {
        // TODO: move to error handler at some point
        throw RuntimeException("Cannot do logical and with the used types");
    }

    // Evaluates the value of the expression
    if (leftNode->getVal().is<Value::BOOL>()) {
        if (rightNode->getVal().is<Value::BOOL>())
            if (leftNode->getVal().get<Value::BOOL>() == true &&
            rightNode->getVal().get<Value::BOOL>() == true) 
                node->setVal(true);
            else node->setVal(false);
        else if (rightNode->getVal().is<Value::INT>()) 
            if (leftNode->getVal().get<Value::BOOL>() == true &&
            rightNode->getVal().get<Value::INT>() == true)
                node->setVal(true);
            else node->setVal(false);
        else if (leftNode->getVal().get<Value::BOOL>() == true &&
            rightNode->getVal().get<Value::FLOAT>() == true)
            node->setVal(true);
        else node->setVal (false);
    } else if (leftNode->getVal().is<Value::INT>()) {
        if (rightNode->getVal().is<Value::BOOL>())
            if (leftNode->getVal().get<Value::INT>() == true &&
            rightNode->getVal().get<Value::BOOL>() == true) 
                node->setVal(true);
            else node->setVal(false);
        else if (rightNode->getVal().is<Value::INT>()) 
            if (leftNode->getVal().get<Value::INT>() == true &&
            rightNode->getVal().get<Value::INT>() == true)
                node->setVal(true);
            else node->setVal(false);
        else if (leftNode->getVal().get<Value::INT>() == true &&
            rightNode->getVal().get<Value::FLOAT>() == true)
            node->setVal(true);
        else node->setVal (false);
    } else if (leftNode->getVal().is<Value::FLOAT>()) {
        if (rightNode->getVal().is<Value::BOOL>())
            if (leftNode->getVal().get<Value::FLOAT>() == true &&
            rightNode->getVal().get<Value::BOOL>() == true) 
                node->setVal(true);
            else node->setVal(false);
        else if (rightNode->getVal().is<Value::INT>()) 
            if (leftNode->getVal().get<Value::FLOAT>() == true &&
            rightNode->getVal().get<Value::INT>() == true)
                node->setVal(true);
            else node->setVal(false);
        else if (leftNode->getVal().get<Value::FLOAT>() == true &&
            rightNode->getVal().get<Value::FLOAT>() == true)
            node->setVal(true);
        else node->setVal (false);
    } else
        throw RuntimeException("Could not convert string to value of nodes");
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
        throw RuntimeException("Left side of assignment must be a stored reference");
    }

    // Compute type of right node
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    // If indexing
    if (isIndexing) {
        indexNode->accept(shared_from_this());
        // Identifier node is always the leftmost node, so we can find it by traversing left nodes
        // until we reach a leaf node
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
                    throw RuntimeException("Index out of range");
                }

                lastIndex = index;
                val = *(*list)[index];
            } else if (val.is<Value::COLUMN>()) {
                Value::INT index = indices[i].get<Value::INT>();
                list = val.getMut<Value::COLUMN>()->data;

                if (index < 0 || static_cast<size_t>(index) >= list->size()) {
                    throw RuntimeException("Index out of range");
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
                    throw RuntimeException("Header not found in table");
                }
            } else {
                throw RuntimeException("Index assignment not allowed for this type");
            }
        }

        // Assign value to innermost list
        if (val.is<Value::COLUMN>()) {
            Value::COLUMN col = val.getMut<Value::COLUMN>();

            if (rightNode->getVal().is<Value::LIST>()) {
                // Check size of right node matches size of column
                if (col->data->size() != rightNode->getVal().get<Value::LIST>()->size()) {
                    throw RuntimeException(
                        "size of right side of assignment does not match size of column");
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

    if (!((isNumeric(leftNode->getVal()) && isNumeric(rightNode->getVal())) || 
        (isNumeric(leftNode->getVal()) && rightNode->getVal().is<Value::COLUMN>()) ||
        (leftNode->getVal().is<Value::COLUMN>() && isNumeric(rightNode->getVal()) ||
        (leftNode->getVal().is<Value::COLUMN>() && rightNode->getVal().is<Value::COLUMN>())))) {
        // TODO: move to error handler at some point
        throw RuntimeException("Cannot divide with the types");
    }

    // Divide with 0 check
    if (rightNode->getVal().is<Value::INT>()) {
        if (rightNode->getVal().get<Value::INT>() == 0) {
            throw RuntimeException("Cannot divide with 0");
        }
    } else if (rightNode->getVal().is<Value::FLOAT>()) {
        if (rightNode->getVal().get<Value::FLOAT>() == 0) {
            throw RuntimeException("Cannot divide with 0");
        }
    } else if (rightNode->getVal().is<Value::BOOL>()) {
        if (rightNode->getVal().get<Value::BOOL>() == 0)
            throw RuntimeException("Cannot divide with 0");
    } else if (rightNode->getVal().is<Value::COLUMN>()){
        // Checks if both columns are the same size
        if (rightNode->getVal().is<Value::COLUMN>())
            for (int i = 0; i < rightNode->getVal().get<Value::COLUMN>()->data->size(); i++) {
                if ((*rightNode->getVal().get<Value::COLUMN>()->data)[i] == 0)
                throw RuntimeException("Cannot divide with 0");
            }
    }

    // Evaluates the value of the expression
    if (leftNode->getVal().is<Value::INT>()) {
        if (rightNode->getVal().is<Value::BOOL>()) {
            node->setVal(static_cast<double>(leftNode->getVal().get<Value::INT>()) /
                         rightNode->getVal().get<Value::BOOL>());
        } else if (rightNode->getVal().is<Value::INT>()) {
            node->setVal(static_cast<double>(leftNode->getVal().get<Value::INT>()) /
                         rightNode->getVal().get<Value::INT>());
        } else {
            node->setVal(static_cast<double>(leftNode->getVal().get<Value::INT>()) /
                         rightNode->getVal().get<Value::FLOAT>());
        }
    } else if (leftNode->getVal().is<Value::FLOAT>()) {
        if (rightNode->getVal().is<Value::BOOL>()) {
            node->setVal(leftNode->getVal().get<Value::FLOAT>() /
                         rightNode->getVal().get<Value::BOOL>());
        } else if (rightNode->getVal().is<Value::INT>()) {
            node->setVal(leftNode->getVal().get<Value::FLOAT>() /
                         rightNode->getVal().get<Value::INT>());
        } else {
            node->setVal(leftNode->getVal().get<Value::FLOAT>() /
                         rightNode->getVal().get<Value::FLOAT>());
        }
    } else if (leftNode->getVal().is<Value::BOOL>()) {
        if (rightNode->getVal().is<Value::BOOL>()) {
            node->setVal(static_cast<double>(leftNode->getVal().get<Value::BOOL>()) /
                         rightNode->getVal().get<Value::BOOL>());
        } else if (rightNode->getVal().is<Value::INT>()) {
            node->setVal(static_cast<double>(leftNode->getVal().get<Value::BOOL>()) /
                         rightNode->getVal().get<Value::INT>());
        } else {
            node->setVal(static_cast<double>(leftNode->getVal().get<Value::BOOL>()) /
                         rightNode->getVal().get<Value::FLOAT>());
        }
    } else if (leftNode->getVal().is<Value::BOOL>()) {
        if (rightNode->getVal().is<Value::BOOL>()) {
            node->setVal(static_cast<double>(leftNode->getVal().get<Value::BOOL>()) /
                         rightNode->getVal().get<Value::BOOL>());
        } else if (rightNode->getVal().is<Value::INT>()) {
            node->setVal(static_cast<double>(leftNode->getVal().get<Value::BOOL>()) /
                         rightNode->getVal().get<Value::INT>());
        } else {
            node->setVal(static_cast<double>(leftNode->getVal().get<Value::BOOL>()) /
                         rightNode->getVal().get<Value::FLOAT>());
        }
    } else if (leftNode->getVal().is<Value::COLUMN>()) {

    } else
        throw RuntimeException("Could not convert string to value of nodes");
}

void Evaluator::visit(const std::shared_ptr<ElseNode> &node) {
    std::vector<std::shared_ptr<AstNode>> elseBodyNodes = node->getChildNodeList();

    for (size_t i = 0; i < elseBodyNodes.size(); ++i) {
        elseBodyNodes[i]->accept(shared_from_this());
    }
    
}

void Evaluator::visit(const std::shared_ptr<EqualExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    bool numeric = isNumeric(leftNode->getVal()) && isNumeric(rightNode->getVal());
    bool string = leftNode->getVal().is<Value::STR>() && rightNode->getVal().is<Value::STR>();

    if (!numeric && !string) {
        // TODO: move to error handler at some point
        throw RuntimeException("Cannot check equality with the used types");
    }

    // Evaluates the value of the expression
    node->setVal(leftNode->getVal() == rightNode->getVal());
}

void Evaluator::visit(const std::shared_ptr<ExpoExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    if (!(isNumeric(leftNode->getVal()) && isNumeric(rightNode->getVal()))) {
        // TODO: move to error handler at some point
        throw RuntimeException("Cannot multiply with the used types");
    }

    // Evaluates the value of the expression

    if (leftNode->getVal().is<Value::INT>()) {
        if (rightNode->getVal().is<Value::BOOL>()) {
            node->setVal(std::pow(leftNode->getVal().get<Value::INT>(),
                                  rightNode->getVal().get<Value::BOOL>()));
        } else if (rightNode->getVal().is<Value::INT>()) {
            if (rightNode->getVal().get<Value::INT>() >= 0) {
                node->setVal(static_cast<Value::INT>(std::pow(leftNode->getVal().get<Value::INT>(),
                                                 rightNode->getVal().get<Value::INT>())));
            } else {
                node->setVal(std::pow(leftNode->getVal().get<Value::INT>(),
                                      rightNode->getVal().get<Value::INT>()));
            }
        } else {
            node->setVal(std::pow(leftNode->getVal().get<Value::INT>(),
                                  rightNode->getVal().get<Value::FLOAT>()));
        }
    } else if (leftNode->getVal().is<Value::BOOL>()) {
        if (rightNode->getVal().is<Value::BOOL>()) {
            node->setVal(std::pow(leftNode->getVal().get<Value::INT>(),
                                  rightNode->getVal().get<Value::BOOL>()));
        } else if (rightNode->getVal().is<Value::INT>()) {
            if (rightNode->getVal().get<Value::INT>() >= 0) {
                node->setVal((int)round(std::pow(leftNode->getVal().get<Value::INT>(),
                                                 rightNode->getVal().get<Value::INT>())));
            } else {
                node->setVal(std::pow(leftNode->getVal().get<Value::INT>(),
                                      rightNode->getVal().get<Value::INT>()));
            }
        } else
            std::pow(leftNode->getVal().get<Value::INT>(), rightNode->getVal().get<Value::FLOAT>());
    } else if (leftNode->getVal().is<Value::FLOAT>()) {
        if (rightNode->getVal().is<Value::BOOL>()) {
            node->setVal(std::pow(leftNode->getVal().get<Value::INT>(),
                                  rightNode->getVal().get<Value::BOOL>()));
        } else if (rightNode->getVal().is<Value::INT>()) {
            if (rightNode->getVal().get<Value::INT>() >= 0) {
                node->setVal((int)round(std::pow(leftNode->getVal().get<Value::INT>(),
                                                 rightNode->getVal().get<Value::INT>())));
            } else {
                node->setVal(std::pow(leftNode->getVal().get<Value::INT>(),
                                      rightNode->getVal().get<Value::INT>()));
            }
        } else {
            node->setVal(std::pow(leftNode->getVal().get<Value::INT>(),
                                  rightNode->getVal().get<Value::FLOAT>()));
        }
    } else
        throw RuntimeException("Could not convert string to value of nodes");
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
        std::map<std::string, std::function<bool(const Value &, const Value &)>> ops = {
            {"<", [](const Value &a, const Value &b) { return a < b; }},
            {">", [](const Value &a, const Value &b) { return a > b; }},
            {"==", [](const Value &a, const Value &b) { return a == b; }},
            {"!=", [](const Value &a, const Value &b) { return a != b; }},
            {">=", [](const Value &a, const Value &b) { return a >= b; }},
            {"<=", [](const Value &a, const Value &b) { return a <= b; }},
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
        Value::TABLE newTable = std::make_shared<std::map<Value::STR, Value::COLUMN>>();
        for (const std::pair<const Value::STR, Value::COLUMN> &entry : *table) {
            Value::LIST newData = std::make_shared<std::vector<std::shared_ptr<Value>>>();
            for (Value::INT index : indicesToKeep) {
                newData->emplace_back((*entry.second->data)[index]);
            }

            Value::COLUMN newCol = std::make_shared<Value::COL_STRUCT>();
            newCol->parent = newTable;
            newCol->header = entry.first;
            newCol->data = newData;
            newTable->insert({entry.first, newCol});
        }

        node->setVal(newTable);
    } else {
        throw RuntimeException("Filter operation not allowed for this type");
    }
}

void Evaluator::visit(const std::shared_ptr<GreaterEqualExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    if (!(isNumeric(leftNode->getVal()) && isNumeric(rightNode->getVal()))) {
        // TODO: move to error handler at some point
        throw RuntimeException("Cannot do greater or equal with the used types");
    }
    // Evaluates the value of the expression
    node->setVal(leftNode->getVal() >= rightNode->getVal());
}

void Evaluator::visit(const std::shared_ptr<GreaterExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    if (!(isNumeric(leftNode->getVal()) && isNumeric(rightNode->getVal()))) {
        // TODO: move to error handler at some point
        throw RuntimeException("Cannot do greater than with the used types");
    }

    // Evaluates the value of the expression
    node->setVal(leftNode->getVal() > rightNode->getVal());
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
            throw RuntimeException("Header not found in table");
        }
    } else {
        throw RuntimeException("Invalid index operation");
    }
}

void Evaluator::visit(const std::shared_ptr<IfNode> &node) {
    std::shared_ptr<AstNode> condNode = node->getCondNode();
    std::vector<std::shared_ptr<AstNode>> bodyNodes = node->getBodyNodes();
    std::shared_ptr<AstNode> elseNode = node->getElseNode();

    condNode->accept(shared_from_this());
    
    if (!isNumeric(condNode->getVal())) {
        // TODO: move to error handler later
        throw RuntimeException("Error: Invalid type.");
    }
    else if (condNode->getVal().is<Value::BOOL>() && condNode->getVal().get<Value::BOOL>()) {
        for (size_t i = 0; i < bodyNodes.size(); ++i) { 
            bodyNodes[i]->accept(shared_from_this());
        }
    }
    else if (condNode->getVal().is<Value::INT>() && condNode->getVal().get<Value::INT>()) {
        for (size_t i = 0; i < bodyNodes.size(); ++i) { 
            bodyNodes[i]->accept(shared_from_this());
        }
    }
    else if (condNode->getVal().is<Value::FLOAT>() && condNode->getVal().get<Value::FLOAT>()) {
        for (size_t i = 0; i < bodyNodes.size(); ++i) { 
            bodyNodes[i]->accept(shared_from_this());
        }
    }
    else if (elseNode != 0) {
        elseNode->accept(shared_from_this());
    }
    
}

void Evaluator::visit(const std::shared_ptr<IndexNode> &node) {
    std::shared_ptr<AstNode> identifierNode = node->getLeftNode();
    std::shared_ptr<AstNode> indexNode = node->getRightNode();

    identifierNode->accept(shared_from_this());
    indexNode->accept(shared_from_this());

    if (!indexNode->getVal().is<Value::INT>()) {
        if (indexNode->getVal().is<Value::STR>()) {
            throw RuntimeException(
                "index must be an integer. Did you forget '$' infront?");
        }

        throw RuntimeException("Index must be an integer");
    }

    Value::INT index = indexNode->getVal().get<Value::INT>();

    Value val = identifierNode->getVal();
    if (val.is<Value::STR>()) {
        Value::STR str = val.get<Value::STR>();

        if (index < 0 || static_cast<size_t>(index) >= str.size()) {
            throw RuntimeException("Index out of range");
        }

        node->setVal(Value::STR{str[index]});
    } else if (val.is<Value::LIST>()) {
        Value::LIST list = val.get<Value::LIST>();

        if (index < 0 || static_cast<size_t>(index) >= list->size()) {
            throw RuntimeException("Index out of range");
        }

        node->setVal(*(*list)[index]);
    } else if (val.is<Value::COLUMN>()) {
        Value::COLUMN col = val.get<Value::COLUMN>();

        if (index < 0 || static_cast<size_t>(index) >= col->data->size()) {
            throw RuntimeException("Index out of range");
        }

        node->setVal(*(*col->data)[index]);
    } else {
        throw RuntimeException("Invalid index operation");
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
            throw RuntimeException("Undefined variable \"" + node->getText() + "\"");
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

    if (!(isNumeric(leftNode->getVal()) && isNumeric(rightNode->getVal()))) {
        // TODO: move to error handler at some point
        throw RuntimeException("Cannot do less or equal with the used types");
    }

    // Evaluates the value of the expression
    node->setVal(leftNode->getVal() <= rightNode->getVal());
}

void Evaluator::visit(const std::shared_ptr<LessExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    if (!(isNumeric(leftNode->getVal()) && isNumeric(rightNode->getVal()))) {
        // TODO: move to error handler at some point
        throw RuntimeException("Cannot do less than with the used types");
    }

    // Evaluates the value of the expression
    node->setVal(leftNode->getVal() < rightNode->getVal());
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

    if (!(isNumeric(leftNode->getVal()) && isNumeric(rightNode->getVal()))) {
        // TODO: move to error handler at some point
        throw RuntimeException("Cannot do substraction with the used types");
    }

    // Evaluates the value of the expression
    if (leftNode->getVal().is<Value::INT>()) {
        if (rightNode->getVal().is<Value::BOOL>()) {
            node->setVal(leftNode->getVal().get<Value::INT>() -
                         rightNode->getVal().get<Value::BOOL>());
        } else if (rightNode->getVal().is<Value::INT>()) {
            node->setVal(leftNode->getVal().get<Value::INT>() -
                         rightNode->getVal().get<Value::INT>());
        } else {
            node->setVal(leftNode->getVal().get<Value::INT>() -
                         rightNode->getVal().get<Value::FLOAT>());
        }
    } else if (leftNode->getVal().is<Value::FLOAT>()) {
        if (rightNode->getVal().is<Value::BOOL>()) {
            node->setVal(leftNode->getVal().get<Value::FLOAT>() -
                         rightNode->getVal().get<Value::BOOL>());
        } else if (rightNode->getVal().is<Value::INT>()) {
            node->setVal(leftNode->getVal().get<Value::FLOAT>() -
                         rightNode->getVal().get<Value::INT>());
        } else {
            node->setVal(leftNode->getVal().get<Value::FLOAT>() -
                         rightNode->getVal().get<Value::FLOAT>());
        }
    } else if (leftNode->getVal().is<Value::BOOL>()) {
        if (rightNode->getVal().is<Value::BOOL>()) {
            node->setVal(leftNode->getVal().get<Value::BOOL>() -
                         rightNode->getVal().get<Value::BOOL>());
        } else if (rightNode->getVal().is<Value::INT>()) {
            node->setVal(leftNode->getVal().get<Value::BOOL>() -
                         rightNode->getVal().get<Value::INT>());
        } else {
            node->setVal(leftNode->getVal().get<Value::BOOL>() -
                         rightNode->getVal().get<Value::FLOAT>());
        }
    } else
        throw RuntimeException("Couldn't convert string to value of nodes");
}

void Evaluator::visit(const std::shared_ptr<MinusNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> childNode = node->getChildNode();
    childNode->accept(shared_from_this());

    if (!isNumeric(childNode->getVal())) {
        // TODO: move to error handler at some point
        throw RuntimeException("Cannot do substraction with the used type");
    }

    // Evaluates the value of the expression
    if (childNode->getVal().is<Value::INT>()) {
        node->setVal(-childNode->getVal().get<Value::INT>());
    } else if (childNode->getVal().is<Value::FLOAT>()) {
        node->setVal(-childNode->getVal().get<Value::FLOAT>());
    } else if (childNode->getVal().is<Value::BOOL>()) {
        node->setVal(-childNode->getVal().get<Value::BOOL>());
    } else
        throw RuntimeException("Couldn't convert string to value of nodes");
}

void Evaluator::visit(const std::shared_ptr<ModExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    if (!(isNumeric(leftNode->getVal()) && isNumeric(rightNode->getVal()))) {
        // TODO: move to error handler at some point
        throw RuntimeException("Cannot do modulo with the used types");
    }

    // Divide with 0 check
    if (rightNode->getVal().is<Value::INT>()) {
        if (rightNode->getVal().get<Value::INT>() == 0) {
            throw RuntimeException("Cannot divide with 0");
        }
    } else if (rightNode->getVal().is<Value::FLOAT>()) {
        if (rightNode->getVal().get<Value::FLOAT>() == 0) {
            throw RuntimeException("Cannot divide with 0");
        }
    } else if (rightNode->getVal().is<Value::BOOL>()) {
        if (rightNode->getVal().get<Value::BOOL>() == 0)
            throw RuntimeException("Cannot divide with 0");
    } else if (rightNode->getVal().is<Value::COLUMN>()){
        // Checks if both columns are the same size
        if (rightNode->getVal().is<Value::COLUMN>())
            for (int i = 0; i < rightNode->getVal().get<Value::COLUMN>()->data->size(); i++) {
                if ((*rightNode->getVal().get<Value::COLUMN>()->data)[i] == 0)
                throw RuntimeException("Cannot divide with 0");
            }
    }
    
    // Evaluates the value of the expression
    if (leftNode->getVal().is<Value::INT>()) {
        if (rightNode->getVal().is<Value::BOOL>()) {
            node->setVal(leftNode->getVal().get<Value::INT>() %
                        rightNode->getVal().get<Value::BOOL>());
        } else if (rightNode->getVal().is<Value::INT>()) {
            node->setVal(leftNode->getVal().get<Value::INT>() %
                        rightNode->getVal().get<Value::INT>());
        } else {
            node->setVal(fmod(leftNode->getVal().get<Value::INT>(),
                            rightNode->getVal().get<Value::FLOAT>()));
        }
    } else if (leftNode->getVal().is<Value::FLOAT>()) {
        if (rightNode->getVal().is<Value::BOOL>()) {
            node->setVal(fmod(leftNode->getVal().get<Value::FLOAT>(),
                            rightNode->getVal().get<Value::BOOL>()));
        } else if (rightNode->getVal().is<Value::INT>()) {
            node->setVal(fmod(leftNode->getVal().get<Value::FLOAT>(),
                            rightNode->getVal().get<Value::INT>()));
        } else {
            node->setVal(fmod(leftNode->getVal().get<Value::FLOAT>(),
                            rightNode->getVal().get<Value::BOOL>()));
        }
    } else if (leftNode->getVal().is<Value::BOOL>()) {
        if (rightNode->getVal().is<Value::BOOL>()) {
            node->setVal(leftNode->getVal().get<Value::BOOL>() %
                        rightNode->getVal().get<Value::BOOL>());
        } else if (rightNode->getVal().is<Value::INT>()) {
            node->setVal(leftNode->getVal().get<Value::BOOL>() %
                        rightNode->getVal().get<Value::INT>());
        } else {
            node->setVal(fmod(leftNode->getVal().get<Value::BOOL>(),
                            rightNode->getVal().get<Value::FLOAT>()));
        }
    } else {
        throw RuntimeException("Couldn't convert string to value of nodes");
    }
}

void Evaluator::visit(const std::shared_ptr<MultExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    if (!((isNumeric(leftNode->getVal()) && isNumeric(rightNode->getVal())) ||
          (leftNode->getVal().is<Value::INT>() && rightNode->getVal().is<Value::STR>()) ||
          (leftNode->getVal().is<Value::STR>() && rightNode->getVal().is<Value::INT>()) ||
          (leftNode->getVal().is<Value::STR>() && rightNode->getVal().is<Value::BOOL>()) ||
          (leftNode->getVal().is<Value::BOOL>() && rightNode->getVal().is<Value::STR>()))) {
        // TODO: move to error handler at some point
        throw RuntimeException("Cannot multiply with the used types");
    }

    // Evaluates the value of the expression
    if (leftNode->getVal().is<Value::INT>()) {
        if (rightNode->getVal().is<Value::BOOL>()) {
            node->setVal(leftNode->getVal().get<Value::INT>() *
                         rightNode->getVal().get<Value::BOOL>());
        } else if (rightNode->getVal().is<Value::INT>()) {
            node->setVal(leftNode->getVal().get<Value::INT>() *
                         rightNode->getVal().get<Value::INT>());
        } else if (rightNode->getVal().is<Value::FLOAT>()) {
            node->setVal(leftNode->getVal().get<Value::INT>() *
                         rightNode->getVal().get<Value::FLOAT>());
        } else {
            node->setVal("");
            for (Value::INT i = 0; i < leftNode->getVal().get<Value::INT>(); i++)
                node->setVal(node->getVal().get<Value::STR>() +
                             rightNode->getVal().get<Value::STR>());
        }
    } else if (leftNode->getVal().is<Value::FLOAT>()) {
        if (rightNode->getVal().is<Value::BOOL>()) {
            node->setVal(leftNode->getVal().get<Value::FLOAT>() *
                         rightNode->getVal().get<Value::BOOL>());
        } else if (rightNode->getVal().is<Value::INT>()) {
            node->setVal(leftNode->getVal().get<Value::FLOAT>() *
                         rightNode->getVal().get<Value::INT>());
        } else {
            node->setVal(leftNode->getVal().get<Value::FLOAT>() *
                         rightNode->getVal().get<Value::FLOAT>());
        }
    } else if (leftNode->getVal().is<Value::BOOL>()) {
        if (rightNode->getVal().is<Value::BOOL>()) {
            node->setVal(leftNode->getVal().get<Value::BOOL>() *
                         rightNode->getVal().get<Value::BOOL>());
        } else if (rightNode->getVal().is<Value::INT>()) {
            node->setVal(leftNode->getVal().get<Value::BOOL>() *
                         rightNode->getVal().get<Value::INT>());
        } else if (rightNode->getVal().is<Value::FLOAT>()) {
            node->setVal(leftNode->getVal().get<Value::BOOL>() *
                         rightNode->getVal().get<Value::FLOAT>());
        } else {
            node->setVal("");
            for (size_t i = 0; i < leftNode->getVal().get<Value::BOOL>(); i++)
                node->setVal(node->getVal().get<Value::STR>() +
                             rightNode->getVal().get<Value::STR>());
        }
    } else if (leftNode->getVal().is<Value::STR>()) {
        node->setVal("");
        if (rightNode->getVal().is<Value::INT>()) {
            for (Value::INT i = 0; i < rightNode->getVal().get<Value::INT>(); i++)
                node->setVal(node->getVal().get<Value::STR>() +
                             leftNode->getVal().get<Value::STR>());
        } else {
            for (size_t i = 0; i < rightNode->getVal().get<Value::BOOL>(); i++)
                node->setVal(node->getVal().get<Value::STR>() +
                             leftNode->getVal().get<Value::STR>());
        }
    } else
        throw RuntimeException("Couldn't convert string to value of nodes");
}

void Evaluator::visit(const std::shared_ptr<NotEqualExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    bool numeric = isNumeric(leftNode->getVal()) && isNumeric(rightNode->getVal());
    bool string = leftNode->getVal().is<Value::STR>() && rightNode->getVal().is<Value::STR>();

    if (!numeric && !string) {
        // TODO: move to error handler at some point
        throw RuntimeException("Cannot dp logical not equal with the used types");
    }

    // Evaluates the value of the expression
    if (leftNode->getVal().is<Value::INT>()) {
        if (rightNode->getVal().is<Value::BOOL>()) {
            node->setVal(leftNode->getVal().get<Value::INT>() !=
                         rightNode->getVal().get<Value::BOOL>());
        } else if (rightNode->getVal().is<Value::INT>()) {
            node->setVal(leftNode->getVal().get<Value::INT>() !=
                         rightNode->getVal().get<Value::INT>());
        } else {
            node->setVal(leftNode->getVal().get<Value::INT>() !=
                         rightNode->getVal().get<Value::FLOAT>());
        }
    } else if (leftNode->getVal().is<Value::FLOAT>()) {
        if (rightNode->getVal().is<Value::BOOL>()) {
            node->setVal(leftNode->getVal().get<Value::FLOAT>() !=
                         rightNode->getVal().get<Value::BOOL>());
        } else if (rightNode->getVal().is<Value::INT>()) {
            node->setVal(leftNode->getVal().get<Value::FLOAT>() !=
                         rightNode->getVal().get<Value::INT>());
        } else {
            node->setVal(leftNode->getVal().get<Value::FLOAT>() !=
                         rightNode->getVal().get<Value::FLOAT>());
        }
    } else if (leftNode->getVal().is<Value::BOOL>()) {
        if (rightNode->getVal().is<Value::BOOL>()) {
            node->setVal(leftNode->getVal().get<Value::BOOL>() !=
                         rightNode->getVal().get<Value::BOOL>());
        } else if (rightNode->getVal().is<Value::INT>()) {
            node->setVal(leftNode->getVal().get<Value::BOOL>() !=
                         rightNode->getVal().get<Value::INT>());
        } else {
            node->setVal(leftNode->getVal().get<Value::BOOL>() !=
                         rightNode->getVal().get<Value::FLOAT>());
        }
    } else if (leftNode->getVal().is<Value::STR>()) {
        node->setVal(leftNode->getVal().get<Value::STR>() != rightNode->getVal().get<Value::STR>());
    } else
        throw RuntimeException("Couldn't convert string to value of nodes");
}

void Evaluator::visit(const std::shared_ptr<NotNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> childNode = node->getChildNode();
    childNode->accept(shared_from_this());

    if (!(isNumeric(childNode->getVal()))) {
        // TODO: move to error handler at some point
        throw RuntimeException("Cannot negate the used type");
    }

    // Evaluates the value of the expression
    if (childNode->getVal().is<Value::INT>()) {
        if (childNode->getVal().get<Value::INT>() != false)
            node->setVal(false);
        else
            node->setVal(true);
    } else if (childNode->getVal().is<Value::INT>()) {
        if (childNode->getVal().get<Value::FLOAT>() != false)
            node->setVal(false);
        else
            node->setVal(true);
    } else if (childNode->getVal().is<Value::BOOL>()) {
        if (childNode->getVal().get<Value::BOOL>() != false)
            node->setVal(false);
        else
            node->setVal(true);
    } else
        throw RuntimeException("Couldn't evaluate negation");
}

void Evaluator::visit(const std::shared_ptr<OrExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    if (!leftNode->getVal().is<Value::BOOL>() || !rightNode->getVal().is<Value::BOOL>()) {
        // TODO: move to error handler at some point
        throw RuntimeException("Cannot do logical or with the used types");
    }

    // Evaluates the value of the expression
    // Evaluates the value of the expression
    if (leftNode->getVal().is<Value::BOOL>()) {
        if (rightNode->getVal().is<Value::BOOL>())
            if (leftNode->getVal().get<Value::BOOL>() == true ||
            rightNode->getVal().get<Value::BOOL>() == true) 
                node->setVal(true);
            else node->setVal(false);
        else if (rightNode->getVal().is<Value::INT>()) 
            if (leftNode->getVal().get<Value::BOOL>() == true ||
            rightNode->getVal().get<Value::INT>() == true)
                node->setVal(true);
            else node->setVal(false);
        else if (leftNode->getVal().get<Value::BOOL>() == true ||
            rightNode->getVal().get<Value::FLOAT>() == true)
            node->setVal(true);
        else node->setVal (false);
    } else if (leftNode->getVal().is<Value::INT>()) {
        if (rightNode->getVal().is<Value::BOOL>())
            if (leftNode->getVal().get<Value::INT>() == true ||
            rightNode->getVal().get<Value::BOOL>() == true) 
                node->setVal(true);
            else node->setVal(false);
        else if (rightNode->getVal().is<Value::INT>()) 
            if (leftNode->getVal().get<Value::INT>() == true ||
            rightNode->getVal().get<Value::INT>() == true)
                node->setVal(true);
            else node->setVal(false);
        else if (leftNode->getVal().get<Value::INT>() == true ||
            rightNode->getVal().get<Value::FLOAT>() == true)
            node->setVal(true);
        else node->setVal (false);
    } else if (leftNode->getVal().is<Value::FLOAT>()) {
        if (rightNode->getVal().is<Value::BOOL>())
            if (leftNode->getVal().get<Value::FLOAT>() == true ||
            rightNode->getVal().get<Value::BOOL>() == true) 
                node->setVal(true);
            else node->setVal(false);
        else if (rightNode->getVal().is<Value::INT>()) 
            if (leftNode->getVal().get<Value::FLOAT>() == true ||
            rightNode->getVal().get<Value::INT>() == true)
                node->setVal(true);
            else node->setVal(false);
        else if (leftNode->getVal().get<Value::FLOAT>() == true ||
            rightNode->getVal().get<Value::FLOAT>() == true)
            node->setVal(true);
        else node->setVal (false);
    } else
        throw RuntimeException("Could not convert string to value of nodes");
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

    if (!((isNumeric(leftNode->getVal()) && isNumeric(rightNode->getVal())) ||
          (leftNode->getVal().is<Value::STR>() && rightNode->getVal().is<Value::STR>()))) {
        // TODO: move to error handler at some point
        throw RuntimeException("Cannot do addition with the used types");
    }

    // Evaluates the value of the expression
    if (leftNode->getVal().is<Value::INT>()) {
        if (rightNode->getVal().is<Value::BOOL>()) {
            node->setVal(leftNode->getVal().get<Value::INT>() +
                         rightNode->getVal().get<Value::BOOL>());
        } else if (rightNode->getVal().is<Value::INT>()) {
            node->setVal(leftNode->getVal().get<Value::INT>() +
                         rightNode->getVal().get<Value::INT>());
        } else {
            node->setVal(leftNode->getVal().get<Value::INT>() +
                         rightNode->getVal().get<Value::FLOAT>());
        }
    } else if (leftNode->getVal().is<Value::FLOAT>()) {
        if (rightNode->getVal().is<Value::BOOL>()) {
            node->setVal(leftNode->getVal().get<Value::FLOAT>() +
                         rightNode->getVal().get<Value::BOOL>());
        } else if (rightNode->getVal().is<Value::INT>()) {
            node->setVal(leftNode->getVal().get<Value::FLOAT>() +
                         rightNode->getVal().get<Value::INT>());
        } else {
            node->setVal(leftNode->getVal().get<Value::FLOAT>() +
                         rightNode->getVal().get<Value::FLOAT>());
        }
    } else if (leftNode->getVal().is<Value::BOOL>()) {
        if (rightNode->getVal().is<Value::BOOL>()) {
            node->setVal(leftNode->getVal().get<Value::BOOL>() +
                         rightNode->getVal().get<Value::BOOL>());
        } else if (rightNode->getVal().is<Value::INT>()) {
            node->setVal(leftNode->getVal().get<Value::BOOL>() +
                         rightNode->getVal().get<Value::INT>());
        } else {
            node->setVal(leftNode->getVal().get<Value::BOOL>() +
                         rightNode->getVal().get<Value::FLOAT>());
        }
    } else if (leftNode->getVal().is<Value::STR>()) {
        node->setVal(leftNode->getVal().get<Value::STR>() + rightNode->getVal().get<Value::STR>());
    } else
        throw RuntimeException("Couldn't convert string to value of nodes");
}

void Evaluator::visit(const std::shared_ptr<PlusNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> childNode = node->getChildNode();
    childNode->accept(shared_from_this());

    if (!isNumeric(childNode->getVal())) {
        // TODO: move to error handler at some point
        throw RuntimeException("Cannot use unary plus with the used type");
    }

    // Evaluates the value of the expression
    if (childNode->getVal().is<Value::INT>()) {
        node->setVal(childNode->getVal().get<Value::INT>());
    } else if (childNode->getVal().is<Value::FLOAT>()) {
        node->setVal(childNode->getVal().get<Value::FLOAT>());
    } else if (childNode->getVal().is<Value::BOOL>()) {
        node->setVal(childNode->getVal().get<Value::BOOL>());
    } else
        throw RuntimeException("Couldn't convert string to value of nodes");
}

void Evaluator::visit(const std::shared_ptr<ProcCallNode> &node) {
    std::shared_ptr<LeafNode> procNode = std::dynamic_pointer_cast<LeafNode>(node->getChildNode());

    Procedure *proc = nullptr;
    try {
        proc = ptable.lookup(procNode->getText(), node->getChildNodeList().size());
    } catch (const std::out_of_range &e) {
        throw RuntimeException("Undefined procedure \"" + procNode->getText() + "\"");
    }

    // Check if amount of arguments is correct
    if (proc->getArity() != node->getChildNodeList().size()) {
        throw RuntimeException("Procedure \"" + procNode->getText() +
                                 "\" called with incorrect number of arguments");
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
        // Abusing try catch to break out of loop when we evaluated return statement
        try {
            bodyNodes[i]->accept(shared_from_this());
        } catch (const ReturnValue &e) {
            node->setVal(e.getVal());
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
    throw ReturnValue(childNode->getVal());
}

void Evaluator::visit(const std::shared_ptr<TableNode> &node) {
    Value::TABLE table = std::make_shared<std::map<Value::STR, Value::COLUMN>>();
    std::vector<std::shared_ptr<AstNode>> childNodes = node->getChildNodeList();

    long size = 0;
    bool sizeSet = false;
    for (std::shared_ptr<AstNode> &child : childNodes) {
        std::shared_ptr<ColumnNode> columnNode = std::dynamic_pointer_cast<ColumnNode>(child);
        columnNode->accept(shared_from_this());

        if (!columnNode->getLeftNode()->getVal().is<Value::STR>()) {
            throw RuntimeException("Table key must be a string");
        }

        Value::STR header = columnNode->getLeftNode()->getVal().get<Value::STR>();

        if (!columnNode->getRightNode()->getVal().is<Value::LIST>()) {
            throw RuntimeException("Table value must be a list");
        }

        Value::LIST val = columnNode->getRightNode()->getVal().get<Value::LIST>();

        Value::COLUMN col = std::make_shared<Value::COL_STRUCT>();
        col->parent = table;
        col->header = header;
        col->data = val;

        if (!sizeSet) {
            sizeSet = true;
            size = val->size();
        } else if (val->size() != static_cast<size_t>(size)) {
            throw RuntimeException("All columns in a table must have the same size");
        }

        table->insert({header, col});
    }

    node->setVal(table);
}

void Evaluator::visit(const std::shared_ptr<UnionExprNode> &node) {}

void Evaluator::visit(const std::shared_ptr<WhileNode> &node) {
    std::shared_ptr<AstNode> condNode = node->getChildNode();
    std::vector<std::shared_ptr<AstNode>> bodyNodes = node->getChildNodeList();

    condNode->accept(shared_from_this());

    if (!isNumeric(condNode->getVal())) {
        // TODO: move to error handler later
        throw RuntimeException("Error: Invalid type.");
    }
    else if (condNode->getVal().is<Value::BOOL>() && condNode->getVal().get<Value::BOOL>()) {
        while(condNode->getVal().get<Value::BOOL>()) {
            for (size_t i = 0; i < bodyNodes.size(); ++i) { 
                bodyNodes[i]->accept(shared_from_this());
            }
            condNode->accept(shared_from_this());
        }
    }
    else if (condNode->getVal().is<Value::INT>() && condNode->getVal().get<Value::INT>()) {
        while(condNode->getVal().get<Value::INT>()) {
            for (size_t i = 0; i < bodyNodes.size(); ++i) { 
                bodyNodes[i]->accept(shared_from_this());
            }
            condNode->accept(shared_from_this());
        }
    }
    else if (condNode->getVal().is<Value::FLOAT>() && condNode->getVal().get<Value::FLOAT>()) {
        while(condNode->getVal().get<Value::FLOAT>()) {
            for (size_t i = 0; i < bodyNodes.size(); ++i) { 
                bodyNodes[i]->accept(shared_from_this());
            }
            condNode->accept(shared_from_this());
        }
    }
}

void Evaluator::initPtable() {
    Procedure::ProcType print1 = [](std::vector<std::shared_ptr<AstNode>> args) {
        std::cout << args[0]->getVal().toString() << '\n';
        return nullptr;
    };

    Procedure::ProcType input0 = []([[maybe_unused]] std::vector<std::shared_ptr<AstNode>> args) {
        std::string inputStr;
        std::getline(std::cin, inputStr);
        return inputStr;
    };

    Procedure::ProcType input1 = [input0](std::vector<std::shared_ptr<AstNode>> args) {
        std::cout << args[0]->getVal().toString();
        return input0(args);
    };

    Procedure::ProcType type1 = [](std::vector<std::shared_ptr<AstNode>> args) {
        return args[0]->getVal().toTypeString();
    };

    Procedure::ProcType str1 = [](std::vector<std::shared_ptr<AstNode>> args) {
        return args[0]->getVal().toString();
    };

    Procedure::ProcType len1 = [](std::vector<std::shared_ptr<AstNode>> args) {
        Value val = args[0]->getVal();

        if (val.is<Value::STR>()) {
            return static_cast<Value::INT>(val.get<Value::STR>().size());
        } else if (val.is<Value::LIST>()) {
            return static_cast<Value::INT>(val.get<Value::LIST>()->size());
        } else if (val.is<Value::TABLE>()) {
            return static_cast<Value::INT>(val.get<Value::TABLE>()->size());
        } else if (val.is<Value::COLUMN>()) {
            return static_cast<Value::INT>(val.get<Value::COLUMN>()->data->size());
        }

        throw RuntimeException("Len called with invalid type " + val.toTypeString() + '\n');
    };

    Procedure::ProcType ceil1 = [](std::vector<std::shared_ptr<AstNode>> args) {
        Value val = args[0]->getVal();

        if (val.is<Value::FLOAT>()) {
            return static_cast<Value::INT>(std::ceil(val.get<Value::FLOAT>()));
        }

        throw RuntimeException("Ceil called with invalid type " + val.toTypeString() + ". Expected: " + Value(0.0).toTypeString());
    };
    
    Procedure::ProcType floor1 = [](std::vector<std::shared_ptr<AstNode>> args) {
        Value val = args[0]->getVal();

        if (val.is<Value::FLOAT>()) {
            return static_cast<Value::INT>(std::floor(val.get<Value::FLOAT>()));
        }

        throw RuntimeException("Floor called with invalid type " + val.toTypeString() + ". Expected: " + Value(0.0).toTypeString());
    };

    Procedure::ProcType readFile1 = [](std::vector<std::shared_ptr<AstNode>> args) {
        Value fileName = args[0]->getVal();

        if (!fileName.is<Value::STR>()) {
            throw RuntimeException("ReadFile called with invalid type " + fileName.toTypeString() + ". Expected: " + Value("").toTypeString() + '\n');
        }

        std::filesystem::path filePath = fileName.get<Value::STR>();
        std::ifstream file(filePath);
        if (!file.is_open()) {
            throw RuntimeException("Could not open file \"" + fileName.toString() + "\"");
        }

        std::string fileContents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

        return fileContents;
    };

    Procedure::ProcType writeFile2 = [](std::vector<std::shared_ptr<AstNode>> args) {
        Value fileName = args[0]->getVal();
        Value content = args[1]->getVal();

        if (!content.is<Value::STR>() || !fileName.is<Value::STR>()) {
            throw RuntimeException("WriteFile called with invalid types");
        }

        std::filesystem::path filePath = fileName.get<Value::STR>();
        std::ofstream file(filePath);
        if (!file.is_open()) {
            throw RuntimeException("Could not open file \"" + fileName.get<Value::STR>() + "\"");
        }

        file << content.get<Value::STR>();

        return nullptr;
    };

    Procedure::ProcType readTable3 = [](std::vector<std::shared_ptr<AstNode>> args) {
        Value fileName = args[0]->getVal();
        Value delimiterVal = args[1]->getVal();
        Value dataTypesVal = args[2]->getVal();

        if (!fileName.is<Value::STR>()) {
            throw RuntimeException("ReadTable called with invalid type " + fileName.toTypeString() + ". Expected: " + Value("").toTypeString() + '\n');
        }

        if (!delimiterVal.is<Value::STR>()) {
            throw RuntimeException("ReadTable called with invalid type " + delimiterVal.toTypeString() + ". Expected: " + Value("").toTypeString() + '\n');
        }

        if (delimiterVal.get<Value::STR>().size() != 1) {
            throw RuntimeException("Delimiter must be a string of size 1");
        }

        if (!dataTypesVal.is<Value::LIST>()) {
            throw RuntimeException("ReadTable called with invalid type " + dataTypesVal.toTypeString() + ". Expected: " + Value({}).toTypeString() + '\n');
        }

        char delimiter = delimiterVal.get<Value::STR>()[0];
        std::filesystem::path filePath = fileName.get<Value::STR>();
        std::ifstream file(filePath);
        if (!file.is_open()) {
            throw RuntimeException("Could not open file \"" + fileName.toString() + "\"");
        }

        bool isFirstLine = true;
        std::string line;
        Value::TABLE table = std::make_shared<std::map<Value::STR, Value::COLUMN>>();
        std::vector<Value::COLUMN> cols;
        std::vector<Value::STR> headers;
        while (std::getline(file, line)) {
            // Split line by delimiter
            bool inQuotes = false;
            std::vector<Value::STR> values;
            Value::STR value;
            for (char c : line) {
                if (c == '"') {
                    inQuotes = !inQuotes;
                } else if (c == delimiter && !inQuotes) {
                    values.push_back(value);
                    value.clear();
                } else {
                    value += c;
                }
            }

            if (!value.empty()) {
                values.push_back(value);
            }

            // If first line we store as headers
            if (isFirstLine) {
                isFirstLine = false;
                headers = values;

                // Initialize columns
                for (size_t i = 0; i < headers.size(); ++i) {
                    cols.emplace_back(std::make_shared<Value::COL_STRUCT>());
                    cols[i]->data = std::make_shared<std::vector<std::shared_ptr<Value>>>();
                }
            } else {
                for (size_t i = 0; i < headers.size(); ++i) {
                    if (i >= values.size() || values[i].empty()) {
                        cols[i]->data->emplace_back(std::make_shared<Value>(nullptr));
                    } else {
                        Value::LIST dataTypes = dataTypesVal.get<Value::LIST>();
                        if (dataTypes->empty()) {
                            cols[i]->data->emplace_back(std::make_shared<Value>(values[i]));
                        } else {
                            Value::STR dataType = dataTypes->at(i)->get<Value::STR>();
                            if (dataType == "int") {
                                cols[i]->data->emplace_back(std::make_shared<Value>(std::stol(values[i])));
                            } else if (dataType == "float") {
                                cols[i]->data->emplace_back(std::make_shared<Value>(std::stod(values[i])));
                            } else if (dataType == "bool") {
                                bool isTrue = values[i] == "True" || values[i] != "0";
                                cols[i]->data->emplace_back(std::make_shared<Value>(isTrue));
                            } else if (dataType == "NoneType") {
                                cols[i]->data->emplace_back(std::make_shared<Value>(nullptr));
                            } else if (dataType == "str") {
                                cols[i]->data->emplace_back(std::make_shared<Value>(values[i]));
                            } else if (dataType == "list") {
                                throw RuntimeException("Type \"lists\" not supported when loading table from file");
                            } else if (dataType == "table") {
                                throw RuntimeException("Type \"table\" not supported when loading table from file");
                            } else if (dataType == "column") {
                                throw RuntimeException("Data can not be explicitly converted to type \"column\"");
                            } else {
                                throw RuntimeException("Trying to convert to invalid data type \"" + dataType + "\"");
                            }
                        }
                    }

                    // If header is missing then we generate a default one to ensure uniqueness
                    if (headers[i].empty()) {
                        std::hash<std::size_t> hash;
                        std::string hashStr = "id" + std::to_string(hash(i));
                        
                        // While the hash is already in headers vector we make a new one to avoid collision
                        size_t j = i;
                        while (std::count(headers.begin(), headers.end(), hashStr)) {
                            ++j;
                            hashStr = "id" + std::to_string(hash(j));
                        }

                        headers[i] = hashStr;
                    }

                    cols[i]->header = headers[i];
                    cols[i]->parent = table;
                }
            }
        }

        // Insert columns into table
        for (size_t i = 0; i < headers.size(); ++i) {
            table->insert({headers[i], cols[i]});
        }

        return table;
    };

    Procedure::ProcType readTable2 = [readTable3](std::vector<std::shared_ptr<AstNode>> args) {
        std::shared_ptr<LeafNode> dataTypes = std::make_shared<LeafNode>(nullptr);
        dataTypes->setVal(std::make_shared<std::vector<std::shared_ptr<Value>>>());
        args.emplace_back(dataTypes);
        return readTable3(args);
    };

    Procedure::ProcType readTable1 = [readTable2](std::vector<std::shared_ptr<AstNode>> args) {
        std::shared_ptr<LeafNode> delim = std::make_shared<LeafNode>(nullptr);
        delim->setVal(Value(","));
        args.emplace_back(delim);
        return readTable2(args);
    };

    Procedure::ProcType writeTable3 = [](std::vector<std::shared_ptr<AstNode>> args) {
        Value fileName = args[0]->getVal();
        Value table = args[1]->getVal();
        Value delimiterVal = args[2]->getVal();

        if (!fileName.is<Value::STR>()) {
            throw RuntimeException("WriteTable called with invalid type " + fileName.toTypeString() + ". Expected: " + Value("").toTypeString() + '\n');
        }

        if (!table.is<Value::TABLE>()) {
            throw RuntimeException("WriteTable called with invalid type " + table.toTypeString() + ". Expected: " + Value("").toTypeString() + '\n');
        }

        if (!delimiterVal.is<Value::STR>()) {
            throw RuntimeException("WriteTable called with invalid type " + delimiterVal.toTypeString() + ". Expected: " + Value("").toTypeString() + '\n');
        }


        if (delimiterVal.get<Value::STR>().size() != 1) {
            throw RuntimeException("Delimiter must be a string of size 1");
        }

        char delimiter = delimiterVal.get<Value::STR>()[0];

        std::filesystem::path filePath = fileName.get<Value::STR>();
        std::ofstream file(filePath);
        if (!file.is_open()) {
            throw RuntimeException("Could not open file \"" + fileName.toString() + "\"");
        }

        // Write headers
        for (const std::pair<const Value::STR, Value::COLUMN> &entry : *table.get<Value::TABLE>()) {
            file << entry.first << delimiter;
        }

        // Overwrite last delimiter
        if (!table.get<Value::TABLE>()->empty()) {
            file.seekp(-1, std::ios_base::end);
        }

        file << '\n';

        // Write data
        for (size_t i = 0; i < table.get<Value::TABLE>()->begin()->second->data->size(); ++i) {
            std::string entryStr;
            for (const std::pair<const Value::STR, Value::COLUMN> &entry : *table.get<Value::TABLE>()) {
                Value::STR val = (*entry.second->data)[i]->toString();
                entryStr += val + delimiter;
            }

            // Overwrite last delimiter
            if (!table.get<Value::TABLE>()->empty()) {
                entryStr.pop_back();
            }

            file << entryStr << '\n';
        }

        return nullptr;
    };

    Procedure::ProcType writeTable2 = [writeTable3](std::vector<std::shared_ptr<AstNode>> args) {
        std::shared_ptr<LeafNode> delim = std::make_shared<LeafNode>(nullptr);
        delim->setVal(Value(","));
        args.emplace_back(delim);
        return writeTable3(args);
    };

    ptable.bind(Procedure("print", {"msg"}, print1));
    ptable.bind(Procedure("input", {}, input0));
    ptable.bind(Procedure("input", {"msg"}, input1));
    ptable.bind(Procedure("type", {"x"}, type1));
    ptable.bind(Procedure("str", {"x"}, str1));
    ptable.bind(Procedure("len", {"x"}, len1));
    ptable.bind(Procedure("ceil", {"x"}, ceil1));
    ptable.bind(Procedure("floor", {"x"}, floor1));
    ptable.bind(Procedure("readFile", {"filename"}, readFile1));
    ptable.bind(Procedure("writeFile", {"filename", "content"}, writeFile2));
    ptable.bind(Procedure("readTable", {"filename"}, readTable1));
    ptable.bind(Procedure("readTable", {"filename", "delimiter"}, readTable2));
    ptable.bind(Procedure("readTable", {"filename", "delimiter", "dataTypes"}, readTable3));
    ptable.bind(Procedure("writeTable", {"filename", "table"}, writeTable2));
    ptable.bind(Procedure("writeTable", {"filename", "table", "delimiter"}, writeTable3));
}

