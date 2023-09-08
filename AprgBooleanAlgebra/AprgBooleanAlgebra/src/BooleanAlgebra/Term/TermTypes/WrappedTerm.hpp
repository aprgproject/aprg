#pragma once

#include <BooleanAlgebra/Term/TermTypes/BaseTermPointers.hpp>

#include <string>
#include <vector>

namespace alba::booleanAlgebra {

struct WrappedTerm {
    // NOLINTEND(google-explicit-constructor,hicpp-explicit-conversions)
    // rule of five or six
    ~WrappedTerm() = default;
    WrappedTerm(WrappedTerm&& wrappedTerm) = default;
    WrappedTerm& operator=(WrappedTerm&& wrappedTerm) = default;
    // NOLINTBEGIN(google-explicit-constructor,hicpp-explicit-conversions)
    WrappedTerm(BaseTerm const& baseTerm);
    WrappedTerm(BaseTerm&& baseTerm);
    WrappedTerm(WrappedTerm const& wrappedTerm);
    WrappedTerm& operator=(WrappedTerm const& wrappedTerm);
    bool operator==(WrappedTerm const& second) const;
    bool operator!=(WrappedTerm const& second) const;
    bool operator<(WrappedTerm const& second) const;
    void clear();
    friend std::ostream& operator<<(std::ostream& out, WrappedTerm const& wrappedTerm);
    BaseTermUniquePointer baseTermPointer;
};

using WrappedTerms = std::vector<WrappedTerm>;

}  // namespace alba::booleanAlgebra
