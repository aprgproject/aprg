#pragma once

#include <Algebra/Constructs/PolynomialOverPolynomial.hpp>
#include <Algebra/Constructs/TermsRaiseToNumbers.hpp>
#include <Algebra/Integration/IntegrationHistory.hpp>
#include <Algebra/Simplification/SimplificationOfExpression.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>
#include <Algebra/Term/TermTypes/TermContainerTypes.hpp>
#include <Algebra/Utilities/NumberMatrix.hpp>
#include <Common/Math/Number/AlbaNumberTypes.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <vector>

namespace alba::algebra {

class Integration {
public:
    struct IntegrationByPartsTerms {
        Term uTimesDvToIntegrate;
        Term uTimesV;
        Term vTimesDuToIntegrate;
    };

    struct TrigonometryFunctionExponents {
        AlbaNumber sinExponent;
        AlbaNumber cosExponent;
        AlbaNumber tanExponent;
        AlbaNumber cscExponent;
        AlbaNumber secExponent;
        AlbaNumber cotExponent;
    };

    struct TrigonometricSubstitutionDetails {
        bool isTrigonometricSubstitutionPossible{};
        std::string thetaName;
        Term a;
        Term u;
        std::string aSquaredAndUSquaredName;
        Term aSquaredAndUSquared;
        Term uEquivalent;
        Term thetaEquivalent;
        Term aSquaredAndUSquaredEquivalent;
        Term theta;
        Term opposite, adjacent, hypotenuse;
    };

    struct Configuration {
        bool shouldFixTrigonometricFunctions;
        Simplification::SimplificationOfExpression::ConfigurationDetails expressionSimplification;
    };

    using ListOfIntegrationByPartsTerms = std::vector<IntegrationByPartsTerms>;
    using InputTermToTrigonometryFunctionExponentsMap = std::map<Term, TrigonometryFunctionExponents>;
    using Configurations = std::vector<Configuration>;
    explicit Integration(std::string const& nameOfVariableToIntegrate);
    Monomial integrateConstant(Constant const& constant);
    Monomial integrateVariable(Variable const& variable);
    Term integrate(Term const& term);
    Term integrate(Constant const& constant);
    Term integrate(Variable const& variable);
    Term integrate(Monomial const& monomial);
    Term integrate(Polynomial const& polynomial);
    Term integrate(Expression const& expression);
    Term integrate(Function const& functionObject);
    Term integrateWithPlusC(Term const& term);
    Term integrateAtDefiniteValues(Term const& term, AlbaNumber const& lowerEnd, AlbaNumber const& higherEnd);
    Term integrateAtDefiniteTerms(Term const& term, Term const& lowerEnd, Term const& higherEnd);
    Term integrateMonomial(Monomial const& monomial);
    Term integratePolynomial(Polynomial const& polynomial);
    Term integrateExpression(Expression const& expression);
    Term integrateFunction(Function const& functionObject);
    bool isConvergent(Term const& term, AlbaNumber const& lowerEnd, AlbaNumber const& higherEnd);

private:
    [[nodiscard]] Monomial integrateMonomialWhenExponentIsNotNegativeOne(Monomial const& monomial) const;
    // For Monomial
    [[nodiscard]] Term integrateMonomialWhenExponentIsNegativeOne(Monomial const& monomial) const;
    [[nodiscard]] Term substituteToNewVariable(Term const& mainTerm, Term const& termForNewVariable) const;

    [[nodiscard]] Term substituteToTrigonometricFunctions(
        Term const& mainTerm, TrigonometricSubstitutionDetails const& details) const;

    [[nodiscard]] Term divideFirstTermAndDerivativeOfSecondTerm(Term const& firstTerm, Term const& secondTerm) const;
    [[nodiscard]] std::string getCurrentVariableToIntegrate() const;
    // Miscellaneous
    [[nodiscard]] bool isVariableToIntegrate(std::string const& variableName) const;
    [[nodiscard]] bool isChangingTerm(Term const& term) const;
    [[nodiscard]] bool hasNonChangingTermRaiseToChangingTerm(Term const& term) const;
    [[nodiscard]] bool wouldDifferentiationYieldToAConstant(Term const& term) const;
    [[nodiscard]] bool isIntegrationUsingSubstitutionAllowed(Term const& term) const;
    [[nodiscard]] bool isIntegrationByPartsAllowed(Term const& term) const;
    [[nodiscard]] bool isIntegrationByPartialFractionAllowed() const;
    void integrateFunctionOnly(Term& result, Function const& functionObject) const;
    void integrateRecognizedFunctionsSquared(Term& result, Term const& functionTerm) const;

    void segregateNonChangingAndChangingTerms(
        TermsWithDetails const& termsToSegregate, TermsWithDetails& nonChangingTerms,
        TermsWithDetails& changingTerms) const;

    void findInnerAndOuterTermForChainRule(Term& innerTerm, Term& outerTerm) const;

    void integrateSimplifiedExpressionOnly(
        Term& result, Expression const& expression, Configuration const& configuration);

    void integrateTermsInAdditionOrSubtraction(Term& result, Expression const& expression);
    void integrateTermsInMultiplicationOrDivision(Term& result, Expression const& expression);
    void integrateTermsInRaiseToPower(Term& result, Expression const& expression);

    // Changing and non changing
    void integrateNonChangingAndChangingTermsInMultiplicationOrDivision(
        Term& result, TermsWithDetails const& termsWithDetails);

    void integrateChangingTermsInMultiplicationOrDivision(Term& result, TermsWithDetails const& changingTerms);
    void integrateNonChangingTermRaiseToChangingTerm(Term& result, Term const& base, Term const& exponent);
    void integrateChangingTermRaiseToNonChangingTerm(Term& result, Term const& base, Term const& exponent);
    // Substitution
    void integrateTermUsingSubstitutionWithMaxDepth(Term& result, Term const& term, Configuration const& configuration);
    void integrateTermUsingSubstitution(Term& result, Term const& term, Configuration const& configuration);

    void integrateBySubstitutionAndUsingANewVariable(
        Term& result, Term const& mainTerm, Term const& termForNewVariable, Configuration const& configuration);

    // Trignometric Substitution
    void integrateTermUsingTrigonometricSubstitution(Term& result, Term const& term);

    void integrateUsingTrigonometricSubstitutionByFindingTwoTerms(
        Term& result, Term const& mainTerm, Term const& termToSubstitute);

    void integrateUsingTrigonometricSubstitutionWithDeterminedTerms(
        Term& result, Term const& mainTerm, std::string const& aSquaredAndUSquaredName, Term const& aSquaredAndUSquared,
        Term const& aSquaredWithSign, Term const& uSquaredWithSign);

    // Reverse chain rule
    void integrateInMultiplicationOrDivisionByTryingReverseChainRule(
        Term& result, TermsWithDetails const& termsWithDetailsInMultiplicationOrDivision);

    void integrateUsingReverseChainRule(
        Term& result, Term const& firstOuterTerm, Term const& firstInnerTerm, Term const& secondTerm);

    // Polynomial over polynomial
    void integrateAsPolynomialOverPolynomialIfPossible(
        Term& result, Term const& term, bool const canProceedToPartialPolynomialFractions);

    void integrateAsPolynomialOverPolynomial(
        Term& result, PolynomialOverPolynomial const& polynomialOverPolynomial, std::string const& variableName,
        bool const canProceedToPartialPolynomialFractions);

    // Partial Fraction
    void integrateUsingPartialFractionPolynomials(
        Term& result, std::string const& variableName, Polynomial const& numerator, Polynomial const& denominator);

    void integratePartialFractionsBasedOnSolvedMatrix(
        Term& result, NumberMatrix const& solvedMatrix, VariableNamesSet const& newVariableNames,
        Polynomials const& partialNumerators, Polynomials const& partialDenominators);

    // Integration by parts
    void integrateByTryingIntegrationByParts(Term& result, Term const& term);
    void integrateUsingIntegrationByPartsByOneTermAndOne(Term& result, Term const& term);
    void integrateUsingIntegrationByPartsByTryingTwoTerms(Term& result, Term const& term);

    void integrateUsingIntegrationByPartsByTryingTwoTermsWithDifferentOrder(
        Term& result, Term const& term, Term const& firstTerm, Term const& secondTerm);

    void integrateUsingIntegrationByPartsAndCheckingPreviousValues(
        Term& result, Term const& term, Term const& u, Term const& dv);

    void integrateUsingIntegrationByParts(
        Term& result, ListOfIntegrationByPartsTerms& listOfIntegrationByPartsTerms, Term const& term, Term const& u,
        Term const& dv);

    void integrateTrigonometricCombinationsIfPossible(
        Term& result, TermsRaiseToNumbers const& remainingTerms,
        InputTermToTrigonometryFunctionExponentsMap const& inputTermToExponents);

    void integrateUsingKnownTrigonometricCombinations(
        Term& result, TrigonometryFunctionExponents const& exponents, Term const& functionInputTerm);

    void integrateSinRaiseToAnIntegerGreaterThanOne(Term& result, Term const& functionInputTerm, int const exponent);
    void integrateCosRaiseToAnIntegerGreaterThanOne(Term& result, Term const& functionInputTerm, int const exponent);
    void integrateTanRaiseToAnIntegerGreaterThanOne(Term& result, Term const& functionInputTerm, int const exponent);
    void integrateCscRaiseToAnIntegerGreaterThanOne(Term& result, Term const& functionInputTerm, int const exponent);
    void integrateSecRaiseToAnIntegerGreaterThanOne(Term& result, Term const& functionInputTerm, int const exponent);
    void integrateCotRaiseToAnIntegerGreaterThanOne(Term& result, Term const& functionInputTerm, int const exponent);

    void integrateSinAndCosCombinationWithExponentsGreaterThanOne(
        Term& result, Term const& functionInputTerm, int const sinExponent, int const cosExponent);

    void integrateCscAndCotCombinationWithExponentsGreaterThanOne(
        Term& result, Term const& functionInputTerm, int const cscExponent, int const cotExponent);

    void integrateSecAndTanCombinationWithExponentsGreaterThanOne(
        Term& result, Term const& functionInputTerm, int const secExponent, int const tanExponent);

    // Internal integration
    Term integrateIntenally(Term const& term);
    Term integrateInternallyWithPurpose(Term const& term, IntegrationPurpose const purpose);

    Term integrateIntenallyWithNewVariable(
        Term const& term, IntegrationPurpose const purpose, std::string const& newVariable);

    // For Expression
    Term integrateAsTermOrExpressionIfNeeded(Expression const& expression);
    // For Function
    Term integrateFunctionInternally(Function const& functionObject);
    static void integrateChangingTermRaiseToChangingTerm(Term& result, Term const& firstTerm, Term const& secondTerm);

    static void retrieveImportantTermsForTrigonometricSubstitutionInExpression(
        bool& shouldProceedToTrigSub, Term& commonFactor, Term& firstAndSecondTerm, Term& firstTerm, Term& secondTerm,
        Expression const& expression);

    static void retrieveImportantTermsForTrigonometricSubstitutionInPolynomial(
        bool& shouldProceedToTrigSub, Term& commonFactor, Term& firstAndSecondTerm, Term& firstTerm, Term& secondTerm,
        Polynomial const& polynomial);

    static void retrievePartialFractions(
        Polynomials& partialNumerators, Polynomials& partialDenominators, std::string const& originalVariableName,
        TermsRaiseToNumbers const& factorsWithExponents);

    static void fillInMatrixForPartialFractions(
        NumberMatrix& matrixWithNewVariables, std::string const& originalVariableName,
        VariableNamesSet const& newVariableNames, AlbaNumbersSet const& exponents, Polynomial const& originalNumerator,
        Polynomial const& numeratorWithNewVariables);

    static void fillInMatrixForPartialFractionsWithVariableValues(
        NumberMatrix& matrixWithNewVariables, std::string const& originalVariableName,
        VariableNamesSet const& newVariableNames, AlbaNumbersSet const& exponents,
        Polynomial const& numeratorWithNewVariables);

    static void fillInMatrixForPartialFractionsWithOutputValues(
        NumberMatrix& matrixWithNewVariables, std::string const& originalVariableName,
        VariableNamesSet const& newVariableNames, AlbaNumbersSet const& exponents, Polynomial const& originalNumerator);

    static void integrateUsingPreviousIntegrationByPartsTerms(
        Term& result, ListOfIntegrationByPartsTerms const& listOfIntegrationByPartsTerms, Term const& termToIntegrate);

    // Trigonometry
    static void retrieveInputTermsAndTrigonometricExponents(
        InputTermToTrigonometryFunctionExponentsMap& inputTermToExponents, TermsRaiseToNumbers& remainingTerms,
        TermsRaiseToNumbers const& termsWithExponentsToCheck);

    static void putReducedSineSquaredToDoubleAngleCosineTerms(
        Term& outputTerm, Term const& inputTerm, int const exponent);

    static void putReducedCosineSquaredToDoubleAngleCosineTerms(
        Term& outputTerm, Term const& inputTerm, int const exponent);

    static void putTangentSquaredToSecantSquaredTerms(Term& outputTerm, Term const& inputTerm, int const exponent);
    static void putCosecantSquaredToCotangentSquaredTerms(Term& outputTerm, Term const& inputTerm, int const exponent);
    static void putSecantSquaredToTangentSquaredTerms(Term& outputTerm, Term const& inputTerm, int const exponent);
    static void putCotangentSquaredToCosecantSquaredTerms(Term& outputTerm, Term const& inputTerm, int const exponent);
    // Simplify
    static void simplifyForIntegration(Term& term, Configuration const& configuration);
    static void simplifyAndFixTrigonometricFunctions(Term& term, bool const shouldFixTrigonometricFunctions);

    static void fixTrigonometricFunctionsBasedFromExponents(
        Term& term, InputTermToTrigonometryFunctionExponentsMap const& trigFunctionsInputTermToExponents,
        TermsRaiseToNumbers const& remainingTermsWithExponents);

    static void putTrigonometricFunctionsWithExponents(
        TermsRaiseToNumbers& newTerms, Term const& inputTerm, TrigonometryFunctionExponents const& exponents);

    // Initialize and Finalize steps
    static void finalizeTermForIntegration(Term& term);

    static AlbaNumbersSet getExponentsForPartialFraction(
        std::string const& originalVariableName, Polynomial const& numeratorWithNewVariables);

    // Integration configurations
    static Configuration getConfigurationWithFactors();
    static Configuration getConfigurationWithCommonDenominator();
    static Configuration getConfigurationWithoutFactors();
    static Configuration getConfigurationWithCombiningRadicals();

    static Polynomial getTotalNumeratorWithNewVariables(
        Polynomial const& originalDenominator, Polynomials const& partialNumerators,
        Polynomials const& partialDenominators);

    static Polynomial getPartialNumeratorForPartialFractions(int const degree, std::string const& variableName);

    static Term substituteBackToOldVariable(
        Term const& mainTerm, std::string const& newVariableName, Term const& termForNewVariable);

    static Term substituteFromTrigonometricFunctionsBackToNormal(
        Term const& mainTerm, TrigonometricSubstitutionDetails const& details);

    static TrigonometricSubstitutionDetails calculateTrigonometricSubstitutionDetails(
        Term const& a, Term const& u, std::string const& aSquaredAndUSquaredName, Term const& aSquaredAndUSquared,
        bool const isANegative, bool const isUNegative);

    static TrigonometryFunctionExponents getTrigonometricExponentsSuitableForIntegration(
        TrigonometryFunctionExponents const& oldExponents);

    static VariableNamesSet getNamesOfNewVariablesForPartialFraction(
        std::string const& originalVariableName, Polynomial const& numeratorWithNewVariables);

    static std::string getNewVariableNameForPartialFractions();

    static bool areExponentsSame(
        TrigonometryFunctionExponents const& exponents1, TrigonometryFunctionExponents const& exponents2);

    static bool isTrigonometricSubstitutionAllowed();
    stringHelper::strings m_variablesToIntegrate;
    IntegrationHistory m_history;
};

}  // namespace alba::algebra
