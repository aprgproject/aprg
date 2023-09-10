#include <Common/Container/AlbaXY.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace {
using IntXY = AlbaXY<int>;
}  // namespace

TEST(AlbaXYTest, DefaultValuesAreZero) {
    IntXY const xyValues;
    EXPECT_EQ(0, xyValues.getX());
    EXPECT_EQ(0, xyValues.getY());
}

TEST(AlbaXYTest, ValuesAreSetAtConstruction) {
    IntXY const xyValues(-5, 5);
    EXPECT_EQ(-5, xyValues.getX());
    EXPECT_EQ(5, xyValues.getY());
}

TEST(AlbaXYTest, EqualityOperatorWorks) {
    IntXY const xyValues(-5, 5);

    EXPECT_TRUE(IntXY(-5, 5) == xyValues);
    EXPECT_FALSE(IntXY(-5, -5) == xyValues);
    EXPECT_FALSE(IntXY(5, -5) == xyValues);
    EXPECT_FALSE(IntXY(5, 5) == xyValues);
}

TEST(AlbaXYTest, NonEqualityOperatorWorks) {
    IntXY const xyValues(-5, 5);

    EXPECT_FALSE(IntXY(-5, 5) != xyValues);
    EXPECT_TRUE(IntXY(-5, -5) != xyValues);
    EXPECT_TRUE(IntXY(5, -5) != xyValues);
    EXPECT_TRUE(IntXY(5, 5) != xyValues);
}

TEST(AlbaXYTest, LessThanOperatorWorks) {
    IntXY const xyValues(-5, 5);

    EXPECT_FALSE(IntXY(-5, 5) < xyValues);
    EXPECT_TRUE(IntXY(-6, 5) < xyValues);
    EXPECT_FALSE(IntXY(-4, 5) < xyValues);
    EXPECT_TRUE(IntXY(-5, 4) < xyValues);
    EXPECT_FALSE(IntXY(-5, 6) < xyValues);
}

TEST(AlbaXYTest, PlusUnaryOperatorWorks) { EXPECT_EQ(IntXY(1, 2), +IntXY(1, 2)); }
TEST(AlbaXYTest, MinusUnaryOperatorWorks) { EXPECT_EQ(IntXY(-1, -2), -IntXY(1, 2)); }
TEST(AlbaXYTest, PlusBinaryOperatorWorks) { EXPECT_EQ(IntXY(4, -2), (IntXY(1, 2) + IntXY(3, -4))); }
TEST(AlbaXYTest, MinusBinaryOperatorWorks) { EXPECT_EQ(IntXY(-2, 6), (IntXY(1, 2) - IntXY(3, -4))); }
TEST(AlbaXYTest, MultiplyBinaryOperatorWorks) { EXPECT_EQ(IntXY(35, -70), (IntXY(5, -10) * 7)); }
TEST(AlbaXYTest, DivideBinaryOperatorWorks) { EXPECT_EQ(IntXY(1, -2), (IntXY(5, -10) / 5)); }

TEST(AlbaXYTest, PlusAssignmentOperatorWorks) {
    IntXY xyzToTest(1, 2);

    xyzToTest += IntXY(3, -4);

    EXPECT_EQ(IntXY(4, -2), xyzToTest);
}

TEST(AlbaXYTest, MinusAssignmentOperatorWorks) {
    IntXY xyzToTest(1, 2);

    xyzToTest -= IntXY(3, -4);

    EXPECT_EQ(IntXY(-2, 6), xyzToTest);
}

TEST(AlbaXYTest, IsEmptyWorks) {
    EXPECT_TRUE(IntXY().isEmpty());
    EXPECT_FALSE(IntXY(-5, 5).isEmpty());
}

TEST(AlbaXYTest, GetXWorks) {
    IntXY const xyValues(-5, 5);

    EXPECT_EQ(-5, xyValues.getX());
}

TEST(AlbaXYTest, GetYWorks) {
    IntXY const xyValues(-5, 5);

    EXPECT_EQ(5, xyValues.getY());
}

TEST(AlbaXYTest, GetXTimesYWorks) {
    IntXY const xyValues(-5, 5);

    EXPECT_EQ(-25, xyValues.getXTimesY());
}

TEST(AlbaXYTest, SetXWorks) {
    IntXY xyValues(-5, 5);

    xyValues.setX(23);

    EXPECT_EQ(IntXY(23, 5), xyValues);
}

TEST(AlbaXYTest, SetYWorks) {
    IntXY xyValues(-5, 5);

    xyValues.setY(45);

    EXPECT_EQ(IntXY(-5, 45), xyValues);
}

TEST(AlbaXYTest, SetXAndYWorks) {
    IntXY xyValues(-5, 5);

    xyValues.setXAndY(23, 45);

    EXPECT_EQ(IntXY(23, 45), xyValues);
}

TEST(AlbaXYTest, SaveMinimumXAndYWorks) {
    IntXY xyValues;

    xyValues.saveMinimumXAndY(IntXY(-5, 5));
    xyValues.saveMinimumXAndY(IntXY(5, -5));
    xyValues.saveMinimumXAndY(IntXY(-5, -5));
    xyValues.saveMinimumXAndY(IntXY(5, 5));

    EXPECT_EQ(IntXY(-5, -5), xyValues);
}

TEST(AlbaXYTest, SaveMaximumXAndYWorks) {
    IntXY xyValues;

    xyValues.saveMaximumXAndY(IntXY(-5, 5));
    xyValues.saveMaximumXAndY(IntXY(5, -5));
    xyValues.saveMaximumXAndY(IntXY(-5, -5));
    xyValues.saveMaximumXAndY(IntXY(5, 5));

    EXPECT_EQ(IntXY(5, 5), xyValues);
}

TEST(AlbaXYTest, OutputStreamOperatorWorks) {
    stringstream testStream;
    IntXY const xyValues(-5, 5);

    testStream << xyValues;

    EXPECT_EQ("(-5,5)", testStream.str());
}

}  // namespace alba
