#include <Algorithm/Graph/EdgeWeightedGraph/EdgeWeightedGraph.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algorithm
{

namespace
{
using Vertex = unsigned int;
using UndirectedGraphForTest = UndirectedGraphWithListOfEdges<Vertex>;
using EdgeWeightedUndirectedGraphForTest = EdgeWeightedGraph<Vertex, double, UndirectedGraphForTest>;
using Edges = GraphTypes<Vertex>::Edges;
using EdgeToWeightMap = EdgeWeightedUndirectedGraphForTest::EdgeToWeightMap;
}

TEST(EdgeWeightedGraphTest, GetWeightWorksOnUndirectedGraph)
{
    EdgeWeightedUndirectedGraphForTest graph;
    graph.connect(0U, 1U, 3.5);
    graph.connect(0U, 2U, 4.5);

    EXPECT_EQ(3.5, graph.getWeight(0U, 1U));
    EXPECT_EQ(4.5, graph.getWeight(0U, 2U));
    EXPECT_EQ(3.5, graph.getWeight(1U, 0U));
    EXPECT_EQ(4.5, graph.getWeight(2U, 0U));
}

TEST(EdgeWeightedGraphTest, GetEdgeToWeightMapWorksOnUndirectedGraph)
{
    EdgeWeightedUndirectedGraphForTest graph;
    graph.connect(0U, 1U, 3.5);
    graph.connect(0U, 2U, 4.5);

    EdgeWeightedUndirectedGraphForTest::EdgeToWeightMap expectedEdgesToWeight
    {{{0U, 1U}, 3.5}, {{0U, 2U}, 4.5}};
    EXPECT_EQ(expectedEdgesToWeight, graph.getEdgeToWeightMap());
}

TEST(EdgeWeightedGraphTest, ConnectWorksOnUndirectedGraph)
{
    EdgeWeightedUndirectedGraphForTest graph;
    graph.connect(0U, 1U, 3.5);
    graph.connect(0U, 2U, 4.5);

    EXPECT_EQ(3U, graph.getNumberOfVertices());
    EXPECT_EQ(2U, graph.getNumberOfEdges());
    Edges edgesToExpect{{0U, 1U}, {0U, 2U}};
    EdgeWeightedUndirectedGraphForTest::EdgeToWeightMap expectedEdgesToWeight
    {{{0U, 1U}, 3.5}, {{0U, 2U}, 4.5}};
    EXPECT_EQ(edgesToExpect, graph.getEdges());
    EXPECT_EQ(expectedEdgesToWeight, graph.getEdgeToWeightMap());
}

TEST(EdgeWeightedGraphTest, DisconnectWorksOnUndirectedGraph)
{
    EdgeWeightedUndirectedGraphForTest graph;
    graph.connect(0U, 1U, 3.5);
    graph.connect(0U, 2U, 4.5);

    graph.disconnect(0U, 1U);

    EXPECT_EQ(2U, graph.getNumberOfVertices());
    EXPECT_EQ(1U, graph.getNumberOfEdges());
    Edges edgesToExpect{{0U, 2U}};
    EdgeWeightedUndirectedGraphForTest::EdgeToWeightMap expectedEdgesToWeight
    {{{0U, 2U}, 4.5}};
    EXPECT_EQ(edgesToExpect, graph.getEdges());
    EXPECT_EQ(expectedEdgesToWeight, graph.getEdgeToWeightMap());
}

}

}
