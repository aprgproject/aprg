#pragma once

#include <Algorithm/Graph/Types/GraphTypes.hpp>

#include <map>
#include <vector>

namespace alba::algorithm {

template <typename Vertex, typename Object>
class InvertedMapForSymbolGraph {
public:
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using ObjectToVertexMap = std::map<Object, Vertex>;
    [[nodiscard]] ObjectToVertexMap const& getObjectToVertexMap() const { return m_invertedMap; }
    [[nodiscard]] Vertices const& getUnusedVertices() const { return m_unusedVertices; }

    void removeObject(Object const& object) {
        auto it = m_invertedMap.find(object);
        if (it != m_invertedMap.cend()) {
            m_unusedVertices.emplace_back(it->second);
            m_invertedMap.erase(object);
        }
    }

    void clear() {
        m_invertedMap.clear();
        m_unusedVertices.clear();
    }

    Vertex const& getVertexIdentifierAndAddObjectIfNeeded(Object const& object) {
        auto it = m_invertedMap.find(object);
        if (it == m_invertedMap.cend()) {
            Vertex vertexToUse(m_invertedMap.size());
            if (!m_unusedVertices.empty()) {
                vertexToUse = m_unusedVertices.back();
                m_unusedVertices.pop_back();
            }
            m_invertedMap.emplace(object, vertexToUse);
            it = m_invertedMap.find(object);
        }
        return it->second;
    }

private:
    ObjectToVertexMap m_invertedMap;
    Vertices m_unusedVertices;
};

}  // namespace alba::algorithm
