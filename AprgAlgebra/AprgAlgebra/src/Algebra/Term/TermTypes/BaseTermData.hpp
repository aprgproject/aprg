#pragma once

namespace alba::algebra {

class BaseTermData {
public:
    BaseTermData() = default;
    virtual ~BaseTermData() = default;  // virtual destructor because it needs to be polymorphically deleted
    BaseTermData(BaseTermData const &) = default;
    BaseTermData(BaseTermData &&) noexcept = default;
    BaseTermData &operator=(BaseTermData const &) = default;
    BaseTermData &operator=(BaseTermData &&) noexcept = default;
};

}  // namespace alba::algebra
