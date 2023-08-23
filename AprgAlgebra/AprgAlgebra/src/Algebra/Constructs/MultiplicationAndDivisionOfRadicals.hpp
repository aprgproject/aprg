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

    MultiplicationAndDivisionOfRadicals();
    explicit MultiplicationAndDivisionOfRadicals(TermsWithDetails const& termsWithDetails);

    [[nodiscard]] Term getCombinedTerm() const;
    [[nodiscard]] TermsWithDetails const& getTermsWithDetails() const;

    void simplify();

private:
    static bool shouldBeCombined(
        RadicalDetails const& radicalDetails, Monomial const& combinedMonomial, AlbaNumber const& gcfOfExponents);
    static bool isNotANegativeTermWithExponentDenominatorEven(
        Monomial const& combinedMonomial, AlbaNumber const& gcfOfExponents);
    void gatherDetails(RadicalDetails& radicalDetails, Monomial& combinedMonomial, TermsWithDetails& remainingTerms);
    static AlbaNumber getGcfOfExponents(RadicalDetails const& radicalDetails);
    void combineMonomialAndRadicalsAndSave(
        RadicalDetails const& radicalDetails, Monomial const& combinedMonomial, AlbaNumber const& gcfOfExponents);
    void saveRemainingTerms(TermsWithDetails const& remainingTerms);

    TermsWithDetails m_termsWithDetails;
};

}  // namespace alba
