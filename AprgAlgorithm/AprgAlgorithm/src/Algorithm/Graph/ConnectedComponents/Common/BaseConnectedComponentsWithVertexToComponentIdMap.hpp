#pragma once

#include <Algorithm/Graph/ConnectedComponents/Common/BaseConnectedComponents.hpp>
#include <Algorithm/Graph/UndirectedGraph/BaseUndirectedGraph.hpp>

namespace alba::algorithm {

template <typename Vertex, typename Graph>
class BaseConnectedComponentsWithVertexToComponentIdMap : public BaseConnectedComponents<Vertex> {
public:
    using VertexToIntMap = typename GraphTypes<Vertex>::VertexToIntMap;

    explicit BaseConnectedComponentsWithVertexToComponentIdMap(Graph const& graph) : m_graph(graph) {}

    ~BaseConnectedComponentsWithVertexToComponentIdMap() override =
        default;  // no need for virtual destructor because base destructor is virtual (similar to other virtual
                  // functions)

    [[nodiscard]] bool isConnected(Vertex const& vertex1, Vertex const& vertex2) const override {
        auto it1 = m_vertexToComponentIdMap.find(vertex1);
        auto it2 = m_vertexToComponentIdMap.find(vertex2);
        bool result(false);
        if (it1 != m_vertexToComponentIdMap.cend() && it2 != m_vertexToComponentIdMap.cend()) {
            result = it1->second == it2->second;
        }
        return result;
    }

    [[nodiscard]] int getNumberOfComponentIds() const override { return m_numberOfComponentIds; }

    [[nodiscard]] int getComponentId(Vertex const& vertex) const override {
        int result(0);
        auto it = m_vertexToComponentIdMap.find(vertex);
        if (it != m_vertexToComponentIdMap.cend()) {
            result = it->second;
        }
        return result;
    }

protected:
    Graph const& m_graph;
    int m_numberOfComponentIds{0};
    VertexToIntMap m_vertexToComponentIdMap;
};

}  // namespace alba::algorithm
