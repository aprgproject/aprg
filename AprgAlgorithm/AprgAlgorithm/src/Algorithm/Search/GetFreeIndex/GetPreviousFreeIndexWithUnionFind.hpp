#pragma once

#include <Algorithm/UnionFind/UnionFindForFreeIndex.hpp>

namespace alba::algorithm {

template <typename Index>
class GetPreviousFreeIndexWithUnionFind {
public:
    using UnionFind = UnionFindForFreeIndex<Index>;

    explicit GetPreviousFreeIndexWithUnionFind(Index const numberOfIndexes)
        : m_numberOfIndexes(numberOfIndexes), m_unionFind(numberOfIndexes) {}

    void setAsNotFree(Index const index) {
        if (index > 0 && index < m_numberOfIndexes) {
            m_unionFind.connect(index, index - 1);
        }
    }

    void setAsFree(Index const index) {
        // NOTE: This is linear
        Index rootOfIndex(m_unionFind.getRoot(index));
        if (index < m_numberOfIndexes && rootOfIndex != index) {
            auto& relativeRoots(m_unionFind.getRelativeRootVectorReference());

            relativeRoots[index] = index;
            for (Index i = index + 1; i < static_cast<Index>(relativeRoots.size()); ++i) {
                if (relativeRoots[i] == rootOfIndex) {
                    relativeRoots[i] = index;
                }
            }
        }
    }

    Index getPreviousFreeIndexAt(Index const index) {
        Index result{};
        if (index < m_numberOfIndexes) {
            result = m_unionFind.getRootWithPathCompression(index);
        }
        return result;
    }

private:
    Index m_numberOfIndexes;
    UnionFind m_unionFind;
};

}  // namespace alba::algorithm
