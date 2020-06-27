#include "SimplificationOfExpression.hpp"

#include <Equation/Constructs/AdditionAndSubtractionOfExpressions.hpp>
#include <Equation/Constructs/AdditionAndSubtractionOfTermsOverTerms.hpp>
#include <Equation/Operations/AccumulateOperations.hpp>
#include <Equation/Utilities.hpp>

using namespace std;
using TermWithDetails=alba::equation::TermsWithAssociation::TermWithDetails;
using TermsWithDetails=alba::equation::TermsWithAssociation::TermsWithDetails;

namespace alba
{

namespace equation
{

namespace Simplification
{

SimplificationOfExpression::SimplificationOfExpression(
        Expression const& expression)
    : m_expression(expression)
    , m_shouldSimplifyToACommonDenominator(false)
{}

Expression SimplificationOfExpression::getExpression() const
{
    return m_expression;
}

void SimplificationOfExpression::setAsShouldSimplifyToACommonDenominator(bool const shouldSimplifyToACommonDenominator)
{
    m_shouldSimplifyToACommonDenominator = shouldSimplifyToACommonDenominator;
}

void SimplificationOfExpression::simplify()
{
    prepareToACommonDenominatorIfNeeded();
    simplifyExpression();
    finalizeToACommonDenominatorIfNeeded();
}

void SimplificationOfExpression::prepareToACommonDenominatorIfNeeded()
{
    if(m_shouldSimplifyToACommonDenominator)
    {
        simplifyToACommonDenominatorForExpressionAndReturnIfChanged(m_expression);
    }
}

void SimplificationOfExpression::finalizeToACommonDenominatorIfNeeded()
{
    if(m_shouldSimplifyToACommonDenominator)
    {
        putNegativeExponentsOnDenominator(m_expression);
    }
}

void SimplificationOfExpression::simplifyExpression()
{
    Expression beforeSimplify(m_expression);

    TermsWithDetails termsToUpdate;
    TermsWithAssociation & termsWithAssociation(m_expression.getTermsWithAssociationReference());
    simplifyAndCopyTerms(termsToUpdate, termsWithAssociation.getTermsWithDetails());
    termsWithAssociation.clear();
    processTermsBaseOnOperatorLevel(termsToUpdate);

    Expression afterSimplify(m_expression);
    simplifyFurtherIfNeeded(beforeSimplify, afterSimplify);

}

void SimplificationOfExpression::simplifyAndCopyTerms(
        TermsWithDetails & termsToUpdate,
        TermsWithDetails const& termsToCheck)
{
    for(TermWithDetails const& termWithDetails : termsToCheck)
    {
        Term const& term(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
        if(term.isExpression())
        {
            Expression expression(term.getExpressionConstReference());
            expression.simplify();
            simplifyAndCopyTermsFromAnExpressionAndSetOperatorLevelIfNeeded(termsToUpdate, expression, termWithDetails.association);
        }
        else if(term.isFunction())
        {
            Term newTerm(simplifyAndConvertFunctionToSimplestTerm(term.getFunctionConstReference()));
            termsToUpdate.emplace_back(newTerm, termWithDetails.association);
        }
        else if(term.isValueTermAndNotAnExpression())
        {
            termsToUpdate.emplace_back(term, termWithDetails.association);
        }
    }
}

void SimplificationOfExpression::simplifyAndCopyTermsFromAnExpressionAndSetOperatorLevelIfNeeded(
        TermsWithDetails & termsToUpdate,
        Expression const& expression,
        TermAssociationType const association)
{
    OperatorLevel expressionOperatorLevel(expression.getCommonOperatorLevel());
    if(expression.containsOnlyOneTerm()
            || OperatorLevel::Unknown == m_expression.getCommonOperatorLevel()
            || expressionOperatorLevel == m_expression.getCommonOperatorLevel())
    {
        m_expression.setCommonOperatorLevelIfStillUnknown(expression.getCommonOperatorLevel());
        TermsWithAssociation termsWithAssociation(getTermsWithAssociationAndReverseIfNeeded(expression, association));
        simplifyAndCopyTerms(termsToUpdate, termsWithAssociation.getTermsWithDetails());
    }
    else
    {
        termsToUpdate.emplace_back(Term(expression), association);
    }
}

void SimplificationOfExpression::simplifyFurtherIfNeeded(Expression const& beforeSimplify, Expression const& afterSimplify)
{
    if(beforeSimplify != afterSimplify)
    {
        simplify();
    }
}

bool SimplificationOfExpression::simplifyToACommonDenominatorForExpressionAndReturnIfChanged(Expression & expression)
{
    bool isChanged(false);
    if(expression.getCommonOperatorLevel() == OperatorLevel::AdditionAndSubtraction)
    {
        isChanged = tryToAddSubtractTermsOverTermsAndReturnIfChanged(expression);
    }
    else
    {
        simplifyTermsWithDetailsInExpressionToACommonDenominator(expression);
    }
    return isChanged;
}

void SimplificationOfExpression::simplifyTermsWithDetailsInExpressionToACommonDenominator(Expression & expression)
{
    bool isChanged(true);
    while(isChanged)
    {
        isChanged=false;
        for(TermWithDetails & termWithDetails : expression.getTermsWithAssociationReference().getTermsWithDetailsReference())
        {
            Term & term(getTermReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
            if(term.isExpression())
            {
                Expression & subExpression(term.getExpressionReference());
                isChanged = isChanged || simplifyToACommonDenominatorForExpressionAndReturnIfChanged(subExpression);
            }
        }
        if(isChanged)
        {
            expression.simplify();
        }
    }
}

bool SimplificationOfExpression::tryToAddSubtractTermsOverTermsAndReturnIfChanged(Expression & addSubtractExpression)
{
    AdditionAndSubtractionOfTermsOverTerms addSubtractTermsOverTerms;
    bool shouldTermsOverTermsBeAddedOrSubtracted(false);
    for(TermWithDetails const& addSubtractTermWithDetails : addSubtractExpression.getTermsWithAssociation().getTermsWithDetails())
    {
        Term const& addSubtractTerm(getTermConstReferenceFromSharedPointer(addSubtractTermWithDetails.baseTermSharedPointer));
        bool isTermAddedOrSubtracted(false);
        if(addSubtractTerm.isExpression())
        {
            Expression expression(addSubtractTerm.getExpressionConstReference());
            if(expression.getCommonOperatorLevel() == OperatorLevel::MultiplicationAndDivision)
            {
                TermsWithDetails numerators;
                TermsWithDetails denominators;
                segregateTermsWithPositiveAndNegativeAssociations(expression.getTermsWithAssociation().getTermsWithDetails(), numerators, denominators);
                if(!denominators.empty())
                {
                    shouldTermsOverTermsBeAddedOrSubtracted=true;
                }
                addSubtractTermsOverTerms.putAsAddOrSubtraction(TermsOverTerms(numerators, denominators), addSubtractTermWithDetails.association);
                isTermAddedOrSubtracted=true;
            }
        }
        if(!isTermAddedOrSubtracted)
        {
            addSubtractTermsOverTerms.putAsAddOrSubtraction(TermsOverTerms({addSubtractTerm}, {}), addSubtractTermWithDetails.association);
        }
    }
    if(shouldTermsOverTermsBeAddedOrSubtracted)
    {
        addSubtractExpression=addSubtractTermsOverTerms.getCombinedExpression();
        addSubtractExpression.simplify();
    }
    return shouldTermsOverTermsBeAddedOrSubtracted;
}

void SimplificationOfExpression::putNegativeExponentsOnDenominator(Expression & expression)
{
    TermsWithDetails & termsWithDetails(expression.getTermsWithAssociationReference().getTermsWithDetailsReference());
    if((termsWithDetails.size()==1 || expression.getCommonOperatorLevel()==OperatorLevel::MultiplicationAndDivision))
    {
        ListOfPolynomialOverPolynomial numeratorsAndDenominators;
        bool isExpressionChanged(false);
        for(TermsWithDetails::iterator it=termsWithDetails.begin(); it!=termsWithDetails.end(); it++)
        {
            Term & term(getTermReferenceFromSharedPointer(it->baseTermSharedPointer));
            if(term.isExpression())
            {
                Expression & subExpression(term.getExpressionReference());
                putNegativeExponentsOnDenominator(subExpression);
            }
            else if(canBeConvertedToPolynomial(term))
            {
                emplaceToNumeratorsAndDenominators(numeratorsAndDenominators, createPolynomialIfPossible(term), it->association);
                isExpressionChanged=true;
                termsWithDetails.erase(it);
                it--;
            }
        }
        if(isExpressionChanged)
        {
            Expression newExpression(createOrCopyExpressionFromATerm(Term(1)));
            TermsWithDetails termsInNumerator;
            TermsWithDetails termsInDenominator;
            segregateTermsWithPositiveAndNegativeAssociations(
                        expression.getTermsWithAssociation().getTermsWithDetails(),
                        termsInNumerator,
                        termsInDenominator);
            putNumeratorsInExpression(newExpression, numeratorsAndDenominators);
            putNumeratorsInExpression(newExpression, termsInNumerator);
            putDenominatorsInExpression(newExpression, numeratorsAndDenominators);
            putDenominatorsInExpression(newExpression, termsInDenominator);
            expression = newExpression;
        }
    }
}

void SimplificationOfExpression::processTermsBaseOnOperatorLevel(
        TermsWithDetails const& termsToProcess)
{
    switch(m_expression.getCommonOperatorLevel())
    {
    case OperatorLevel::Unknown:
    {
        m_expression.putTermsWithDetails(termsToProcess);
        break;
    }
    case OperatorLevel::AdditionAndSubtraction:
    {
        processAndSaveTermsForAdditionAndSubtraction(termsToProcess);
        break;
    }
    case OperatorLevel::MultiplicationAndDivision:
    {
        processAndSaveTermsForMultiplicationAndDivision(termsToProcess);
        break;
    }
    case OperatorLevel::RaiseToPower:
    {
        processAndSaveTermsForRaiseToPower(termsToProcess);
        break;
    }
    }
}

void SimplificationOfExpression::processAndSaveTermsForAdditionAndSubtraction(
        TermsWithDetails const& termsToProcess)
{
    Term combinedTerm;
    TermsWithDetails termsWithNonExpressions;
    TermsWithDetails termsWithExpressions;
    segregateNonExpressionsAndExpressions(termsToProcess, termsWithNonExpressions, termsWithExpressions);
    accumulateTermsForAdditionAndSubtraction(combinedTerm, termsWithNonExpressions);
    addOrSubtractTermsWithExpressions(combinedTerm, termsWithExpressions);
    m_expression.setTerm(combinedTerm);
}

void SimplificationOfExpression::processAndSaveTermsForMultiplicationAndDivision(
        TermsWithDetails const& termsToProcess)
{
    Term combinedTerm(1);
    TermsWithDetails numerators;
    TermsWithDetails denominators;
    segregateTermsWithPositiveAndNegativeAssociations(termsToProcess, numerators, denominators);
    processNumeratorsAndDenominators(combinedTerm, numerators, denominators);
    m_expression.setTerm(combinedTerm);
}

void SimplificationOfExpression::processAndSaveTermsForRaiseToPower(
        TermsWithDetails const& termsToProcess)
{
    if(!termsToProcess.empty())
    {
        Term combinedTerm;
        Term const& baseOfRaiseToPower=getTermConstReferenceFromSharedPointer(termsToProcess.at(0).baseTermSharedPointer);
        if(baseOfRaiseToPower.isTheValueZero())
        {
            combinedTerm = Term(Constant(0));
        }
        else if(baseOfRaiseToPower.isTheValueOne())
        {
            combinedTerm = Term(1);
        }
        else if(termsToProcess.size() == 2)
        {
            accumulateTermsForRaiseToPower(combinedTerm, termsToProcess);
        }
        else
        {
            TermsWithDetails exponents(termsToProcess.cbegin()+1, termsToProcess.cend());
            saveBaseAndExponentsToTerm(combinedTerm, baseOfRaiseToPower, exponents);
        }
        m_expression.setTerm(combinedTerm);
    }
}

void SimplificationOfExpression::putNumeratorsInExpression(
        Expression & expression,
        ListOfPolynomialOverPolynomial const& numeratorsAndDenominators)
{
    for(PolynomialOverPolynomial const& numeratorAndDenominator : numeratorsAndDenominators)
    {
        expression.putTermWithMultiplicationIfNeeded(
                    simplifyAndConvertPolynomialToSimplestTerm(
                        numeratorAndDenominator.getNumerator()));
    }
}

void SimplificationOfExpression::putNumeratorsInExpression(
        Expression& expression,
        TermsWithDetails const& numerators)
{
    for(TermWithDetails numeratorWithDetails : numerators)
    {
        Term & numeratorTerm(getTermReferenceFromSharedPointer(numeratorWithDetails.baseTermSharedPointer));
        expression.putTermWithMultiplicationIfNeeded(numeratorTerm);
    }
}

void SimplificationOfExpression::putDenominatorsInExpression(
        Expression & expression,
        ListOfPolynomialOverPolynomial const& numeratorsAndDenominators)
{
    for(PolynomialOverPolynomial const& numeratorAndDenominator : numeratorsAndDenominators)
    {
        expression.putTermWithDivisionIfNeeded(
                    simplifyAndConvertPolynomialToSimplestTerm(
                        numeratorAndDenominator.getDenominator()));
    }
}

void SimplificationOfExpression::putDenominatorsInExpression(
        Expression& expression,
        TermsWithDetails const& denominators)
{
    for(TermWithDetails denominatorWithDetails : denominators)
    {
        Term & denominatorTerm(getTermReferenceFromSharedPointer(denominatorWithDetails.baseTermSharedPointer));
        expression.putTermWithDivisionIfNeeded(denominatorTerm);
    }
}

void SimplificationOfExpression::addOrSubtractTermsWithExpressions(
        Term & combinedTerm,
        TermsWithDetails const& termsWithExpressions) const
{
    AdditionAndSubtractionOfExpressions additionAndSubtraction;
    additionAndSubtraction.putTermsWithDetails(termsWithExpressions);
    additionAndSubtraction.combineExpressionsIfPossible();
    accumulateTermsForAdditionAndSubtraction(combinedTerm, additionAndSubtraction.getAsTermsWithDetails());
}

void SimplificationOfExpression::processNumeratorsAndDenominators(
        Term & combinedTerm,
        TermsWithDetails const& numerators,
        TermsWithDetails const& denominators) const
{
    TermsOverTerms termsOverTerms(numerators, denominators);
    termsOverTerms.simplify();
    accumulateTermsForMultiplicationAndDivision(
                combinedTerm,
                termsOverTerms.getNumeratorAndDenominatorAsTermWithDetails());
}

void SimplificationOfExpression::saveBaseAndExponentsToTerm(
        Term & combinedTerm,
        Term const& baseOfRaiseToPower,
        TermsWithDetails const& exponents)
{
    Term exponentTerm;
    accumulateTermsForMultiplicationAndDivision(exponentTerm, exponents);
    if(exponentTerm.isTheValueZero())
    {
        combinedTerm = Term(1);
    }
    else if(exponentTerm.isTheValueOne())
    {
        combinedTerm = baseOfRaiseToPower;
    }
    else
    {
        Expression raiseToPowerExpression(createOrCopyExpressionFromATerm(baseOfRaiseToPower));
        raiseToPowerExpression.putTermWithRaiseToPowerIfNeeded(exponentTerm);
        combinedTerm = Term(raiseToPowerExpression);
    }
}

TermsWithAssociation SimplificationOfExpression::getTermsWithAssociationAndReverseIfNeeded(
        Expression const& expression,
        TermAssociationType const association)
{
    TermsWithAssociation termsWithAssociation(expression.getTermsWithAssociation());
    if(TermAssociationType::Negative == association)
    {
        termsWithAssociation.reverseTheAssociationOfTheTerms();
    }
    return termsWithAssociation;
}

void SimplificationOfExpression::emplaceToNumeratorsAndDenominators(
        ListOfPolynomialOverPolynomial & numeratorsAndDenominators,
        Polynomial const& polynomial,
        TermAssociationType const termAssociationType)
{
    Polynomial numerator(polynomial);
    Polynomial denominator(createPolynomialFromConstant(1));
    if(TermAssociationType::Negative == termAssociationType)
    {
        swap(numerator, denominator);
    }
    PolynomialOverPolynomial numeratorAndDenominator(numerator, denominator);
    numeratorAndDenominator.simplify();
    numeratorsAndDenominators.emplace_back(numeratorAndDenominator);
}

}

}

}
