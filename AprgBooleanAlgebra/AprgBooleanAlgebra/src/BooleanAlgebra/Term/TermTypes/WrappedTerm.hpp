#pragma once

#include <BooleanAlgebra/Term/TermTypes/BaseTermPointers.hpp>

#include <string>
#include <vector>

namespace alba::booleanAlgebra {

struct WrappedTerm {
    // NOLINTBEGIN(google-explicit-constructor,hicpp-explicit-conversions)
    WrappedTerm(BaseTerm const& baseTerm);
    WrappedTerm(BaseTerm&& baseTerm);
    // NOLINTEND(google-explicit-constructor,hicpp-explicit-conversions)
    // rule of five or six
    ~WrappedTerm() = default;
    WrappedTerm(WrappedTerm const& wrappedTerm);
    WrappedTerm(WrappedTerm&& wrappedTerm) noexcept = default;
    WrappedTerm& operator=(WrappedTerm const& wrappedTerm);
    WrappedTerm& operator=(WrappedTerm&& wrappedTerm) noexcept = default;
    bool operator==(WrappedTerm const& second) const;
    bool operator!=(WrappedTerm const& second) const;
    bool operator<(WrappedTerm const& second) const;
    void clear();
    friend std::ostream& operator<<(std::ostream& out, WrappedTerm const& wrappedTerm);
    BaseTermUniquePointer baseTermPointer;
};

using WrappedTerms = std::vector<WrappedTerm>;

}  // namespace alba::booleanAlgebra
