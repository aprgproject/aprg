#pragma once

#include <CodeUtilities/Common/Term/Term.hpp>

#include <memory>

namespace alba::CodeUtilities {

class BaseMatcher {
public:
    using BaseMatcherPtr = std::unique_ptr<BaseMatcher>;
    BaseMatcher() = default;
    // virtual destructor because it needs to be polymorphically deleted
    virtual ~BaseMatcher() = default;
    BaseMatcher(BaseMatcher const &) = default;
    BaseMatcher(BaseMatcher &&) noexcept = default;
    BaseMatcher &operator=(BaseMatcher const &) = default;
    BaseMatcher &operator=(BaseMatcher &&) noexcept = default;
    [[nodiscard]] virtual BaseMatcherPtr createClone() const = 0;
    [[nodiscard]] virtual bool isAMatch(Term const &term) const = 0;
};

}  // namespace alba::CodeUtilities
