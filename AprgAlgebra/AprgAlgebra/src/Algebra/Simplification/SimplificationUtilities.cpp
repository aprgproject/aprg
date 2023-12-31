#include "SimplificationUtilities.hpp"

#include <Algebra/Constructs/AdditionAndSubtractionOfTermsOverTerms.hpp>
#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Simplification/SimplificationOfExpression.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>

using namespace std;

namespace alba::algebra::Simplification {

void simplifyTermToACommonDenominator(Term& term) {
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
        SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
    configurationDetails.shouldSimplifyToACommonDenominator = true;

    SimplificationOfExpression::ScopeObject const scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    term.clearAllInnerSimplifiedFlags();
    term.simplify();
}

void simplifyTermByCombiningRadicals(Term& term) {
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
        SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
    configurationDetails.shouldSimplifyByCombiningRadicalsInMultiplicationAndDivision = true;

    SimplificationOfExpression::ScopeObject const scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    term.clearAllInnerSimplifiedFlags();
    term.simplify();
}

void simplifyTermByFactoringToNonDoubleFactors(Term& term) {
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
        SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
    configurationDetails.shouldSimplifyToFactors = true;
    configurationDetails.shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue = true;

    SimplificationOfExpression::ScopeObject const scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    term.clearAllInnerSimplifiedFlags();
    term.simplify();
}

void simplifyTermByFactoringToNonDoubleFactorsToACommonDenominator(Term& term) {
    SimplificationOfExpression::ConfigurationDetails configurationDetails(
        SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
    configurationDetails.shouldSimplifyToACommonDenominator = true;
    configurationDetails.shouldSimplifyToFactors = true;
    configurationDetails.shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue = true;

    SimplificationOfExpression::ScopeObject const scopeObject;
    scopeObject.setInThisScopeThisConfiguration(configurationDetails);

    term.clearAllInnerSimplifiedFlags();
    term.simplify();
}

void simplifyTermsWithDetailsInExpressionToACommonDenominator(Expression& expression) {
    bool isChanged(true);
    while (isChanged) {
        isChanged = false;
        for (TermWithDetails& termWithDetails :
             expression.getTermsWithAssociationReference().getTermsWithDetailsReference()) {
            Term& term(getTermReferenceFromUniquePointer(termWithDetails.baseTermPointer));
            if (term.isExpression()) {
                Expression& subExpression(term.getAsExpressionReference());
                isChanged =
                    isChanged ||
                    simplifyToACommonDenominatorForExpressionAndReturnIfAdditionOrSubtractionOfTermsOverTermsOccurred(
                        subExpression);
            }
        }
        if (isChanged) {
            expression.simplify();
        }
    }
}

void simplifyAndCopyTermsAndChangeOperatorLevelIfNeeded(
    TermsWithDetails& newTermsWithDetails, OperatorLevel& mainOperatorLevel,
    TermsWithDetails const& oldTermsWithDetails) {
    for (TermWithDetails const& oldTermWithDetails : oldTermsWithDetails) {
        Term const& term(getTermConstReferenceFromUniquePointer(oldTermWithDetails.baseTermPointer));
        if (term.isExpression()) {
            Expression subExpression(term.getAsExpression());
            subExpression.simplify();
            TermAssociationType const subExpressionAssociation(oldTermWithDetails.association);
            simplifyAndCopyTermsFromAnExpressionAndChangeOperatorLevelIfNeeded(
                newTermsWithDetails, mainOperatorLevel, subExpression, subExpressionAssociation);
        } else if (isNonEmptyOrNonOperatorType(term)) {
            Term newTerm(term);
            newTerm.simplify();
            newTermsWithDetails.emplace_back(newTerm, oldTermWithDetails.association);
        }
    }
}

void simplifyAndCopyTermsFromAnExpressionAndChangeOperatorLevelIfNeeded(
    TermsWithDetails& newTermsWithDetails, OperatorLevel& mainOperatorLevel, Expression const& subExpression,
    TermAssociationType const subExpressionAssociation) {
    OperatorLevel const subExpressionOperatorLevel(subExpression.getCommonOperatorLevel());
    if (subExpression.containsOnlyOnePositivelyAssociatedTerm() || OperatorLevel::Unknown == mainOperatorLevel ||
        (subExpressionOperatorLevel == mainOperatorLevel &&
         (OperatorLevel::AdditionAndSubtraction == mainOperatorLevel ||
          OperatorLevel::MultiplicationAndDivision == mainOperatorLevel))) {
        if (OperatorLevel::Unknown == mainOperatorLevel) {
            mainOperatorLevel = subExpression.getCommonOperatorLevel();
        }
        TermsWithAssociation const termsWithAssociation(
            getTermsWithAssociationAndReverseIfNeeded(subExpression, subExpressionAssociation));
        simplifyAndCopyTermsAndChangeOperatorLevelIfNeeded(
            newTermsWithDetails, mainOperatorLevel, termsWithAssociation.getTermsWithDetails());
    } else {
        newTermsWithDetails.emplace_back(Term(subExpression), subExpressionAssociation);
    }
}

TermsWithAssociation getTermsWithAssociationAndReverseIfNeeded(
    Expression const& expression, TermAssociationType const overallAssociation) {
    TermsWithAssociation termsWithAssociation(expression.getTermsWithAssociation());
    if (TermAssociationType::Negative == overallAssociation) {
        termsWithAssociation.reverseTheAssociationOfTheTerms();
    }
    return termsWithAssociation;
}

bool simplifyToACommonDenominatorForExpressionAndReturnIfAdditionOrSubtractionOfTermsOverTermsOccurred(
    Expression& expression) {
    bool isChanged(false);
    if (expression.getCommonOperatorLevel() == OperatorLevel::AdditionAndSubtraction) {
        isChanged = tryToAddSubtractTermsOverTermsAndReturnIfChanged(expression);
    } else {
        simplifyTermsWithDetailsInExpressionToACommonDenominator(expression);
    }
    return isChanged;
}

bool tryToAddSubtractTermsOverTermsAndReturnIfChanged(Expression& addSubtractExpression) {
    AdditionAndSubtractionOfTermsOverTerms addSubtractTermsOverTerms;
    bool isAddSubtractExpressionUpdateNeeded(false);
    for (TermWithDetails const& addSubtractTermWithDetails :
         addSubtractExpression.getTermsWithAssociation().getTermsWithDetails()) {
        Term const& addSubtractTerm(getTermConstReferenceFromUniquePointer(addSubtractTermWithDetails.baseTermPointer));
        TermsOverTerms const termsOverTerms(createTermsOverTermsFromTerm(addSubtractTerm));
        if (!termsOverTerms.getDenominators().empty()) {
            isAddSubtractExpressionUpdateNeeded = true;
        }
        addSubtractTermsOverTerms.putAsAddOrSubtraction(termsOverTerms, addSubtractTermWithDetails.association);
    }
    if (isAddSubtractExpressionUpdateNeeded) {
        addSubtractExpression = addSubtractTermsOverTerms.getCombinedExpression();
        addSubtractExpression.simplify();
    }
    return isAddSubtractExpressionUpdateNeeded;
}

}  // namespace alba::algebra::Simplification
