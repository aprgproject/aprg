#pragma once

#include <Algebra/Differentiation/Differentiation.hpp>
#include <Algebra/Differentiation/DifferentiationUtilities.hpp>
#include <Algebra/Integration/Integration.hpp>
#include <Algebra/Integration/IntegrationUtilities.hpp>
#include <Algebra/Limit/Continuity.hpp>
#include <Algebra/Limit/Limit.hpp>
#include <Algebra/Retrieval/VariableNamesRetriever.hpp>
#include <Algebra/Simplification/SimplificationUtilities.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Vector/MathVectorOfTermsUtilitiesTemplateHeaders.hpp>
#include <Common/Math/Angle/AlbaAngle.hpp>
#include <Common/Math/Vector/AlbaMathVectorUtilities.hpp>

#include <algorithm>

namespace alba::algebra::VectorUtilities {

// utilities function
void simplifyForTermInVector(Term& term);

void retrieveWithAndWithoutOtherCoordinates(
    Term& termWithOtherCoordinates, Term& termWithoutOtherCoordinates, Term const& termToAnalyze,
    std::string const& coordinateVariableName, stringHelper::strings const& allCoordinates);

Equation getTangentPlaneOnAPointOfASurface(
    Equation const& surface, ArrayOfThreeStrings const& coordinateVariables, MathVectorOfThreeNumbers const& point);

Equations getPerpendicularLineOnAPointOfASurface(
    Equation const& surface, ArrayOfThreeStrings const& coordinateVariables, MathVectorOfThreeNumbers const& point);

MathVectorOfThreeTerms getNormalOfASurfaceOnAPoint(
    Equation const& surface, ArrayOfThreeStrings const& coordinateVariables, MathVectorOfThreeNumbers const& point);

MathVectorOfThreeTerms getCurl(
    MathVectorOfThreeTerms const& termVector, ArrayOfThreeStrings const& coordinateVariables);

SegregateTermsByConditionInAdditionAndSubtractionRetriever getRetrieverForComparison(
    Term const& termToAnalyze, std::string const& coordinateVariableName,
    stringHelper::strings const& processedCoordinates);

Term getDyOverDx(MathVectorOfTwoTerms const& termVector, std::string const& variableName);

Term getDirectionalDerivativeInTwoDimensions(
    Term const& term, ArrayOfTwoStrings const& coordinateVariables, AlbaAngle const& angleOfDirection);

Term getDirectionalDerivativeInThreeDimensions(
    Term const& term, ArrayOfThreeStrings const& coordinateVariables, MathVectorOfThreeAngles const& coordinateAngles);

Term getLineIntegralOfAClosedNonIntersectingPathUsingGreensTheorem(
    MathVectorOfTwoTerms const& vectorField, ArrayOfTwoStrings const& coordinateVariables,
    DetailsForDefiniteIntegralWithTerms const& xDetailsForLinePath,
    DetailsForDefiniteIntegralWithTerms const& yDetailsForLinePath);

Term getAreaOfAClosedNonIntersectingPathUsingGreensTheorem(
    ArrayOfTwoStrings const& coordinateVariables, MathVectorOfTwoTerms const& linePath,
    DetailsForDefiniteIntegralWithTerms const& linePathIntegralDetails);

bool isDivergenceOfCurlZero(MathVectorOfThreeTerms const& termVector, ArrayOfThreeStrings const& coordinateVariables);

bool isGaussDivergenceTheoremInAPlaneTrue(
    MathVectorOfTwoTerms const& vectorField, MathVectorOfTwoTerms const& regionOfLineIntegral,
    MathVectorOfTwoTerms const& unitOutwardNormal, DetailsForDefiniteIntegralWithTerms const& lineIntegralDetails,
    DetailsForDefiniteIntegralWithTerms const& areaDetailsInX,
    DetailsForDefiniteIntegralWithTerms const& areaDetailsInY, ArrayOfTwoStrings const& coordinateVariables);

bool isStokesTheoremInAPlaneTrue(
    MathVectorOfTwoTerms const& vectorField, MathVectorOfTwoTerms const& regionOfLineIntegral,
    MathVectorOfTwoTerms const& unitTangentVector, DetailsForDefiniteIntegralWithTerms const& lineIntegralDetails,
    DetailsForDefiniteIntegralWithTerms const& areaDetailsInX,
    DetailsForDefiniteIntegralWithTerms const& areaDetailsInY, ArrayOfTwoStrings const& coordinateVariables);

template <size_t SIZE>
bool isContinuousAt(
    MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName, AlbaNumber const& value) {
    using Values = typename MathVectorOfTerms<SIZE>::ValuesInArray;
    Values const& values(termVector.getValues());
    return std::all_of(values.cbegin(), values.cend(), [&](Term const& term) {
        return isContinuousAt(term, variableName, value, LimitAtAValueApproachType::BothSides);
    });
}

template <size_t SIZE>
bool isDifferentiableAt(
    MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName, AlbaNumber const& value) {
    using Values = typename MathVectorOfTerms<SIZE>::ValuesInArray;
    Values const& values(termVector.getValues());
    return std::all_of(values.cbegin(), values.cend(), [&](Term const& term) {
        return isDifferentiableAt(term, variableName, value);
    });
}

template <size_t SIZE>
bool areOriginalAndDerivativeVectorsOrthogonal(MathVectorOfTerms<SIZE> const& termVector) {
    return termVector.getMagnitude().isConstant();
}

template <size_t SIZE>
Term getLengthOfArcDerivative(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName) {
    return differentiate(termVector, variableName).getMagnitude();
}

template <size_t SIZE>
Term getLengthOfArc(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName) {
    Integration integration(variableName);
    return integration.integrate(getLengthOfArcDerivative(termVector, variableName));
}

template <size_t SIZE>
Term getLengthOfArcFromStartToEnd(
    MathVectorOfTerms<SIZE> const& termVector, DetailsForDefiniteIntegralWithTerms const& integralDetails) {
    return evaluateTermsAndGetDifference(
        getLengthOfArc(termVector, integralDetails.variableName), integralDetails.variableName,
        integralDetails.lowerEnd, integralDetails.higherEnd);
}

template <size_t SIZE>
Term getCurvature(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName) {
    MathVectorOfTerms<SIZE> const curvatureVector(getCurvatureVector(termVector, variableName));
    Term result(curvatureVector.getMagnitude());
    simplifyForTermInVector(result);
    return result;
}

template <size_t SIZE>
Term getTermThatYieldsToThisGradient(
    MathVectorOfTerms<SIZE> const& gradient, ArrayOfStrings<SIZE> const& coordinateVariables,
    bool& isExactDifferential) {
    Term result;
    bool isFirst(true);
    isExactDifferential = true;
    Term partForComparison;
    stringHelper::strings processedCoordinates;
    stringHelper::strings const allCoordinates(coordinateVariables.cbegin(), coordinateVariables.cend());
    for (size_t i = 0; isExactDifferential && i < SIZE; ++i) {
        std::string const& coordinateVariableName(coordinateVariables[i]);
        Term termWithOtherCoordinates;
        Term termWithoutOtherCoordinates;
        retrieveWithAndWithoutOtherCoordinates(
            termWithOtherCoordinates, termWithoutOtherCoordinates, gradient.getValueAt(i), coordinateVariableName,
            allCoordinates);
        processedCoordinates.emplace_back(coordinateVariableName);
        Integration integration(coordinateVariableName);
        if (isFirst) {
            partForComparison = integration.integrate(termWithOtherCoordinates);
            isFirst = false;
        } else {
            Term const currentPartForComparison(integration.integrate(termWithOtherCoordinates));
            SegregateTermsByConditionInAdditionAndSubtractionRetriever const retriever1(
                getRetrieverForComparison(partForComparison, coordinateVariableName, processedCoordinates));
            SegregateTermsByConditionInAdditionAndSubtractionRetriever const retriever2(
                getRetrieverForComparison(currentPartForComparison, coordinateVariableName, processedCoordinates));
            isExactDifferential = retriever1.getTermWithCondition() == retriever2.getTermWithCondition();
            if (isExactDifferential) {
                partForComparison = retriever1.getTermWithCondition() + retriever1.getTermWithoutCondition() +
                                    retriever2.getTermWithoutCondition();
            } else {
                break;
            }
        }
        result += integration.integrate(termWithoutOtherCoordinates);
    }
    if (isExactDifferential) {
        result += partForComparison;
    } else {
        result.clear();
    }
    simplifyForTermInVector(result);
    return result;
}

template <size_t SIZE>
Term getPotentialFunctionForVectorFieldGradient(
    MathVectorOfTerms<SIZE> const& gradient, ArrayOfStrings<SIZE> const& coordinateVariables, bool& isConservative) {
    return getTermThatYieldsToThisGradient<SIZE>(gradient, coordinateVariables, isConservative);
}

template <size_t SIZE>
Term getDivergence(MathVectorOfTerms<SIZE> const& termVector, ArrayOfStrings<SIZE> const& coordinateVariables) {
    using Values = typename MathVectorOfTerms<SIZE>::ValuesInArray;
    MathVectorOfTerms<SIZE> const del(getDel<SIZE>(termVector, coordinateVariables));
    Values const& values(del.getValues());
    return std::accumulate(values.cbegin(), values.cend(), Term(0), std::plus<>());
}

template <size_t SIZE>
Term getLaplaceTerm(MathVectorOfTerms<SIZE> const& termVector, ArrayOfStrings<SIZE> const& coordinateVariables) {
    using Values = typename MathVectorOfTerms<SIZE>::ValuesInArray;
    MathVectorOfTerms<SIZE> const del(getDoubleDel<SIZE>(termVector, coordinateVariables));
    Values const& values(del.getValues());
    return std::accumulate(values.cbegin(), values.cend(), Term(0), std::plus<>());
}

template <size_t SIZE>
Term getLineIntegral(
    MathVectorOfTerms<SIZE> const& vectorField, ArrayOfStrings<SIZE> const& coordinateVariables,
    MathVectorOfTerms<SIZE> const& linePath, DetailsForDefiniteIntegralWithTerms const& linePathIntegralDetails) {
    SubstitutionOfVariablesToTerms substitution;
    Differentiation const differentiation(linePathIntegralDetails.variableName);
    for (size_t i = 0; i < SIZE; ++i) {
        substitution.putVariableWithTerm(coordinateVariables[i], linePath.getValueAt(i));
        DerivativeVariableName const derivativeVariableName(1, "", coordinateVariables[i]);
        substitution.putVariableWithTerm(
            derivativeVariableName.getNameInLeibnizNotation(), differentiation.differentiate(linePath.getValueAt(i)));
    }
    MathVectorOfTerms<SIZE> linePathInVectorField;
    for (size_t i = 0; i < SIZE; ++i) {
        linePathInVectorField.getValueReferenceAt(i) = substitution.performSubstitutionTo(vectorField.getValueAt(i));
    }
    MathVectorOfTerms<SIZE> const differentiatedLinePath(differentiate(linePath, linePathIntegralDetails.variableName));
    Term const termIntegrate(getDotProduct(linePathInVectorField, differentiatedLinePath));
    Integration integration(linePathIntegralDetails.variableName);
    return integration.integrateAtDefiniteTerms(
        termIntegrate, linePathIntegralDetails.lowerEnd, linePathIntegralDetails.higherEnd);
}

template <size_t SIZE>
Term getLineIntegralIndependentOfPath(
    MathVectorOfTerms<SIZE> const& vectorField, ArrayOfStrings<SIZE> const& coordinateVariables,
    MathVectorOfNumbers<SIZE> const& lowerValues, MathVectorOfNumbers<SIZE> const& higherValues) {
    bool isConservative(false);
    Term const potential(
        getPotentialFunctionForVectorFieldGradient<SIZE>(vectorField, coordinateVariables, isConservative));

    Term result;
    if (isConservative) {
        SubstitutionOfVariablesToValues substitutionForLowerValues;
        SubstitutionOfVariablesToValues substitutionForHigherValues;
        for (size_t i = 0; i < SIZE; ++i) {
            substitutionForLowerValues.putVariableWithValue(coordinateVariables[i], lowerValues.getValueAt(i));
            substitutionForHigherValues.putVariableWithValue(coordinateVariables[i], higherValues.getValueAt(i));
        }
        result = substitutionForHigherValues.performSubstitutionTo(potential) -
                 substitutionForLowerValues.performSubstitutionTo(potential);
    }
    return result;
}

template <size_t SIZE>
MathVectorOfTerms<SIZE> getLimit(
    MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName, AlbaNumber const& valueToApproach) {
    using Values = typename MathVectorOfTerms<SIZE>::ValuesInArray;
    MathVectorOfTerms<SIZE> result;
    Values const& values(termVector.getValues());
    std::transform(values.cbegin(), values.cend(), result.getValuesReference().begin(), [&](Term const& term) {
        return getLimit(term, variableName, valueToApproach);
    });
    return result;
}

template <size_t SIZE>
MathVectorOfTerms<SIZE> differentiate(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName) {
    using Values = typename MathVectorOfTerms<SIZE>::ValuesInArray;
    MathVectorOfTerms<SIZE> result;
    Differentiation const differentiation(variableName);
    Values const& values(termVector.getValues());
    std::transform(values.cbegin(), values.cend(), result.getValuesReference().begin(), [&](Term const& term) {
        return differentiation.differentiate(term);
    });
    return result;
}

template <size_t SIZE>
MathVectorOfTerms<SIZE> differentiateMultipleTimes(
    MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName, size_t const numberOfTimes) {
    using Values = typename MathVectorOfTerms<SIZE>::ValuesInArray;
    MathVectorOfTerms<SIZE> result;
    Differentiation const differentiation(variableName);
    Values const& values(termVector.getValues());
    std::transform(values.cbegin(), values.cend(), result.getValuesReference().begin(), [&](Term const& term) {
        return differentiation.differentiateMultipleTimes(term, static_cast<int>(numberOfTimes));
    });
    return result;
}

template <size_t SIZE>
MathVectorOfTerms<SIZE> integrate(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName) {
    using Values = typename MathVectorOfTerms<SIZE>::ValuesInArray;
    MathVectorOfTerms<SIZE> result;
    Integration integration(variableName);
    Values const& values(termVector.getValues());
    std::transform(values.cbegin(), values.cend(), result.getValuesReference().begin(), [&](Term const& term) {
        return integration.integrate(term);
    });
    return result;
}

template <size_t SIZE>
MathVectorOfTerms<SIZE> getUnitTangentVector(
    MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName) {
    MathVectorOfTerms<SIZE> result(differentiate(termVector, variableName));
    result /= result.getMagnitude();
    simplifyForTermVector(result);
    return result;
}

template <size_t SIZE>
MathVectorOfTerms<SIZE> getUnitNormalVector(
    MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName) {
    MathVectorOfTerms<SIZE> result(differentiate(getUnitTangentVector(termVector, variableName), variableName));
    result /= result.getMagnitude();
    simplifyForTermVector(result);
    return result;
}

template <size_t SIZE>
MathVectorOfTerms<SIZE> getCurvatureVector(MathVectorOfTerms<SIZE> const& termVector, std::string const& variableName) {
    MathVectorOfTerms<SIZE> const derivativeOfTermVector(differentiate(termVector, variableName));
    MathVectorOfTerms<SIZE> result(differentiate(getUnitTangentVector(termVector, variableName), variableName));
    result /= derivativeOfTermVector.getMagnitude();
    simplifyForTermVector(result);
    return result;
}

template <size_t SIZE>
MathVectorOfTerms<SIZE> getGradient(Term const& term, ArrayOfStrings<SIZE> const& coordinateVariables) {
    MathVectorOfTerms<SIZE> result;
    for (size_t i = 0; i < SIZE; ++i) {
        result.getValueReferenceAt(i) = getPartialDerivative(term, coordinateVariables[i]);
    }
    return result;
}

template <size_t SIZE>
MathVectorOfTerms<SIZE> getDel(
    MathVectorOfTerms<SIZE> const& termVector, ArrayOfStrings<SIZE> const& coordinateVariables) {
    MathVectorOfTerms<SIZE> result(termVector);
    for (size_t i = 0; i < SIZE; ++i) {
        result.getValueReferenceAt(i) = getPartialDerivative(termVector.getValueAt(i), coordinateVariables[i]);
    }
    return result;
}

template <size_t SIZE>
MathVectorOfTerms<SIZE> getDoubleDel(
    MathVectorOfTerms<SIZE> const& termVector, ArrayOfStrings<SIZE> const& coordinateVariables) {
    MathVectorOfTerms<SIZE> result;
    for (size_t i = 0; i < SIZE; ++i) {
        result.getValueReferenceAt(i) = getPartialDerivative(
            getPartialDerivative(termVector.getValueAt(i), coordinateVariables[i]), coordinateVariables[i]);
    }
    return result;
}

template <size_t SIZE>
void simplifyForTermVector(MathVectorOfTerms<SIZE>& termVector) {
    for (Term& term : termVector.getValuesReference()) {
        simplifyForTermInVector(term);
    }
}

}  // namespace alba::algebra::VectorUtilities
