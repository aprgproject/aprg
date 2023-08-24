#pragma once

#include <CPlusPlus/Utilities.hpp>

#include <map>
#include <string>

using std::map;
using std::pair;
using std::string;

namespace codeReview {

class CPlusPlusNamespace {
public:
    [[nodiscard]] bool isVariable(string const& variableName) const;
    [[nodiscard]] bool isFunction(string const& functionName) const;
    [[nodiscard]] bool isClass(string const& className) const;
    [[nodiscard]] bool isNamespace(string const& namespaceName) const;

    VectorOfStrings& getVariableNamesReference();
    VectorOfStrings& getFunctionNamesReference();
    VectorOfStrings& getClassNamesReference();
    VectorOfStrings& getNamespaceNamesReference();

    void addVariable(string const& variableName);
    void addFunction(string const& functionName);
    void addClass(string const& className);
    void addNamespace(string const& namespaceName);

private:
    VectorOfStrings m_variables;
    VectorOfStrings m_functions;
    VectorOfStrings m_classes;
    VectorOfStrings m_namespaces;
};

}  // namespace codeReview
