#include <Common/Print/AlbaPrintMacros.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <CommonTestsUtilities/Print/PrintUtilities.hpp>

#include <gtest/gtest.h>

#include <map>
#include <memory>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

TEST(AlbaPrintMacrosTest, PrintingWorks) {
    stringstream ssToVerify;
    performASimplePrintingTest(
        ssToVerify, [](stringstream& ssToVerify, int singleParameter1, int singleParameter2, int singleParameter3) {
            ALBA_PRINT3(ssToVerify, singleParameter1, singleParameter2, singleParameter3);
        });
}

TEST(AlbaPrintMacrosTest, PrintingStringsWorks) {
    stringstream ssToVerify;
    string stringToTest = "std::string to test";

    ALBA_PRINT2(ssToVerify, stringToTest, "string literal to test");

    string actualPrintString(ssToVerify.str());
    int runningIndex = 0;
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "stringToTest", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "std::string to test", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "string literal to test", runningIndex));
}

TEST(AlbaPrintMacrosTest, PrintingPointersWorks) {
    stringstream ssToVerify;
    unique_ptr<int> uniquePointer(make_unique<int>(695));
    int const* nullPointer = nullptr;
    int const* rawPointer = uniquePointer.get();

    ALBA_PRINT3(ssToVerify, nullPointer, rawPointer, uniquePointer);

    string actualPrintString(ssToVerify.str());
    int runningIndex = 0;
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "nullPointer", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "nullptr", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "rawPointer", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "695", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "uniquePointer", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "695", runningIndex));
}

TEST(AlbaPrintMacrosTest, PrintingContainersWorks) {
    stringstream ssToVerify;
    vector<int> container1{454, 6, 512, 315};
    map<int, char> container2{{1, 'A'}, {5, 'E'}, {7, 'G'}};

    ALBA_PRINT2(ssToVerify, container1, container2);

    string actualPrintString(ssToVerify.str());
    int runningIndex = 0;
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "container1", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "454, 6, 512, 315,", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "container2", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "(1, A), (5, E), (7, G),", runningIndex));
}

#if defined(__clang__) || defined(__GNUC__) || defined(__GNUG__)

TEST(AlbaPrintMacrosTest, PrintingWithoutSpecifyNumberOfParametersWorks) {
    stringstream ssToVerify;
    performASimplePrintingTest(
        ssToVerify, [](stringstream& ssToVerify, int singleParameter1, int singleParameter2, int singleParameter3) {
            ALBA_PRINT_ALL(ssToVerify, singleParameter1, singleParameter2, singleParameter3);
        });
}

#endif

}  // namespace alba
