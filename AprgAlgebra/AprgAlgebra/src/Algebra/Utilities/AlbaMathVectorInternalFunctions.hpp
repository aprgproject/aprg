#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>
#include <Common/Math/Vector/AlbaMathVectorUtilitiesHeaders.hpp>

namespace alba {

// Template specialization
template <>
bool isEqualForMathVectorDataType(algebra::Term const& value1, algebra::Term const& value2);

template <>
algebra::Term raiseToPowerForMathVectorDataType(algebra::Term const& value1, algebra::Term const& value2);

}  // namespace alba
