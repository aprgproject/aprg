#pragma once

#include <CPlusPlus/Utilities.hpp>

#include <string>

using std::string;

namespace codeReview {

struct CPlusPlusClassTemplateParameter;
struct CPlusPlusClassTemplateSignature;
class CPlusPlusClass;

using CPlusPlusClassTemplateParameters = vector<CPlusPlusClassTemplateParameter>;
using CPlusPlusClassTemplateSignatures = vector<CPlusPlusClassTemplateSignature>;

class CPlusPlusClassTemplateParameter {
public:
    CPlusPlusClassTemplateParameter(CPlusPlusType type, string name);
    [[nodiscard]] string getString() const;
    [[nodiscard]] string getName() const;
    [[nodiscard]] CPlusPlusType getType() const;
    bool operator==(CPlusPlusClassTemplateParameter const& cPlusPlusClassTemplateParameter) const;

private:
    CPlusPlusType m_type;
    string m_name;
};

class CPlusPlusClassTemplateSignature {
public:
    void addParameter(CPlusPlusType type, string name);
    [[nodiscard]] string getString() const;
    bool operator==(CPlusPlusClassTemplateSignature const& cPlusPlusClassTemplateSignature) const;
    CPlusPlusClassTemplateParameters& getTemplateParametersReference();
    [[nodiscard]] int getNumberOfParameters() const;

private:
    CPlusPlusClassTemplateParameters m_templateParameters;
};

class CPlusPlusClass {
public:
    explicit CPlusPlusClass();
    explicit CPlusPlusClass(string const& className);

    [[nodiscard]] bool isVariable(string const& variableName) const;
    [[nodiscard]] bool isFunction(string const& functionName) const;
    [[nodiscard]] bool isClass(string const& className) const;
    [[nodiscard]] bool isNamespace(string const& namespaceName) const;

    CPlusPlusType& getTypeReference();
    VectorOfStrings& getClassNamesReference();
    VectorOfStrings& getFunctionNamesReference();
    VectorOfStrings& getNamespaceNamesReference();
    VectorOfStrings& getVariableNamesReference();

    void addClass(string const& className);
    void addFunction(string const& functionName);
    void addNamespace(string const& namespaceName);
    void addVariable(string const& variableName);

protected:
    VectorOfStrings m_classes;
    VectorOfStrings m_functions;
    VectorOfStrings m_namespaces;
    VectorOfStrings m_variables;

private:
    CPlusPlusType m_type;
};

class CPlusPlusTemplateClass : public CPlusPlusClass {
public:
    explicit CPlusPlusTemplateClass();
    explicit CPlusPlusTemplateClass(
        string const& templateClassName, CPlusPlusClassTemplateSignature const& cPlusPlusClassTemplateSignature);
    void addTemplateInstantiation(CPlusPlusClassTemplateSignature const& cPlusPlusClassTemplateSignature);
    CPlusPlusType getTemplateClassInstantiationType(
        CPlusPlusClassTemplateSignature const& cPlusPlusClassTemplateSignature);
    CPlusPlusType& getTypeReference();
    CPlusPlusClassTemplateSignature& getTemplateSignatureReference();
    CPlusPlusClassTemplateSignature& getTemplateSignatureInstantiationReference(int instantiationIndex);

private:
    CPlusPlusClassTemplateSignature m_templateSignature;
    CPlusPlusClassTemplateSignatures m_templateInstantiations;
    CPlusPlusType m_type;
};

}  // namespace codeReview
