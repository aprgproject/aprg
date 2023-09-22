#pragma once

namespace alba::algebra {

class BaseTermData {
public:
    virtual ~BaseTermData() = default;  // virtual destructor because it needs to be polymorphically deleted
    BaseTermData() = default;
    BaseTermData(BaseTermData const &) = default;
    BaseTermData(BaseTermData &&) = default;
    BaseTermData &operator=(BaseTermData const &) = default;
    BaseTermData &operator=(BaseTermData &&) = default;
};

}  // namespace alba::algebra
