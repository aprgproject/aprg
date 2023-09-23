#pragma once

#include <Algebra/Constructs/TermRaiseToANumber.hpp>

#include <vector>

namespace alba::algebra {

class MultiplicationAndDivisionOfRadicals {
public:
    struct RadicalDetail {
        TermRaiseToANumber radical;
        TermAssociationType association;
    };

    using RadicalDetails = std::vector<RadicalDetail>;
    explicit MultiplicationAndDivisionOfRadicals(TermsWithDetails const& termsWithDetails);
    explicit MultiplicationAndDivisionOfRadicals(TermsWithDetails&& termsWithDetails);
    MultiplicationAndDivisionOfRadicals();
    [[nodiscard]] Term getCombinedTerm() const;
    [[nodiscard]] TermsWithDetails const& getTermsWithDetails() const;
    void simplify();

private:
    void gatherDetails(RadicalDetails& radicalDetails, Monomial& combinedMonomial, TermsWithDetails& remainingTerms);
    void combineMonomialAndRadicalsAndSave(
        RadicalDetails const& radicalDetails, Monomial const& combinedMonomial, AlbaNumber const& gcfOfExponents);
    void saveRemainingTerms(TermsWithDetails const& remainingTerms);
    static AlbaNumber getGcfOfExponents(RadicalDetails const& radicalDetails);
    static bool shouldBeCombined(
        RadicalDetails const& radicalDetails, Monomial const& combinedMonomial, AlbaNumber const& gcfOfExponents);
    static bool isNotANegativeTermWithExponentDenominatorEven(
        Monomial const& combinedMonomial, AlbaNumber const& gcfOfExponents);
    TermsWithDetails m_termsWithDetails;
};

}  // namespace alba::algebra
