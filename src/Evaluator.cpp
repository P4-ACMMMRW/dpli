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
    bool error = !isLeaf && !isIndexing || (isLeaf && !leafNode->getIsIdentifier());
    if (error) {
        // TODO: move to error handler at some point
        throw std::runtime_error("Error: left side of assignment must be a reference\n");
    }

    // Compute type of right node
    std::shared_ptr<AstNode> rightNode = node->getRightNode();
    rightNode->accept(shared_from_this());

    // If indexing
    if (isIndexing) {
        std::shared_ptr<AstNode> identifierNode = indexNode->getRightNode();

        Variable *var = vtable.lookup(identifierNode->getText());
        Value val = var->getVal();

        int index = indexNode->getLeftNode()->getVal().get<long>();

        // For some types indexing is read-only
        if (!val.is<Value::LIST>()) {
            throw std::runtime_error("Error: list assigment not allowed for this type\n");
        }

        val.getMut<Value::LIST>()[index] = rightNode->getVal();

        vtable.bind(Variable(identifierNode->getText(), val));
    } else {
        vtable.bind(Variable(leftNode->getText(), rightNode->getVal()));
    }
}

void Evaluator::visit(const std::shared_ptr<ColumnNode> &node) {}

void Evaluator::visit(const std::shared_ptr<DivExprNode> &node) {}

void Evaluator::visit(const std::shared_ptr<ElseNode> &node) {}

void Evaluator::visit(const std::shared_ptr<EqualExprNode> &node) {}

void Evaluator::visit(const std::shared_ptr<ExpoExprNode> &node) {}

void Evaluator::visit(const std::shared_ptr<FilterNode> &node) {}

void Evaluator::visit(const std::shared_ptr<GreaterEqualExprNode> &node) {}

void Evaluator::visit(const std::shared_ptr<GreaterExprNode> &node) {}

void Evaluator::visit(const std::shared_ptr<HeaderIndexNode> &node) {}

void Evaluator::visit(const std::shared_ptr<IfNode> &node) {}

void Evaluator::visit(const std::shared_ptr<IndexNode> &node) {
    std::shared_ptr<AstNode> identifierNode = node->getRightNode();
    std::shared_ptr<AstNode> indexNode = node->getLeftNode();

    identifierNode->accept(shared_from_this());
    indexNode->accept(shared_from_this());

    int index = indexNode->getVal().get<Value::INT>();

    Value val = identifierNode->getVal();
    if (val.is<Value::STR>()) {
        Value::STR str = val.get<Value::STR>();

        if (index < 0 || static_cast<size_t>(index) >= str.size()) {
            throw std::runtime_error("Error: index out of range\n");
        }

        node->setVal(Value::STR{str[index]});
    } else if (val.is<Value::LIST>()) {
        Value::LIST list = val.get<Value::LIST>();

        if (index < 0 || index >= list.size()) {
            throw std::runtime_error("Error: index out of range\n");
        }

        node->setVal(list[index]);
    } else {
        throw std::runtime_error("Error: invalid index operation\n");
    }
}

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

    std::vector<Value> values;
    for (size_t i = 0; i < childNodes.size(); ++i) {
        childNodes[i]->accept(shared_from_this());
        values.emplace_back(childNodes[i]->getVal());
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

void Evaluator::visit(const std::shared_ptr<TableNode> &node) {}

void Evaluator::visit(const std::shared_ptr<UnaryExprNode> &node) {}

void Evaluator::visit(const std::shared_ptr<WhileNode> &node) {}

void Evaluator::initPtable() {
    Procedure::ProcType print = [](std::vector<std::shared_ptr<AstNode>> arg) {
        std::cout << arg[0]->getVal().toString() << '\n';
        return nullptr;
    };

    Procedure::ProcType input = [](std::vector<std::shared_ptr<AstNode>> arg) {
        std::cout << arg[0]->getVal().toString();
        std::string inputStr;
        std::getline(std::cin, inputStr);
        return inputStr;
    };

    Procedure::ProcType type = [](std::vector<std::shared_ptr<AstNode>> arg) {
        return arg[0]->getVal().toTypeString();
    };

    Procedure::ProcType str = [](std::vector<std::shared_ptr<AstNode>> arg) {
        return arg[0]->getVal().toString();
    };

    ptable.bind(Procedure("print", {"msg"}, print));
    ptable.bind(Procedure("input", {"msg"}, input));
    ptable.bind(Procedure("type", {"x"}, type));
    ptable.bind(Procedure("str", {"x"}, str));
}
