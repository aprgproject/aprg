#include "ConvertHelpers.hpp"

#include <Algebra/Simplification/SimplificationOfFunctionToTerm.hpp>
#include <Algebra/Term/Utilities/MonomialHelpers.hpp>
#include <Algebra/Term/Utilities/PolynomialHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

using namespace alba::algebra::Simplification;
using namespace std;

namespace alba::algebra {

Operator reverse(Operator const& operatorToReverse) {
    if (operatorToReverse.isAddition()) {
        return {"-"};
    }
    if (operatorToReverse.isSubtraction()) {
        return {"+"};
    }
    if (operatorToReverse.isMultiplication()) {
        return {"/"};
    }
    if (operatorToReverse.isDivision()) {
        return {"*"};
    }
    return {};
}

Term simplifyAndConvertMonomialToSimplestTerm(Monomial const& monomial) {
    Monomial newMonomial(monomial);
    newMonomial.simplify();
    return convertMonomialToSimplestTerm(newMonomial);
}

Term simplifyAndConvertPolynomialToSimplestTerm(Polynomial const& polynomial) {
    Polynomial newPolynomial(polynomial);
    newPolynomial.simplify();
    return convertPolynomialToSimplestTerm(newPolynomial);
}

Term simplifyAndConvertExpressionToSimplestTerm(Expression const& expression) {
    Expression newExpression(expression);
    newExpression.simplify();
    return convertExpressionToSimplestTerm(newExpression);
}

Term simplifyAndConvertFunctionToSimplestTerm(Function const& functionObject) {
    Function newFunction(functionObject);
    newFunction.simplify();
    return convertFunctionToSimplestTerm(newFunction);
}

Term convertMonomialToSimplestTerm(Monomial const& monomial) {
    Term newTerm(monomial);
    if (isTheValue(monomial, 0)) {
        newTerm = 0;
    } else if (isConstantOnly(monomial)) {
        newTerm = monomial.getCoefficient();
    } else if (isVariableOnly(monomial)) {
        newTerm = getFirstVariableName(monomial);
    }
    return newTerm;
}

Term convertPolynomialToSimplestTerm(Polynomial const& polynomial) {
    Term newTerm(polynomial);
    if (isTheValue(polynomial, 0)) {
        newTerm = Term(0);
    } else if (isOneMonomial(polynomial)) {
        newTerm = simplifyAndConvertMonomialToSimplestTerm(getFirstMonomial(polynomial));
    }
    return newTerm;
}

Term convertExpressionToSimplestTerm(Expression const& expression) {
    Term newTerm(expression);
    if (expression.isEmpty()) {
        newTerm.clear();
    } else if (expression.containsOnlyOnePositivelyAssociatedTerm()) {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-static-cast-downcast)
        Term const& term = static_cast<Term const&>(expression.getFirstTerm());
        newTerm = term;
        newTerm.simplify();
    }
    return newTerm;
}

Term convertFunctionToSimplestTerm(Function const& functionObject) {
    SimplificationOfFunctionToTerm const simplification;
    return alba::algebra::Simplification::SimplificationOfFunctionToTerm::simplifyToTerm(functionObject);
}

bool canBeConvertedToConstant(Polynomial const& polynomial) {
    return polynomial.isEmpty() || (isOneMonomial(polynomial) && isConstantOnly(getFirstMonomial(polynomial)));
}

bool canBeConvertedToMonomial(Term const& term) {
    TermType const termType(term.getTermType());
    bool isPolynomialWithOneMonomial(false);
    if (term.isPolynomial()) {
        isPolynomialWithOneMonomial = isOneMonomial(term.getAsPolynomial());
    }
    return TermType::Constant == termType || TermType::Variable == termType || TermType::Monomial == termType ||
           isPolynomialWithOneMonomial;
}

bool canBeConvertedToPolynomial(Term const& term) {
    TermType const termType(term.getTermType());
    return TermType::Constant == termType || TermType::Variable == termType || TermType::Monomial == termType ||
           TermType::Polynomial == termType;
}

}  // namespace alba::algebra
