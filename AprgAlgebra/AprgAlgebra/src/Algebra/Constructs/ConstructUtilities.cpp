#include "ConstructUtilities.hpp"

#include <Algebra/Constructs/PolynomialRaiseToAnUnsignedInt.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/MonomialHelpers.hpp>
#include <Algebra/Term/Utilities/SegregateHelpers.hpp>
#include <Optional/AlbaOptional.hpp>

using namespace std;

namespace alba
{

namespace algebra
{

PolynomialOverPolynomialOptional createPolynomialOverPolynomialFromTermIfPossible(
        Term const& term)
{
    PolynomialOverPolynomialOptional result;
    Term simplifiedTerm(term);
    simplifiedTerm.simplify();

    if(canBeConvertedToPolynomial(simplifiedTerm))
    {
        result.setConstReference(PolynomialOverPolynomial(createPolynomialIfPossible(simplifiedTerm), createPolynomialFromConstant(1)));
    }
    else if(simplifiedTerm.isExpression())
    {
        Expression const& expression(simplifiedTerm.getExpressionConstReference());
        if(OperatorLevel::MultiplicationAndDivision == expression.getCommonOperatorLevel())
        {
            bool canBeConvertedToPolynomialOverPolynomial(true);
            Polynomial numerator(createPolynomialFromConstant(1));
            Polynomial denominator(createPolynomialFromConstant(1));
            for(TermWithDetails const& termWithDetails
                : expression.getTermsWithAssociation().getTermsWithDetails())
            {
                Term const& termInExpression(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
                if(canBeConvertedToPolynomial(termInExpression))
                {
                    if(termWithDetails.hasPositiveAssociation())
                    {
                        numerator.multiplyPolynomial(createPolynomialIfPossible(termInExpression));
                    }
                    else
                    {
                        denominator.multiplyPolynomial(createPolynomialIfPossible(termInExpression));
                    }
                }
                else
                {
                    canBeConvertedToPolynomialOverPolynomial=false;
                    break;
                }
            }
            if(canBeConvertedToPolynomialOverPolynomial)
            {
                result.setConstReference(PolynomialOverPolynomial(numerator, denominator));
            }
        }
    }
    if(result.hasContent())
    {
        result.getReference().simplify();
    }
    return result;
}

TermsOverTerms createTermsOverTermsFromTerm(Term const& term)
{
    TermsOverTerms result;
    Term simplifiedTerm(term);
    simplifiedTerm.simplify();

    bool isResultUpdatedWithContent(false);
    if(simplifiedTerm.isExpression())
    {
        Expression const& expression(simplifiedTerm.getExpressionConstReference());
        if(OperatorLevel::MultiplicationAndDivision == expression.getCommonOperatorLevel())
        {
            TermsWithDetails numerators;
            TermsWithDetails denominators;
            segregateTermsWithPositiveAndNegativeAssociations(expression.getTermsWithAssociation().getTermsWithDetails(), numerators, denominators);
            result = TermsOverTerms(numerators, denominators);
            isResultUpdatedWithContent=true;
        }
    }
    if(!isResultUpdatedWithContent)
    {
        result = TermsOverTerms({simplifiedTerm}, {Term(1)});
    }
    result.simplify();
    return result;
}

TermRaiseToANumber createTermRaiseToANumberFromTerm(Term const& term)
{
    TermRaiseToANumber result;
    Term simplifiedTerm(term);
    simplifiedTerm.simplify();

    if(simplifiedTerm.isMonomial())
    {
        result = createTermRaiseToANumberFromMonomial(simplifiedTerm.getMonomialConstReference());
    }
    else if(simplifiedTerm.isPolynomial())
    {
        result = createTermRaiseToANumberFromPolynomial(simplifiedTerm.getPolynomialConstReference());
    }
    else if(simplifiedTerm.isExpression())
    {
        result = createTermRaiseToANumberFromExpression(simplifiedTerm.getExpressionConstReference());
    }
    if(!result.isEmpty())
    {
        result.getBaseReference().simplify();
    }
    else
    {
        result = TermRaiseToANumber(simplifiedTerm, 1);
    }
    return result;
}

TermRaiseToANumber createTermRaiseToANumberFromMonomial(Monomial const& monomial)
{
    Monomial newMonomial(monomial);
    Monomial::VariablesToExponentsMap const& variablesToExponentsMap(
                newMonomial.getVariablesToExponentsMapConstReference());
    AlbaNumber exponent = (variablesToExponentsMap.size() == 1)
            ? (variablesToExponentsMap.cbegin())->second
            : getGcfOfExponentsInMonomial(newMonomial);
    newMonomial.raiseToPowerNumber(AlbaNumber(1)/exponent);
    return TermRaiseToANumber(Term(newMonomial), exponent);
}

TermRaiseToANumber createTermRaiseToANumberFromPolynomial(Polynomial const& polynomial)
{
    PolynomialRaiseToAnUnsignedInt polynomialRaiseToAnUnsignedInt(polynomial);
    return TermRaiseToANumber(Term(polynomialRaiseToAnUnsignedInt.getBase()), polynomialRaiseToAnUnsignedInt.getExponent());
}

TermRaiseToANumber createTermRaiseToANumberFromExpression(Expression const& expression)
{
    TermRaiseToANumber result;
    if(OperatorLevel::RaiseToPower == expression.getCommonOperatorLevel())
    {
        TermsWithDetails raiseToPowerTerms(expression.getTermsWithAssociation().getTermsWithDetails());
        if(raiseToPowerTerms.size() == 1)
        {
            Term const& base(getTermConstReferenceFromSharedPointer(raiseToPowerTerms.back().baseTermSharedPointer));
            result = TermRaiseToANumber(base, 1);
        }
        else if(raiseToPowerTerms.size() >= 2)
        {
            Term const& exponent(getTermConstReferenceFromSharedPointer(raiseToPowerTerms.back().baseTermSharedPointer));
            if(exponent.isConstant())
            {
                Term const& base(getTermConstReferenceFromSharedPointer(raiseToPowerTerms.front().baseTermSharedPointer));
                result = TermRaiseToANumber(base, exponent.getConstantValueConstReference());
            }
            else if(exponent.isMonomial())
            {
                Monomial oldExponentMonomial(exponent.getMonomialConstReference());
                AlbaNumber newExponentValue(oldExponentMonomial.getConstantConstReference());
                raiseToPowerTerms.pop_back();
                Expression newBaseExpression;
                newBaseExpression.setCommonOperatorLevel(OperatorLevel::RaiseToPower);
                newBaseExpression.putTermsWithDetails(raiseToPowerTerms);
                oldExponentMonomial.setConstant(1);
                newBaseExpression.putTermWithRaiseToPowerIfNeeded(Term(oldExponentMonomial));
                result = TermRaiseToANumber(Term(newBaseExpression), newExponentValue);
            }
            // how about if exponent is polynomial or expression? should we introduce factorization here?
        }
    }
    return result;
}

}

}
