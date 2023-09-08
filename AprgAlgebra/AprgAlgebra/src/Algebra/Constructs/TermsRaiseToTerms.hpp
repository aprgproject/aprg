#pragma once

#include <Algebra/Constructs/TermRaiseToTerms.hpp>
#include <Algebra/Constructs/TermsRaiseToExponents.hpp>

namespace alba::algebra {

using TermsRaiseToTermsBase = TermsRaiseToExponents<Term, TermRaiseToTerms>;

class TermsRaiseToTerms : public TermsRaiseToTermsBase {
public:
    explicit TermsRaiseToTerms(BaseToExponentMap const& baseToExponentMap);
    TermsRaiseToTerms();
};

}  // namespace alba::algebra
