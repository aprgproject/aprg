#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/FlowNetwork/FordFulkerson/FordFulkersonUsingBfs.hpp>
#include <Algorithm/Graph/FlowNetwork/SinkSourceFlowNetwork.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algorithm
{

namespace
{
using VertexForTest = unsigned int;
using FlowDataTypeForTest = double;
using EdgesForTest = typename GraphTypes<VertexForTest>::Edges;
using DirectedGraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
using FlowNetworkForTest = SinkSourceFlowNetwork<VertexForTest, FlowDataTypeForTest, DirectedGraphForTest>;
using MaxFlowForTest = FordFulkersonUsingBfs<FlowNetworkForTest>;
}

TEST(FordFulkersonUsingBfsTest, GetMaxFlowValueAndIsInMaxFlowMinCutWorksOnExample1)
{
    FlowNetworkForTest flowNetwork(0, 5);
    flowNetwork.connect(0U, 1U, 2.0, 0.0);    flowNetwork.connect(0U, 2U, 3.0, 0.0);
    flowNetwork.connect(1U, 3U, 3.0, 0.0);
    flowNetwork.connect(1U, 4U, 1.0, 0.0);
    flowNetwork.connect(2U, 3U, 1.0, 0.0);
    flowNetwork.connect(2U, 4U, 1.0, 0.0);
    flowNetwork.connect(3U, 5U, 2.0, 0.0);
    flowNetwork.connect(4U, 5U, 3.0, 0.0);
    MaxFlowForTest maxFlow(flowNetwork);

    EdgesForTest expectedMinCutEdges{{0U, 1U}, {2U, 3U}, {2U, 4U}};
    EXPECT_DOUBLE_EQ(4.0, maxFlow.getMaxFlowValue());
    EXPECT_EQ(expectedMinCutEdges, maxFlow.getMinCutEdges());
}


TEST(FordFulkersonUsingBfsTest, GetMaxFlowValueAndIsInMaxFlowMinCutWorksOnExample2)
{
    FlowNetworkForTest flowNetwork(1, 6);
    flowNetwork.connect(1U, 2U, 5.0, 0.0);
    flowNetwork.connect(1U, 4U, 4.0, 0.0);
    flowNetwork.connect(2U, 3U, 6.0, 0.0);
    flowNetwork.connect(3U, 5U, 8.0, 0.0);
    flowNetwork.connect(3U, 6U, 6.0, 0.0);
    flowNetwork.connect(4U, 2U, 3.0, 0.0);
    flowNetwork.connect(4U, 5U, 1.0, 0.0);
    flowNetwork.connect(5U, 6U, 2.0, 0.0);
    MaxFlowForTest maxFlow(flowNetwork);

    EdgesForTest expectedMinCutEdges{{2U, 3U}, {4U, 5U}};
    EXPECT_DOUBLE_EQ(7.0, maxFlow.getMaxFlowValue());
    EXPECT_EQ(expectedMinCutEdges, maxFlow.getMinCutEdges());
}
}

}