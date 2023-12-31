#pragma once

#include <Algorithm/Graph/DirectedGraph/BaseDirectedGraph.hpp>
#include <Algorithm/Graph/Types/GraphTypes.hpp>
#include <Algorithm/Graph/UndirectedGraph/BaseUndirectedGraph.hpp>
#include <Algorithm/Graph/Utilities/GraphUtilities.hpp>
#include <Common/Math/Helpers/DivisibilityHelpers.hpp>

namespace alba::algorithm {

template <typename Vertex>
bool areAllDegreesEven(BaseUndirectedGraph<Vertex> const& graph) {
    auto vertices(graph.getVertices());
    return std::all_of(vertices.cbegin(), vertices.cend(), [&graph](Vertex const& vertex) {
        return mathHelper::isEven(GraphUtilities::getDegreeAt(graph, vertex));
    });
}

template <typename Vertex>
bool isAtMostTwoVerticesHaveOddDegrees(BaseUndirectedGraph<Vertex> const& graph) {
    int countOfOdd(0);
    for (Vertex const& vertex : graph.getVertices()) {
        if (mathHelper::isOdd(GraphUtilities::getDegreeAt(graph, vertex))) {
            ++countOfOdd;
        }
        if (countOfOdd > 2) {
            break;
        }
    }
    return countOfOdd <= 2;
}

template <typename Vertex>
bool areAllInDegreesEqualsOutDegrees(BaseDirectedGraph<Vertex> const& graph) {
    auto vertexToDegreesPairMap(GraphUtilities::getAllInDegreesAndOutDegrees<Vertex>(graph));
    bool result(true);
    // cppcheck-suppress unusedVariable
    for (auto const& [_, degrees] : vertexToDegreesPairMap) {
        auto const& [inDegree, outDegree] = degrees;
        result = inDegree == outDegree;
        if (!result) {
            break;
        }
    }
    return result;
}

template <typename Vertex>
bool hasAtLeastOneLesserAndGreaterInAndOutDegrees(BaseDirectedGraph<Vertex> const& graph) {
    auto vertexToDegreesPairMap(GraphUtilities::getAllInDegreesAndOutDegrees<Vertex>(graph));
    int numberOfLesser(0);
    int numberOfGreater(0);
    bool result(true);
    // cppcheck-suppress unusedVariable
    for (auto const& [_, degrees] : vertexToDegreesPairMap) {
        auto const& [inDegree, outDegree] = degrees;
        bool const lesserByOne = inDegree + 1 == outDegree;
        bool const greaterByOne = inDegree == outDegree + 1;
        numberOfLesser += lesserByOne ? 1 : 0;
        numberOfGreater += greaterByOne ? 1 : 0;
        result =
            inDegree == outDegree || (lesserByOne && numberOfLesser <= 1) || (greaterByOne && numberOfGreater <= 1);
        if (!result) {
            break;
        }
    }
    return result;
}

template <typename Vertex>
bool hasEulerCycleForUndirectedGraph(BaseUndirectedGraph<Vertex> const& graph) {
    // Euler path is possible iff graph is connected and all vertices have even degree
    // A graph will contain an Euler path if it contains at most two vertices of odd degree.
    return GraphUtilities::isGraphConnected(graph) && areAllDegreesEven(graph);
}

template <typename Vertex>
bool hasEulerPathForUndirectedGraph(BaseUndirectedGraph<Vertex> const& graph) {
    // A graph will contain an Euler path if it contains at most two vertices of odd degree.
    return GraphUtilities::isGraphConnected(graph) && isAtMostTwoVerticesHaveOddDegrees(graph);
}

template <typename Vertex>
bool hasEulerCycleForDirectedGraph(BaseDirectedGraph<Vertex> const& graph) {
    // Euler path is possible in a directed graph iff
    // -> in each node, the indegree equals the outdegree.
    // -> or
    // --> (1st condition) in one node, the indegree is one larger than the outdegree,
    // --> (2nd condition) in another node, the outdegree is one larger than the indegree,
    // --> (3rd condition) and in all other nodes, the indegree equals the outdegree
    return areAllInDegreesEqualsOutDegrees(graph);
}

template <typename Vertex>
bool hasEulerPathForDirectedGraph(BaseDirectedGraph<Vertex> const& graph) {
    // Euler path is possible in a directed graph iff
    // --> (1st condition) in one node, the indegree is one larger than the outdegree,
    // --> (2nd condition) in another node, the outdegree is one larger than the indegree,
    // --> (3rd condition) and in all other nodes, the indegree equals the outdegree
    return hasAtLeastOneLesserAndGreaterInAndOutDegrees(graph);
}

}  // namespace alba::algorithm
