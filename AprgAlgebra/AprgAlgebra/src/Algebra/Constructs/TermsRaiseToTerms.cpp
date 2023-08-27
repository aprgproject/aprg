#include "TermsRaiseToTerms.hpp"

namespace alba::algebra {

TermsRaiseToTerms::TermsRaiseToTerms() = default;

TermsRaiseToTerms::TermsRaiseToTerms(BaseToExponentMap const& baseToExponentMap)
    : TermsRaiseToTermsBase(baseToExponentMap) {}

}  // namespace alba::algebra
