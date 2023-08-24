#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba::algebra {

class AdditionAndSubtractionOfExpressions {
public:
    AdditionAndSubtractionOfExpressions();
    explicit AdditionAndSubtractionOfExpressions(TermsWithDetails const& termsWithDetails);

    [[nodiscard]] Expressions const& getExpressions() const;
    [[nodiscard]] TermAssociationTypes const& getAssociations() const;
    [[nodiscard]] int getSize() const;
    [[nodiscard]] TermsWithDetails getAsTermsWithDetails() const;

    Term getCombinedTerm();

    void putAsAddition(Expression const& expression);
    void putAsSubtraction(Expression const& expression);
    void putAsAddOrSubtraction(Expression const& expression, TermAssociationType const association);
    void putTermsWithDetails(TermsWithDetails const& termsWithDetails);

    void combineExpressionsIfPossible();

private:
    void mergeExpressionsByCheckingTwoTermsAtATime(Terms& mergeParts, Terms& commonParts);
    static Term mergeTerms(
        Term const& mergePart1, Term const& mergePart2, TermAssociationType const association1,
        TermAssociationType const association2);
    static void prepareCommonParts(Terms& commonParts);
    void retrieveMergeParts(Terms& mergeParts);
    void retrieveCommonParts(Terms& commonParts);
    static void retrieveMergePart(Term& mergePart, Expression const& expression);
    static void retrieveCommonPart(Term& commonPart, Expression const& expression);
    [[nodiscard]] bool doAllSizesMatch(Terms const& mergeParts, Terms const& commonParts) const;
    static bool canBeMerged(
        Term const& mergePart1, Term const& mergePart2, Term const& commonPart1, Term const& commonPart2);
    void putItem(Expression const& expression, TermAssociationType const association);
    Expressions m_expressions;
    TermAssociationTypes m_associations;
};

}  // namespace alba::algebra
