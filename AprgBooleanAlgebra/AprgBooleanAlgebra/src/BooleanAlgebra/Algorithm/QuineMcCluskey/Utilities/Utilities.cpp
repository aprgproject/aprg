#include "Utilities.hpp"

namespace alba::booleanAlgebra {

LogicalValue getLogicalValue(bool const value) { return value ? LogicalValue::True : LogicalValue::False; }

}  // namespace alba
