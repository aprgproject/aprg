#pragma once

#include <string>

namespace alba::algebra {

class BaseTerm {
public:
    virtual ~BaseTerm() = default;  // virtual destructor because it needs to be polymorphically deleted
    BaseTerm() = default;
    BaseTerm(BaseTerm const &) = default;
    BaseTerm(BaseTerm &&) = default;
    BaseTerm &operator=(BaseTerm const &) = default;
    BaseTerm &operator=(BaseTerm &&) = default;
};

}  // namespace alba::algebra
