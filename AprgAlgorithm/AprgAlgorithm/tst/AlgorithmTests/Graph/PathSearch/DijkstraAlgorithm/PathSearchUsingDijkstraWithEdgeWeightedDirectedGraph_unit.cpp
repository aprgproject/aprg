#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/EdgeWeightedGraph/EdgeWeightedGraph.hpp>
#include <Algorithm/Graph/PathSearch/DijkstraAlgorithm/PathSearchUsingDijkstra.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::algorithm {

namespace {

using VertexForTest = int;
using WeightForTest = double;
using PathForTest = GraphTypes<VertexForTest>::Path;
using DirectedGraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
using EdgeWeightedDirectedGraphForTest = EdgeWeightedGraph<VertexForTest, WeightForTest, DirectedGraphForTest>;

using ShortestPathSearchForTest =
    PathSearchUsingDijkstra<VertexForTest, WeightForTest, EdgeWeightedDirectedGraphForTest, less>;

using LongestPathSearchForTest =
    PathSearchUsingDijkstra<VertexForTest, WeightForTest, EdgeWeightedDirectedGraphForTest, greater>;

void putConnectionsWithCyclesForTest(EdgeWeightedDirectedGraphForTest& graph) {
    graph.connect(0, 1, 0.26);
    graph.connect(1, 2, 0.38);
    graph.connect(2, 3, 0.29);
    graph.connect(3, 0, 0.34);
}

void putConnectionsWithNoCyclesForTest(EdgeWeightedDirectedGraphForTest& graph) {
    graph.connect(0, 2, 0.26);
    graph.connect(0, 4, 0.38);
    graph.connect(1, 3, 0.29);
    graph.connect(2, 7, 0.34);
    graph.connect(3, 6, 0.52);
    graph.connect(4, 5, 0.35);
    graph.connect(4, 7, 0.37);
    graph.connect(5, 1, 0.32);
    graph.connect(5, 7, 0.28);
    graph.connect(7, 3, 0.39);
}

}  // namespace

TEST(PathSearchUsingDijkstraTest, StillProcessWhenThereAreCyclesInLesserComparison) {
    EdgeWeightedDirectedGraphForTest graph;
    putConnectionsWithCyclesForTest(graph);
    ShortestPathSearchForTest const pathSearch(graph, 0);

    EXPECT_TRUE(pathSearch.hasPathTo(0));
    EXPECT_TRUE(pathSearch.hasPathTo(1));
    EXPECT_TRUE(pathSearch.hasPathTo(2));
    EXPECT_TRUE(pathSearch.hasPathTo(3));
    EXPECT_FALSE(pathSearch.hasPathTo(4));
    EXPECT_EQ(PathForTest(), pathSearch.getPathTo(0));
    EXPECT_EQ(PathForTest({0, 1}), pathSearch.getPathTo(1));
    EXPECT_EQ(PathForTest({0, 1, 2}), pathSearch.getPathTo(2));
    EXPECT_EQ(PathForTest({0, 1, 2, 3}), pathSearch.getPathTo(3));
    EXPECT_EQ(PathForTest(), pathSearch.getPathTo(4));
}

TEST(PathSearchUsingDijkstraTest, DoesNotProcessWhenThereAreCyclesInGreaterComparison) {
    EdgeWeightedDirectedGraphForTest graph;
    putConnectionsWithCyclesForTest(graph);
    LongestPathSearchForTest const pathSearch(graph, 0);

    EXPECT_FALSE(pathSearch.hasPathTo(0));
    EXPECT_FALSE(pathSearch.hasPathTo(1));
    EXPECT_FALSE(pathSearch.hasPathTo(2));
    EXPECT_FALSE(pathSearch.hasPathTo(3));
    EXPECT_FALSE(pathSearch.hasPathTo(4));
    EXPECT_TRUE(pathSearch.getPathTo(0).empty());
    EXPECT_TRUE(pathSearch.getPathTo(1).empty());
    EXPECT_TRUE(pathSearch.getPathTo(2).empty());
    EXPECT_TRUE(pathSearch.getPathTo(3).empty());
    EXPECT_TRUE(pathSearch.getPathTo(4).empty());
}

TEST(PathSearchUsingDijkstraTest, HasPathToWorksWithEdgeWeightedDirectedGraphAndLesserComparison) {
    EdgeWeightedDirectedGraphForTest graph;
    putConnectionsWithNoCyclesForTest(graph);
    ShortestPathSearchForTest const pathSearch(graph, 0);

    EXPECT_FALSE(pathSearch.hasPathTo(0));
    EXPECT_TRUE(pathSearch.hasPathTo(1));
    EXPECT_TRUE(pathSearch.hasPathTo(2));
    EXPECT_TRUE(pathSearch.hasPathTo(3));
    EXPECT_TRUE(pathSearch.hasPathTo(4));
    EXPECT_TRUE(pathSearch.hasPathTo(5));
    EXPECT_TRUE(pathSearch.hasPathTo(6));
    EXPECT_TRUE(pathSearch.hasPathTo(7));
    EXPECT_FALSE(pathSearch.hasPathTo(8));
}

TEST(PathSearchUsingDijkstraTest, GetPathToWorksWithEdgeWeightedDirectedGraphAndLesserComparison) {
    EdgeWeightedDirectedGraphForTest graph;
    putConnectionsWithNoCyclesForTest(graph);
    ShortestPathSearchForTest const pathSearch(graph, 0);

    EXPECT_EQ(PathForTest(), pathSearch.getPathTo(0));
    EXPECT_EQ(PathForTest({0, 4, 5, 1}), pathSearch.getPathTo(1));
    EXPECT_EQ(PathForTest({0, 2}), pathSearch.getPathTo(2));
    EXPECT_EQ(PathForTest({0, 2, 7, 3}), pathSearch.getPathTo(3));
    EXPECT_EQ(PathForTest({0, 4}), pathSearch.getPathTo(4));
    EXPECT_EQ(PathForTest({0, 4, 5}), pathSearch.getPathTo(5));
    EXPECT_EQ(PathForTest({0, 2, 7, 3, 6}), pathSearch.getPathTo(6));
    EXPECT_EQ(PathForTest({0, 2, 7}), pathSearch.getPathTo(7));
    EXPECT_EQ(PathForTest(), pathSearch.getPathTo(8));
}

TEST(PathSearchUsingDijkstraTest, HasPathToWorksWithEdgeWeightedDirectedGraphAndGreaterComparison) {
    EdgeWeightedDirectedGraphForTest graph;
    putConnectionsWithNoCyclesForTest(graph);
    LongestPathSearchForTest const pathSearch(graph, 0);

    EXPECT_FALSE(pathSearch.hasPathTo(0));
    EXPECT_TRUE(pathSearch.hasPathTo(1));
    EXPECT_TRUE(pathSearch.hasPathTo(2));
    EXPECT_TRUE(pathSearch.hasPathTo(3));
    EXPECT_TRUE(pathSearch.hasPathTo(4));
    EXPECT_TRUE(pathSearch.hasPathTo(5));
    EXPECT_TRUE(pathSearch.hasPathTo(6));
    EXPECT_TRUE(pathSearch.hasPathTo(7));
    EXPECT_FALSE(pathSearch.hasPathTo(8));
}

TEST(PathSearchUsingDijkstraTest, GetPathToWorksWithEdgeWeightedDirectedGraphAndGreaterComparison) {
    EdgeWeightedDirectedGraphForTest graph;
    putConnectionsWithNoCyclesForTest(graph);
    LongestPathSearchForTest const pathSearch(graph, 0);

    EXPECT_EQ(PathForTest(), pathSearch.getPathTo(0));
    EXPECT_EQ(PathForTest({0, 4, 5, 1}), pathSearch.getPathTo(1));
    EXPECT_EQ(PathForTest({0, 2}), pathSearch.getPathTo(2));
    EXPECT_EQ(PathForTest({0, 4, 5, 7, 3}), pathSearch.getPathTo(3));
    EXPECT_EQ(PathForTest({0, 4}), pathSearch.getPathTo(4));
    EXPECT_EQ(PathForTest({0, 4, 5}), pathSearch.getPathTo(5));
    EXPECT_EQ(PathForTest({0, 4, 5, 7, 3, 6}), pathSearch.getPathTo(6));
    EXPECT_EQ(PathForTest({0, 4, 5, 7}), pathSearch.getPathTo(7));
    EXPECT_EQ(PathForTest(), pathSearch.getPathTo(8));
}

}  // namespace alba::algorithm
