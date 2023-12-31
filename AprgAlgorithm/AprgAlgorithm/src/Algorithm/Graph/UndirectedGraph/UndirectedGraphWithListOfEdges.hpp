#pragma once

#include <Algorithm/Graph/UndirectedGraph/BaseUndirectedGraph.hpp>

#include <algorithm>
#include <ostream>

namespace alba::algorithm {

template <typename Vertex>
class UndirectedGraphWithListOfEdges : public BaseUndirectedGraph<Vertex> {
public:
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using Edge = typename GraphTypes<Vertex>::Edge;
    using Edges = typename GraphTypes<Vertex>::Edges;
    using SetOfEdges = typename GraphTypes<Vertex>::SetOfEdges;
    UndirectedGraphWithListOfEdges() = default;

    [[nodiscard]] Edges getEdges() const override {
        Edges result;
        copy_if(m_edges.cbegin(), m_edges.cend(), back_inserter(result), [&](auto const& edge) {
            return edge.first <= edge.second;
        });
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
        Vertices result;
        for (auto const& [startVertexOfEdge, endVertexOfEdge] : m_edges) {
            if (result.empty() || (result.back() != startVertexOfEdge)) {
                result.emplace_back(startVertexOfEdge);
            }
        }
        return result;
    }

    [[nodiscard]] int getNumberOfVertices() const override { return getVertices().size(); }
    [[nodiscard]] int getNumberOfEdges() const override { return m_numberOfEdges; }
    [[nodiscard]] bool isEmpty() const override { return m_edges.empty(); }

    [[nodiscard]] bool hasAnyConnection(Vertex const& vertex) const override {
        bool result(false);
        auto itLower = m_edges.lower_bound({vertex, Vertex{}});
        if (itLower != m_edges.cend()) {
            result = itLower->first == vertex;
        }
        return result;
    }

    [[nodiscard]] bool isDirectlyConnected(Vertex const& vertex1, Vertex const& vertex2) const override {
        return m_edges.find({vertex1, vertex2}) != m_edges.cend();
    }

    void connect(Vertex const& vertex1, Vertex const& vertex2) override {
        if (!isDirectlyConnected(vertex1, vertex2)) {
            ++m_numberOfEdges;
            m_edges.emplace(vertex1, vertex2);
            m_edges.emplace(vertex2, vertex1);
        }
    }

    void disconnect(Vertex const& vertex1, Vertex const& vertex2) override {
        if (isDirectlyConnected(vertex1, vertex2)) {
            --m_numberOfEdges;
            m_edges.erase({vertex1, vertex2});
            m_edges.erase({vertex2, vertex1});
        }
    }

    void clear() override {
        m_numberOfEdges = 0;
        m_edges.clear();
    }

    SetOfEdges& getSetOfEdgesReference() { return m_edges; }

protected:
    friend std::ostream& operator<<(std::ostream& out, UndirectedGraphWithListOfEdges const& graph) {
        out << "Edges: {";
        for (auto const& edge : graph.m_edges) {
            out << edge.first << "<->" << edge.second << ", ";
        }
        out << "}";
        return out;
    }

    int m_numberOfEdges{};
    SetOfEdges m_edges{};
};

}  // namespace alba::algorithm
