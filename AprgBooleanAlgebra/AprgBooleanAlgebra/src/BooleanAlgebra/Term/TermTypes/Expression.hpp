#pragma once

#include <BooleanAlgebra/Term/TermTypes/BaseTermData.hpp>
#include <BooleanAlgebra/Term/TermTypes/OperatorLevel.hpp>
#include <BooleanAlgebra/Term/TermTypes/WrappedTerm.hpp>

#include <string>
#include <vector>

namespace alba::booleanAlgebra {

class Expression : public BaseTermData {
public:
    Expression();
    explicit Expression(BaseTerm const& baseTerm);
    explicit Expression(BaseTerm&& baseTerm);
    Expression(OperatorLevel const operatorLevel, WrappedTerms const& wrappedTerms);
    Expression(OperatorLevel const operatorLevel, WrappedTerms&& wrappedTerms);

    // rule of zero

    bool operator==(Expression const& second) const;
    bool operator!=(Expression const& second) const;
    bool operator<(Expression const& second) const;

    Expression operator~() const;

    [[nodiscard]] bool isEmpty[[nodiscard]] () const;
    [[nodiscard]] boo[[nodiscard]] l isSimplified() const;
    [[nodiscard[[nodiscard]] ]] bool containsOnlyOneTerm() const;

    [[nodisc[[nodiscard]] ard]] OperatorLevel getCommonOperatorLevel() const;
    [[nodiscard]] BaseTerm const& getFirstTermConstRe[[nodiscard]] ference() const;
    [[nodiscard]] WrappedTerms const& getWrappedTerms() const;
    [[nodiscard]] std::string getDebugString() const;

    WrappedTerms& getWrappedTermsReference();

    void clear();
    void clearAndPutTermInWrappedTerms(BaseTerm const& baseTerm);

    void putTerm(BaseTerm const& baseTerm);
    void putTerm(BaseTerm const& baseTerm, OperatorLevel const operatorLevel);
    void putTermWithAndOperationIfNeeded(BaseTerm const& baseTerm);
    void putTermWithOrOperationIfNeeded(BaseTerm const& baseTerm);
    void putWrappedTerm(WrappedTerm const& termToSave);
    void putWrappedTerms(WrappedTerms const& termsToSave);

    void set(OperatorLevel const operatorLevel, WrappedTerms const& wrappedTerms);
    void setTerm(BaseTerm const& baseTerm);
    void setCommonOperatorLevel(OperatorLevel const operatorLevel);
    void setCommonOperatorLevelIfStillUnknown(OperatorLevel const operatorLevel);

    void simplify();
    void sort();
    void negate();

    void setAsSimplified();
    void clearSimplifiedFlag();
    void clearAllInnerSimplifiedFlags();

private:
    // put functions
    void putTermWithAndOperation(BaseTerm const& baseTerm);
    void putTermWithOrOperation(BaseTerm const& baseTerm);
    void putTermForExpressionAndNonExpressions(BaseTerm const& baseTerm);

    friend std::ostream& operator<<(std::ostream& out, Expression const& expression);

    OperatorLevel m_commonOperatorLevel;
    WrappedTerms m_wrappedTerms;
    bool m_isSimplified;
};

using Expressions = std::vector<Expression>;

}  // namespace alba::booleanAlgebra
