#pragma once

#include <CPlusPlus/Database/CPlusPlusClass/CPlusPlusClass.hpp>
#include <CPlusPlus/Database/CPlusPlusFunction/CPlusPlusFunction.hpp>
#include <CPlusPlus/Database/CPlusPlusMacro.hpp>
#include <CPlusPlus/Database/CPlusPlusNamespace.hpp>
#include <CPlusPlus/Database/CPlusPlusScope.hpp>
#include <CPlusPlus/Database/CPlusPlusVariable.hpp>
#include <CPlusPlus/Utilities.hpp>
#include <Common/Container/AlbaOptional.hpp>

#include <functional>
#include <map>
#include <set>
#include <string>
#include <vector>

using std::function;
using std::map;
using std::pair;
using std::set;
using std::string;
using std::vector;

namespace codeReview {

using IncludeFiles = set<string>;
using IncludeFile = string;
using Classes = map<string, CPlusPlusClass>;
using ClassPair = pair<string, CPlusPlusClass>;
using TemplateClasses = map<string, CPlusPlusTemplateClass>;
using TemplateClassPair = pair<string, CPlusPlusTemplateClass>;
using Functions = map<string, CPlusPlusFunction>;
using FunctionPair = pair<string, CPlusPlusFunction>;
using Macros = map<string, CPlusPlusMacro>;
using MacroPair = pair<string, CPlusPlusMacro>;
using Namespaces = map<string, CPlusPlusNamespace>;
using NamespacePair = pair<string, CPlusPlusNamespace>;
using Types = map<string, CPlusPlusType>;
using TypePair = pair<string, CPlusPlusType>;
using Variables = map<string, CPlusPlusVariable>;
using VariablePair = pair<string, CPlusPlusVariable>;
using Scopes = vector<CPlusPlusScope>;

class CPlusPlusDatabase {
public:
    CPlusPlusDatabase();
    void initializeCStyleArray();

    void print(ostream& outputStream);
    [[nodiscard]] bool isDatabaseModified() const;
    [[nodiscard]] bool isClass(string const& className) const;
    bool isClassWithAlias(string const& className);
    [[nodiscard]] bool isFunction(string const& functionName) const;
    bool isFunctionWithAlias(string const& functionName);
    [[nodiscard]] bool isMacro(string const& macroName) const;
    [[nodiscard]] bool isNamespace(string const& namespaceName) const;
    bool isNamespaceWithAlias(string const& namespaceName);
    [[nodiscard]] bool isType(string const& typeDefName) const;
    [[nodiscard]] bool isVariable(string const& variableName) const;
    bool isVariableWithAlias(string const& variableName);
    [[nodiscard]] bool isTemplateClass(string const& className) const;
    bool isTemplateClassWithAlias(string const& className);

    string getCorrectClassName(string const& className);
    string getCorrectTemplateClassName(string const& templateClassName);
    CPlusPlusClass& getClassReference(string const& className);
    CPlusPlusClass& getClassReferenceWithAlias(string const& className);
    CPlusPlusScope& getCurrentScope();
    CPlusPlusFunction& getFunctionReference(string const& functionName);
    CPlusPlusFunctionOptional getFunctionOptionalInClass(string const& className, string const& functionName);
    CPlusPlusFunctionOptional getFunctionOptionalInTemplateClass(
        string const& templateClassName, string const& functionName, int instantiationIndex);
    CPlusPlusFunction& getFunctionReferenceWithAlias(string const& functionName);
    CPlusPlusNamespace& getNamespaceReference(string const& namespaceName);
    CPlusPlusMacro& getMacroReference(string const& macroName);
    VectorOfTerms& getMacroEquivalentReference(string const& macroName);
    CPlusPlusTemplateClass& getTemplateClassReference(string const& className);
    CPlusPlusTemplateClass& getTemplateClassReferenceWithAlias(string const& className);
    CPlusPlusType& getTypeReferenceWithAlias(string const& typeName);
    CPlusPlusVariable& getVariableReferenceWithAlias(string const& variableName);

    Classes& getClassesReference();
    Functions& getFunctionsReference();
    IncludeFiles& getIncludeFilesReference();
    Macros& getMacrosReference();
    Namespaces& getNamespacesReference();
    TemplateClasses& getTemplateClassesReference();
    Types& getTypesReference();
    VectorOfStrings& getUsingNamespacesReference();
    Variables& getVariablesReference();

    void clearIsDatabaseModified();
    void addClass(string const& className);
    void addFunction(string const& functionName);
    void addIncludeFile(string const& includeFileName);
    void addMacro(string const& macroName);
    void addNamespace(string const& namespaceName);
    void addTemplateClass(
        string const& templateClassName, CPlusPlusClassTemplateSignature const& cPlusPlusClassTemplateSignature);
    void addType(string const& typeDefName, CPlusPlusType const& type);
    void addUsingNamespace(string const& usingNamespace);
    void addVariable(string const& variableName, CPlusPlusType const& cPlusPlusType);
    void removeMacro(string const& macroName);
    void copyContentsOf(CPlusPlusDatabase const& cPlusPlusDatabase);
    void performInNewScope(function<void(void)> perform);
    void performInClass(string const& className, function<void(void)> perform);
    void performInNamespace(string const& namespaceName, function<void(void)> perform);
    void performInTemplateClass(string const& templateClassName, function<void(void)> perform);

private:
    void addClassToScope(string const& className);
    void addFunctionToScope(string const& functionName);
    void addNamespaceToScope(string const& namespaceName);
    void addTypeToScope(string const& namespaceName);
    void addVariableToScope(string const& variableName);
    string getAliasWithCurrentScope(string const& name);
    void enterScope(CPlusPlusScopeType const scopeType, string const& name);
    void exitScope();
    Classes m_classes;
    Functions m_functions;
    IncludeFiles m_includedFiles;
    Macros m_macros;
    Namespaces m_namespaces;
    TemplateClasses m_templateClasses;
    Types m_types;
    Variables m_variables;
    VectorOfStrings m_usingNamespaces;
    Scopes m_scopes;
    bool m_isModified{true};
};

}  // namespace codeReview
