#pragma once

#include <CodeUtilities/Common/CommonTypes.hpp>

namespace alba::CodeUtilities {

Indexes searchForPatternsForwards(Terms const& terms, int const startIndex, Patterns const& searchPatterns);
Indexes searchForPatternsBackwards(Terms const& terms, int const startIndex, Patterns const& searchPatterns);
Indexes checkPatternAt(Terms const& terms, int const termIndex, Patterns const& searchPatterns);
Indexes checkMatcherAtBackwards(Terms const& terms, int const termIndex, TermMatcher const& matcher);
void replaceAllForwards(
    Terms& terms, int const startIndex, Patterns const& searchPatterns, Terms const& replacementTerms);
void replaceCommentsWithExtraLine(Terms& terms, int const startIndex);

void combineTermsInPlace(Terms& terms, TermType const newTermType, int const startIndex, int const endIndex);
void changeTerm(Term& term, TermType const newTermType, std::string const& content);

std::string getCombinedContents(Terms const& terms);
std::string getCombinedContents(Terms const& terms, int const startIndex, int const endIndex);
std::string getLocatorString(Terms const& terms, int const index);
std::string convertToString(TermType const termType);
std::string convertToString(MatcherType const type);

bool isAllWhiteSpaceOrComment(Terms const& terms);
bool isAMatch(MatcherType const matcherType, Term const& term);
bool isComment(Term const& term);
bool isWhiteSpace(Term const& term);
bool isCommentOrWhiteSpace(Term const& term);
bool isWhiteSpaceWithNewLine(Term const& term);
bool hasNewLine(Term const& term);

}  // namespace alba::CodeUtilities
