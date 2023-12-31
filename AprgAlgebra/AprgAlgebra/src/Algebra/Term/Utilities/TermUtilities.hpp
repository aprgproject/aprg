#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>
#include <Common/Math/Number/AlbaNumberTypes.hpp>

namespace alba::algebra {

AlbaNumber getConstantFactor(Term const& term);
AlbaNumber getDegree(Term const& term);

AlbaNumberPairs evaluateAndGetInputOutputPair(
    AlbaNumbers const& numbers, std::string const& variableName, Term const& term);

Expression negateExpression(Expression const& expression);
Term getPiAsATerm();
Term getEAsATerm();
Term getPositiveInfinityAsATerm();
Term getNegativeInfinityAsATerm();
Term convertPositiveTermIfNegative(Term const& term);
Term negateTerm(Term const& term);
Term flipTerm(Term const& term);
Term negateTermIfHasNegativeAssociation(TermWithDetails const& termWithDetails);
Term flipTermIfHasNegativeAssociation(TermWithDetails const& termWithDetails);
Term invertTerm(Term const& term, std::string const& variableName);
int getNumberOfTerms(Term const& term);
bool isTermSimpler(Term const& supposeToBeComplicatedTerm, Term const& supposeToBeSimpleTerm);
bool isNegatedTermSimpler(Term const& term, Term const& negatedTerm);
bool isNonEmptyOrNonOperatorType(Term const& term);
bool isNonEmptyOrNonOperatorOrNonExpressionType(Term const& term);
bool isARadicalTerm(Term const& term);

}  // namespace alba::algebra
