#include <IndexNode.hpp>

void IndexNode::addChild(std::shared_ptr<AstNode> child) {
    if (getRightNode() == nullptr) {
        setRightNode(child);
    } else if (getLeftNode() == nullptr) {
        setLeftNode(child);
    } else {
        throw std::runtime_error("BinaryNode already has two children");
    }
}
