#include <Common/Math/Vector/AlbaMathVector.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace {
using VectorTwoElements = AlbaMathVector<double, 2>;
}  // anonymous namespace

TEST(AlbaMathVectorTest, ConstructionWorks) {
    VectorTwoElements const mathVector1;
    VectorTwoElements::ValuesInArray const values{6, 7};
    VectorTwoElements const mathVector2(values);
    VectorTwoElements const mathVector3{3, 4};

    ASSERT_EQ(2U, mathVector1.getSize());
    EXPECT_DOUBLE_EQ(0, mathVector1.getValueAt(0));
    EXPECT_DOUBLE_EQ(0, mathVector1.getValueAt(1));
    ASSERT_EQ(2U, mathVector2.getSize());
    EXPECT_DOUBLE_EQ(6, mathVector2.getValueAt(0));
    EXPECT_DOUBLE_EQ(7, mathVector2.getValueAt(1));
    ASSERT_EQ(2U, mathVector3.getSize());
    EXPECT_DOUBLE_EQ(3, mathVector3.getValueAt(0));
    EXPECT_DOUBLE_EQ(4, mathVector3.getValueAt(1));
}

TEST(AlbaMathVectorTest, OperatorEqualsWorks) {
    VectorTwoElements const mathVector1{3, 4};
    VectorTwoElements const mathVector2{3, 4};
    VectorTwoElements const mathVector3{3, 3};
    VectorTwoElements const mathVector4{4, 4};
    VectorTwoElements const mathVector5{5, 5};
    VectorTwoElements const mathVector6{static_cast<double>(1) / 3, static_cast<double>(4) / 3};

    EXPECT_TRUE(mathVector1 == mathVector1);
    EXPECT_TRUE(mathVector1 == mathVector2);
    EXPECT_FALSE(mathVector1 == mathVector3);
    EXPECT_FALSE(mathVector1 == mathVector4);
    EXPECT_FALSE(mathVector1 == mathVector5);
    EXPECT_TRUE(mathVector6 == mathVector6);
}

TEST(AlbaMathVectorTest, OperatorNotEqualsWorks) {
    VectorTwoElements const mathVector1{3, 4};
    VectorTwoElements const mathVector2{3, 4};
    VectorTwoElements const mathVector3{3, 3};
    VectorTwoElements const mathVector4{4, 4};
    VectorTwoElements const mathVector5{5, 5};
    VectorTwoElements const mathVector6{static_cast<double>(1) / 3, static_cast<double>(4) / 3};

    EXPECT_FALSE(mathVector1 != mathVector1);
    EXPECT_FALSE(mathVector1 != mathVector2);
    EXPECT_TRUE(mathVector1 != mathVector3);
    EXPECT_TRUE(mathVector1 != mathVector4);
    EXPECT_TRUE(mathVector1 != mathVector5);
    EXPECT_FALSE(mathVector6 != mathVector6);
}

TEST(AlbaMathVectorTest, OperatorLessThanWorks) {
    VectorTwoElements const mathVector1{3, 4};
    VectorTwoElements const mathVector2{3, 4};
    VectorTwoElements const mathVector3{3, 3};
    VectorTwoElements const mathVector4{4, 4};
    VectorTwoElements const mathVector5{5, 5};
    VectorTwoElements const mathVector6{static_cast<double>(1) / 3, static_cast<double>(4) / 3};

    EXPECT_FALSE(mathVector1 < mathVector1);
    EXPECT_FALSE(mathVector1 < mathVector2);
    EXPECT_FALSE(mathVector1 < mathVector3);
    EXPECT_TRUE(mathVector1 < mathVector4);
    EXPECT_TRUE(mathVector1 < mathVector5);
    EXPECT_TRUE(mathVector3 < mathVector1);
    EXPECT_FALSE(mathVector4 < mathVector1);
    EXPECT_FALSE(mathVector5 < mathVector1);
    EXPECT_FALSE(mathVector6 < mathVector6);
}

TEST(AlbaMathVectorTest, OperatorBinaryAddWorks) {
    VectorTwoElements const mathVector1{3, 4};
    VectorTwoElements const mathVector2{5, 6};

    VectorTwoElements const actualMathVector(mathVector1 + mathVector2);

    VectorTwoElements const expectedMathVector{8, 10};
    EXPECT_EQ(expectedMathVector, actualMathVector);
}

TEST(AlbaMathVectorTest, OperatorBinaryMinusWorks) {
    VectorTwoElements const mathVector1{7, 9};
    VectorTwoElements const mathVector2{5, 6};

    VectorTwoElements const actualMathVector(mathVector1 - mathVector2);

    VectorTwoElements const expectedMathVector{2, 3};
    EXPECT_EQ(expectedMathVector, actualMathVector);
}

TEST(AlbaMathVectorTest, OperatorUnaryAddWorks) {
    VectorTwoElements const mathVector{3, 4};

    VectorTwoElements const actualMathVector(+mathVector);

    VectorTwoElements const expectedMathVector{3, 4};
    EXPECT_EQ(expectedMathVector, actualMathVector);
}

TEST(AlbaMathVectorTest, OperatorUnaryMinusWorks) {
    VectorTwoElements const mathVector{7, 9};

    VectorTwoElements const actualMathVector(-mathVector);

    VectorTwoElements const expectedMathVector{-7, -9};
    EXPECT_EQ(expectedMathVector, actualMathVector);
}

TEST(AlbaMathVectorTest, OperatorBinaryMultiplyScalarWorks) {
    VectorTwoElements const mathVector{3, 4};

    VectorTwoElements const actualMathVector(mathVector * 2);

    VectorTwoElements const expectedMathVector{6, 8};
    EXPECT_EQ(expectedMathVector, actualMathVector);
}

TEST(AlbaMathVectorTest, OperatorBinaryDivideScalarWorks) {
    VectorTwoElements const mathVector{7, 9};

    VectorTwoElements const actualMathVector(mathVector / 2);

    VectorTwoElements const expectedMathVector{3.5, 4.5};
    EXPECT_EQ(expectedMathVector, actualMathVector);
}

TEST(AlbaMathVectorTest, OperatorAdditionAssignmentWorks) {
    VectorTwoElements actualMathVector{3, 4};
    VectorTwoElements const anotherMathVector{5, 6};

    actualMathVector += anotherMathVector;

    VectorTwoElements const expectedMathVector{8, 10};
    EXPECT_EQ(expectedMathVector, actualMathVector);
}

TEST(AlbaMathVectorTest, OperatorSubtractionAssignmentWorks) {
    VectorTwoElements actualMathVector{7, 9};
    VectorTwoElements const anotherMathVector{5, 6};

    actualMathVector -= anotherMathVector;

    VectorTwoElements const expectedMathVector{2, 3};
    EXPECT_EQ(expectedMathVector, actualMathVector);
}

TEST(AlbaMathVectorTest, GetSizeWorks) {
    VectorTwoElements const mathVector{3.5, 4.5};

    EXPECT_EQ(2U, mathVector.getSize());
}

TEST(AlbaMathVectorTest, GetValueAtWorks) {
    VectorTwoElements const mathVector{3.5, 4.5};

    ASSERT_EQ(2U, mathVector.getSize());
    EXPECT_DOUBLE_EQ(3.5, mathVector.getValueAt(0));
    EXPECT_DOUBLE_EQ(4.5, mathVector.getValueAt(1));
}

TEST(AlbaMathVectorTest, GetMagnitudeWorks) {
    VectorTwoElements const mathVector1{3, 4};
    VectorTwoElements const mathVector2{6, 7};

    EXPECT_DOUBLE_EQ(5, mathVector1.getMagnitude());
    EXPECT_DOUBLE_EQ(9.2195444572928871, mathVector2.getMagnitude());
}

TEST(AlbaMathVectorTest, GetValuesWorks) {
    VectorTwoElements const mathVector{3.5, 4.5};

    VectorTwoElements::ValuesInArray values(mathVector.getValues());

    ASSERT_EQ(2U, values.size());
    EXPECT_DOUBLE_EQ(3.5, values[0]);
    EXPECT_DOUBLE_EQ(4.5, values[1]);
}

TEST(AlbaMathVectorTest, OutputStreamOperatorWorks) {
    stringstream testStream;
    VectorTwoElements const mathVector{3.5, 4.5};

    testStream << mathVector;

    EXPECT_EQ("{3.5, 4.5}", testStream.str());
}

}  // namespace alba
