#pragma once

namespace alba::booleanAlgebra {

class BaseTermData {
public:
    BaseTermData() = default;
    virtual ~BaseTermData() = default;  // virtual destructor because of virtual functions (vtable exists)
};

}  // namespace alba::booleanAlgebra
