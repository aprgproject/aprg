#pragma once

#include <functional>

namespace alba::algorithm {

template <typename Object>
class BaseBag {
    // Bag data stucture just collects data and can traverse the data (order does not matter)
public:
    using TraverseFunction = std::function<void(Object const &object)>;
    BaseBag() = default;
    virtual ~BaseBag() = default;  // virtual destructor because of virtual functions (vtable exists)
    BaseBag(BaseBag const &) = default;
    BaseBag(BaseBag &&) noexcept = default;
    BaseBag &operator=(BaseBag const &) = default;
    BaseBag &operator=(BaseBag &&) noexcept = default;
    [[nodiscard]] virtual int getSize() const = 0;
    [[nodiscard]] virtual bool isEmpty() const = 0;
    virtual void add(Object const &object) = 0;
    virtual void traverse(TraverseFunction const &traverseFunction) = 0;
};

}  // namespace alba::algorithm
