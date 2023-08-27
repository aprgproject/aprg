#pragma once

#include <string>

namespace alba::algebra {

class BaseTerm {
public:
    BaseTerm() = default;
    virtual ~BaseTerm() = default;  // virtual destructor because it needs to be polymorphically deleted
};

}  // namespace alba::algebra
