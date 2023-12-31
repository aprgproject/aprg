#pragma once

#include <Algorithm/UnionFind/BaseUnionFind.hpp>

#include <array>
#include <numeric>

namespace alba::algorithm {

template <typename Object, int SIZE>
class QuickFind : public BaseUnionFind<Object> {
public:
    using RootArray = std::array<Object, SIZE>;
    QuickFind() : m_roots() { initialize(); }
    [[nodiscard]] Object getRoot(Object const& object) const override { return m_roots[object]; }

    [[nodiscard]] bool isConnected(Object const& object1, Object const& object2) const override {
        return getRoot(object1) == getRoot(object2);
    }

    void connect(Object const& object1, Object const& object2) override {
        // runs in linear time (too expensive it should take constant/logarithmic time)
        Object root1(getRoot(object1));
        Object root2(getRoot(object2));
        if (root1 != root2) {
            // this is an eager approach (every connect -> update new root to all old roots)
            replaceAllOldRootsWithNewRoot(root2, root1);
        }
    }

    [[nodiscard]] RootArray const& getRootArray() const { return m_roots; }

private:
    void initialize() {
        // runs in linear time
        std::iota(m_roots.begin(), m_roots.end(), 0);
    }

    void replaceAllOldRootsWithNewRoot(Object const& oldRoot, Object const& newRoot) {
        for (int i = 0; i < SIZE; ++i) {
            if (m_roots[i] == oldRoot) {
                m_roots[i] = newRoot;
            }
        }
    }

    RootArray m_roots;
};

}  // namespace alba::algorithm
