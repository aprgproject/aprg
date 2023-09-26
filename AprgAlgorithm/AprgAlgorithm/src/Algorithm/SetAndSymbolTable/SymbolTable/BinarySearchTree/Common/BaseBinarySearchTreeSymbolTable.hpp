#pragma once

#include <Algorithm/SetAndSymbolTable/Common/BinarySearchTree/BaseBinarySearchTree.hpp>
#include <Algorithm/SetAndSymbolTable/Common/BinarySearchTree/BinarySearchTreeNodes.hpp>
#include <Algorithm/SetAndSymbolTable/SymbolTable/BaseSymbolTable.hpp>
#include <Algorithm/SetAndSymbolTable/SymbolTable/BinarySearchTree/Common/BaseSymbolTableWithBaseTree.hpp>

namespace alba::algorithm {

template <typename Key, typename Value>
class BaseBinarySearchTreeSymbolTable
    : public BaseSymbolTableWithBaseTree<
          Value, BaseBinarySearchTree<Key, BasicTreeNodeWithValue<Key, Value>, BaseSymbolTable<Key, Value>>> {
public:
    BaseBinarySearchTreeSymbolTable() = default;
    // no need for virtual destructor because base destructor is
    // virtual (similar to other virtual functions)
    ~BaseBinarySearchTreeSymbolTable() override = default;
    BaseBinarySearchTreeSymbolTable(BaseBinarySearchTreeSymbolTable const &) = default;
    BaseBinarySearchTreeSymbolTable(BaseBinarySearchTreeSymbolTable &&) noexcept = default;
    BaseBinarySearchTreeSymbolTable &operator=(BaseBinarySearchTreeSymbolTable const &) = default;
    BaseBinarySearchTreeSymbolTable &operator=(BaseBinarySearchTreeSymbolTable &&) noexcept = default;
};

}  // namespace alba::algorithm
