#pragma once

#include <Common/Math/Number/AlbaNumberTypes.hpp>

#include <functional>
#include <map>
#include <string>

namespace alba::algebra {

class SolutionSet {
public:
    using FunctionForCheckingValues = std::function<bool(AlbaNumber const&)>;
    SolutionSet() = default;
    [[nodiscard]] AlbaNumberIntervals const& getAcceptedIntervals() const;
    [[nodiscard]] AlbaNumbers const& getAcceptedValues() const;
    [[nodiscard]] AlbaNumbers const& getRejectedValues() const;
    [[nodiscard]] bool isEmpty() const;
    void addAcceptedValue(AlbaNumber const& value);
    void addRejectedValue(AlbaNumber const& value);
    void addAcceptedValues(AlbaNumbers const& values);
    void addRejectedValues(AlbaNumbers const& values);
    void addAcceptedInterval(AlbaNumberInterval const& interval);
    void addValue(AlbaNumber const& value, FunctionForCheckingValues const& isValueAcceptedFunction);

    void determineAndAddAcceptedIntervals(
        AlbaNumbers const& additionalValuesToCheck, FunctionForCheckingValues const& isValueAcceptedFunction);

private:
    void prepareValuesToCheck(AlbaNumbers& combinedValuesToCheck);

    void checkValuesAndPutIntervals(
        AlbaNumbers const& valuesToCheck, FunctionForCheckingValues const& isValueAcceptedFunction);

    void addInterval(
        AlbaNumber const& lowerEndpointValue, AlbaNumber const& intervalValueToCheck,
        AlbaNumber const& higherEndpointValue, FunctionForCheckingValues const& isValueAcceptedFunction);

    void combineAcceptedIntervalsIfPossible();
    friend std::ostream& operator<<(std::ostream& out, SolutionSet const& solutionSet);
    AlbaNumbers m_acceptedValues;
    AlbaNumbers m_rejectedValues;
    AlbaNumberIntervals m_acceptedIntervals;
};

}  // namespace alba::algebra
