#pragma once

#include <CPlusPlus/Database/CPlusPlusType.hpp>

#include <string>

using std::string;

namespace codeReview {

class CPlusPlusVariable {
public:
    CPlusPlusVariable();
    explicit CPlusPlusVariable(CPlusPlusType const& cPlusPlusType);
    [[nodiscard]] CPlusPlusType getType() const;

private:
    CPlusPlusType m_type;
};

}  // namespace codeReview
