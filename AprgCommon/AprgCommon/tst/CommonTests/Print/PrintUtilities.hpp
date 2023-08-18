#pragma once

#include <functional>
#include <sstream>

namespace alba {

void performASimplePrintingTest(
    std::stringstream &out, std::function<void(std::stringstream &, int, int, int)> printAction);

}
