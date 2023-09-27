#pragma once

#include <Common/Math/Matrix/Utilities/AlbaMatrixUtilities.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <Common/User/DisplayTable.hpp>

#include <cassert>
#include <functional>
#include <set>
#include <sstream>
#include <tuple>
#include <unordered_map>
#include <vector>

namespace alba::matrix {

template <typename DataType>
class AlbaSparseMatrix {
public:
    using MatrixData = std::unordered_map<size_t, DataType>;
    using ListedMatrixData = std::vector<DataType>;
    using UniqueIndexes = std::set<size_t>;
    using UnaryFunction = std::function<DataType(DataType const&)>;
    using BinaryFunction = std::function<DataType(DataType const&, DataType const&)>;
    AlbaSparseMatrix() = default;

    AlbaSparseMatrix(size_t const numberOfColumns, size_t const numberOfRows)
        : m_numberOfColumns(numberOfColumns), m_numberOfRows(numberOfRows), m_matrixData() {}

    AlbaSparseMatrix(size_t const numberOfColumns, size_t const numberOfRows, ListedMatrixData const& matrixData)
        : m_numberOfColumns(numberOfColumns), m_numberOfRows(numberOfRows), m_matrixData() {
        setEntries(matrixData);
    }

    AlbaSparseMatrix operator+(AlbaSparseMatrix const& secondMatrix) const {
        assert(
            (m_numberOfColumns == secondMatrix.m_numberOfColumns) && (m_numberOfRows == secondMatrix.m_numberOfRows));
        return doBinaryOperation(*this, secondMatrix, BinaryFunction(std::plus<DataType>()));
    }

    AlbaSparseMatrix operator-(AlbaSparseMatrix const& secondMatrix) const {
        assert(
            (m_numberOfColumns == secondMatrix.m_numberOfColumns) && (m_numberOfRows == secondMatrix.m_numberOfRows));
        return doBinaryOperation(*this, secondMatrix, BinaryFunction(std::minus<DataType>()));
    }

    AlbaSparseMatrix operator*(DataType const& scalarMultiplier) const {  // scalar multiplication
        return doUnaryOperation(*this, [&scalarMultiplier](DataType const& data) { return scalarMultiplier * data; });
    }

    AlbaSparseMatrix operator*(AlbaSparseMatrix const& secondMatrix) const {  // matrix multiplication
        assert(m_numberOfColumns == secondMatrix.m_numberOfRows);
        size_t const size(std::min(m_numberOfColumns, secondMatrix.m_numberOfRows));
        AlbaSparseMatrix result(m_numberOfRows, secondMatrix.m_numberOfColumns);
        for (size_t yPosition = 0; yPosition < m_numberOfRows; ++yPosition) {
            for (size_t xPosition = 0; xPosition < secondMatrix.m_numberOfColumns; ++xPosition) {
                DataType cellValue{};
                for (size_t kPosition = 0; kPosition < size; ++kPosition) {
                    cellValue += getEntry(kPosition, yPosition) * secondMatrix.getEntry(xPosition, kPosition);
                }
                result.setEntry(xPosition, yPosition, cellValue);
            }
        }
        return result;
    }

    // rule of zero
    bool operator==(AlbaSparseMatrix const& secondMatrix) const {
        bool isEqual(true);
        if (m_numberOfColumns != secondMatrix.m_numberOfColumns || m_numberOfRows != secondMatrix.m_numberOfRows) {
            isEqual = false;
        } else if (m_matrixData != secondMatrix.m_matrixData) {
            UniqueIndexes const allIndexes(getAllIndexes(m_matrixData, secondMatrix.m_matrixData));
            for (size_t const index : allIndexes) {
                if (getEntry(index) != secondMatrix.getEntry(index)) {
                    isEqual = false;
                    break;
                }
            }
        }
        return isEqual;
    }

    bool operator!=(AlbaSparseMatrix const& secondMatrix) const { return !operator==(secondMatrix); }

    [[nodiscard]] DataType getEntry(size_t const xPosition, size_t const yPosition) const {
        assert((xPosition < m_numberOfColumns) && (yPosition < m_numberOfRows));
        return getEntry(getMatrixIndex(xPosition, yPosition));
    }

    [[nodiscard]] MatrixData const& getMatrixData() const { return m_matrixData; }
    [[nodiscard]] size_t getNumberOfColumns() const { return m_numberOfColumns; }
    [[nodiscard]] size_t getNumberOfRows() const { return m_numberOfRows; }

    [[nodiscard]] size_t getMatrixIndex(size_t const xPosition, size_t const yPosition) const {
        return getMatrixIndex(xPosition, yPosition, m_numberOfColumns);
    }

    void setEntry(size_t const xPosition, size_t const yPosition, DataType const& value) {
        assert((xPosition < m_numberOfColumns) && (yPosition < m_numberOfRows));
        m_matrixData[getMatrixIndex(xPosition, yPosition)] = value;
    }

    void setEntries(ListedMatrixData const& dataSampleValues) {
        size_t const limit = std::min<size_t>(dataSampleValues.size(), m_numberOfColumns * m_numberOfRows);
        for (size_t i = 0; i < limit; ++i) {
            if (!isEqualForMathMatrixDataType(dataSampleValues[i], static_cast<DataType>(0))) {
                m_matrixData[i] = dataSampleValues[i];
            }
        }
    }

    void clearAndResize(size_t const numberOfColumns, size_t const numberOfRows) {
        m_numberOfColumns = numberOfColumns;
        m_numberOfRows = numberOfRows;
        m_matrixData.clear();
    }

    void negate() {
        // cppcheck-suppress unusedVariable
        for (auto& [_, value] : m_matrixData) {
            value *= -1;
        }
    }

    void transpose() {
        MatrixData newMatrixData;
        for (auto const& [index, value] : m_matrixData) {
            newMatrixData.try_emplace(getTranposeIndex(index), value);
        }
        clearAndResize(m_numberOfRows, m_numberOfColumns);
        m_matrixData = newMatrixData;
    }

    DataType& getEntryReference(size_t const xPosition, size_t const yPosition) {
        assert((xPosition < m_numberOfColumns) && (yPosition < m_numberOfRows));
        return m_matrixData[getMatrixIndex(xPosition, yPosition)];
    }

private:
    [[nodiscard]] AlbaSparseMatrix doUnaryOperation(
        AlbaSparseMatrix const& inputMatrix, UnaryFunction const& unaryFunction) const {
        AlbaSparseMatrix resultMatrix(inputMatrix.getNumberOfColumns(), inputMatrix.getNumberOfRows());
        for (auto const& [index, value] : m_matrixData) {
            resultMatrix.m_matrixData[index] = unaryFunction(value);
        }
        return resultMatrix;
    }

    [[nodiscard]] AlbaSparseMatrix doBinaryOperation(
        AlbaSparseMatrix const& firstMatrix, AlbaSparseMatrix const& secondMatrix,
        BinaryFunction const& binaryFunction) const {
        assert(
            (firstMatrix.getNumberOfColumns() == secondMatrix.getNumberOfColumns()) &&
            (firstMatrix.getNumberOfRows() == secondMatrix.getNumberOfRows()));
        AlbaSparseMatrix resultMatrix(firstMatrix.getNumberOfColumns(), firstMatrix.getNumberOfRows());
        UniqueIndexes const allIndexes(getAllIndexes(m_matrixData, secondMatrix.m_matrixData));
        for (size_t const index : allIndexes) {
            resultMatrix.m_matrixData[index] =
                binaryFunction(firstMatrix.getEntry(index), secondMatrix.getEntry(index));
        }
        return resultMatrix;
    }

    [[nodiscard]] DataType getEntry(size_t const index) const {
        DataType result{};
        auto matrixIt = m_matrixData.find(index);
        if (matrixIt != m_matrixData.cend()) {
            result = matrixIt->second;
        }
        return result;
    }

    [[nodiscard]] UniqueIndexes getAllIndexes(MatrixData const& data1, MatrixData const& data2) const {
        UniqueIndexes result;
        for (auto const& [index, value] : data1) {
            result.emplace(index);
        }
        for (auto const& [index, value] : data2) {
            result.emplace(index);
        }
        return result;
    }

    [[nodiscard]] size_t getMatrixIndex(
        size_t const xPosition, size_t const yPosition, size_t const numberOfColumns) const {
        return (yPosition * numberOfColumns) + xPosition;
    }

    [[nodiscard]] size_t getTranposeIndex(size_t const index) const {
        return getMatrixIndex(index / m_numberOfColumns, index % m_numberOfColumns, m_numberOfRows);
    }

    friend std::ostream& operator<<(std::ostream& out, AlbaSparseMatrix const& matrix) {
        DisplayTable table;
        table.setBorders("-", "|");
        for (size_t yPosition = 0; yPosition < matrix.m_numberOfRows; ++yPosition) {
            table.addRow();
            for (size_t xPosition = 0; xPosition < matrix.m_numberOfColumns; ++xPosition) {
                table.getLastRow().addCell(alba::stringHelper::convertToString(matrix.getEntry(xPosition, yPosition)));
            }
        }

        out << "Matrix output:\n" << table;
        return out;
    }

    size_t m_numberOfColumns{};
    size_t m_numberOfRows{};
    MatrixData m_matrixData;
};

}  // namespace alba::matrix
