#pragma once

#include <Algorithm/Graph/DirectedGraph/BaseDirectedGraph.hpp>

#include <algorithm>
#include <ostream>

namespace alba::algorithm {

template <typename Vertex>
class DirectedGraphWithListOfEdges : public BaseDirectedGraph<Vertex> {
public:
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using SetOfVertices = typename GraphTypes<Vertex>::SetOfVertices;
    using Edge = typename GraphTypes<Vertex>::Edge;
    using Edges = typename GraphTypes<Vertex>::Edges;
    using SetOfEdges = typename GraphTypes<Vertex>::SetOfEdges;
    DirectedGraphWithListOfEdges() = default;

    [[nodiscard]] Edges getEdges() const override {
        Edges result;
        result.reserve(m_edges.size());
        std::transform(
            m_edges.cbegin(), m_edges.cend(), std::back_inserter(result), [](Edge const& edge) { return edge; });
        return result;
    }

    [[nodiscard]] Vertices getAdjacentVerticesAt(Vertex const& vertex) const override {
        Vertices result;
        for (auto it = m_edges.lower_bound({vertex, Vertex{}}); it != m_edges.cend() && it->first == vertex; ++it) {
            result.emplace_back(it->second);
        };
        return result;
    }

    [[nodiscard]] Vertices getVertices() const override {
        SetOfVertices const uniqueVertices(getUniqueVertices());
        return Vertices(uniqueVertices.cbegin(), uniqueVertices.cend());
    }

    [[nodiscard]] int getNumberOfVertices() const override { return getUniqueVertices().size(); }
    [[nodiscard]] int getNumberOfEdges() const override { return m_numberOfEdges; }
    [[nodiscard]] bool isEmpty() const override { return m_edges.empty(); }

    [[nodiscard]] bool isDirectlyConnected(Vertex const& sourceVertex, Vertex const& destinationVertex) const override {
        return m_edges.find({sourceVertex, destinationVertex}) != m_edges.cend();
    }

    void connect(Vertex const& sourceVertex, Vertex const& destinationVertex) override {
        if (!isDirectlyConnected(sourceVertex, destinationVertex)) {
            ++m_numberOfEdges;
            m_edges.emplace(sourceVertex, destinationVertex);
        }
    }

    void disconnect(Vertex const& sourceVertex, Vertex const& destinationVertex) override {
        if (isDirectlyConnected(sourceVertex, destinationVertex)) {
            --m_numberOfEdges;
            m_edges.erase({sourceVertex, destinationVertex});
        }
    }

    void clear() override {
        m_numberOfEdges = 0;
        m_edges.clear();
    }

protected:
    [[nodiscard]] SetOfVertices getUniqueVertices() const {
        SetOfVertices uniqueVertices;
        for (auto const& [startVertexOfEdge, endVertexOfEdge] : m_edges) {
            uniqueVertices.emplace(startVertexOfEdge);
            uniqueVertices.emplace(endVertexOfEdge);
        }
        return uniqueVertices;
    }

    friend std::ostream& operator<<(std::ostream& out, DirectedGraphWithListOfEdges const& graph) {
        out << "Edges: {";
        for (auto const& edge : graph.m_edges) {
            out << edge.first << "->" << edge.second << ", ";
        }
        out << "}";
        return out;
    }

    int m_numberOfEdges{};
    SetOfEdges m_edges;
};

}  // namespace alba::algorithm
