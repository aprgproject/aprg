#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/VertexOrdering/VertexOrderingUsingDfs.hpp>

#include <gtest/gtest.h>

namespace alba::algorithm {

namespace {
using VertexForTest = int;
using VerticesForTest = GraphTypes<VertexForTest>::Vertices;
using GraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
using VertexOrderingForTest = VertexOrderingUsingDfs<VertexForTest>;
}  // namespace

TEST(VertexOrderingUsingDfsTest, VertexOrderingWorksWhenGraphIsEmptyWithDirectedGraph) {
    GraphForTest const graph;
    VertexOrderingForTest vertexOrderingWithDfs(graph);

    VerticesForTest const preOrderFromAVertex(
        vertexOrderingWithDfs.getVerticesInThisOrder(1, VertexTraversalOrder::PreOrder));
    VerticesForTest const postOrderFromAVertex(
        vertexOrderingWithDfs.getVerticesInThisOrder(1, VertexTraversalOrder::PostOrder));
    VerticesForTest const reversePostOrderAVertex(
        vertexOrderingWithDfs.getVerticesInThisOrder(1, VertexTraversalOrder::ReversePostOrder));
    VerticesForTest const preOrderFromAllVertices(
        vertexOrderingWithDfs.getVerticesInThisOrder(VertexTraversalOrder::PreOrder));
    VerticesForTest const postOrderFromAllVertices(
        vertexOrderingWithDfs.getVerticesInThisOrder(VertexTraversalOrder::PostOrder));
    VerticesForTest const reversePostOrderFromAllVertices(
        vertexOrderingWithDfs.getVerticesInThisOrder(VertexTraversalOrder::ReversePostOrder));

    EXPECT_TRUE(preOrderFromAVertex.empty());
    EXPECT_TRUE(postOrderFromAVertex.empty());
    EXPECT_TRUE(reversePostOrderAVertex.empty());
    EXPECT_TRUE(preOrderFromAllVertices.empty());
    EXPECT_TRUE(postOrderFromAllVertices.empty());
    EXPECT_TRUE(reversePostOrderFromAllVertices.empty());
}

TEST(VertexOrderingUsingDfsTest, VertexOrderingWorksUsingExample1WithDirectedGraph) {
    GraphForTest graph;
    graph.connect(40, 30);  // first value set
    graph.connect(40, 31);
    graph.connect(40, 32);
    graph.connect(40, 33);
    graph.connect(30, 20);  // second value set
    graph.connect(31, 21);
    graph.connect(32, 22);
    graph.connect(33, 23);
    graph.connect(20, 10);  // third value set
    graph.connect(21, 11);
    graph.connect(22, 12);
    graph.connect(23, 13);
    VertexOrderingForTest vertexOrderingWithDfs(graph);

    VerticesForTest const preOrderFromAVertex(
        vertexOrderingWithDfs.getVerticesInThisOrder(30, VertexTraversalOrder::PreOrder));
    VerticesForTest const postOrderFromAVertex(
        vertexOrderingWithDfs.getVerticesInThisOrder(30, VertexTraversalOrder::PostOrder));
    VerticesForTest const reversePostOrderAVertex(
        vertexOrderingWithDfs.getVerticesInThisOrder(30, VertexTraversalOrder::ReversePostOrder));
    VerticesForTest const preOrderFromAllVertices(
        vertexOrderingWithDfs.getVerticesInThisOrder(VertexTraversalOrder::PreOrder));
    VerticesForTest const postOrderFromAllVertices(
        vertexOrderingWithDfs.getVerticesInThisOrder(VertexTraversalOrder::PostOrder));
    VerticesForTest const reversePostOrderFromAllVertices(
        vertexOrderingWithDfs.getVerticesInThisOrder(VertexTraversalOrder::ReversePostOrder));

    VerticesForTest const expectedPreOrderFromAVertex{30, 20, 10};
    VerticesForTest const expectedPostOrderFromAVertex{10, 20, 30};
    VerticesForTest const expectedReversePostOrderFromAVertex{30, 20, 10};
    VerticesForTest const expectedPreOrderFromAllVertices{10, 11, 12, 13, 20, 21, 22, 23, 30, 31, 32, 33, 40};
    VerticesForTest const expectedPostOrderFromAllVertices{10, 11, 12, 13, 20, 21, 22, 23, 30, 31, 32, 33, 40};
    VerticesForTest const expectedReversePostOrderFromAllVertices{40, 33, 32, 31, 30, 23, 22, 21, 20, 13, 12, 11, 10};
    EXPECT_EQ(expectedPreOrderFromAVertex, preOrderFromAVertex);
    EXPECT_EQ(expectedPostOrderFromAVertex, postOrderFromAVertex);
    EXPECT_EQ(expectedReversePostOrderFromAVertex, reversePostOrderAVertex);
    EXPECT_EQ(expectedPreOrderFromAllVertices, preOrderFromAllVertices);
    EXPECT_EQ(expectedPostOrderFromAllVertices, postOrderFromAllVertices);
    EXPECT_EQ(expectedReversePostOrderFromAllVertices, reversePostOrderFromAllVertices);
}

TEST(VertexOrderingUsingDfsTest, VertexOrderingWorksUsingExample2WithDirectedGraph) {
    GraphForTest graph;
    graph.connect(0, 1);
    graph.connect(0, 5);
    graph.connect(0, 6);
    graph.connect(2, 0);
    graph.connect(2, 3);
    graph.connect(3, 5);
    graph.connect(5, 4);
    graph.connect(6, 4);
    graph.connect(6, 9);
    graph.connect(7, 6);
    graph.connect(8, 7);
    graph.connect(9, 10);
    graph.connect(9, 11);
    graph.connect(9, 12);
    graph.connect(11, 12);
    VertexOrderingForTest vertexOrderingWithDfs(graph);

    VerticesForTest const preOrderFromAVertex(
        vertexOrderingWithDfs.getVerticesInThisOrder(7, VertexTraversalOrder::PreOrder));
    VerticesForTest const postOrderFromAVertex(
        vertexOrderingWithDfs.getVerticesInThisOrder(7, VertexTraversalOrder::PostOrder));
    VerticesForTest const reversePostOrderAVertex(
        vertexOrderingWithDfs.getVerticesInThisOrder(7, VertexTraversalOrder::ReversePostOrder));
    VerticesForTest const preOrderFromAllVertices(
        vertexOrderingWithDfs.getVerticesInThisOrder(VertexTraversalOrder::PreOrder));
    VerticesForTest const postOrderFromAllVertices(
        vertexOrderingWithDfs.getVerticesInThisOrder(VertexTraversalOrder::PostOrder));
    VerticesForTest const reversePostOrderFromAllVertices(
        vertexOrderingWithDfs.getVerticesInThisOrder(VertexTraversalOrder::ReversePostOrder));

    VerticesForTest const expectedPreOrderFromAVertex{7, 6, 4, 9, 10, 11, 12};
    VerticesForTest const expectedPostOrderFromAVertex{4, 10, 12, 11, 9, 6, 7};
    VerticesForTest const expectedReversePostOrderFromAVertex{7, 6, 9, 11, 12, 10, 4};
    VerticesForTest const expectedPreOrderFromAllVertices{0, 1, 5, 4, 6, 9, 10, 11, 12, 2, 3, 7, 8};
    VerticesForTest const expectedPostOrderFromAllVertices{1, 4, 5, 10, 12, 11, 9, 6, 0, 3, 2, 7, 8};
    VerticesForTest const expectedReversePostOrderFromAllVertices{8, 7, 2, 3, 0, 6, 9, 11, 12, 10, 5, 4, 1};
    EXPECT_EQ(expectedPreOrderFromAVertex, preOrderFromAVertex);
    EXPECT_EQ(expectedPostOrderFromAVertex, postOrderFromAVertex);
    EXPECT_EQ(expectedReversePostOrderFromAVertex, reversePostOrderAVertex);
    EXPECT_EQ(expectedPreOrderFromAllVertices, preOrderFromAllVertices);
    EXPECT_EQ(expectedPostOrderFromAllVertices, postOrderFromAllVertices);
    EXPECT_EQ(expectedReversePostOrderFromAllVertices, reversePostOrderFromAllVertices);
}

TEST(VertexOrderingUsingDfsTest, GetVerticesInTopologicalOrderWorksWithDirectedGraph) {
    GraphForTest graph;
    graph.connect(0, 1);
    graph.connect(0, 5);
    graph.connect(0, 6);
    graph.connect(2, 0);
    graph.connect(2, 3);
    graph.connect(3, 5);
    graph.connect(5, 4);
    graph.connect(6, 4);
    graph.connect(6, 9);
    graph.connect(7, 6);
    graph.connect(8, 7);
    graph.connect(9, 10);
    graph.connect(9, 11);
    graph.connect(9, 12);
    graph.connect(11, 12);
    VertexOrderingForTest vertexOrderingWithDfs(graph);

    VerticesForTest const pathFromAVertex(vertexOrderingWithDfs.getVerticesInTopologicalOrder(7));
    VerticesForTest const pathFromAllVertices(vertexOrderingWithDfs.getVerticesInTopologicalOrder());

    VerticesForTest const expectedPathFromAVertex{7, 6, 9, 11, 12, 10, 4};
    VerticesForTest const expectedPathFromAllVertices{8, 7, 2, 3, 0, 6, 9, 11, 12, 10, 5, 4, 1};
    EXPECT_EQ(expectedPathFromAVertex, pathFromAVertex);
    EXPECT_EQ(expectedPathFromAllVertices, pathFromAllVertices);
}

TEST(VertexOrderingUsingDfsTest, GetVerticesInTopologicalOrderWithDagCheckingWorksWithDirectedGraph) {
    GraphForTest graph;
    graph.connect(0, 1);
    graph.connect(0, 5);
    graph.connect(0, 6);
    graph.connect(2, 0);
    graph.connect(2, 3);
    graph.connect(3, 5);
    graph.connect(5, 4);
    graph.connect(6, 4);
    graph.connect(6, 9);
    graph.connect(7, 6);
    graph.connect(8, 7);
    graph.connect(9, 10);
    graph.connect(9, 11);
    graph.connect(9, 12);
    graph.connect(11, 12);
    VertexOrderingForTest vertexOrderingWithDfs(graph);

    VerticesForTest const pathFromAllVertices(vertexOrderingWithDfs.getVerticesInTopologicalOrderWithDagChecking());

    VerticesForTest const expectedPathFromAllVertices{8, 7, 2, 3, 0, 6, 9, 11, 12, 10, 5, 4, 1};
    EXPECT_EQ(expectedPathFromAllVertices, pathFromAllVertices);
}

}  // namespace alba::algorithm
