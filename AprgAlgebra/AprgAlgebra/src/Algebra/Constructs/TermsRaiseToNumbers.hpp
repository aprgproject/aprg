#pragma once

#include <Algebra/Constructs/TermRaiseToANumber.hpp>
#include <Algebra/Constructs/TermsRaiseToExponents.hpp>

namespace alba::algebra {

using TermsRaiseToNumbersBase = TermsRaiseToExponents<AlbaNumber, TermRaiseToANumber>;

class TermsRaiseToNumbers : public TermsRaiseToNumbersBase {
public:
    explicit TermsRaiseToNumbers(BaseToExponentMap const& baseToExponentMap);
    TermsRaiseToNumbers();
};

}  // namespace alba::algebra
