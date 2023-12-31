#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/EdgeWeightedGraph/EdgeWeightedGraph.hpp>
#include <Algorithm/Graph/PathSearch/DepthFirstSearch/PathSearchUsingDfsWithDistanceSum.hpp>

#include <gtest/gtest.h>

namespace alba::algorithm {

namespace {

using VertexForTest = int;
using WeightForTest = double;
using ContentMapForTest = GraphTypesWithWeights<VertexForTest, WeightForTest>::VertexToWeightMap;
using DirectedGraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
using EdgeWeightedDirectedGraphForTest = EdgeWeightedGraph<VertexForTest, WeightForTest, DirectedGraphForTest>;

using PathSearchForTest =
    PathSearchUsingDfsWithDistanceSum<VertexForTest, WeightForTest, EdgeWeightedDirectedGraphForTest>;

void putConnectionsForTest(EdgeWeightedDirectedGraphForTest& graph) {
    graph.connect(0, 1, 0.05);
    graph.connect(0, 2, 0.10);
    graph.connect(0, 5, 0.15);
    graph.connect(1, 2, 0.20);
    graph.connect(2, 3, 0.25);
    graph.connect(2, 4, 0.30);
    graph.connect(3, 4, 0.35);
    graph.connect(3, 5, 0.40);
}

}  // namespace

TEST(PathSearchUsingDfsWithDistanceSumTest, GetDistanceToWorksWithDirectedGraph) {
    EdgeWeightedDirectedGraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest const pathSearch(graph, {0});

    EXPECT_DOUBLE_EQ(0, pathSearch.getDistanceTo(0));
    EXPECT_DOUBLE_EQ(0.05, pathSearch.getDistanceTo(1));
    EXPECT_DOUBLE_EQ(0.25, pathSearch.getDistanceTo(2));
    EXPECT_DOUBLE_EQ(0.5, pathSearch.getDistanceTo(3));
    EXPECT_DOUBLE_EQ(0.85, pathSearch.getDistanceTo(4));
    EXPECT_DOUBLE_EQ(0.9, pathSearch.getDistanceTo(5));
    EXPECT_DOUBLE_EQ(0, pathSearch.getDistanceTo(6));
}

TEST(PathSearchUsingDfsWithDistanceSumTest, GetEndVertexToDistanceSumMapWorksWithDirectedGraph) {
    EdgeWeightedDirectedGraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest const pathSearch(graph, {0});

    ContentMapForTest const expectedMap{{0, 0.0}, {1, 0.05}, {2, 0.25}, {3, 0.5}, {4, 0.85}, {5, 0.9}};
    EXPECT_EQ(expectedMap, pathSearch.getEndVertexToDistanceSumMap());
}

}  // namespace alba::algorithm
