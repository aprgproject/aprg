#include <Common/Math/Helpers/PrecisionHelpers.hpp>
#include <Common/Math/Matrix/AlbaMatrix.hpp>
#include <Common/Randomizer/AlbaUniformNonDeterministicRandomizer.hpp>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_cdf.h>
#include <gsl/gsl_combination.h>
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_fft_halfcomplex.h>
#include <gsl/gsl_fft_real.h>
#include <gsl/gsl_filter.h>
#include <gsl/gsl_histogram.h>
#include <gsl/gsl_histogram2d.h>
#include <gsl/gsl_integration.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_movstat.h>
#include <gsl/gsl_multiset.h>
#include <gsl/gsl_ntuple.h>
#include <gsl/gsl_permutation.h>
#include <gsl/gsl_poly.h>
#include <gsl/gsl_qrng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_rstat.h>
#include <gsl/gsl_sf_bessel.h>
#include <gsl/gsl_sf_gamma.h>
#include <gsl/gsl_sort.h>
#include <gsl/gsl_sort_double.h>
#include <gsl/gsl_statistics.h>
#include <gsl/gsl_vector.h>

#include <gtest/gtest.h>

#include <array>
#include <iterator>
#include <math.h>
#include <vector>

using namespace alba::mathHelper;
using namespace alba::matrix;
using namespace std;

namespace alba {

struct data {
    double x;
    double y;
    double z;
};

double function1ToIntegrate(double const inputValue, void *parameters) {
    double const alpha = *static_cast<double *>(parameters);
    return log(alpha * inputValue) / sqrt(inputValue);
}

double function2ToIntegrate(double const inputValue, void *parameters) {
    int const mFunctionInput = *static_cast<int *>(parameters);
    return gsl_pow_int(inputValue, mFunctionInput) + 1.0;
}

double func(const size_t n, double x[], void *params) {
    const double alpha = *static_cast<double *>(params);
    gsl_sort(x, 1, n);
    return gsl_stats_trmean_from_sorted_data(alpha, x, 1, n);
}

double val_func(void *ntuple_data, void *) {
    auto *data = static_cast<struct data *>(ntuple_data);
    double x = NAN;
    double y = NAN;
    double z = NAN;
    x = data->x;
    y = data->y;
    z = data->z;
    return x * x + y * y + z * z;
}

int sel_func(void *ntuple_data, void *params) {
    auto *data = static_cast<struct data *>(ntuple_data);
    double x = NAN;
    double y = NAN;
    double z = NAN;
    double E2 = NAN;
    double scale = NAN;
    scale = *static_cast<double *>(params);
    x = data->x;
    y = data->y;
    z = data->z;
    E2 = x * x + y * y + z * z;
    return static_cast<int>(E2 > scale);
}

TEST(GslTest, GettingTheBesselFunctionInGslWorks) {
    double const xValue = 5.0;
    double const yValue = gsl_sf_bessel_J0(xValue);

    EXPECT_DOUBLE_EQ(-0.17759677131433830434739701, yValue);
}

TEST(GslTest, PolynomialRootFindingInGslWorks) {
    // To demonstrate the use of the general polynomial solver we will take the polynomial P(x) = x^5 - 1
    // which has these roots: 1; e^(2*pi*index/5); e^(4*pi*index/5); e^(6*pi*index/5); e^(8*pi*index/5)
    // coefficients of P(x) = -1 + x^5
    constexpr int NUMBER_OF_COEFFICIENTS = 6;
    array<double, NUMBER_OF_COEFFICIENTS> coefficients = {-1, 0, 0, 0, 0, 1};
    array<double, 10> rootArray{};

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
    PermutationVector const initialPermutation(permutation1->data, permutation1->data + permutation1->size);
    PermutationVector const expectedInitialPermutation{0, 1, 2, 3, 4};
    EXPECT_EQ(expectedInitialPermutation, initialPermutation);

    gsl_permutation_next(permutation1);
    PermutationVector const nextPermutation(permutation1->data, permutation1->data + permutation1->size);
    PermutationVector const expectedNextPermutation{0, 1, 2, 4, 3};
    EXPECT_EQ(expectedNextPermutation, nextPermutation);

    gsl_permutation_prev(permutation1);
    PermutationVector const prevPermutation(permutation1->data, permutation1->data + permutation1->size);
    PermutationVector const expectedPrevPermutation{0, 1, 2, 3, 4};
    EXPECT_EQ(expectedPrevPermutation, prevPermutation);

    gsl_permutation_next(permutation1);
    gsl_permutation_next(permutation1);
    gsl_permutation_next(permutation1);
    gsl_permutation_inverse(permutation2, permutation1);
    // The inverse of a permutation is another permutation that,
    // when composed with the original permutation, results in the identity permutation
    PermutationVector const inversePermutation(permutation2->data, permutation2->data + permutation2->size);
    PermutationVector const expectedInversePermutation{0, 1, 4, 2, 3};
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
    constexpr int NUMBER_OF_DIGITS = 3;
    cout << "All subsets of {0,1,2,3} by size:\n";
    for (int index = 0; index <= NUMBER_OF_DIGITS; ++index) {
        gsl_combination *combination = gsl_combination_calloc(NUMBER_OF_DIGITS, index);
        int exitStatus = GSL_SUCCESS;
        while (exitStatus == GSL_SUCCESS) {
            cout << "{";
            gsl_combination_fprintf(stdout, combination, " %u");
            cout << " }\n";
            exitStatus = gsl_combination_next(combination);
        }
        gsl_combination_free(combination);
    }
}

TEST(GslTest, GettingMultisetsInGslWorks) {
    // This prints all multisets elements containing the values 0; 1; 2; 3 ordered by size.
    constexpr int NUMBER_OF_DIGITS = 3;
    cout << "All subsets of {0,1,2} by size:\n";
    for (int index = 0; index <= NUMBER_OF_DIGITS; ++index) {
        gsl_multiset *multiset = gsl_multiset_calloc(NUMBER_OF_DIGITS, index);
        int exitStatus = GSL_SUCCESS;
        while (exitStatus == GSL_SUCCESS) {
            cout << "{";
            gsl_multiset_fprintf(stdout, multiset, " %u");
            cout << " }\n";
            exitStatus = gsl_multiset_next(multiset);
        }
        gsl_multiset_free(multiset);
    }
}

TEST(GslTest, SortingAndGettingTheSmallestValuesInGslWorks) {
    // This uses the function gsl_sort_smallest() to select the 5 smallest numbers.
    constexpr int NUMBER_OF_VALUES = 10;
    constexpr int NUMBER_OF_SMALLEST_VALUES = 5;
    constexpr size_t stride = 1;
    array<double, NUMBER_OF_VALUES> values{3, 8, 4, 5, 1, 7, 9, 0, 2, 6};
    array<double, NUMBER_OF_SMALLEST_VALUES> smallestValues{};

    gsl_sort_smallest(smallestValues.data(), NUMBER_OF_SMALLEST_VALUES, values.data(), stride, NUMBER_OF_VALUES);

    decltype(smallestValues) const expectedSmallestValues{0, 1, 2, 3, 4};
    EXPECT_EQ(expectedSmallestValues, smallestValues);
}

TEST(GslTest, MatrixMultiplicationInGslWorks) {
    // Thi computes the product of two matrices using the Level-3 BLAS function DGEMM.
    // Create two matrices.
    AlbaMatrix<double> matrixA(3, 2, {0.11, 0.12, 0.13, 0.21, 0.22, 0.23});
    AlbaMatrix<double> matrixB(2, 3, {1011, 1012, 1021, 1022, 1031, 1032});
    AlbaMatrix<double> matrixC(2, 2, {0.00, 0.00, 0.00, 0.00});
    gsl_matrix_view const matrixViewA = gsl_matrix_view_array(matrixA.getMatrixDataReference().data(), 2, 3);
    gsl_matrix_view const matrixViewB = gsl_matrix_view_array(matrixB.getMatrixDataReference().data(), 3, 2);
    gsl_matrix_view matrixViewC = gsl_matrix_view_array(matrixC.getMatrixDataReference().data(), 2, 2);

    // Compute C = A * B
    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, &matrixViewA.matrix, &matrixViewB.matrix, 0.0, &matrixViewC.matrix);

    AlbaMatrix<double> const expectedMatrixC(2, 2, {367.76, 368.12, 674.06, 674.72});
    EXPECT_EQ(expectedMatrixC, matrixC);
}

TEST(GslTest, MatrixMultiplicationWithRandomNumbersInGslWorks) {
    constexpr int SIDE_SIZE = 3;
    AlbaMatrix<double> matrixA(SIDE_SIZE, SIDE_SIZE, {0.11, 0.12, 0.13, 0.21, 0.22, 0.23});
    AlbaMatrix<double> matrixB(SIDE_SIZE, SIDE_SIZE, {1011, 1012, 1021, 1022, 1031, 1032});
    AlbaMatrix<double> matrixC(SIDE_SIZE, SIDE_SIZE);
    gsl_matrix_view const matrixViewA =
        gsl_matrix_view_array(matrixA.getMatrixDataReference().data(), SIDE_SIZE, SIDE_SIZE);
    gsl_matrix_view const matrixViewB =
        gsl_matrix_view_array(matrixB.getMatrixDataReference().data(), SIDE_SIZE, SIDE_SIZE);
    gsl_matrix_view matrixViewC = gsl_matrix_view_array(matrixC.getMatrixDataReference().data(), SIDE_SIZE, SIDE_SIZE);
    // Fill the matrices with random numbers.
    AlbaUniformNonDeterministicRandomizer<double> randomizer(0, 100);
    for (int index = 0; index < SIDE_SIZE; ++index) {
        for (int index2 = 0; index2 < SIDE_SIZE; ++index2) {
            matrixA.setEntry(index, index2, randomizer.getRandomValue());
            matrixB.setEntry(index, index2, randomizer.getRandomValue());
        }
    }

    // Multiply the matrices.
    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, &matrixViewA.matrix, &matrixViewB.matrix, 0.0, &matrixViewC.matrix);

    // Check that the product is correct.
    for (int index = 0; index < SIDE_SIZE; ++index) {
        for (int index2 = 0; index2 < SIDE_SIZE; ++index2) {
            double expectedCEntry = 0.0;
            for (int k = 0; k < SIDE_SIZE; ++k) {
                expectedCEntry += matrixA.getEntry(k, index) * matrixB.getEntry(index2, k);
            }
            EXPECT_EQ(matrixC.getEntry(index2, index), expectedCEntry);
        }
    }
}

TEST(GslTest, SolvingLinearSystemInGslWorks) {
    // This solves the linear system Ax = b.
    AlbaMatrix<double> matrixA(
        4, 4, {0.18, 0.60, 0.57, 0.96, 0.41, 0.24, 0.99, 0.58, 0.14, 0.30, 0.97, 0.66, 0.51, 0.13, 0.19, 0.85});
    vector<double> vectorB{1.0, 2.0, 3.0, 4.0};
    vector<double> vectorX{0.0, 0.0, 0.0, 0.0};
    gsl_matrix_view matrixViewA = gsl_matrix_view_array(matrixA.getMatrixDataReference().data(), 4, 4);
    gsl_vector_view const vectorViewB = gsl_vector_view_array(vectorB.data(), 4);
    gsl_vector_view vectorViewX = gsl_vector_view_array(vectorX.data(), 4);
    int signum{};
    gsl_permutation *permutation = gsl_permutation_alloc(4);

    gsl_linalg_LU_decomp(&matrixViewA.matrix, permutation, &signum);
    gsl_linalg_LU_solve(&matrixViewA.matrix, permutation, &vectorViewB.vector, &vectorViewX.vector);

    vector<double> const expectedVectorX{
        -4.0520502295739744, -12.605611395906907, 1.6609116267088422, 8.6937669287952293};
    EXPECT_EQ(expectedVectorX, vectorX);
    gsl_permutation_free(permutation);
}

TEST(GslTest, GettingEigenValuesAndVectorInGslWorks) {
    // This computes the eigenvalues and eigenvectors of the 4-th order Hilbert matrix, H(index,index2) = 1/(index
    // +index2 + 1).
    AlbaMatrix<double> matrixHilbert(
        4, 4,
        {1.0, 1 / 2.0, 1 / 3.0, 1 / 4.0, 1 / 2.0, 1 / 3.0, 1 / 4.0, 1 / 5.0, 1 / 3.0, 1 / 4.0, 1 / 5.0, 1 / 6.0,
         1 / 4.0, 1 / 5.0, 1 / 6.0, 1 / 7.0});
    vector<double> eigenValues{0.0, 0.0, 0.0, 0.0};
    AlbaMatrix<double> eigenVectors(4, 4);
    gsl_matrix_view matrixViewHilbert = gsl_matrix_view_array(matrixHilbert.getMatrixDataReference().data(), 4, 4);
    gsl_vector_view eigenValuesView = gsl_vector_view_array(eigenValues.data(), 4);
    gsl_matrix_view eigenVectorsView = gsl_matrix_view_array(eigenVectors.getMatrixDataReference().data(), 4, 4);

    gsl_eigen_symmv_workspace *workspace = gsl_eigen_symmv_alloc(4);
    gsl_eigen_symmv(&matrixViewHilbert.matrix, &eigenValuesView.vector, &eigenVectorsView.matrix, workspace);
    gsl_eigen_symmv_free(workspace);
    gsl_eigen_symmv_sort(&eigenValuesView.vector, &eigenVectorsView.matrix, GSL_EIGEN_SORT_ABS_ASC);

    vector<double> const expectedEigenValues{
        9.6702304022603313e-05, 0.0067382736057606408, 0.16914122022144978, 1.5002142800592426};
    AlbaMatrix<double> const expectedEigenVectors(
        4, 4,
        {-0.029193323164787031432, -0.17918629053545487295, 0.58207569949723725333, 0.79260829116376363412,
         0.32871205576319251218, 0.74191779062845186754, -0.37050218506709270416, 0.45192312090159986182,
         -0.79141114583312643926, -0.1002281369471880873, -0.50957863450179985421, 0.32241639858182497003,
         0.5145527499971501717, -0.63828252819361663839, -0.5140482722221645373, 0.25216116968824192623});
    EXPECT_EQ(expectedEigenVectors, eigenVectors);
    EXPECT_EQ(expectedEigenValues, eigenValues);
}

TEST(GslTest, FastFourierTransformInGslWorks) {
    // This is an using gsl_fft_real_transform() and gsl_fft_halfcomplex_inverse().
    // It generates a real signal in the shape of a square pulse.
    // The pulse is Fourier transformed to frequency space, and all but the lowest ten frequency components are removed
    // from the array of Fourier coefficients returned by gsl_fft_real_transform().
    // The remaining Fourier coefficients are transformed back to the time-domain,
    // to give a filtered version of the square pulse.
    // Since Fourier coefficients are stored using the half-complex symmetry both positive and negative
    // frequencies are removed and the final filtered signal is also real.
    constexpr int NUMBER_OF_ITEMS = 100;
    array<double, NUMBER_OF_ITEMS> inputData{};
    gsl_fft_real_workspace *workspace = gsl_fft_real_workspace_alloc(NUMBER_OF_ITEMS);
    int index{};
    for (index = 0; index < NUMBER_OF_ITEMS; ++index) {
        inputData[index] = 0.0;
    }
    for (index = NUMBER_OF_ITEMS / 3; index < 2 * NUMBER_OF_ITEMS / 3; ++index) {
        inputData[index] = 1.0;
    }
    for (index = 0; index < NUMBER_OF_ITEMS; ++index) {
        cout << index << ": " << inputData[index] << ", ";
    }
    cout << "\n";

    gsl_fft_real_wavetable *real = gsl_fft_real_wavetable_alloc(NUMBER_OF_ITEMS);
    gsl_fft_real_transform(inputData.data(), 1, NUMBER_OF_ITEMS, real, workspace);
    gsl_fft_real_wavetable_free(real);
    for (index = 11; index < NUMBER_OF_ITEMS; ++index) {
        inputData[index] = 0;
    }

    gsl_fft_halfcomplex_wavetable *halfComplex = gsl_fft_halfcomplex_wavetable_alloc(NUMBER_OF_ITEMS);
    gsl_fft_halfcomplex_inverse(inputData.data(), 1, NUMBER_OF_ITEMS, halfComplex, workspace);
    gsl_fft_halfcomplex_wavetable_free(halfComplex);
    for (index = 0; index < NUMBER_OF_ITEMS; ++index) {
        cout << index << ": " << inputData[index] << ", ";
    }
    cout << "\n";

    gsl_fft_real_workspace_free(workspace);
}

TEST(GslTest, NumericalAdaptiveIntegrationInGslWorks) {
    // This uses adaptive integration to integrate.
    // The integrator QAGS will handle a large class of definite integrals.
    // For example, consider the following integral, which has an algebraic-logarithmic singularity at the origin,
    // integrate(x^(-1/2) * log(x) dx) evaluated from 1 to 0 = -4
    // The program below computes this integral to a relative accuracy bound of 1e-7.
    gsl_integration_workspace *workspace = gsl_integration_workspace_alloc(1000);
    double estimatedError{};
    double alpha = 1.0;
    gsl_function gslFunction{};
    gslFunction.function = &function1ToIntegrate;
    gslFunction.params = &alpha;

    double actualValue{};
    gsl_integration_qags(&gslFunction, 0, 1, 0, 1e-7, 1000, workspace, &actualValue, &estimatedError);

    double const expectedValue = -4.0;
    cout << "actualValue = " << actualValue << "\n";
    cout << "expectedValue = " << expectedValue << "\n";
    cout << "estimatedError = " << estimatedError << "\n";
    cout << "actualError = " << actualValue - expectedValue << "\n";
    cout << "intervals = " << workspace->size << "\n";
    EXPECT_TRUE(isAlmostEqual(expectedValue, actualValue, AlbaMathConstants::COMPARISON_TOLERANCE_FOR_FLOAT));

    gsl_integration_workspace_free(workspace);
}

TEST(GslTest, NumericalFixedPointQuadratureIntegrationInGslWorks) {
    // This uses a fixed-point quadrature rule to integrate.
    // Consulting our table of fixed point quadratures,
    // we see that this integral can be evaluated with a Hermite uadrature rule, setting  = 0; a = 0; b = 1.
    // Since we are integrating a polynomial of degree m,
    // we need to choose the number of nodes n  (m + 1) = 2 to achieve the best results.
    constexpr int numberOfQuadratureNodes = 6;
    const gsl_integration_fixed_type *integrationType = gsl_integration_fixed_hermite;
    gsl_integration_fixed_workspace *workspace =
        gsl_integration_fixed_alloc(integrationType, numberOfQuadratureNodes, 0.0, 1.0, 0.0, 0.0);
    int mFunctionInput = 10;
    double actualValue{};
    gsl_function gslFunction{};
    gslFunction.function = &function2ToIntegrate;
    gslFunction.params = &mFunctionInput;

    gsl_integration_fixed(&gslFunction, &actualValue, workspace);

    double const expectedValue =
        (mFunctionInput % 2 == 0) ? M_SQRTPI + gsl_sf_gamma(0.5 * (1.0 + mFunctionInput)) : M_SQRTPI;
    cout << "mFunctionInput = " << mFunctionInput << "\n";
    cout << "intervals = " << gsl_integration_fixed_n(workspace) << "\n";
    cout << "actualValue = " << actualValue << "\n";
    cout << "expectedValue = " << expectedValue << "\n";
    cout << "actualError = " << actualValue - expectedValue << "\n";
    EXPECT_TRUE(isAlmostEqual(expectedValue, actualValue, AlbaMathConstants::COMPARISON_TOLERANCE_FOR_FLOAT));

    gsl_integration_fixed_free(workspace);
}

TEST(GslTest, UsingARandomGeneratorInGslWorks) {
    // This demonstrates the use of a random number generator
    // to produce uniform random numbers in the range [0.0, 1.0),
    const gsl_rng_type *randomGeneratorType = gsl_rng_default;
    gsl_rng_env_setup();
    gsl_rng *randomGenerator = gsl_rng_alloc(randomGeneratorType);
    int const NUMBER_OF_ITEMS = 10;
    for (int index = 0; index < NUMBER_OF_ITEMS; ++index) {
        cout << gsl_rng_uniform(randomGenerator) << ",";
    }
    cout << "\n";

    gsl_rng_free(randomGenerator);
}

TEST(GslTest, UsingAQuasiRandomGeneratorInGslWorks) {
    // The following program prints the first 10 points of the 2-dimensional Sobol sequence.
    gsl_qrng *quasiRandomSequenceGenerator = gsl_qrng_alloc(gsl_qrng_sobol, 2);
    array<double, 2> randomValues{};
    for (int index = 0; index < 10; ++index) {
        gsl_qrng_get(quasiRandomSequenceGenerator, randomValues.data());
        cout << randomValues[0] << " " << randomValues[1] << ",";
    }
    cout << "\n";

    gsl_qrng_free(quasiRandomSequenceGenerator);
}

TEST(GslTest, UsingARandomGeneratorWithPoissonDistributionWorks) {
    // The following program demonstrates the use of a random number generator to produce variates from a distribution.
    // It prints 10 samples from the Poisson distribution with a mean of 3.
    double const mu = 3.0;
    gsl_rng_env_setup();
    const gsl_rng_type *randomGeneratorType = gsl_rng_default;
    gsl_rng *randomGenerator = gsl_rng_alloc(randomGeneratorType);
    int const NUMBER_OF_ITEMS = 10;
    for (int index = 0; index < NUMBER_OF_ITEMS; ++index) {
        cout << gsl_ran_poisson(randomGenerator, mu) << ",";
    }
    printf("\n");

    gsl_rng_free(randomGenerator);
}

TEST(GslTest, UsingARandomGeneratorWithTwoDimensionsWorks) {
    // This demonstrates the use of a random number generator to produce variates from a distribution.
    // It prints 10 samples from the Poisson distribution with a mean of 3.
    double x = 0;
    double y = 0;
    gsl_rng_env_setup();
    const gsl_rng_type *randomGeneratorType = gsl_rng_default;
    gsl_rng *randomGenerator = gsl_rng_alloc(randomGeneratorType);
    int const NUMBER_OF_ITEMS = 10;
    for (int index = 0; index < NUMBER_OF_ITEMS; ++index) {
        double dx = 0;
        double dy = 0;
        gsl_ran_dir_2d(randomGenerator, &dx, &dy);
        x += dx;
        y += dy;
        cout << "(" << x << "," << y << "), ";
    }
    printf("\n");

    gsl_rng_free(randomGenerator);
}

TEST(GslTest, GettingPdfAnCdfWorks) {
    // This computes the upper and lower cumulative distribution functions for the standard normal distribution at x
    // = 2.
    double x = 2.0;
    double const P = gsl_cdf_ugaussian_P(x);
    cout << "prob(x < " << x << ") = " << P << "\n";
    EXPECT_DOUBLE_EQ(0.97724986805182079, P);

    double const Q = gsl_cdf_ugaussian_Q(x);
    cout << "prob(x > " << x << ") = " << Q << "\n";
    EXPECT_DOUBLE_EQ(0.022750131948179212, Q);

    x = gsl_cdf_ugaussian_Pinv(P);
    cout << "Pinv(" << P << ") = " << x << "\n";
    EXPECT_DOUBLE_EQ(2, x);

    x = gsl_cdf_ugaussian_Qinv(Q);
    cout << "Qinv(" << Q << ") = " << x << "\n";
    EXPECT_DOUBLE_EQ(2, x);
}

TEST(GslTest, GettingStatisticsWorks) {
    // This is a basic example of how to use the statistical functions
    array<double, 5> values = {17.2, 18.1, 16.5, 18.3, 12.6};

    double const mean = gsl_stats_mean(values.data(), 1, 5);
    cout << "The sample mean is " << mean << "\n";
    EXPECT_DOUBLE_EQ(16.539999999999999, mean);

    double const variance = gsl_stats_variance(values.data(), 1, 5);
    cout << "The estimated variance is " << variance << "\n";
    EXPECT_DOUBLE_EQ(5.373, variance);

    double const largest = gsl_stats_max(values.data(), 1, 5);
    cout << "The largest value is " << largest << "\n";
    EXPECT_DOUBLE_EQ(18.3, largest);

    double const smallest = gsl_stats_min(values.data(), 1, 5);
    cout << "The smallest value is " << smallest << "\n";
    EXPECT_DOUBLE_EQ(12.6, smallest);
}

TEST(GslTest, GettingStatisticsInSortedDAtaWorks) {
    // This is an example using sorted data
    array<double, 5> values = {17.2, 18.1, 16.5, 18.3, 12.6};
    gsl_sort(values.data(), 1, 5);

    double const median = gsl_stats_median_from_sorted_data(values.data(), 1, 5);
    cout << "The median is " << median << "\n";
    EXPECT_DOUBLE_EQ(17.199999999999999, median);

    double const upperq = gsl_stats_quantile_from_sorted_data(values.data(), 1, 5, 0.75);
    cout << "The upper quartile is " << upperq << "\n";
    EXPECT_DOUBLE_EQ(18.100000000000001, upperq);

    double const lowerq = gsl_stats_quantile_from_sorted_data(values.data(), 1, 5, 0.25);
    cout << "The lower quartile is " << lowerq << "\n";
    EXPECT_DOUBLE_EQ(16.5, lowerq);
}

TEST(GslTest, GettingRunningStatisticsWorks) {
    // This is a basic example of how to use the running statistical functions
    array<double, 5> const values = {17.2, 18.1, 16.5, 18.3, 12.6};

    gsl_rstat_workspace *runningStatistics = gsl_rstat_alloc();

    // add data to rstat accumulator
    for (double const value : values) {
        gsl_rstat_add(value, runningStatistics);
    }

    double const mean = gsl_rstat_mean(runningStatistics);
    cout << "The sample mean is " << mean << "\n";
    EXPECT_DOUBLE_EQ(16.539999999999999, mean);

    double const variance = gsl_rstat_variance(runningStatistics);
    cout << "The estimated variance is " << variance << "\n";
    EXPECT_DOUBLE_EQ(5.3729999999999984, variance);

    double const largest = gsl_rstat_max(runningStatistics);
    cout << "The largest value is " << largest << "\n";
    EXPECT_DOUBLE_EQ(18.300000000000001, largest);

    double const smallest = gsl_rstat_min(runningStatistics);
    cout << "The smallest value is " << smallest << "\n";
    EXPECT_DOUBLE_EQ(12.6, smallest);

    double const median = gsl_rstat_median(runningStatistics);
    cout << "The median is " << median << "\n";
    EXPECT_DOUBLE_EQ(17.199999999999999, median);

    double const sd = gsl_rstat_sd(runningStatistics);
    cout << "The standard deviation is " << sd << "\n";
    EXPECT_DOUBLE_EQ(2.3179732526498227, sd);

    double const sdMean = gsl_rstat_sd_mean(runningStatistics);
    cout << "The standard devation of the mean is " << sdMean << "\n";
    EXPECT_DOUBLE_EQ(1.0366291525902596, sdMean);

    double const skew = gsl_rstat_skew(runningStatistics);
    cout << "The skew is " << skew << "\n";
    EXPECT_DOUBLE_EQ(-0.82905750003696543, skew);

    double const rms = gsl_rstat_rms(runningStatistics);
    cout << "The root mean square is " << rms << "\n";
    EXPECT_DOUBLE_EQ(16.669433103738111, rms);

    double const kurtosis = gsl_rstat_kurtosis(runningStatistics);
    cout << "The kurtosis " << kurtosis << "\n";
    EXPECT_DOUBLE_EQ(-1.2217029020861698, kurtosis);

    size_t n = gsl_rstat_n(runningStatistics);
    cout << "There are " << n << " items in the accumulator\n";
    gsl_rstat_reset(runningStatistics);
    EXPECT_DOUBLE_EQ(5, n);

    n = gsl_rstat_n(runningStatistics);
    cout << "There are " << n << " items in the accumulator\n";
    gsl_rstat_free(runningStatistics);
    EXPECT_DOUBLE_EQ(0, n);
}

TEST(GslTest, GettingMovingStatisticsWorks) {
    // The following example program computes the moving mean, minimum and maximum of a noisy sinusoid signal of
    // length N = 500 with a symmetric moving window of size K = 11.
    const size_t N = 500; /* length of time series */
    const size_t K = 11;  /* window size */
    gsl_movstat_workspace *w = gsl_movstat_alloc(K);
    gsl_vector *x = gsl_vector_alloc(N);
    gsl_vector *xmean = gsl_vector_alloc(N);
    gsl_vector *xmin = gsl_vector_alloc(N);
    gsl_vector *xmax = gsl_vector_alloc(N);
    gsl_rng *r = gsl_rng_alloc(gsl_rng_default);
    size_t i = 0;
    for (i = 0; i < N; ++i) {
        double const xi = cos(4.0 * M_PI * i / static_cast<double>(N));
        double const ei = gsl_ran_gaussian(r, 0.1);
        gsl_vector_set(x, i, xi + ei);
    }
    /* compute moving statistics */
    gsl_movstat_mean(GSL_MOVSTAT_END_PADVALUE, x, xmean, w);
    gsl_movstat_minmax(GSL_MOVSTAT_END_PADVALUE, x, xmin, xmax, w);
    /* print results */
    for (i = 0; i < N; ++i) {
        printf(
            "%zu %f %f %f %f\n", i, gsl_vector_get(x, i), gsl_vector_get(xmean, i), gsl_vector_get(xmin, i),
            gsl_vector_get(xmax, i));
    }
    gsl_vector_free(x);
    gsl_vector_free(xmean);
    gsl_rng_free(r);
    gsl_movstat_free(w);
}

TEST(GslTest, GettingMovingStatisticsWorksOnGaussianRandomVariates) {
    // The following example program analyzes a time series of length N = 1000 composed of Gaussian random variates
    // with zero mean whose standard deviation changes in a piecewise constant fashion
    const size_t N = 1000;                               /* length of time series */
    const double sigma[] = {1.0, 5.0, 1.0, 3.0, 5.0};    /* variances */
    const size_t N_sigma[] = {200, 450, 600, 850, 1000}; /* samples where variance␣
,!changes */
    const size_t K = 41;                                 /* window size */
    gsl_vector *x = gsl_vector_alloc(N);
    gsl_vector *xmedian = gsl_vector_alloc(N);
    gsl_vector *xmad = gsl_vector_alloc(N);
    gsl_vector *xiqr = gsl_vector_alloc(N);
    gsl_vector *xSn = gsl_vector_alloc(N);
    gsl_vector *xQn = gsl_vector_alloc(N);
    gsl_vector *xsd = gsl_vector_alloc(N);
    gsl_rng *r = gsl_rng_alloc(gsl_rng_default);
    gsl_movstat_workspace *w = gsl_movstat_alloc(K);
    size_t idx = 0;
    size_t i = 0;
    for (i = 0; i < N; ++i) {
        double const gi = gsl_ran_gaussian(r, sigma[idx]);
        double const u = gsl_rng_uniform(r);
        double const outlier = (u < 0.01) ? 15.0 * GSL_SIGN(gi) : 0.0;
        double const xi = gi + outlier;
        gsl_vector_set(x, i, xi);
        if (i == N_sigma[idx] - 1) {
            ++idx;
        }
    }
    /* compute moving statistics */
    gsl_movstat_mad(GSL_MOVSTAT_END_TRUNCATE, x, xmedian, xmad, w);
    gsl_movstat_qqr(GSL_MOVSTAT_END_TRUNCATE, x, 0.25, xiqr, w);
    gsl_movstat_Sn(GSL_MOVSTAT_END_TRUNCATE, x, xSn, w);
    gsl_movstat_Qn(GSL_MOVSTAT_END_TRUNCATE, x, xQn, w);
    gsl_movstat_sd(GSL_MOVSTAT_END_TRUNCATE, x, xsd, w);
    /* scale IQR by factor to approximate standard deviation */
    gsl_vector_scale(xiqr, 0.7413);
    /* print results */
    idx = 0;
    for (i = 0; i < N; ++i) {
        printf(
            "%zu %f %f %f %f %f %f %f\n", i, gsl_vector_get(x, i), sigma[idx], gsl_vector_get(xmad, i),
            gsl_vector_get(xiqr, i), gsl_vector_get(xSn, i), gsl_vector_get(xQn, i), gsl_vector_get(xsd, i));
        if (i == N_sigma[idx] - 1) {
            ++idx;
        }
    }
    gsl_vector_free(x);
    gsl_vector_free(xmedian);
    gsl_vector_free(xmad);
    gsl_vector_free(xiqr);
    gsl_vector_free(xSn);
    gsl_vector_free(xQn);
    gsl_vector_free(xsd);
    gsl_rng_free(r);
    gsl_movstat_free(w);
}

TEST(GslTest, GettingMovingStatisticsWorksOnUserDefinedMovingWindow) {
    // This example program illustrates how a user can define their own moving window function to apply to an input
    // vector. It constructs a random noisy time series of length N = 1000 with some outliers added. Then it applies a
    // moving window trimmed mean to the time series with trim parameter  = 0:1. The length of the moving window is K =
    // 11, so the smallest and largest sample of each window is discarded prior to computing the mean.
    const size_t N = 1000;               /* length of time series */
    const size_t K = 11;                 /* window size */
    double alpha = 0.1;                  /* trimmed mean parameter */
    gsl_vector *x = gsl_vector_alloc(N); /* input vector */
    gsl_vector *y = gsl_vector_alloc(N); /* filtered output vector for alpha1 */
    gsl_rng *r = gsl_rng_alloc(gsl_rng_default);
    gsl_movstat_workspace *w = gsl_movstat_alloc(K);
    gsl_movstat_function F;
    size_t i = 0;
    double sum = 0.0;
    /* generate input signal */
    for (i = 0; i < N; ++i) {
        double const ui = gsl_ran_gaussian(r, 1.0);
        double const outlier = (gsl_rng_uniform(r) < 0.01) ? 10.0 * GSL_SIGN(ui) : 0.0;
        sum += ui;
        gsl_vector_set(x, i, sum + outlier);
    }
    /* apply moving window function */
    F.function = func;
    F.params = &alpha;
    gsl_movstat_apply(GSL_MOVSTAT_END_PADVALUE, &F, x, y, w);
    /* print results */
    for (i = 0; i < N; ++i) {
        double const xi = gsl_vector_get(x, i);
        double const yi = gsl_vector_get(y, i);
        printf("%f %f\n", xi, yi);
    }
    gsl_vector_free(x);
    gsl_vector_free(y);
    gsl_rng_free(r);
    gsl_movstat_free(w);
}

TEST(GslTest, GettingRunningStatisticsForQuantileWorks) {
    // This estimates the lower quartile, median and upper quartile from 100 samples of a random Rayleigh
    // distribution. This uses the P2 algorithm of Jain and Chlamtec. For comparison, the exact values are also computed
    // from the sorted dataset.
    array<double, 100> values = {};

    gsl_rstat_quantile_workspace *workspaceFor25 = gsl_rstat_quantile_alloc(0.25);
    gsl_rstat_quantile_workspace *workspaceFor50 = gsl_rstat_quantile_alloc(0.5);
    gsl_rstat_quantile_workspace *workspaceFor75 = gsl_rstat_quantile_alloc(0.75);
    gsl_rng *randomGenerator = gsl_rng_alloc(gsl_rng_default);

    // add data to quantile accumulators; also store data for exact comparisons
    for (double &value : values) {
        value = gsl_ran_rayleigh(randomGenerator, 1.0);
        gsl_rstat_quantile_add(value, workspaceFor25);
        gsl_rstat_quantile_add(value, workspaceFor50);
        gsl_rstat_quantile_add(value, workspaceFor75);
    }

    // exact values
    gsl_sort(values.data(), 1, values.size());
    double const exactFor25 =
        gsl_stats_quantile_from_sorted_data(values.data(), 1, static_cast<int>(values.size()), 0.25);
    double const exactFor50 =
        gsl_stats_quantile_from_sorted_data(values.data(), 1, static_cast<int>(values.size()), 0.5);
    double const exactFor75 =
        gsl_stats_quantile_from_sorted_data(values.data(), 1, static_cast<int>(values.size()), 0.75);

    // estimated values
    double const actualFor25 = gsl_rstat_quantile_get(workspaceFor25);
    double const actualFor50 = gsl_rstat_quantile_get(workspaceFor50);
    double const actualFor75 = gsl_rstat_quantile_get(workspaceFor75);
    cout << "0.25 quartile: exact = " << exactFor25 << ", estimated = " << actualFor25
         << ", error = " << (actualFor25 - exactFor25) / exactFor25 << "\n";
    cout << "0.50 quartile: exact = " << exactFor50 << ", estimated = " << actualFor50
         << ", error = " << (actualFor50 - exactFor50) / exactFor50 << "\n";
    cout << "0.75 quartile: exact = " << exactFor75 << ", estimated = " << actualFor75
         << ", error = " << (actualFor75 - exactFor75) / exactFor75 << "\n";

    gsl_rstat_quantile_free(workspaceFor25);
    gsl_rstat_quantile_free(workspaceFor50);
    gsl_rstat_quantile_free(workspaceFor75);
    gsl_rng_free(randomGenerator);
}

TEST(GslTest, GaussianFilterWorksInExample1) {
    // This illustrates the Gaussian filter applied to smoothing a time series of lengthN = 500 with a
    // kernel size of K = 51. Three filters are applied with parameters  = 0:5; 3; 10. We see that the filter
    // corresponding to  = 0:5 applies the most smoothing, while  = 10 corresponds to the least amount of smoothing.
    const size_t N = 500;                     /* length of time series */
    const size_t K = 51;                      /* window size */
    const double alpha[3] = {0.5, 3.0, 10.0}; /* alpha values */
    gsl_vector *x = gsl_vector_alloc(N);      /* input vector */
    gsl_vector *y1 = gsl_vector_alloc(N);     /* filtered output vector for alpha1 */
    gsl_vector *y2 = gsl_vector_alloc(N);     /* filtered output vector for alpha2 */
    gsl_vector *y3 = gsl_vector_alloc(N);     /* filtered output vector for alpha3 */
    gsl_vector *k1 = gsl_vector_alloc(K);     /* Gaussian kernel for alpha1 */
    gsl_vector *k2 = gsl_vector_alloc(K);     /* Gaussian kernel for alpha2 */
    gsl_vector *k3 = gsl_vector_alloc(K);     /* Gaussian kernel for alpha3 */
    gsl_rng *r = gsl_rng_alloc(gsl_rng_default);
    gsl_filter_gaussian_workspace *gauss_p = gsl_filter_gaussian_alloc(K);
    size_t i = 0;
    double sum = 0.0;
    /* generate input signal */
    for (i = 0; i < N; ++i) {
        double const ui = gsl_ran_gaussian(r, 1.0);
        sum += ui;
        gsl_vector_set(x, i, sum);
    }
    /* compute kernels without normalization */
    gsl_filter_gaussian_kernel(alpha[0], 0, 0, k1);
    gsl_filter_gaussian_kernel(alpha[1], 0, 0, k2);
    gsl_filter_gaussian_kernel(alpha[2], 0, 0, k3);
    /* apply filters */
    gsl_filter_gaussian(GSL_FILTER_END_PADVALUE, alpha[0], 0, x, y1, gauss_p);
    gsl_filter_gaussian(GSL_FILTER_END_PADVALUE, alpha[1], 0, x, y2, gauss_p);
    gsl_filter_gaussian(GSL_FILTER_END_PADVALUE, alpha[2], 0, x, y3, gauss_p);
    /* print kernels */
    for (i = 0; i < K; ++i) {
        double const k1i = gsl_vector_get(k1, i);
        double const k2i = gsl_vector_get(k2, i);
        double const k3i = gsl_vector_get(k3, i);
        printf("%e %e %e\n", k1i, k2i, k3i);
    }
    printf("\n\n");
    /* print filter results */
    for (i = 0; i < N; ++i) {
        double const xi = gsl_vector_get(x, i);
        double const y1i = gsl_vector_get(y1, i);
        double const y2i = gsl_vector_get(y2, i);
        double const y3i = gsl_vector_get(y3, i);
        printf("%.12e %.12e %.12e %.12e\n", xi, y1i, y2i, y3i);
    }
    gsl_vector_free(x);
    gsl_vector_free(y1);
    gsl_vector_free(y2);
    gsl_vector_free(y3);
    gsl_vector_free(k1);
    gsl_vector_free(k2);
    gsl_vector_free(k3);
    gsl_rng_free(r);
    gsl_filter_gaussian_free(gauss_p);
}

TEST(GslTest, GaussianFilterWorksInExample2) {
    // A common application of the Gaussian filter is to detect edges, or sudden jumps, in a noisy input signal.
    // It is used both for 1D edge detection in time series, as well as 2D edge detection in images.
    // Here we will examine a noisy time series of length N = 1000 with a single edge.
    const size_t N = 1000;                 /* length of time series */
    const size_t K = 61;                   /* window size */
    const double alpha = 3.0;              /* Gaussian kernel has +/- 3 standard␣
                 ,!deviations */
    gsl_vector *x = gsl_vector_alloc(N);   /* input vector */
    gsl_vector *y = gsl_vector_alloc(N);   /* filtered output vector */
    gsl_vector *dy = gsl_vector_alloc(N);  /* first derivative filtered vector */
    gsl_vector *d2y = gsl_vector_alloc(N); /* second derivative filtered vector */
    gsl_rng *r = gsl_rng_alloc(gsl_rng_default);
    gsl_filter_gaussian_workspace *gauss_p = gsl_filter_gaussian_alloc(K);
    size_t i = 0;
    /* generate input signal */
    for (i = 0; i < N; ++i) {
        double const xi = (i > N / 2) ? 0.5 : 0.0;
        double const ei = gsl_ran_gaussian(r, 0.1);
        gsl_vector_set(x, i, xi + ei);
    }
    /* apply filters */
    gsl_filter_gaussian(GSL_FILTER_END_PADVALUE, alpha, 0, x, y, gauss_p);
    gsl_filter_gaussian(GSL_FILTER_END_PADVALUE, alpha, 1, x, dy, gauss_p);
    gsl_filter_gaussian(GSL_FILTER_END_PADVALUE, alpha, 2, x, d2y, gauss_p);
    /* print results */
    for (i = 0; i < N; ++i) {
        double const xi = gsl_vector_get(x, i);
        double const yi = gsl_vector_get(y, i);
        double const dyi = gsl_vector_get(dy, i);
        double const d2yi = gsl_vector_get(d2y, i);
        double dxi = NAN;
        /* compute finite difference of x vector */
        if (i == 0) {
            dxi = gsl_vector_get(x, i + 1) - xi;
        } else if (i == N - 1) {
            dxi = gsl_vector_get(x, i) - gsl_vector_get(x, i - 1);
        } else {
            dxi = 0.5 * (gsl_vector_get(x, i + 1) - gsl_vector_get(x, i - 1));
        }
        printf("%.12e %.12e %.12e %.12e %.12e\n", xi, yi, dxi, dyi, d2yi);
    }
    gsl_vector_free(x);
    gsl_vector_free(y);
    gsl_vector_free(dy);
    gsl_vector_free(d2y);
    gsl_rng_free(r);
    gsl_filter_gaussian_free(gauss_p);
}

TEST(GslTest, MedianFilterWorksInSquareWaveSignalExample) {
    // The following example program illustrates the median filters on a noisy square wave signal. Median filters are
    // well known for preserving sharp edges in the input signal while reducing noise. The program constructs a 5 Hz
    // square wave signal with Gaussian noise added. Then the signal is filtered with a standard median filter and
    // recursive median filter using a symmetric window of length K = 7.
    const size_t N = 1000; /* length of time series */
    const size_t K = 7;    /* window size */
    const double f = 5.0;  /* frequency of square wave in Hz␣
     ,!*/
    gsl_filter_median_workspace *median_p = gsl_filter_median_alloc(K);
    gsl_filter_rmedian_workspace *rmedian_p = gsl_filter_rmedian_alloc(K);
    gsl_vector *t = gsl_vector_alloc(N);         /* time */
    gsl_vector *x = gsl_vector_alloc(N);         /* input vector */
    gsl_vector *y_median = gsl_vector_alloc(N);  /* median filtered output */
    gsl_vector *y_rmedian = gsl_vector_alloc(N); /* recursive median filtered␣
    ,!output */
    gsl_rng *r = gsl_rng_alloc(gsl_rng_default);
    size_t i = 0;
    /* generate input signal */
    for (i = 0; i < N; ++i) {
        double const ti = static_cast<double>(i) / (N - 1.0);
        double const tmp = sin(2.0 * M_PI * f * ti);
        double const xi = (tmp >= 0.0) ? 1.0 : -1.0;
        double const ei = gsl_ran_gaussian(r, 0.1);
        gsl_vector_set(t, i, ti);
        gsl_vector_set(x, i, xi + ei);
    }
    gsl_filter_median(GSL_FILTER_END_PADVALUE, x, y_median, median_p);
    gsl_filter_rmedian(GSL_FILTER_END_PADVALUE, x, y_rmedian, rmedian_p);
    /* print results */
    for (i = 0; i < N; ++i) {
        double const ti = gsl_vector_get(t, i);
        double const xi = gsl_vector_get(x, i);
        double const medi = gsl_vector_get(y_median, i);
        double const rmedi = gsl_vector_get(y_rmedian, i);
        printf("%f %f %f %f\n", ti, xi, medi, rmedi);
    }
    gsl_vector_free(t);
    gsl_vector_free(x);
    gsl_vector_free(y_median);
    gsl_vector_free(y_rmedian);
    gsl_rng_free(r);
    gsl_filter_median_free(median_p);
}

TEST(GslTest, ImpulseDetectionFilterWorksInSquareWaveSignalExample) {
    // The following example program illustrates the impulse detection filter.
    // First, it constructs a sinusoid signal of length N = 1000 with Gaussian noise added.
    // Then, about 1% of the data are perturbed to represent large outliers.
    // An impulse detecting filter is applied with a window size K = 25 and tuning parameter t = 4, using the Qn
    // statistic as the robust measure of scale.
    const size_t N = 1000;                              /* length of time series */
    const size_t K = 25;                                /* window size */
    const double t = 4.0;                               /* number of scale factors for␣
                                  ,!outlier detection */
    gsl_vector *x = gsl_vector_alloc(N);                /* input vector */
    gsl_vector *y = gsl_vector_alloc(N);                /* output (filtered) vector */
    gsl_vector *xmedian = gsl_vector_alloc(N);          /* window medians */
    gsl_vector *xsigma = gsl_vector_alloc(N);           /* window scale estimates */
    gsl_vector_int *ioutlier = gsl_vector_int_alloc(N); /* outlier detected? */
    gsl_filter_impulse_workspace *w = gsl_filter_impulse_alloc(K);
    gsl_rng *r = gsl_rng_alloc(gsl_rng_default);
    size_t noutlier = 0;
    size_t i = 0;
    /* generate input signal */
    for (i = 0; i < N; ++i) {
        double const xi = 10.0 * sin(2.0 * M_PI * i / static_cast<double>(N));
        double const ei = gsl_ran_gaussian(r, 2.0);
        double const u = gsl_rng_uniform(r);
        double const outlier = (u < 0.01) ? 15.0 * GSL_SIGN(ei) : 0.0;
        gsl_vector_set(x, i, xi + ei + outlier);
    }
    /* apply impulse detection filter */
    gsl_filter_impulse(GSL_FILTER_END_TRUNCATE, GSL_FILTER_SCALE_QN, t, x, y, xmedian, xsigma, &noutlier, ioutlier, w);
    /* print results */
    for (i = 0; i < N; ++i) {
        double const xi = gsl_vector_get(x, i);
        double const yi = gsl_vector_get(y, i);
        double const xmedi = gsl_vector_get(xmedian, i);
        double const xsigmai = gsl_vector_get(xsigma, i);
        int const outlier = gsl_vector_int_get(ioutlier, i);
        printf("%zu %f %f %f %f %d\n", i, xi, yi, xmedi + t * xsigmai, xmedi - t * xsigmai, outlier);
    }
    gsl_vector_free(x);
    gsl_vector_free(y);
    gsl_vector_free(xmedian);
    gsl_vector_free(xsigma);
    gsl_vector_int_free(ioutlier);
    gsl_filter_impulse_free(w);
    gsl_rng_free(r);
}

TEST(GslTest, DISABLED_OneDimensionalHistogramWorks) {
    // The following program shows how to make a simple histogram of a column of numerical data supplied on stdin. The
    // program takes three arguments, specifying the upper and lower bounds of the histogram and the number of bins. It
    // then reads numbers from stdin, one line at a time, and adds them to the histogram. When there is no more data to
    // read it prints out the accumulated histogram using gsl_histogram_fprintf().
    double const minimumValue = -100;
    double const maximumValue = 100;
    size_t const n = 10;
    double x = NAN;
    gsl_histogram *h = gsl_histogram_alloc(n);
    gsl_histogram_set_ranges_uniform(h, minimumValue, maximumValue);
    while (fscanf(stdin, "%lg", &x) == 1) {
        gsl_histogram_increment(h, x);
    }
    gsl_histogram_fprintf(stdout, h, "%g", "%g");
    gsl_histogram_free(h);
}

TEST(GslTest, TwoDimensionalHistogramWorks) {
    // This demonstrates two features of two-dimensional histograms.
    // First a 10-by-10 two-dimensional histogram is created with x and y running from 0 to 1.
    // Then a few sample points are added to the histogram, at (0.3,0.3) with a height of 1, at (0.8,0.1) with a height
    // of 5 and at (0.7,0.9) with a height of 0.5. This histogram with three events is used to generate a random sample
    // of 1000 simulated events, which are printed out.
    const gsl_rng_type *T = nullptr;
    gsl_rng *r = nullptr;
    gsl_histogram2d *h = gsl_histogram2d_alloc(10, 10);
    gsl_histogram2d_set_ranges_uniform(h, 0.0, 1.0, 0.0, 1.0);
    gsl_histogram2d_accumulate(h, 0.3, 0.3, 1);
    gsl_histogram2d_accumulate(h, 0.8, 0.1, 5);
    gsl_histogram2d_accumulate(h, 0.7, 0.9, 0.5);
    gsl_rng_env_setup();
    T = gsl_rng_default;
    r = gsl_rng_alloc(T);
    {
        int i = 0;
        gsl_histogram2d_pdf *p = gsl_histogram2d_pdf_alloc(h->nx, h->ny);
        gsl_histogram2d_pdf_init(p, h);
        for (i = 0; i < 1000; ++i) {
            double x = NAN;
            double y = NAN;
            double const u = gsl_rng_uniform(r);
            double const v = gsl_rng_uniform(r);
            gsl_histogram2d_pdf_sample(p, u, v, &x, &y);
            printf("%g %g\n", x, y);
        }
        gsl_histogram2d_pdf_free(p);
    }
    gsl_histogram2d_free(h);
    gsl_rng_free(r);
}

// TEST(GslTest, NTuplesWorks) {
//     // This demonstrate the use of ntuples in managing a large dataset. The first program
//     // creates a set of 10,000 simulated “events”, each with 3 associated values (x; y; z). These are generated from
//     a
//     // Gaussian distribution with unit variance, for demonstration purposes, and written to the ntuple file test.dat.
//     {
//         const gsl_rng_type *T;
//         gsl_rng *r;
//         struct data ntuple_row;
//         int i;
//         gsl_ntuple *ntuple = gsl_ntuple_create("test.dat", &ntuple_row, sizeof(ntuple_row));
//         gsl_rng_env_setup();
//         T = gsl_rng_default;
//         r = gsl_rng_alloc(T);
//         for (i = 0; i < 10000; i++) {
//             ntuple_row.x = gsl_ran_ugaussian(r);
//             ntuple_row.y = gsl_ran_ugaussian(r);
//             ntuple_row.z = gsl_ran_ugaussian(r);
//             gsl_ntuple_write(ntuple);
//         }
//         gsl_ntuple_close(ntuple);
//         gsl_rng_free(r);
//     }
//
//     // This analyses the ntuple data in the file test.dat. The analysis procedure is to compute the
//     // squared magnitude of each event, E2 = x2 + y2 + z2, and select only those which exceed a lower limit of 1.5.
//     The
//     // selected events are then histogrammed using their E2 values.
//     {
//         struct data ntuple_row;
//         gsl_ntuple *ntuple = gsl_ntuple_open("test.dat", &ntuple_row, sizeof(ntuple_row));
//         double lower = 1.5;
//         gsl_ntuple_select_fn S;
//         gsl_ntuple_value_fn V;
//         gsl_histogram *h = gsl_histogram_alloc(100);
//         gsl_histogram_set_ranges_uniform(h, 0.0, 10.0);
//         S.function = &sel_func;
//         S.params = &lower;
//         V.function = &val_func;
//         V.params = 0;
//         gsl_ntuple_project(h, ntuple, &V, &S);
//         gsl_histogram_fprintf(stdout, h, "%f", "%f");
//         gsl_histogram_free(h);
//         gsl_ntuple_close(ntuple);
//     }
// }

}  // namespace alba
