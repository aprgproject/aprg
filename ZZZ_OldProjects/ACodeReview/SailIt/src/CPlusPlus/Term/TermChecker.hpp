#pragma once

#include <CPlusPlus/Term/MultipleTerms.hpp>
#include <CPlusPlus/Term/Term.hpp>
#include <Common/Container/AlbaOptional.hpp>

#include <ostream>
#include <string>

using alba::AlbaOptional;
using std::ostream;
using std::string;

namespace codeReview {

enum class TermCheckerType {
    ConcreteTerm,
    isAssignmentOperator,
    isBiDirectionalOperator,
    isConstant,
    isProcessed,
    isIncrementDecrementOperator,
    isLValue,
    isOtherMacro,
    isPrefixOperator,
    isRelationalBiDirectionalOperator,
    isRelationalPrefixOperator,
    isRValue,
    isStopForTermSimplification,
    isCPlusPlusType,
    isValue,
    MultipleTerms
};

class TermChecker {
public:
    // NOLINTBEGIN(google-explicit-constructor,hicpp-explicit-conversions)
    TermChecker(TermCheckerType const termCheckerType);
    TermChecker(Term const& term);
    TermChecker(std::initializer_list<Term> const& initializerList);

    operator Term() const;
    // NOLINTEND(google-explicit-constructor,hicpp-explicit-conversions)
    friend ostream& operator<<(ostream& out, TermChecker const& termChecker);
    bool operator==(Term const& term) const;
    friend bool operator==(Term const& term, TermChecker const& termChecker);
    bool operator!=(Term const& term) const;
    friend bool operator!=(Term const& term, TermChecker const& termChecker);

    [[nodiscard]] bool isCorrect(Term const& termToCheck) const;
    [[nodiscard]] TermCheckerType getTermCheckerType() const;
    [[nodiscard]] Term getTerm() const;
    [[nodiscard]] string getTermCheckerTypeString() const;

private:
    TermCheckerType m_termCheckerType;
    Term m_term;
    alba::AlbaOptional<MultipleTerms> m_multipleTermsOptional;
};

}  // namespace codeReview
