#pragma once

#include <Algorithm/Graph/Types/GraphTypes.hpp>

#include <string>

namespace alba::algorithm {

template <typename Vertex>
class BaseGraph {
public:
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using Edges = typename GraphTypes<Vertex>::Edges;
    BaseGraph() = default;
    virtual ~BaseGraph() = default;  // virtual destructor because of virtual functions (vtable exists)
    BaseGraph(BaseGraph const& graph) = default;
    BaseGraph(BaseGraph&& graph) noexcept = default;
    BaseGraph& operator=(BaseGraph const& graph) = default;
    BaseGraph& operator=(BaseGraph&& graph) noexcept = default;
    [[nodiscard]] virtual Edges getEdges() const = 0;
    [[nodiscard]] virtual GraphDirectionType getGraphDirectionType() const = 0;
    [[nodiscard]] virtual Vertices getAdjacentVerticesAt(Vertex const& vertex) const = 0;
    [[nodiscard]] virtual Vertices getVertices() const = 0;
    [[nodiscard]] virtual int getNumberOfVertices() const = 0;
    [[nodiscard]] virtual int getNumberOfEdges() const = 0;
    [[nodiscard]] virtual bool isEmpty() const = 0;
    [[nodiscard]] virtual bool isDirectlyConnected(Vertex const& vertex1, Vertex const& vertex2) const = 0;
    virtual void connect(Vertex const& sourceVertex, Vertex const& destinationVertex) = 0;
    virtual void disconnect(Vertex const& sourceVertex, Vertex const& destinationVertex) = 0;
    virtual void clear() = 0;
};

}  // namespace alba::algorithm
