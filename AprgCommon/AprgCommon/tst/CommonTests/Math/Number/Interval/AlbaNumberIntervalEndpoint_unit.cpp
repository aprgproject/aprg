#include <Common/Math/Number/Interval/AlbaNumberIntervalEndpoint.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(AlbaNumberIntervalEndpointTest, EqualityForEndpointsWorks) {
    AlbaNumberIntervalEndpoint const endpoint1(AlbaNumberIntervalEndpoint::Type::Open, 645);
    AlbaNumberIntervalEndpoint const endpoint2(AlbaNumberIntervalEndpoint::Type::Open, 645);
    AlbaNumberIntervalEndpoint const endpoint3(AlbaNumberIntervalEndpoint::Type::Open, 784);
    AlbaNumberIntervalEndpoint const endpoint4(AlbaNumberIntervalEndpoint::Type::Close, 645);
    AlbaNumberIntervalEndpoint const endpoint5(AlbaNumberIntervalEndpoint::Type::Close, 784);

    EXPECT_TRUE(endpoint1 == endpoint2);
    EXPECT_FALSE(endpoint1 == endpoint3);
    EXPECT_FALSE(endpoint1 == endpoint4);
    EXPECT_FALSE(endpoint1 == endpoint5);
}

TEST(AlbaNumberIntervalEndpointTest, OutputStreamOperatorWorks) {
    stringstream testStream;
    AlbaNumberIntervalEndpoint const endpoint1(AlbaNumberIntervalEndpoint::Type::Open, 645);
    AlbaNumberIntervalEndpoint const endpoint2(AlbaNumberIntervalEndpoint::Type::Close, 784);

    testStream << endpoint1 << endpoint2;

    EXPECT_EQ("(Open,645)(Close,784)", testStream.str());
}

TEST(AlbaNumberIntervalEndpointTest, GetValueForEndpointWorks) {
    AlbaNumberIntervalEndpoint const endpoint1(AlbaNumberIntervalEndpoint::Type::Open, 645);
    AlbaNumberIntervalEndpoint const endpoint2(AlbaNumberIntervalEndpoint::Type::Close, 784);

    EXPECT_EQ(645, endpoint1.getValue().getInteger());
    EXPECT_EQ(784, endpoint2.getValue().getInteger());
}

TEST(AlbaNumberIntervalEndpointTest, ConstructionForEndpointWorks) {
    AlbaNumberIntervalEndpoint const endpoint1(AlbaNumberIntervalEndpoint::Type::Open, 645);
    AlbaNumberIntervalEndpoint const endpoint2(AlbaNumberIntervalEndpoint::Type::Close, 784);

    EXPECT_EQ(AlbaNumberIntervalEndpoint::Type::Open, endpoint1.getType());
    EXPECT_EQ(645, endpoint1.getValue().getInteger());
    EXPECT_EQ(AlbaNumberIntervalEndpoint::Type::Close, endpoint2.getType());
    EXPECT_EQ(784, endpoint2.getValue().getInteger());
}

TEST(AlbaNumberIntervalEndpointTest, SetTypeForEndpointWorks) {
    AlbaNumberIntervalEndpoint endpoint(AlbaNumberIntervalEndpoint::Type::Open, 784);

    endpoint.setType(AlbaNumberIntervalEndpoint::Type::Close);

    EXPECT_EQ(AlbaNumberIntervalEndpoint::Type::Close, endpoint.getType());
    EXPECT_EQ(784, endpoint.getValue().getInteger());
}

TEST(AlbaNumberIntervalEndpointTest, GetTypeForEndpointWorks) {
    AlbaNumberIntervalEndpoint const endpoint1(AlbaNumberIntervalEndpoint::Type::Open, 645);
    AlbaNumberIntervalEndpoint const endpoint2(AlbaNumberIntervalEndpoint::Type::Close, 784);

    EXPECT_EQ(AlbaNumberIntervalEndpoint::Type::Open, endpoint1.getType());
    EXPECT_EQ(AlbaNumberIntervalEndpoint::Type::Close, endpoint2.getType());
}

TEST(AlbaNumberIntervalEndpointTest, GetTypeStringForEndpointWorks) {
    AlbaNumberIntervalEndpoint const endpoint1(AlbaNumberIntervalEndpoint::Type::Open, 645);
    AlbaNumberIntervalEndpoint const endpoint2(AlbaNumberIntervalEndpoint::Type::Close, 784);

    EXPECT_EQ("Open", endpoint1.getTypeString());
    EXPECT_EQ("Close", endpoint2.getTypeString());
}

TEST(AlbaNumberIntervalEndpointTest, IsOpenForEndpointWorks) {
    AlbaNumberIntervalEndpoint const endpoint1(AlbaNumberIntervalEndpoint::Type::Open, 645);
    AlbaNumberIntervalEndpoint const endpoint2(AlbaNumberIntervalEndpoint::Type::Close, 784);

    EXPECT_TRUE(endpoint1.isOpen());
    EXPECT_FALSE(endpoint2.isOpen());
}

TEST(AlbaNumberIntervalEndpointTest, IsCloseForEndpointWorks) {
    AlbaNumberIntervalEndpoint const endpoint1(AlbaNumberIntervalEndpoint::Type::Open, 645);
    AlbaNumberIntervalEndpoint const endpoint2(AlbaNumberIntervalEndpoint::Type::Close, 784);

    EXPECT_FALSE(endpoint1.isClose());
    EXPECT_TRUE(endpoint2.isClose());
}

}  // namespace alba
