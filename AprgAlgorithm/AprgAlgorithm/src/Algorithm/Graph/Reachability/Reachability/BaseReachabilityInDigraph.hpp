#pragma once

#include <Algorithm/Graph/BaseGraph.hpp>

namespace alba::algorithm {

template <typename Vertex>
class BaseReachabilityInDigraph {
public:
    BaseReachabilityInDigraph() = default;
    BaseReachabilityInDigraph(BaseReachabilityInDigraph const &) = default;
    BaseReachabilityInDigraph(BaseReachabilityInDigraph &&) = default;
    BaseReachabilityInDigraph &operator=(BaseReachabilityInDigraph const &) = default;
    BaseReachabilityInDigraph &operator=(BaseReachabilityInDigraph &&) = default;
    virtual ~BaseReachabilityInDigraph() = default;  // virtual destructor because of virtual functions (vtable exists)
    [[nodiscard]] virtual bool isReachable(Vertex const &destinationVertex) const = 0;
};

}  // namespace alba::algorithm
