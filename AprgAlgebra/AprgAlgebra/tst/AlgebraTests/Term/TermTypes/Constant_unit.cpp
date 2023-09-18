#include <Algebra/Term/TermTypes/Constant.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::algebra {

TEST(ConstantTest, EqualityOperatorWorks) {
    Constant const constant1;
    Constant const constant2(3484);
    Constant const constant3(-1561);
    Constant const constant4(3484);

    EXPECT_TRUE(constant1 == constant1);
    EXPECT_FALSE(constant1 == constant2);
    EXPECT_TRUE(constant2 == constant2);
    EXPECT_FALSE(constant2 == constant3);
    EXPECT_TRUE(constant2 == constant4);
}

TEST(ConstantTest, InequalityOperatorWorks) {
    Constant const constant1;
    Constant const constant2(3484);
    Constant const constant3(-1561);
    Constant const constant4(3484);

    EXPECT_FALSE(constant1 != constant1);
    EXPECT_TRUE(constant1 != constant2);
    EXPECT_FALSE(constant2 != constant2);
    EXPECT_TRUE(constant2 != constant3);
    EXPECT_FALSE(constant2 != constant4);
}

TEST(ConstantTest, OutputStreamOperatorWorks) {
    stringstream ss;
    Constant const constant1;
    Constant const constant2(3484);
    Constant const constant3(-1561);
    Constant const constant4(AlbaNumber::createFraction(-415, 41745));
    Constant const constant5(-85.45631);

    ss << constant1 << "," << constant2 << "," << constant3 << "," << constant4 << "," << constant5;

    EXPECT_EQ("0,3484,-1561,(-83/8349),-85.4563", ss.str());
}

TEST(ConstantTest, LessThanOperatorWorks) {
    EXPECT_FALSE(Constant() < Constant());
    EXPECT_FALSE(Constant(34) < Constant(34));
    EXPECT_FALSE(Constant(34) < Constant(33));
    EXPECT_TRUE(Constant(34) < Constant(35));
}

TEST(ConstantTest, ConstantsAreConstructedCorrectly) {
    Constant const constant1;
    Constant const constant2(3484);
    Constant const constant3(-1561);
    Constant const constant4(AlbaNumber::createFraction(-415, 41745));
    Constant const constant5(-85.45631);

    EXPECT_DOUBLE_EQ(0, constant1.getNumber().getDouble());
    EXPECT_DOUBLE_EQ(3484, constant2.getNumber().getDouble());
    EXPECT_DOUBLE_EQ(-1561, constant3.getNumber().getDouble());
    EXPECT_DOUBLE_EQ(-0.0099413103365672533, constant4.getNumber().getDouble());
    EXPECT_DOUBLE_EQ(-85.45631, constant5.getNumber().getDouble());
}

TEST(ConstantTest, SettingANewNumberWorks) {
    Constant constant(3484);
    EXPECT_DOUBLE_EQ(3484, constant.getNumber().getDouble());

    constant.setNumber(4521);
    EXPECT_DOUBLE_EQ(4521, constant.getNumber().getDouble());
}

}  // namespace alba::algebra
