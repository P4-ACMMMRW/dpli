#include "Evaluator.hpp"

using namespace dplsrc;

void Evaluator::visit(const std::shared_ptr<AndExprNode> &node) {}

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
        throw std::runtime_error("Error: left side of assignment must be a reference\n");
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

        Value::INT index = indexNode->getRightNode()->getVal().get<Value::INT>();

        if (val.is<Value::LIST>()) {
            Value::LIST list = val.getMut<Value::LIST>();
            if (index < 0 || static_cast<size_t>(index) >= list->size()) {
                throw std::runtime_error("Error: index out of range\n");
            }

            (*list)[index] = rightNode->getVal();
        } else if (val.is<Value::COLUMN>()) {
            std::vector<std::shared_ptr<Value>> valPtrs = val.getMut<Value::COLUMN>()->data;
            if (index < 0 || static_cast<size_t>(index) >= valPtrs.size()) {
                throw std::runtime_error("Error: index out of range\n");
            }

            *valPtrs[index] = rightNode->getVal();
        } else {
            throw std::runtime_error("Error: index assignment not allowed for this type\n");
        }

        vtable.bind(Variable(identifierNode->getText(), val));
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

void Evaluator::visit(const std::shared_ptr<DivExprNode> &node) {}

void Evaluator::visit(const std::shared_ptr<ElseNode> &node) {}

void Evaluator::visit(const std::shared_ptr<EqualExprNode> &node) {}

void Evaluator::visit(const std::shared_ptr<ExpoExprNode> &node) {}

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

        std::vector<Value::INT> indicesToKeep;
        for (size_t i = 0; i < col->data.size(); ++i) {
            Value val = *col->data[i];
            if (val == filterVal) indicesToKeep.push_back(i);
        }

        Value::TABLE table = col->parent;
        Value::TABLE newTable = std::make_shared<std::unordered_map<Value::STR, Value::COLUMN>>();

        for (const std::pair<const Value::STR, Value::COLUMN> &entry : *table) {
            std::vector<std::shared_ptr<Value>> newData;
            for (Value::INT index : indicesToKeep) {
                newData.emplace_back(entry.second->data[index]);
            }

            Value::COLUMN newCol = std::make_shared<Value::COL_STRUCT>();
            newCol->parent = newTable;
            newCol->header = entry.first;
            newCol->data = newData;
            newCol->size = newData.size();
            newTable->insert({entry.first, newCol});
        }

        node->setVal(newTable);
    } else {
        throw std::runtime_error("Error: filter operation not allowed for this type\n");
    }
}

void Evaluator::visit(const std::shared_ptr<GreaterEqualExprNode> &node) {}

void Evaluator::visit(const std::shared_ptr<GreaterExprNode> &node) {}

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

        node->setVal((*list)[index]);
    } else if (val.is<Value::COLUMN>()) {
        Value::COLUMN col = val.get<Value::COLUMN>();

        if (index < 0 || static_cast<size_t>(index) >= col->data.size()) {
            throw std::runtime_error("Error: index out of range\n");
        }

        node->setVal(*col->data[index]);
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

void Evaluator::visit(const std::shared_ptr<LessEqualExprNode> &node) {}

void Evaluator::visit(const std::shared_ptr<LessExprNode> &node) {}

void Evaluator::visit(const std::shared_ptr<ListNode> &node) {
    std::vector<std::shared_ptr<AstNode>> childNodes = node->getChildNodeList();

    Value::LIST values = std::make_shared<std::vector<Value>>();
    for (size_t i = 0; i < childNodes.size(); ++i) {
        childNodes[i]->accept(shared_from_this());
        values->emplace_back(childNodes[i]->getVal());
    }

    node->setVal(values);
}

void Evaluator::visit(const std::shared_ptr<MinusExprNode> &node) {}

void Evaluator::visit(const std::shared_ptr<MinusNode> &node) {}

void Evaluator::visit(const std::shared_ptr<ModExprNode> &node) {}

void Evaluator::visit(const std::shared_ptr<MultExprNode> &node) {}

void Evaluator::visit(const std::shared_ptr<NotEqualExprNode> &node) {}

void Evaluator::visit(const std::shared_ptr<NotNode> &node) {}

void Evaluator::visit(const std::shared_ptr<OrExprNode> &node) {}

void Evaluator::visit(const std::shared_ptr<ParNode> &node) {
    std::shared_ptr<AstNode> childNode = node->getChildNode();
    childNode->accept(shared_from_this());
    node->setVal(childNode->getVal());
}

void Evaluator::visit(const std::shared_ptr<PlusExprNode> &node) {}

void Evaluator::visit(const std::shared_ptr<PlusNode> &node) {}

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
    bool sizeSet;
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
        std::vector<std::shared_ptr<Value>> valPtrs;

        for (Value &v : *val) {
            valPtrs.emplace_back(std::make_shared<Value>(v));
        }

        Value::COLUMN col = std::make_shared<Value::COL_STRUCT>();
        col->parent = table;
        col->header = header;
        col->data = valPtrs;

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
            return static_cast<Value::INT>(val.get<Value::COLUMN>()->data.size());
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
