#include <Algorithm/LinearProgramming/SimplexAlgorithm.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::algorithm {

namespace {
using SimplexForTest = SimplexAlgorithm<double>;
}  // namespace

TEST(SimplexAlgorithmTest, SimplexWorksOnBrewersProblem) {
    SimplexForTest::Matrix const constraintsCoefficients(
        2, 3,
        {
            5,
            15,
            4,
            4,
            35,
            20,
        });
    SimplexForTest::MatrixData const constraintsValues{480, 160, 1190};
    SimplexForTest::MatrixData const objectiveFunctionCoefficients{13, 23};
    SimplexForTest const simplex(constraintsCoefficients, constraintsValues, objectiveFunctionCoefficients);

    SimplexForTest::Matrix const expectedSolution(3, 3, {0.0, 0.0, 210.0, 0.0, 1.0, 28.0, 1.0, 0.0, 12.0});
    EXPECT_TRUE(simplex.isOptimized());
    EXPECT_DOUBLE_EQ(800, simplex.getOptimizedObjectiveValue());
    EXPECT_EQ(expectedSolution, simplex.getSolution());
}

}  // namespace alba::algorithm
