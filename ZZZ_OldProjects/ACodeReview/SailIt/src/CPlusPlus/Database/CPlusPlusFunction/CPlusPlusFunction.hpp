#pragma once

#include <CPlusPlus/Database/CPlusPlusFunction/CPlusPlusFunctionSignature.hpp>
#include <CPlusPlus/Database/CPlusPlusType.hpp>
#include <Common/Container/AlbaOptional.hpp>

#include <string>
#include <vector>

using std::string;
using std::vector;

namespace codeReview {

class CPlusPlusClassTemplateSignature;

typedef vector<CPlusPlusFunctionSignature> CPlusPlusFunctionSignatures;

class CPlusPlusFunction {
public:
    CPlusPlusFunction();
    void printSignatures() const;
    [[nodiscard]] bool isFunctionSignatureExist(CPlusPlusFunctionSignature const& cPlusPlusFunctionSignature) const;
    [[nodiscard]] bool isFunctionSignatureExistBasedFromFunctionCall(
        CPlusPlusFunctionSignature const& cPlusPlusFunctionSignature) const;
    [[nodiscard]] bool isFunctionSignatureExistAndNamesDoesNotMatch(
        CPlusPlusFunctionSignature const& cPlusPlusFunctionSignature) const;
    void addFunctionSignature(CPlusPlusFunctionSignature const& cPlusPlusFunctionSignature);
    void replaceTemplateParameters(
        CPlusPlusClassTemplateSignature& templateSignature, CPlusPlusClassTemplateSignature& templateInstantiation);
    CPlusPlusFunctionSignatures& getFunctionSignaturesReference();
    [[nodiscard]] CPlusPlusType getReturnTypeWithSignature(CPlusPlusFunctionSignature const& cPlusPlusFunctionSignature) const;

private:
    CPlusPlusFunctionSignatures m_signatures;
};

typedef alba::AlbaOptional<CPlusPlusFunction> CPlusPlusFunctionOptional;

}  // namespace codeReview
