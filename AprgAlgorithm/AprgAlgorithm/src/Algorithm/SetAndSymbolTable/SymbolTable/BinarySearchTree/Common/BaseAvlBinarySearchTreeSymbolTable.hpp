#pragma once

#include <Algorithm/SetAndSymbolTable/Common/BinarySearchTree/BaseAvlBinarySearchTree.hpp>
#include <Algorithm/SetAndSymbolTable/Common/BinarySearchTree/BinarySearchTreeNodes.hpp>
#include <Algorithm/SetAndSymbolTable/SymbolTable/BaseSymbolTable.hpp>
#include <Algorithm/SetAndSymbolTable/SymbolTable/BinarySearchTree/Common/BaseSymbolTableWithBaseTree.hpp>

namespace alba::algorithm {

template <typename Key, typename Value>
class BaseAvlBinarySearchTreeSymbolTable
    : public BaseSymbolTableWithBaseTree<
          Value, BaseAvlBinarySearchTree<Key, AvlTreeNodeWithValue<Key, Value>, BaseSymbolTable<Key, Value>>> {
public:
    // no need for virtual destructor because base destructor
    // is virtual (similar to other virtual functions)
    ~BaseAvlBinarySearchTreeSymbolTable() override = default;
    BaseAvlBinarySearchTreeSymbolTable() = default;
    BaseAvlBinarySearchTreeSymbolTable(BaseAvlBinarySearchTreeSymbolTable const &) = default;
    BaseAvlBinarySearchTreeSymbolTable(BaseAvlBinarySearchTreeSymbolTable &&) = default;
    BaseAvlBinarySearchTreeSymbolTable &operator=(BaseAvlBinarySearchTreeSymbolTable const &) = default;
    BaseAvlBinarySearchTreeSymbolTable &operator=(BaseAvlBinarySearchTreeSymbolTable &&) = default;
};

}  // namespace alba::algorithm
