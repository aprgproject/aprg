#pragma once

namespace alba::algorithm {

template <typename Object>
class BaseQueue {
public:
    BaseQueue() = default;
    virtual ~BaseQueue() = default;  // virtual destructor because of virtual functions (vtable exists)
    BaseQueue(BaseQueue const &) = default;
    BaseQueue(BaseQueue &&) noexcept = default;
    BaseQueue &operator=(BaseQueue const &) = default;
    BaseQueue &operator=(BaseQueue &&) noexcept = default;
    [[nodiscard]] virtual int getSize() const = 0;
    [[nodiscard]] virtual bool isEmpty() const = 0;
    virtual void enqueue(Object const &object) = 0;  // Add item to the end of the list
    virtual Object dequeue() = 0;                    // Remove item from the beginning of the list
};

}  // namespace alba::algorithm
