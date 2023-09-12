#include "TrigonometricEquations.hpp"

#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba::algebra {

Equation getTrigonometricPythagoreanIdentity(Term const& term) {
    // sin(x)^2 + cos(x)^2 = 1
    Term const leftSideTerm(createExpressionIfPossible({getSineSquared(term), "+", getCosineSquared(term)}));
    return {leftSideTerm, "=", 1};
}

Equation getSineEquationOfRightTriangle(Term const& angle, Term const& oppositeSideOfAngle, Term const& hypotenuse) {
    // sin(x) = o/h
    Term const leftSideTerm(sin(angle));
    Term const rightSideTerm(createExpressionIfPossible({oppositeSideOfAngle, "/", hypotenuse}));
    return {leftSideTerm, "=", rightSideTerm};
}

Equation getCosineEquationOfRightTriangle(Term const& angle, Term const& adjacentSideOfAngle, Term const& hypotenuse) {
    // cos(x) = a/h
    Term const leftSideTerm(cos(angle));
    Term const rightSideTerm(createExpressionIfPossible({adjacentSideOfAngle, "/", hypotenuse}));
    return {leftSideTerm, "=", rightSideTerm};
}

Equation getTangentEquationOfRightTriangle(
    Term const& angle, Term const& oppositeSideOfAngle, Term const& adjacentSideOfAngle) {
    // (x) = o/a
    Term const leftSideTerm(tan(angle));
    Term const rightSideTerm(createExpressionIfPossible({oppositeSideOfAngle, "/", adjacentSideOfAngle}));
    return {leftSideTerm, "=", rightSideTerm};
}

Equation getLawOfSineEquation(
    Term const& side1, Term const& oppositeAngleOfSide1, Term const& side2, Term const& oppositeAngleOfSide2) {
    // x/sin(angleOppositeOfX) = y/sin(angleOppositeOfY) = z/sin(angleOppositeOfZ)
    Term const leftSideTerm(createExpressionIfPossible({side1, "/", sin(oppositeAngleOfSide1)}));
    Term const rightSideTerm(createExpressionIfPossible({side2, "/", sin(oppositeAngleOfSide2)}));
    return {leftSideTerm, "=", rightSideTerm};
}

Equation getLawOfCosineEquation(
    Term const& side1, Term const& side2, Term const& side3, Term const& oppositeAngleOfSide1) {
    // x^2 = y^2 + z^2 - 2*y*z*cos(angleOppositeOfX)
    Term const side1Squared(createExpressionIfPossible({side1, "^", 2}));
    Term const side2Squared(createExpressionIfPossible({side2, "^", 2}));
    Term const side3Squared(createExpressionIfPossible({side3, "^", 2}));
    Term const cosinePart(createExpressionIfPossible({2, "*", side2, "*", side3, "*", cos(oppositeAngleOfSide1)}));
    Term const& leftSideTerm(side1Squared);
    Term const rightSideTerm(createExpressionIfPossible({side2Squared, "+", side3Squared, "-", cosinePart}));
    return {leftSideTerm, "=", rightSideTerm};
}

Term getSineSquared(Term const& term) {
    // sin(x)^2
    return {createExpressionIfPossible({sin(term), "^", 2})};
}

Term getSineSquaredInCosine(Term const& term) {
    // sin(x)^2 = 1 - cos(x)^2
    return {createExpressionIfPossible({1, "-", cos(term), "^", 2})};
}

Term getCosineSquared(Term const& term) {
    // cos(x)^2
    return {createExpressionIfPossible({cos(term), "^", 2})};
}

Term getCosineSquaredInSine(Term const& term) {
    // cos(x)^2 = 1 - sin(x)^2
    return {createExpressionIfPossible({1, "-", sin(term), "^", 2})};
}

Term getTangentSquared(Term const& term) {
    // tan(x)^2
    return {createExpressionIfPossible({tan(term), "^", 2})};
}

Term getTangentSquaredInSecant(Term const& term) {
    // tan(x)^2 = sec(x)^2 - 1
    return {createExpressionIfPossible({sec(term), "^", 2, "-", 1})};
}

Term getCosecantSquared(Term const& term) {
    // csc(x)^2
    return {createExpressionIfPossible({csc(term), "^", 2})};
}

Term getCosecantSquaredInCotangent(Term const& term) {
    // csc(x)^2 = cot(x)^2 + 1
    return {createExpressionIfPossible({cot(term), "^", 2, "+", 1})};
}

Term getSecantSquared(Term const& term) {
    // sec(x)^2
    return {createExpressionIfPossible({sec(term), "^", 2})};
}

Term getSecantSquaredInTangent(Term const& term) {
    // sec(x)^2 = tan(x)^2 + 1
    return {createExpressionIfPossible({tan(term), "^", 2, "+", 1})};
}

Term getCotangentSquared(Term const& term) {
    // cot(x)^2
    return {createExpressionIfPossible({cot(term), "^", 2})};
}

Term getCotangentSquaredInCosecant(Term const& term) {
    // cot(x)^2 = csc(x)^2 - 1
    return {createExpressionIfPossible({csc(term), "^", 2, "-", 1})};
}

Term getSineOfSumOrDifferenceOfTwoTerms(Term const& term1, Operator const& operatorObject, Term const& term2) {
    // sin(x +- y) =  sin(x)*cos(y) +- cos(x)*sin(y)
    Term result;
    if (operatorObject.isAddition() || operatorObject.isSubtraction()) {
        Term const firstPart(createExpressionIfPossible({sin(term1), "*", cos(term2)}));
        Term const secondPart(createExpressionIfPossible({cos(term1), "*", sin(term2)}));
        result = Term(createExpressionIfPossible({firstPart, operatorObject, secondPart}));
    }
    return result;
}

Term getCosineOfSumOrDifferenceOfTwoTerms(Term const& term1, Operator const& operatorObject, Term const& term2) {
    // cos(x +- y) =  cos(x)*cos(y) -+ sin(x)*sin(y)
    Term result;
    if (operatorObject.isAddition() || operatorObject.isSubtraction()) {
        Term const firstPart(createExpressionIfPossible({cos(term1), "*", cos(term2)}));
        Term const secondPart(createExpressionIfPossible({sin(term1), "*", sin(term2)}));
        result = Term(createExpressionIfPossible({firstPart, reverse(operatorObject), secondPart}));
    }
    return result;
}

Term getTangentOfSumOrDifferenceOfTwoTerms(Term const& term1, Operator const& operatorObject, Term const& term2) {
    // tan(x +- y) =  (tan(x) +- tan(y)) / (1 -+ tan(x)*tan(y))
    Term result;
    if (operatorObject.isAddition() || operatorObject.isSubtraction()) {
        Term const numerator(createExpressionIfPossible({tan(term1), operatorObject, tan(term2)}));
        Term const denominator(createExpressionIfPossible(
            {1, reverse(operatorObject), createExpressionIfPossible({tan(term1), "*", tan(term2)})}));
        result = Term(createExpressionIfPossible({numerator, "/", denominator}));
    }
    return result;
}

Term getSineOfDoubledValue(Term const& term) {
    // sin(2*x) =  2*sin(x)*cos(x)
    return {createExpressionIfPossible({2, "*", sin(term), "*", cos(term)})};
}

Term getCosineOfDoubledValue(Term const& term) {
    // cos(2*x) =  cos(x)^2 - sin(x)^2
    return {createExpressionIfPossible({getCosineSquared(term), "-", getSineSquared(term)})};
}

Term getTangentOfDoubledValue(Term const& term) {
    // tan(2*x) =  (2*tan(x)) / (1-tan(x)^2)
    Term const numerator(createExpressionIfPossible({2, "*", tan(term)}));
    Term const denominator(createExpressionIfPossible({1, "-", getTangentSquared(term)}));
    return {createExpressionIfPossible({numerator, "/", denominator})};
}

Term getSineOfHalvedValue(Term const& term, bool const isPositiveRoot) {
    // sin(x/2) =  +- ((1-cos(x))/2)^(1/2)
    Term result(createExpressionIfPossible({getSineSquaredOfHalvedValue(term), "^", AlbaNumber::createFraction(1, 2)}));
    if (!isPositiveRoot) {
        result = Term(createExpressionIfPossible({-1, "*", result}));
    }
    return result;
}

Term getCosineOfHalvedValue(Term const& term, bool const isPositiveRoot) {
    // cos(x/2) =  +- ((1+cos(x))/2)^(1/2)
    Term result(
        createExpressionIfPossible({getCosineSquaredOfHalvedValue(term), "^", AlbaNumber::createFraction(1, 2)}));
    if (!isPositiveRoot) {
        result = Term(createExpressionIfPossible({-1, "*", result}));
    }
    return result;
}

Term getSineSquaredOfHalvedValue(Term const& term) {
    // sin(x/2)^2 =  +- ((1-cos(x))/2)
    Term const numerator(createExpressionIfPossible({1, "-", cos(term)}));
    return {createExpressionIfPossible({numerator, "/", 2})};
}

Term getCosineSquaredOfHalvedValue(Term const& term) {
    // cos(x/2)^2 =  +- ((1+cos(x))/2)
    Term const numerator(createExpressionIfPossible({1, "+", cos(term)}));
    return {createExpressionIfPossible({numerator, "/", 2})};
}

}  // namespace alba::algebra
