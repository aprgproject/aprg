#pragma once

#include <Algebra/Term/TermTypes/BaseTermData.hpp>
#include <Algebra/Term/TermTypes/Monomial.hpp>

#include <string>
#include <vector>

namespace alba::algebra {

class Polynomial : public BaseTermData {
public:
    explicit Polynomial(Monomials const& monomials);
    explicit Polynomial(Monomials&& monomials);
    Polynomial();
    Polynomial(std::initializer_list<Monomial> const& monomials);
    // rule of zero
    bool operator==(Polynomial const& second) const;
    bool operator!=(Polynomial const& second) const;
    bool operator<(Polynomial const& second) const;
    [[nodiscard]] Monomials const& getMonomials() const;
    [[nodiscard]] bool isEmpty() const;
    [[nodiscard]] bool isSimplified() const;
    void clear();
    void simplify();
    void sortMonomialsWithInversePriority();
    void addMonomial(Monomial const& monomial);
    void addPolynomial(Polynomial const& polynomial);
    void multiplyNumber(AlbaNumber const& number);
    void divideNumber(AlbaNumber const& number);
    void multiplyMonomial(Monomial const& monomial);
    void multiplyPolynomial(Polynomial const& polynomial);
    void divideMonomial(Monomial const& monomial);
    void raiseToUnsignedInteger(int const exponent);
    void setAsSimplified();
    void clearSimplifiedFlag();
    Monomials& getMonomialsReference();

private:
    void setNan();
    void simplifyContinuouslyIfChanged();
    void simplifyMonomialsAndReAdd();
    static bool isFurtherSimplificationNeeded(Polynomial const& beforeSimplify, Polynomial const& afterSimplify);
    friend std::ostream& operator<<(std::ostream& out, Polynomial const& polynomial);
    Monomials m_monomials;
    bool m_isSimplified{false};
};

using Polynomials = std::vector<Polynomial>;

}  // namespace alba::algebra
