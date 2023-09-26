#pragma once

#include <Algorithm/SetAndSymbolTable/Common/BinarySearchTree/BaseRedBlackBinarySearchTree.hpp>
#include <Algorithm/SetAndSymbolTable/Set/BaseSet.hpp>
#include <Algorithm/SetAndSymbolTable/Set/BinarySearchTree/Common/BaseSetWithBaseTree.hpp>

#include <memory>

namespace alba::algorithm {

template <typename Key, typename Node>
class BaseRedBlackBinarySearchTreeSet
    : public BaseSetWithBaseTree<BaseRedBlackBinarySearchTree<Key, Node, BaseSet<Key>>> {
public:
    BaseRedBlackBinarySearchTreeSet() = default;
    // no need for virtual destructor because base destructor is
    // virtual (similar to other virtual functions)
    ~BaseRedBlackBinarySearchTreeSet() override = default;
    BaseRedBlackBinarySearchTreeSet(BaseRedBlackBinarySearchTreeSet const &) = default;
    BaseRedBlackBinarySearchTreeSet(BaseRedBlackBinarySearchTreeSet &&) noexcept = default;
    BaseRedBlackBinarySearchTreeSet &operator=(BaseRedBlackBinarySearchTreeSet const &) = default;
    BaseRedBlackBinarySearchTreeSet &operator=(BaseRedBlackBinarySearchTreeSet &&) noexcept = default;
};

}  // namespace alba::algorithm
