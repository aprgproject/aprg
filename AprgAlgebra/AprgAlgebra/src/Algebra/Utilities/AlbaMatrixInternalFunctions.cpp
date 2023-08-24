#include "AlbaMatrixInternalFunctions.hpp"

namespace alba::matrix {

template <>
bool isEqualForMathMatrixDataType(AlbaNumber const& value1, AlbaNumber const& value2) {
    return value1 == value2;
}

}  // namespace alba
