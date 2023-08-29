#pragma once

#include <Algorithm/Graph/BaseGraph.hpp>

namespace alba::algorithm {

template <typename Vertex>
class BaseUndirectedGraph : public BaseGraph<Vertex> {
public:
    // virtual destructor because of virtual functions (vtable exists)
    ~BaseUndirectedGraph() override = default;

    [[nodiscard]] virtual bool hasAnyConnection(Vertex const& vertex) const = 0;

    [[nodiscard]] GraphDirectionType getGraphDirectionType() const override { return DIRECTION_TYPE; }
    static constexpr GraphDirectionType DIRECTION_TYPE = GraphDirectionType::Undirected;
};

}  // namespace alba::algorithm
