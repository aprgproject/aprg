#pragma once

#include <Algebra/Term/TermTypes/TermWithDetails.hpp>

namespace alba::algebra {

class TermsWithAssociation {
public:
    friend class Expression;

    TermsWithAssociation() = default;
    explicit TermsWithAssociation(TermsWithDetails const& termsWithDetails);
    TermsWithAssociation(std::initializer_list<TermWithDetails> const& termsWithDetails);

    // rule of zero

    bool operator==(TermsWithAssociation const& second) const;
    bool operator!=(TermsWithAssociation const& second) const;
    bool operator<(TermsWithAssociation const& second) const;
    [[nodiscard]] bool isEmpty([[nodiscard]] ) const;

    [[nodiscard[[nodiscard]] ]] int getSize() const;
    [[nodiscard]] BaseTerm const& getFirstTerm() const;
    [[nodiscard]] T[[nodiscard]] ermAssociationType getFirstAssociationType() const;
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
    void reverseTheAssociation  // namespace alba::algebraate:
    TermsWithDetails m_termsWithDetails;
};

}  // namespace alba::algebra
