#pragma once

#include <Algorithm/Graph/PathSearch/DirectedAcyclicGraph/PathSearchForDirectedAcyclicGraph.hpp>
#include <Algorithm/Graph/Tree/LongestPathsInTree.hpp>

namespace alba::algorithm::GraphUtilities {

template <typename Vertex>
int getDiameterOfATree(BaseUndirectedGraph<Vertex> const& graph) {
    // The diameter of a tree is the maximum length of a path between two nodes.
    LongestPathsInTree<Vertex> longestPathsInTree(graph);
    longestPathsInTree.searchForAtLeastOneEndPointPair();
    return longestPathsInTree.getLongestDistance();
}

template <typename Vertex, typename Weight, typename EdgeWeightedGraphType>
typename GraphTypes<Vertex>::Path getCriticalPath(
    EdgeWeightedGraphType const& graph, Vertex const& sourceVertex, Vertex const& destinationVertex) {
    using Path = typename GraphTypes<Vertex>::Path;

    Path result;
    // Needs to be a directed acyclic path because if not the maximum path will be forever loop around the cycle
    if (isDirectedAcyclicGraph(graph)) {
        // Use greater comparison for longest path
        PathSearchForDirectedAcyclicGraph<Vertex, Weight, EdgeWeightedGraphType, std::greater> pathSearch(
            graph, sourceVertex);
        result = pathSearch.getPathTo(destinationVertex);
    }
    return result;
}

}  // namespace alba::algorithm::GraphUtilities
