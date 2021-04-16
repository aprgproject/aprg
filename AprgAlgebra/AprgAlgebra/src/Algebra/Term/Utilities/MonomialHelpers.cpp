#include "MonomialHelpers.hpp"

#include <Algebra/Retrieval/VariableNamesRetriever.hpp>
#include <Common/Math/AlbaMathHelper.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace algebra
{

bool canBeMergedInAMonomialByAdditionOrSubtraction(Term const& term1, Term const& term2)
{
    bool result(false);
    if(term1.isConstant() && term2.isConstant())
    {
        result = true;
    }
    else if(term1.isVariable() && term2.isVariable())
    {
        result = canBeMergedInAMonomialByAdditionOrSubtraction(term1.getVariableConstReference(), term2.getVariableConstReference());
    }
    else if(term1.isMonomial() && term2.isMonomial())
    {
        result = canBeMergedInAMonomialByAdditionOrSubtraction(term1.getMonomialConstReference(), term2.getMonomialConstReference());
    }
    else if(term1.isMonomial() && term2.isVariable())
    {
        result = canBeMergedInAMonomialByAdditionOrSubtraction(term1.getMonomialConstReference(), term2.getVariableConstReference());
    }
    else if(term1.isVariable() && term2.isMonomial())
    {
        result = canBeMergedInAMonomialByAdditionOrSubtraction(term2.getMonomialConstReference(), term1.getVariableConstReference());
    }
    return result;
}

bool canBeMergedInAMonomialByAdditionOrSubtraction(Monomial const& monomial1, Monomial const& monomial2)
{
    Monomial::VariablesToExponentsMap const& variablesMap1(monomial1.getVariablesToExponentsMapConstReference());
    Monomial::VariablesToExponentsMap const& variablesMap2(monomial2.getVariablesToExponentsMapConstReference());
    bool result(false);
    if(variablesMap1.size() == variablesMap2.size())
    {
        using MapConstIterator=Monomial::VariablesToExponentsMap::const_iterator;
        using MismatchResultType=pair<MapConstIterator, MapConstIterator>;
        MismatchResultType mismatchResult = mismatch(variablesMap1.cbegin(), variablesMap1.end(), variablesMap2.cbegin());
        result = mismatchResult.first == variablesMap1.cend();
    }
    return result;
}

bool canBeMergedInAMonomialByAdditionOrSubtraction(Monomial const& monomial, Variable const& variable)
{
    Monomial::VariablesToExponentsMap const& variablesMap(monomial.getVariablesToExponentsMapConstReference());
    string variableName(variable.getVariableName());
    bool result(false);
    if(variablesMap.size() == 1)
    {
        if(variablesMap.find(variableName) != variablesMap.cend())
        {
            result = variablesMap.at(variableName)==1;
        }
    }
    return result;
}

bool canBeMergedInAMonomialByAdditionOrSubtraction(Variable const& variable1, Variable const& variable2)
{
    return variable1.getVariableName() == variable2.getDisplayableString();
}

bool doesCoefficientsHaveSameSign(Monomial const& monomial1, Monomial const& monomial2)
{
    return getSign(monomial1.getConstantConstReference()) == getSign(monomial2.getConstantConstReference());
}

bool hasNegativeExponents(Monomial const& monomial)
{
    bool result(false);
    for(auto const& variableExponentsPair
        : monomial.getVariablesToExponentsMapConstReference())
    {
        if(variableExponentsPair.second < 0)
        {
            result=true;
            break;
        }
    }
    return result;
}

bool isConstantOnly(Monomial const& monomial)
{
    Monomial::VariablesToExponentsMap const& variableToExponentMap(
                monomial.getVariablesToExponentsMapConstReference());
    return variableToExponentMap.empty();
}

bool isVariableOnly(Monomial const& monomial)
{
    Monomial::VariablesToExponentsMap const& variableToExponentMap(
                monomial.getVariablesToExponentsMapConstReference());
    return monomial.getConstantConstReference() == 1 &&
            variableToExponentMap.size() == 1 &&
            (variableToExponentMap.cbegin())->second == 1;
}

bool hasASingleVariable(Monomial const& monomial)
{
    Monomial::VariablesToExponentsMap const& variableToExponentMap(
                monomial.getVariablesToExponentsMapConstReference());
    return variableToExponentMap.size() == 1;
}

string getFirstVariableName(Monomial const& monomial)
{
    Monomial::VariablesToExponentsMap const& variableToExponentMap(
                monomial.getVariablesToExponentsMapConstReference());
    string variableName;
    if(!variableToExponentMap.empty())
    {
        variableName = (variableToExponentMap.cbegin())->first;
    }
    return variableName;
}

AlbaNumber getDegree(Monomial const& monomial)
{
    AlbaNumber degree;
    for(auto const& variableExponentPair : monomial.getVariablesToExponentsMapConstReference())
    {
        degree = degree + variableExponentPair.second;
    }
    return degree;
}

AlbaNumber getMaxExponent(Monomial const& monomial)
{
    AlbaNumber maxExponent;
    bool isFirst(true);
    for(auto const& variableExponentPair : monomial.getVariablesToExponentsMapConstReference())
    {
        if(isFirst)
        {
            maxExponent = variableExponentPair.second;
            isFirst = false;
        }
        else
        {
            maxExponent = max(maxExponent, variableExponentPair.second);
        }
    }
    return maxExponent;
}

AlbaNumber getGcfOfExponentsInMonomial(Monomial const& monomial)
{
    AlbaNumber commonExponent(1);
    bool isFirst(true);
    for(auto const& variablePair : monomial.getVariablesToExponentsMapConstReference())
    {
        AlbaNumber const& exponent(variablePair.second);
        if(exponent.isIntegerOrFractionType())
        {
            if(isFirst)
            {
                commonExponent = exponent;
                isFirst = false;
            }
            else
            {
                commonExponent = getGreatestCommonFactor(commonExponent, exponent);
            }
        }
    }
    return commonExponent;
}

AlbaNumber getGcfOfCoefficientsInMonomials(Monomials const& monomials)
{
    AlbaNumber commonCoefficient(1);
    bool isFirst(true);
    for(Monomial const& monomial : monomials)
    {
        AlbaNumber const& coefficient(monomial.getConstantConstReference());
        if(coefficient.isIntegerOrFractionType())
        {
            if(isFirst)
            {
                commonCoefficient = coefficient;
                isFirst = false;
            }
            else
            {
                commonCoefficient = getGreatestCommonFactor(commonCoefficient, coefficient);
            }
        }
    }
    return commonCoefficient;
}

AlbaNumber getLcmOfCoefficientsInMonomials(Monomials const& monomials)
{
    AlbaNumber commonCoefficient(1);
    bool isFirst(true);
    for(Monomial const& monomial : monomials)
    {
        AlbaNumber const& coefficient(monomial.getConstantConstReference());
        if(coefficient.isIntegerOrFractionType())
        {
            if(isFirst)
            {
                commonCoefficient = coefficient;
                isFirst = false;
            }
            else
            {
                commonCoefficient = getLeastCommonMultiple(commonCoefficient, coefficient);
            }
        }
    }
    return commonCoefficient;
}

AlbaNumber getCommonSignInMonomials(Monomials const& monomials)
{
    bool isFirst(true);
    bool isFirstMonomialNegative(false);
    unsigned int negativeSignCount(0);
    for(Monomial const& monomial : monomials)
    {
        if(monomial.getConstantConstReference() < AlbaNumber(0))
        {
            negativeSignCount++;
            if(isFirst)
            {
                isFirstMonomialNegative = true;
            }
        }
        isFirst=false;
    }
    return (isFirstMonomialNegative||(negativeSignCount>0 && negativeSignCount == monomials.size())) ? -1 : 1;
}

Monomial getGcfMonomialInMonomials(Monomials const& monomials)
{
    AlbaNumber commonCoefficient(getGcfOfCoefficientsInMonomials(monomials));
    Monomial minExponentMonomial(getMonomialWithMinimumExponentsInMonomials(monomials));
    if(commonCoefficient != 1)
    {
        commonCoefficient = getCommonSignInMonomials(monomials)*commonCoefficient;
    }
    minExponentMonomial.setConstant(commonCoefficient);
    minExponentMonomial.simplify();
    return minExponentMonomial;
}

Monomial getLcmMonomialInMonomials(Monomials const& monomials)
{
    AlbaNumber lcmCoefficient(getLcmOfCoefficientsInMonomials(monomials));
    Monomial maxExponentMonomial(getMonomialWithMaximumExponentsInMonomials(monomials));
    maxExponentMonomial.setConstant(getCommonSignInMonomials(monomials)*lcmCoefficient);
    maxExponentMonomial.simplify();
    return maxExponentMonomial;
}

Monomial compareMonomialsAndSaveMinimumExponentsForEachVariable(Monomial const& firstMonomial, Monomial const& secondMonomial)
{
    Monomial::VariablesToExponentsMap newVariableExponentMap;
    VariableNamesRetriever variableNamesRetriever;
    variableNamesRetriever.retrieveFromMonomial(firstMonomial);
    variableNamesRetriever.retrieveFromMonomial(secondMonomial);
    for(string const& variableName : variableNamesRetriever.getSavedData())
    {
        newVariableExponentMap[variableName] = min(
                    firstMonomial.getExponentForVariable(variableName),
                    secondMonomial.getExponentForVariable(variableName));
    }
    return Monomial(1, newVariableExponentMap);
}

Monomial compareMonomialsAndSaveMaximumExponentsForEachVariable(Monomial const& firstMonomial, Monomial const& secondMonomial)
{
    Monomial::VariablesToExponentsMap newVariableExponentMap;
    VariableNamesRetriever variableNamesRetriever;
    variableNamesRetriever.retrieveFromMonomial(firstMonomial);
    variableNamesRetriever.retrieveFromMonomial(secondMonomial);
    for(string const& variableName : variableNamesRetriever.getSavedData())
    {
        newVariableExponentMap[variableName] = max(
                    firstMonomial.getExponentForVariable(variableName),
                    secondMonomial.getExponentForVariable(variableName));
    }
    return Monomial(1, newVariableExponentMap);
}

Monomial getMonomialWithMinimumExponentsInMonomials(Monomials const& monomials)
{
    Monomial monomialWithMinimumExponents(1, {});
    bool isFirst(true);
    for(Monomial const& monomial : monomials)
    {
        if(isFirst)
        {
            monomialWithMinimumExponents = monomial;
            isFirst=false;
        }
        else
        {
            monomialWithMinimumExponents
                    = compareMonomialsAndSaveMinimumExponentsForEachVariable(monomialWithMinimumExponents, monomial);
        }
    }
    monomialWithMinimumExponents.simplify();
    return monomialWithMinimumExponents;
}

Monomial getMonomialWithMaximumExponentsInMonomials(Monomials const& monomials)
{
    Monomial monomialWithMaximumExponents(1, {});
    bool isFirst(true);
    for(Monomial const& monomial : monomials)
    {
        if(isFirst)
        {
            monomialWithMaximumExponents = monomial;
            isFirst=false;
        }
        else
        {
            monomialWithMaximumExponents
                    = compareMonomialsAndSaveMaximumExponentsForEachVariable(monomialWithMaximumExponents, monomial);
        }
    }
    monomialWithMaximumExponents.simplify();
    return monomialWithMaximumExponents;
}


}

}
