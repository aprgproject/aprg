#pragma once

#include <Algebra/Constructs/TermRaiseToTerms.hpp>
#include <Algebra/Constructs/TermsRaiseToExponents.hpp>

namespace alba::algebra {

using TermsRaiseToTermsBase = TermsRaiseToExponents<Term, TermRaiseToTerms>;

class TermsRaiseToTerms : public TermsRaiseToTermsBase {
public:
    TermsRaiseToTerms();
    explicit TermsRaiseToTerms(BaseToExponentMap const& baseToExponentMap);
};

}  // namespace alba::algebra
