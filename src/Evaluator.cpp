#include "Evaluator.hpp"

#include <cmath>
#include <string>
#include <utility>

using namespace dplsrc;

void Evaluator::visit(const std::shared_ptr<AndExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    if (leftNode->getVal().is<Value::COLUMN>() || rightNode->getVal().is<Value::COLUMN>()) {
        // TODO: move to error handler at some point
        throw RuntimeException("Cannot do logical and with the used types");
    }

    // Evaluates the value of the expression
    if (leftNode->getVal().is<Value::BOOL>()) {
        if (rightNode->getVal().is<Value::BOOL>()) {
            if (leftNode->getVal().get<Value::BOOL>() && rightNode->getVal().get<Value::BOOL>()) {
                node->setVal(true);
            } else {
                node->setVal(false);
            }
        } else if (rightNode->getVal().is<Value::INT>()) {
            if (leftNode->getVal().get<Value::BOOL>() &&
                static_cast<bool>(rightNode->getVal().get<Value::INT>())) {
                node->setVal(true);
            } else {
                node->setVal(false);
            }
        } else if (leftNode->getVal().get<Value::BOOL>() &&
                   static_cast<bool>(rightNode->getVal().get<Value::FLOAT>())) {
            node->setVal(true);
        } else if (rightNode->getVal().is<Value::STR>() || rightNode->getVal().is<Value::LIST>()) {
            node->setVal(rightNode->getVal());
        } else {
            node->setVal(false);
        }
    } else if (leftNode->getVal().is<Value::INT>()) {
        if (rightNode->getVal().is<Value::BOOL>()) {
            if (static_cast<bool>(leftNode->getVal().get<Value::INT>()) &&
                rightNode->getVal().get<Value::BOOL>()) {
                node->setVal(true);
            } else {
                node->setVal(false);
            }
        } else if (rightNode->getVal().is<Value::INT>()) {
            if (static_cast<bool>(leftNode->getVal().get<Value::INT>()) &&
                static_cast<bool>(rightNode->getVal().get<Value::INT>())) {
                node->setVal(true);
            } else {
                node->setVal(false);
            }
        } else if (static_cast<bool>(leftNode->getVal().get<Value::INT>()) &&
                   static_cast<bool>(rightNode->getVal().get<Value::FLOAT>())) {
            node->setVal(true);
        } else if (rightNode->getVal().is<Value::STR>() || rightNode->getVal().is<Value::LIST>()) {
            node->setVal(rightNode->getVal());
        } else {
            node->setVal(false);
        }
    } else if (leftNode->getVal().is<Value::FLOAT>()) {
        if (rightNode->getVal().is<Value::BOOL>()) {
            if (static_cast<bool>(leftNode->getVal().get<Value::FLOAT>()) &&
                rightNode->getVal().get<Value::BOOL>()) {
                node->setVal(true);
            } else {
                node->setVal(false);
            }
        } else if (rightNode->getVal().is<Value::INT>()) {
            if (static_cast<bool>(leftNode->getVal().get<Value::FLOAT>()) &&
                static_cast<bool>(rightNode->getVal().get<Value::INT>())) {
                node->setVal(true);
            } else {
                node->setVal(false);
            }
        } else if (static_cast<bool>(leftNode->getVal().get<Value::FLOAT>()) &&
                   static_cast<bool>(rightNode->getVal().get<Value::FLOAT>())) {
            node->setVal(true);
        } else if (rightNode->getVal().is<Value::STR>() || rightNode->getVal().is<Value::LIST>()) {
            node->setVal(rightNode->getVal());
        } else {
            node->setVal(false);
        }
    } else if (leftNode->getVal().is<Value::STR>()) {
        node->setVal(rightNode->getVal());
    } else if (leftNode->getVal().is<Value::LIST>()) {
        node->setVal(rightNode->getVal());
    } else {
        RuntimeException("Could not convert string to value of nodes");
    }
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
        for (size_t i = indices.size(); (i--) != 0U;) {
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

void Evaluator::visit([[maybe_unused]] const std::shared_ptr<BreakNode> &node) {
    throw BreakValue();
}

void Evaluator::visit(const std::shared_ptr<ColumnNode> &node) {
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    std::shared_ptr<AstNode> rightNode = node->getRightNode();

    leftNode->accept(shared_from_this());
    rightNode->accept(shared_from_this());
}

void Evaluator::visit([[maybe_unused]] const std::shared_ptr<ContinueNode> &node) {
    throw ContinueValue();
}

void Evaluator::visit(const std::shared_ptr<DivExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    node->setVal(rightNode->getVal() / leftNode->getVal());
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

    node->setVal(rightNode->getVal().pow(leftNode->getVal()));
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
        const Value::COLUMN &col = identifierVal.get<Value::COLUMN>();

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
            if (ops[op](val, filterVal)) {
                indicesToKeep.push_back(i);
            }
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
        const Value::TABLE &table = val.get<Value::TABLE>();
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
        throw RuntimeException("Error: Invalid type.");
    }

    if (Evaluator::getNumericValue(condNode->getVal() == true) != 0.0) {
        for (size_t i = 0; i < bodyNodes.size(); ++i) {
            bodyNodes[i]->accept(shared_from_this());
        }
    } else if (elseNode != 0) {
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
            throw RuntimeException("index must be an integer. Did you forget '$' infront?");
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
        const Value::LIST &list = val.get<Value::LIST>();

        if (index < 0 || static_cast<size_t>(index) >= list->size()) {
            throw RuntimeException("Index out of range");
        }

        node->setVal(*(*list)[index]);
    } else if (val.is<Value::COLUMN>()) {
        const Value::COLUMN &col = val.get<Value::COLUMN>();

        if (index < 0 || static_cast<size_t>(index) >= col->data->size()) {
            throw RuntimeException("Index out of range");
        }

        node->setVal(*(*col->data)[index]);
    } else {
        throw RuntimeException("Invalid index operation");
    }
}

void Evaluator::visit(const std::shared_ptr<IntersectionExprNode> &node) {
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    if (!node->getLeftNode()->getVal().is<Value::TABLE>() ||
        !node->getRightNode()->getVal().is<Value::TABLE>()) {
        throw RuntimeException("Intersection operation only allowed for Table type");
    }

    Value::TABLE leftTable = leftNode->getVal().get<Value::TABLE>();
    Value::TABLE rightTable = rightNode->getVal().get<Value::TABLE>();

    if (leftTable->size() != rightTable->size()) {
        throw RuntimeException("Tables must have the same number of columns");
    }

    Value::TABLE table = std::make_shared<std::map<Value::STR, Value::COLUMN>>();

    if (!isSameColumns(leftTable, rightTable)) {
        throw RuntimeException("Tables doesn't have equivalent headers");
    }

    size_t size = leftTable->size();
    std::vector<std::shared_ptr<std::vector<std::shared_ptr<dplsrc::Value>>>> cols(size);
    for (size_t i = 0; i < size; ++i) {
        cols[i] = std::make_shared<std::vector<std::shared_ptr<dplsrc::Value>>>();
    }

    auto entryLeft = std::next(leftTable->begin(), 0);
    auto entryLeftCol = entryLeft->second;
    auto entryRightCol = Evaluator::getColumnByHeader(rightTable, entryLeft->first);

    for (size_t i = 0; i < entryLeftCol->data->size(); ++i) {
        std::shared_ptr<Value> entryLeftData = entryLeftCol->data->at(i);
        for (size_t j = 0; j < entryRightCol->data->size(); ++j) {
            std::shared_ptr<Value> entryRightData = entryRightCol->data->at(j);

            if (*entryLeftData == *entryRightData && rowsIntersect(leftTable, rightTable, i, j)) {
                addDataToCols(leftTable, cols, i);
            }
        }
    };

    for (size_t i = 0; i < leftTable->size(); ++i) {
        auto leftCol = std::next(leftTable->begin(), i);
        Evaluator::insertColInTable(table, leftCol->first, cols[i]);
    }
    node->setVal(table);
}

void Evaluator::visit(const std::shared_ptr<LeafNode> &node) {
    if (node->getText() == "<EOF>") {
        return;
    }

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

    node->setVal(rightNode->getVal() - leftNode->getVal());
}

void Evaluator::visit(const std::shared_ptr<MinusNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> childNode = node->getChildNode();
    childNode->accept(shared_from_this());

    if (!(isNumeric(childNode->getVal()) || childNode->getVal().is<Value::COLUMN>())) {
        // TODO: move to error handler at some point
        throw RuntimeException("Cannot do substraction with the used type");
    }

    // Evaluates the value of the expression
    if (childNode->getVal().is<Value::INT>()) {
        node->setVal(-childNode->getVal().get<Value::INT>());
    } else if (childNode->getVal().is<Value::FLOAT>()) {
        node->setVal(-childNode->getVal().get<Value::FLOAT>());
    } else if (childNode->getVal().is<Value::BOOL>()) {
        node->setVal(-static_cast<int>(childNode->getVal().get<Value::BOOL>()));
    } else if (childNode->getVal().is<Value::COLUMN>()) {
        Value::COLUMN col;
        for (size_t i = 0; i < childNode->getVal().get<Value::COLUMN>()->data->size(); i++) {
            if ((*(*childNode->getVal().get<Value::COLUMN>()->data)[i]).is<Value::INT>()) {
                *(*col->data)[i] =
                    -(*(*childNode->getVal().get<Value::COLUMN>()->data)[i]).get<Value::INT>();
            } else if ((*(*childNode->getVal().get<Value::COLUMN>()->data)[i]).is<Value::BOOL>()) {
                *(*col->data)[i] = -static_cast<int>(
                    (*(*childNode->getVal().get<Value::COLUMN>()->data)[i]).get<Value::BOOL>());
            } else if ((*(*childNode->getVal().get<Value::COLUMN>()->data)[i]).is<Value::FLOAT>()) {
                *(*col->data)[i] =
                    -(*(*childNode->getVal().get<Value::COLUMN>()->data)[i]).get<Value::FLOAT>();
            } else {
                throw RuntimeException("Cannot divide with columns contained type");
            }
        }
        node->setVal(col);
    } else {
        throw RuntimeException("Couldn't convert string to value of nodes");
    }
}

void Evaluator::visit(const std::shared_ptr<ModExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    node->setVal(rightNode->getVal() % leftNode->getVal());
}

void Evaluator::visit(const std::shared_ptr<MultExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    node->setVal(rightNode->getVal() * leftNode->getVal());
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
        throw RuntimeException("Cannot dp logical not equal with the used types");
    }

    // Evaluates the value of the expression
    if (leftNode->getVal().is<Value::INT>()) {
        if (rightNode->getVal().is<Value::BOOL>()) {
            node->setVal(leftNode->getVal().get<Value::INT>() !=
                         static_cast<long>(rightNode->getVal().get<Value::BOOL>()));
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
                         static_cast<double>(rightNode->getVal().get<Value::BOOL>()));
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
            node->setVal(static_cast<long>(leftNode->getVal().get<Value::BOOL>()) !=
                         rightNode->getVal().get<Value::INT>());
        } else {
            node->setVal(static_cast<double>(leftNode->getVal().get<Value::BOOL>()) !=
                         rightNode->getVal().get<Value::FLOAT>());
        }
    } else if (leftNode->getVal().is<Value::STR>()) {
        node->setVal(leftNode->getVal().get<Value::STR>() != rightNode->getVal().get<Value::STR>());
    } else {
        throw RuntimeException("Couldn't convert string to value of nodes");
    }
}

void Evaluator::visit(const std::shared_ptr<NotNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> childNode = node->getChildNode();
    childNode->accept(shared_from_this());

    if (!(isNumeric(childNode->getVal()))) {
        throw RuntimeException("Cannot negate the used type");
    }

    // Evaluates the value of the expression
    if (childNode->getVal().is<Value::INT>()) {
        if (static_cast<bool>(childNode->getVal().get<Value::INT>())) {
            node->setVal(false);
        } else {
            node->setVal(true);
        }
    } else if (childNode->getVal().is<Value::INT>()) {
        if (static_cast<bool>(childNode->getVal().get<Value::FLOAT>())) {
            node->setVal(false);
        } else {
            node->setVal(true);
        }
    } else if (childNode->getVal().is<Value::BOOL>()) {
        if (childNode->getVal().get<Value::BOOL>()) {
            node->setVal(false);
        } else {
            node->setVal(true);
        }
    } else {
        throw RuntimeException("Couldn't evaluate negation");
    }
}

void Evaluator::visit(const std::shared_ptr<OrExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    if (leftNode->getVal().is<Value::COLUMN>() || rightNode->getVal().is<Value::COLUMN>()) {
        // TODO: move to error handler at some point
        throw RuntimeException("Cannot do logical or with the used types");
    }

    // Evaluates the value of the expression
    // Evaluates the value of the expression
    if (leftNode->getVal().is<Value::BOOL>()) {
        if (rightNode->getVal().is<Value::BOOL>()) {
            if (leftNode->getVal().get<Value::BOOL>() || rightNode->getVal().get<Value::BOOL>()) {
                node->setVal(true);
            } else {
                node->setVal(false);
            }
        } else if (rightNode->getVal().is<Value::INT>()) {
            if (leftNode->getVal().get<Value::BOOL>() ||
                static_cast<bool>(rightNode->getVal().get<Value::INT>())) {
                node->setVal(true);
            } else {
                node->setVal(false);
            }
        } else if (leftNode->getVal().get<Value::BOOL>() ||
                   static_cast<bool>(rightNode->getVal().get<Value::FLOAT>())) {
            node->setVal(true);
        } else if (rightNode->getVal().is<Value::STR>() || rightNode->getVal().is<Value::LIST>()) {
            node->setVal(leftNode->getVal());
        } else {
            node->setVal(false);
        }
    } else if (leftNode->getVal().is<Value::INT>()) {
        if (rightNode->getVal().is<Value::BOOL>()) {
            if (static_cast<bool>(leftNode->getVal().get<Value::INT>()) ||
                rightNode->getVal().get<Value::BOOL>()) {
                node->setVal(true);
            } else {
                node->setVal(false);
            }
        } else if (rightNode->getVal().is<Value::INT>()) {
            if (static_cast<bool>(leftNode->getVal().get<Value::INT>()) ||
                static_cast<bool>(rightNode->getVal().get<Value::INT>())) {
                node->setVal(true);
            } else {
                node->setVal(false);
            }
        } else if (static_cast<bool>(leftNode->getVal().get<Value::INT>()) ||
                   static_cast<bool>(rightNode->getVal().get<Value::FLOAT>())) {
            node->setVal(true);
        } else if (rightNode->getVal().is<Value::STR>() || rightNode->getVal().is<Value::LIST>()) {
            node->setVal(leftNode->getVal());
        } else {
            node->setVal(false);
        }
    } else if (leftNode->getVal().is<Value::FLOAT>()) {
        if (rightNode->getVal().is<Value::BOOL>()) {
            if (static_cast<bool>(leftNode->getVal().get<Value::FLOAT>()) ||
                rightNode->getVal().get<Value::BOOL>()) {
                node->setVal(true);
            } else {
                node->setVal(false);
            }
        } else if (rightNode->getVal().is<Value::INT>()) {
            if (static_cast<bool>(leftNode->getVal().get<Value::FLOAT>()) ||
                static_cast<bool>(rightNode->getVal().get<Value::INT>())) {
                node->setVal(true);
            } else {
                node->setVal(false);
            }
        } else if (static_cast<bool>(leftNode->getVal().get<Value::FLOAT>()) ||
                   static_cast<bool>(rightNode->getVal().get<Value::FLOAT>())) {
            node->setVal(true);
        } else if (rightNode->getVal().is<Value::STR>() || rightNode->getVal().is<Value::LIST>()) {
            node->setVal(leftNode->getVal());
        } else {
            node->setVal(false);
        }
    } else if (leftNode->getVal().is<Value::STR>()) {
        node->setVal(leftNode->getVal());
    } else if (leftNode->getVal().is<Value::LIST>()) {
        node->setVal(leftNode->getVal());
    } else {
        throw RuntimeException("Could not convert string to value of nodes");
    }
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

    node->setVal(rightNode->getVal() + leftNode->getVal());
}

void Evaluator::visit(const std::shared_ptr<PlusNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> childNode = node->getChildNode();
    childNode->accept(shared_from_this());

    if (!isNumeric(childNode->getVal()) && !childNode->getVal().is<Value::COLUMN>()) {
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
    } else if (childNode->getVal().is<Value::COLUMN>()) {
        node->setVal(childNode->getVal().get<Value::COLUMN>());
    } else {
        throw RuntimeException("Couldn't convert string to value of nodes");
    }
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
    try {
        for (size_t i = 0; i < childNodes.size(); ++i) {
            childNodes[i]->accept(shared_from_this());
        }
    } catch (const ReturnValue &e) {
        throw RuntimeException("Return statement not allowed outside functions");
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

void Evaluator::visit(const std::shared_ptr<UnionExprNode> &node) {
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    if (!node->getLeftNode()->getVal().is<Value::TABLE>() ||
        !node->getRightNode()->getVal().is<Value::TABLE>()) {
        throw RuntimeException("Intersection operation only allowed for Table type");
    }

    Value::TABLE leftTable = leftNode->getVal().get<Value::TABLE>();
    Value::TABLE rightTable = rightNode->getVal().get<Value::TABLE>();

    Value::TABLE table = std::make_shared<std::map<Value::STR, Value::COLUMN>>();

    size_t largestTableSize =
        (leftTable->size() > rightTable->size()) ? leftTable->size() : rightTable->size();

    for (size_t i = 0; i < largestTableSize; ++i) {
        auto leftColPair =
            (i > leftTable->size()) ? leftTable->end() : std::next(leftTable->begin(), i);
        auto rightColPair =
            (i > rightTable->size()) ? rightTable->end() : std::next(rightTable->begin(), i);

        if (leftColPair == leftTable->end()) {
            auto leftCol = Evaluator::getColumnByHeader(leftTable, rightColPair->first);
            addColUnionToTable(table, leftCol, rightColPair->second, rightColPair->first);
        } else if (rightColPair == rightTable->end()) {
            auto rightCol = Evaluator::getColumnByHeader(rightTable, leftColPair->first);
            addColUnionToTable(table, leftColPair->second, rightCol, leftColPair->first);
        } else if (leftColPair->first == rightColPair->first) {
            addColUnionToTable(table, leftColPair->second, rightColPair->second,
                               rightColPair->first);
        } else {
            auto leftColMatch = Evaluator::getColumnByHeader(leftTable, rightColPair->first);
            auto rightColMatch = Evaluator::getColumnByHeader(rightTable, leftColPair->first);

            addColUnionToTable(table, leftColMatch, rightColPair->second, rightColPair->first);
            addColUnionToTable(table, leftColPair->second, rightColMatch, leftColPair->first);
        }
    }
    node->setVal(table);
}

void Evaluator::visit(const std::shared_ptr<WhileNode> &node) {
    std::shared_ptr<AstNode> condNode = node->getChildNode();
    std::vector<std::shared_ptr<AstNode>> bodyNodes = node->getChildNodeList();

    condNode->accept(shared_from_this());

    if (!isNumeric(condNode->getVal())) {
        throw RuntimeException("Invalid type");
    }
    while (Evaluator::getNumericValue(condNode->getVal()) != 0.0) {
        if (Evaluator::loopBody(bodyNodes)) {
            break;
        }
        condNode->accept(shared_from_this());
    }
}

void Evaluator::initPtable() {
    Procedure::ProcType print1 = [](std::vector<std::shared_ptr<AstNode>> args) {
        std::cout << args[0]->getVal().toString() << '\n';
        return nullptr;
    };

    Procedure::ProcType input0 =
        []([[maybe_unused]] const std::vector<std::shared_ptr<AstNode>> &args) {
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

    Procedure::ProcType int1 = [](std::vector<std::shared_ptr<AstNode>> args) {
        if (args[0]->getVal().is<Value::INT>()) {
            return args[0]->getVal().get<Value::INT>();
        }
        if (args[0]->getVal().is<Value::FLOAT>()) {
            return static_cast<Value::INT>(args[0]->getVal().get<Value::FLOAT>());
        } if (args[0]->getVal().is<Value::BOOL>()) {
            return static_cast<Value::INT>(args[0]->getVal().get<Value::BOOL>());
        } else if (args[0]->getVal().is<Value::STR>()) {
            try {
                return std::stol(args[0]->getVal().get<Value::STR>());
            } catch (const std::invalid_argument &e) {
                throw RuntimeException("Could not convert string to int");
            }
        }

        throw RuntimeException("Could not convert value to int");
    };

    Procedure::ProcType float1 = [](std::vector<std::shared_ptr<AstNode>> args) {
        if (args[0]->getVal().is<Value::INT>()) {
            return static_cast<Value::FLOAT>(args[0]->getVal().get<Value::INT>());
        }
        if (args[0]->getVal().is<Value::FLOAT>()) {
            return args[0]->getVal().get<Value::FLOAT>();
        } if (args[0]->getVal().is<Value::BOOL>()) {
            return static_cast<Value::FLOAT>(args[0]->getVal().get<Value::BOOL>());
        } else if (args[0]->getVal().is<Value::STR>()) {
            try {
                return std::stod(args[0]->getVal().get<Value::STR>());
            } catch (const std::invalid_argument &e) {
                throw RuntimeException("Could not convert string to float");
            }
        }

        throw RuntimeException("Could not convert value to float");
    };

    Procedure::ProcType bool1 = [](std::vector<std::shared_ptr<AstNode>> args) {
        if (args[0]->getVal().is<Value::INT>()) {
            return static_cast<Value::BOOL>(args[0]->getVal().get<Value::INT>());
        }
        if (args[0]->getVal().is<Value::FLOAT>()) {
            return static_cast<Value::BOOL>(args[0]->getVal().get<Value::FLOAT>());
        } if (args[0]->getVal().is<Value::BOOL>()) {
            return args[0]->getVal().get<Value::BOOL>();
        }

        throw RuntimeException("Could not convert value to bool");
    };

    Procedure::ProcType len1 = [](std::vector<std::shared_ptr<AstNode>> args) {
        Value val = args[0]->getVal();

        if (val.is<Value::STR>()) {
            return static_cast<Value::INT>(val.get<Value::STR>().size());
        }
        if (val.is<Value::LIST>()) {
            return static_cast<Value::INT>(val.get<Value::LIST>()->size());
        } if (val.is<Value::TABLE>()) {
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

        throw RuntimeException("Ceil called with invalid type " + val.toTypeString() +
                               ". Expected: " + Value(0.0).toTypeString());
    };

    Procedure::ProcType floor1 = [](std::vector<std::shared_ptr<AstNode>> args) {
        Value val = args[0]->getVal();

        if (val.is<Value::FLOAT>()) {
            return static_cast<Value::INT>(std::floor(val.get<Value::FLOAT>()));
        }

        throw RuntimeException("Floor called with invalid type " + val.toTypeString() +
                               ". Expected: " + Value(0.0).toTypeString());
    };

    Procedure::ProcType round1 = [](std::vector<std::shared_ptr<AstNode>> args) {
        Value val = args[0]->getVal();

        if (val.is<Value::FLOAT>()) {
            return static_cast<Value::INT>(std::round(val.get<Value::FLOAT>()));
        }

        throw RuntimeException("Round called with invalid type " + val.toTypeString() +
                               ". Expected: " + Value(0.0).toTypeString());
    };

    Procedure::ProcType copy1 = [this](std::vector<std::shared_ptr<AstNode>> args) {
        Value val = args[0]->getVal();
        if (val.is<Value::LIST>()) {
            return Value(copyList(val.get<Value::LIST>()));
        }
        if (val.is<Value::TABLE>()) {
            return Value(copyTable(val.get<Value::TABLE>()));
        }

        throw RuntimeException("Copy called with invalid type " + val.toTypeString());
    };

    Procedure::ProcType readFile1 = [](std::vector<std::shared_ptr<AstNode>> args) {
        Value fileName = args[0]->getVal();

        if (!fileName.is<Value::STR>()) {
            throw RuntimeException("ReadFile called with invalid type " + fileName.toTypeString() +
                                   ". Expected: " + Value("").toTypeString() + '\n');
        }

        std::filesystem::path filePath = fileName.get<Value::STR>();
        std::ifstream file(filePath);
        if (!file.is_open()) {
            throw RuntimeException("Could not open file \"" + fileName.toString() + "\"");
        }

        std::string fileContents((std::istreambuf_iterator<char>(file)),
                                 std::istreambuf_iterator<char>());

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
            throw RuntimeException("ReadTable called with invalid type " + fileName.toTypeString() +
                                   ". Expected: " + Value("").toTypeString() + '\n');
        }

        if (!delimiterVal.is<Value::STR>()) {
            throw RuntimeException("ReadTable called with invalid type " +
                                   delimiterVal.toTypeString() +
                                   ". Expected: " + Value("").toTypeString() + '\n');
        }

        if (delimiterVal.get<Value::STR>().size() != 1) {
            throw RuntimeException("Delimiter must be a string of size 1");
        }

        if (!dataTypesVal.is<Value::LIST>()) {
            throw RuntimeException("ReadTable called with invalid type " +
                                   dataTypesVal.toTypeString() +
                                   ". Expected: " + Value({}).toTypeString() + '\n');
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
                        const Value::LIST &dataTypes = dataTypesVal.get<Value::LIST>();
                        if (dataTypes->empty()) {
                            cols[i]->data->emplace_back(std::make_shared<Value>(values[i]));
                        } else {
                            Value::STR dataType = dataTypes->at(i)->get<Value::STR>();
                            if (dataType == "int") {
                                cols[i]->data->emplace_back(
                                    std::make_shared<Value>(std::stol(values[i])));
                            } else if (dataType == "float") {
                                cols[i]->data->emplace_back(
                                    std::make_shared<Value>(std::stod(values[i])));
                            } else if (dataType == "bool") {
                                bool isTrue = values[i] == "True" || values[i] != "0";
                                cols[i]->data->emplace_back(std::make_shared<Value>(isTrue));
                            } else if (dataType == "NoneType") {
                                cols[i]->data->emplace_back(std::make_shared<Value>(nullptr));
                            } else if (dataType == "str") {
                                cols[i]->data->emplace_back(std::make_shared<Value>(values[i]));
                            } else if (dataType == "list") {
                                throw RuntimeException(
                                    "Type \"lists\" not supported when loading table from file");
                            } else if (dataType == "table") {
                                throw RuntimeException(
                                    "Type \"table\" not supported when loading table from file");
                            } else if (dataType == "column") {
                                throw RuntimeException(
                                    "Data can not be explicitly converted to type \"column\"");
                            } else {
                                throw RuntimeException("Trying to convert to invalid data type \"" +
                                                       dataType + "\"");
                            }
                        }
                    }

                    // If header is missing then we generate a default one to ensure uniqueness
                    if (headers[i].empty()) {
                        std::hash<std::size_t> hash;
                        std::string hashStr = "id" + std::to_string(hash(i));

                        // While the hash is already in headers vector we make a new one to avoid
                        // collision
                        size_t j = i;
                        while (std::count(headers.begin(), headers.end(), hashStr) != 0) {
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
            throw RuntimeException("WriteTable called with invalid type " +
                                   fileName.toTypeString() +
                                   ". Expected: " + Value("").toTypeString() + '\n');
        }

        if (!table.is<Value::TABLE>()) {
            throw RuntimeException("WriteTable called with invalid type " + table.toTypeString() +
                                   ". Expected: " + Value("").toTypeString() + '\n');
        }

        if (!delimiterVal.is<Value::STR>()) {
            throw RuntimeException("WriteTable called with invalid type " +
                                   delimiterVal.toTypeString() +
                                   ". Expected: " + Value("").toTypeString() + '\n');
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
            for (const std::pair<const Value::STR, Value::COLUMN> &entry :
                 *table.get<Value::TABLE>()) {
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
    ptable.bind(Procedure("int", {"x"}, int1));
    ptable.bind(Procedure("float", {"x"}, float1));
    ptable.bind(Procedure("bool", {"x"}, bool1));
    ptable.bind(Procedure("len", {"x"}, len1));
    ptable.bind(Procedure("ceil", {"x"}, ceil1));
    ptable.bind(Procedure("floor", {"x"}, floor1));
    ptable.bind(Procedure("round", {"x"}, round1));
    ptable.bind(Procedure("copy", {"x"}, copy1));
    ptable.bind(Procedure("readFile", {"filename"}, readFile1));
    ptable.bind(Procedure("writeFile", {"filename", "content"}, writeFile2));
    ptable.bind(Procedure("readTable", {"filename"}, readTable1));
    ptable.bind(Procedure("readTable", {"filename", "delimiter"}, readTable2));
    ptable.bind(Procedure("readTable", {"filename", "delimiter", "dataTypes"}, readTable3));
    ptable.bind(Procedure("writeTable", {"filename", "table"}, writeTable2));
    ptable.bind(Procedure("writeTable", {"filename", "table", "delimiter"}, writeTable3));
}

bool Evaluator::rowsIntersect(const Value::TABLE &leftTable, const Value::TABLE &rightTable,
                              size_t i, size_t j) {
    for (size_t l = 0; l < leftTable->size(); ++l) {
        auto leftMap = std::next(leftTable->begin(), l);
        auto rightCol = Evaluator::getColumnByHeader(rightTable, leftMap->first);

        auto leftData = (*leftMap->second->data)[i];
        auto rightData = (*rightCol->data)[j];

        if (*leftData != *rightData) {
            return false;
        }
    }
    return true;
}

double Evaluator::getNumericValue(const Value &val) {
    if (val.is<Value::BOOL>()) {
        return static_cast<double>(val.get<Value::BOOL>());
    }
    if (val.is<Value::INT>()) {
        return static_cast<double>(val.get<Value::INT>());
    } if (val.is<Value::FLOAT>()) {
        return val.get<Value::FLOAT>();
    } else {
        return 0.0;
    }
}

bool Evaluator::loopBody(std::vector<std::shared_ptr<AstNode>> bodyNodes) {
    bool breakFromLoop = false;
    for (size_t i = 0; i < bodyNodes.size(); ++i) {
        try {
            bodyNodes[i]->accept(shared_from_this());
        } catch (const ContinueValue &e) {
            break;
        } catch (const BreakValue &e) {
            breakFromLoop = true;
            break;
        }
    }
    return breakFromLoop;
}

void Evaluator::addDataToCols(
    const Value::TABLE &table,
    std::vector<std::shared_ptr<std::vector<std::shared_ptr<dplsrc::Value>>>> &cols, size_t i) {
    for (size_t l = 0; l < table->size(); ++l) {
        auto leftMap = std::next(table->begin(), l);
        auto leftData = (*leftMap->second->data)[i];
        cols[l]->emplace_back(leftData);
    }
}

Value::COLUMN Evaluator::getColumnByHeader(const Value::TABLE &table, const std::string &header) {
    for (const auto &entry : *table) {
        if (entry.first == header) {
            return entry.second;
        }
    }
    return nullptr;  // Return null if no column with the given header is found
}

bool Evaluator::isSameColumns(const Value::TABLE &leftTable, const Value::TABLE &rightTable) {
    for (size_t i = 0; i < leftTable->size(); ++i) {
        const auto &tempEntryLeft = std::next(leftTable->begin(), i);
        if (getColumnByHeader(rightTable, tempEntryLeft->first) == nullptr) {
            return false;
        }
    }
    return true;
}

void Evaluator::addColUnionToTable(Value::TABLE &table,
                                   const std::shared_ptr<dplsrc::Value::COL_STRUCT> &col1,
                                   const std::shared_ptr<dplsrc::Value::COL_STRUCT> &col2,
                                   const Value::STR &header) {
    auto tempList = std::make_shared<std::vector<std::shared_ptr<dplsrc::Value>>>();

    if (col1 == nullptr) {
        Evaluator::addNullValuesToList(tempList, col2->data->size());
    } else {
        Evaluator::addListToList(col1->data, tempList);
    }

    if (col2 == nullptr) {
        Evaluator::addNullValuesToList(tempList, col1->data->size());
    } else {
        Evaluator::addListToList(col2->data, tempList);
    }

    Evaluator::insertColInTable(table, header, tempList);
}

void Evaluator::addNullValuesToList(
    const std::shared_ptr<std::vector<std::shared_ptr<dplsrc::Value>>> &list, size_t size) {
    for (size_t j = 0; j < size; ++j) {
        list->push_back(std::make_shared<Value>(nullptr));
    }
}

void Evaluator::insertColInTable(const Value::TABLE &table, const std::string &header,
                                 Value::LIST list) {
    Value::COLUMN col = std::make_shared<Value::COL_STRUCT>();
    col->header = header;
    col->data = std::move(list);
    col->parent = table;
    table->insert({header, col});
}

void Evaluator::addListToList(
    const std::shared_ptr<std::vector<std::shared_ptr<dplsrc::Value>>> &srcList,
    const std::shared_ptr<std::vector<std::shared_ptr<dplsrc::Value>>> &dstList) {
    for (size_t i = 0; i < srcList->size(); ++i) {
        dstList->push_back(srcList->at(i));
    }
}

Value::LIST Evaluator::copyList(const Value::LIST &list) {
    Value::LIST copiedList = std::make_shared<std::vector<std::shared_ptr<Value>>>();
    std::stack<std::pair<Value::LIST, std::shared_ptr<Value>>> stack;

    for (auto it = list->rbegin(); it != list->rend(); ++it) {
        stack.push({copiedList, *it});
    }

    while (!stack.empty()) {
        auto [currentList, valPtr] = stack.top();
        stack.pop();

        if (valPtr->is<Value::LIST>()) {
            Value::LIST nestedList = std::make_shared<std::vector<std::shared_ptr<Value>>>();
            for (const std::shared_ptr<Value> &nestedVal : *valPtr->get<Value::LIST>()) {
                stack.push({nestedList, nestedVal});
            }
            currentList->emplace_back(std::make_shared<Value>(nestedList));
        } else if (valPtr->is<Value::TABLE>()) {
            Value::TABLE copiedTable = copyTable(valPtr->get<Value::TABLE>());
            currentList->emplace_back(std::make_shared<Value>(copiedTable));
        } else {
            currentList->emplace_back(std::make_shared<Value>(*valPtr));
        }
    }

    return copiedList;
}

Value::TABLE Evaluator::copyTable(const Value::TABLE &table) {
    Value::TABLE copiedTable = std::make_shared<std::map<Value::STR, Value::COLUMN>>();

    for (const std::pair<const Value::STR, Value::COLUMN> &entry : *table) {
        Value::COLUMN copiedCol = std::make_shared<Value::COL_STRUCT>();
        copiedCol->header = entry.second->header;
        copiedCol->parent = copiedTable;
        copiedCol->data = copyList(entry.second->data);
        copiedTable->insert({entry.first, copiedCol});
    }

    return copiedTable;
}
