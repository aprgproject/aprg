#pragma once

namespace alba::booleanAlgebra {

class BaseTermData {
public:
    virtual ~BaseTermData() = default;  // virtual destructor because of virtual functions (vtable exists)
    BaseTermData() = default;
    BaseTermData(BaseTermData const &) = default;
    BaseTermData(BaseTermData &&) = default;
    BaseTermData &operator=(BaseTermData const &) = default;
    BaseTermData &operator=(BaseTermData &&) = default;
};

}  // namespace alba::booleanAlgebra
