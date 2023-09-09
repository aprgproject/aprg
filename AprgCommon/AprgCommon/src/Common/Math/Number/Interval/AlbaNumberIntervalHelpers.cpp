#include "AlbaNumberIntervalHelpers.hpp"

#include <Common/Math/Number/AlbaNumberConstants.hpp>

#include <algorithm>

using namespace alba::AlbaNumberConstants;
using namespace std;

namespace alba {

AlbaNumberInterval createAllRealValuesInterval() {
    return {createNegativeInfinityOpenEndpoint(), createPositiveInfinityOpenEndpoint()};
}

AlbaNumberIntervalEndpoint createOpenEndpoint(AlbaNumber const value) {
    return {AlbaNumberIntervalEndpoint::Type::Open, value};
}

AlbaNumberIntervalEndpoint createCloseEndpoint(AlbaNumber const value) {
    return {AlbaNumberIntervalEndpoint::Type::Close, value};
}

AlbaNumberIntervalEndpoint createEndpoint(bool const isCloseEndpoint, AlbaNumber const value) {
    return {getEndpointTypeWithCheckingIfItsClosed(isCloseEndpoint), value};
}

AlbaNumberIntervalEndpoint createPositiveInfinityOpenEndpoint() {
    return createOpenEndpoint(ALBA_NUMBER_POSITIVE_INFINITY);
}

AlbaNumberIntervalEndpoint createNegativeInfinityOpenEndpoint() {
    return createOpenEndpoint(ALBA_NUMBER_NEGATIVE_INFINITY);
}

AlbaNumbers getNumbersInsideTheInterval(AlbaNumbers const& numbersToCheck, AlbaNumberInterval const& intervalToCheck) {
    AlbaNumbers result;
    copy_if(
        numbersToCheck.begin(), numbersToCheck.end(), back_inserter(result),
        [&intervalToCheck](AlbaNumber const& numberToCheck) {
            return intervalToCheck.isValueInsideTheInterval(numberToCheck);
        });
    return result;
}

AlbaNumberIntervalEndpoint::Type getEndpointTypeWithCheckingIfItsClosed(bool const isCloseEndpoint) {
    return isCloseEndpoint ? AlbaNumberIntervalEndpoint::Type::Close : AlbaNumberIntervalEndpoint::Type::Open;
}

bool isValueInsideTheIntervals(AlbaNumber const innerValue, AlbaNumberIntervals const& outerIntervals) {
    return any_of(outerIntervals.cbegin(), outerIntervals.cend(), [&](AlbaNumberInterval const& interval) {
        return interval.isValueInsideTheInterval(innerValue);
    });
}

bool isIntervalInsideTheIntervals(AlbaNumberInterval const& innerInterval, AlbaNumberIntervals const& outerIntervals) {
    return any_of(outerIntervals.cbegin(), outerIntervals.cend(), [&](AlbaNumberInterval const& outerInterval) {
        return outerInterval.isIntervalInsideTheInterval(innerInterval);
    });
}

bool areTheIntervalsInsideTheInterval(
    AlbaNumberIntervals const& innerIntervals, AlbaNumberInterval const& outerInterval) {
    return all_of(innerIntervals.cbegin(), innerIntervals.cend(), [&](AlbaNumberInterval const& innerInterval) {
        return outerInterval.isIntervalInsideTheInterval(innerInterval);
    });
}

}  // namespace alba
