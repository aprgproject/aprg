#pragma once

#include <memory>

namespace alba::ReversingALinkedList {

struct Node {
    int value;
    std::unique_ptr<Node> nextPointer;
    // ~Node(); blows up the stack
};

std::unique_ptr<Node> reverseALinkedList(std::unique_ptr<Node> head);

}  // namespace alba::ReversingALinkedList
