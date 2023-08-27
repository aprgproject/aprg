#pragma once

#include <Algebra/Constructs/TermsOverTerms.hpp>

namespace alba::algebra {

class AdditionAndSubtractionOfTermsOverTerms {
public:
    AdditionAndSubtractionOfTermsOverTerms();

    [[nodiscard]] VectorOfTermsOverTerms const& getItems() const;
    [[nodiscard]] TermAssociationTypes const& getAssociations() const;
    [[nodiscard]] Expression getCombinedExpression() const;
    [[nodiscard]] Terms getLcmOfDenominatorTerms() const;
    [[nodiscard]] Terms getRevisedNumeratorTermsBasedOnLcmOnIndex(
        int itemIndex, Terms const& lcmOfDenominatorTerms) const;

    void putAsAddition(TermsOverTerms const& addend);
    void putAsSubtraction(TermsOverTerms const& subtrahend);
    void putAsAddOrSubtraction(TermsOverTerms const& item, TermAssociationType const association);

private:
    static void eraseCommonFactorOrAddDistinctFactor(
        Term const& termToCheck, Terms& commonFactors, Terms& outputFactors);
    static Monomial getCombinedMonomialMultiplier(Terms const& monomialMultiplierTerms);
    void updateMonomialAndNonMonomialMultipliersBasedOnDenominatorOnIndex(
        int itemIndex, Monomial& monomialMultiplier, Terms& nonMonomialMultiplierTerms) const;
    void emplaceExistingNumeratorTerms(Terms& numeratorTerms, int itemIndex) const;
    static void emplaceMonomialMultiplierIfNeeded(Terms& numeratorTerms, Monomial const& monomialMultiplier);
    static void emplaceNonMonomialMultipliers(Terms& numeratorTerms, Terms const& nonMonomialMultiplierTerms);
    [[nodiscard]] Expression getCombinedNumeratorExpression(Terms const& lcmDenominatorTerms) const;
    static Expression getCombinedDenominatorExpression(Terms const& lcmDenominatorTerms);
    [[nodiscard]] Expression getCombinedExpressionForNumeratorOnIndex(
        int numeratorIndex, Terms const& lcmDenominatorTerms) const;
    static void combineExpressionAsAddOrSubtract(
        Expression& combinedExpression, Expression const& expression, TermAssociationType const association);
    static TermsOverTerms getSimplifiedTermsOverTerms(TermsOverTerms const& termsOverTerms);
    void putItem(TermsOverTerms const& item, TermAssociationType const association);
    VectorOfTermsOverTerms m_items;
    TermAssociationTypes m_associations;
};

}  // namespace alba::algebra
