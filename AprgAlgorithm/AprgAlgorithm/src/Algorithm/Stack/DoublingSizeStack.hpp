#pragma once

#include <Algorithm/Stack/BaseStack.hpp>

#include <algorithm>
#include <cassert>
#include <memory>

namespace alba::algorithm {

template <typename Object>
class DoublingSizeStack : public BaseStack<Object> {
public:
    DoublingSizeStack() : m_objects(nullptr) { initialize(MINUMUM_CONTAINER_SIZE); }
    ~DoublingSizeStack() override = default;
    DoublingSizeStack(DoublingSizeStack const &) = default;
    DoublingSizeStack(DoublingSizeStack &&) noexcept = default;
    DoublingSizeStack &operator=(DoublingSizeStack const &) = default;
    DoublingSizeStack &operator=(DoublingSizeStack &&) noexcept = default;
    [[nodiscard]] int getSize() const override { return m_stackSize; }
    [[nodiscard]] bool isEmpty() const override { return m_stackSize == 0; }

    // constant amortized (best case: constant, worst case: linear due to resizing)
    void push(Object const &object) override {
        resizeOnPushIfNeeded();
        m_objects[m_stackSize++] = object;
    }

    // constant amortized (best case: constant, worst case: linear due to resizing)
    Object pop() override {
        assert(m_stackSize > 0);
        Object result(m_objects[--m_stackSize]);
        resizeOnPopIfNeeded();
        return result;
    }

    [[nodiscard]] int getContainerSize() const { return m_containerSize; }
    static constexpr int MINUMUM_CONTAINER_SIZE = 1;

private:
    void initialize(int const initialSize) {
        m_objects = std::make_unique<Object[]>(initialSize);
        m_containerSize = initialSize;
    }

    void resize(int const newSize) {
        // array is between 25% and 100% full
        auto newObjects = std::make_unique<Object[]>(newSize);
        if (m_objects != nullptr) {
            std::copy(m_objects.get(), m_objects.get() + std::min(m_stackSize, newSize), newObjects.get());
        }
        std::swap(m_objects, newObjects);
        m_containerSize = newSize;
    }

    void resizeOnPushIfNeeded() {
        // only resize to double when stack is full, on average the cost is 3N -> N + (2+4+8+...+N) = 3N
        if (m_stackSize == m_containerSize) {
            resize(m_containerSize * 2);
        }
    }

    void resizeOnPopIfNeeded() {
        // only resize to half when its one-fourth full to avoid "thrashing" (push pop push pop action)
        if (m_containerSize > 0 && m_stackSize == m_containerSize / 4) {
            resize(std::max(MINUMUM_CONTAINER_SIZE, m_containerSize / 2));
        }
    }

    int m_stackSize{};
    int m_containerSize{};
    std::unique_ptr<Object[]> m_objects;
};

}  // namespace alba::algorithm
