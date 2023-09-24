#pragma once

#include <Algorithm/Graph/DirectedGraph/BaseDirectedGraph.hpp>
#include <Algorithm/Graph/SuccessorGraph/WalkInSuccessorGraph.hpp>

namespace alba::algorithm {

template <typename Vertex>
class BrentAlgorithmForSuccessorGraphs {
public:
    using BaseDirectedGraphWithVertex = BaseDirectedGraph<Vertex>;
    using Walker = WalkInSuccessorGraph<Vertex>;
    using Path = typename GraphTypes<Vertex>::Path;

    explicit BrentAlgorithmForSuccessorGraphs(BaseDirectedGraphWithVertex const& graph)
        : m_graph(graph), m_walker(graph) {}

    [[nodiscard]] Path getCycle() const { return m_cyclePath; }
    [[nodiscard]] bool hasACycle() const { return m_hasACycle; }

    void reinitializeStartingFrom(Vertex const& startOfGraph) {
        int const cycleLength(getCycleLength(startOfGraph));
        m_hasACycle = cycleLength > 1;  // we dont consider self loops as cycles
        m_cyclePath.clear();
        if (m_hasACycle) {
            saveCycle(getStartOfCycle(startOfGraph, cycleLength), cycleLength);
        }
    }

private:
    [[nodiscard]] bool isAtTheEnd(Vertex const& vertex) const { return m_walker.isAtTheEnd(vertex); }

    void saveCycle(Vertex const& startOfCycle, int const cycleLength) {
        Vertex vertex = startOfCycle;
        for (int i = 0; i < cycleLength; ++i) {
            // based from cycle length, iterate vertex of cycle
            m_cyclePath.emplace_back(vertex);
            vertex = walkOne(vertex);
        }
        m_cyclePath.emplace_back(vertex);  // append last/first vertex to demonstrate a cycle
    }

    Vertex getStartOfCycle(Vertex const& startOfGraph, int const cycleLength) {
        Vertex vertex1 = startOfGraph;
        Vertex vertex2 = startOfGraph;
        for (int i = 0; i < cycleLength; ++i) {
            // put cycle length distance between vertex1 and vertex2;
            vertex2 = walkOne(vertex2);
        }
        while (vertex1 != vertex2) {
            // walk both until equal
            vertex1 = walkOne(vertex1);
            vertex2 = walkOne(vertex2);
        }
        return vertex1;  // if equal, then start of cycle is found
    }

    Vertex walkOne(Vertex const& vertex) { return m_walker.walk(vertex, 1); }
    Vertex walkTwo(Vertex const& vertex) { return m_walker.walk(vertex, 2); }

    int getCycleLength(Vertex const& startOfGraph) {
        // This is actually cyclePath.size()-1.
        // For example the cycle, {4, 5, 6, 4} has a cycle length of 3.
        int powerOfTwo = 1;
        int cycleLength = 1;
        Vertex tortoise = startOfGraph;
        Vertex hare = walkOne(startOfGraph);
        while (tortoise != hare) {
            if (powerOfTwo == cycleLength) {
                // if cycleLength is power of 2
                tortoise = hare;  // set current vertex as something to check
                powerOfTwo *= 2;  // set next power of 2 limit
                cycleLength = 0;
            }
            hare = walkOne(hare);  // iterate all thoughout the graph
            ++cycleLength;
        }
        return cycleLength;
    }

    BaseDirectedGraphWithVertex const& m_graph;
    Walker m_walker;
    bool m_hasACycle{false};
    Path m_cyclePath;
};

}  // namespace alba::algorithm
