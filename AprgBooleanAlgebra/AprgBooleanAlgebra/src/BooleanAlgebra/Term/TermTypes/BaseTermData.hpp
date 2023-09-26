#pragma once

namespace alba::booleanAlgebra {

class BaseTermData {
public:
    BaseTermData() = default;
    virtual ~BaseTermData() = default;  // virtual destructor because of virtual functions (vtable exists)
    BaseTermData(BaseTermData const &) = default;
    BaseTermData(BaseTermData &&) noexcept = default;
    BaseTermData &operator=(BaseTermData const &) = default;
    BaseTermData &operator=(BaseTermData &&) noexcept = default;
};

}  // namespace alba::booleanAlgebra
