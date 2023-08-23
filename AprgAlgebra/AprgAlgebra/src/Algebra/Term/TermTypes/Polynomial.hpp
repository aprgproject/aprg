#pragma once

#include <Algebra/Term/TermTypes/BaseTermData.hpp>
#include <Algebra/Term/TermTypes/Monomial.hpp>

#include <string>
#include <vector>

namespace alba::algebra {

class Polynomial : public BaseTermData {
public:
    Polynomial();
    explicit Polynomial(Monomials const& monomials);
    Polynomial(std::initializer_list<Monomial> const& monomials);

    // rule of zero

    bool operator==(Polynomial const& second) const;
    bool operator!=(Polynomial const& second) const;
    bool operator<(Polynomial const& second) const;
    [[nodiscard]] bool isEmpty() const;
    [[nodiscard]] bool isSimplified() const;
    [[nodiscard]] Monomials const& getMonomials() const;

    Monomials& getMonomialsReference();
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

private:
    static bool isFurtherSimplificationNeeded(Polynomial const& beforeSimplify, Polynomial const& afterSimplify);
    void setNan();
    void simplifyContinuouslyIfChanged();
    void simplifyMonomialsAndReAdd();

    friend std::ostream& operator<<(std::ostream& out, Polynomial const& polynomial);

    Monomials m_monomials;
    bool m_isSimplified;
};

using Polynomials = std::vector<Polynomial>;

}  // namespace alba::algebra
