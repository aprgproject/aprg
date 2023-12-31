#pragma once

#include <Algorithm/Graph/FlowNetwork/FlowNetwork.hpp>

#include <algorithm>

namespace alba::algorithm {

template <typename VertexUnderlyingType, typename FlowDataTypeUnderlyingType, typename DirectedGraph>
class SinkSourceFlowNetwork : public FlowNetwork<VertexUnderlyingType, FlowDataTypeUnderlyingType, DirectedGraph> {
public:
    using Vertex = VertexUnderlyingType;
    using FlowDataType = FlowDataTypeUnderlyingType;
    using BaseClass = FlowNetwork<Vertex, FlowDataType, DirectedGraph>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    // An ST-flow network has two identified vertices, a source "s" and a sink "t";
    SinkSourceFlowNetwork(Vertex const& source, Vertex const& sink) : BaseClass(), m_source(source), m_sink(sink) {}
    SinkSourceFlowNetwork(Vertex&& source, Vertex&& sink) : BaseClass(), m_source(source), m_sink(sink) {}
    [[nodiscard]] Vertex getSourceVertex() const { return m_source; }
    [[nodiscard]] Vertex getSinkVertex() const { return m_sink; }

    [[nodiscard]] bool isAnStCut(Vertices const& partWithSource, Vertices const& partWithSink) const {
        // An st-cut is a cut that places vertex "source" in one of this its sets and vertex "sink" in the other
        return std::find(partWithSource.cbegin(), partWithSource.cend(), m_source) != partWithSource.cend() &&
               std::find(partWithSink.cbegin(), partWithSink.cend(), m_sink) != partWithSink.cend();
    }

private:
    Vertex m_source;
    Vertex m_sink;
};

}  // namespace alba::algorithm
