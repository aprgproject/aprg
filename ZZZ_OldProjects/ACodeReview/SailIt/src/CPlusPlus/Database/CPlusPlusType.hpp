#pragma once

#include <ostream>
#include <string>

using std::ostream;
using std::string;

namespace codeReview {

enum class CPlusPlusTypeType {
    Class,
    ConstantNumber,
    NoType,
    Primitive,
    TemplateClass,
    TemplateClassInstantiation,
    TemplateType
};

class CPlusPlusType {
public:
    CPlusPlusType();
    CPlusPlusType(string const& typeName, CPlusPlusTypeType const cPlusPlusTypeType, int pointerCount = 0);
    friend ostream& operator<<(ostream& out, CPlusPlusType const& cPlusPlusType);
    [[nodiscard]] string getTypeName() const;
    [[nodiscard]] string getString() const;
    [[nodiscard]] int getPointerCount() const;
    [[nodiscard]] int getTemplateInstantiationIndex() const;
    [[nodiscard]] bool isConst() const;
    [[nodiscard]] bool isPrimitive() const;
    [[nodiscard]] bool isClass() const;
    [[nodiscard]] bool isTemplateType() const;
    [[nodiscard]] bool isTemplateClassInstantiation() const;
    [[nodiscard]] bool isNotAPointerOrReference() const;
    [[nodiscard]] bool isPointer() const;
    [[nodiscard]] bool isReference() const;
    [[nodiscard]] bool isEqualIgnoreReference(CPlusPlusType const& type) const;
    static void swapType(CPlusPlusTypeType& type1, CPlusPlusTypeType& type2);

    bool operator==(CPlusPlusType const& cPlusPlusType) const;
    void incrementPointerCount();
    void decrementPointerCount();
    void clearReferenceFlag();
    void setAsReference();
    void setAsConst();
    void set(string const& typeName, CPlusPlusTypeType const cPlusPlusTypeType);
    void setTypeName(string const& typeName);
    void setTemplateInstantiationIndex(int index);

private:
    bool m_isConst;
    bool m_isReference;
    int m_pointerCount;
    CPlusPlusTypeType m_typeType;
    string m_typeName;
    int m_templateInstantationIndex;
};

}  // namespace codeReview
