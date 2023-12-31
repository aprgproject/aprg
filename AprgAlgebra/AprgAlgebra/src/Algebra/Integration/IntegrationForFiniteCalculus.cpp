#include "IntegrationForFiniteCalculus.hpp"

#include <Algebra/Constructs/TermRaiseToTerms.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Integration/IntegrationUtilities.hpp>
#include <Algebra/Retrieval/VariableNamesRetriever.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToTerms.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Algebra/Utilities/KnownNames.hpp>
#include <Common/Math/Helpers/CombinatoricsHelpers.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>
#include <Common/Math/Number/AlbaNumberConstants.hpp>

#include <algorithm>

using namespace alba::AlbaNumberConstants;
using namespace alba::algebra::Functions;
using namespace alba::mathHelper;
using namespace std;

namespace alba::algebra {

IntegrationForFiniteCalculus::IntegrationForFiniteCalculus(string const& nameOfVariableToIntegrate)
    : m_nameOfVariableToIntegrate(nameOfVariableToIntegrate) {}

IntegrationForFiniteCalculus::IntegrationForFiniteCalculus(string&& nameOfVariableToIntegrate)
    : m_nameOfVariableToIntegrate(nameOfVariableToIntegrate) {}

Monomial IntegrationForFiniteCalculus::integrateConstant(Constant const& constant) const {
    return {constant.getNumber(), {{m_nameOfVariableToIntegrate, 1}}};
}

Polynomial IntegrationForFiniteCalculus::integrateVariable(Variable const& variable) const {
    Polynomial result;
    string const& nameOfVariable(variable.getVariableName());
    if (isVariableToIntegrate(nameOfVariable)) {
        result = Polynomial{
            Monomial(AlbaNumber::createFraction(1, 2), {{variable.getVariableName(), 2}}),
            Monomial(AlbaNumber::createFraction(-1, 2), {{variable.getVariableName(), 1}})};
    } else {
        result = Polynomial{Monomial(1, {{variable.getVariableName(), 1}, {m_nameOfVariableToIntegrate, 1}})};
    }
    return result;
}

Term IntegrationForFiniteCalculus::integrate(Term const& term) const { return integrateTerm(term); }
Term IntegrationForFiniteCalculus::integrate(Constant const& constant) const { return integrateConstant(constant); }

Term IntegrationForFiniteCalculus::integrate(Variable const& variable) const {
    Term result(integrateVariable(variable));
    result.simplify();
    return result;
}

Term IntegrationForFiniteCalculus::integrate(Monomial const& monomial) const {
    Term result(integrateMonomial(monomial));
    result.simplify();
    return result;
}

Term IntegrationForFiniteCalculus::integrate(Polynomial const& polynomial) const {
    Term result(integratePolynomial(polynomial));
    result.simplify();
    return result;
}

Term IntegrationForFiniteCalculus::integrate(Expression const& expression) const {
    return integrateExpression(expression);
}

Term IntegrationForFiniteCalculus::integrateWithPlusC(Term const& term) const {
    Term result(createExpressionIfPossible({integrateTerm(term), "+", C}));
    result.simplify();
    return result;
}

Term IntegrationForFiniteCalculus::integrateAtDefiniteValues(
    Term const& term, AlbaNumber const& lowerEnd, AlbaNumber const& higherEnd) const {
    return evaluateValuesAndGetDifference(integrateTerm(term), m_nameOfVariableToIntegrate, lowerEnd, higherEnd);
}

Term IntegrationForFiniteCalculus::integrateTerm(Term const& term) const {
    Term result;
    if (term.isConstant()) {
        result = integrate(term.getAsConstant());
    } else if (term.isVariable()) {
        result = integrate(term.getAsVariable());
    } else if (term.isMonomial()) {
        result = integrate(term.getAsMonomial());
    } else if (term.isPolynomial()) {
        result = integrate(term.getAsPolynomial());
    } else if (term.isExpression()) {
        result = integrate(term.getAsExpression());
    } else if (term.isFunction()) {
        result = integrate(term.getAsFunction());
    }
    return result;
}

Term IntegrationForFiniteCalculus::integrateMonomial(Monomial const& monomial) const {
    Term result;
    AlbaNumber const exponent(monomial.getExponentForVariable(m_nameOfVariableToIntegrate));
    if (exponent.isIntegerType()) {
        int const exponentInteger(static_cast<int>(exponent.getInteger()));
        if (exponentInteger >= 0) {
            Polynomial const polynomialInFallingPower(
                convertMonomialWithPositiveExponentsFromRegularPowerToFallingPower(monomial));
            Polynomial const integratedPolynomialInFallingPower(
                integratePolynomialInFallingPower(polynomialInFallingPower));
            Polynomial const integratedPolynomial(convertPolynomialWithPositiveExponentsFromFallingPowerToRegularPower(
                integratedPolynomialInFallingPower));
            result = integratedPolynomial;
        } else if (exponentInteger == -1) {
            // this is special case
            // in infinite calculus this ln(x), but in finite calculus its the summation of 1/x (this is called the
            // harmonic number) for the proof, consider doing the derivative of this
            Monomial monomialToRetain(monomial);
            monomialToRetain.putVariableWithExponent(m_nameOfVariableToIntegrate, 0);
            result = createExpressionIfPossible({monomialToRetain, "*", harmonicNumber(m_nameOfVariableToIntegrate)});
            result.simplify();
        } else {
            AlbaNumber const exponentAbsoluteValue(getAbsoluteValue(exponent));
            Monomial monomialWithOneLessExponent(monomial);
            monomialWithOneLessExponent.putVariableWithExponent(m_nameOfVariableToIntegrate, exponentAbsoluteValue - 1);
            Polynomial const denominatorInFallingPower(
                convertMonomialWithPositiveExponentsFromRegularPowerToFallingPower(monomialWithOneLessExponent));
            Term const termToIntegrate(createExpressionIfPossible({1, "/", denominatorInFallingPower}));
            Term const integratedTermInFallingPower(integrateTerm(termToIntegrate));
            if (!isNan(integratedTermInFallingPower) && canBeConvertedToPolynomial(integratedTermInFallingPower)) {
                Polynomial const integratedPolynomial(
                    convertPolynomialWithPositiveExponentsFromFallingPowerToRegularPower(
                        createPolynomialIfPossible(integratedTermInFallingPower)));
                result = integratedPolynomial;
            } else {
                result = ALBA_NUMBER_NOT_A_NUMBER;
            }
        }
    } else {
        result = ALBA_NUMBER_NOT_A_NUMBER;
    }
    return result;
}

Term IntegrationForFiniteCalculus::integratePolynomial(Polynomial const& polynomial) const {
    Term result;
    auto const& monomials(polynomial.getMonomials());
    if (!monomials.empty()) {
        result = integrateMonomial(monomials.front());
        for (auto it = monomials.cbegin() + 1; it != monomials.cend(); ++it) {
            result = result + integrateMonomial(*it);
        }
        result.simplify();
    }
    return result;
}

Term IntegrationForFiniteCalculus::integrateExpression(Expression const& expression) const {
    return integrateAsTermOrExpressionIfNeeded(expression);
}

Term IntegrationForFiniteCalculus::integrate(Function const& functionObject) {
    return integrateFunction(functionObject);
}

Monomial IntegrationForFiniteCalculus::integrateMonomialInFallingPower(Monomial const& monomial) const {
    Monomial result(monomial);
    bool hasVariabletoIntegrate(false);
    for (auto const& [variableName, exponent] : monomial.getVariablesToExponentsMap()) {
        if (isVariableToIntegrate(variableName)) {
            result.putVariableWithExponent(variableName, exponent + 1);
            result.divideNumber(exponent + 1);
            hasVariabletoIntegrate = true;
        }
    }
    if (!hasVariabletoIntegrate) {
        result.putVariableWithExponent(m_nameOfVariableToIntegrate, 1);
    }
    result.simplify();
    return result;
}

Polynomial IntegrationForFiniteCalculus::integratePolynomialInFallingPower(Polynomial const& polynomial) const {
    Polynomial result;
    for (Monomial const& monomial : polynomial.getMonomials()) {
        result.addMonomial(integrateMonomialInFallingPower(monomial));
    }
    result.simplify();
    return result;
}

Polynomial IntegrationForFiniteCalculus::convertMonomialWithPositiveExponentsFromRegularPowerToFallingPower(
    Monomial const& monomial) const {
    Polynomial result;
    int const exponent(static_cast<int>(monomial.getExponentForVariable(m_nameOfVariableToIntegrate).getInteger()));
    if (exponent >= 0) {
        int const exponentUnsigned = static_cast<int>(exponent);
        Monomial monomialToRetain(monomial);
        monomialToRetain.putVariableWithExponent(m_nameOfVariableToIntegrate, 0);
        for (int i = 0; i <= exponentUnsigned; ++i) {
            result.addMonomial(
                Monomial(getStirlingNumberOfTheSecondKind(exponentUnsigned, i), {{m_nameOfVariableToIntegrate, i}}));
        }
        result.multiplyMonomial(monomialToRetain);
    }
    result.simplify();
    return result;
}

Polynomial IntegrationForFiniteCalculus::convertMonomialWithPositiveExponentsFromFallingPowerToRegularPower(
    Monomial const& monomial) const {
    Polynomial result;
    int const exponent(static_cast<int>(monomial.getExponentForVariable(m_nameOfVariableToIntegrate).getInteger()));
    if (exponent > 0) {
        int const exponentUnsigned = static_cast<int>(exponent);
        result = createPolynomialFromNumber(1);
        Monomial monomialToRetain(monomial);
        monomialToRetain.putVariableWithExponent(m_nameOfVariableToIntegrate, 0);
        for (int i = 0; i < exponentUnsigned; ++i) {
            result.multiplyPolynomial(
                Polynomial{Monomial(1, {{m_nameOfVariableToIntegrate, 1}}), Monomial(-AlbaNumber(i), {})});
        }
        result.multiplyMonomial(monomialToRetain);
    }
    result.simplify();
    return result;
}

Polynomial IntegrationForFiniteCalculus::convertPolynomialWithPositiveExponentsFromRegularPowerToFallingPower(
    Polynomial const& polynomial) const {
    Polynomial result;
    for (Monomial const& monomial : polynomial.getMonomials()) {
        result.addPolynomial(convertMonomialWithPositiveExponentsFromRegularPowerToFallingPower(monomial));
    }
    result.simplify();
    return result;
}

Polynomial IntegrationForFiniteCalculus::convertPolynomialWithPositiveExponentsFromFallingPowerToRegularPower(
    Polynomial const& polynomial) const {
    Polynomial result;
    for (Monomial const& monomial : polynomial.getMonomials()) {
        result.addPolynomial(convertMonomialWithPositiveExponentsFromFallingPowerToRegularPower(monomial));
    }
    result.simplify();
    return result;
}

Term IntegrationForFiniteCalculus::integrateAsTermOrExpressionIfNeeded(Expression const& expression) const {
    Term result;
    Term simplifiedTerm(expression);
    simplifiedTerm.simplify();
    if (simplifiedTerm.isExpression()) {
        result = integrateSimplifiedExpressionOnly(simplifiedTerm.getAsExpression());
    } else {
        result = integrate(simplifiedTerm);
    }
    return result;
}

Term IntegrationForFiniteCalculus::integrateSimplifiedExpressionOnly(Expression const& expression) const {
    Term result;
    if (OperatorLevel::AdditionAndSubtraction == expression.getCommonOperatorLevel()) {
        result = integrateTermsInAdditionOrSubtraction(expression);
    } else if (OperatorLevel::MultiplicationAndDivision == expression.getCommonOperatorLevel()) {
        result = integrateTermsInMultiplicationOrDivision(expression);
    } else if (OperatorLevel::RaiseToPower == expression.getCommonOperatorLevel()) {
        result = integrateTermsInRaiseToPower(expression);
    }
    if (result.isEmpty()) {
        result = ALBA_NUMBER_NOT_A_NUMBER;
    }
    return result;
}

Term IntegrationForFiniteCalculus::integrateTermsInAdditionOrSubtraction(Expression const& expression) const {
    TermsWithDetails const& termsWithDetails(expression.getTermsWithAssociation().getTermsWithDetails());
    Expression accumulatedExpression(createOrCopyExpressionFromATerm(0));
    for (TermWithDetails const& termWithDetails : termsWithDetails) {
        Term const& currentTerm(getTermConstReferenceFromUniquePointer(termWithDetails.baseTermPointer));
        Term const integratedTerm(integrate(currentTerm));
        if (termWithDetails.hasPositiveAssociation()) {
            accumulatedExpression.putTermWithAdditionIfNeeded(integratedTerm);
        } else {
            accumulatedExpression.putTermWithSubtractionIfNeeded(integratedTerm);
        }
    }
    return {accumulatedExpression};
}

Term IntegrationForFiniteCalculus::integrateTermsInMultiplicationOrDivision(Expression const& expression) const {
    TermsWithDetails const& termsWithDetails(expression.getTermsWithAssociation().getTermsWithDetails());
    Term result(ALBA_NUMBER_NOT_A_NUMBER);
    integrateNonChangingAndChangingTermsInMultiplicationOrDivision(result, termsWithDetails);
    return result;
}

Term IntegrationForFiniteCalculus::integrateTermsInRaiseToPower(Expression const& expression) const {
    TermsWithDetails const& termsWithDetails(expression.getTermsWithAssociation().getTermsWithDetails());
    Term result;
    TermRaiseToTerms termRaiseToTerms(termsWithDetails);
    termRaiseToTerms.simplify();
    Term const firstTerm(termRaiseToTerms.getBase());
    Term const secondTerm(termRaiseToTerms.getCombinedExponents());
    bool const isFirstAChangingTerm = isChangingTerm(firstTerm);
    bool const isSecondAChangingTerm = isChangingTerm(secondTerm);
    if (!isFirstAChangingTerm && !isSecondAChangingTerm) {
        result = termRaiseToTerms.getCombinedTerm() * m_nameOfVariableToIntegrate;
    } else if (!isFirstAChangingTerm && isSecondAChangingTerm) {
        result = integrateNonChangingTermRaiseToChangingTerm(firstTerm, secondTerm);
    } else if (isFirstAChangingTerm && !isSecondAChangingTerm) {
        result = integrateChangingTermRaiseToNonChangingTerm(firstTerm, secondTerm);
    } else {
        result = integrateChangingTermRaiseToChangingTerm(firstTerm, secondTerm);
    }
    return result;
}

Term IntegrationForFiniteCalculus::integrateNonChangingTermRaiseToChangingTerm(
    Term const& base, Term const& exponent) const {
    Term result(ALBA_NUMBER_NOT_A_NUMBER);
    // Process:
    // Dx(c^x) = c^(x+1) - c^x
    // Dx(c^x) = (c-1) * (c^x)
    // Using fundamental theorem of calculus:
    // c^x = Integrate((c-1) * (c^x))
    // c^x = (c-1) * Integrate((c^x))
    // (c^x)/(c-1) = Integrate((c^x))
    // Integrate((c^x)) = (c^x)/(c-1)
    Term nPlusOne(Polynomial{Monomial(1, {{m_nameOfVariableToIntegrate, 1}}), Monomial(1, {})});
    SubstitutionOfVariablesToTerms const substitution{{m_nameOfVariableToIntegrate, nPlusOne}};
    Term const exponentWithNPlusOneSubstitution(substitution.performSubstitutionTo(exponent));
    Term const exponentDifference(exponentWithNPlusOneSubstitution - exponent);

    if (!isChangingTerm(exponentDifference)) {
        // if exponentDifference can be factored out
        Term denominator(createExpressionIfPossible({base, "^", exponentDifference, "-", 1}));
        denominator.simplify();
        result = createExpressionIfPossible({base, "^", exponent, "/", denominator});
    }
    return result;
}

bool IntegrationForFiniteCalculus::isVariableToIntegrate(string const& variableName) const {
    return variableName == m_nameOfVariableToIntegrate;
}

bool IntegrationForFiniteCalculus::isChangingTerm(Term const& term) const {
    VariableNamesRetriever retriever;
    retriever.retrieveFromTerm(term);
    VariableNamesSet const& variableNames(retriever.getVariableNames());
    return any_of(variableNames.cbegin(), variableNames.cend(), [&](string const& variableName) {
        return isVariableToIntegrate(variableName);
    });
}

void IntegrationForFiniteCalculus::integrateNonChangingAndChangingTermsInMultiplicationOrDivision(
    Term& result, TermsWithDetails const& termsWithDetails) const {
    TermsWithDetails nonChangingTerms;
    TermsWithDetails changingTerms;
    segregateNonChangingAndChangingTerms(termsWithDetails, nonChangingTerms, changingTerms);
    if (nonChangingTerms.empty()) {
        integrateChangingTermsInMultiplicationOrDivision(result, changingTerms);
    } else {
        Term const nonChangingTermCombined(createTermWithMultiplicationAndDivisionTermsWithDetails(nonChangingTerms));
        Term const changingTermCombined(createTermWithMultiplicationAndDivisionTermsWithDetails(changingTerms));
        Term const integratedChangingTerm(integrateTerm(changingTermCombined));
        if (isNan(integratedChangingTerm)) {
            result = ALBA_NUMBER_NOT_A_NUMBER;
        } else {
            result = nonChangingTermCombined * integratedChangingTerm;
        }
    }
}

void IntegrationForFiniteCalculus::segregateNonChangingAndChangingTerms(
    TermsWithDetails const& termsToSegregate, TermsWithDetails& nonChangingTerms,
    TermsWithDetails& changingTerms) const {
    for (TermWithDetails const& termToSegregate : termsToSegregate) {
        Term const& term(getTermConstReferenceFromUniquePointer(termToSegregate.baseTermPointer));
        if (isChangingTerm(term)) {
            changingTerms.emplace_back(termToSegregate);
        } else {
            nonChangingTerms.emplace_back(termToSegregate);
        }
    }
}

void IntegrationForFiniteCalculus::integrateChangingTermsInMultiplicationOrDivision(
    Term& result, TermsWithDetails const&) {
    // no impl
    result = ALBA_NUMBER_NOT_A_NUMBER;
}

Term IntegrationForFiniteCalculus::integrateFunction(Function const&) { return ALBA_NUMBER_NOT_A_NUMBER; }

Term IntegrationForFiniteCalculus::integrateChangingTermRaiseToNonChangingTerm(Term const&, Term const&) {
    return ALBA_NUMBER_NOT_A_NUMBER;
}

Term IntegrationForFiniteCalculus::integrateChangingTermRaiseToChangingTerm(Term const&, Term const&) {
    return ALBA_NUMBER_NOT_A_NUMBER;
}

}  // namespace alba::algebra
