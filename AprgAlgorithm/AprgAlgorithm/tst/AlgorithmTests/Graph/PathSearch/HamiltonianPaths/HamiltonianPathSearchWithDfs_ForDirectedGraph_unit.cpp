#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/PathSearch/HamiltonianPaths/HamiltonianPathSearchWithDfs.hpp>

#include <gtest/gtest.h>

namespace alba::algorithm {

namespace {
using VertexForTest = int;
using GraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
using PathSearchForTest = HamiltonianPathSearchWithDfs<VertexForTest>;
using PathForTest = PathSearchForTest::Path;
using PathsForTest = PathSearchForTest::Paths;
}  // namespace

TEST(HamiltonianPathSearchWithDfsTestForDirectedGraph, GetAllHamiltonianPathsWorks) {
    GraphForTest graph;
    graph.connect(0, 1);
    graph.connect(1, 2);
    graph.connect(2, 3);
    graph.connect(3, 0);
    PathSearchForTest pathSearch(graph);

    PathsForTest const pathsToVerify(pathSearch.getAllHamiltonianPaths());

    PathsForTest const pathsToExpect{{0, 1, 2, 3}, {1, 2, 3, 0}, {2, 3, 0, 1}, {3, 0, 1, 2}};
    EXPECT_EQ(pathsToExpect, pathsToVerify);
}

TEST(HamiltonianPathSearchWithDfsTestForDirectedGraph, GetOneHamiltonianPathWorks) {
    GraphForTest graph;
    graph.connect(0, 1);
    graph.connect(1, 2);
    graph.connect(2, 3);
    graph.connect(3, 0);
    PathSearchForTest pathSearch(graph);

    PathForTest const pathsToVerify(pathSearch.getOneHamiltonianPath());

    PathForTest const pathsToExpect{0, 1, 2, 3};
    EXPECT_EQ(pathsToExpect, pathsToVerify);
}

TEST(HamiltonianPathSearchWithDfsTestForDirectedGraph, GetAllHamiltonianCyclesWorks) {
    GraphForTest graph;
    graph.connect(0, 1);
    graph.connect(1, 2);
    graph.connect(2, 3);
    graph.connect(3, 0);
    PathSearchForTest pathSearch(graph);

    PathsForTest const pathsToVerify(pathSearch.getAllHamiltonianCycles());

    PathsForTest const pathsToExpect{{0, 1, 2, 3, 0}, {1, 2, 3, 0, 1}, {2, 3, 0, 1, 2}, {3, 0, 1, 2, 3}};
    EXPECT_EQ(pathsToExpect, pathsToVerify);
}

TEST(HamiltonianPathSearchWithDfsTestForDirectedGraph, GetOneHamiltonianCycleWorks) {
    GraphForTest graph;
    graph.connect(0, 1);
    graph.connect(1, 2);
    graph.connect(2, 3);
    graph.connect(3, 0);
    PathSearchForTest pathSearch(graph);

    PathForTest const pathsToVerify(pathSearch.getOneHamiltonianCycle());

    PathForTest const pathsToExpect{0, 1, 2, 3, 0};
    EXPECT_EQ(pathsToExpect, pathsToVerify);
}

}  // namespace alba::algorithm
