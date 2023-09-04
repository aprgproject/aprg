#include "TermUtilities.hpp"

#include <Common/String/AlbaStringHelper.hpp>

#include <algorithm>

using namespace alba::stringHelper;
using namespace std;

namespace alba::CodeUtilities {

Indexes searchForPatternsForwards(Terms const& terms, int const startIndex, Patterns const& searchPatterns) {
    for (int termIndex = startIndex; termIndex < static_cast<int>(terms.size()); ++termIndex) {
        IndexesOptional patternIndexesOptional = checkPatternAt(terms, termIndex, searchPatterns);
        if (patternIndexesOptional) {
            return patternIndexesOptional.value();
        }
    }
    return {};
}

Indexes searchForPatternsBackwards(Terms const& terms, int const startIndex, Patterns const& searchPatterns) {
    for (int termIndex = startIndex; termIndex >= 0; --termIndex) {
        IndexesOptional patternIndexesOptional = checkPatternAt(terms, termIndex, searchPatterns);
        if (patternIndexesOptional) {
            return patternIndexesOptional.value();
        }
    }
    return {};
}

IndexesOptional checkPatternAt(Terms const& terms, int const termIndex, Patterns const& searchPatterns) {
    int matchIndex = 0;
    Indexes patternIndexes;
    for (Pattern const& searchPattern : searchPatterns) {
        for (int termIndex2 = termIndex;
             termIndex2 < static_cast<int>(terms.size()) && matchIndex < static_cast<int>(searchPattern.size());
             ++termIndex2) {
            Term const& currentTerm(terms[termIndex2]);
            bool isMatchForThisIndex = currentTerm == searchPattern[matchIndex];
            if (isMatchForThisIndex) {
                patternIndexes.emplace_back(termIndex2);
                ++matchIndex;
            }
            if (!isCommentOrWhiteSpace(currentTerm) && !isMatchForThisIndex) {
                break;
            }
        }
        if (matchIndex == static_cast<int>(searchPattern.size())) {
            return {patternIndexes};
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
        changeTerm(firstTerm, newTermType, combinedContent);
        terms.erase(terms.begin() + startIndex + 1, terms.begin() + endIndex + 1);
    }
}

void changeTerm(Term& term, TermType const newTermType, string const& content) {
    term.setTermType(newTermType);
    term.setContent(content);
}

string convertToString(TermType const type) {
#define GET_ENUM_STRING(en) \
    case en:                \
        return #en;
    switch (type) {
        GET_ENUM_STRING(TermType::Aggregate)
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

string convertToString(MatcherType const type) {
#define GET_ENUM_STRING(en) \
    case en:                \
        return #en;
    switch (type) {
        GET_ENUM_STRING(MatcherType::NotAWhiteSpace)
        GET_ENUM_STRING(MatcherType::IdentifierWithPascalCase)
    }
    return {};
}

bool isAMatch(MatcherType const matcherType, Term const& term) {
    switch (matcherType) {
        case MatcherType::NotAWhiteSpace:
            return !isWhiteSpace(term);
        case MatcherType::IdentifierWithPascalCase:
            return TermType::Identifier == term.getTermType() && isPascalCase(term.getContent());
    }
    return false;
}

bool isComment(Term const& term) {
    return term.getTermType() == TermType::CommentMultiline || term.getTermType() == TermType::CommentSingleLine;
}

bool isWhiteSpace(Term const& term) { return term.getTermType() == TermType::WhiteSpace; }

bool isCommentOrWhiteSpace(Term const& term) { return isComment(term) || isWhiteSpace(term); }

}  // namespace alba::CodeUtilities
