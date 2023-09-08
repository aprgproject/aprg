#pragma once

#include <string>

namespace alba::booleanAlgebra {

class BaseTerm {
public:
    virtual ~BaseTerm() = default;  // virtual destructor because of virtual functions (vtable exists)
    BaseTerm() = default;

private:
};

std::ostream& operator<<(std::ostream& out, BaseTerm const& baseTerm);

}  // namespace alba::booleanAlgebra
