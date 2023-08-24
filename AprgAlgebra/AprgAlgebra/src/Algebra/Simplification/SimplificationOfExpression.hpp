#pragma once

#include <Algebra/Constructs/TermRaiseToTerms.hpp>
#include <Algebra/Constructs/TermsOverTerms.hpp>
#include <Algebra/Factorization/FactorizationConfiguration.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>
#include <Common/Container/AlbaConfigurationHolder.hpp>

namespace alba {

namespace algebra::Simplification {

class SimplificationOfExpression {
public:
    // is logarithm simplification needed?
    struct ConfigurationDetails {
        bool shouldSimplifyToACommonDenominator;
        bool shouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase;
        bool shouldSimplifyByCombiningRadicalsInMultiplicationAndDivision;
        bool shouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt;
        bool shouldSimplifyByRationalizingNumerator;
        bool shouldSimplifyByRationalizingDenominator;
        bool shouldSimplifyBySubstitutingExpressionAndFunctionsToVariables;
        bool shouldSimplifyToFactors;
        bool shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue;
        bool shouldNotSimplifyByDistributingConstantExponentToEachBase;
        bool shouldPerformDebug;
    };

    class Configuration : public AlbaConfigurationHolder<ConfigurationDetails> {};

    class ScopeObject : public AlbaConfigurationScopeObject<ConfigurationDetails> {};

    SimplificationOfExpression();
    explicit SimplificationOfExpression(Expression const& expression);

    static bool shouldSimplifyToACommonDenominator();
    static bool shouldSimplifyWithEvenExponentsCancellationAndPutAbsoluteValueAtBase();
    static bool shouldSimplifyByCombiningRadicalsInMultiplicationAndDivision();
    static bool shouldSimplifyByCheckingPolynomialRaiseToAnUnsignedInt();
    static bool shouldSimplifyByRationalizingNumerator();
    static bool shouldSimplifyByRationalizingDenominator();
    static bool shouldSimplifyBySubstitutingExpressionAndFunctionsToVariables();
    static bool shouldSimplifyToFactors();
    static bool shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue();
    static bool shouldNotSimplifyByDistributingConstantExponentToEachBase();
    static bool shouldPerformDebug();

    [[nodiscard]] Expression getExpression() const;

    void simplify();

private:
    static bool isChangeDetected(Expression const& expression1, Expression const& expression2);

    void simplifyExpressionUntilNoChange();
    static void simplifyExpression(Expression& expression);
    void simplifyExpressionUntilNoChangeInitiallyIfNeeded();
    void simplifyToACommonDenominatorIfNeeded();
    void simplifyBySubstitutingExpressionAndFunctionsToVariablesIfNeeded();

    static void processTermsBaseOnOperatorLevel(
        Expression& expression, TermsWithDetails const& termsToProcess, OperatorLevel const operatorLevel);
    static void processAndSaveTermsForAdditionAndSubtraction(
        Expression& expression, TermsWithDetails const& termsToProcess);
    static void processAndSaveTermsForMultiplicationAndDivision(
        Expression& expression, TermsWithDetails const& termsToProcess);
    static void processAndSaveTermsForRaiseToPower(Expression& expression, TermsWithDetails const& termsToProcess);

    // functions for addition/subtraction
    static void addOrSubtractTermsWithExpressions(Term& combinedTerm, TermsWithDetails const& termsWithExpressions);

    // functions for multiplication/division
    static void simplifyByCombiningRadicalsInMultiplicationAndDivisionIfNeeded(
        TermsWithDetails& termsInMultiplicationAndDivision);
    static Term getCombinedTermAndSimplifyByRationalizingNumeratorOrDenominatorIfNeeded(
        TermsOverTerms const& termsOverTerms);

    // functions for raise to power
    static Term getCombinedTermUsingTermsRaiseToTerms(TermRaiseToTerms const& termRaiseToTerms);
    static Term getEachBasesRaisedToConstantIfPossible(TermRaiseToTerms const& termRaiseToTerms);

    // other functions
    static bool shouldDistributeExponentConstantToEachBase();
    static Factorization::ConfigurationDetails getFactorizationConfiguration();
    bool tryToSubstituteSubExpressionOrSubFunctionAndReturnIfContinue(Expression const& expression);
    static Expression getNewExpressionWithSubstitutedVariableForTerm(
        Term const& mainExpression, Term const& termToSubstitute);
    void convertPolynomialOverPolynomialIfNeeded();
    void convertPolynomialToPolynomialOverPolynomial(Term& term);
    void convertPolynomialToPolynomialOverPolynomial(Expression& expression);

    Expression m_expression;
};

}  // namespace algebra::Simplification

template <>
algebra::Simplification::SimplificationOfExpression::ConfigurationDetails
getDefaultConfigurationDetails<algebra::Simplification::SimplificationOfExpression::ConfigurationDetails>();

}  // namespace alba
