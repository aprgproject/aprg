#include <Algorithm/Graph/SymbolGraph/SymbolGraph.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>
#include <Common/Memory/AlbaCast.hpp>

#include <gtest/gtest.h>

#include <cstdint>

namespace alba::algorithm {

template <>
uint64_t getUniqueVertexIdentifier<uint64_t, double>(double const& object) {
    return getFloatingPointMemoryRepresentation<double, uint64_t>(object);
}

template <>
void removeUniqueVertexIdentifierIfNeeded<uint64_t, double>(double const&) {
    // do nothing
}

namespace {
using GraphForTest = UndirectedGraphWithListOfEdges<uint64_t>;
using SymbolGraphForTest = SymbolGraph<uint64_t, double, GraphForTest>;
constexpr uint64_t vertexFor12 = 0x3FF3333333333333LL;
constexpr uint64_t vertexFor13 = 0x3FF4CCCCCCCCCCCDULL;
constexpr uint64_t vertexFor23 = 0x4002666666666666LL;
constexpr uint64_t vertexFor45 = 0x4012000000000000LL;
}  // namespace

TEST(SymbolGraphWithDoubleTest, ContainsWorksWhenEmpty) {
    SymbolGraphForTest const symbolGraph;

    EXPECT_FALSE(symbolGraph.contains(1.2));
    EXPECT_FALSE(symbolGraph.contains(1.3));
    EXPECT_FALSE(symbolGraph.contains(2.3));
    EXPECT_FALSE(symbolGraph.contains(4.5));
}

TEST(SymbolGraphWithDoubleTest, ContainsWorksWhenNotEmpty) {
    SymbolGraphForTest symbolGraph;

    symbolGraph.connect(1.2, 1.3);
    symbolGraph.connect(1.2, 2.3);
    symbolGraph.connect(1.3, 2.3);

    EXPECT_TRUE(symbolGraph.contains(1.2));
    EXPECT_TRUE(symbolGraph.contains(1.3));
    EXPECT_TRUE(symbolGraph.contains(2.3));
    EXPECT_FALSE(symbolGraph.contains(4.5));
}

TEST(SymbolGraphWithDoubleTest, GetVertexWorks) {
    SymbolGraphForTest const symbolGraph;

    EXPECT_EQ(vertexFor12, symbolGraph.getVertex(1.2));
    EXPECT_EQ(vertexFor13, symbolGraph.getVertex(1.3));
    EXPECT_EQ(vertexFor23, symbolGraph.getVertex(2.3));
    EXPECT_EQ(vertexFor45, symbolGraph.getVertex(4.5));
}

TEST(SymbolGraphWithDoubleTest, GetObjectWorks) {
    SymbolGraphForTest symbolGraph;
    symbolGraph.connect(1.2, 1.3);
    symbolGraph.connect(1.2, 2.3);
    symbolGraph.connect(1.3, 2.3);

    EXPECT_DOUBLE_EQ(1.2, symbolGraph.getObject(vertexFor12));
    EXPECT_DOUBLE_EQ(1.3, symbolGraph.getObject(vertexFor13));
    EXPECT_DOUBLE_EQ(2.3, symbolGraph.getObject(vertexFor23));
    EXPECT_DOUBLE_EQ(0.0, symbolGraph.getObject(vertexFor45));
}

TEST(SymbolGraphWithDoubleTest, GetGraphWorks) {
    SymbolGraphForTest symbolGraph;
    symbolGraph.connect(1.2, 1.3);
    symbolGraph.connect(1.2, 2.3);
    symbolGraph.connect(1.3, 2.3);

    GraphForTest::Edges const expectedEdges{
        {vertexFor12, vertexFor13}, {vertexFor12, vertexFor23}, {vertexFor13, vertexFor23}};
    EXPECT_EQ(expectedEdges, symbolGraph.getGraph().getEdges());
}

TEST(SymbolGraphWithDoubleTest, GetSymbolTableWorks) {
    SymbolGraphForTest symbolGraph;
    symbolGraph.connect(1.2, 1.3);
    symbolGraph.connect(1.2, 2.3);
    symbolGraph.connect(1.3, 2.3);

    SymbolGraphForTest::SymbolTable const expectedSymbolTable{
        {vertexFor12, 1.2}, {vertexFor13, 1.3}, {vertexFor23, 2.3}};
    EXPECT_EQ(expectedSymbolTable, symbolGraph.getSymbolTable());
}

TEST(SymbolGraphWithDoubleTest, ConnectWorks) {
    SymbolGraphForTest symbolGraph;
    symbolGraph.connect(1.2, 1.3);
    symbolGraph.connect(1.2, 2.3);
    symbolGraph.connect(1.3, 2.3);

    GraphForTest::Edges const expectedEdges{
        {vertexFor12, vertexFor13}, {vertexFor12, vertexFor23}, {vertexFor13, vertexFor23}};
    SymbolGraphForTest::SymbolTable const expectedSymbolTable{
        {vertexFor12, 1.2}, {vertexFor13, 1.3}, {vertexFor23, 2.3}};
    EXPECT_EQ(expectedEdges, symbolGraph.getGraph().getEdges());
    EXPECT_EQ(expectedSymbolTable, symbolGraph.getSymbolTable());
}

TEST(SymbolGraphWithDoubleTest, DisconnectWorks) {
    SymbolGraphForTest symbolGraph;
    symbolGraph.connect(1.2, 1.3);
    symbolGraph.connect(1.2, 2.3);
    symbolGraph.connect(1.3, 2.3);

    symbolGraph.disconnect(1.2, 1.3);
    symbolGraph.disconnect(1.2, 2.3);

    GraphForTest::Edges const expectedEdges{{vertexFor13, vertexFor23}};
    SymbolGraphForTest::SymbolTable const expectedSymbolTable{{vertexFor13, 1.3}, {vertexFor23, 2.3}};
    EXPECT_EQ(expectedEdges, symbolGraph.getGraph().getEdges());
    EXPECT_EQ(expectedSymbolTable, symbolGraph.getSymbolTable());
}

}  // namespace alba::algorithm
