#pragma once

#include <Algorithm/Graph/PathSearch/DepthFirstSearch/PathSearchUsingDfs.hpp>
#include <Algorithm/Graph/Utilities/GraphUtilities.hpp>
#include <Common/Bit/AlbaBitValueUtilities.hpp>

namespace alba::algorithm {

template <typename Vertex>
class AncestorsInTree {
public:
    using BaseUndirectedGraphWithVertex = BaseUndirectedGraph<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using VertexToVertexMap = typename GraphTypes<Vertex>::VertexToVertexMap;
    using VertexAndCountPair = std::pair<Vertex, int>;
    using VertexAndCountPairToVertexMap = std::map<VertexAndCountPair, Vertex>;
    using Dfs = PathSearchUsingDfs<Vertex>;
    using BitValueUtilities = AlbaBitValueUtilities<int>;

    AncestorsInTree(BaseUndirectedGraphWithVertex const& graph, Vertex const& rootOfTree)
        : m_graph(graph), m_rootOfTree(rootOfTree), m_dfs(m_graph, m_rootOfTree) {
        initializeIfNeeded();
    }

    [[nodiscard]] Vertex getAncestor(Vertex const& child, int const distance) const {
        return getAncestorInternal(child, distance);
    }

private:
    [[nodiscard]] Vertex getAncestorInternal(Vertex const& vertex, int const distance) const {
        Vertex result{};
        if (distance > 0) {
            // not zero
            if (BitValueUtilities::isPowerOfTwo(distance)) {
                // is power of two
                auto it = m_startAndDistancePairToDestinationMap.find({vertex, distance});
                if (it != m_startAndDistancePairToDestinationMap.cend()) {
                    result = it->second;
                }
            } else {
                int const powerOfTwoDistance =
                    BitValueUtilities::get2ToThePowerOf(BitValueUtilities::getLogarithmWithBase2Of(distance));
                result =
                    getAncestorInternal(getAncestorInternal(vertex, distance - powerOfTwoDistance), powerOfTwoDistance);
            }
        } else {
            result = vertex;
        }
        return result;
    }

    void initializeIfNeeded() {
        if (GraphUtilities::isATree(m_graph)) {
            initialize();
        }
    }

    void initialize() {
        VertexToVertexMap const& vertexToPreviousVertexMap(m_dfs.getVertexToPreviousVertexMap());
        for (Vertex const& child : m_graph.getVertices()) {
            int distanceFromChild(0);
            Vertex currentParent = child;
            while (m_rootOfTree != currentParent) {
                updateDestinationMapIfNeeded(child, distanceFromChild, currentParent);
                auto it = vertexToPreviousVertexMap.find(currentParent);
                if (it != vertexToPreviousVertexMap.cend()) {
                    currentParent = it->second;
                    ++distanceFromChild;
                } else {
                    break;
                }
            }
            if (m_rootOfTree == currentParent) {
                updateDestinationMapIfNeeded(child, distanceFromChild, currentParent);
            }
        }
    }

    void updateDestinationMapIfNeeded(Vertex const& child, int const distanceFromChild, Vertex const& parent) {
        if (distanceFromChild > 0 && BitValueUtilities::isPowerOfTwo(distanceFromChild)) {
            // is power of two but not zero
            m_startAndDistancePairToDestinationMap[VertexAndCountPair(child, distanceFromChild)] = parent;
        }
    }

    BaseUndirectedGraphWithVertex const& m_graph;
    Vertex m_rootOfTree;
    Dfs m_dfs;
    VertexAndCountPairToVertexMap m_startAndDistancePairToDestinationMap;
};

}  // namespace alba::algorithm
