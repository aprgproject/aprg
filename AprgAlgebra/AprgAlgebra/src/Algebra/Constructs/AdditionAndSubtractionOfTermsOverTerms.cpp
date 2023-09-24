#include "AdditionAndSubtractionOfTermsOverTerms.hpp"

#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/MonomialHelpers.hpp>
#include <Algebra/Term/Utilities/SegregateHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

#include <algorithm>

namespace alba::algebra {

Expression AdditionAndSubtractionOfTermsOverTerms::getCombinedExpression() const {
    Terms const lcmDenominatorTerms(getLcmOfDenominatorTerms());
    Expression const combinedNumerator = getCombinedNumeratorExpression(lcmDenominatorTerms);
    Expression const combinedDenominator = getCombinedDenominatorExpression(lcmDenominatorTerms);
    Expression combinedExpression;
    combinedExpression.putTermWithMultiplicationIfNeeded(convertExpressionToSimplestTerm(combinedNumerator));
    combinedExpression.putTermWithDivisionIfNeeded(convertExpressionToSimplestTerm(combinedDenominator));
    return combinedExpression;
}

TermAssociationTypes const& AdditionAndSubtractionOfTermsOverTerms::getAssociations() const { return m_associations; }

Terms AdditionAndSubtractionOfTermsOverTerms::getLcmOfDenominatorTerms() const {
    Terms lcmTerms;
    Monomials lcmMonomials;
    for (TermsOverTerms const& item : m_items) {
        Terms currentCommonFactors = lcmTerms;
        for (Term const& denominatorTerm : item.getDenominators()) {
            if (!(isTheValue(denominatorTerm, 1) || denominatorTerm.isEmpty())) {
                if (canBeConvertedToMonomial(denominatorTerm)) {
                    lcmMonomials.emplace_back(createMonomialIfPossible(denominatorTerm));
                } else {
                    eraseCommonFactorOrAddDistinctFactor(denominatorTerm, currentCommonFactors, lcmTerms);
                }
            }
        }
    }
    Monomial const lcmMonomial(getLcmMonomialInMonomials(lcmMonomials));
    if (!isTheValue(lcmMonomial, 1)) {
        lcmTerms.emplace(lcmTerms.begin(), lcmMonomial);
    }
    if (lcmTerms.empty()) {
        lcmTerms.emplace_back(1);
    }
    return lcmTerms;
}

Terms AdditionAndSubtractionOfTermsOverTerms::getRevisedNumeratorTermsBasedOnLcmOnIndex(
    int const itemIndex, Terms const& lcmOfDenominatorTerms) const {
    Terms numeratorTerms;
    if (itemIndex < static_cast<int>(m_items.size())) {
        Terms const& multipliers(lcmOfDenominatorTerms);
        Terms monomialMultiplierTerms;
        Terms nonMonomialMultiplierTerms;
        segregateMonomialsAndNonMonomials(multipliers, monomialMultiplierTerms, nonMonomialMultiplierTerms);
        Monomial monomialMultiplier(getCombinedMonomialMultiplier(monomialMultiplierTerms));
        updateMonomialAndNonMonomialMultipliersBasedOnDenominatorOnIndex(
            itemIndex, monomialMultiplier, nonMonomialMultiplierTerms);
        emplaceExistingNumeratorTerms(numeratorTerms, itemIndex);
        emplaceMonomialMultiplierIfNeeded(numeratorTerms, monomialMultiplier);
        emplaceNonMonomialMultipliers(numeratorTerms, nonMonomialMultiplierTerms);
    }
    return numeratorTerms;
}

VectorOfTermsOverTerms const& AdditionAndSubtractionOfTermsOverTerms::getItems() const { return m_items; }

void AdditionAndSubtractionOfTermsOverTerms::putAsAddition(TermsOverTerms const& addend) {
    putItem(getSimplifiedTermsOverTerms(addend), TermAssociationType::Positive);
}

void AdditionAndSubtractionOfTermsOverTerms::putAsSubtraction(TermsOverTerms const& subtrahend) {
    putItem(getSimplifiedTermsOverTerms(subtrahend), TermAssociationType::Negative);
}

void AdditionAndSubtractionOfTermsOverTerms::putAsAddOrSubtraction(
    TermsOverTerms const& item, TermAssociationType const association) {
    putItem(getSimplifiedTermsOverTerms(item), association);
}

Expression AdditionAndSubtractionOfTermsOverTerms::getCombinedNumeratorExpression(
    Terms const& lcmDenominatorTerms) const {
    Expression combinedNumerator;
    int const numberOfItems = static_cast<int>(m_items.size());
    for (int numeratorIndex = 0; numeratorIndex < numberOfItems; ++numeratorIndex) {
        Expression const combinedNumeratorOnIndex(
            getCombinedExpressionForNumeratorOnIndex(numeratorIndex, lcmDenominatorTerms));
        combineExpressionAsAddOrSubtract(combinedNumerator, combinedNumeratorOnIndex, m_associations[numeratorIndex]);
    }
    return combinedNumerator;
}

Expression AdditionAndSubtractionOfTermsOverTerms::getCombinedExpressionForNumeratorOnIndex(
    int const numeratorIndex, Terms const& lcmDenominatorTerms) const {
    Expression combinedNumeratorOnIndex(Term(1));
    Terms const numeratorTermsOnIndex(getRevisedNumeratorTermsBasedOnLcmOnIndex(numeratorIndex, lcmDenominatorTerms));
    for (Term const& numeratorTermOnIndex : numeratorTermsOnIndex) {
        combinedNumeratorOnIndex.putTermWithMultiplicationIfNeeded(numeratorTermOnIndex);
    }
    return combinedNumeratorOnIndex;
}

void AdditionAndSubtractionOfTermsOverTerms::updateMonomialAndNonMonomialMultipliersBasedOnDenominatorOnIndex(
    int const itemIndex, Monomial& monomialMultiplier, Terms& nonMonomialMultiplierTerms) const {
    for (Term const& denominatorTerm : m_items[itemIndex].getDenominators()) {
        if (canBeConvertedToMonomial(denominatorTerm)) {
            monomialMultiplier.divideMonomial(createMonomialIfPossible(denominatorTerm));
        } else {
            auto multiplierIterator =
                find(nonMonomialMultiplierTerms.begin(), nonMonomialMultiplierTerms.end(), denominatorTerm);
            if (multiplierIterator != nonMonomialMultiplierTerms.end()) {
                nonMonomialMultiplierTerms.erase(multiplierIterator);
            }
        }
    }
}

void AdditionAndSubtractionOfTermsOverTerms::emplaceExistingNumeratorTerms(
    Terms& numeratorTerms, int const itemIndex) const {
    Terms const& termsToCopy(m_items[itemIndex].getNumerators());
    numeratorTerms.reserve(numeratorTerms.size() + termsToCopy.size());
    copy(termsToCopy.cbegin(), termsToCopy.cend(), back_inserter(numeratorTerms));
}

void AdditionAndSubtractionOfTermsOverTerms::putItem(
    TermsOverTerms const& item, TermAssociationType const association) {
    m_items.emplace_back(item);
    m_associations.emplace_back(association);
}

void AdditionAndSubtractionOfTermsOverTerms::eraseCommonFactorOrAddDistinctFactor(
    Term const& termToCheck, Terms& commonFactors, Terms& outputFactors) {
    auto matchedTermIterator = find(commonFactors.begin(), commonFactors.end(), termToCheck);
    if (matchedTermIterator == commonFactors.end()) {
        outputFactors.emplace_back(termToCheck);
    } else {
        commonFactors.erase(matchedTermIterator);
    }
}

void AdditionAndSubtractionOfTermsOverTerms::emplaceMonomialMultiplierIfNeeded(
    Terms& numeratorTerms, Monomial const& monomialMultiplier) {
    if (!isTheValue(monomialMultiplier, 1)) {
        numeratorTerms.emplace_back(monomialMultiplier);
    }
}

void AdditionAndSubtractionOfTermsOverTerms::emplaceNonMonomialMultipliers(
    Terms& numeratorTerms, Terms const& nonMonomialMultiplierTerms) {
    numeratorTerms.reserve(numeratorTerms.size() + nonMonomialMultiplierTerms.size());
    copy(nonMonomialMultiplierTerms.cbegin(), nonMonomialMultiplierTerms.cend(), back_inserter(numeratorTerms));
}

void AdditionAndSubtractionOfTermsOverTerms::combineExpressionAsAddOrSubtract(
    Expression& combinedExpression, Expression const& expression, TermAssociationType const association) {
    if (TermAssociationType::Positive == association) {
        combinedExpression.putTermWithAdditionIfNeeded(Term(expression));
    } else {
        combinedExpression.putTermWithSubtractionIfNeeded(Term(expression));
    }
}

Expression AdditionAndSubtractionOfTermsOverTerms::getCombinedDenominatorExpression(Terms const& lcmDenominatorTerms) {
    Expression combinedDenominator;
    for (Term const& denominatorTerm : lcmDenominatorTerms) {
        combinedDenominator.putTermWithMultiplicationIfNeeded(denominatorTerm);
    }
    return combinedDenominator;
}

Monomial AdditionAndSubtractionOfTermsOverTerms::getCombinedMonomialMultiplier(Terms const& monomialMultiplierTerms) {
    Monomials monomialMultipliers;
    monomialMultipliers.reserve(monomialMultiplierTerms.size());
    transform(
        monomialMultiplierTerms.cbegin(), monomialMultiplierTerms.cend(), back_inserter(monomialMultipliers),
        [&](Term const& monomialMultiplierTerm) { return createMonomialIfPossible(monomialMultiplierTerm); });
    return getLcmMonomialInMonomials(monomialMultipliers);
}

TermsOverTerms AdditionAndSubtractionOfTermsOverTerms::getSimplifiedTermsOverTerms(
    TermsOverTerms const& termsOverTerms) {
    TermsOverTerms termsOverTermsSimplified(termsOverTerms);
    termsOverTermsSimplified.setAsShouldSimplifyToFactors(true);
    termsOverTermsSimplified.simplify();
    return termsOverTermsSimplified;
}

AdditionAndSubtractionOfTermsOverTerms::AdditionAndSubtractionOfTermsOverTerms() = default;

}  // namespace alba::algebra
