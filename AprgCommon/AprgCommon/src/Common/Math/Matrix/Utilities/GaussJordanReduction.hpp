#pragma once

#include "GaussJordanReductionHeaders.hpp"  // needs to be first
#include <Common/Math/Matrix/AlbaMatrix.hpp>
#include <Common/Math/Matrix/Utilities/AlbaMatrixUtilities.hpp>

#include <cassert>

namespace alba::matrix {

template <typename DataType>
bool areRowsWithAllZerosInTheBottom(AlbaMatrix<DataType> const& matrix) {
    size_t numberOfRows(matrix.getNumberOfRows());
    size_t numberOfColumns(matrix.getNumberOfColumns());
    bool isRowWithNonZeroEncountered(false);
    for (size_t yPlusOne = numberOfRows; yPlusOne > 0; yPlusOne--) {
        size_t yPosition(yPlusOne - 1);
        bool isRowWithAllZero(true);
        for (size_t xPosition = 0; xPosition < numberOfColumns; xPosition++) {
            if (isRowWithAllZero &&
                !isEqualForMathMatrixDataType(matrix.getEntry(xPosition, yPosition), static_cast<DataType>(0))) {
                isRowWithAllZero = false;
                break;
            }
        }
        if (!isRowWithNonZeroEncountered) {
            isRowWithNonZeroEncountered = !isRowWithAllZero;
        }
        if (isRowWithNonZeroEncountered && isRowWithAllZero) {
            // 1. All rows consisting entirely of zeros, if any, are at the bottom of the matrix.
            return false;
        }
    }
    return true;
}

template <typename DataType>
bool areLeadingEntriesInReducedRowEchelonForm(AlbaMatrix<DataType> const& matrix) {
    size_t numberOfRows(matrix.getNumberOfRows());
    size_t numberOfColumns(matrix.getNumberOfColumns());
    int currentLeadingEntryColumn(-1);
    for (size_t yPosition = 0; yPosition < numberOfRows; yPosition++) {
        for (size_t xPosition = 0; xPosition < numberOfColumns; xPosition++) {
            if (isEqualForMathMatrixDataType(matrix.getEntry(xPosition, yPosition), static_cast<DataType>(0))) {
            } else if (isEqualForMathMatrixDataType(matrix.getEntry(xPosition, yPosition), static_cast<DataType>(1))) {
                if (currentLeadingEntryColumn < static_cast<int>(xPosition)) {
                    for (size_t yZeroCheck = 0; yZeroCheck < numberOfRows; yZeroCheck++) {
                        if (yZeroCheck != yPosition &&
                            !isEqualForMathMatrixDataType(
                                matrix.getEntry(xPosition, yZeroCheck), static_cast<DataType>(0))) {
                            // 4. If a column contains a leading entry of some row, then all other entries in that
                            // column are zero
                            return false;
                        }
                    }
                } else {
                    // 3. If rows i and i+1 are two successive rows that do not consist entirely of zeros, then the
                    // leading entry of row i+1 is to the right of the leading entry of row i.
                    return false;
                }
                currentLeadingEntryColumn = static_cast<int>(xPosition);
                break;
            } else {
                // 2. By reading from left to right, the first nonzero entry in each row that does not consist entirely
                // of zeros is a 1, called the leading entry of its row.
                return false;
            }
        }
    }
    return true;
}

template <typename DataType>
bool isReducedRowEchelonForm(AlbaMatrix<DataType> const& matrix) {
    return areRowsWithAllZerosInTheBottom(matrix) && areLeadingEntriesInReducedRowEchelonForm(matrix);
}

template <typename DataType>
void transformToReducedEchelonFormUsingGaussJordanReduction(AlbaMatrix<DataType>& matrix) {
    size_t numberOfRows(matrix.getNumberOfRows());
    size_t numberOfColumns(matrix.getNumberOfColumns());
    size_t yWithLeadingEntry = 0;
    for (size_t xPosition = 0; xPosition < numberOfColumns; xPosition++) {
        for (size_t yPosition = yWithLeadingEntry; yPosition < numberOfRows; yPosition++) {
            if (!isEqualForMathMatrixDataType(matrix.getEntry(xPosition, yPosition), static_cast<DataType>(0))) {
                interchangeRows(matrix, yPosition, yWithLeadingEntry);
                multiplyValueInRowAndPutProductInAnotherRow(
                    matrix, static_cast<DataType>(1) / matrix.getEntry(xPosition, yWithLeadingEntry), yWithLeadingEntry,
                    yWithLeadingEntry);
                for (size_t yToZero = 0; yToZero < numberOfRows; yToZero++) {
                    if (yToZero != yWithLeadingEntry &&
                        !isEqualForMathMatrixDataType(matrix.getEntry(xPosition, yToZero), static_cast<DataType>(0))) {
                        subtractRowsWithMultiplierPutDifferenceInAnotherRow(
                            matrix, matrix.getEntry(xPosition, yToZero) / matrix.getEntry(xPosition, yWithLeadingEntry),
                            yToZero, yWithLeadingEntry, yToZero);
                    }
                }
                yWithLeadingEntry++;
                break;
            }
        }
    }
}

template <typename DataType>
void multiplyValueInRowAndPutProductInAnotherRow(
    AlbaMatrix<DataType>& matrix, DataType const& multiplierForInput, size_t const yInput, size_t const yOutput) {
    assert((yInput < matrix.getNumberOfRows()) && (yOutput < matrix.getNumberOfRows()));
    traverseWithUnaryOperationForDifferentRows(
        matrix, yInput, yOutput,
        UnaryFunction<DataType>([&](DataType const& input) { return input * multiplierForInput; }));
}

template <typename DataType>
void subtractRowsWithMultiplierPutDifferenceInAnotherRow(
    AlbaMatrix<DataType>& matrix, DataType const& multiplierForInput2, size_t const yInput1, size_t const yInput2,
    size_t const yOutput) {
    assert(
        (yInput1 < matrix.getNumberOfRows()) && (yInput2 < matrix.getNumberOfRows()) &&
        (yOutput < matrix.getNumberOfRows()));
    traverseWithBinaryOperationForDifferentRows(
        matrix, yInput1, yInput2, yOutput,
        BinaryFunction<DataType>(
            [&](DataType const& input1, DataType const& input2) { return input1 - (input2 * multiplierForInput2); }));
}

}  // namespace alba::matrix
