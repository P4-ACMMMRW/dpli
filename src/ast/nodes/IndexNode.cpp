#include <IndexNode.hpp>

using namespace dplsrc;

void IndexNode::addChild(std::shared_ptr<AstNode> child) {
    if (getRightNode() == nullptr) {
        setRightNode(child);
    } else if (getLeftNode() == nullptr) {
        setLeftNode(child);
    } else {
        throw AstException("BinaryNode already has two children");
    }
}
