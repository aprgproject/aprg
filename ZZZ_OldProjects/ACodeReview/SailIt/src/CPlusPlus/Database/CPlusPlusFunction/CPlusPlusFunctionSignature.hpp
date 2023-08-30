#pragma once

#include <CPlusPlus/Database/CPlusPlusFunction/CPlusPlusFunctionParameter.hpp>
#include <CPlusPlus/Database/CPlusPlusType.hpp>

#include <string>
#include <vector>

using std::string;
using std::vector;

namespace codeReview {

using CPlusPlusFunctionParameters = vector<CPlusPlusFunctionParameter>;

class CPlusPlusFunctionSignature {
public:
    void printSignature() const;
    CPlusPlusType& getReturnTypeReference();
    [[nodiscard]] CPlusPlusType getReturnType() const;
    void setReturnType(CPlusPlusType const& type);
    void addParameter(CPlusPlusType const& type);
    void addParameter(CPlusPlusType const& type, string const& name);
    bool operator==(CPlusPlusFunctionSignature const& cPlusPlusFunctionSignature) const;
    [[nodiscard]] bool isEqualBasedFromFunctionCall(CPlusPlusFunctionSignature const& cPlusPlusFunctionSignature) const;
    [[nodiscard]] bool areTheNamesEqual(CPlusPlusFunctionSignature const& cPlusPlusFunctionSignature) const;
    CPlusPlusFunctionParameters& getFunctionParametersReference();

private:
    CPlusPlusType m_returnType;
    CPlusPlusFunctionParameters m_parameters;
};

}  // namespace codeReview
