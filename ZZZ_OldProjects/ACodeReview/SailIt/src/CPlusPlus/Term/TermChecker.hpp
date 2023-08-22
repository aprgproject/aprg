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
    explicit TermChecker(TermCheckerType const termCheckerType);
    explicit TermChecker(Term const& term);
    nitializer_list<Term> const& initializerList);

    explicit explicit explicit operator Term() const;
    friend ostream& operator<<(ostream& out, TermChecker const& termChecker);
    bool operator==(Term const& term) const;
    friend bool operator==(Term const& term, TermChecker const& termChecker);
    bool operator!=(Term const& term) const;
    friend bool operator!=(Term const& term, TermChecker const& termChecker);

    bool isCorrect(Term const& termToCheck) const;
    TermCheckerType getTermCheckerType() const;
    Term getTerm() const;
    string getTermCheckerTypeString() const;

private:
    TermCheckerType m_termCheckerType;
    Term m_term;
    alba::AlbaOptional<MultipleTerms> m_multipleTermsOptional;
};

}  // namespace codeReview
