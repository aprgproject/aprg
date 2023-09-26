#pragma once

#include <Algorithm/SetAndSymbolTable/Common/BinarySearchTree/BaseBinarySearchTree.hpp>
#include <Algorithm/SetAndSymbolTable/Common/BinarySearchTree/BinarySearchTreeNodes.hpp>
#include <Algorithm/SetAndSymbolTable/Set/BaseSet.hpp>
#include <Algorithm/SetAndSymbolTable/Set/BinarySearchTree/Common/BaseSetWithBaseTree.hpp>

namespace alba::algorithm {

template <typename Key>
class BaseBinarySearchTreeSet
    : public BaseSetWithBaseTree<BaseBinarySearchTree<Key, BasicTreeNode<Key>, BaseSet<Key>>> {
public:
    BaseBinarySearchTreeSet() = default;
    // no need for virtual destructor because base destructor is virtual
    // (similar to other virtual functions)
    ~BaseBinarySearchTreeSet() override = default;
    BaseBinarySearchTreeSet(BaseBinarySearchTreeSet const &) = default;
    BaseBinarySearchTreeSet(BaseBinarySearchTreeSet &&) noexcept = default;
    BaseBinarySearchTreeSet &operator=(BaseBinarySearchTreeSet const &) = default;
    BaseBinarySearchTreeSet &operator=(BaseBinarySearchTreeSet &&) noexcept = default;
};

}  // namespace alba::algorithm
