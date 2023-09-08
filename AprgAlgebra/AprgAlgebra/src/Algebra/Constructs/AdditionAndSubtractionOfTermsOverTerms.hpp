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
        int const itemIndex, Terms const& lcmOfDenominatorTerms) const;
    void putAsAddition(TermsOverTerms const& addend);
    void putAsSubtraction(TermsOverTerms const& subtrahend);
    void putAsAddOrSubtraction(TermsOverTerms const& item, TermAssociationType const association);

private:
    static Monomial getCombinedMonomialMultiplier(Terms const& monomialMultiplierTerms);
    static Expression getCombinedDenominatorExpression(Terms const& lcmDenominatorTerms);
    static TermsOverTerms getSimplifiedTermsOverTerms(TermsOverTerms const& termsOverTerms);
    static void eraseCommonFactorOrAddDistinctFactor(
        Term const& termToCheck, Terms& commonFactors, Terms& outputFactors);
    static void emplaceMonomialMultiplierIfNeeded(Terms& numeratorTerms, Monomial const& monomialMultiplier);
    static void emplaceNonMonomialMultipliers(Terms& numeratorTerms, Terms const& nonMonomialMultiplierTerms);
    static void combineExpressionAsAddOrSubtract(
        Expression& combinedExpression, Expression const& expression, TermAssociationType const association);
    [[nodiscard]] Expression getCombinedNumeratorExpression(Terms const& lcmDenominatorTerms) const;
    [[nodiscard]] Expression getCombinedExpressionForNumeratorOnIndex(
        int const numeratorIndex, Terms const& lcmDenominatorTerms) const;
    void updateMonomialAndNonMonomialMultipliersBasedOnDenominatorOnIndex(
        int const itemIndex, Monomial& monomialMultiplier, Terms& nonMonomialMultiplierTerms) const;
    void emplaceExistingNumeratorTerms(Terms& numeratorTerms, int const itemIndex) const;
    void putItem(TermsOverTerms const& item, TermAssociationType const association);
    VectorOfTermsOverTerms m_items;
    TermAssociationTypes m_associations;
};

}  // namespace alba::algebra
