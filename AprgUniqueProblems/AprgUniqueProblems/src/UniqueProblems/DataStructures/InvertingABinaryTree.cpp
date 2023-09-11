#include "InvertingABinaryTree.hpp"

using namespace std;

namespace alba::InvertingABinaryTree {

unique_ptr<Node> invertABinaryTree(unique_ptr<Node> parent) {
    if (parent) {
        unique_ptr<Node> newRightChild = std::move(parent->leftPointer);
        unique_ptr<Node> newLeftChild = std::move(parent->rightPointer);
        parent->leftPointer = invertABinaryTree(std::move(newLeftChild));
        parent->rightPointer = invertABinaryTree(std::move(newRightChild));
    }
    return parent;
}

}  // namespace alba::InvertingABinaryTree
