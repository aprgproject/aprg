#include <Common/Math/Matrix/AlbaMatrix.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::stringHelper;
using namespace std;

namespace alba::matrix {

TEST(AlbaMatrixTest, MatrixCanBeCopyConstructed) {
    AlbaMatrix<int> const matrix(2, 3, {1, 2, 3, 4, 5, 6});
    AlbaMatrix<int> copyConstructedMatrix;

    copyConstructedMatrix = matrix;

    AlbaMatrix<int> const expectedMatrix(2, 3, {1, 2, 3, 4, 5, 6});
    EXPECT_EQ(expectedMatrix, copyConstructedMatrix);
}

TEST(AlbaMatrixTest, MatrixCanBeCopyAssigned) {
    AlbaMatrix<int> const matrix(2, 3, {1, 2, 3, 4, 5, 6});
    AlbaMatrix<int> copyAssignedMatrix;

    copyAssignedMatrix = matrix;

    AlbaMatrix<int> const expectedMatrix(2, 3, {1, 2, 3, 4, 5, 6});
    EXPECT_EQ(expectedMatrix, copyAssignedMatrix);
}

TEST(AlbaMatrixTest, OperatorPlusWorks) {
    AlbaMatrix<int> const matrix(2, 3, {1, 2, 3, 4, 5, 6});

    AlbaMatrix<int> const matrixToVerify(matrix + matrix);

    AlbaMatrix<int> const expectedMatrix(2, 3, {2, 4, 6, 8, 10, 12});
    EXPECT_EQ(expectedMatrix, matrixToVerify);
}

TEST(AlbaMatrixTest, OperatorMinusWorks) {
    AlbaMatrix<int> const matrix1(2, 3, {100, 200, 300, 400, 500, 600});
    AlbaMatrix<int> const matrix2(2, 3, {1, 2, 3, 4, 5, 6});

    AlbaMatrix<int> const matrixToVerify(matrix1 - matrix2);

    AlbaMatrix<int> const expectedMatrix(2, 3, {99, 198, 297, 396, 495, 594});
    EXPECT_EQ(expectedMatrix, matrixToVerify);
}

TEST(AlbaMatrixTest, OperatorMultiplyWorksWithMatrixAndConstant) {
    AlbaMatrix<int> const matrix(2, 3, {1, 2, 3, 4, 5, 6});

    AlbaMatrix<int> const matrixToVerify(matrix * 2);

    AlbaMatrix<int> const expectedMatrix(2, 3, {2, 4, 6, 8, 10, 12});
    EXPECT_EQ(expectedMatrix, matrixToVerify);
}

TEST(AlbaMatrixTest, OperatorMultiplyWorksWithMatrixAndMatrix) {
    AlbaMatrix<int> const matrix1(3, 2, {1, 2, 3, 4, 5, 6});
    AlbaMatrix<int> const matrix2(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});

    AlbaMatrix<int> const matrixToVerify(matrix1 * matrix2);

    AlbaMatrix<int> const expectedMatrix(4, 2, {38, 44, 50, 56, 83, 98, 113, 128});
    EXPECT_EQ(expectedMatrix, matrixToVerify);
}

TEST(AlbaMatrixTest, OperatorPlusAssignmentWorks) {
    AlbaMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});

    matrix += matrix;

    AlbaMatrix<int> const expectedMatrix(2, 3, {2, 4, 6, 8, 10, 12});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaMatrixTest, OperatorMinusAssignmentWorks) {
    AlbaMatrix<int> matrix1(2, 3, {100, 200, 300, 400, 500, 600});
    AlbaMatrix<int> const matrix2(2, 3, {1, 2, 3, 4, 5, 6});

    matrix1 -= matrix2;

    AlbaMatrix<int> const expectedMatrix(2, 3, {99, 198, 297, 396, 495, 594});
    EXPECT_EQ(expectedMatrix, matrix1);
}

TEST(AlbaMatrixTest, OperatorMultiplyAssignmentWorksWithMatrixAndConstant) {
    AlbaMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});

    matrix *= 2;

    AlbaMatrix<int> const expectedMatrix(2, 3, {2, 4, 6, 8, 10, 12});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaMatrixTest, OperatorMultiplyAssignmentWorksWithMatrixAndMatrix) {
    AlbaMatrix<int> matrix1(3, 2, {1, 2, 3, 4, 5, 6});
    AlbaMatrix<int> const matrix2(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});

    matrix1 *= matrix2;

    AlbaMatrix<int> const expectedMatrix(4, 2, {38, 44, 50, 56, 83, 98, 113, 128});
    EXPECT_EQ(expectedMatrix, matrix1);
}

TEST(AlbaMatrixTest, OutputStreamOperatorWorks) {
    AlbaMatrix<int> const matrix(2, 3, {1, 2, 3, 4, 5, 6});

    EXPECT_EQ("Matrix output:\n-----\n|1|2|\n-----\n|3|4|\n-----\n|5|6|\n-----\n", convertToString(matrix));
}

TEST(AlbaMatrixTest, GetEntryWorksAsValueCanBeFetchedFromEmptyVector) {
    AlbaMatrix<int> const matrix(2, 3);

    EXPECT_EQ(0, matrix.getEntry(0, 0));
    EXPECT_EQ(0, matrix.getEntry(1, 0));
    EXPECT_EQ(0, matrix.getEntry(0, 1));
    EXPECT_EQ(0, matrix.getEntry(1, 1));
    EXPECT_EQ(0, matrix.getEntry(0, 2));
    EXPECT_EQ(0, matrix.getEntry(1, 2));
}

TEST(AlbaMatrixTest, GetEntryWorksAsValueCanBeFetchedFromNonEmptyVector) {
    AlbaMatrix<int> const matrix(2, 3, {1, 2, 3, 4, 5, 6});

    EXPECT_EQ(1, matrix.getEntry(0, 0));
    EXPECT_EQ(2, matrix.getEntry(1, 0));
    EXPECT_EQ(3, matrix.getEntry(0, 1));
    EXPECT_EQ(4, matrix.getEntry(1, 1));
    EXPECT_EQ(5, matrix.getEntry(0, 2));
    EXPECT_EQ(6, matrix.getEntry(1, 2));
}

TEST(AlbaMatrixTest, GetMatrixDataWorks) {
    AlbaMatrix<int> const matrix(2, 3, {1, 2, 3, 4, 5, 6});

    AlbaMatrix<int>::MatrixData const& matrixData(matrix.getMatrixData());

    ASSERT_EQ(6U, matrixData.size());
    EXPECT_EQ(1, matrixData[0]);
    EXPECT_EQ(2, matrixData[1]);
    EXPECT_EQ(3, matrixData[2]);
    EXPECT_EQ(4, matrixData[3]);
    EXPECT_EQ(5, matrixData[4]);
    EXPECT_EQ(6, matrixData[5]);
}

TEST(AlbaMatrixTest, AlbaMatrixCanBeCreatedByDefaultConstructor) {
    AlbaMatrix<int> const matrix;

    EXPECT_EQ(0U, matrix.getNumberOfColumns());
    EXPECT_EQ(0U, matrix.getNumberOfRows());
    AlbaMatrix<int>::MatrixData const& matrixData(matrix.getMatrixData());
    ASSERT_TRUE(matrixData.empty());
}

TEST(AlbaMatrixTest, AlbaMatrixCanBeCreatedWithSize) {
    AlbaMatrix<int> const matrix(2, 3);

    EXPECT_EQ(2U, matrix.getNumberOfColumns());
    EXPECT_EQ(3U, matrix.getNumberOfRows());
    AlbaMatrix<int>::MatrixData const& matrixData(matrix.getMatrixData());
    ASSERT_EQ(6U, matrixData.size());
    EXPECT_EQ(0, matrixData[0]);
    EXPECT_EQ(0, matrixData[1]);
    EXPECT_EQ(0, matrixData[2]);
    EXPECT_EQ(0, matrixData[3]);
    EXPECT_EQ(0, matrixData[4]);
    EXPECT_EQ(0, matrixData[5]);
}

TEST(AlbaMatrixTest, AlbaMatrixCanBeCreatedWithUniquePointers) {
    AlbaMatrix<unique_ptr<int>> const matrix(2, 3);

    EXPECT_EQ(2U, matrix.getNumberOfColumns());
    EXPECT_EQ(3U, matrix.getNumberOfRows());
    AlbaMatrix<unique_ptr<int>>::MatrixData const& matrixData(matrix.getMatrixData());
    ASSERT_EQ(6U, matrixData.size());
    EXPECT_FALSE(matrixData[0]);
    EXPECT_FALSE(matrixData[1]);
    EXPECT_FALSE(matrixData[2]);
    EXPECT_FALSE(matrixData[3]);
    EXPECT_FALSE(matrixData[4]);
    EXPECT_FALSE(matrixData[5]);
}

TEST(AlbaMatrixTest, AlbaMatrixCanBeCreatedWithSizeAndInitialValue) {
    AlbaMatrix<int> const matrix(2, 3, 55);

    EXPECT_EQ(2U, matrix.getNumberOfColumns());
    EXPECT_EQ(3U, matrix.getNumberOfRows());
    AlbaMatrix<int>::MatrixData const& matrixData(matrix.getMatrixData());
    ASSERT_EQ(6U, matrixData.size());
    EXPECT_EQ(55, matrixData[0]);
    EXPECT_EQ(55, matrixData[1]);
    EXPECT_EQ(55, matrixData[2]);
    EXPECT_EQ(55, matrixData[3]);
    EXPECT_EQ(55, matrixData[4]);
    EXPECT_EQ(55, matrixData[5]);
}

TEST(AlbaMatrixTest, AlbaMatrixCanBeCreatedWithMatrixDataWithSameSize) {
    AlbaMatrix<int> const matrix(2, 3, {1, 2, 3, 4, 5, 6});

    EXPECT_EQ(2U, matrix.getNumberOfColumns());
    EXPECT_EQ(3U, matrix.getNumberOfRows());
    AlbaMatrix<int>::MatrixData const& matrixData(matrix.getMatrixData());
    ASSERT_EQ(6U, matrixData.size());
    EXPECT_EQ(1, matrixData[0]);
    EXPECT_EQ(2, matrixData[1]);
    EXPECT_EQ(3, matrixData[2]);
    EXPECT_EQ(4, matrixData[3]);
    EXPECT_EQ(5, matrixData[4]);
    EXPECT_EQ(6, matrixData[5]);
}

TEST(AlbaMatrixTest, AlbaMatrixCanBeCreatedWithMatrixDataWithLesserSize) {
    AlbaMatrix<int> const matrix(2, 3, {1, 2, 3, 4, 5});

    EXPECT_EQ(2U, matrix.getNumberOfColumns());
    EXPECT_EQ(3U, matrix.getNumberOfRows());
    AlbaMatrix<int>::MatrixData const& matrixData(matrix.getMatrixData());
    ASSERT_EQ(6U, matrixData.size());
    EXPECT_EQ(1, matrixData[0]);
    EXPECT_EQ(2, matrixData[1]);
    EXPECT_EQ(3, matrixData[2]);
    EXPECT_EQ(4, matrixData[3]);
    EXPECT_EQ(5, matrixData[4]);
    EXPECT_EQ(0, matrixData[5]);
}

TEST(AlbaMatrixTest, AlbaMatrixCanBeCreatedWithMatrixDataWithGreaterSize) {
    AlbaMatrix<int> const matrix(2, 3, {1, 2, 3, 4, 5, 6, 7});

    EXPECT_EQ(2U, matrix.getNumberOfColumns());
    EXPECT_EQ(3U, matrix.getNumberOfRows());
    AlbaMatrix<int>::MatrixData const& matrixData(matrix.getMatrixData());
    ASSERT_EQ(6U, matrixData.size());
    EXPECT_EQ(1, matrixData[0]);
    EXPECT_EQ(2, matrixData[1]);
    EXPECT_EQ(3, matrixData[2]);
    EXPECT_EQ(4, matrixData[3]);
    EXPECT_EQ(5, matrixData[4]);
    EXPECT_EQ(6, matrixData[5]);
}

TEST(AlbaMatrixTest, GetColumnsWorks) {
    AlbaMatrix<int> const matrix(14, 6);

    EXPECT_EQ(14U, matrix.getNumberOfColumns());
}

TEST(AlbaMatrixTest, GetRowsWorks) {
    AlbaMatrix<int> const matrix(14, 6);

    EXPECT_EQ(6U, matrix.getNumberOfRows());
}

TEST(AlbaMatrixTest, GetNumberOfCellsWorks) {
    AlbaMatrix<int> const matrix(14, 6);

    EXPECT_EQ(84U, matrix.getNumberOfCells());
}

TEST(AlbaMatrixTest, GetMatrixIndexWorks) {
    AlbaMatrix<int> const matrix(14, 6);

    EXPECT_EQ(45U, matrix.getMatrixIndex(3, 3));
    EXPECT_EQ(73U, matrix.getMatrixIndex(3, 5));
    EXPECT_EQ(47U, matrix.getMatrixIndex(5, 3));
    EXPECT_EQ(75U, matrix.getMatrixIndex(5, 5));
}

TEST(AlbaMatrixTest, IsEmptyWorks) {
    AlbaMatrix<int> const emptyMatrix;
    AlbaMatrix<int> const nonEmptyMatrix(14, 6);

    EXPECT_TRUE(emptyMatrix.isEmpty());
    EXPECT_FALSE(nonEmptyMatrix.isEmpty());
}

TEST(AlbaMatrixTest, IsInsideTheMatrixWorks) {
    AlbaMatrix<int> const matrix(14, 6);

    EXPECT_FALSE(matrix.isInside(14, 6));
    EXPECT_FALSE(matrix.isInside(14, 5));
    EXPECT_FALSE(matrix.isInside(13, 6));
    EXPECT_TRUE(matrix.isInside(13, 5));
}

TEST(AlbaMatrixTest, RetrieveColumnWorks) {
    AlbaMatrix<int> const matrix(2, 3, {1, 2, 3, 4, 5, 6});

    AlbaMatrix<int>::MatrixData secondColumn;
    matrix.retrieveColumn(secondColumn, 1);

    ASSERT_EQ(3U, secondColumn.size());
    EXPECT_EQ(2, secondColumn[0]);
    EXPECT_EQ(4, secondColumn[1]);
    EXPECT_EQ(6, secondColumn[2]);
}

TEST(AlbaMatrixTest, RetrieveRowWorks) {
    AlbaMatrix<int> const matrix(2, 3, {1, 2, 3, 4, 5, 6});

    AlbaMatrix<int>::MatrixData secondRow;
    matrix.retrieveRow(secondRow, 1);

    ASSERT_EQ(2U, secondRow.size());
    EXPECT_EQ(3, secondRow[0]);
    EXPECT_EQ(4, secondRow[1]);
}

TEST(AlbaMatrixTest, RetrieveColumnsWorks) {
    AlbaMatrix<int> const matrix(2, 3, {1, 2, 3, 4, 5, 6});

    AlbaMatrix<int>::ListOfMatrixData columns;
    matrix.retrieveColumns(columns);

    ASSERT_EQ(2U, columns.size());
    ASSERT_EQ(3U, columns[0].size());
    EXPECT_EQ(1, columns[0][0]);
    EXPECT_EQ(3, columns[0][1]);
    EXPECT_EQ(5, columns[0][2]);
    ASSERT_EQ(3U, columns[1].size());
    EXPECT_EQ(2, columns[1][0]);
    EXPECT_EQ(4, columns[1][1]);
    EXPECT_EQ(6, columns[1][2]);
}

TEST(AlbaMatrixTest, RetrieveRowsWorks) {
    AlbaMatrix<int> const matrix(2, 3, {1, 2, 3, 4, 5, 6});

    AlbaMatrix<int>::ListOfMatrixData rows;
    matrix.retrieveRows(rows);

    ASSERT_EQ(3U, rows.size());
    ASSERT_EQ(2U, rows[0].size());
    EXPECT_EQ(1, rows[0][0]);
    EXPECT_EQ(2, rows[0][1]);
    ASSERT_EQ(2U, rows[1].size());
    EXPECT_EQ(3, rows[1][0]);
    EXPECT_EQ(4, rows[1][1]);
    ASSERT_EQ(2U, rows[2].size());
    EXPECT_EQ(5, rows[2][0]);
    EXPECT_EQ(6, rows[2][1]);
}

TEST(AlbaMatrixTest, RetrieveXAndYFromIndexWorks) {
    AlbaMatrix<int> const matrix(14, 6);

    size_t xValue{};
    size_t yValue{};
    matrix.retrieveXAndYFromIndex(xValue, yValue, 43);

    EXPECT_EQ(1U, xValue);
    EXPECT_EQ(3U, yValue);
}

TEST(AlbaMatrixTest, IterateAllThroughYAndThenXWorks) {
    AlbaMatrix<int> const matrix(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});

    using PairOfNumbers = pair<int, int>;
    vector<PairOfNumbers> xyPairsToVerify;
    matrix.iterateAllThroughYAndThenX(
        [&](int const xValue, int const yValue) { xyPairsToVerify.emplace_back(xValue, yValue); });

    ASSERT_EQ(9U, xyPairsToVerify.size());
    EXPECT_EQ(PairOfNumbers(0, 0), xyPairsToVerify[0]);
    EXPECT_EQ(PairOfNumbers(1, 0), xyPairsToVerify[1]);
    EXPECT_EQ(PairOfNumbers(2, 0), xyPairsToVerify[2]);
    EXPECT_EQ(PairOfNumbers(0, 1), xyPairsToVerify[3]);
    EXPECT_EQ(PairOfNumbers(1, 1), xyPairsToVerify[4]);
    EXPECT_EQ(PairOfNumbers(2, 1), xyPairsToVerify[5]);
    EXPECT_EQ(PairOfNumbers(0, 2), xyPairsToVerify[6]);
    EXPECT_EQ(PairOfNumbers(1, 2), xyPairsToVerify[7]);
    EXPECT_EQ(PairOfNumbers(2, 2), xyPairsToVerify[8]);
}

TEST(AlbaMatrixTest, IterateThroughYAndThenXWithRangesWorks) {
    AlbaMatrix<int> const matrix(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});
    AlbaMatrix<int>::MatrixIndexRange const xRange(0, 1, 1);
    AlbaMatrix<int>::MatrixIndexRange const yRange(1, 2, 1);

    using PairOfNumbers = pair<int, int>;
    vector<PairOfNumbers> xyPairsToVerify;
    matrix.iterateThroughYAndThenXWithRanges(
        yRange, xRange, [&](int const xValue, int const yValue) { xyPairsToVerify.emplace_back(xValue, yValue); });

    ASSERT_EQ(4U, xyPairsToVerify.size());
    EXPECT_EQ(PairOfNumbers(0, 1), xyPairsToVerify[0]);
    EXPECT_EQ(PairOfNumbers(1, 1), xyPairsToVerify[1]);
    EXPECT_EQ(PairOfNumbers(0, 2), xyPairsToVerify[2]);
    EXPECT_EQ(PairOfNumbers(1, 2), xyPairsToVerify[3]);
}

TEST(AlbaMatrixTest, IterateThroughXAndThenYWithRangesWorks) {
    AlbaMatrix<int> const matrix(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});
    AlbaMatrix<int>::MatrixIndexRange const xRange(0, 1, 1);
    AlbaMatrix<int>::MatrixIndexRange const yRange(1, 2, 1);

    using PairOfNumbers = pair<int, int>;
    vector<PairOfNumbers> xyPairsToVerify;
    matrix.iterateThroughXAndThenYWithRanges(
        xRange, yRange, [&](int const xValue, int const yValue) { xyPairsToVerify.emplace_back(xValue, yValue); });

    ASSERT_EQ(4U, xyPairsToVerify.size());
    EXPECT_EQ(PairOfNumbers(0, 1), xyPairsToVerify[0]);
    EXPECT_EQ(PairOfNumbers(0, 2), xyPairsToVerify[1]);
    EXPECT_EQ(PairOfNumbers(1, 1), xyPairsToVerify[2]);
    EXPECT_EQ(PairOfNumbers(1, 2), xyPairsToVerify[3]);
}

TEST(AlbaMatrixTest, OperatorEqualWorks) {
    AlbaMatrix<int> const matrix1(2, 3, {1, 2, 3, 4, 5, 6});
    AlbaMatrix<int> matrix2(2, 3);
    AlbaMatrix<int> const matrix3(3, 3);
    AlbaMatrix<int> const matrix4(2, 4);
    AlbaMatrix<int> matrix5(2, 3);
    matrix2 = matrix1;
    matrix5.setEntry(1, 1, 2);

    EXPECT_TRUE(matrix1 == matrix1);
    EXPECT_TRUE(matrix1 == matrix2);
    EXPECT_FALSE(matrix1 == matrix3);
    EXPECT_FALSE(matrix1 == matrix4);
    EXPECT_FALSE(matrix1 == matrix5);
}

TEST(AlbaMatrixTest, SetEntryWorksAsValueCanSavedInTheMatrix) {
    AlbaMatrix<int> matrix(2, 3);

    matrix.setEntry(0, 0, 1);
    matrix.setEntry(1, 0, 2);
    matrix.setEntry(0, 1, 3);
    matrix.setEntry(1, 1, 4);
    matrix.setEntry(0, 2, 5);
    matrix.setEntry(1, 2, 6);

    AlbaMatrix<int> const expectedMatrix(2, 3, {1, 2, 3, 4, 5, 6});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaMatrixTest, SetEntriesWorksAsMultipleValuesCanSavedInTheMatrix) {
    AlbaMatrix<int> matrix(2, 3);

    matrix.setEntries({1, 2, 3, 4, 5, 6});

    AlbaMatrix<int> const expectedMatrix(2, 3, {1, 2, 3, 4, 5, 6});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaMatrixTest, SetEntriesWorksAsOverwritesExistingValuesAndDoesNotChangeOtherValues) {
    AlbaMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});

    matrix.setEntries({9, 8, 7});

    AlbaMatrix<int> const expectedMatrix(2, 3, {9, 8, 7, 4, 5, 6});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaMatrixTest, SetColumnWorks) {
    AlbaMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});

    matrix.setColumn(1, {9, 8, 7});

    AlbaMatrix<int> const expectedMatrix(2, 3, {1, 9, 3, 8, 5, 7});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaMatrixTest, SetRowWorks) {
    AlbaMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});

    matrix.setRow(1, {9, 8});

    AlbaMatrix<int> const expectedMatrix(2, 3, {1, 2, 9, 8, 5, 6});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaMatrixTest, ClearAndResizeWorks) {
    AlbaMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});

    matrix.clearAndResize(3, 2);

    AlbaMatrix<int> const expectedMatrix(3, 2, {0, 0, 0, 0, 0, 0});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaMatrixTest, ClearAndResizeWorksWithInitialValue) {
    AlbaMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});

    matrix.clearAndResize(3, 2, 55);

    AlbaMatrix<int> const expectedMatrix(3, 2, {55, 55, 55, 55, 55, 55});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaMatrixTest, NegateWorks) {
    AlbaMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});

    matrix.negate();

    AlbaMatrix<int> const expectedMatrix(2, 3, {-1, -2, -3, -4, -5, -6});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaMatrixTest, TransposeWorks) {
    AlbaMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});

    matrix.transpose();

    AlbaMatrix<int> const expectedMatrix(3, 2, {1, 3, 5, 2, 4, 6});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaMatrixTest, InvertWorks) {
    AlbaMatrix<double> matrix(3, 3, {1.0, 1.0, 1.0, 0.0, 2.0, 3.0, 5.0, 5.0, 1.0});

    matrix.invert();

    AlbaMatrix<double> const expectedMatrix(3, 3, {1.625, -0.5, -0.125, -1.875, 0.5, 0.375, 1.25, 0.0, -0.25});
    EXPECT_EQ(expectedMatrix, matrix);
}

}  // namespace alba::matrix
