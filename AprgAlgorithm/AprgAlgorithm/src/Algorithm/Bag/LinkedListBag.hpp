#pragma once

#include <Algorithm/Bag/BaseBag.hpp>

#include <memory>

namespace alba::algorithm {

template <typename Object>
class LinkedListBag : public BaseBag<Object> {
public:
    using BaseClass = BaseBag<Object>;
    using TraverseFunction = typename BaseBag<Object>::TraverseFunction;
    struct Node;
    using NodeUniquePointer = std::unique_ptr<Node>;

    struct Node {
        Object object;
        NodeUniquePointer next;
    };

    LinkedListBag() : m_first(nullptr) {}
    [[nodiscard]] int getSize() const override { return m_size; }
    [[nodiscard]] bool isEmpty() const override { return m_size == 0; }

    void add(Object const& object) override {
        m_first = NodeUniquePointer(new Node{object, std::move(m_first)});
        ++m_size;
    }

    void traverse(TraverseFunction const& traverseFunction) override {
        Node* currentPointer = m_first.get();
        while (currentPointer != nullptr) {
            traverseFunction(currentPointer->object);
            currentPointer = currentPointer->next.get();
        }
    }

private:
    int m_size{};
    NodeUniquePointer m_first;
};

}  // namespace alba::algorithm
