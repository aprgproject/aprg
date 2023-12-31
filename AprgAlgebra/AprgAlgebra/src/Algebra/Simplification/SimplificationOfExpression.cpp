#include "SimplificationOfExpression.hpp"

#include <Algebra/Constructs/AdditionAndSubtractionOfExpressions.hpp>
#include <Algebra/Constructs/MultiplicationAndDivisionOfRadicals.hpp>
#include <Algebra/Constructs/PolynomialOverPolynomial.hpp>
#include <Algebra/Constructs/RationalizeTermOverTerm.hpp>
#include <Algebra/Factorization/FactorizationOfTerm.hpp>
#include <Algebra/Operations/AccumulateOperations.hpp>
#include <Algebra/Simplification/SimplificationUtilities.hpp>
#include <Algebra/Substitution/SubstitutionOfTermsToTerms.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToTerms.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/RetrieveHelpers.hpp>
#include <Algebra/Term/Utilities/SegregateHelpers.hpp>
#include <Algebra/Term/Utilities/StringHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

using namespace alba::algebra::Factorization;
using namespace std;

namespace alba {

namespace algebra::Simplification {

SimplificationOfExpression::SimplificationOfExpression(Expression const& expression) : m_expression(expression) {}
SimplificationOfExpression::SimplificationOfExpression(Expression&& expression) : m_expression(expression) {}
Expression SimplificationOfExpression::getExpression() const { return m_expression; }

void SimplificationOfExpression::simplify() {
    simplifyExpressionUntilNoChangeInitiallyIfNeeded();
    simplifyBySubstitutingExpressionAndFunctionsToVariablesIfNeeded();
    simplifyToACommonDenominatorIfNeeded();
    simplifyExpressionUntilNoChange();
}

bool SimplificationOfExpression::shouldSimplifyToACommonDenominator() {
    return Configuration::getInstance().getConfigurationDetails().shouldSimplifyToACommonDenominator;
}

bool SimplificationOfExpression::shouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase() {
    return Configuration::getInstance()
        .getConfigurationDetails()
        .shouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase;
}

bool SimplificationOfExpression::shouldSimplifyByCombiningRadicalsInMultiplicationAndDivision() {
    return Configuration::getInstance()
        .getConfigurationDetails()
        .shouldSimplifyByCombiningRadicalsInMultiplicationAndDivision;
}

bool SimplificationOfExpression::shouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt() {
    return Configuration::getInstance()
        .getConfigurationDetails()
        .shouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt;
}

bool SimplificationOfExpression::shouldSimplifyByRationalizingNumerator() {
    return Configuration::getInstance().getConfigurationDetails().shouldSimplifyByRationalizingNumerator;
}

bool SimplificationOfExpression::shouldSimplifyByRationalizingDenominator() {
    return Configuration::getInstance().getConfigurationDetails().shouldSimplifyByRationalizingDenominator;
}

bool SimplificationOfExpression::shouldSimplifyBySubstitutingExpressionAndFunctionsToVariables() {
    return Configuration::getInstance()
        .getConfigurationDetails()
        .shouldSimplifyBySubstitutingExpressionAndFunctionsToVariables;
}

bool SimplificationOfExpression::shouldSimplifyToFactors() {
    return Configuration::getInstance().getConfigurationDetails().shouldSimplifyToFactors;
}

bool SimplificationOfExpression::shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue() {
    return Configuration::getInstance()
        .getConfigurationDetails()
        .shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue;
}

bool SimplificationOfExpression::shouldNotSimplifyByDistributingConstantExponentToEachBase() {
    return Configuration::getInstance()
        .getConfigurationDetails()
        .shouldNotSimplifyByDistributingConstantExponentToEachBase;
}

bool SimplificationOfExpression::shouldPerformDebug() {
    return Configuration::getInstance().getConfigurationDetails().shouldPerformDebug;
}

void SimplificationOfExpression::simplifyExpressionUntilNoChange() {
    Expression beforeSimplify;
    do {
        beforeSimplify = m_expression;
        simplifyExpression(m_expression);
    } while (isChangeDetected(beforeSimplify, m_expression));
}

void SimplificationOfExpression::simplifyExpressionUntilNoChangeInitiallyIfNeeded() {
    if (shouldSimplifyToACommonDenominator() || shouldSimplifyBySubstitutingExpressionAndFunctionsToVariables()) {
        convertPolynomialOverPolynomialIfNeeded();
        simplifyExpressionUntilNoChange();
    }
}

void SimplificationOfExpression::simplifyToACommonDenominatorIfNeeded() {
    if (shouldSimplifyToACommonDenominator()) {
        simplifyToACommonDenominatorForExpressionAndReturnIfAdditionOrSubtractionOfTermsOverTermsOccurred(m_expression);
    }
}

void SimplificationOfExpression::simplifyBySubstitutingExpressionAndFunctionsToVariablesIfNeeded() {
    if (shouldSimplifyBySubstitutingExpressionAndFunctionsToVariables()) {
        SimplificationOfExpression::ConfigurationDetails substitutionSimplificationConfigurationDetails(
            Configuration::getInstance().getConfigurationDetails());
        substitutionSimplificationConfigurationDetails.shouldSimplifyToACommonDenominator = true;
        substitutionSimplificationConfigurationDetails.shouldSimplifyBySubstitutingExpressionAndFunctionsToVariables =
            false;

        SimplificationOfExpression::ScopeObject const scopeObject;
        scopeObject.setInThisScopeThisConfiguration(substitutionSimplificationConfigurationDetails);

        while (tryToSubstituteSubExpressionOrSubFunctionAndReturnIfContinue(m_expression)) {
            ;
        }
    }
}

void SimplificationOfExpression::convertPolynomialOverPolynomialIfNeeded() {
    if (shouldSimplifyToACommonDenominator()) {
        convertPolynomialToPolynomialOverPolynomial(m_expression);
    }
}

void SimplificationOfExpression::convertPolynomialToPolynomialOverPolynomial(Term& term) {
    if (term.isPolynomial()) {
        PolynomialOverPolynomial pop(term.getAsPolynomial(), createPolynomialFromNumber(1));
        pop.simplify();
        if (!isTheValue(pop.getDenominator(), 1)) {
            term = createExpressionIfPossible({pop.getNumerator(), "/", pop.getDenominator()});
        }
    } else if (term.isExpression()) {
        convertPolynomialToPolynomialOverPolynomial(term.getAsExpressionReference());
    } else if (term.isFunction()) {
        convertPolynomialToPolynomialOverPolynomial(
            getTermReferenceFromBaseTerm(term.getAsFunctionReference().getInputTermReference()));
    }
}

void SimplificationOfExpression::convertPolynomialToPolynomialOverPolynomial(Expression& expression) {
    TermsWithDetails& termsWithDetails(expression.getTermsWithAssociationReference().getTermsWithDetailsReference());
    for (TermWithDetails& termWithDetails : termsWithDetails) {
        Term& term(getTermReferenceFromUniquePointer(termWithDetails.baseTermPointer));
        convertPolynomialToPolynomialOverPolynomial(term);
    }
}

bool SimplificationOfExpression::tryToSubstituteSubExpressionOrSubFunctionAndReturnIfContinue(
    Expression const& expression) {
    bool continueToTryToSubstitute = false;
    int const oldNumberOfTerms = static_cast<int>(expression.getTermsWithAssociation().getTermsWithDetails().size());
    Terms const expressionAndFunctionTerms(retrieveSubExpressionsAndSubFunctions(expression));
    for (Term const& expressionOrFunctionTerm : expressionAndFunctionTerms) {
        Expression const newExpression(
            getNewExpressionWithSubstitutedVariableForTerm(m_expression, expressionOrFunctionTerm));
        int const newNumberOfTerms =
            static_cast<int>(newExpression.getTermsWithAssociation().getTermsWithDetails().size());
        if (expression.getCommonOperatorLevel() != newExpression.getCommonOperatorLevel() ||
            oldNumberOfTerms != newNumberOfTerms) {
            m_expression = newExpression;
            continueToTryToSubstitute = true;
            break;
        }
    }
    return continueToTryToSubstitute;
}

void SimplificationOfExpression::simplifyExpression(Expression& expression) {
    TermsWithDetails newTermsWithDetails;
    OperatorLevel newOperatorLevel(expression.getCommonOperatorLevel());
    simplifyAndCopyTermsAndChangeOperatorLevelIfNeeded(
        newTermsWithDetails, newOperatorLevel, expression.getTermsWithAssociation().getTermsWithDetails());

    // is clearing the expression and then copying simplified terms the most efficient way?
    expression.clear();
    processTermsBaseOnOperatorLevel(expression, newTermsWithDetails, newOperatorLevel);
}

void SimplificationOfExpression::processTermsBaseOnOperatorLevel(
    Expression& expression, TermsWithDetails const& termsToProcess, OperatorLevel const operatorLevel) {
    switch (operatorLevel) {
        case OperatorLevel::Unknown: {
            expression.putTermsWithDetails(termsToProcess);
            break;
        }
        case OperatorLevel::AdditionAndSubtraction: {
            processAndSaveTermsForAdditionAndSubtraction(expression, termsToProcess);
            break;
        }
        case OperatorLevel::MultiplicationAndDivision: {
            processAndSaveTermsForMultiplicationAndDivision(expression, termsToProcess);
            break;
        }
        case OperatorLevel::RaiseToPower: {
            processAndSaveTermsForRaiseToPower(expression, termsToProcess);
            break;
        }
    }
}

void SimplificationOfExpression::processAndSaveTermsForAdditionAndSubtraction(
    Expression& expression, TermsWithDetails const& termsToProcess) {
    Term combinedTerm;
    TermsWithDetails termsWithNonExpressions;
    TermsWithDetails termsWithExpressions;
    segregateNonExpressionsAndExpressions(termsToProcess, termsWithNonExpressions, termsWithExpressions);
    accumulateTermsForAdditionAndSubtraction(combinedTerm, termsWithNonExpressions);
    addOrSubtractTermsWithExpressions(combinedTerm, termsWithExpressions);
    expression.setTerm(combinedTerm);
}

void SimplificationOfExpression::processAndSaveTermsForMultiplicationAndDivision(
    Expression& expression, TermsWithDetails const& termsToProcess) {
    TermsWithDetails termsInMultiplicationAndDivision(termsToProcess);
    simplifyByCombiningRadicalsInMultiplicationAndDivisionIfNeeded(termsInMultiplicationAndDivision);

    TermsOverTerms termsOverTerms(termsInMultiplicationAndDivision);
    termsOverTerms.setAsShouldSimplifyToFactors(shouldSimplifyToFactors());
    termsOverTerms.setFactorizationConfigurationDetails(getFactorizationConfiguration());
    termsOverTerms.simplify();

    Term const combinedTerm(getCombinedTermAndSimplifyByRationalizingNumeratorOrDenominatorIfNeeded(termsOverTerms));
    expression.setTerm(combinedTerm);
}

void SimplificationOfExpression::processAndSaveTermsForRaiseToPower(
    Expression& expression, TermsWithDetails const& termsToProcess) {
    TermRaiseToTerms termRaiseToTerms(termsToProcess);
    termRaiseToTerms.setAsShouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt(
        shouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt());
    termRaiseToTerms.setAsShouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase(
        shouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase());
    termRaiseToTerms.setAsShouldSimplifyToFactors(shouldSimplifyToFactors());
    termRaiseToTerms.simplify();

    expression.setTerm(getCombinedTermUsingTermsRaiseToTerms(termRaiseToTerms));
}

void SimplificationOfExpression::addOrSubtractTermsWithExpressions(
    Term& combinedTerm, TermsWithDetails const& termsWithExpressions) {
    AdditionAndSubtractionOfExpressions additionAndSubtraction(termsWithExpressions);
    additionAndSubtraction.combineExpressionsIfPossible();
    accumulateTermsForAdditionAndSubtraction(combinedTerm, additionAndSubtraction.getAsTermsWithDetails());
}

void SimplificationOfExpression::simplifyByCombiningRadicalsInMultiplicationAndDivisionIfNeeded(
    TermsWithDetails& termsInMultiplicationAndDivision) {
    if (shouldSimplifyByCombiningRadicalsInMultiplicationAndDivision()) {
        MultiplicationAndDivisionOfRadicals multiplicationAndDivisionOfRadicals(termsInMultiplicationAndDivision);
        multiplicationAndDivisionOfRadicals.simplify();
        termsInMultiplicationAndDivision = multiplicationAndDivisionOfRadicals.getTermsWithDetails();
    }
}

Factorization::ConfigurationDetails SimplificationOfExpression::getFactorizationConfiguration() {
    Factorization::ConfigurationDetails configurationDetails(
        Factorization::Configuration::getInstance().getConfigurationDetails());
    configurationDetails.shouldSimplifyExpressionsToFactors = shouldSimplifyToFactors();
    configurationDetails.shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue =
        shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue();
    return configurationDetails;
}

Expression SimplificationOfExpression::getNewExpressionWithSubstitutedVariableForTerm(
    Term const& mainExpression, Term const& termToSubstitute) {
    string variableNameForSubstitution(createVariableNameForSubstitution(termToSubstitute));

    SubstitutionOfTermsToTerms const substitutionToVariable{{termToSubstitute, variableNameForSubstitution}};
    Term const termWithNewVariable(substitutionToVariable.performSubstitutionTo(mainExpression));

    SubstitutionOfVariablesToTerms const substitutionFromVariable{{variableNameForSubstitution, termToSubstitute}};
    Term const termWithoutNewVariable(substitutionFromVariable.performSubstitutionTo(termWithNewVariable));

    return createOrCopyExpressionFromATerm(termWithoutNewVariable);
}

Term SimplificationOfExpression::getCombinedTermAndSimplifyByRationalizingNumeratorOrDenominatorIfNeeded(
    TermsOverTerms const& termsOverTerms) {
    Term combinedTerm;
    if (shouldSimplifyByRationalizingNumerator()) {
        RationalizeTermOverTerm rationalizeTermOverTerm(
            termsOverTerms.getCombinedNumerator(), termsOverTerms.getCombinedDenominator());
        rationalizeTermOverTerm.rationalizeNumerator();
        combinedTerm = rationalizeTermOverTerm.getCombinedTerm();
    } else if (shouldSimplifyByRationalizingDenominator()) {
        RationalizeTermOverTerm rationalizeTermOverTerm(
            termsOverTerms.getCombinedNumerator(), termsOverTerms.getCombinedDenominator());
        rationalizeTermOverTerm.rationalizeDenominator();
        combinedTerm = rationalizeTermOverTerm.getCombinedTerm();
    } else {
        combinedTerm = termsOverTerms.getCombinedTerm();
    }
    return combinedTerm;
}

Term SimplificationOfExpression::getCombinedTermUsingTermsRaiseToTerms(TermRaiseToTerms const& termRaiseToTerms) {
    Term combinedTerm;
    Term const eachBasesRaisedToConstant(getEachBasesRaisedToConstantIfPossible(termRaiseToTerms));
    if (!eachBasesRaisedToConstant.isEmpty()) {
        combinedTerm = eachBasesRaisedToConstant;
    } else {
        combinedTerm = termRaiseToTerms.getCombinedTerm();
    }
    return combinedTerm;
}

Term SimplificationOfExpression::getEachBasesRaisedToConstantIfPossible(TermRaiseToTerms const& termRaiseToTerms) {
    Term result;
    if (shouldDistributeExponentConstantToEachBase()) {
        Term const& base(termRaiseToTerms.getBase());
        Term const exponent(termRaiseToTerms.getCombinedExponents());
        if (exponent.isConstant() && !isTheValue(exponent, 1)) {
            Factorization::ScopeObject const scopeObject;
            scopeObject.setInThisScopeThisConfiguration(getFactorizationConfiguration());

            Terms const bases(factorizeTerm(base));
            if (bases.size() > 1) {
                TermsRaiseToNumbers termsRaiseToNumbers;
                termsRaiseToNumbers.putTerms(bases, TermAssociationType::Positive);
                termsRaiseToNumbers.multiplyToExponents(exponent.getAsNumber());
                Term const combinedTerm(termsRaiseToNumbers.getCombinedTerm());
                if (!hasDoubleValues(combinedTerm) && !hasNonRealFiniteNumbers(combinedTerm)) {
                    result = combinedTerm;
                }
            }
        }
    }
    return result;
}

bool SimplificationOfExpression::isChangeDetected(Expression const& expression1, Expression const& expression2) {
    return expression1 != expression2 && !hasNan(expression2);
}

bool SimplificationOfExpression::shouldDistributeExponentConstantToEachBase() {
    return !shouldNotSimplifyByDistributingConstantExponentToEachBase() &&
           !shouldSimplifyByCombiningRadicalsInMultiplicationAndDivision();
}

}  // namespace algebra::Simplification

template <>
algebra::Simplification::SimplificationOfExpression::ConfigurationDetails
getDefaultConfigurationDetails<alba::algebra::Simplification::SimplificationOfExpression::ConfigurationDetails>() {
    return algebra::Simplification::SimplificationOfExpression::ConfigurationDetails{
        false, false, false, false, false, false, false, false, false, false, false};
}

}  // namespace alba
