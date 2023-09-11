#include "ReversingALinkedList.hpp"

using namespace std;

namespace alba::ReversingALinkedList {

unique_ptr<Node> reverseALinkedList(unique_ptr<Node> head) {
    unique_ptr<Node> result;
    if (head) {
        unique_ptr<Node> current = std::move(head->nextPointer);
        result = std::move(head);
        while (current) {
            unique_ptr<Node> temporary = std::move(current->nextPointer);
            current->nextPointer = std::move(result);
            result = std::move(current);
            current = std::move(temporary);
        }
    }
    return result;
}

}  // namespace alba::ReversingALinkedList
