#pragma once

#include <BooleanAlgebra/Term/TermTypes/BaseTermPointers.hpp>

#include <string>
#include <vector>

namespace alba::booleanAlgebra {

struct WrappedTerm {
    WrappedTerm(BaseTerm const& baseTerm);
    WrappedTerm(BaseTerm&& baseTerm);
    // rule of five or six
    // NOLINTBEGIN(google-explicit-constructor,hicpp-explicit-conversions)
    ~WrappedTerm() = default;
    WrappedTerm(WrappedTerm const& wrappedTerm);
    WrappedTerm(WrappedTerm&& wrappedTerm) noexcept = default;
    WrappedTerm& operator=(WrappedTerm const& wrappedTerm);
    WrappedTerm& operator=(WrappedTerm&& wrappedTerm) noexcept = default;
    // NOLINTEND(google-explicit-constructor,hicpp-explicit-conversions)
    bool operator==(WrappedTerm const& second) const;
    bool operator!=(WrappedTerm const& second) const;
    bool operator<(WrappedTerm const& second) const;
    void clear();
    friend std::ostream& operator<<(std::ostream& out, WrappedTerm const& wrappedTerm);
    BaseTermUniquePointer baseTermPointer;
};

using WrappedTerms = std::vector<WrappedTerm>;

}  // namespace alba::booleanAlgebra
