#pragma once

#include <Algorithm/Queue/BaseQueue.hpp>

#include <cassert>
#include <memory>

namespace alba::algorithm {

template <typename Object, typename StackWithObject>
class QueueUsingTwoStacks : public BaseQueue<Object> {
public:
    QueueUsingTwoStacks() = default;
    [[nodiscard]] int getSize() const override { return m_stackFromEnqueue.getSize() + m_stackToDequeue.getSize(); }
    [[nodiscard]] bool isEmpty() const override { return getSize() == 0; }

    void enqueue(Object const& object) override {
        enqueueInConstantTime(object);
        // enqueueInAmortizedConstantTime(object);
    }

    Object dequeue() override { return dequeueInAmortizedConstantTime(); }

private:
    void enqueueInConstantTime(Object const& object) { m_stackFromEnqueue.push(object); }

    void enqueueInAmortizedConstantTime(Object const& object) {
        // the best size can be determined by the total size used but lets just keep it simple
        constexpr int bestSizeToTransfer = 10;

        m_stackFromEnqueue.push(object);
        if (bestSizeToTransfer >= getSize()) {
            transferAllIfPossible();
        }
    }

    void transferAllIfPossible() {
        if (m_stackToDequeue.isEmpty()) {
            while (!m_stackFromEnqueue.isEmpty()) {
                m_stackToDequeue.push(m_stackFromEnqueue.pop());
            }
        }
    }

    Object dequeueInAmortizedConstantTime() {
        transferAllIfPossible();
        return m_stackToDequeue.pop();
    }

    StackWithObject m_stackFromEnqueue;
    StackWithObject m_stackToDequeue;
};

}  // namespace alba::algorithm
