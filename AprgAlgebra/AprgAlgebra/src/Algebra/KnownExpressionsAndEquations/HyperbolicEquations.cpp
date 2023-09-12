#include "HyperbolicEquations.hpp"

#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba::algebra {

Equation getHyperbolicSineDefinition(Term const& term) {
    // sinh(x) = (e^x - e^(-x)) / 2
    Term const leftSideTerm(sinh(term));
    Term const rightSideTerm(createExpressionIfPossible({getEToTheXMinusEToTheNegativeX(term), "/", 2}));
    return {leftSideTerm, "=", rightSideTerm};
}

Equation getHyperbolicCosineDefinition(Term const& term) {
    // cosh(x) = (e^x + e^(-x)) / 2
    Term const leftSideTerm(cosh(term));
    Term const rightSideTerm(createExpressionIfPossible({getEToTheXPlusEToTheNegativeX(term), "/", 2}));
    return {leftSideTerm, "=", rightSideTerm};
}

Equation getHyperbolicTangentDefinition(Term const& term) {
    // tanh(x) = (e^x - e^(-x)) / (e^x + e^(-x))
    Term const leftSideTerm(tanh(term));
    Term const rightSideTerm(
        createExpressionIfPossible({getEToTheXMinusEToTheNegativeX(term), "/", getEToTheXPlusEToTheNegativeX(term)}));
    return {leftSideTerm, "=", rightSideTerm};
}

Equation getHyperbolicCosecantDefinition(Term const& term) {
    // csch(x) = 2 / (e^x - e^(-x))
    Term const leftSideTerm(csch(term));
    Term const rightSideTerm(createExpressionIfPossible({2, "/", getEToTheXMinusEToTheNegativeX(term)}));
    return {leftSideTerm, "=", rightSideTerm};
}

Equation getHyperbolicSecantDefinition(Term const& term) {
    // sech(x) = 2 / (e^x + e^(-x))
    Term const leftSideTerm(sech(term));
    Term const rightSideTerm(createExpressionIfPossible({2, "/", getEToTheXPlusEToTheNegativeX(term)}));
    return {leftSideTerm, "=", rightSideTerm};
}

Equation getHyperbolicCotangentDefinition(Term const& term) {
    // coth(x) = (e^x + e^(-x)) / (e^x - e^(-x))
    Term const leftSideTerm(coth(term));
    Term const rightSideTerm(
        createExpressionIfPossible({getEToTheXPlusEToTheNegativeX(term), "/", getEToTheXMinusEToTheNegativeX(term)}));
    return {leftSideTerm, "=", rightSideTerm};
}

Equation getHyperbolicFunctionIdentityEquation(Term const& term) {
    // cosh(x)^2 - sinh(x)^2 = 1
    Term const leftSideTerm(createExpressionIfPossible({cosh(term), "^", 2, "-", sinh(term), "^", 2}));
    return {leftSideTerm, "=", 1};
}

Equation getEToTheXFromHyperbolicFunctionsEquation(Term const& term) {
    // e^x = cosh(x) + sinh(x)
    Term const leftSideTerm(getEToTheX(term));
    Term const rightSideTerm(createExpressionIfPossible({cosh(term), "+", sinh(term)}));
    return {leftSideTerm, "=", rightSideTerm};
}

Equation getEToTheNegativeXFromHyperbolicFunctionsEquation(Term const& term) {
    // e^(-x) = cosh(x) - sinh(x)
    Term const leftSideTerm(getEToTheNegativeX(term));
    Term const rightSideTerm(createExpressionIfPossible({cosh(term), "-", sinh(term)}));
    return {leftSideTerm, "=", rightSideTerm};
}

Equation getHyperbolicArcSineDefinition(Term const& term) {
    Term const leftSideTerm(arcsinh(term));
    Term const insideSquareRoot(createExpressionIfPossible({term, "^", 2, "+", 1}));
    Term const squareRootTerm(createExpressionIfPossible({insideSquareRoot, "^", AlbaNumber::createFraction(1, 2)}));
    Term const insideLogarithm(createExpressionIfPossible({term, "+", squareRootTerm}));
    Term const rightSideTerm(ln(insideLogarithm));
    return {leftSideTerm, "=", rightSideTerm};
}

Equation getHyperbolicArcCosineDefinition(Term const& term) {
    Term const leftSideTerm(arccosh(term));
    Term const insideSquareRoot(createExpressionIfPossible({term, "^", 2, "-", 1}));
    Term const squareRootTerm(createExpressionIfPossible({insideSquareRoot, "^", AlbaNumber::createFraction(1, 2)}));
    Term const insideLogarithm(createExpressionIfPossible({term, "+", squareRootTerm}));
    Term const rightSideTerm(ln(insideLogarithm));
    return {leftSideTerm, "=", rightSideTerm};
}

Equation getHyperbolicArcTangentDefinition(Term const& term) {
    Term const leftSideTerm(arctanh(term));
    Term const oneMinusTerm(createExpressionIfPossible({1, "-", term}));
    Term const onePlusTerm(createExpressionIfPossible({1, "+", term}));
    Term const insideLogarithm(createExpressionIfPossible({oneMinusTerm, "/", onePlusTerm}));
    Term const logarithmTerm(ln(insideLogarithm));
    Term const rightSideTerm(createExpressionIfPossible({AlbaNumber::createFraction(1, 2), "*", logarithmTerm}));
    return {leftSideTerm, "=", rightSideTerm};
}

Equation getHyperbolicArcCotangentDefinition(Term const& term) {
    Term const leftSideTerm(arccoth(term));
    Term const termPlusOne(createExpressionIfPossible({term, "+", 1}));
    Term const termMinusOne(createExpressionIfPossible({term, "-", 1}));
    Term const insideLogarithm(createExpressionIfPossible({termPlusOne, "/", termMinusOne}));
    Term const logarithmTerm(ln(insideLogarithm));
    Term const rightSideTerm(createExpressionIfPossible({AlbaNumber::createFraction(1, 2), "*", logarithmTerm}));
    return {leftSideTerm, "=", rightSideTerm};
}

Term getEToTheX(Term const& term) {
    // e^x
    return {createExpressionIfPossible({getEAsATerm(), "^", term})};
}

Term getEToTheNegativeX(Term const& term) {
    // e^(-x)
    return {createExpressionIfPossible({getEAsATerm(), "^", negateTerm(term)})};
}

Term getEToTheXPlusEToTheNegativeX(Term const& term) {
    // e^x + e^(-x)
    return {createExpressionIfPossible({getEToTheX(term), "+", getEToTheNegativeX(term)})};
}

Term getEToTheXMinusEToTheNegativeX(Term const& term) {
    // e^x - e^(-x)
    return {createExpressionIfPossible({getEToTheX(term), "-", getEToTheNegativeX(term)})};
}

Term getHyperbolicSineOfSumOfTwoTerms(Term const& term1, Term const& term2) {
    // sinh(x + y) =  sinh(x)*cosh(y) + cosh(x)*sinh(y)
    Term const firstPart(createExpressionIfPossible({sinh(term1), "*", cosh(term2)}));
    Term const secondPart(createExpressionIfPossible({cosh(term1), "*", sinh(term2)}));
    return {createExpressionIfPossible({firstPart, "+", secondPart})};
}

Term getHyperbolicCosineOfSumOfTwoTerms(Term const& term1, Term const& term2) {
    // cosh(x + y) =  cosh(x)*cosh(y) + sinh(x)*sinh(y)
    Term const firstPart(createExpressionIfPossible({cosh(term1), "*", cosh(term2)}));
    Term const secondPart(createExpressionIfPossible({sinh(term1), "*", sinh(term2)}));
    return {createExpressionIfPossible({firstPart, "+", secondPart})};
}

Term getHyperbolicSineOfDoubledValue(Term const& term) {
    // sinh(2*x) =  2*sinh(x)*cosh(x)
    return {createExpressionIfPossible({2, "*", sinh(term), "*", cosh(term)})};
}

Term getHyperbolicCosineOfDoubledValue(Term const& term) {
    // cosh(2*x) =  cosh(x)^2 + sinh(x)^2
    return {createExpressionIfPossible({cosh(term), "^", 2, "+", sinh(term), "^", 2})};
}

Term getHyperbolicSineOfHalvedValue(Term const& term, bool const isPositiveRoot) {
    // sinh(x/2) =  +- ((cosh(x)-1)/2)^(1/2)
    Term const numerator(createExpressionIfPossible({cosh(term), "-", 1}));
    Term const insideSquareRoot(createExpressionIfPossible({numerator, "/", 2}));
    Term result(createExpressionIfPossible({insideSquareRoot, "^", AlbaNumber::createFraction(1, 2)}));
    if (!isPositiveRoot) {
        result = Term(createExpressionIfPossible({-1, "*", result}));
    }
    return result;
}

Term getHyperbolicCosineOfHalvedValue(Term const& term) {
    // sinh(x/2) = ((cosh(x)+1)/2)^(1/2)
    Term const numerator(createExpressionIfPossible({cosh(term), "+", 1}));
    Term const insideSquareRoot(createExpressionIfPossible({numerator, "/", 2}));
    Term result(createExpressionIfPossible({insideSquareRoot, "^", AlbaNumber::createFraction(1, 2)}));
    return result;
}

}  // namespace alba::algebra
