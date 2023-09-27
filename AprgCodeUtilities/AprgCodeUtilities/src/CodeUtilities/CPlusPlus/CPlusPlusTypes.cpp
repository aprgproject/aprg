#include "CPlusPlusTypes.hpp"

#include <Common/Macros/AlbaMacros.hpp>

using namespace std;

namespace alba::CodeUtilities {

string getString(ScopeType const enumValue) {
    switch (enumValue) {
        ALBA_MACROS_CASE_ENUM_STRING(ScopeType::AnonymousNamespace)
        ALBA_MACROS_CASE_ENUM_STRING(ScopeType::ClassDeclaration)
        ALBA_MACROS_CASE_ENUM_STRING(ScopeType::EnumClass)
        ALBA_MACROS_CASE_ENUM_STRING(ScopeType::NamedNamespace)
        ALBA_MACROS_CASE_ENUM_STRING(ScopeType::TopLevel)
        ALBA_MACROS_CASE_ENUM_STRING(ScopeType::Unknown)
        default:
            return "default";
    }
}

string getString(CppFileType const enumValue) {
    switch (enumValue) {
        ALBA_MACROS_CASE_ENUM_STRING(CppFileType::CppFile)
        ALBA_MACROS_CASE_ENUM_STRING(CppFileType::HeaderFile)
        ALBA_MACROS_CASE_ENUM_STRING(CppFileType::Unknown)
        default:
            return "default";
    }
}

ostream& operator<<(ostream& out, ScopeType const enumValue) {
    out << getString(enumValue);
    return out;
}

ostream& operator<<(ostream& out, CppFileType const enumValue) {
    out << getString(enumValue);
    return out;
}

}  // namespace alba::CodeUtilities
