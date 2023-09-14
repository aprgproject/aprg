#pragma once

#include <Algorithm/Graph/Types/GraphTypes.hpp>
#include <Algorithm/Graph/Utilities/SortedEdge.hpp>
#include <Common/Math/Helpers/PrecisionHelpers.hpp>

#include <algorithm>

namespace alba::algorithm {

template <typename Vertex, typename FlowDataType, typename DirectedGraph>
class FlowNetwork : public DirectedGraph {
public:
    using BaseClass = DirectedGraph;
    using Edge = typename GraphTypes<Vertex>::Edge;
    using FlowDataTypes = std::vector<FlowDataType>;

    struct FlowEdgeDetails {
        bool operator==(FlowEdgeDetails const& second) const {
            return mathHelper::isAlmostEqual(capacity, second.capacity) && mathHelper::isAlmostEqual(flow, second.flow);
        }

        FlowDataType capacity;
        FlowDataType flow;
    };

    struct FlowEdge {
        bool operator==(FlowEdge const& second) const {
            return source == second.source && destination == second.destination &&
                   mathHelper::isAlmostEqual(capacity, second.capacity) && mathHelper::isAlmostEqual(flow, second.flow);
        }

        [[nodiscard]] FlowDataType getResidualCapacityTo(Vertex const& vertex) const {
            FlowDataType result{};
            if (source == vertex) {
                result = flow;
            } else if (destination == vertex) {
                result = capacity - flow;
            }
            return result;
        }

        [[nodiscard]] Vertex getTheOtherVertex(Vertex const& mainVertex) const {
            return source == mainVertex ? destination : source;
        }

        void addResidualCapacityTo(Vertex const& vertex, FlowDataType const delta) {
            if (source == vertex) {
                flow -= delta;
            } else if (destination == vertex) {
                flow += delta;
            }
        }

        Vertex source{};
        Vertex destination{};
        FlowDataType capacity{};
        FlowDataType flow{};
    };

    using FlowEdges = std::vector<FlowEdge>;
    using EdgeToFlowEdgeDetailsMap = std::map<Edge, FlowEdgeDetails>;

    FlowNetwork() : BaseClass() {
        static_assert(
            GraphDirectionType::Directed == DirectedGraph::DIRECTION_TYPE,
            "Flow network's underlying graph should be a directed graph");
    }

    void disconnect(Vertex const& vertex1, Vertex const& vertex2) override {
        BaseClass::disconnect(vertex1, vertex2);
        m_edgeToFlowEdgeDetailsMap.erase({vertex1, vertex2});
    }

    [[nodiscard]] EdgeToFlowEdgeDetailsMap const& getEdgeToFlowEdgeDetailsMap() const {
        return m_edgeToFlowEdgeDetailsMap;
    }

    [[nodiscard]] FlowDataType getDeltaFlowAt(Vertex const& vertex) const {
        // this is linear (not optimized)
        FlowDataType result{};
        for (auto const& [edge, details] : m_edgeToFlowEdgeDetailsMap) {
            if (edge.first == vertex) {
                result -= details.flow;
            }
            if (edge.second == vertex) {
                result += details.flow;
            }
        }
        return result;
    }

    [[nodiscard]] FlowDataTypes getSortedCapacities() const {
        FlowDataTypes capacities(getAllCapacities());
        std::sort(capacities.begin(), capacities.end());
        return capacities;
    }

    [[nodiscard]] FlowDataTypes getSortedFlows() const {
        FlowDataTypes flows(getAllFlows());
        std::sort(flows.begin(), flows.end());
        return flows;
    }

    [[nodiscard]] FlowDataTypes getSortedWeights() const { return getSortedCapacities(); }

    [[nodiscard]] FlowEdge getFlowEdge(Vertex const& vertex1, Vertex const& vertex2) const {
        FlowEdgeDetails flowEdgeDetails(getFlowEdgeDetails(vertex1, vertex2));
        return FlowEdge{vertex1, vertex2, flowEdgeDetails.capacity, flowEdgeDetails.flow};
    }

    [[nodiscard]] FlowEdgeDetails getFlowEdgeDetails(Vertex const& vertex1, Vertex const& vertex2) const {
        FlowEdgeDetails result{};
        auto it = m_edgeToFlowEdgeDetailsMap.find({vertex1, vertex2});
        if (it != m_edgeToFlowEdgeDetailsMap.cend()) {
            result = it->second;
        }
        return result;
    }

    [[nodiscard]] FlowEdges getFlowEdges() const {
        FlowEdges result;
        result.reserve(m_edgeToFlowEdgeDetailsMap.size());
        std::transform(
            m_edgeToFlowEdgeDetailsMap.cbegin(), m_edgeToFlowEdgeDetailsMap.cend(), std::back_inserter(result),
            [](auto const& edgeAndDetailsPair) {
                return FlowEdge{
                    edgeAndDetailsPair.first.first, edgeAndDetailsPair.first.second, edgeAndDetailsPair.second.capacity,
                    edgeAndDetailsPair.second.flow};
            });
        return result;
    }

    [[nodiscard]] FlowEdges getFlowEdgesWithVertex(Vertex const& vertex) const {
        // this is linear (not optimized)
        FlowEdges result;
        for (auto const& [edge, details] : m_edgeToFlowEdgeDetailsMap) {
            if (edge.first == vertex || edge.second == vertex) {
                result.emplace_back(FlowEdge{edge.first, edge.second, details.capacity, details.flow});
            }
        }
        return result;
    }

    [[nodiscard]] bool hasAUniqueMinimumSpanningTree() const { return hasNoDuplicateValues(getSortedWeights()); }

    [[nodiscard]] bool hasLocalEquilibrium(Vertex const& vertex) const {
        return mathHelper::isAlmostEqual(getDeltaFlowAt(vertex), static_cast<FlowDataType>(0));
    }

    void connect(Vertex const& vertex1, Vertex const& vertex2, FlowDataType const& capacity, FlowDataType const& flow) {
        connect(vertex1, vertex2);
        m_edgeToFlowEdgeDetailsMap[Edge{vertex1, vertex2}] = {capacity, flow};
    }

    void updateEdge(FlowEdge const& flowEdge) {
        FlowEdgeDetails& detailsToUpdate(m_edgeToFlowEdgeDetailsMap[Edge{flowEdge.source, flowEdge.destination}]);
        detailsToUpdate.capacity = flowEdge.capacity;
        detailsToUpdate.flow = flowEdge.flow;
    }

private:
    void connect(Vertex const& vertex1, Vertex const& vertex2) override { BaseClass::connect(vertex1, vertex2); }

    [[nodiscard]] FlowDataTypes getAllCapacities() const {
        FlowDataTypes result;
        result.reserve(m_edgeToFlowEdgeDetailsMap.size());
        std::transform(
            m_edgeToFlowEdgeDetailsMap.cbegin(), m_edgeToFlowEdgeDetailsMap.cend(), std::back_inserter(result),
            [&](auto const& edgeAndDetailsPair) { return edgeAndDetailsPair.second.capacity; });
        return result;
    }

    [[nodiscard]] FlowDataTypes getAllFlows() const {
        FlowDataTypes result;
        result.reserve(m_edgeToFlowEdgeDetailsMap.size());
        std::transform(
            m_edgeToFlowEdgeDetailsMap.cbegin(), m_edgeToFlowEdgeDetailsMap.cend(), std::back_inserter(result),
            [&](auto const& edgeAndDetailsPair) { return edgeAndDetailsPair.second.flow; });
        return result;
    }

    [[nodiscard]] bool hasNoDuplicateValues(FlowDataTypes const& flowDataTypes) const {
        return std::adjacent_find(flowDataTypes.cbegin(), flowDataTypes.cend()) == flowDataTypes.cend();
    }

    friend std::ostream& operator<<(std::ostream& out, FlowNetwork const& graph) {
        out << static_cast<BaseClass const&>(graph) << "Flow edges: {";
        for (auto const& [edge, details] : graph.m_edgeToFlowEdgeDetailsMap) {
            out << edge.first << "->" << edge.second << "(capacity: " << details.capacity << " flow: " << details.flow
                << "), ";
        }
        out << "}";
        return out;
    }

    EdgeToFlowEdgeDetailsMap m_edgeToFlowEdgeDetailsMap;
};

}  // namespace alba::algorithm
