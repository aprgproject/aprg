#pragma once

#include <Algebra/Term/TermTypes/TermWithDetails.hpp>

namespace alba::algebra {

class TermsWithAssociation {
public:
    friend class Expression;
    TermsWithAssociation() = default;
    // NOLINTBEGIN(google-explicit-constructor,hicpp-explicit-conversions)
    TermsWithAssociation(TermsWithDetails const& termsWithDetails);
    TermsWithAssociation(TermsWithDetails&& termsWithDetails);
    TermsWithAssociation(std::initializer_list<TermWithDetails> const& termsWithDetails);
    // NOLINTEND(google-explicit-constructor,hicpp-explicit-conversions)
    // rule of zero
    bool operator==(TermsWithAssociation const& second) const;
    bool operator!=(TermsWithAssociation const& second) const;
    bool operator<(TermsWithAssociation const& second) const;
    [[nodiscard]] BaseTerm const& getFirstTerm() const;
    [[nodiscard]] TermAssociationType getFirstAssociationType() const;
    [[nodiscard]] TermsWithDetails const& getTermsWithDetails() const;
    [[nodiscard]] int getSize() const;
    [[nodiscard]] bool isEmpty() const;
    void clear();
    void sort(bool const dontSortFirstItem);
    void putTermWithDetails(TermWithDetails const& termWithDetails);
    void putTermsWithDetails(std::initializer_list<TermWithDetails> const& termsWithDetails);
    void putTermsWithDetails(TermsWithDetails const& termsWithDetails);
    void putTermWithAssociation(BaseTerm const& baseTerm, TermAssociationType const associationType);
    void putTermWithPositiveAssociation(BaseTerm const& baseTerm);
    void putTermWithNegativeAssociation(BaseTerm const& baseTerm);
    void reverseTheAssociationOfTheTerms();
    TermsWithDetails& getTermsWithDetailsReference();

private:
    TermsWithDetails m_termsWithDetails;
};

}  // namespace alba::algebra
