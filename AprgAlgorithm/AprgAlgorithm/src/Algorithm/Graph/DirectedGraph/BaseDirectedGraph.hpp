#pragma once

#include <Algorithm/Graph/BaseGraph.hpp>

namespace alba::algorithm {

template <typename Vertex>
class BaseDirectedGraph : public BaseGraph<Vertex> {
public:
    using Edges = typename GraphTypes<Vertex>::Edges;
    ~BaseDirectedGraph() override = default;  // no need for virtual destructor because base destructor is virtual
    BaseDirectedGraph() = default;
    BaseDirectedGraph(BaseDirectedGraph const &) = default;
    BaseDirectedGraph(BaseDirectedGraph &&) = default;
    BaseDirectedGraph &operator=(BaseDirectedGraph const &) = default;
    BaseDirectedGraph &operator=(BaseDirectedGraph &&) = default;
    // (similar to other virtual functions)
    [[nodiscard]] GraphDirectionType getGraphDirectionType() const override { return DIRECTION_TYPE; }

    void reverseDirections() {
        Edges const originalEdges(this->getEdges());
        this->clear();
        for (auto const &[startVertexOfEdge, endVertexOfEdge] : originalEdges) {
            this->connect(endVertexOfEdge, startVertexOfEdge);
        }
    }

    static constexpr GraphDirectionType DIRECTION_TYPE = GraphDirectionType::Directed;
};

}  // namespace alba::algorithm
