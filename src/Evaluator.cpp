#include "Evaluator.hpp"

using namespace dplsrc;

void Evaluator::visit(const std::shared_ptr<AndExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    node->setVal(leftNode->getVal() && rightNode->getVal());
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
            std::shared_ptr<FilterNode> filterNode =
                std::dynamic_pointer_cast<FilterNode>(indexNode);

            if (filterNode) {
                filterNode->accept(shared_from_this());
                indices.emplace_back(filterNode->getVal());
            } else {
                indices.emplace_back(indexNode->getRightNode()->getVal());
            }

            indexNode = std::dynamic_pointer_cast<IndexNode>(indexNode->getLeftNode());
        }

        // Get the pointer to the innermost list or column
        Value::LIST list = nullptr;
        Value::INT lastIndex = 0;

        for (size_t i = indices.size(); (i--) != 0u;) {
            if (val.is<Value::LIST>()) {
                Value::INT index = indices[i].get<Value::INT>();
                list = val.getMut<Value::LIST>();
                lastIndex = index;
                val = *(*list)[index];
            } else if (val.is<Value::COLUMN>()) {
                if (indices[i].is<Value::INT>()) {
                    Value::INT index = indices[i].get<Value::INT>();
                    list = val.getMut<Value::COLUMN>()->data;
                    lastIndex = index;
                    val = *(*list)[index];
                } else {
                    val = indices[i];
                }
            } else if (val.is<Value::TABLE>()) {
                // Tables index by header name
                Value::TABLE table = val.get<Value::TABLE>();
                Value::STR header = indices[i].get<Value::STR>();
                val = table->second.at(header);
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
            if (list) {
                *(*list)[lastIndex] = rightNode->getVal();
            } else {
                throw RuntimeException("cannot directly assign a value to a unnamed table");
            }
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

    node->setVal(leftNode->getVal() / rightNode->getVal());
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

    // Evaluates the value of the expression
    node->setVal(leftNode->getVal() == rightNode->getVal());
}

void Evaluator::visit(const std::shared_ptr<ExpoExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    node->setVal(leftNode->getVal().pow(rightNode->getVal()));
}

void Evaluator::visit(const std::shared_ptr<FilterNode> &node) {
    std::shared_ptr<AstNode> identifierNode = node->getLeftNode();
    std::shared_ptr<AstNode> filterNode = node->getRightNode();

    identifierNode->accept(shared_from_this());
    filterNode->accept(shared_from_this());

    Value identifierVal = identifierNode->getVal();
    Value filterVal = filterNode->getVal();

    if (!identifierVal.is<Value::COLUMN>()) {
        throw RuntimeException("Filter operation not allowed for this type");
    }
    const Value::COLUMN &col = identifierVal.get<Value::COLUMN>();

    // Map string to operator function
    std::unordered_map<std::string, std::function<bool(const Value &, const Value &)>> ops = {
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
    Value::TABLE newTable = std::make_shared<
        std::pair<std::vector<Value::STR>, std::unordered_map<Value::STR, Value::COLUMN>>>();
    for (const Value::STR &key : table->first) {
        Value::LIST newData = std::make_shared<std::vector<std::shared_ptr<Value>>>();
        for (Value::INT index : indicesToKeep) {
            newData->emplace_back((*table->second.at(key)->data)[index]);
        }

        Value::COLUMN newCol = std::make_shared<Value::COL_STRUCT>();
        newCol->parent = newTable;
        newCol->header = key;
        newCol->data = newData;
        newTable->first.emplace_back(key);
        newTable->second.insert({key, newCol});
    }

    node->setVal(newTable);
}

void Evaluator::visit(const std::shared_ptr<GreaterEqualExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    // Evaluates the value of the expression
    node->setVal(leftNode->getVal() >= rightNode->getVal());
}

void Evaluator::visit(const std::shared_ptr<GreaterExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

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
            node->setVal(table->second.at(header));
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

    if (condNode->getVal().getBoolValue()) {
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

    if (leftTable->second.size() != rightTable->second.size()) {
        throw RuntimeException("Tables must have the same number of columns");
    }

    Value::TABLE table = std::make_shared<
        std::pair<std::vector<Value::STR>, std::unordered_map<Value::STR, Value::COLUMN>>>();

    if (!isSameColumns(leftTable, rightTable)) {
        throw RuntimeException("Tables doesn't have equivalent headers");
    }

    size_t size = leftTable->second.size();
    std::vector<std::shared_ptr<std::vector<std::shared_ptr<dplsrc::Value>>>> cols(size);
    for (size_t i = 0; i < size; ++i) {
        cols[i] = std::make_shared<std::vector<std::shared_ptr<dplsrc::Value>>>();
    }

    auto entryLeft = std::next(leftTable->second.begin(), 0);
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

    for (size_t i = 0; i < leftTable->first.size(); ++i) {
        ;
        Evaluator::insertColInTable(table, leftTable->first[i], cols[i]);
    }
    node->setVal(copyTable(table));
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
            try {
                node->setVal(std::stol(node->getText()));
            } catch (const std::out_of_range &e) {
                throw RuntimeException("Integer value out of range");
            }
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

    // Evaluates the value of the expression
    node->setVal(leftNode->getVal() <= rightNode->getVal());
}

void Evaluator::visit(const std::shared_ptr<LessExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

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

    node->setVal(leftNode->getVal() - rightNode->getVal());
}

void Evaluator::visit(const std::shared_ptr<MinusNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> childNode = node->getChildNode();
    childNode->accept(shared_from_this());

    // Evaluates the value of the expression
    node->setVal(-childNode->getVal());
}

void Evaluator::visit(const std::shared_ptr<ModExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    node->setVal(leftNode->getVal() % rightNode->getVal());
}

void Evaluator::visit(const std::shared_ptr<MultExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    node->setVal(leftNode->getVal() * rightNode->getVal());
}

void Evaluator::visit(const std::shared_ptr<NotEqualExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    node->setVal(leftNode->getVal() != rightNode->getVal());
}

void Evaluator::visit(const std::shared_ptr<NotNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> childNode = node->getChildNode();
    childNode->accept(shared_from_this());

    node->setVal(!childNode->getVal());
}

void Evaluator::visit(const std::shared_ptr<OrExprNode> &node) {
    // Get left and right node
    std::shared_ptr<AstNode> leftNode = node->getLeftNode();
    leftNode->accept(shared_from_this());
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    node->setVal(leftNode->getVal() || rightNode->getVal());
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

    node->setVal(leftNode->getVal() + rightNode->getVal());
}

void Evaluator::visit(const std::shared_ptr<PlusNode> &node) {
    std::shared_ptr<AstNode> childNode = node->getChildNode();
    childNode->accept(shared_from_this());
    node->setVal(childNode->getVal());  // temp fix until PlusNode deleted
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
    Value::TABLE table = std::make_shared<
        std::pair<std::vector<Value::STR>, std::unordered_map<Value::STR, Value::COLUMN>>>();
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

        table->first.emplace_back(header);
        table->second.insert({header, col});
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
        throw RuntimeException("Union operation only allowed for Table type");
    }

    Value::TABLE leftTable = leftNode->getVal().get<Value::TABLE>();
    Value::TABLE rightTable = rightNode->getVal().get<Value::TABLE>();

    Value::TABLE table = std::make_shared<
        std::pair<std::vector<Value::STR>, std::unordered_map<Value::STR, Value::COLUMN>>>();

    size_t leftSize = leftTable->first.size();
    size_t rightSize = rightTable->first.size();
    size_t largestTableSize = std::max(leftSize, rightSize);

    for (size_t i = 0; i < largestTableSize; ++i) {
        bool withinLeft = i < leftSize;
        bool withinRight = i < rightSize;

        if (!withinLeft) {
            Value::COLUMN rightCol = rightTable->second.at(rightTable->first[i]);
            addColUnionToTable(table, nullptr, rightCol, rightTable->first[i]);
        } else if (!withinRight) {
            Value::COLUMN leftCol = leftTable->second.at(leftTable->first[i]);
            addColUnionToTable(table, leftCol, nullptr, leftTable->first[i]);
        } else if (leftTable->first[i] == rightTable->first[i]) {
            Value::COLUMN leftCol = leftTable->second.at(rightTable->first[i]);
            Value::COLUMN rightCol = rightTable->second.at(rightTable->first[i]);
            addColUnionToTable(table, leftCol, rightCol, rightTable->first[i]);
        } else {
            Value::COLUMN leftCol = Evaluator::getColumnByHeader(leftTable, rightTable->first[i]);
            Value::COLUMN rightCol = rightTable->second.at(rightTable->first[i]);
            addColUnionToTable(table, leftCol, rightCol, rightTable->first[i]);

            leftCol = leftTable->second.at(leftTable->first[i]);
            rightCol = Evaluator::getColumnByHeader(rightTable, leftTable->first[i]);
            addColUnionToTable(table, leftCol, rightCol, leftTable->first[i]);
        }
    }

    node->setVal(copyTable(table));
}

void Evaluator::visit(const std::shared_ptr<WhileNode> &node) {
    std::shared_ptr<AstNode> condNode = node->getChildNode();
    std::vector<std::shared_ptr<AstNode>> bodyNodes = node->getChildNodeList();

    condNode->accept(shared_from_this());

    while (condNode->getVal().getBoolValue()) {
        if (Evaluator::loopBody(bodyNodes)) {
            break;
        }
        condNode->accept(shared_from_this());
    }
}

bool Evaluator::rowsIntersect(const Value::TABLE &leftTable, const Value::TABLE &rightTable,
                              size_t i, size_t j) {
    for (size_t l = 0; l < leftTable->second.size(); ++l) {
        auto leftMap = std::next(leftTable->second.begin(), l);
        auto rightCol = Evaluator::getColumnByHeader(rightTable, leftMap->first);

        auto leftData = (*leftMap->second->data)[i];
        auto rightData = (*rightCol->data)[j];

        if (*leftData != *rightData) {
            return false;
        }
    }
    return true;
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

void Evaluator::addDataToCols(const Value::TABLE &table, std::vector<Value::LIST> &cols, size_t i) {
    for (size_t l = 0; l < table->first.size(); ++l) {
        Value::STR header = table->first[l];
        Value::COLUMN column = table->second.at(header);
        auto data = (*column->data)[i];
        cols[l]->emplace_back(data);
    }
}

Value::COLUMN Evaluator::getColumnByHeader(const Value::TABLE &table, const std::string &header) {
    try {
        return table->second.at(header);
    } catch (const std::out_of_range &e) {
        return nullptr;
    }
}

bool Evaluator::isSameColumns(const Value::TABLE &leftTable, const Value::TABLE &rightTable) {
    for (size_t i = 0; i < leftTable->second.size(); ++i) {
        const auto &tempEntryLeft = std::next(leftTable->second.begin(), i);
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

    // Dont add headers twice
    if (Evaluator::getColumnByHeader(table, header)) { return;
}

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
    table->first.emplace_back(header);
    table->second.insert({header, col});
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
    Value::TABLE copiedTable = std::make_shared<
        std::pair<std::vector<Value::STR>, std::unordered_map<Value::STR, Value::COLUMN>>>();

    for (const Value::STR &key : table->first) {
        Value::COLUMN copiedCol = std::make_shared<Value::COL_STRUCT>();
        std::pair<Value::STR, Value::COLUMN> entry(key, table->second.at(key));
        copiedCol->header = entry.second->header;
        copiedCol->parent = copiedTable;
        copiedCol->data = copyList(entry.second->data);
        copiedTable->first.emplace_back(key);
        copiedTable->second.insert({key, copiedCol});
    }

    return copiedTable;
}
