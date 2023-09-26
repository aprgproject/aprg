#pragma once

#include <Algorithm/Graph/BaseGraph.hpp>

namespace alba::algorithm {

template <typename Vertex>
class BaseReachabilityInDigraph {
public:
    BaseReachabilityInDigraph() = default;
    virtual ~BaseReachabilityInDigraph() = default;  // virtual destructor because of virtual functions (vtable exists)
    BaseReachabilityInDigraph(BaseReachabilityInDigraph const &) = default;
    BaseReachabilityInDigraph(BaseReachabilityInDigraph &&) noexcept = default;
    BaseReachabilityInDigraph &operator=(BaseReachabilityInDigraph const &) = default;
    BaseReachabilityInDigraph &operator=(BaseReachabilityInDigraph &&) noexcept = default;
    [[nodiscard]] virtual bool isReachable(Vertex const &destinationVertex) const = 0;
};

}  // namespace alba::algorithm
