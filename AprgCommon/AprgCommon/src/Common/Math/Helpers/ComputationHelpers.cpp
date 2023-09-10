#include "ComputationHelpers.hpp"

#include <Common/Math/Helpers/ComplexNumberHelpers.hpp>

using namespace std;

namespace alba::mathHelper {

AlbaNumbers getQuadraticRoots(
    RootType const rootType, AlbaNumber const& aValue, AlbaNumber const& bValue, AlbaNumber const& cValue) {
    AlbaNumbers result;
    AlbaNumber const twoA = aValue * 2;
    AlbaNumber const firstPart((-bValue) / twoA);
    AlbaNumber const discriminant((bValue ^ 2) - (aValue * cValue * 4));
    if (discriminant >= 0) {
        AlbaNumber const discriminantSquaredRoot = discriminant ^ (AlbaNumber::createFraction(1, 2));
        AlbaNumber const secondPart(discriminantSquaredRoot / twoA);
        result.emplace_back(firstPart + secondPart);
        result.emplace_back(firstPart - secondPart);
    } else if (RootType::RealAndImaginaryRoots == rootType) {
        AlbaComplexNumber<double> const discriminantComplex(discriminant.getDouble(), 0.0);
        result.emplace_back(firstPart + createNumberFromComplexNumber(discriminantComplex.getNthRoot(0, 2)) / twoA);
        result.emplace_back(firstPart + createNumberFromComplexNumber(discriminantComplex.getNthRoot(1, 2)) / twoA);
    }
    return result;
}

}  // namespace alba::mathHelper
