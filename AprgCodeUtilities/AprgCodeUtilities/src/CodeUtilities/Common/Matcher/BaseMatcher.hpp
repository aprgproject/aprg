#pragma once

#include <CodeUtilities/Common/Term/Term.hpp>

#include <memory>

namespace alba::CodeUtilities {

class BaseMatcher {
public:
    using BaseMatcherPtr = std::unique_ptr<BaseMatcher>;
    // virtual destructor because it needs to be polymorphically deleted
    virtual ~BaseMatcher() = default;
    BaseMatcher() = default;
    BaseMatcher(BaseMatcher const &) = default;
    BaseMatcher(BaseMatcher &&) = default;
    BaseMatcher &operator=(BaseMatcher const &) = default;
    BaseMatcher &operator=(BaseMatcher &&) = default;
    [[nodiscard]] virtual BaseMatcherPtr createClone() const = 0;
    [[nodiscard]] virtual bool isAMatch(Term const &term) const = 0;
};

}  // namespace alba::CodeUtilities
