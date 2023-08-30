#pragma once

#include <Algorithm/Graph/PathSearch/BreadthFirstSearch/PathSearchUsingBfsWithDistanceCount.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>
#include <Common/Math/Matrix/AlbaMatrix.hpp>
#include <UniqueProblems/Utilities/PrintUtilities.hpp>

namespace alba {

class NearestEqualCells {
public:
    // This is an example of combining algorithm using "Case processing".

    // Suppose that we are given a two-dimensional grid that contains n cells.
    // Each cell is assigned a letter, and our task is to find two cells with the same letter whose distance is minimum,
    // where the distance between cells (x1, y1) and (x2, y2) is |x1-x2|+|y1-y2|.

    using Value = int;
    using ValueMatrix = matrix::AlbaMatrix<Value>;
    using Coordinate = std::pair<int, int>;
    using CoordinatePair = std::pair<Coordinate, Coordinate>;
    using Coordinates = std::vector<Coordinate>;
    using Graph = algorithm::UndirectedGraphWithListOfEdges<Coordinate>;
    using Bfs = algorithm::PathSearchUsingBfsWithDistanceCount<Coordinate>;

    explicit NearestEqualCells(ValueMatrix const& valueMatrix);

    [[nodiscard]] CoordinatePair getNearestEqualPair(Value const value) const;
    [[nodiscard]] CoordinatePair getNearestEqualPairByCheckingAllPairs(Value const value) const;
    [[nodiscard]] CoordinatePair getNearestEqualPairUsingBfs(Value const value) const;

private:
    void initializeGraph();
    [[nodiscard]] Coordinates getCoordinatesWithThisValue(Value const value) const;
    [[nodiscard]] Coordinate getFirstCoordinateUsingBfs(Value const value) const;
    [[nodiscard]] Coordinate getSecondCoordinateUsingBfs(Value const value, Coordinate const& firstCoordinate) const;
    Coordinate getCoordinateUsingBfs(Value const value, Coordinate const& firstCoordinate, Bfs& bfs) const;
    static int getDistance(Coordinate const& coordinate1, Coordinate const& coordinate2);
    ValueMatrix const& m_valueMatrix;
    Graph m_coordinateGraph;
};

}  // namespace alba
