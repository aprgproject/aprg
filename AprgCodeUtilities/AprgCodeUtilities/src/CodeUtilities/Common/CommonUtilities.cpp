#include "CommonUtilities.hpp"

#include <Common/Macros/AlbaMacros.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <algorithm>

using namespace alba::stringHelper;
using namespace std;

namespace alba::CodeUtilities {

void replaceAllForwards(Terms& terms, Patterns const& searchPatterns, Terms const& replacementTerms) {
    for (int termIndex = 0; termIndex < static_cast<int>(terms.size());) {
        Indexes hitIndexes = searchPatternsAt(termIndex, terms, searchPatterns);
        if (!hitIndexes.empty()) {
            terms.erase(terms.cbegin() + hitIndexes.front(), terms.cbegin() + hitIndexes.back() + 1);
            terms.insert(terms.cbegin() + hitIndexes.front(), replacementTerms.cbegin(), replacementTerms.cend());
            int const sizeDifference =
                static_cast<int>(replacementTerms.size()) - (hitIndexes.back() + 1 - hitIndexes.front());
            if (sizeDifference == 0) {
                termIndex = hitIndexes.front() + 1;
            } else {
                termIndex = hitIndexes.front();
            }
        } else {
            ++termIndex;
        }
    }
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

void changeTerm(Term& term, TermType const newTermType, string const& content) {
    term.setTermType(newTermType);
    term.setContent(content);
}

Indexes searchForwardsForPatterns(Terms const& terms, Patterns const& searchPatterns) {
    return searchForwardsForPatterns(0, static_cast<int>(terms.size()) - 1, terms, searchPatterns);
}

Indexes searchForwardsForPatterns(int const startIndex, Terms const& terms, Patterns const& searchPatterns) {
    return searchForwardsForPatterns(startIndex, static_cast<int>(terms.size()) - 1, terms, searchPatterns);
}

Indexes searchForwardsForPatterns(
    int const startIndex, int const endIndex, Terms const& terms, Patterns const& searchPatterns) {
    for (int termIndex = startIndex; termIndex <= endIndex; ++termIndex) {
        Indexes hitIndexes = searchPatternsAt(termIndex, endIndex, terms, searchPatterns);
        if (!hitIndexes.empty()) {
            return hitIndexes;
        }
    }
    return {};
}

Indexes searchBackwardsForPatterns(int const startIndex, Terms const& terms, Patterns const& searchPatterns) {
    for (int termIndex = startIndex; termIndex >= 0; --termIndex) {
        Indexes hitIndexes = searchPatternsAt(termIndex, terms, searchPatterns);
        if (!hitIndexes.empty()) {
            return hitIndexes;
        }
    }
    return {};
}

Indexes searchPatternsAt(Terms const& terms, Patterns const& searchPatterns) {
    return searchPatternsAt(0, static_cast<int>(terms.size()) - 1, terms, searchPatterns);
}

Indexes searchPatternsAt(int const startIndex, Terms const& terms, Patterns const& searchPatterns) {
    return searchPatternsAt(startIndex, static_cast<int>(terms.size()) - 1, terms, searchPatterns);
}

Indexes searchPatternsAt(int const startIndex, int const endIndex, Terms const& terms, Patterns const& searchPatterns) {
    for (Pattern const& searchPattern : searchPatterns) {
        Indexes hitIndexes;
        int matchIndex = 0;
        for (int termIndex = startIndex; termIndex <= endIndex && matchIndex < static_cast<int>(searchPattern.size());
             ++termIndex) {
            Term const& currentTerm(terms[termIndex]);
            bool const isMatchForThisIndex = currentTerm == searchPattern[matchIndex];
            if (isMatchForThisIndex) {
                hitIndexes.emplace_back(termIndex);
                ++matchIndex;
            }
            if (!isCommentOrWhiteSpace(currentTerm) && !isMatchForThisIndex) {
                break;
            }
        }
        if (matchIndex == static_cast<int>(searchPattern.size())) {
            return {hitIndexes};
        }
    }
    return {};
}

Indexes searchBackwardsWithMatcher(int const termIndex, Terms const& terms, Matcher const& matcher) {
    Indexes hitIndexes;
    for (int termIndex2 = termIndex; termIndex2 >= 0; --termIndex2) {
        Term const& currentTerm(terms[termIndex2]);
        bool const isMatchForThisIndex = currentTerm == matcher;
        if (isMatchForThisIndex) {
            hitIndexes.emplace_back(termIndex2);
        }
        if (!isCommentOrWhiteSpace(currentTerm) || isMatchForThisIndex) {
            break;
        }
    }
    return hitIndexes;
}

Terms extractTermsInRange(int const startIndex, int const endIndex, Terms const& terms) {
    Terms extractedTerms;
    if (startIndex <= endIndex) {
        extractedTerms.reserve(endIndex + 1 - startIndex);
        copy(terms.begin() + startIndex, terms.cbegin() + endIndex + 1, back_inserter(extractedTerms));
    }
    return extractedTerms;
}

string getCombinedContents(Terms const& terms) {
    return getCombinedContents(0, static_cast<int>(terms.size()) - 1, terms);
}

string getCombinedContents(int const startIndex, int const endIndex, Terms const& terms) {
    string combinedContent;
    for (int termIndex = startIndex; termIndex <= endIndex; ++termIndex) {
        combinedContent += terms[termIndex].getContent();
    }
    return combinedContent;
}

string getLocatorString(int const index, Terms const& terms) {
    string combinedContent;
    constexpr int itemsOnOneSide = 8;
    int const sizeIndex = static_cast<int>(terms.size());
    int const startIndex = (index >= itemsOnOneSide) ? index - itemsOnOneSide : 0;
    int const endIndex = (index + itemsOnOneSide < sizeIndex) ? index + itemsOnOneSide : sizeIndex - 1;
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

string convertToString(TermType const type) {
    switch (type) {
        ALBA_MACROS_CASE_ENUM_STRING(TermType::Aggregate)
        ALBA_MACROS_CASE_ENUM_STRING(TermType::Attribute)
        ALBA_MACROS_CASE_ENUM_STRING(TermType::Boolean)
        ALBA_MACROS_CASE_ENUM_STRING(TermType::CharacterLiteral)
        ALBA_MACROS_CASE_ENUM_STRING(TermType::CommentMultiline)
        ALBA_MACROS_CASE_ENUM_STRING(TermType::CommentSingleLine)
        ALBA_MACROS_CASE_ENUM_STRING(TermType::Empty)
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

string convertToString(SpecialMatcherType const type) {
    switch (type) {
        ALBA_MACROS_CASE_ENUM_STRING(SpecialMatcherType::Comment)
        ALBA_MACROS_CASE_ENUM_STRING(SpecialMatcherType::HasNewLine)
        ALBA_MACROS_CASE_ENUM_STRING(SpecialMatcherType::IdentifierAndNotAScreamingSnakeCase)
        ALBA_MACROS_CASE_ENUM_STRING(SpecialMatcherType::IdentifierStartsWithLetterUnderscore)
        ALBA_MACROS_CASE_ENUM_STRING(SpecialMatcherType::IdentifierWithPascalCase)
        ALBA_MACROS_CASE_ENUM_STRING(SpecialMatcherType::IdentifierWithSnakeCase)
        ALBA_MACROS_CASE_ENUM_STRING(SpecialMatcherType::Literal)
        ALBA_MACROS_CASE_ENUM_STRING(SpecialMatcherType::NotACommentNorWhiteSpace)
        ALBA_MACROS_CASE_ENUM_STRING(SpecialMatcherType::WhiteSpaceWithNewLine)
    }
    return {};
}

int getPatternIndexOfAMatchBySearchingForward(int& termIndex, Terms const& terms, Patterns const& searchPatterns) {
    int patternIndex(-1);
    for (; termIndex < static_cast<int>(terms.size()); ++termIndex) {
        patternIndex = getPatternIndexOfAMatchAt(termIndex, terms, searchPatterns);
        if (patternIndex >= 0) {
            break;
        }
    }
    return patternIndex;
}

int getPatternIndexOfAMatchAt(int const termIndex, Terms const& terms, Patterns const& searchPatterns) {
    int patternIndex(0);
    for (Pattern const& searchPattern : searchPatterns) {
        int matchIndex = 0;
        for (int termIndex2 = termIndex;
             termIndex2 < static_cast<int>(terms.size()) && matchIndex < static_cast<int>(searchPattern.size());
             ++termIndex2) {
            Term const& currentTerm(terms[termIndex2]);
            bool const isMatchForThisIndex = currentTerm == searchPattern[matchIndex];
            if (isMatchForThisIndex) {
                ++matchIndex;
            }
            if (!isCommentOrWhiteSpace(currentTerm) && !isMatchForThisIndex) {
                break;
            }
        }
        if (matchIndex == static_cast<int>(searchPattern.size())) {
            break;
        }
        ++patternIndex;
    }
    // -1 represents no hit
    return patternIndex < static_cast<int>(searchPatterns.size()) ? patternIndex : -1;
}

int getIndexAtClosingString(
    Terms const& terms, int const openingIndex, string const& openingString, string const& closingString) {
    Patterns const searchPatterns{{M(openingString)}, {M(closingString)}};
    int endIndex = openingIndex + 1;
    int numberOfOpenings = 1;
    bool isFound(true);
    while (isFound) {
        Indexes hitIndexes = searchForwardsForPatterns(endIndex, terms, searchPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            int const firstHitIndex = hitIndexes.front();
            Term const& firstTerm(terms[firstHitIndex]);
            if (firstTerm.getContent() == openingString) {
                endIndex = firstHitIndex + 1;
                ++numberOfOpenings;
            } else if (firstTerm.getContent() == closingString) {
                endIndex = firstHitIndex + 1;
                if (--numberOfOpenings == 0) {
                    break;
                }
            } else {
                break;
            }
        }
    }
    return endIndex;
}

bool isAllWhiteSpaceOrComment(Terms const& terms) {
    return all_of(terms.cbegin(), terms.cend(), [](Term const& term) { return isCommentOrWhiteSpace(term); });
}

bool isAMatch(SpecialMatcherType const matcherType, Term const& term) {
    switch (matcherType) {
        case SpecialMatcherType::Comment:
            return isComment(term);
        case SpecialMatcherType::HasNewLine:
            return hasNewLine(term);
        case SpecialMatcherType::IdentifierAndNotAScreamingSnakeCase:
            return TermType::Identifier == term.getTermType() && !isScreamingSnakeCase(term.getContent());
        case SpecialMatcherType::IdentifierStartsWithLetterUnderscore:
            return TermType::Identifier == term.getTermType() && startsWithLetterUnderscore(term.getContent());
        case SpecialMatcherType::IdentifierWithPascalCase:
            return TermType::Identifier == term.getTermType() && isPascalCase(term.getContent());
        case SpecialMatcherType::IdentifierWithSnakeCase:
            return TermType::Identifier == term.getTermType() && isSnakeCase(term.getContent());
        case SpecialMatcherType::Literal:
            return TermType::Boolean == term.getTermType() || TermType::CharacterLiteral == term.getTermType() ||
                   TermType::Number == term.getTermType() || TermType::StringLiteral == term.getTermType();
        case SpecialMatcherType::NotACommentNorWhiteSpace:
            return !isCommentOrWhiteSpace(term);
        case SpecialMatcherType::WhiteSpaceWithNewLine:
            return isWhiteSpaceWithNewLine(term);
    }
    return false;
}

bool isComment(Term const& term) {
    return term.getTermType() == TermType::CommentMultiline || term.getTermType() == TermType::CommentSingleLine;
}

bool isWhiteSpace(Term const& term) { return term.getTermType() == TermType::WhiteSpace; }
bool isCommentOrWhiteSpace(Term const& term) { return isComment(term) || isWhiteSpace(term); }

bool isWhiteSpaceWithNewLine(Term const& term) {
    return term.getTermType() == TermType::WhiteSpace && stringHelper::hasNewLine(term.getContent());
}

bool hasNewLine(Term const& term) { return stringHelper::hasNewLine(term.getContent()); }

bool startsWithLetterUnderscore(string const& content) {
    if (content.length() >= 2) {
        return isLowerCaseLetter(content[0]) && '_' == content[1];
    }
    return false;
}

}  // namespace alba::CodeUtilities
