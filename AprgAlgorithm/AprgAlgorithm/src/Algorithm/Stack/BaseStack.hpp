#pragma once

namespace alba::algorithm {

template <typename Object>
class BaseStack {
public:
    virtual ~BaseStack() = default;  // virtual destructor because of virtual functions (vtable exists)
    [[nodiscard]] virtual bool isEmpty() const = 0;
    [[nodiscard]] virtual int getSize() const = 0;
    virtual Object pop() = 0;
    virtual void push(Object const& object) = 0;
};

}  // namespace alba::algorithm
