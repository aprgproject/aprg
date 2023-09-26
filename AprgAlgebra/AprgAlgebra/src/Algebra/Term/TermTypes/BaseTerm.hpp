#pragma once

#include <string>

namespace alba::algebra {

class BaseTerm {
public:
    BaseTerm() = default;
    virtual ~BaseTerm() = default;  // virtual destructor because it needs to be polymorphically deleted
    BaseTerm(BaseTerm const &) = default;
    BaseTerm(BaseTerm &&) noexcept = default;
    BaseTerm &operator=(BaseTerm const &) = default;
    BaseTerm &operator=(BaseTerm &&) noexcept = default;
};

}  // namespace alba::algebra
