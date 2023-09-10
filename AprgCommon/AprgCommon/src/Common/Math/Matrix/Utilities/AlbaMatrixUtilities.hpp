#pragma once

#include "AlbaMatrixUtilitiesHeaders.hpp"  // needs to be first
#include <Common/Math/Helpers/PrecisionHelpers.hpp>
#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <algorithm>
#include <cassert>

namespace alba::matrix {

template <typename DataType>
bool isEqualForMathMatrixDataType(DataType const& value1, DataType const& value2) {
    if constexpr (typeHelper::isFloatingPointType<DataType>()) {
        return mathHelper::isAlmostEqual(value1, value2);
    }
    return value1 == value2;
}

template <typename DataType>
bool isSquare(AlbaMatrix<DataType> const& matrix) {
    return matrix.getNumberOfRows() == matrix.getNumberOfColumns();
}

template <typename DataType>
bool isZeroMatrix(AlbaMatrix<DataType> const& matrix) {
    auto const& matrixData(matrix.getMatrixData());
    return std::all_of(matrixData.cbegin(), matrixData.cend(), [](DataType const& data) {
        return isEqualForMathMatrixDataType(data, static_cast<DataType>(0));
    });
}

template <typename DataType>
bool isIdentityMatrix(AlbaMatrix<DataType> const& matrix) {
    size_t const numberOfRows(matrix.getNumberOfRows());
    size_t const numberOfColumns(matrix.getNumberOfColumns());
    bool isIdentityMatrix(numberOfRows == numberOfColumns);
    for (size_t yPosition = 0; isIdentityMatrix && yPosition < numberOfRows; ++yPosition) {
        for (size_t xPosition = 0; isIdentityMatrix && xPosition < numberOfColumns; ++xPosition) {
            if (xPosition == yPosition) {
                isIdentityMatrix = isIdentityMatrix && matrix.getEntry(xPosition, yPosition) == 1;
            } else {
                isIdentityMatrix = isIdentityMatrix && matrix.getEntry(xPosition, yPosition) == 0;
            }
        }
    }
    return isIdentityMatrix;
}

template <typename DataType>
bool isSingular(AlbaMatrix<DataType> const& matrix) {
    // means the its non invertible
    // Another method:
    // Matrix is invertible iff determinant is zero
    // But this is costly because of determinant.
    // Code:
    // return getDeterminant(matrix) != 0;
    AlbaMatrix<DataType> inverseOfInverse(matrix);
    inverseOfInverse.invert();
    inverseOfInverse.invert();
    return !(matrix == inverseOfInverse);
}

template <typename DataType>
AlbaMatrix<DataType> getIdentityMatrix(size_t const sideSize) {
    AlbaMatrix<DataType> resultMatrix(sideSize, sideSize);
    for (size_t index = 0; index < sideSize; ++index) {
        resultMatrix.setEntry(index, index, 1);
    }
    return resultMatrix;
}

template <typename DataType>
AlbaMatrix<DataType> doUnaryOperation(
    AlbaMatrix<DataType> const& inputMatrix, UnaryFunction<DataType> const& unaryFunction) {
    AlbaMatrix<DataType> resultMatrix(inputMatrix.getNumberOfColumns(), inputMatrix.getNumberOfRows());
    inputMatrix.iterateAllThroughYAndThenX([&](size_t const xPosition, size_t const yPosition) {
        resultMatrix.setEntry(xPosition, yPosition, unaryFunction(inputMatrix.getEntry(xPosition, yPosition)));
    });
    return resultMatrix;
}

template <typename DataType>
AlbaMatrix<DataType> doBinaryOperationWithSameDimensions(
    AlbaMatrix<DataType> const& firstMatrix, AlbaMatrix<DataType> const& secondMatrix,
    BinaryFunction<DataType> const& binaryFunction) {
    assert(
        (firstMatrix.getNumberOfColumns() == secondMatrix.getNumberOfColumns()) &&
        (firstMatrix.getNumberOfRows() == secondMatrix.getNumberOfRows()));
    AlbaMatrix<DataType> resultMatrix(firstMatrix.getNumberOfColumns(), firstMatrix.getNumberOfRows());
    firstMatrix.iterateAllThroughYAndThenX([&](size_t const xPosition, size_t const yPosition) {
        resultMatrix.setEntry(
            xPosition, yPosition,
            binaryFunction(firstMatrix.getEntry(xPosition, yPosition), secondMatrix.getEntry(xPosition, yPosition)));
    });
    return resultMatrix;
}

template <typename DataType>
void doUnaryAssignmentOperation(AlbaMatrix<DataType>& inputOutputMatrix, UnaryFunction<DataType> const& unaryFunction) {
    inputOutputMatrix.iterateAllThroughYAndThenX([&](size_t const xPosition, size_t const yPosition) {
        inputOutputMatrix.setEntry(
            xPosition, yPosition, unaryFunction(inputOutputMatrix.getEntry(xPosition, yPosition)));
    });
}

template <typename DataType>
void doBinaryAssignmentOperationWithSameDimensions(
    AlbaMatrix<DataType>& firstMatrix, AlbaMatrix<DataType> const& secondMatrix,
    BinaryFunction<DataType> const& binaryFunction) {
    assert(
        (firstMatrix.getNumberOfColumns() == secondMatrix.getNumberOfColumns()) &&
        (firstMatrix.getNumberOfRows() == secondMatrix.getNumberOfRows()));
    firstMatrix.iterateAllThroughYAndThenX([&](size_t const xPosition, size_t const yPosition) {
        firstMatrix.setEntry(
            xPosition, yPosition,
            binaryFunction(firstMatrix.getEntry(xPosition, yPosition), secondMatrix.getEntry(xPosition, yPosition)));
    });
}

template <typename DataType>
AlbaMatrix<DataType> multiplyMatrices(AlbaMatrix<DataType> const& first, AlbaMatrix<DataType> const& second) {
    // Using a straightforward algorithm, we can calculate the product of two nxn matrices in O(n^3) time.
    // There are also more efficient algorithms for matrix multiplication,
    // but they are mostly of theoretical interest and such algorithms are not practical.
    assert(first.getNumberOfColumns() == second.getNumberOfRows());

    AlbaMatrix<DataType> result(second.getNumberOfColumns(), first.getNumberOfRows());
    ListOfAlbaMatrixData<DataType> rowsOfFirstMatrix;
    ListOfAlbaMatrixData<DataType> columnsOfSecondMatrix;
    first.retrieveRows(rowsOfFirstMatrix);
    second.retrieveColumns(columnsOfSecondMatrix);
    size_t yPosition = 0;
    for (AlbaMatrixData<DataType> const& rowOfFirstMatrix : rowsOfFirstMatrix) {
        size_t xPosition = 0;
        for (AlbaMatrixData<DataType> const& columnOfSecondMatrix : columnsOfSecondMatrix) {
            result.setEntry(xPosition, yPosition, multiplyEachItemAndGetSum(rowOfFirstMatrix, columnOfSecondMatrix));
            ++xPosition;
        }
        ++yPosition;
    }
    return result;
}

template <typename DataType>
AlbaMatrix<DataType> getMatrixRaiseToScalarPower(AlbaMatrix<DataType> const& base, size_t const scalarExponent) {
    assert(base.getNumberOfColumns() == base.getNumberOfRows());

    AlbaMatrix<DataType> result(getIdentityMatrix<DataType>(base.getNumberOfColumns()));
    AlbaMatrix<DataType> newBase(base);
    size_t newExponent(scalarExponent);
    while (newExponent > 0) {
        if (mathHelper::isEven(newExponent)) {
            newBase *= newBase;
            newExponent /= 2;
        } else {
            result *= newBase;
            --newExponent;
        }
    }
    return result;
}

template <typename DataType>
void interchangeRows(AlbaMatrix<DataType>& matrix, size_t const yPosition1, size_t const yPosition2) {
    assert((yPosition1 < matrix.getNumberOfRows()) && (yPosition2 < matrix.getNumberOfRows()));
    for (size_t xPosition = 0; xPosition < matrix.getNumberOfColumns(); ++xPosition) {
        std::swap(matrix.getEntryReference(xPosition, yPosition1), matrix.getEntryReference(xPosition, yPosition2));
    }
}

template <typename DataType>
void addTwoRowsAndPutSumInAnotherRow(
    AlbaMatrix<DataType>& matrix, size_t const yInput1, size_t const yInput2, size_t const yOutput) {
    size_t const numberOfRows(matrix.getNumberOfRows());
    assert((yInput1 < numberOfRows) && (yInput2 < numberOfRows) && (yOutput < numberOfRows));
    traverseWithBinaryOperationForDifferentRows(
        matrix, yInput1, yInput2, yOutput, BinaryFunction<DataType>(std::plus<DataType>()));
}

template <typename DataType>
DataType multiplyEachItemAndGetSum(AlbaMatrixData<DataType> const& first, AlbaMatrixData<DataType> const& second) {
    DataType result{};
    size_t const minSize = std::min(first.size(), second.size());
    for (size_t index = 0; index < minSize; ++index) {
        result += first[index] * second[index];
    }
    return result;
}

template <typename DataType>
size_t getIndexWithHighestSatisfiedCount(
    ListOfAlbaMatrixData<DataType> const& rowsOrColumns, BoolUnaryFunction<DataType> const& condition) {
    size_t index = 0;
    size_t bestIndex = 0;
    size_t highestCount = 0;
    for (auto const& rowOrColumn : rowsOrColumns) {
        size_t const count = std::count_if(rowOrColumn.cbegin(), rowOrColumn.cend(), condition);
        if (highestCount < count) {
            highestCount = count;
            bestIndex = index;
        }
        ++index;
    }
    return bestIndex;
}

template <typename DataType>
void traverseWithUnaryOperationForDifferentRows(
    AlbaMatrix<DataType>& matrix, size_t const yInput, size_t const yOutput,
    UnaryFunction<DataType> const& unaryFunction) {
    assert((yInput < matrix.getNumberOfRows()) && (yOutput < matrix.getNumberOfRows()));
    for (size_t xPosition = 0; xPosition < matrix.getNumberOfColumns(); ++xPosition) {
        matrix.setEntry(xPosition, yOutput, unaryFunction(matrix.getEntry(xPosition, yInput)));
    }
}

template <typename DataType>
void traverseWithBinaryOperationForDifferentRows(
    AlbaMatrix<DataType>& matrix, size_t const yInput1, size_t const yInput2, size_t const yOutput,
    BinaryFunction<DataType> const& binaryFunction) {
    assert(
        (yInput1 < matrix.getNumberOfRows()) && (yInput2 < matrix.getNumberOfRows()) &&
        (yOutput < matrix.getNumberOfRows()));
    for (size_t xPosition = 0; xPosition < matrix.getNumberOfColumns(); ++xPosition) {
        matrix.setEntry(
            xPosition, yOutput,
            binaryFunction(matrix.getEntry(xPosition, yInput1), matrix.getEntry(xPosition, yInput2)));
    }
}

}  // namespace alba::matrix
