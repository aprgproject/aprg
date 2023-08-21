#include "PrintUtilities.hpp"

#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

void performASimplePrintingTest(
    stringstream &ssToVerify, function<void(stringstream &, int, int, int)> const &printAction) {
    int singleParameter1 = 12, singleParameter2 = 345, singleParameter3 = 6789;

    printAction(ssToVerify, singleParameter1, singleParameter2, singleParameter3);

    string actualPrintString(ssToVerify.str());
    int runningIndex = 0;
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "singleParameter1", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "12", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "singleParameter2", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "345", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "singleParameter3", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "6789", runningIndex));
}

}  // namespace alba
