#include "TermUtilities.hpp"

#include <algorithm>

using namespace std;

namespace alba::CodeUtilities {

PatternIndexes findFirstPatternIgnoringSpacesAndComments(
    Terms const& terms, TermMatchers const& matchers, int const startIndex) {
    for (int termIndex = startIndex; termIndex < static_cast<int>(terms.size()); ++termIndex) {
        int matchIndex = 0;
        PatternIndexes patternIndexes;
        for (int termIndexInPattern = termIndex;
             termIndexInPattern < static_cast<int>(terms.size()) && matchIndex < static_cast<int>(matchers.size());
             ++termIndexInPattern) {
            Term const& currentTerm(terms[termIndexInPattern]);
            bool isAMatch = currentTerm == matchers[matchIndex];
            if (isAMatch) {
                patternIndexes.emplace_back(termIndexInPattern);
                ++matchIndex;
            }
            if (!isCommentOrWhiteSpace(currentTerm) && !isAMatch) {
                break;
            }
        }
        if (static_cast<int>(patternIndexes.size()) == static_cast<int>(matchers.size())) {
            return patternIndexes;
        }
    }
    return {};
}

void combineTermsInPlace(Terms& terms, TermType const newTermType, int const startIndex, int const endIndex) {
    if (startIndex < endIndex) {
        string combinedContent;
        for (int termIndex = startIndex; termIndex <= endIndex && termIndex < static_cast<int>(terms.size());
             ++termIndex) {
            combinedContent += terms[termIndex].getContent();
        }
        Term& firstTerm(terms[startIndex]);
        firstTerm.setTermType(newTermType);
        firstTerm.setContent(combinedContent);
        terms.erase(terms.begin() + startIndex + 1, terms.begin() + endIndex + 1);
    }
}

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

bool isComment(Term const& term) {
    return term.getTermType() == TermType::CommentMultiline || term.getTermType() == TermType::CommentSingleLine;
}

bool isWhiteSpace(Term const& term) { return term.getTermType() == TermType::WhiteSpace; }

bool isCommentOrWhiteSpace(Term const& term) { return isComment(term) || isWhiteSpace(term); }

}  // namespace alba::CodeUtilities
