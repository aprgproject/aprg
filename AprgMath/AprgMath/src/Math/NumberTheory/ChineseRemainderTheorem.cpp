#include "ChineseRemainderTheorem.hpp"

#include <Math/NumberTheory/ModularArithmetic.hpp>

#include <algorithm>
#include <numeric>

using namespace std;

namespace alba::math {

ChineseRemainderTheorem::ChineseRemainderTheorem(UnsignedIntegers const& numbers, UnsignedIntegers const& modulos) {
    solve(numbers, modulos);
}

UnsignedInteger ChineseRemainderTheorem::getSolutionValue() const { return m_solutionValue; }

UnsignedInteger ChineseRemainderTheorem::getAnotherSolutionValue(UnsignedInteger const multiplier) const {
    return m_solutionValue + multiplier * m_productOfModulos;
}

void ChineseRemainderTheorem::solve(UnsignedIntegers const& numbers, UnsignedIntegers const& modulos) {
    if (numbers.size() == modulos.size()) {
        // fk = formulaForK = (m1*m2*m3...mn)/mk
        // x = a1*f1*(inverse of f1 with modulo m1) + a2*f2*(inverse of f2 with modulo m2) + ... an*fn*(inverse of fn
        // with modulo mn)
        m_productOfModulos =
            std::accumulate(modulos.cbegin(), modulos.cend(), static_cast<UnsignedInteger>(1), std::multiplies<>());
        for (int k = 0; k < static_cast<int>(numbers.size()); ++k) {
            UnsignedInteger const& number(numbers[k]);
            UnsignedInteger const& modulo(modulos[k]);
            UnsignedInteger const formulaForK = m_productOfModulos / modulo;
            UnsignedInteger const modularInverseOfFk = getModularInverseByEulersTheorem(formulaForK, modulo);
            m_solutionValue += number * formulaForK * modularInverseOfFk;
        }
    }
}

}  // namespace alba::math
