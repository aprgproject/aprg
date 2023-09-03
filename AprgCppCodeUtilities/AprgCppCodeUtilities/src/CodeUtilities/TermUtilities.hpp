#pragma once

#include <CodeUtilities/Term.hpp>

#include <string>

namespace alba::CodeUtilities {

bool isComment(Term const& term);
bool isWhiteSpace(Term const& term);
std::string convertToString(TermType const termType);

}  // namespace alba::CodeUtilities
