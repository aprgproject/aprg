#pragma once

#include <string>

namespace alba::booleanAlgebra {

class BaseTerm {
public:
    BaseTerm() = default;
    virtual ~BaseTerm() = default;  // virtual destructor because of virtual functions (vtable exists)

private:
};

std::ostream& operator<<(std::ostream& out, BaseTerm const& baseTerm);

}  // namespace alba::booleanAlgebra
