#pragma once

#include <Algebra/Term/TermTypes/BaseTermPointers.hpp>
#include <Algebra/Term/TermTypes/TermAssociationType.hpp>

#include <string>
#include <vector>

namespace alba::algebra {

struct TermWithDetails {
    TermWithDetails(BaseTerm const& baseTerm, TermAssociationType const associationParameter);
    TermWithDetails(BaseTerm&& baseTerm, TermAssociationType const associationParameter);
    // rule of five or six
    ~TermWithDetails() = default;
    TermWithDetails(TermWithDetails const& termWithDetails);
    TermWithDetails(TermWithDetails&& termWithDetails) noexcept = default;
    TermWithDetails& operator=(TermWithDetails const& termWithDetails);
    TermWithDetails& operator=(TermWithDetails&& termWithDetails) noexcept = default;
    bool operator==(TermWithDetails const& second) const;
    bool operator!=(TermWithDetails const& second) const;
    bool operator<(TermWithDetails const& second) const;
    [[nodiscard]] int getAssociationPriority() const;
    [[nodiscard]] bool hasPositiveAssociation() const;
    [[nodiscard]] bool hasNegativeAssociation() const;
    void clear();
    void reverseAssociation();
    BaseTermUniquePointer baseTermPointer;
    TermAssociationType association;
};

using TermsWithDetails = std::vector<TermWithDetails>;

}  // namespace alba::algebra
