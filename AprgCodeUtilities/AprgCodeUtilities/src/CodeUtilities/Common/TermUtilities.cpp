#include "TermUtilities.hpp"

#include <Common/Macros/AlbaMacros.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <algorithm>

using namespace alba::stringHelper;
using namespace std;

namespace alba::CodeUtilities {

Indexes searchForPatternsForwards(Terms const& terms, int const startIndex, Patterns const& searchPatterns) {
    for (int termIndex = startIndex; termIndex < static_cast<int>(terms.size()); ++termIndex) {
        Indexes patternIndexes = checkPatternAt(terms, termIndex, searchPatterns);
        if (!patternIndexes.empty()) {
            return patternIndexes;
        }
    }
    return {};
}

Indexes searchForPatternsBackwards(Terms const& terms, int const startIndex, Patterns const& searchPatterns) {
    for (int termIndex = startIndex; termIndex >= 0; --termIndex) {
        Indexes patternIndexes = checkPatternAt(terms, termIndex, searchPatterns);
        if (!patternIndexes.empty()) {
            return patternIndexes;
        }
    }
    return {};
}

Indexes checkPatternAt(Terms const& terms, int const termIndex, Patterns const& searchPatterns) {
    Indexes patternIndexes;
    for (Pattern const& searchPattern : searchPatterns) {
        int matchIndex = 0;
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
        for (int termIndex = startIndex; termIndex <= endIndex; ++termIndex) {
            combinedContent += terms[termIndex].getContent();
        }
        Term& firstTerm(terms[startIndex]);
        changeTerm(firstTerm, newTermType, combinedContent);
        terms.erase(terms.begin() + startIndex + 1, terms.begin() + endIndex + 1);
    }
}

string getCombinedContents(Terms const& terms) {
    return getCombinedContents(terms, 0, static_cast<int>(terms.size()) - 1);
}

string getCombinedContents(Terms const& terms, int const startIndex, int const endIndex) {
    string combinedContent;
    for (int termIndex = startIndex; termIndex <= endIndex; ++termIndex) {
        combinedContent += terms[termIndex].getContent();
    }
    return combinedContent;
}

string getLocatorString(Terms const& terms, int const index) {
    string combinedContent;
    constexpr int itemsOnOneSide = 6;
    int sizeIndex = static_cast<int>(terms.size());
    int startIndex = (index >= itemsOnOneSide) ? index - itemsOnOneSide : 0;
    int endIndex = (index + itemsOnOneSide < sizeIndex) ? index + itemsOnOneSide : sizeIndex - 1;
    for (int termIndex = startIndex; termIndex < index; ++termIndex) {
        combinedContent += terms[termIndex].getContent();
    }
    combinedContent += "@";
    combinedContent += terms[index].getContent();
    combinedContent += "@";
    for (int termIndex = index + 1; termIndex <= endIndex; ++termIndex) {
        combinedContent += terms[termIndex].getContent();
    }
    return combinedContent;
}

void changeTerm(Term& term, TermType const newTermType, string const& content) {
    term.setTermType(newTermType);
    term.setContent(content);
}

string convertToString(TermType const type) {
    switch (type) {
        ALBA_MACROS_CASE_ENUM_STRING(TermType::Aggregate)
        ALBA_MACROS_CASE_ENUM_STRING(TermType::Attribute)
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
        ALBA_MACROS_CASE_ENUM_STRING(MatcherType::Comment)
        ALBA_MACROS_CASE_ENUM_STRING(MatcherType::HasNewLine)
        ALBA_MACROS_CASE_ENUM_STRING(MatcherType::IdentifierWithPascalCase)
        ALBA_MACROS_CASE_ENUM_STRING(MatcherType::IdentifierWithSnakeCase)
        ALBA_MACROS_CASE_ENUM_STRING(MatcherType::IdentifierAndNotAScreamingSnakeCase)
        ALBA_MACROS_CASE_ENUM_STRING(MatcherType::NotAWhiteSpace)
    }
    return {};
}

bool isAMatch(MatcherType const matcherType, Term const& term) {
    switch (matcherType) {
        case MatcherType::Comment:
            return isComment(term);
        case MatcherType::HasNewLine:
            return hasNewLine(term);
        case MatcherType::IdentifierWithPascalCase:
            return TermType::Identifier == term.getTermType() && isPascalCase(term.getContent());
        case MatcherType::IdentifierWithSnakeCase:
            return TermType::Identifier == term.getTermType() && isSnakeCase(term.getContent());
        case MatcherType::IdentifierAndNotAScreamingSnakeCase:
            return TermType::Identifier == term.getTermType() && !isScreamingSnakeCase(term.getContent());
        case MatcherType::NotAWhiteSpace:
            return !isWhiteSpace(term);
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
