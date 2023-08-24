#pragma once

#include <CPlusPlus/Database/CPlusPlusType.hpp>

#include <string>

namespace codeReview {

class CPlusPlusFunctionParameter {
public:
    explicit CPlusPlusFunctionParameter(CPlusPlusType const& type, string const& name);
    bool operator==(CPlusPlusFunctionParameter const& cPlusPlusFunctionParameter) const;
    [[nodiscard]] bool isEqualBasedFromFunctionCall(CPlusPlusFunctionParameter const& cPlusPlusFunctionParameter) const;
    [[nodiscard]] bool areTheNamesEqual(CPlusPlusFunctionParameter const& cPlusPlusFunctionParameter) const;
    [[nodiscard]] string getName() const;
    [[nodiscard]] CPlusPlusType getType() const;
    void set(CPlusPlusType const& type, string const& name);

private:
    CPlusPlusType m_type;
    string m_name;
};

}  // namespace codeReview
