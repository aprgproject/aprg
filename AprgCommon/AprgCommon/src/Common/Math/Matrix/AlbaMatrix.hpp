#pragma once

#include <Common/Container/AlbaValueRange.hpp>
#include <Common/Math/Helpers/DivisibilityHelpers.hpp>
#include <Common/Math/Matrix/AlbaMatrixDataTypes.hpp>
#include <Common/Math/Matrix/Utilities/AlbaMatrixUtilities.hpp>
#include <Common/Math/Matrix/Utilities/GaussJordanReduction.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <Common/Types/AlbaTypeHelper.hpp>
#include <Common/User/DisplayTable.hpp>

#include <algorithm>
#include <cassert>
#include <functional>
#include <sstream>

namespace alba::matrix {

// constexpr functions:
template <typename DataType>
constexpr AlbaMatrixData<DataType> getDefaultMatrix(size_t const numberOfColumns, size_t const numberOfRows) {
    if constexpr (typeHelper::isArithmeticType<DataType>()) {
        // if arithmetic type, initialize it to zero
        return AlbaMatrixData<DataType>(numberOfColumns * numberOfRows, DataType{});
    } else {
        // if non arithmetic type, default construct it
        return AlbaMatrixData<DataType>(numberOfColumns * numberOfRows);
    }
}

template <typename DataType>
class AlbaMatrix {
public:
    using MatrixData = AlbaMatrixData<DataType>;
    using ListOfMatrixData = ListOfAlbaMatrixData<DataType>;
    using LoopFunction = std::function<void(size_t const xPosition, size_t const yPosition)>;

    using LoopWithValueFunction =
        std::function<void(size_t const xPosition, size_t const yPosition, DataType const& value)>;

    using MatrixIndexRange = AlbaValueRange<size_t>;
    // Do we have to make rows and columns as template parameter?
    // No, its better to have this on runtime because matrix can have different dimensions on applications.
    AlbaMatrix() : m_numberOfColumns(0), m_numberOfRows(0) {}

    AlbaMatrix(size_t const numberOfColumns, size_t const numberOfRows)
        : m_numberOfColumns(numberOfColumns),
          m_numberOfRows(numberOfRows),
          m_matrixData(getDefaultMatrix<DataType>(numberOfColumns, numberOfRows)) {}

    AlbaMatrix(size_t const numberOfColumns, size_t const numberOfRows, DataType const& initialValue)
        : m_numberOfColumns(numberOfColumns),
          m_numberOfRows(numberOfRows),
          m_matrixData(numberOfColumns * numberOfRows, initialValue) {}

    AlbaMatrix(size_t const numberOfColumns, size_t const numberOfRows, MatrixData const& matrixData)
        : m_numberOfColumns(numberOfColumns),
          m_numberOfRows(numberOfRows),
          m_matrixData(
              matrixData.cbegin(),
              matrixData.cbegin() + std::min(static_cast<size_t>(matrixData.size()), numberOfColumns * numberOfRows)) {
        fillRemainingEntriesToZeroIfNeeded(numberOfColumns, numberOfRows);
        m_matrixData.shrink_to_fit();
    }

    AlbaMatrix operator+(AlbaMatrix const& secondMatrix) const {
        assert(
            (m_numberOfColumns == secondMatrix.m_numberOfColumns) && (m_numberOfRows == secondMatrix.m_numberOfRows));
        return doBinaryOperationWithSameDimensions(
            *this, secondMatrix, BinaryFunction<DataType>(std::plus<DataType>()));
    }

    AlbaMatrix operator-(AlbaMatrix const& secondMatrix) const {
        assert(
            (m_numberOfColumns == secondMatrix.m_numberOfColumns) && (m_numberOfRows == secondMatrix.m_numberOfRows));
        return doBinaryOperationWithSameDimensions(
            *this, secondMatrix, BinaryFunction<DataType>(std::minus<DataType>()));
    }

    AlbaMatrix operator*(DataType const& scalarMultiplier) const {
        // scalar multiplication
        UnaryFunction<DataType> const scalarMultiplication = [&scalarMultiplier](DataType const& value) {
            return scalarMultiplier * value;
        };
        return doUnaryOperation(*this, scalarMultiplication);
    }

    AlbaMatrix operator*(AlbaMatrix const& secondMatrix) const {
        // matrix multiplication
        return multiplyMatrices(*this, secondMatrix);
    }

    AlbaMatrix operator^(DataType const& scalarExponent) const {
        // scalar raise to power
        return getMatrixRaiseToScalarPower(*this, scalarExponent);
    }

    // rule of zero
    bool operator==(AlbaMatrix const& secondMatrix) const {
        bool isEqual(true);
        if (m_numberOfColumns != secondMatrix.m_numberOfColumns || m_numberOfRows != secondMatrix.m_numberOfRows) {
            isEqual = false;
        } else if (m_matrixData != secondMatrix.m_matrixData) {
            isEqual = std::equal(
                m_matrixData.cbegin(), m_matrixData.cend(), secondMatrix.m_matrixData.cbegin(),
                secondMatrix.m_matrixData.cend(), [](DataType const& first, DataType const& second) {
                    return isEqualForMathMatrixDataType(first, second);
                });
        }
        return isEqual;
    }

    bool operator!=(AlbaMatrix const& secondMatrix) const { return !operator==(secondMatrix); }

    AlbaMatrix& operator+=(AlbaMatrix const& secondMatrix) {
        doBinaryAssignmentOperationWithSameDimensions(
            *this, secondMatrix, BinaryFunction<DataType>(std::plus<DataType>()));
        return *this;
    }

    AlbaMatrix& operator-=(AlbaMatrix const& secondMatrix) {
        doBinaryAssignmentOperationWithSameDimensions(
            *this, secondMatrix, BinaryFunction<DataType>(std::minus<DataType>()));
        return *this;
    }

    AlbaMatrix& operator*=(DataType const& scalarMultiplier) {
        UnaryFunction<DataType> const scalarMultiplication = [&scalarMultiplier](DataType const& value) {
            return scalarMultiplier * value;
        };
        doUnaryAssignmentOperation(*this, scalarMultiplication);
        return *this;
    }

    AlbaMatrix& operator*=(AlbaMatrix const& secondMatrix) {
        AlbaMatrix& self(*this);
        self = multiplyMatrices(*this, secondMatrix);
        return self;
    }

    [[nodiscard]] DataType getEntry(size_t const xPosition, size_t const yPosition) const {
        assert(isInside(xPosition, yPosition));
        return m_matrixData[getMatrixIndex(xPosition, yPosition)];
    }

    [[nodiscard]] DataType const& getEntryConstReference(size_t const xPosition, size_t const yPosition) const {
        assert(isInside(xPosition, yPosition));
        return m_matrixData[getMatrixIndex(xPosition, yPosition)];
    }

    [[nodiscard]] MatrixData const& getMatrixData() const { return m_matrixData; }
    [[nodiscard]] size_t getNumberOfColumns() const { return m_numberOfColumns; }
    [[nodiscard]] size_t getNumberOfRows() const { return m_numberOfRows; }
    [[nodiscard]] size_t getNumberOfCells() const { return m_numberOfColumns * m_numberOfRows; }

    [[nodiscard]] size_t getMatrixIndex(size_t const xPosition, size_t const yPosition) const {
        return getMatrixIndex(xPosition, yPosition, m_numberOfColumns);
    }

    [[nodiscard]] bool isEmpty() const { return m_matrixData.empty(); }

    [[nodiscard]] bool isInside(size_t const xPosition, size_t const yPosition) const {
        return xPosition < m_numberOfColumns && yPosition < m_numberOfRows;
    }

    void retrieveColumn(MatrixData& column, size_t const xPosition) const {
        column.reserve(m_numberOfRows);
        for (size_t yPosition = 0; yPosition < m_numberOfRows; ++yPosition) {
            column.emplace_back(getEntry(xPosition, yPosition));
        }
    }

    void retrieveRow(MatrixData& row, size_t const yPosition) const {
        row.reserve(m_numberOfColumns);
        for (size_t xPosition = 0; xPosition < m_numberOfColumns; ++xPosition) {
            row.emplace_back(getEntry(xPosition, yPosition));
        }
    }

    void retrieveColumns(ListOfMatrixData& columns) const {
        for (size_t xPosition = 0; xPosition < m_numberOfColumns; ++xPosition) {
            columns.emplace_back();
            retrieveColumn(columns.back(), xPosition);
        }
    }

    void retrieveRows(ListOfMatrixData& rows) const {
        for (size_t yPosition = 0; yPosition < m_numberOfRows; ++yPosition) {
            rows.emplace_back();
            retrieveRow(rows.back(), yPosition);
        }
    }

    void retrieveXAndYFromIndex(size_t& xPosition, size_t& yPosition, size_t const index) const {
        xPosition = index % m_numberOfColumns;
        yPosition = index / m_numberOfColumns;
    }

    void iterateAllThroughYAndThenX(LoopFunction const& loopFunction) const {
        for (size_t yPosition = 0; yPosition < m_numberOfRows; ++yPosition) {
            for (size_t xPosition = 0; xPosition < m_numberOfColumns; ++xPosition) {
                loopFunction(xPosition, yPosition);
            }
        }
    }

    void iterateThroughYAndThenXWithRanges(
        MatrixIndexRange const& yRange, MatrixIndexRange const& xRange, LoopFunction const& loopFunction) const {
        yRange.traverse(
            [&](size_t const yValue) { xRange.traverse([&](size_t const xValue) { loopFunction(xValue, yValue); }); });
    }

    void iterateThroughXAndThenYWithRanges(
        MatrixIndexRange const& xRange, MatrixIndexRange const& yRange, LoopFunction const& loopFunction) const {
        xRange.traverse(
            [&](size_t const xValue) { yRange.traverse([&](size_t const yValue) { loopFunction(xValue, yValue); }); });
    }

    void setEntry(size_t const xPosition, size_t const yPosition, DataType const& value) {
        assert(isInside(xPosition, yPosition));
        m_matrixData[getMatrixIndex(xPosition, yPosition)] = value;
    }

    void setEntries(MatrixData const& dataSampleValues) {
        size_t const limit = std::min(m_matrixData.size(), dataSampleValues.size());
        std::copy(begin(dataSampleValues), begin(dataSampleValues) + limit, begin(m_matrixData));
    }

    void setColumn(size_t const columnIndex, MatrixData const& dataSampleValues) {
        size_t const limit = std::min(m_numberOfRows, static_cast<size_t>(dataSampleValues.size()));
        for (size_t yPosition = 0; yPosition < limit; ++yPosition) {
            setEntry(columnIndex, yPosition, dataSampleValues[yPosition]);
        }
    }

    void setRow(size_t const rowIndex, MatrixData const& dataSampleValues) {
        size_t const limit = std::min(m_numberOfColumns, static_cast<size_t>(dataSampleValues.size()));
        for (size_t xPosition = 0; xPosition < limit; ++xPosition) {
            setEntry(xPosition, rowIndex, dataSampleValues[xPosition]);
        }
    }

    void clearAndResize(size_t const numberOfColumns, size_t const numberOfRows, DataType const initialValue = {}) {
        m_numberOfColumns = numberOfColumns;
        m_numberOfRows = numberOfRows;
        m_matrixData.clear();
        m_matrixData.resize(numberOfColumns * numberOfRows, initialValue);
        m_matrixData.shrink_to_fit();
    }

    void negate() {
        for_each(m_matrixData.begin(), m_matrixData.end(), [&](DataType& value) { value *= -1; });
    }

    void transpose() {
        size_t oldColumns(m_numberOfColumns);
        size_t const oldRows(m_numberOfRows);
        MatrixData oldMatrixData(m_matrixData);
        clearAndResize(oldRows, oldColumns);
        MatrixIndexRange const yRange(0, oldRows - 1, 1);
        MatrixIndexRange const xRange(0, oldColumns - 1, 1);
        iterateThroughYAndThenXWithRanges(yRange, xRange, [&](size_t const xPosition, size_t const yPosition) {
            // NOLINTNEXTLINE(readability-suspicious-call-argument)
            m_matrixData[getMatrixIndex(yPosition, xPosition)] =
                oldMatrixData[getMatrixIndex(xPosition, yPosition, oldColumns)];
        });
    }

    void invert() {
        // Another formula:
        // Inverse of matrix at[i, j] = cofactor at[j,i] / determinant(matrix)
        // But this is costly because of determinant.
        assert(m_numberOfColumns == m_numberOfRows);
        size_t newColumns = m_numberOfColumns * 2;
        AlbaMatrix tempMatrix(newColumns, m_numberOfRows);
        iterateAllThroughYAndThenX([&](size_t const xPosition, size_t const yPosition) {
            tempMatrix.m_matrixData[getMatrixIndex(xPosition, yPosition, newColumns)] = getEntry(xPosition, yPosition);
        });
        size_t const diagonalLimit = std::min(m_numberOfColumns, m_numberOfRows);
        for (size_t diagonalCount = 0; diagonalCount < diagonalLimit; ++diagonalCount) {
            tempMatrix.m_matrixData[getMatrixIndex(m_numberOfColumns + diagonalCount, diagonalCount, newColumns)] = 1;
        }
        transformToReducedEchelonFormUsingGaussJordanReduction(tempMatrix);
        iterateAllThroughYAndThenX([&](size_t const xPosition, size_t const yPosition) {
            m_matrixData[getMatrixIndex(xPosition, yPosition)] =
                tempMatrix.m_matrixData[getMatrixIndex(m_numberOfColumns + xPosition, yPosition, newColumns)];
        });
    }

    DataType& getEntryReference(size_t const xPosition, size_t const yPosition) {
        assert(isInside(xPosition, yPosition));
        return m_matrixData[getMatrixIndex(xPosition, yPosition)];
    }

    // Use getMatrixDataReference() only if needed
    MatrixData& getMatrixDataReference() { return m_matrixData; }

private:
    [[nodiscard]] size_t getMatrixIndex(
        size_t const xPosition, size_t const yPosition, size_t const numberOfColumns) const {
        return (yPosition * numberOfColumns) + xPosition;
    }

    void fillRemainingEntriesToZeroIfNeeded(size_t const numberOfColumns, size_t const numberOfRows) {
        size_t const targetSize = numberOfColumns * numberOfRows;
        if (m_matrixData.size() != targetSize) {
            size_t const originalSize = m_matrixData.size();
            m_matrixData.resize(targetSize);
            std::fill(begin(m_matrixData) + originalSize, end(m_matrixData), DataType{});
        }
    }

    friend std::ostream& operator<<(std::ostream& out, AlbaMatrix const& matrix) {
        DisplayTable table;
        table.setBorders("-", "|");
        for (size_t yPosition = 0; yPosition < matrix.m_numberOfRows; ++yPosition) {
            table.addRow();
            for (size_t xPosition = 0; xPosition < matrix.m_numberOfColumns; ++xPosition) {
                table.getLastRow().addCell(
                    alba::stringHelper::convertToString(matrix.getEntryConstReference(xPosition, yPosition)));
            }
        }

        out << "Matrix output:\n" << table;
        return out;
    }

    size_t m_numberOfColumns;
    size_t m_numberOfRows;
    MatrixData m_matrixData;
};

}  // namespace alba::matrix
