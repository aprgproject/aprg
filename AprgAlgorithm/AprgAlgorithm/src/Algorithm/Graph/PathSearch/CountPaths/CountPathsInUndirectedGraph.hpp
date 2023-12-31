#pragma once

#include <Algorithm/Graph/UndirectedGraph/BaseUndirectedGraph.hpp>
#include <Algorithm/Graph/Utilities/CheckableVertices.hpp>

namespace alba::algorithm {

template <typename Vertex>
class CountPathsInUndirectedGraph {
public:
    using BaseUndirectedGraphWithVertex = BaseUndirectedGraph<Vertex>;
    using CheckableVerticesWithVertex = CheckableVertices<Vertex>;
    using VertexPair = std::pair<Vertex, Vertex>;
    using VertexPairToCountMap = std::map<VertexPair, int>;
    explicit CountPathsInUndirectedGraph(BaseUndirectedGraphWithVertex const& graph) : m_graph(graph) {}
    int getCount(Vertex const& start, Vertex const& end) { return getCountInternal(start, end); }

private:
    void traverseUsingDfs(Vertex const& start, Vertex const& current, CheckableVerticesWithVertex& processingVertices) {
        processingVertices.putVertex(current);
        for (Vertex const& adjacentToCurrent : m_graph.getAdjacentVerticesAt(current)) {
            if (processingVertices.isNotFound(adjacentToCurrent)) {
                traverseUsingDfs(start, adjacentToCurrent, processingVertices);
                VertexPair const endPointPair{start, adjacentToCurrent};
                m_pathCounts.emplace(endPointPair, 0);
                m_pathCounts[endPointPair]++;
            }
        }
        processingVertices.removeVertex(current);
    }

    int getCountInternal(Vertex const& start, Vertex const& end) {
        int result(1);  // if start and end are equal, then return one count
        if (start != end) {
            auto it = m_pathCounts.find({start, end});
            if (it != m_pathCounts.cend()) {
                result = it->second;
            } else {
                CheckableVerticesWithVertex processingVertices;
                processingVertices.putVertex(start);
                traverseUsingDfs(
                    start, start,
                    processingVertices);  // complete DFS search, to count all paths starting from this vertex
                result = m_pathCounts[{start, end}];
            }
        }
        return result;
    }

    BaseUndirectedGraphWithVertex const& m_graph;
    VertexPairToCountMap m_pathCounts;  // dynamic programming
};

}  // namespace alba::algorithm
