#pragma once

#include <memory>

namespace alba::InvertingABinaryTree {

struct Node {
    int value;
    std::unique_ptr<Node> leftPointer;
    std::unique_ptr<Node> rightPointer;
    // ~Node(); blows up the stack
};

std::unique_ptr<Node> invertABinaryTree(std::unique_ptr<Node> parent);

}  // namespace alba::InvertingABinaryTree
