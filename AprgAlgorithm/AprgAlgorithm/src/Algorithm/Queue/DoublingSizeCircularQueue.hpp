#pragma once

#include <Algorithm/Queue/BaseQueue.hpp>

#include <algorithm>
#include <cassert>
#include <memory>

namespace alba::algorithm {

template <typename Object>
class DoublingSizeCircularQueue : public BaseQueue<Object> {
public:
    DoublingSizeCircularQueue() { initialize(MINUMUM_CONTAINER_SIZE); }
    ~DoublingSizeCircularQueue() override = default;
    DoublingSizeCircularQueue(DoublingSizeCircularQueue const &) = default;
    DoublingSizeCircularQueue(DoublingSizeCircularQueue &&) noexcept = default;
    DoublingSizeCircularQueue &operator=(DoublingSizeCircularQueue const &) = default;
    DoublingSizeCircularQueue &operator=(DoublingSizeCircularQueue &&) noexcept = default;

    [[nodiscard]] int getSize() const override {
        if (m_firstIndex <= m_afterLastIndex) {
            return m_afterLastIndex - m_firstIndex;
        }
        return m_containerSize - m_firstIndex + m_afterLastIndex;
    }

    [[nodiscard]] bool isEmpty() const override { return getSize() == 0; }

    void enqueue(Object const &object) override {
        resizeOnEnqueueIfNeeded();
        moveBackIndexIfNeeded(m_afterLastIndex);
        m_objects[m_afterLastIndex++] = object;
    }

    Object dequeue() override {
        // should be not empty
        assert(m_firstIndex != m_afterLastIndex);
        moveBackIndexIfNeeded(m_firstIndex);
        Object result(m_objects[m_firstIndex++]);
        resizeOnDequeueIfNeeded();
        return result;
    }

    [[nodiscard]] int getContainerSize() const { return m_containerSize; }
    static constexpr int MINUMUM_CONTAINER_SIZE = 1;

private:
    void initialize(int const initialSize) {
        m_objects = std::make_unique<Object[]>(initialSize);
        m_containerSize = initialSize;
    }

    void moveBackIndexIfNeeded(int &index) {
        if (index >= m_containerSize) {
            index = 0;
        }
    }

    void resize(int const newSize) {
        auto newObjects = std::make_unique<Object[]>(newSize);
        if (m_objects != nullptr) {
            if (m_firstIndex <= m_afterLastIndex) {
                std::copy(m_objects.get() + m_firstIndex, m_objects.get() + m_afterLastIndex, newObjects.get());
            } else {
                std::copy(m_objects.get() + m_firstIndex, m_objects.get() + m_containerSize, newObjects.get());
                std::copy(
                    m_objects.get(), m_objects.get() + m_afterLastIndex,
                    newObjects.get() + m_containerSize - m_firstIndex);
            }
        }
        m_afterLastIndex = getSize();
        m_firstIndex = 0;
        swap(m_objects, newObjects);
        m_containerSize = newSize;
    }

    void resizeOnEnqueueIfNeeded() {
        if (getSize() >= m_containerSize) {
            resize(m_containerSize * 2);
        }
    }

    void resizeOnDequeueIfNeeded() {
        if (m_containerSize > 0 && getSize() == m_containerSize / 4) {
            resize(std::max(MINUMUM_CONTAINER_SIZE, m_containerSize / 2));
        }
    }

    int m_containerSize{};
    int m_firstIndex{};
    int m_afterLastIndex{};
    std::unique_ptr<Object[]> m_objects;
};

}  // namespace alba::algorithm
