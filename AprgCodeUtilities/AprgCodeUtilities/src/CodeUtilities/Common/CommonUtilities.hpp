#pragma once

#include <CodeUtilities/Common/CommonTypes.hpp>
#include <CodeUtilities/Common/Matcher/SpecialMatcherType.hpp>

namespace alba::CodeUtilities {

void replaceAllForwards(
    Terms& terms, int const startIndex, Patterns const& searchPatterns, Terms const& replacementTerms);

void combineTermsInPlace(Terms& terms, TermType const newTermType, int const startIndex, int const endIndex);
void changeTerm(Term& term, TermType const newTermType, std::string const& content);
Indexes searchForwardsForPatterns(Terms const& terms, int const startIndex, Patterns const& searchPatterns);
Indexes searchBackwardsForPatterns(Terms const& terms, int const startIndex, Patterns const& searchPatterns);
Indexes searchPatternsAt(Terms const& terms, int const termIndex, Patterns const& searchPatterns);
Indexes searchBackwardsWithMatcher(Terms const& terms, int const termIndex, Matcher const& matcher);
std::string getCombinedContents(Terms const& terms);
std::string getCombinedContents(Terms const& terms, int const startIndex, int const endIndex);
std::string getLocatorString(Terms const& terms, int const index);
std::string convertToString(TermType const termType);
std::string convertToString(SpecialMatcherType const type);
int getPatternIndexOfAMatchBySearchingForward(int& termIndex, Terms const& terms, Patterns const& searchPatterns);
int getPatternIndexOfAMatchAt(Terms const& terms, int const termIndex, Patterns const& searchPatterns);
bool isAllWhiteSpaceOrComment(Terms const& terms);
bool isAMatch(SpecialMatcherType const matcherType, Term const& term);
bool isComment(Term const& term);
bool isWhiteSpace(Term const& term);
bool isCommentOrWhiteSpace(Term const& term);
bool isWhiteSpaceWithNewLine(Term const& term);
bool hasNewLine(Term const& term);

}  // namespace alba::CodeUtilities
