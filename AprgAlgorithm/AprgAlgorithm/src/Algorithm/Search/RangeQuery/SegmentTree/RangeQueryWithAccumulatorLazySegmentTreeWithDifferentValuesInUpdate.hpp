#pragma once

#include <Algorithm/Search/RangeQuery/SegmentTree/RangeQueryWithStaticSegmentTree.hpp>
#include <Algorithm/Utilities/IndexHelper.hpp>
#include <Common/Math/Helpers/ComputationHelpers.hpp>

namespace alba::algorithm {

template <typename Values>
class RangeQueryWithAccumulatorLazySegmentTreeWithDifferentValuesInUpdate
    : private RangeQueryWithStaticSegmentTree<Values> {
public:
    // Example for "range query with accumulator" is sum queries
    using BaseClass = RangeQueryWithStaticSegmentTree<Values>;
    using Value = typename BaseClass::Value;
    using Index = typename BaseClass::Index;
    using Function = typename BaseClass::Function;
    using Utilities = typename BaseClass::Utilities;
    using IncrementFunction = std::function<Value(Index const, Index const)>;
    using UpdateDetail = Index;
    using PendingUpdateDetail = std::optional<UpdateDetail>;
    using PendingUpdateDetails = std::vector<PendingUpdateDetail>;

    RangeQueryWithAccumulatorLazySegmentTreeWithDifferentValuesInUpdate(
        Values const& valuesToCheck, Function const& functionObject, IncrementFunction const& incrementFunction)
        : BaseClass(valuesToCheck, functionObject),
          b_startOfChildren(BaseClass::m_startOfChildren),
          b_treeValues(BaseClass::m_treeValues),
          b_function(BaseClass::m_function),
          m_incrementFunction(incrementFunction),
          m_startIndexesForPendingUpdates(b_startOfChildren, PendingUpdateDetail()) {
        // only parent have pending updates
    }

    RangeQueryWithAccumulatorLazySegmentTreeWithDifferentValuesInUpdate(
        Values const& valuesToCheck, Function const& functionObject, IncrementFunction&& incrementFunction)
        : BaseClass(valuesToCheck, functionObject),
          b_startOfChildren(BaseClass::m_startOfChildren),
          b_treeValues(BaseClass::m_treeValues),
          b_function(BaseClass::m_function),
          m_incrementFunction(incrementFunction),
          m_startIndexesForPendingUpdates(b_startOfChildren, PendingUpdateDetail()) {
        // only parent have pending updates
    }

    void increaseAtRange(Index const start, Index const end) {
        if (start <= end && (b_startOfChildren + start) < static_cast<Index>(b_treeValues.size()) &&
            (b_startOfChildren + end) < static_cast<Index>(b_treeValues.size())) {
            increaseAtRangeFromTopToBottom(
                start, end, Utilities::ROOT_PARENT_INDEX, 0, b_startOfChildren);  // startOfChildren is size of base too
        }
    }

    Value getValueOnInterval(Index const start, Index const end) {
        // This has log(N) running time
        Value result{};
        if (start <= end && (b_startOfChildren + start) < static_cast<Index>(b_treeValues.size()) &&
            (b_startOfChildren + end) < static_cast<Index>(b_treeValues.size())) {
            result = getValueOnIntervalFromTopToBottom(
                start, end, Utilities::ROOT_PARENT_INDEX, 0, b_startOfChildren);  // startOfChildren is size of base too
        }
        return result;
    }

private:
    inline void increment(Value& valueToChange, Index const startIndex, Index const left, Index const right) const {
        Index const numberOfChildren = b_treeValues.size() - b_startOfChildren;
        Index const startInterval = std::min(left, numberOfChildren - 1) - startIndex;
        Index const endInterval = std::min(right, numberOfChildren - 1) - startIndex;
        valueToChange = b_function(valueToChange, m_incrementFunction(startInterval, endInterval));
    }

    inline void incrementOrUpdateAtIndex(
        Index const index, Index const baseLeft, Index const baseRight,
        PendingUpdateDetail const& startIndexForPendingUpdate) {
        if (isAParent(index)) {
            performUpdateAtIndexIfNeeded(index, baseLeft, baseRight);
            m_startIndexesForPendingUpdates[index] = startIndexForPendingUpdate;  // copy pending update to children
        } else {
            increment(b_treeValues[index], startIndexForPendingUpdate.value(), baseLeft, baseRight);
        }
    }

    [[nodiscard]] Index isAParent(Index const treeIndex) const { return treeIndex < b_startOfChildren; }

    void increaseAtRangeFromTopToBottom(
        Index const startInterval, Index const endInterval, Index const currentChild, Index const baseLeft,
        Index const baseRight) {
        // This has log(N) running time
        // performUpdateAtIndexIfNeeded(currentChild, baseLeft, baseRight); // propagate current update before
        // processing, but I think its not needed
        if (baseLeft == baseRight) {
            increment(b_treeValues[currentChild], startInterval, baseLeft, baseLeft);
        } else if (startInterval <= baseLeft && baseRight <= endInterval) {
            m_startIndexesForPendingUpdates[currentChild] = startInterval;
        } else {
            Index const intersectionLeft = std::max(startInterval, baseLeft);
            Index const intersectionRight = std::min(endInterval, baseRight);
            increment(b_treeValues[currentChild], startInterval, intersectionLeft, intersectionRight);

            Index const baseMidPoint = getMidpointOfIndexes(baseLeft, baseRight);
            bool const doesLeftPartIntersect = !(endInterval < baseLeft || startInterval > baseMidPoint);
            bool const doesRightPartIntersect = !(endInterval < baseMidPoint + 1 || startInterval > baseRight);
            if (doesLeftPartIntersect && doesRightPartIntersect) {
                increaseAtRangeFromTopToBottom(
                    startInterval, endInterval, Utilities::getLeftChild(currentChild), baseLeft, baseMidPoint);
                increaseAtRangeFromTopToBottom(
                    startInterval, endInterval, Utilities::getRightChild(currentChild), baseMidPoint + 1, baseRight);
            } else if (doesLeftPartIntersect) {
                increaseAtRangeFromTopToBottom(
                    startInterval, endInterval, Utilities::getLeftChild(currentChild), baseLeft, baseMidPoint);
            } else if (doesRightPartIntersect) {
                increaseAtRangeFromTopToBottom(
                    startInterval, endInterval, Utilities::getRightChild(currentChild), baseMidPoint + 1, baseRight);
            }
        }
    }

    void performUpdateAtIndexIfNeeded(Index const index, Index const baseLeft, Index const baseRight) {
        if (index < static_cast<Index>(m_startIndexesForPendingUpdates.size())) {
            PendingUpdateDetail& startIndexForPendingUpdate = m_startIndexesForPendingUpdates[index];
            if (startIndexForPendingUpdate) {
                increment(b_treeValues[index], startIndexForPendingUpdate.value(), baseLeft, baseRight);
                Index const baseMidPoint = getMidpointOfIndexes(baseLeft, baseRight);
                incrementOrUpdateAtIndex(
                    Utilities::getLeftChild(index), baseLeft, baseMidPoint, startIndexForPendingUpdate);
                incrementOrUpdateAtIndex(
                    Utilities::getRightChild(index), baseMidPoint + 1, baseRight, startIndexForPendingUpdate);
                startIndexForPendingUpdate.reset();
            }
        }
    }

    Value getValueOnIntervalFromTopToBottom(
        Index const startInterval, Index const endInterval, Index const currentChild, Index const baseLeft,
        Index const baseRight) {
        // This has log(N) running time
        Value result{};
        performUpdateAtIndexIfNeeded(currentChild, baseLeft, baseRight);  // propagate current update before processing
        if (startInterval <= baseLeft && baseRight <= endInterval) {
            result = b_treeValues[currentChild];
        } else {
            Index const baseMidPoint = getMidpointOfIndexes(baseLeft, baseRight);
            bool const doesLeftPartIntersect = !(endInterval < baseLeft || baseMidPoint < startInterval);
            bool const doesRightPartIntersect = !(endInterval < baseMidPoint + 1 || baseRight < startInterval);
            if (doesLeftPartIntersect && doesRightPartIntersect) {
                result = b_function(
                    getValueOnIntervalFromTopToBottom(
                        startInterval, endInterval, Utilities::getLeftChild(currentChild), baseLeft, baseMidPoint),
                    getValueOnIntervalFromTopToBottom(
                        startInterval, endInterval, Utilities::getRightChild(currentChild), baseMidPoint + 1,
                        baseRight));
            } else if (doesLeftPartIntersect) {
                result = getValueOnIntervalFromTopToBottom(
                    startInterval, endInterval, Utilities::getLeftChild(currentChild), baseLeft, baseMidPoint);
            } else if (doesRightPartIntersect) {
                result = getValueOnIntervalFromTopToBottom(
                    startInterval, endInterval, Utilities::getRightChild(currentChild), baseMidPoint + 1, baseRight);
            }
        }
        return result;
    }

    Index const b_startOfChildren;
    Values& b_treeValues;
    Function const& b_function;
    IncrementFunction m_incrementFunction;
    PendingUpdateDetails m_startIndexesForPendingUpdates;
};

}  // namespace alba::algorithm
