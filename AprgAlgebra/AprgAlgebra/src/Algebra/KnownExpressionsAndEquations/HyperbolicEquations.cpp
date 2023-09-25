#include "HyperbolicEquations.hpp"

#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba::algebra {

Equation getHyperbolicSineDefinition(Term const& term) {
    // sinh(x) = (e^x - e^(-x)) / 2
    return {sinh(term), "=", createExpressionIfPossible({getEToTheXMinusEToTheNegativeX(term), "/", 2})};
}

Equation getHyperbolicCosineDefinition(Term const& term) {
    // cosh(x) = (e^x + e^(-x)) / 2
    return {cosh(term), "=", createExpressionIfPossible({getEToTheXPlusEToTheNegativeX(term), "/", 2})};
}

Equation getHyperbolicTangentDefinition(Term const& term) {
    // tanh(x) = (e^x - e^(-x)) / (e^x + e^(-x))
    return {
        tanh(term), "=",
        createExpressionIfPossible({getEToTheXMinusEToTheNegativeX(term), "/", getEToTheXPlusEToTheNegativeX(term)})};
}

Equation getHyperbolicCosecantDefinition(Term const& term) {
    // csch(x) = 2 / (e^x - e^(-x))
    return {csch(term), "=", createExpressionIfPossible({2, "/", getEToTheXMinusEToTheNegativeX(term)})};
}

Equation getHyperbolicSecantDefinition(Term const& term) {
    // sech(x) = 2 / (e^x + e^(-x))
    return {sech(term), "=", createExpressionIfPossible({2, "/", getEToTheXPlusEToTheNegativeX(term)})};
}

Equation getHyperbolicCotangentDefinition(Term const& term) {
    // coth(x) = (e^x + e^(-x)) / (e^x - e^(-x))
    return {
        coth(term), "=",
        createExpressionIfPossible({getEToTheXPlusEToTheNegativeX(term), "/", getEToTheXMinusEToTheNegativeX(term)})};
}

Equation getHyperbolicFunctionIdentityEquation(Term const& term) {
    // cosh(x)^2 - sinh(x)^2 = 1
    return {createExpressionIfPossible({cosh(term), "^", 2, "-", sinh(term), "^", 2}), "=", 1};
}

Equation getEToTheXFromHyperbolicFunctionsEquation(Term const& term) {
    // e^x = cosh(x) + sinh(x)
    return {getEToTheX(term), "=", createExpressionIfPossible({cosh(term), "+", sinh(term)})};
}

Equation getEToTheNegativeXFromHyperbolicFunctionsEquation(Term const& term) {
    // e^(-x) = cosh(x) - sinh(x)
    return {getEToTheNegativeX(term), "=", createExpressionIfPossible({cosh(term), "-", sinh(term)})};
}

Equation getHyperbolicArcSineDefinition(Term const& term) {
    Term const insideSquareRoot(createExpressionIfPossible({term, "^", 2, "+", 1}));
    Term const squareRootTerm(createExpressionIfPossible({insideSquareRoot, "^", AlbaNumber::createFraction(1, 2)}));
    Term const insideLogarithm(createExpressionIfPossible({term, "+", squareRootTerm}));
    return {arcsinh(term), "=", ln(insideLogarithm)};
}

Equation getHyperbolicArcCosineDefinition(Term const& term) {
    Term const insideSquareRoot(createExpressionIfPossible({term, "^", 2, "-", 1}));
    Term const squareRootTerm(createExpressionIfPossible({insideSquareRoot, "^", AlbaNumber::createFraction(1, 2)}));
    Term const insideLogarithm(createExpressionIfPossible({term, "+", squareRootTerm}));
    return {arccosh(term), "=", ln(insideLogarithm)};
}

Equation getHyperbolicArcTangentDefinition(Term const& term) {
    Term const oneMinusTerm(createExpressionIfPossible({1, "-", term}));
    Term const onePlusTerm(createExpressionIfPossible({1, "+", term}));
    Term const insideLogarithm(createExpressionIfPossible({oneMinusTerm, "/", onePlusTerm}));
    Term const logarithmTerm(ln(insideLogarithm));
    return {arctanh(term), "=", createExpressionIfPossible({AlbaNumber::createFraction(1, 2), "*", logarithmTerm})};
}

Equation getHyperbolicArcCotangentDefinition(Term const& term) {
    Term const termPlusOne(createExpressionIfPossible({term, "+", 1}));
    Term const termMinusOne(createExpressionIfPossible({term, "-", 1}));
    Term const insideLogarithm(createExpressionIfPossible({termPlusOne, "/", termMinusOne}));
    Term const logarithmTerm(ln(insideLogarithm));
    return {arccoth(term), "=", createExpressionIfPossible({AlbaNumber::createFraction(1, 2), "*", logarithmTerm})};
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
