#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

#include <map>

namespace alba::algebra {

template <typename ExponentType, typename BaseRaiseToExponentType>
class TermsRaiseToExponents {
public:
    using BaseToExponentMap = std::map<Term, ExponentType>;
    using BaseExponentPair = std::pair<Term, ExponentType>;
    TermsRaiseToExponents();
    explicit TermsRaiseToExponents(BaseToExponentMap const& baseToExponentMap);
    explicit TermsRaiseToExponents(BaseToExponentMap&& baseToExponentMap);
    [[nodiscard]] BaseToExponentMap const& getBaseToExponentMap() const;
    [[nodiscard]] ExponentType getExponentOfBase(Term const& base) const;
    [[nodiscard]] Term getCombinedTerm() const;
    [[nodiscard]] Terms getTermsInMultiplicationOperation() const;
    [[nodiscard]] TermsWithDetails getTermWithDetailsInMultiplicationAndDivisionOperation() const;
    void addExponents(TermsRaiseToExponents const& termsRaiseToNumbers);
    void subtractExponents(TermsRaiseToExponents const& termsRaiseToNumbers);
    void multiplyToExponents(ExponentType const& exponent);
    void putTerm(Term const& term, TermAssociationType const association);
    void putTerms(Terms const& terms, TermAssociationType const association);
    void setBaseAndExponent(Term const& base, ExponentType const& exponent);
    void removeItemWithBase(Term const& base);
    void clear();
    void simplify();

protected:
    [[nodiscard]] Term convertToTerm(Term const& base, ExponentType const& exponent) const;
    [[nodiscard]] bool isNegative(ExponentType const& exponent) const;
    void removeItemsWithExponentsZero();
    void putTermUsingBaseToExponentType(Term const& term, int const sign);
    BaseToExponentMap m_baseToExponentMap;
};

}  // namespace alba::algebra
