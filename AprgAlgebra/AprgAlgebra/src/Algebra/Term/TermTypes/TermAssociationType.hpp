#pragma once

#include <vector>

namespace alba::algebra {

enum class TermAssociationType { Positive, Negative };

using TermAssociationTypes = std::vector<TermAssociationType>;

}  // namespace alba
