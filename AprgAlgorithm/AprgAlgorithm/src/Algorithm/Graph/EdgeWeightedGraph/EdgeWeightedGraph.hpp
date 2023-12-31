#pragma once

#include <Algorithm/Graph/Types/GraphTypes.hpp>
#include <Algorithm/Graph/Utilities/SortedEdge.hpp>

#include <algorithm>
#include <ostream>

namespace alba::algorithm {

template <typename Vertex, typename Weight, typename Graph>
class EdgeWeightedGraph : public Graph {
public:
    using BaseClass = Graph;
    using Edge = typename GraphTypes<Vertex>::Edge;
    using EdgeToWeightMap = std::map<Edge, Weight>;
    using EdgeOrderedByWeight = typename GraphTypesWithWeights<Vertex, Weight>::EdgeOrderedByWeight;
    using EdgesWithWeight = typename GraphTypesWithWeights<Vertex, Weight>::EdgesWithWeight;
    using Weights = std::vector<Weight>;
    EdgeWeightedGraph() = default;

    void disconnect(Vertex const& vertex1, Vertex const& vertex2) override {
        BaseClass::disconnect(vertex1, vertex2);
        m_edgeToWeightMap.erase(createEdgeInMap(vertex1, vertex2));
    }

    [[nodiscard]] EdgeToWeightMap const& getEdgeToWeightMap() const { return m_edgeToWeightMap; }

    [[nodiscard]] EdgesWithWeight getEdgesWithWeight() const {
        EdgesWithWeight result;
        result.reserve(m_edgeToWeightMap.size());
        std::transform(
            m_edgeToWeightMap.cbegin(), m_edgeToWeightMap.cend(), std::back_inserter(result),
            [](auto const& edgeAndWeightPair) {
                return EdgeOrderedByWeight(
                    edgeAndWeightPair.first.first, edgeAndWeightPair.first.second, edgeAndWeightPair.second);
            });
        return result;
    }

    [[nodiscard]] Weight getWeight(Vertex const& vertex1, Vertex const& vertex2) const {
        Weight result{};
        auto it = m_edgeToWeightMap.find(createEdgeInMap(vertex1, vertex2));
        if (it != m_edgeToWeightMap.cend()) {
            result = it->second;
        }
        return result;
    }

    [[nodiscard]] Weights getSortedWeights() const {
        Weights weights(getAllWeights());
        std::sort(weights.begin(), weights.end());
        return weights;
    }

    [[nodiscard]] bool hasAUniqueMinimumSpanningTree() const { return hasNoDuplicateWeights(getSortedWeights()); }

    void connect(Vertex const& vertex1, Vertex const& vertex2, Weight const& weight) {
        BaseClass::connect(vertex1, vertex2);
        m_edgeToWeightMap[createEdgeInMap(vertex1, vertex2)] = weight;
    }

private:
    using Graph::connect;  // prevents clang warning about hiding an overloaded virtual function

    [[nodiscard]] Edge createEdgeInMap(Vertex const& vertex1, Vertex const& vertex2) const {
        if (this->DIRECTION_TYPE == GraphDirectionType::Undirected) {
            return createSortedEdge<Vertex, Edge>(vertex1, vertex2);
        }
        return Edge(vertex1, vertex2);
    }

    [[nodiscard]] Weights getAllWeights() const {
        Weights result;
        result.reserve(m_edgeToWeightMap.size());
        std::transform(
            m_edgeToWeightMap.cbegin(), m_edgeToWeightMap.cend(), std::back_inserter(result),
            [&](auto const& edgeAndWeightPair) { return edgeAndWeightPair.second; });
        return result;
    }

    [[nodiscard]] bool hasNoDuplicateWeights(Weights const& sortedWeights) const {
        return std::adjacent_find(sortedWeights.cbegin(), sortedWeights.cend()) == sortedWeights.cend();
    }

    friend std::ostream& operator<<(std::ostream& out, EdgeWeightedGraph const& graph) {
        out << static_cast<BaseClass const&>(graph) << "Edges with weight: {";
        for (auto const& edgeOrderedByWeight : graph.m_edgeToWeightMap) {
            out << edgeOrderedByWeight.first.first << "<->" << edgeOrderedByWeight.first.second << "("
                << edgeOrderedByWeight.second << "), ";
        }
        out << "}";
        return out;
    }

    EdgeToWeightMap m_edgeToWeightMap;
};

}  // namespace alba::algorithm
