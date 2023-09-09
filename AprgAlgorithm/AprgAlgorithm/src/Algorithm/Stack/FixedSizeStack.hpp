#pragma once

#include <Algorithm/Stack/BaseStack.hpp>

#include <array>
#include <cassert>

namespace alba::algorithm {

template <typename Object, int SIZE>
class FixedSizeStack : public BaseStack<Object> {
public:
    using Objects = std::array<Object, SIZE>;
    FixedSizeStack() = default;
    [[nodiscard]] Objects const& getObjects() const { return m_objects; }
    [[nodiscard]] int getSize() const override { return m_size; }
    [[nodiscard]] bool isEmpty() const override { return m_size == 0; }

    void push(Object const& object) override {
        // runs in constant time and no allocation (faster than linked list)
        assert(m_size < SIZE);
        m_objects[m_size++] = object;
    }

    Object pop() override {
        // runs in constant time and no deallocation (faster than linked list)
        assert(m_size > 0);
        return m_objects[--m_size];
    }

private:
    int m_size{0};
    Objects m_objects{};
};

}  // namespace alba::algorithm
