#pragma once

#include <Algebra/Constructs/TermsOverTerms.hpp>

namespace alba::algebra {

class AdditionAndSubtractionOfTermsOverTerms {
public:
    AdditionAndSubtractionOfTermsOverTerms();
    [[nodiscard]] Expression getCombinedExpression() const;
    [[nodiscard]] TermAssociationTypes const& getAssociations() const;
    [[nodiscard]] Terms getLcmOfDenominatorTerms() const;

    [[nodiscard]] Terms getRevisedNumeratorTermsBasedOnLcmOnIndex(
        int const itemIndex, Terms const& lcmOfDenominatorTerms) const;

    [[nodiscard]] VectorOfTermsOverTerms const& getItems() const;
    void putAsAddition(TermsOverTerms const& addend);
    void putAsSubtraction(TermsOverTerms const& subtrahend);
    void putAsAddOrSubtraction(TermsOverTerms const& item, TermAssociationType const association);

private:
    [[nodiscard]] Expression getCombinedNumeratorExpression(Terms const& lcmDenominatorTerms) const;

    [[nodiscard]] Expression getCombinedExpressionForNumeratorOnIndex(
        int const numeratorIndex, Terms const& lcmDenominatorTerms) const;

    void updateMonomialAndNonMonomialMultipliersBasedOnDenominatorOnIndex(
        int const itemIndex, Monomial& monomialMultiplier, Terms& nonMonomialMultiplierTerms) const;

    void emplaceExistingNumeratorTerms(Terms& numeratorTerms, int const itemIndex) const;
    void putItem(TermsOverTerms const& item, TermAssociationType const association);

    static void eraseCommonFactorOrAddDistinctFactor(
        Term const& termToCheck, Terms& commonFactors, Terms& outputFactors);

    static void emplaceMonomialMultiplierIfNeeded(Terms& numeratorTerms, Monomial const& monomialMultiplier);
    static void emplaceNonMonomialMultipliers(Terms& numeratorTerms, Terms const& nonMonomialMultiplierTerms);

    static void combineExpressionAsAddOrSubtract(
        Expression& combinedExpression, Expression const& expression, TermAssociationType const association);

    static Expression getCombinedDenominatorExpression(Terms const& lcmDenominatorTerms);
    static Monomial getCombinedMonomialMultiplier(Terms const& monomialMultiplierTerms);
    static TermsOverTerms getSimplifiedTermsOverTerms(TermsOverTerms const& termsOverTerms);
    VectorOfTermsOverTerms m_items;
    TermAssociationTypes m_associations;
};

}  // namespace alba::algebra
