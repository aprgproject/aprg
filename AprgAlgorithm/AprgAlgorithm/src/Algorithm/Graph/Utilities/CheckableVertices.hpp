#pragma once

#include <Algorithm/Graph/Types/GraphTypes.hpp>

#include <algorithm>
#include <iterator>

namespace alba::algorithm {

template <typename Vertex>
class CheckableVertices {
public:
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using SetOfVertices = typename GraphTypes<Vertex>::SetOfVertices;
    CheckableVertices() = default;
    [[nodiscard]] SetOfVertices const& getVertices() const { return m_vertices; }
    [[nodiscard]] bool isFound(Vertex const& vertex) const { return m_vertices.find(vertex) != m_vertices.cend(); }
    [[nodiscard]] bool isNotFound(Vertex const& vertex) const { return m_vertices.find(vertex) == m_vertices.cend(); }
    void putVertex(Vertex const& vertex) { m_vertices.emplace(vertex); }

    void putVertices(Vertices const& vertices) {
        std::copy(vertices.cbegin(), vertices.cend(), std::inserter(m_vertices, m_vertices.cbegin()));
    }

    void removeVertex(Vertex const& vertex) { m_vertices.erase(vertex); }
    void clear() { m_vertices.clear(); }

private:
    SetOfVertices m_vertices;
};

}  // namespace alba::algorithm
