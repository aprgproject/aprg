#pragma once

#include <CPlusPlus/Term/Term.hpp>

#include <deque>
#include <ostream>
#include <set>
#include <string>
#include <vector>

using std::deque;
using std::set;
using std::string;
using std::vector;

namespace codeReview {

using VectorOfStrings = vector<string>;
using SetOfStrings = set<string>;

using DequeOfTerms = deque<Term>;
using TermsIterator = deque<Term>::iterator;
using TermsReverseIterator = deque<Term>::reverse_iterator;
using VectorOfTerms = vector<Term>;
using ExpectedTermsIterator = vector<Term>::iterator;

void printTerms(DequeOfTerms const& terms);
void printTerms(VectorOfTerms const& terms);
void printContentOfTerms(DequeOfTerms const& terms, std::ostream& fileStream);

}  // namespace codeReview
