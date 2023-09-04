#include "TermUtilities.hpp"

#include <Common/Macros/AlbaMacros.hpp>
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
    switch (type) {
        ALBA_MACROS_CASE_ENUM_STRING(TermType::Aggregate)
        ALBA_MACROS_CASE_ENUM_STRING(TermType::Boolean)
        ALBA_MACROS_CASE_ENUM_STRING(TermType::CharacterLiteral)
        ALBA_MACROS_CASE_ENUM_STRING(TermType::CommentMultiline)
        ALBA_MACROS_CASE_ENUM_STRING(TermType::CommentSingleLine)
        ALBA_MACROS_CASE_ENUM_STRING(TermType::Identifier)
        ALBA_MACROS_CASE_ENUM_STRING(TermType::Keyword)
        ALBA_MACROS_CASE_ENUM_STRING(TermType::Macro)
        ALBA_MACROS_CASE_ENUM_STRING(TermType::Number)
        ALBA_MACROS_CASE_ENUM_STRING(TermType::Operator)
        ALBA_MACROS_CASE_ENUM_STRING(TermType::PrimitiveType)
        ALBA_MACROS_CASE_ENUM_STRING(TermType::StringLiteral)
        ALBA_MACROS_CASE_ENUM_STRING(TermType::Unknown)
        ALBA_MACROS_CASE_ENUM_STRING(TermType::WhiteSpace)
    }
    return {};
}

string convertToString(MatcherType const type) {
    switch (type) {
        ALBA_MACROS_CASE_ENUM_STRING(MatcherType::NotAWhiteSpace)
        ALBA_MACROS_CASE_ENUM_STRING(MatcherType::IdentifierWithPascalCase)
        ALBA_MACROS_CASE_ENUM_STRING(MatcherType::IdentifierWithSnakeCase)
        ALBA_MACROS_CASE_ENUM_STRING(MatcherType::IdentifierAndNotAScreamingSnakeCase)
        ALBA_MACROS_CASE_ENUM_STRING(MatcherType::Comment)
    }
    return {};
}

bool isAMatch(MatcherType const matcherType, Term const& term) {
    switch (matcherType) {
        case MatcherType::NotAWhiteSpace:
            return !isWhiteSpace(term);
        case MatcherType::IdentifierWithPascalCase:
            return TermType::Identifier == term.getTermType() && isPascalCase(term.getContent());
        case MatcherType::IdentifierWithSnakeCase:
            return TermType::Identifier == term.getTermType() && isSnakeCase(term.getContent());
        case MatcherType::IdentifierAndNotAScreamingSnakeCase:
            return TermType::Identifier == term.getTermType() && !isScreamingSnakeCase(term.getContent());
        case MatcherType::Comment:
            return isComment(term);
    }
    return false;
}

bool isComment(Term const& term) {
    return term.getTermType() == TermType::CommentMultiline || term.getTermType() == TermType::CommentSingleLine;
}

bool isWhiteSpace(Term const& term) { return term.getTermType() == TermType::WhiteSpace; }

bool isCommentOrWhiteSpace(Term const& term) { return isComment(term) || isWhiteSpace(term); }

bool hasNewLine(Term const& term) { return stringHelper::hasNewLine(term.getContent()); }

}  // namespace alba::CodeUtilities
