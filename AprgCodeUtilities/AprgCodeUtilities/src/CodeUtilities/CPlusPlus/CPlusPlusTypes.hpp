#pragma once

namespace alba::CodeUtilities {

enum class ScopeType { AnonymousNamespace, ClassDeclaration, EnumClass, NamedNamespace, TopLevel, Unknown };

enum class CppFileType { CppFile, HeaderFile, Unknown };

}  // namespace alba::CodeUtilities
