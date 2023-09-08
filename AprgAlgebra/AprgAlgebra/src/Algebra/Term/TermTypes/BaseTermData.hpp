#pragma once

namespace alba::algebra {

class BaseTermData {
public:
    virtual ~BaseTermData() = default;  // virtual destructor because it needs to be polymorphically deleted
    BaseTermData() = default;
};

}  // namespace alba::algebra
