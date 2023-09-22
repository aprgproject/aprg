#pragma once

namespace alba::algorithm {

template <typename Object>
class BaseStack {
public:
    // virtual destructor because of virtual functions (vtable exists)
    virtual ~BaseStack() = default;
    BaseStack() = default;
    BaseStack(BaseStack const &) = default;
    BaseStack(BaseStack &&) = default;
    BaseStack &operator=(BaseStack const &) = default;
    BaseStack &operator=(BaseStack &&) = default;
    [[nodiscard]] virtual int getSize() const = 0;
    [[nodiscard]] virtual bool isEmpty() const = 0;
    virtual void push(Object const &object) = 0;
    virtual Object pop() = 0;
};

}  // namespace alba::algorithm
