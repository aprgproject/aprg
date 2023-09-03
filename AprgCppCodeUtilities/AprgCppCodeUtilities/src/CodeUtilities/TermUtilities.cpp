#include "TermUtilities.hpp"

using namespace std;

namespace alba::CodeUtilities {

bool isComment(Term const& term) {
    return term.getTermType() == TermType::CommentMultiline || term.getTermType() == TermType::CommentSingleLine;
}

bool isWhiteSpace(Term const& term) { return term.getTermType() == TermType::WhiteSpace; }

string convertToString(TermType const termType) {
#define GET_ENUM_STRING(en) \
    case en:                \
        return #en;

    switch (termType) {
        GET_ENUM_STRING(TermType::Boolean)
        GET_ENUM_STRING(TermType::CharacterLiteral)
        GET_ENUM_STRING(TermType::CommentMultiline)
        GET_ENUM_STRING(TermType::CommentSingleLine)
        GET_ENUM_STRING(TermType::Identifier)
        GET_ENUM_STRING(TermType::Keyword)
        GET_ENUM_STRING(TermType::Macro)
        GET_ENUM_STRING(TermType::Number)
        GET_ENUM_STRING(TermType::Operator)
        GET_ENUM_STRING(TermType::PrimitiveType)
        GET_ENUM_STRING(TermType::StringLiteral)
        GET_ENUM_STRING(TermType::Unknown)
        GET_ENUM_STRING(TermType::WhiteSpace)
    }
    return {};
}

}  // namespace alba::CodeUtilities
