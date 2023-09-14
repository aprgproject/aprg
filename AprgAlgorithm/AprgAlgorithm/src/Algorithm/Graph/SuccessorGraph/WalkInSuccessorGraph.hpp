#pragma once

#include <Algorithm/Graph/DirectedGraph/BaseDirectedGraph.hpp>
#include <Common/Math/Helpers/FactorAndMultiplesHelpers.hpp>

namespace alba::algorithm {

template <typename Vertex>
class WalkInSuccessorGraph {
public:
    using BaseDirectedGraphWithVertex = BaseDirectedGraph<Vertex>;
    using Edge = typename GraphTypes<Vertex>::Edge;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using VertexAndCountPair = std::pair<Vertex, int>;
    using VertexAndCountPairToVertexMap = std::map<VertexAndCountPair, Vertex>;
    explicit WalkInSuccessorGraph(BaseDirectedGraphWithVertex const& graph) : m_graph(graph) {}
    [[nodiscard]] bool isAtTheEnd(Vertex const& vertex) const { return m_graph.getAdjacentVerticesAt(vertex).empty(); }
    Vertex walk(Vertex const& start, int const distance) { return walkInternal(start, distance); }

private:
    Vertex walkInternal(Vertex const& vertex, int const distance) {
        Vertex result(vertex);
        if (distance > 0) {
            auto it = m_startAndDistancePairToDestinationMap.find({vertex, distance});
            if (it != m_startAndDistancePairToDestinationMap.cend()) {
                result = it->second;
            } else {
                if (distance > 1) {
                    int const halfDistance = distance / 2;
                    result = walkInternal(walkInternal(vertex, distance - halfDistance), halfDistance);
                } else if (distance == 1) {
                    Vertices adjacentVertices(
                        m_graph.getAdjacentVerticesAt(vertex));  // should be one because its a successor graph
                    if (!adjacentVertices.empty()) {
                        result = adjacentVertices.front();
                    }
                }
                if (mathHelper::isPowerOfTwo(distance) != 0) {
                    // save distance if power of 2
                    m_startAndDistancePairToDestinationMap.emplace(VertexAndCountPair{vertex, distance}, result);
                }
            }
        }
        return result;
    }

    BaseDirectedGraphWithVertex const& m_graph;
    VertexAndCountPairToVertexMap m_startAndDistancePairToDestinationMap;  // dynamic programming
};

}  // namespace alba::algorithm
