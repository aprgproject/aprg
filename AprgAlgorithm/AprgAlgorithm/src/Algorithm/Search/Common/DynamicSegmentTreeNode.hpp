#pragma once

#include <memory>

namespace alba::algorithm {

template <typename Value>
struct DynamicSegmentTreeNode {
    Value value;
    std::unique_ptr<DynamicSegmentTreeNode> leftChildPointer;
    std::unique_ptr<DynamicSegmentTreeNode> rightChildPointer;
};

template <typename Value>
struct PersistentDynamicSegmentTreeNode {
    Value value;
    std::shared_ptr<PersistentDynamicSegmentTreeNode> leftChildPointer;
    std::shared_ptr<PersistentDynamicSegmentTreeNode> rightChildPointer;
};

}  // namespace alba::algorithm
