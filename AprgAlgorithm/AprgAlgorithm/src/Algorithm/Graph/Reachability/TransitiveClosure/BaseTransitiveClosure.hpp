#pragma once

namespace alba::algorithm {

template <typename Vertex>
class BaseTransitiveClosure {
public:
    BaseTransitiveClosure() = default;
    virtual ~BaseTransitiveClosure() = default;  // virtual destructor because of virtual functions (vtable exists)
    BaseTransitiveClosure(BaseTransitiveClosure const &) = default;
    BaseTransitiveClosure(BaseTransitiveClosure &&) noexcept = default;
    BaseTransitiveClosure &operator=(BaseTransitiveClosure const &) = default;
    BaseTransitiveClosure &operator=(BaseTransitiveClosure &&) noexcept = default;
    [[nodiscard]] virtual bool isReachable(Vertex const &sourceVertex, Vertex const &destinationVertex) const = 0;
};

}  // namespace alba::algorithm
