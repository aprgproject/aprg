#include "TermsRaiseToNumbers.hpp"

namespace alba::algebra {

TermsRaiseToNumbers::TermsRaiseToNumbers() = default;

TermsRaiseToNumbers::TermsRaiseToNumbers(BaseToExponentMap const& baseToExponentMap)
    : TermsRaiseToNumbersBase(baseToExponentMap) {}

}  // namespace alba::algebra
