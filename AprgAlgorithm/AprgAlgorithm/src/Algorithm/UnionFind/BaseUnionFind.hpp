#pragma once

namespace alba::algorithm {

template <typename Object>
class BaseUnionFind {
public:
    BaseUnionFind() = default;
    // virtual destructor because of virtual functions (vtable exists)
    virtual ~BaseUnionFind() = default;
    BaseUnionFind(BaseUnionFind const&) = default;
    BaseUnionFind(BaseUnionFind&&) noexcept = default;
    BaseUnionFind& operator=(BaseUnionFind const&) = default;
    BaseUnionFind& operator=(BaseUnionFind&&) noexcept = default;

    [[nodiscard]] virtual Object getRoot(
        Object const& object) const = 0;  // this is basically an identifier for the connected components

    [[nodiscard]] virtual bool isConnected(Object const& object1, Object const& object2) const = 0;
    virtual void connect(Object const& object1, Object const& object2) = 0;
};

}  // namespace alba::algorithm

// This can be called as a disjoint-set data structure.
// A disjoint-set data structure is a data structure that keeps track of a set of elements partitioned
// into a number of disjoint (non-overlapping) subsets.
// A union-find algorithm is an algorithm that performs two useful operations on such a data structure:
// -> Find: Determine which subset a particular element is in. This can be used for determining if two elements are in
// the same subset.
// -> Union: Join two subsets into a single subset.
// In this post, we will discuss the application of Disjoint Set Data Structure.
