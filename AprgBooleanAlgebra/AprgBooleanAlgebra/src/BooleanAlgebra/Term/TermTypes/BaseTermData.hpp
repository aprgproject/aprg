#pragma once

namespace alba::booleanAlgebra {

class BaseTermData {
public:
    virtual ~BaseTermData() = default;  // virtual destructor because of virtual functions (vtable exists)
    BaseTermData() = default;
};

}  // namespace alba::booleanAlgebra
