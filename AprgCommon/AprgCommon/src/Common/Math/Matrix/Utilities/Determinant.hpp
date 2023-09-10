#pragma once

#include "DeterminantHeaders.hpp"  // needs to be first
#include <Common/Math/Helpers/DivisibilityHelpers.hpp>
#include <Common/Math/Matrix/AlbaMatrix.hpp>

namespace alba::matrix {

template <typename DataType>
size_t getIndexWithHighestNumberOfZeros(ListOfAlbaMatrixData<DataType> const& rowsOrColumns) {
    BoolUnaryFunction<DataType> const equalCondition = [](DataType const& entry) {
        return isEqualForMathMatrixDataType(entry, DataType{});
    };
    return getIndexWithHighestSatisfiedCount(rowsOrColumns, equalCondition);
}

template <typename DataType>
size_t getIndexWithHighestNumberOfNonZeros(ListOfAlbaMatrixData<DataType> const& rowsOrColumns) {
    BoolUnaryFunction<DataType> const nonEqualCondition = [](DataType const& entry) {
        return !isEqualForMathMatrixDataType(entry, DataType{});
    };
    return getIndexWithHighestSatisfiedCount(rowsOrColumns, nonEqualCondition);
}

template <typename DataType>
DataType getDeterminant(AlbaMatrix<DataType> const& matrix) {
    size_t const numberOfRows(matrix.getNumberOfRows());
    size_t const numberOfColumns(matrix.getNumberOfColumns());
    assert(numberOfRows == numberOfColumns);
    DataType determinant{};
    if (numberOfColumns == 1) {
        determinant = matrix.getEntry(0, 0);
    } else if (numberOfColumns == 2) {
        determinant = matrix.getEntry(0, 0) * matrix.getEntry(1, 1) - matrix.getEntry(0, 1) * matrix.getEntry(1, 0);
    } else {
        determinant = getDeterminantWhenSideIsMoreThan2(matrix);
    }
    return determinant;
}

template <typename DataType>
DataType getValueUsingCramerRule(
    AlbaMatrix<DataType> const& matrix, size_t const columnIndex, AlbaMatrixData<DataType> const& newColumnValues) {
    size_t const numberOfRows(matrix.getNumberOfRows());
    size_t const numberOfColumns(matrix.getNumberOfColumns());
    assert(numberOfRows == numberOfColumns);
    AlbaMatrix<DataType> matrixWithNewColumn(matrix);
    matrixWithNewColumn.setColumn(columnIndex, newColumnValues);
    return getDeterminant(matrixWithNewColumn) / getDeterminant(matrix);
}

template <typename DataType>
DataType getValueFromCoFactorExpansion(
    AlbaMatrix<DataType> const& matrix, size_t const xPosition, size_t const yPosition) {
    DataType value{};
    DataType entry = matrix.getEntry(xPosition, yPosition);
    if (!isEqualForMathMatrixDataType(entry, 0)) {
        int const sign = mathHelper::isEven(xPosition + yPosition) ? 1 : -1;
        DataType subDeterminant = getDeterminant(getMatrixWithOneColumnAndOneRowRemoved(matrix, xPosition, yPosition));
        value = entry * subDeterminant * sign;
    }
    return value;
}

template <typename DataType>
DataType getDeterminantWhenSideIsMoreThan2(AlbaMatrix<DataType> const& matrix) {
    DataType determinant{};

    typename AlbaMatrix<DataType>::ListOfMatrixData rowsAndColumns;
    matrix.retrieveRows(rowsAndColumns);
    matrix.retrieveColumns(rowsAndColumns);

    size_t const numberOfRows(matrix.getNumberOfRows());
    size_t const numberOfColumns(matrix.getNumberOfColumns());
    size_t const bestIndex = getIndexWithHighestNumberOfZeros(rowsAndColumns);
    if (bestIndex < numberOfRows) {
        size_t const yPosition = bestIndex;
        for (size_t xPosition = 0; xPosition < numberOfColumns; ++xPosition) {
            determinant += getValueFromCoFactorExpansion(matrix, xPosition, yPosition);
        }
    } else {
        size_t const xPosition = bestIndex - numberOfRows;
        for (size_t yPosition = 0; yPosition < numberOfRows; ++yPosition) {
            determinant += getValueFromCoFactorExpansion(matrix, xPosition, yPosition);
        }
    }
    return determinant;
}

template <typename DataType>
AlbaMatrix<DataType> getMatrixWithOneColumnAndOneRowRemoved(
    AlbaMatrix<DataType> const& matrix, size_t const columnIndex, size_t const rowIndex) {
    size_t const numberOfRows(matrix.getNumberOfRows());
    size_t const numberOfColumns(matrix.getNumberOfColumns());
    assert((columnIndex < numberOfColumns) && (rowIndex < numberOfRows));
    AlbaMatrix<DataType> result(numberOfColumns - 1, numberOfRows - 1);
    matrix.iterateAllThroughYAndThenX([&](size_t const xPosition, size_t const yPosition) {
        if (columnIndex != xPosition && rowIndex != yPosition) {
            size_t const newX = (xPosition >= columnIndex) ? xPosition - 1 : xPosition;
            size_t const newY = (yPosition >= rowIndex) ? yPosition - 1 : yPosition;
            result.setEntry(newX, newY, matrix.getEntry(xPosition, yPosition));
        }
    });
    return result;
}

}  // namespace alba::matrix
