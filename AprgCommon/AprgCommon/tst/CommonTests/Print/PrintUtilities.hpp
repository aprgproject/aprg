#pragma once

#include <functional>
#include <sstream>

namespace alba {

void performASimplePrintingTest(
    std::stringstream &ssToVerify, std::function<void(std::stringstream &, int, int, int)> const &printAction);

}  // namespace alba
