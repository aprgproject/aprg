#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

#include <map>
#include <string>

namespace alba::algebra {

using ConditionFunctionForTermsWithDetails = std::function<bool(TermWithDetails const&)>;
using VariableToValueMap = std::map<std::string, AlbaNumber>;
void retrieveTermsFromTermsWithDetails(Terms& terms, TermsWithDetails const& termsWithDetails);
AlbaNumber getCoefficientOfMonomialWithNoVariables(Polynomial const& polynomial);
AlbaNumber getCoefficientOfMonomialWithVariableOnly(Polynomial const& polynomial, std::string const& variableName);
Terms retrieveSubExpressionsAndSubFunctions(Term const& term);
Terms retrieveSubTerms(Term const& term);

TermsWithDetails retrieveTermsWithDetailsThatSatisfiesCondition(
    TermsWithDetails const& termsWithDetails, ConditionFunctionForTermsWithDetails const& conditionFunction);

VariableToValueMap getCoefficientsForVariablesOnly(Polynomial const& polynomial);
bool hasAnyFunctions(Term const& term);
bool hasAnyTrigonometricFunctions(Term const& term);
bool isVariableFoundInTerm(Term const& term, std::string const& variableName);

}  // namespace alba::algebra
