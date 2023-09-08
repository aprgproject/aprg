#pragma once

#include <Algebra/Term/TermTypes/TermWithDetails.hpp>

namespace alba::algebra {

class TermsWithAssociation {
public:
    friend class Expression;
    TermsWithAssociation() = default;
    // NOLINTNEXTLINE(google-explicit-constructor,hicpp-explicit-conversions)
    TermsWithAssociation(TermsWithDetails const& termsWithDetails);
    TermsWithAssociation(std::initializer_list<TermWithDetails> const& termsWithDetails);
    // rule of zero
    bool operator==(TermsWithAssociation const& second) const;
    bool operator!=(TermsWithAssociation const& second) const;
    bool operator<(TermsWithAssociation const& second) const;
    [[nodiscard]] bool isEmpty() const;
    [[nodiscard]] int getSize() const;
    [[nodiscard]] BaseTerm const& getFirstTerm() const;
    [[nodiscard]] TermAssociationType getFirstAssociationType() const;
    [[nodiscard]] TermsWithDetails const& getTermsWithDetails() const;
    TermsWithDetails& getTermsWithDetailsReference();
    void clear();
    void sort(bool const dontSortFirstItem);
    void putTermWithDetails(TermWithDetails const& termWithDetails);
    void putTermsWithDetails(std::initializer_list<TermWithDetails> const& termsWithDetails);
    void putTermsWithDetails(TermsWithDetails const& termsWithDetails);
    void putTermWithAssociation(BaseTerm const& baseTerm, TermAssociationType const associationType);
    void putTermWithPositiveAssociation(BaseTerm const& baseTerm);
    void putTermWithNegativeAssociation(BaseTerm const& baseTerm);
    void reverseTheAssociationOfTheTerms();

private:
    TermsWithDetails m_termsWithDetails;
};

}  // namespace alba::algebra
