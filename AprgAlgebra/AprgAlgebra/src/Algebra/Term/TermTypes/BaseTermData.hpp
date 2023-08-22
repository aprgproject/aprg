#pragma once

namespace alba::algebra {

class BaseTermData {
public:
    BaseTermData() = default;
    virtual ~BaseTermData() = default;  // virtual destructor because it needs to be polymorphically deleted
};

}  // namespace alba
