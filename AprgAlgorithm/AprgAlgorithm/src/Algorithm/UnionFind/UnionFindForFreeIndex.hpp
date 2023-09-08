#pragma once

#include <Algorithm/UnionFind/BaseUnionFind.hpp>

#include <vector>

namespace alba::algorithm {

template <typename Object>
class UnionFindForFreeIndex : public BaseUnionFind<Object> {
public:
    using RootVector = std::vector<Object>;
    explicit UnionFindForFreeIndex(int const maximumSize) : m_relativeRoots() { initialize(maximumSize); }

    [[nodiscard]] bool isConnected(Object const& object1, Object const& object2) const override {
        return getRoot(object1) == getRoot(object2);
    }

    [[nodiscard]] Object getRoot(Object const& object) const override {
        Object currentRoot(object);
        Object nextRoot(m_relativeRoots[object]);
        while (currentRoot != nextRoot) {
            currentRoot = nextRoot;
            nextRoot = m_relativeRoots[currentRoot];
        }
        return currentRoot;
    }

    [[nodiscard]] RootVector const& getRelativeRootVector() const { return m_relativeRoots; }

    Object getRootWithPathCompression(Object const& object) {
        RootVector relativeRoots;
        Object mainRoot = getRootAndRelativeRoots(object, relativeRoots);
        saveNewRootOnRelativeRoots(mainRoot, relativeRoots);
        return mainRoot;
    }

    RootVector& getRelativeRootVectorReference() { return m_relativeRoots; }

    void connect(Object const& source, Object const& destination) override {
        // Path compression
        RootVector relativeRoots;
        getRootAndRelativeRoots(source, relativeRoots);
        Object mainRoot = getRootAndRelativeRoots(destination, relativeRoots);
        saveNewRootOnRelativeRoots(mainRoot, relativeRoots);
    }

private:
    Object getRootAndRelativeRoots(Object const& object, RootVector& relativeRoots) const {
        Object currentRoot(object);
        Object nextRoot(m_relativeRoots[object]);
        relativeRoots.emplace_back(currentRoot);
        while (currentRoot != nextRoot) {
            currentRoot = nextRoot;
            relativeRoots.emplace_back(nextRoot);
            nextRoot = m_relativeRoots[currentRoot];
        }
        return currentRoot;
    }

    void initialize(int const maximumSize) {
        // runs in linear time
        m_relativeRoots.reserve(maximumSize);
        for (int i = 0; i < maximumSize; ++i) {
            m_relativeRoots.emplace_back(i);
        }
        m_relativeRoots.shrink_to_fit();
    }

    void saveNewRootOnRelativeRoots(Object const& newRoot, RootVector const& relativeRoots) {
        for (Object const& relativeRoot : relativeRoots) {
            m_relativeRoots[relativeRoot] = newRoot;
        }
    }

    RootVector m_relativeRoots;
};

}  // namespace alba::algorithm
