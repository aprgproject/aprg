#pragma once

#include <Algorithm/Graph/Utilities/LaplaceanMatrix.hpp>
#include <Common/Math/Matrix/Utilities/Determinant.hpp>

namespace alba::algorithm {

template <typename Vertex>
class CountSpanningTreesUsingKirchhoffTheorem {
public:
    // Kirchhoff’s theorem provides a way to calculate the number of spanning trees of a graph as a determinant of a
    // special matrix.
    using RowAndColumnPair = std::pair<int, int>;
    // rule of five or six
    CountSpanningTreesUsingKirchhoffTheorem() = delete;
    ~CountSpanningTreesUsingKirchhoffTheorem() = delete;
    CountSpanningTreesUsingKirchhoffTheorem(CountSpanningTreesUsingKirchhoffTheorem const&) = delete;
    CountSpanningTreesUsingKirchhoffTheorem(CountSpanningTreesUsingKirchhoffTheorem&&) noexcept = delete;
    CountSpanningTreesUsingKirchhoffTheorem& operator=(CountSpanningTreesUsingKirchhoffTheorem const&) = delete;
    CountSpanningTreesUsingKirchhoffTheorem& operator=(CountSpanningTreesUsingKirchhoffTheorem&&) noexcept = delete;

    template <int MAX_VERTEX_VALUE>
    static int getCount(BaseGraph<Vertex> const& graph) {
        // L is the Laplacean matrix.
        // It can be shown that the number of spanning trees equals the determinant of a matrix that is obtained
        // when we remove any row and any column from L.
        // The determinant is always the same, regardless of which row and column we remove from L.
        // Note that Cayley’s formula is a special case of Kirchhoff’s theorem, because in a complete graph of n nodes.
        LaplaceanMatrix const laplaceanMatrix(createLaplaceanMatrix<Vertex, MAX_VERTEX_VALUE>(graph));
        RowAndColumnPair const rowAndColumnPair(getBestRowAndColumnPairToRemove(laplaceanMatrix));
        LaplaceanMatrix const reducedMatrix(matrix::getMatrixWithOneColumnAndOneRowRemoved(
            laplaceanMatrix, rowAndColumnPair.first, rowAndColumnPair.second));
        return matrix::getDeterminant(reducedMatrix);
    }

private:
    static RowAndColumnPair getBestRowAndColumnPairToRemove(LaplaceanMatrix const& laplaceanMatrix) {
        LaplaceanMatrix::ListOfMatrixData columns;
        LaplaceanMatrix::ListOfMatrixData rows;
        laplaceanMatrix.retrieveColumns(columns);
        laplaceanMatrix.retrieveRows(rows);

        return RowAndColumnPair{
            matrix::getIndexWithHighestNumberOfNonZeros(columns), matrix::getIndexWithHighestNumberOfNonZeros(rows)};
    }
};

}  // namespace alba::algorithm
