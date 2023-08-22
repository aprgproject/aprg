#pragma once

#include <CPlusPlus/Term/Term.hpp>

#include <initializer_list>
#include <vector>

using std::initializer_list;
using std::vector;

namespace codeReview {

class MultipleTerms {
public:
    ializer_list<Term> const& initializerList);
    bool isEqualToAnyOfTheTerms(Term const& termToCompare) const;

private:
    vector<Term> m_terms;
};

}  // namespace codeReview
