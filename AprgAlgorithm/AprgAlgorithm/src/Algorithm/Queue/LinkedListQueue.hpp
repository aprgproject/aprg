#pragma once

#include <Algorithm/Queue/BaseQueue.hpp>

#include <cassert>
#include <memory>

namespace alba::algorithm {

template <typename Object>
class LinkedListQueue : public BaseQueue<Object> {
public:
    struct Node;
    using NodeUniquePointer = std::unique_ptr<Node>;

    struct Node {
        Object object;
        NodeUniquePointer next;
    };

    LinkedListQueue() : m_first(nullptr), m_nextOfLastDoublePointer(&m_first) {}
    [[nodiscard]] int getSize() const override { return m_size; }
    [[nodiscard]] bool isEmpty() const override { return m_first == nullptr; }

    void enqueue(Object const& object) override {
        *m_nextOfLastDoublePointer = NodeUniquePointer(new Node{object, nullptr});
        m_nextOfLastDoublePointer = &((*m_nextOfLastDoublePointer)->next);
        ++m_size;
    }

    Object dequeue() override {
        assert(m_first);
        Object result{};
        if (m_first) {
            result = m_first->object;
            m_first = std::move(m_first->next);
            --m_size;
            if (isEmpty()) {
                m_nextOfLastDoublePointer = &m_first;
            }
        }
        return result;
    }

private:
    int m_size{};
    NodeUniquePointer m_first;
    NodeUniquePointer* m_nextOfLastDoublePointer;
};

}  // namespace alba::algorithm
