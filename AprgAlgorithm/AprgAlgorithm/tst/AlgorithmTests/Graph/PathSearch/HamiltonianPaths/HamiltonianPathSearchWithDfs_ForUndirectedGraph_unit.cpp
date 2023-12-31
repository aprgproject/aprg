#include <Algorithm/Graph/PathSearch/HamiltonianPaths/HamiltonianPathSearchWithDfs.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

namespace alba::algorithm {

namespace {
using VertexForTest = int;
using GraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using PathSearchForTest = HamiltonianPathSearchWithDfs<VertexForTest>;
using PathForTest = PathSearchForTest::Path;
using PathsForTest = PathSearchForTest::Paths;
}  // namespace

TEST(HamiltonianPathSearchWithDfsTestForUndirectedGraph, GetAllHamiltonianPathsWorks) {
    GraphForTest graph;
    graph.connect(0, 1);
    graph.connect(0, 2);
    graph.connect(1, 2);
    graph.connect(1, 3);
    graph.connect(2, 3);
    PathSearchForTest pathSearch(graph);

    PathsForTest const pathsToVerify(pathSearch.getAllHamiltonianPaths());

    PathsForTest const pathsToExpect{{0, 1, 2, 3}, {0, 1, 3, 2}, {0, 2, 1, 3}, {0, 2, 3, 1},
                                     {1, 0, 2, 3}, {1, 3, 2, 0}, {2, 0, 1, 3}, {2, 3, 1, 0},
                                     {3, 1, 0, 2}, {3, 1, 2, 0}, {3, 2, 0, 1}, {3, 2, 1, 0}};
    EXPECT_EQ(pathsToExpect, pathsToVerify);
}

TEST(HamiltonianPathSearchWithDfsTestForUndirectedGraph, GetOneHamiltonianPathWorks) {
    GraphForTest graph;
    graph.connect(0, 1);
    graph.connect(0, 2);
    graph.connect(1, 2);
    graph.connect(1, 3);
    graph.connect(2, 3);
    PathSearchForTest pathSearch(graph);

    PathForTest const pathsToVerify(pathSearch.getOneHamiltonianPath());

    PathForTest const pathsToExpect{0, 1, 2, 3};
    EXPECT_EQ(pathsToExpect, pathsToVerify);
}

TEST(HamiltonianPathSearchWithDfsTestForUndirectedGraph, GetAllHamiltonianCyclesWorks) {
    GraphForTest graph;
    graph.connect(0, 1);
    graph.connect(0, 2);
    graph.connect(1, 2);
    graph.connect(1, 3);
    graph.connect(2, 3);
    PathSearchForTest pathSearch(graph);

    PathsForTest const pathsToVerify(pathSearch.getAllHamiltonianCycles());

    PathsForTest const pathsToExpect{{0, 1, 3, 2, 0}, {0, 2, 3, 1, 0}, {1, 0, 2, 3, 1}, {1, 3, 2, 0, 1},
                                     {2, 0, 1, 3, 2}, {2, 3, 1, 0, 2}, {3, 1, 0, 2, 3}, {3, 2, 0, 1, 3}};
    EXPECT_EQ(pathsToExpect, pathsToVerify);
}

TEST(HamiltonianPathSearchWithDfsTestForUndirectedGraph, GetOneHamiltonianCycleWorks) {
    GraphForTest graph;
    graph.connect(0, 1);
    graph.connect(0, 2);
    graph.connect(1, 2);
    graph.connect(1, 3);
    graph.connect(2, 3);
    PathSearchForTest pathSearch(graph);

    PathForTest const pathsToVerify(pathSearch.getOneHamiltonianCycle());

    PathForTest const pathsToExpect{0, 1, 3, 2, 0};
    EXPECT_EQ(pathsToExpect, pathsToVerify);
}

}  // namespace alba::algorithm
