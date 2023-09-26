#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba::algebra {

using TermToTermMap = std::map<Term, Term>;
using TermTermPair = std::pair<Term, Term>;

class SubstitutionOfTermsToTerms {
public:
    SubstitutionOfTermsToTerms();
    explicit SubstitutionOfTermsToTerms(TermToTermMap const& variablesWithValues);
    SubstitutionOfTermsToTerms(std::initializer_list<TermTermPair> const& variablesWithValues);
    [[nodiscard]] Equation performSubstitutionTo(Equation const& equation) const;
    [[nodiscard]] Expression performSubstitutionForExpression(Expression const& expression) const;
    [[nodiscard]] Function performSubstitutionForFunction(Function const& functionObject) const;
    [[nodiscard]] Term getTermForTerm(Term const& term) const;
    [[nodiscard]] Term performSubstitutionTo(Expression const& expression) const;
    [[nodiscard]] Term performSubstitutionTo(Function const& functionObject) const;
    [[nodiscard]] Term performSubstitutionTo(Term const& term) const;
    [[nodiscard]] int getSize() const;
    [[nodiscard]] bool isEmpty() const;
    [[nodiscard]] bool isTermFound(Term const& term) const;
    void putTermsToTermsMapping(std::initializer_list<TermTermPair> const& variablesWithValues);
    void putTermsToTermsMapping(TermToTermMap const& variablesWithValues);
    void putTermToTermMapping(Term const& term1, Term const& term2);

private:
    void performSubstitutionForTermsWithAssociation(TermsWithAssociation& termsWithAssociation) const;
    TermToTermMap m_termsToTermsMap;
};

}  // namespace alba::algebra
