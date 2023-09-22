#pragma once

namespace alba::algorithm {

template <typename Vertex>
class BaseTransitiveClosure {
public:
    BaseTransitiveClosure() = default;
    BaseTransitiveClosure(BaseTransitiveClosure const &) = default;
    BaseTransitiveClosure(BaseTransitiveClosure &&) = default;
    BaseTransitiveClosure &operator=(BaseTransitiveClosure const &) = default;
    BaseTransitiveClosure &operator=(BaseTransitiveClosure &&) = default;
    virtual ~BaseTransitiveClosure() = default;  // virtual destructor because of virtual functions (vtable exists)
    [[nodiscard]] virtual bool isReachable(Vertex const &sourceVertex, Vertex const &destinationVertex) const = 0;
};

}  // namespace alba::algorithm
