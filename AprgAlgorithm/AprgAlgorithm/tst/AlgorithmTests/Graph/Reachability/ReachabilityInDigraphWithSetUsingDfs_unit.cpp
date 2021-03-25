#include <Algorithm/Graph/Reachability/ReachabilityInDigraphWithSetUsingDfs.hpp>
#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <AlgorithmTests/Graph/Reachability/Utilities/CommonTestsWithReachability.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithReachability;

namespace alba
{

namespace algorithm
{

namespace
{
using GraphForTest = DirectedGraphWithListOfEdges<unsigned int>;
using ReachabilityForTest = ReachabilityInDigraphWithSetUsingDfs<unsigned int>;
}

TEST(ReachabilityInDigraphWithSetUsingDfsTest, IsReachableWorksWhenEmpty)
{
    testIsReachableWhenEmptyWithVertexAsUnsignedInt<ReachabilityForTest, GraphForTest>();
}

TEST(ReachabilityInDigraphWithSetUsingDfsTest, IsReachableWorksWhenNotEmpty)
{
    testIsReachableWhenNotEmptyWithVertexAsUnsignedInt<ReachabilityForTest, GraphForTest>();
}

}

}
