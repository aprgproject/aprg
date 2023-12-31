#pragma once

#include <Algorithm/Graph/ConnectedComponents/Common/BaseConnectedComponentsWithVertexToComponentIdMap.hpp>
#include <Algorithm/Graph/UndirectedGraph/BaseUndirectedGraph.hpp>
#include <Algorithm/UnionFind/UnionFindUsingMap.hpp>

namespace alba::algorithm {

template <typename Vertex>
class ConnectedComponentsUsingUnionFind
    : public BaseConnectedComponentsWithVertexToComponentIdMap<Vertex, BaseUndirectedGraph<Vertex>> {
public:
    using BaseUndirectedGraphWithVertex = BaseUndirectedGraph<Vertex>;
    using BaseClass = BaseConnectedComponentsWithVertexToComponentIdMap<Vertex, BaseUndirectedGraphWithVertex>;
    using SetOfVertices = typename GraphTypes<Vertex>::SetOfVertices;
    using Edge = typename GraphTypes<Vertex>::Edge;
    using VertexToIntMap = typename GraphTypes<Vertex>::VertexToIntMap;
    using UnionFind = UnionFindUsingMap<Vertex>;

    explicit ConnectedComponentsUsingUnionFind(BaseUndirectedGraphWithVertex const& graph)
        : BaseClass(graph),
          b_graph(BaseClass::m_graph),
          b_numberOfComponentIds(BaseClass::m_numberOfComponentIds),
          b_vertexToComponentIdMap(BaseClass::m_vertexToComponentIdMap) {
        initialize();
    }

private:
    void initialize() {
        UnionFind unionFind;
        for (Edge const& edge : b_graph.getEdges()) {
            unionFind.connect(edge.first, edge.second);
        }
        SetOfVertices roots;
        for (Vertex const& vertex : b_graph.getVertices()) {
            int componentId{};
            Vertex root(unionFind.getRoot(vertex));
            auto it = roots.find(root);
            if (it != roots.cend()) {
                componentId = std::distance(roots.cbegin(), it);
            } else {
                componentId = roots.size();
                roots.emplace(root);
            }
            b_vertexToComponentIdMap[vertex] = componentId + 1;
        }
        b_numberOfComponentIds = roots.size();
    }

    BaseUndirectedGraphWithVertex const& b_graph;
    int& b_numberOfComponentIds;
    VertexToIntMap& b_vertexToComponentIdMap;
};

}  // namespace alba::algorithm
