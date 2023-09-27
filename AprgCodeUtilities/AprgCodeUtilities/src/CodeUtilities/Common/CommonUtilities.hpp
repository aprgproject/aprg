#pragma once

#include <CodeUtilities/Common/CommonTypes.hpp>
#include <CodeUtilities/Common/Matcher/SpecialMatcherType.hpp>

namespace alba::CodeUtilities {

void replaceAllForwards(Terms& terms, Patterns const& searchPatterns, Terms const& replacementTerms);
void combineTermsInPlace(Terms& terms, TermType const newTermType, int const startIndex, int const endIndex);
void changeTerm(Term& term, TermType const newTermType, std::string const& content);
Indexes searchForwardsForPatterns(Terms const& terms, Patterns const& searchPatterns);
Indexes searchForwardsForPatterns(int const startIndex, Terms const& terms, Patterns const& searchPatterns);

Indexes searchForwardsForPatterns(
    int const startIndex, int const endIndex, Terms const& terms, Patterns const& searchPatterns);

Indexes searchBackwardsForPatterns(int const startIndex, Terms const& terms, Patterns const& searchPatterns);
Indexes searchPatternsAt(Terms const& terms, Patterns const& searchPatterns);
Indexes searchPatternsAt(int const startIndex, Terms const& terms, Patterns const& searchPatterns);
Indexes searchPatternsAt(int const startIndex, int const endIndex, Terms const& terms, Patterns const& searchPatterns);
Indexes searchBackwardsWithMatcher(int const termIndex, Terms const& terms, Matcher const& matcher);
Terms extractTermsInRange(int const startIndex, int const endIndex, Terms const& terms);
std::string getCombinedContents(Terms const& terms);
std::string getCombinedContents(int const startIndex, int const endIndex, Terms const& terms);
std::string getLocatorString(int const index, Terms const& terms);
std::string convertToString(TermType const termType);
std::string convertToString(SpecialMatcherType const type);
int getPatternIndexOfAMatchBySearchingForward(int& termIndex, Terms const& terms, Patterns const& searchPatterns);
int getPatternIndexOfAMatchAt(int const termIndex, Terms const& terms, Patterns const& searchPatterns);

int getIndexAtClosingString(
    Terms const& terms, int const openingIndex, std::string const& openingString, std::string const& closingString);

bool isAllWhiteSpaceOrComment(Terms const& terms);
bool isAMatch(SpecialMatcherType const matcherType, Term const& term);
bool isComment(Term const& term);
bool isWhiteSpace(Term const& term);
bool isCommentOrWhiteSpace(Term const& term);
bool isWhiteSpaceWithNewLine(Term const& term);
bool hasNewLine(Term const& term);
bool startsWithLetterUnderscore(std::string const& content);

}  // namespace alba::CodeUtilities
