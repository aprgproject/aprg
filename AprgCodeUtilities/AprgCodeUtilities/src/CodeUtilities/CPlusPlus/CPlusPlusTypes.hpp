#pragma once

namespace alba::CodeUtilities {

enum class ScopeType { Unknown, TopLevel, NamedNamespace, AnonymousNamespace, ClassDeclaration, EnumClass };
enum class CppFileType { Unknown, HeaderFile, CppFile };

}  // namespace alba::CodeUtilities
