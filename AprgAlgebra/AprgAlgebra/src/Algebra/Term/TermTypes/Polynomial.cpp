#include "Polynomial.hpp"

#include <Algebra/Term/Utilities/MonomialHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Common/Math/Number/AlbaNumberConstants.hpp>

#include <algorithm>

using namespace alba::AlbaNumberConstants;
using namespace std;

namespace alba::algebra {

Polynomial::Polynomial(Monomials const& monomials) : m_monomials(monomials) {}
Polynomial::Polynomial(Monomials&& monomials) : m_monomials(monomials) {}

Polynomial::Polynomial(initializer_list<Monomial> const& monomials) {
    m_monomials.reserve(monomials.size());
    copy(monomials.begin(), monomials.end(), back_inserter(m_monomials));
}

bool Polynomial::operator==(Polynomial const& second) const {
    Monomials const& monomials1(m_monomials);
    Monomials const& monomials2(second.m_monomials);
    bool result(false);
    if (monomials1.size() == monomials2.size()) {
        using MonomialsIterator = Monomials::const_iterator;
        using MismatchResultType = pair<MonomialsIterator, MonomialsIterator>;
        MismatchResultType const mismatchResult = mismatch(monomials1.cbegin(), monomials1.end(), monomials2.cbegin());
        result = mismatchResult.first == monomials1.cend();
    }
    return result;
}

bool Polynomial::operator!=(Polynomial const& second) const { return !(operator==(second)); }

bool Polynomial::operator<(Polynomial const& second) const {
    Monomials const& monomials1(m_monomials);
    Monomials const& monomials2(second.m_monomials);
    bool result(false);
    if (monomials1.size() == monomials2.size()) {
        int const size = static_cast<int>(monomials1.size());
        for (int i = 0; i < size; ++i) {
            Monomial const& monomial1(monomials1[i]);
            Monomial const& monomial2(monomials2[i]);
            if (monomial1 != monomial2) {
                result = monomial1 < monomial2;
                break;
            }
        }
    } else {
        result = monomials1.size() < monomials2.size();
    }
    return result;
}

Monomials const& Polynomial::getMonomials() const { return m_monomials; }
bool Polynomial::isEmpty() const { return m_monomials.empty(); }
bool Polynomial::isSimplified() const { return m_isSimplified; }

void Polynomial::clear() {
    m_monomials.clear();
    clearSimplifiedFlag();
}

void Polynomial::simplify() {
    if (!m_isSimplified) {
        if (hasNan(*this)) {
            setNan();
        } else {
            simplifyContinuouslyIfChanged();
        }
        setAsSimplified();
    }
}

void Polynomial::sortMonomialsWithInversePriority() {
    stable_sort(m_monomials.begin(), m_monomials.end(), [](Monomial const& monomial1, Monomial const& monomial2) {
        return monomial2 < monomial1;
    });
    clearSimplifiedFlag();
}

void Polynomial::addMonomial(Monomial const& monomial) {
    bool isFoundInPolynomial(false);
    for (Monomial& monomialInternal : m_monomials) {
        if (canBeMergedInAMonomialByAdditionOrSubtraction(monomialInternal, monomial)) {
            isFoundInPolynomial = true;
            monomialInternal.setConstant(monomialInternal.getCoefficient() + monomial.getCoefficient());
        }
    }
    if (!isFoundInPolynomial) {
        m_monomials.emplace_back(monomial);
    }
    clearSimplifiedFlag();
}

void Polynomial::addPolynomial(Polynomial const& polynomial) {
    for (Monomial const& monomial : polynomial.getMonomials()) {
        addMonomial(monomial);
    }
    clearSimplifiedFlag();
}

void Polynomial::multiplyNumber(AlbaNumber const& number) {
    for (Monomial& monomial : m_monomials) {
        monomial.setConstant(monomial.getCoefficient() * number);
    }
    clearSimplifiedFlag();
}

void Polynomial::divideNumber(AlbaNumber const& number) {
    for (Monomial& monomial : m_monomials) {
        monomial.setConstant(monomial.getCoefficient() / number);
    }
    clearSimplifiedFlag();
}

void Polynomial::multiplyMonomial(Monomial const& monomial) {
    for (Monomial& monomialInternal : m_monomials) {
        monomialInternal.multiplyMonomial(monomial);
    }
    clearSimplifiedFlag();
}

void Polynomial::multiplyPolynomial(Polynomial const& polynomial) {
    Monomials const monomialsCopy(m_monomials);
    m_monomials.clear();
    for (Monomial const& monomial2 : polynomial.getMonomials()) {
        for (Monomial const& monomial1 : monomialsCopy) {
            Monomial newMonomial(monomial1);
            newMonomial.multiplyMonomial(monomial2);
            addMonomial(newMonomial);
        }
    }
    clearSimplifiedFlag();
}

void Polynomial::divideMonomial(Monomial const& monomial) {
    for (Monomial& monomialInternal : m_monomials) {
        monomialInternal.divideMonomial(monomial);
    }
    clearSimplifiedFlag();
}

void Polynomial::raiseToUnsignedInteger(int const exponent) {
    Polynomial const base(*this);
    for (int exponentCount = 1; exponentCount < exponent; ++exponentCount) {
        multiplyPolynomial(base);
    }
    clearSimplifiedFlag();
}

void Polynomial::setAsSimplified() { m_isSimplified = true; }
void Polynomial::clearSimplifiedFlag() { m_isSimplified = false; }

Monomials& Polynomial::getMonomialsReference() {
    clearSimplifiedFlag();
    return m_monomials;
}

void Polynomial::setNan() {
    m_monomials.clear();
    addMonomial(Monomial(ALBA_NUMBER_NOT_A_NUMBER, {}));
}

void Polynomial::simplifyContinuouslyIfChanged() {
    Polynomial beforeSimplify;
    Polynomial afterSimplify;
    do {
        beforeSimplify = *this;
        simplifyMonomialsAndReAdd();
        sortMonomialsWithInversePriority();
        afterSimplify = *this;
    } while (isFurtherSimplificationNeeded(beforeSimplify, afterSimplify));
}

void Polynomial::simplifyMonomialsAndReAdd() {
    Monomials previousMonomials(m_monomials);
    m_monomials.clear();
    for (Monomial& monomial : previousMonomials) {
        monomial.simplify();
        if (!isTheValue(monomial, 0)) {
            addMonomial(monomial);
        }
    }
}

bool Polynomial::isFurtherSimplificationNeeded(Polynomial const& beforeSimplify, Polynomial const& afterSimplify) {
    return beforeSimplify != afterSimplify && !hasNan(afterSimplify);
}

ostream& operator<<(ostream& out, Polynomial const& polynomial) {
    Monomials const& monomials(polynomial.m_monomials);
    if (monomials.empty()) {
        out << "(EmptyPolynomial)";
    } else {
        out << "(" << monomials.front();
        for (auto it = monomials.cbegin() + 1; it != monomials.cend(); ++it) {
            out << " + " << *it;
        }
        out << ")";
    }
    return out;
}

}  // namespace alba::algebra
