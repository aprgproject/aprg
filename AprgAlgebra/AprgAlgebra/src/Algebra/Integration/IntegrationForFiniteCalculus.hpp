#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba::algebra {

class IntegrationForFiniteCalculus {
public:
    explicit IntegrationForFiniteCalculus(std::string const& nameOfVariableToIntegrate);
    explicit IntegrationForFiniteCalculus(std::string&& nameOfVariableToIntegrate);
    [[nodiscard]] Monomial integrateConstant(Constant const& constant) const;
    [[nodiscard]] Polynomial integrateVariable(Variable const& variable) const;
    [[nodiscard]] Term integrate(Term const& term) const;
    [[nodiscard]] Term integrate(Constant const& constant) const;
    [[nodiscard]] Term integrate(Variable const& variable) const;
    [[nodiscard]] Term integrate(Monomial const& monomial) const;
    [[nodiscard]] Term integrate(Polynomial const& polynomial) const;
    [[nodiscard]] Term integrate(Expression const& expression) const;
    [[nodiscard]] Term integrateWithPlusC(Term const& term) const;
    [[nodiscard]] Term integrateAtDefiniteValues(
        Term const& term, AlbaNumber const& lowerEnd, AlbaNumber const& higherEnd) const;
    [[nodiscard]] Term integrateTerm(Term const& term) const;
    [[nodiscard]] Term integrateMonomial(Monomial const& monomial) const;
    [[nodiscard]] Term integratePolynomial(Polynomial const& polynomial) const;
    [[nodiscard]] Term integrateExpression(Expression const& expression) const;
    static Term integrate(Function const& functionObject);
    static Term integrateFunction(Function const& functionObject);

private:
    // For Monomial and Polynomial
    [[nodiscard]] Monomial integrateMonomialInFallingPower(Monomial const& monomial) const;
    [[nodiscard]] Polynomial integratePolynomialInFallingPower(Polynomial const& polynomial) const;
    [[nodiscard]] Polynomial convertMonomialWithPositiveExponentsFromRegularPowerToFallingPower(
        Monomial const& monomial) const;
    [[nodiscard]] Polynomial convertMonomialWithPositiveExponentsFromFallingPowerToRegularPower(
        Monomial const& monomial) const;
    [[nodiscard]] Polynomial convertPolynomialWithPositiveExponentsFromRegularPowerToFallingPower(
        Polynomial const& polynomial) const;
    [[nodiscard]] Polynomial convertPolynomialWithPositiveExponentsFromFallingPowerToRegularPower(
        Polynomial const& polynomial) const;
    // For Expression
    [[nodiscard]] Term integrateAsTermOrExpressionIfNeeded(Expression const& expression) const;
    [[nodiscard]] Term integrateSimplifiedExpressionOnly(Expression const& expression) const;
    [[nodiscard]] Term integrateTermsInAdditionOrSubtraction(Expression const& expression) const;
    [[nodiscard]] Term integrateTermsInMultiplicationOrDivision(Expression const& expression) const;
    [[nodiscard]] Term integrateTermsInRaiseToPower(Expression const& expression) const;
    [[nodiscard]] Term integrateNonChangingTermRaiseToChangingTerm(Term const& base, Term const& exponent) const;
    [[nodiscard]] bool isVariableToIntegrate(std::string const& variableName) const;
    [[nodiscard]] bool isChangingTerm(Term const& term) const;
    // For changing and non changing
    void integrateNonChangingAndChangingTermsInMultiplicationOrDivision(
        Term& result, TermsWithDetails const& termsWithDetails) const;

    void segregateNonChangingAndChangingTerms(
        TermsWithDetails const& termsToSegregate, TermsWithDetails& nonChangingTerms,
        TermsWithDetails& changingTerms) const;

    static void integrateChangingTermsInMultiplicationOrDivision(Term& result, TermsWithDetails const&);
    static Term integrateChangingTermRaiseToNonChangingTerm(Term const& base, Term const& exponent);
    static Term integrateChangingTermRaiseToChangingTerm(Term const& firstTerm, Term const& secondTerm);
    std::string m_nameOfVariableToIntegrate;
};

}  // namespace alba::algebra
