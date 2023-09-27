#pragma once

#include <ostream>
#include <string>

namespace alba::CodeUtilities {

enum class ScopeType { AnonymousNamespace, ClassDeclaration, EnumClass, NamedNamespace, TopLevel, Unknown };

enum class CppFileType { CppFile, HeaderFile, Unknown };

std::ostream& operator<<(std::ostream& out, ScopeType const enumValue);
std::ostream& operator<<(std::ostream& out, CppFileType const enumValue);
std::string getString(ScopeType const enumValue);
std::string getString(CppFileType const enumValue);

}  // namespace alba::CodeUtilities
