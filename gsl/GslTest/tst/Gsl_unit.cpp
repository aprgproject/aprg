#include <Common/Randomizer/AlbaUniformNonDeterministicRandomizer.hpp>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_combination.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_multiset.h>
#include <gsl/gsl_permutation.h>
#include <gsl/gsl_poly.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_sf_bessel.h>
#include <gsl/gsl_sort_double.h>

#include <gtest/gtest.h>

#include <array>
#include <iterator>
#include <vector>

using namespace alba;
using namespace std;

TEST(GslTest, GettingTheBesselFunctionInGslWorks) {
    double xValue = 5.0;
    double yValue = gsl_sf_bessel_J0(xValue);

    EXPECT_DOUBLE_EQ(-0.17759677131433830434739701, yValue);
}

TEST(GslTest, PolynomialRootFindingInGslWorks) {
    // To demonstrate the use of the general polynomial solver we will take the polynomial P(x) = x^5 - 1 which has
    // these roots: 1; e^(2*pi*i/5); e^(4*pi*i/5); e^(6*pi*i/5); e^(8*pi*i/5)

    // coefficients of P(x) = -1 + x^5
    constexpr int NUMBER_OF_COEFFICIENTS = 6;
    std::array<double, NUMBER_OF_COEFFICIENTS> coefficients = {-1, 0, 0, 0, 0, 1};
    std::array<double, 10> rootArray{};

    gsl_poly_complex_workspace *workspace = gsl_poly_complex_workspace_alloc(NUMBER_OF_COEFFICIENTS);
    gsl_poly_complex_solve(coefficients.data(), NUMBER_OF_COEFFICIENTS, workspace, rootArray.data());
    gsl_poly_complex_workspace_free(workspace);

    EXPECT_DOUBLE_EQ(-0.809016994374947673, rootArray[0]);
    EXPECT_DOUBLE_EQ(+0.587785252292473359, rootArray[1]);
    EXPECT_DOUBLE_EQ(-0.809016994374947673, rootArray[2]);
    EXPECT_DOUBLE_EQ(-0.587785252292473359, rootArray[3]);
    EXPECT_DOUBLE_EQ(+0.309016994374947507, rootArray[4]);
    EXPECT_DOUBLE_EQ(+0.951056516295152976, rootArray[5]);
    EXPECT_DOUBLE_EQ(+0.309016994374947507, rootArray[6]);
    EXPECT_DOUBLE_EQ(-0.951056516295152976, rootArray[7]);
    EXPECT_DOUBLE_EQ(+0.999999999999999889, rootArray[8]);
    EXPECT_DOUBLE_EQ(+0.000000000000000000, rootArray[9]);
}

TEST(GslTest, PermutationFunctionsInGslWorks) {
    // Th iscreates a random permutation (by shuffling the elements of the identity) and finds its inverse.

    using PermutationVector = vector<size_t>;
    constexpr size_t NUMBER_OF_DIGITS = 5;
    gsl_permutation *permutation1 = gsl_permutation_alloc(NUMBER_OF_DIGITS);
    gsl_permutation *permutation2 = gsl_permutation_alloc(NUMBER_OF_DIGITS);

    gsl_permutation_init(permutation1);
    PermutationVector initialPermutation(permutation1->data, permutation1->data + permutation1->size);
    PermutationVector expectedInitialPermutation{0, 1, 2, 3, 4};
    EXPECT_EQ(expectedInitialPermutation, initialPermutation);

    gsl_permutation_next(permutation1);
    PermutationVector nextPermutation(permutation1->data, permutation1->data + permutation1->size);
    PermutationVector expectedNextPermutation{0, 1, 2, 4, 3};
    EXPECT_EQ(expectedNextPermutation, nextPermutation);

    gsl_permutation_prev(permutation1);
    PermutationVector prevPermutation(permutation1->data, permutation1->data + permutation1->size);
    PermutationVector expectedPrevPermutation{0, 1, 2, 3, 4};
    EXPECT_EQ(expectedPrevPermutation, prevPermutation);

    gsl_permutation_next(permutation1);
    gsl_permutation_next(permutation1);
    gsl_permutation_next(permutation1);
    gsl_permutation_inverse(permutation2, permutation1);
    // The inverse of a permutation is another permutation that,
    // when composed with the original permutation, results in the identity permutation
    PermutationVector inversePermutation(permutation2->data, permutation2->data + permutation2->size);
    PermutationVector expectedInversePermutation{0, 1, 4, 2, 3};
    EXPECT_EQ(expectedInversePermutation, inversePermutation);

    gsl_permutation_free(permutation1);
    gsl_permutation_free(permutation2);
}

TEST(GslTest, GettingRandomPermutationsInGslWorks) {
    constexpr size_t NUMBER_OF_DIGITS = 5;
    gsl_permutation *permutation1 = gsl_permutation_alloc(NUMBER_OF_DIGITS);

    gsl_rng_env_setup();
    const gsl_rng_type *randomGeneratorType = gsl_rng_default;
    gsl_rng *randomGenerator = gsl_rng_alloc(randomGeneratorType);

    gsl_permutation_init(permutation1);
    gsl_ran_shuffle(randomGenerator, permutation1->data, NUMBER_OF_DIGITS, sizeof(size_t));
    cout << "random permutation:";
    gsl_permutation_fprintf(stdout, permutation1, " %u");
    cout << "\n";

    gsl_permutation_free(permutation1);
    gsl_rng_free(randomGenerator);
}

TEST(GslTest, GettingPermutationsInGslWorks) {
    // This steps forwards through all possible third order permutations, starting from the identity.

    gsl_permutation *permutation = gsl_permutation_alloc(3);
    gsl_permutation_init(permutation);
    int exitStatus = GSL_SUCCESS;
    while (exitStatus == GSL_SUCCESS) {
        gsl_permutation_fprintf(stdout, permutation, " %u");
        cout << "\n";
        exitStatus = gsl_permutation_next(permutation);
    }
    gsl_permutation_free(permutation);
}

TEST(GslTest, GettingCombinationsInGslWorks) {
    // This prints all subsets of the set 0, 1, 2, 3 ordered by size.

    gsl_combination *combination(nullptr);
    cout << "All subsets of {0,1,2,3} by size:\n";
    for (int i = 0; i <= 4; i++) {
        combination = gsl_combination_calloc(4, i);
        int exitStatus = GSL_SUCCESS;
        while (exitStatus == GSL_SUCCESS) {
            printf("{");
            gsl_combination_fprintf(stdout, combination, " %u");
            printf(" }\n");
            exitStatus = gsl_combination_next(combination);
        }
        gsl_combination_free(combination);
    }
}

TEST(GslTest, GettingMultisetsInGslWorks) {
    // This prints all multisets elements containing the values 0; 1; 2; 3 ordered by size.

    gsl_multiset *multiset(nullptr);
    cout << "All subsets of {0,1,2,3} by size:\n";
    for (int i = 0; i <= 4; i++) {
        multiset = gsl_multiset_calloc(4, i);
        int exitStatus = GSL_SUCCESS;
        while (exitStatus == GSL_SUCCESS) {
            printf("{");
            gsl_multiset_fprintf(stdout, multiset, " %u");
            printf(" }\n");
            exitStatus = gsl_multiset_next(multiset);
        }
        gsl_multiset_free(multiset);
    }
}

TEST(GslTest, SortingAndGettingTheSmallestValuesInGslWorks) {
    // This uses the function gsl_sort_smallest() to select the 5 smallest numbers.

    constexpr int NUMBER_OF_VALUES = 10, NUMBER_OF_SMALLEST_VALUES = 5;
    constexpr size_t stride = 1;
    std::array<double, NUMBER_OF_VALUES> values{3, 8, 4, 5, 1, 7, 9, 0, 2, 6};
    std::array<double, NUMBER_OF_SMALLEST_VALUES> smallestValues{};

    gsl_sort_smallest(smallestValues.data(), NUMBER_OF_SMALLEST_VALUES, values.data(), stride, NUMBER_OF_VALUES);

    decltype(smallestValues) expectedSmallestValues{0, 1, 2, 3, 4};
    EXPECT_EQ(expectedSmallestValues, smallestValues);
}

TEST(GslTest, MatrixMultiplicationInGslWorks) {
    AlbaUniformNonDeterministicRandomizer<double> randomizer(0, 100);

    // Create two matrices.
    gsl_matrix *matrixA = gsl_matrix_alloc(3, 3);
    gsl_matrix *matrixB = gsl_matrix_alloc(3, 3);
    gsl_matrix *matrixC = gsl_matrix_alloc(3, 3);

    // Fill the matrices with random numbers.
    for (int i = 0; i < static_cast<int>(matrixA->size1); ++i) {
        for (int j = 0; j < static_cast<int>(matrixA->size2); ++j) {
            gsl_matrix_set(matrixA, i, j, randomizer.getRandomValue());
            gsl_matrix_set(matrixB, i, j, randomizer.getRandomValue());
        }
    }

    // Multiply the matrices.
    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, matrixA, matrixB, 0.0, matrixC);

    // Check that the product is correct.
    for (int i = 0; i < static_cast<int>(matrixC->size1); ++i) {
        for (int j = 0; j < static_cast<int>(matrixC->size2); ++j) {
            double expected = 0.0;
            for (int k = 0; k < static_cast<int>(matrixA->size2); ++k) {
                expected += gsl_matrix_get(matrixA, i, k) * gsl_matrix_get(matrixB, k, j);
            }
            EXPECT_EQ(gsl_matrix_get(matrixC, i, j), expected);
        }
    }

    // Free the matrices.
    gsl_matrix_free(matrixA);
    gsl_matrix_free(matrixB);
    gsl_matrix_free(matrixC);
}
