#include "Expression.hpp"

#include <Optional/AlbaOptional.hpp>
#include <PerformOperation.hpp>
#include <Term.hpp>
#include <Utilities.hpp>

#include <sstream>


#include <Debug/AlbaDebug.hpp>

using namespace std;

namespace alba
{

namespace equation
{

Expression::Expression()
    : m_commonOperatorLevel(OperatorLevel::Unknown)
{}

Expression::Expression(BaseTerm const& baseTerm)
    : m_commonOperatorLevel(OperatorLevel::Unknown)
{
    m_termsWithPriorityAndAssociation.putTermWithPositiveAssociation(baseTerm);
}

Expression::~Expression()
{}

bool Expression::operator==(Expression const& second) const
{
    ALBA_PRINT2(static_cast<int>(m_commonOperatorLevel), static_cast<int>(second.m_commonOperatorLevel));
    return m_commonOperatorLevel == second.m_commonOperatorLevel
            && m_termsWithPriorityAndAssociation==second.m_termsWithPriorityAndAssociation;
}

bool Expression::containsOnlyOneTerm() const
{
    return 1 == m_termsWithPriorityAndAssociation.getSize();
}

OperatorLevel Expression::getCommonOperatorLevel() const
{
    return m_commonOperatorLevel;
}

BaseTerm const& Expression::getFirstTermConstReference() const
{
    return m_termsWithPriorityAndAssociation.getFirstTermConstReference();
}

TermsWithPriorityAndAssociation const& Expression::getTerms() const
{
    return m_termsWithPriorityAndAssociation;
}

string Expression::getDisplayableString() const
{
    bool isFirst(true);
    stringstream result;
    TermsWithPriorityAndAssociation::TermsWithDetails const& termsWithDetails(m_termsWithPriorityAndAssociation.getTermsWithDetails());
    result << "(";
    for(TermsWithPriorityAndAssociation::TermWithDetails const& termWithDetails : termsWithDetails)
    {
        Term const& term = *dynamic_cast<Term const*const>(termWithDetails.baseTermSharedPointer.get());
        if(isFirst)
        {
            if(termWithDetails.hasNegativeAssociation())
            {
                if(OperatorLevel::AdditionAndSubtraction == m_commonOperatorLevel)
                {
                    result << "-";
                }
                else if(OperatorLevel::MultiplicationAndDivision == m_commonOperatorLevel)
                {
                    result << "1/";
                }
            }
            isFirst=false;
        }
        else
        {
            result << getOperatingString(termWithDetails.association, m_commonOperatorLevel);
        }
        result << term.getDisplayableString();
    }
    result << ")";
    return result.str();
}

void Expression::simplify()
{
    TermsWithPriorityAndAssociation::TermsWithDetails onlySimplifiedExpressions;
    TermsWithPriorityAndAssociation::TermsWithDetails onlyValueTermsNonExpressions;
    TermsWithPriorityAndAssociation::TermsWithDetails inputTerms(
                m_termsWithPriorityAndAssociation.getTermsWithDetails());
    for(TermsWithPriorityAndAssociation::TermWithDetails const& termWithDetails : inputTerms)
    {
        Term const& term = *dynamic_cast<Term const*const>(termWithDetails.baseTermSharedPointer.get());
        ALBA_PRINT2(static_cast<unsigned int>(term.getTermType()), term.getDisplayableString());
        if(term.isExpression())
        {
            Expression expression(term.getExpressionConstReference());
            expression.simplify();
            if(expression.containsOnlyOneTerm())
            {
                Term const& oneTermInExpression = dynamic_cast<Term const&>(expression.getFirstTermConstReference());
                if(oneTermInExpression.isExpression())
                {
                    onlySimplifiedExpressions.emplace_back(getBaseTermConstReferenceFromTerm(oneTermInExpression), termWithDetails.association);
                }
                else if(term.isValueTermButNotAnExpression())
                {
                    onlyValueTermsNonExpressions.emplace_back(getBaseTermConstReferenceFromTerm(oneTermInExpression), termWithDetails.association);
                }
            }
            else if(expression.getCommonOperatorLevel() == m_commonOperatorLevel)
            {
                TermsWithPriorityAndAssociation::TermsWithDetails const& termsInSubExpression(
                            m_termsWithPriorityAndAssociation.getTermsWithDetails());
                for(TermsWithPriorityAndAssociation::TermWithDetails const& termWithDetailsInSubExpression : termsInSubExpression)
                {
                    Term const& termInSubExpression = *dynamic_cast<Term const*const>(termWithDetailsInSubExpression.baseTermSharedPointer.get());
                    if(termInSubExpression.isExpression())
                    {
                        onlySimplifiedExpressions.emplace_back(getBaseTermConstReferenceFromTerm(termInSubExpression), termWithDetailsInSubExpression.association);
                    }
                    else if(termInSubExpression.isValueTermButNotAnExpression())
                    {
                        onlyValueTermsNonExpressions.emplace_back(getBaseTermConstReferenceFromTerm(termInSubExpression), termWithDetailsInSubExpression.association);
                    }
                }
            }
            else
            {
                onlySimplifiedExpressions.emplace_back(getBaseTermConstReferenceFromTerm(term), termWithDetails.association);
            }
        }
        else if(term.isValueTermButNotAnExpression())
        {
            onlyValueTermsNonExpressions.emplace_back(getBaseTermConstReferenceFromTerm(term), termWithDetails.association);
            ALBA_PRINT1(onlyValueTermsNonExpressions.size());
        }
    }
    Term newTermForCombiningNonExpressions;
    bool isFirst(true);
    for(TermsWithPriorityAndAssociation::TermWithDetails const& termWithDetails : onlyValueTermsNonExpressions)
    {
        Term const& term = *dynamic_cast<Term const*const>(termWithDetails.baseTermSharedPointer.get());
        ALBA_PRINT2(isFirst, term.getDisplayableString());
        if((OperatorLevel::AdditionAndSubtraction == m_commonOperatorLevel &&  term.isTheValueZero()) ||
                (OperatorLevel::MultiplicationAndDivision == m_commonOperatorLevel &&  term.isTheValueOne()) ||
                (OperatorLevel::RaiseToPower == m_commonOperatorLevel &&  term.isTheValueOne()))
        {
            continue;
        }
        else if(isFirst)
        {
            newTermForCombiningNonExpressions = term;
            isFirst=false;
        }
        else
        {
            accumulateAndDoOperationOnTermDetails(newTermForCombiningNonExpressions, m_commonOperatorLevel, termWithDetails);
        }
    }
    m_termsWithPriorityAndAssociation.clear();
    m_termsWithPriorityAndAssociation.putTermWithPositiveAssociation(getBaseTermConstReferenceFromTerm(newTermForCombiningNonExpressions));
    for(TermsWithPriorityAndAssociation::TermWithDetails const& termWithDetails : onlySimplifiedExpressions)
    {
        Term const& term = *dynamic_cast<Term const*const>(termWithDetails.baseTermSharedPointer.get());
        ALBA_PRINT1(term.getDisplayableString());
        m_termsWithPriorityAndAssociation.putTermWithDetails(termWithDetails);
    }
}

void Expression::clearAndSetTerm(BaseTerm const& baseTerm)
{
    m_termsWithPriorityAndAssociation.clear();
    m_termsWithPriorityAndAssociation.putTermWithPositiveAssociation(baseTerm);
    m_commonOperatorLevel = OperatorLevel::Unknown;
}

void Expression::addTerm(BaseTerm const& baseTerm)
{
    switch(m_commonOperatorLevel)
    {
    case OperatorLevel::Unknown:
        m_commonOperatorLevel = OperatorLevel::AdditionAndSubtraction;
    case OperatorLevel::AdditionAndSubtraction:
    {
        m_termsWithPriorityAndAssociation.putTermWithPositiveAssociation(baseTerm);
        break;
    }
    case OperatorLevel::MultiplicationAndDivision:
    case OperatorLevel::RaiseToPower:
    {
        clearAndSetTerm(getBaseTermConstReferenceFromTerm(Term(Expression(*this))));
        m_commonOperatorLevel = OperatorLevel::AdditionAndSubtraction;
        m_termsWithPriorityAndAssociation.putTermWithPositiveAssociation(baseTerm);
        break;
    }
    }
}

void Expression::subtractTerm(BaseTerm const& baseTerm)
{
    switch(m_commonOperatorLevel)
    {
    case OperatorLevel::Unknown:
        m_commonOperatorLevel = OperatorLevel::AdditionAndSubtraction;
    case OperatorLevel::AdditionAndSubtraction:
    {
        m_termsWithPriorityAndAssociation.putTermWithNegativeAssociation(baseTerm);
        break;
    }
    case OperatorLevel::MultiplicationAndDivision:
    case OperatorLevel::RaiseToPower:
    {
        clearAndSetTerm(getBaseTermConstReferenceFromTerm(Term(Expression(*this))));
        m_commonOperatorLevel = OperatorLevel::AdditionAndSubtraction;
        m_termsWithPriorityAndAssociation.putTermWithNegativeAssociation(baseTerm);
        break;
    }
    }
}

void Expression::multiplyTerm(BaseTerm const& baseTerm)
{
    switch(m_commonOperatorLevel)
    {
    case OperatorLevel::Unknown:
        m_commonOperatorLevel = OperatorLevel::MultiplicationAndDivision;
    case OperatorLevel::MultiplicationAndDivision:
    {
        m_termsWithPriorityAndAssociation.putTermWithPositiveAssociation(baseTerm);
        break;
    }
    case OperatorLevel::AdditionAndSubtraction:
    case OperatorLevel::RaiseToPower:
    {
        clearAndSetTerm(getBaseTermConstReferenceFromTerm(Term(Expression(*this))));
        m_commonOperatorLevel = OperatorLevel::MultiplicationAndDivision;
        m_termsWithPriorityAndAssociation.putTermWithPositiveAssociation(baseTerm);
        break;
    }
    }
}

void Expression::divideTerm(BaseTerm const& baseTerm)
{
    switch(m_commonOperatorLevel)
    {
    case OperatorLevel::Unknown:
        m_commonOperatorLevel = OperatorLevel::MultiplicationAndDivision;
    case OperatorLevel::MultiplicationAndDivision:
    {
        m_termsWithPriorityAndAssociation.putTermWithNegativeAssociation(baseTerm);
        break;
    }
    case OperatorLevel::AdditionAndSubtraction:
    case OperatorLevel::RaiseToPower:
    {
        clearAndSetTerm(getBaseTermConstReferenceFromTerm(Term(Expression(*this))));
        m_commonOperatorLevel = OperatorLevel::MultiplicationAndDivision;
        m_termsWithPriorityAndAssociation.putTermWithNegativeAssociation(baseTerm);
        break;
    }
    }
}

void Expression::raiseToPowerTerm(BaseTerm const& baseTerm)
{
    switch(m_commonOperatorLevel)
    {
    case OperatorLevel::Unknown:
        m_commonOperatorLevel = OperatorLevel::RaiseToPower;
    case OperatorLevel::RaiseToPower:
    {
        m_termsWithPriorityAndAssociation.putTermWithPositiveAssociation(baseTerm);
        break;
    }
    case OperatorLevel::AdditionAndSubtraction:
    case OperatorLevel::MultiplicationAndDivision:
    {
        clearAndSetTerm(getBaseTermConstReferenceFromTerm(Term(Expression(*this))));
        m_commonOperatorLevel = OperatorLevel::RaiseToPower;
        m_termsWithPriorityAndAssociation.putTermWithPositiveAssociation(baseTerm);
        break;
    }
    }
}

void Expression::setCommonOperatorLevel(OperatorLevel const operatorLevel)
{
    m_commonOperatorLevel = operatorLevel;
}

void Expression::reverseTheAssociationOfTheTerms()
{
    m_termsWithPriorityAndAssociation.reverseTheAssociationOfTheTerms();
}


}

}
