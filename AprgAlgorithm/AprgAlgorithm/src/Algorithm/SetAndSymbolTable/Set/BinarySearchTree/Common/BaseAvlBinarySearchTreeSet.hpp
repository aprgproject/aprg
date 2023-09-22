#pragma once

#include <Algorithm/SetAndSymbolTable/Common/BinarySearchTree/BaseAvlBinarySearchTree.hpp>
#include <Algorithm/SetAndSymbolTable/Common/BinarySearchTree/BinarySearchTreeNodes.hpp>
#include <Algorithm/SetAndSymbolTable/Set/BaseSet.hpp>
#include <Algorithm/SetAndSymbolTable/Set/BinarySearchTree/Common/BaseSetWithBaseTree.hpp>

namespace alba::algorithm {

template <typename Key>
class BaseAvlBinarySearchTreeSet
    : public BaseSetWithBaseTree<BaseAvlBinarySearchTree<Key, AvlTreeNode<Key>, BaseSet<Key>>> {
public:
    // no need for virtual destructor because base destructor is virtual
    // (similar to other virtual functions)
    ~BaseAvlBinarySearchTreeSet() override = default;
    BaseAvlBinarySearchTreeSet() = default;
    BaseAvlBinarySearchTreeSet(BaseAvlBinarySearchTreeSet const &) = default;
    BaseAvlBinarySearchTreeSet(BaseAvlBinarySearchTreeSet &&) = default;
    BaseAvlBinarySearchTreeSet &operator=(BaseAvlBinarySearchTreeSet const &) = default;
    BaseAvlBinarySearchTreeSet &operator=(BaseAvlBinarySearchTreeSet &&) = default;
};

}  // namespace alba::algorithm
