#include "SolutionUtilities.hpp"

#include <Algebra/Retrieval/NumbersRetriever.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba::algebra {

void retrieveInitialValuesForIteratingMethods(AlbaNumbersSet& allValues, Term const& term) {
    NumbersRetriever retriever;
    retriever.retrieveFromTerm(term);
    AlbaNumbersSet const& numbers(retriever.getNumbers());
    for (AlbaNumber const& number : numbers) {
        AlbaNumber const positiveNumber(getAbsoluteValue(number));
        AlbaNumber const positiveLogarithm(log(positiveNumber.getDouble()));
        allValues.emplace(positiveNumber * -1);
        allValues.emplace(positiveLogarithm * -1);
        allValues.emplace(positiveLogarithm);
        allValues.emplace(positiveNumber);
    }
}

AlbaNumber getPositiveLogarithmOfLargestNumber(Term const& term) {
    NumbersRetriever retriever;
    retriever.retrieveFromTerm(term);
    AlbaNumbersSet const& numbers(retriever.getNumbers());
    AlbaNumber initialValue(0);
    if (!numbers.empty()) {
        initialValue = log(getAbsoluteValue((*numbers.cbegin()).getDouble()));
    }
    return initialValue;
}

AlbaNumbers getInitialValuesForIteratingMethods(Term const& term) {
    AlbaNumbers result;
    AlbaNumbersSet allValues;
    retrieveInitialValuesForIteratingMethods(allValues, term);
    result.reserve(allValues.size());
    copy(allValues.cbegin(), allValues.cend(), back_inserter(result));
    return result;
}

AlbaNumbers getInitialValuesForIteratingMethods(Equation const& equation) {
    AlbaNumbers result;
    AlbaNumbersSet allValues;
    retrieveInitialValuesForIteratingMethods(allValues, equation.getLeftHandTerm());
    retrieveInitialValuesForIteratingMethods(allValues, equation.getRightHandTerm());
    result.reserve(allValues.size());
    copy(allValues.cbegin(), allValues.cend(), back_inserter(result));
    return result;
}

}  // namespace alba::algebra
