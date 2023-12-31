#include <ProcessFiles/ReplaceStringInFiles/ReplaceStringInFiles.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(AlbaReplaceStringInFileTest, ReplaceCStylePrintWithCPlusPlusStylePrint) {
    string const result(alba::ReplaceStringInFiles::getCPlusPlusStylePrintFromC(
        R"(TLH_DEBUG_PRINT("Creating new licence entry in DB for featureCode: %d.", featureCode);)"));
    EXPECT_EQ(
        R"(debug() << "Creating new licence entry in DB for featureCode: " << featureCode << "." << flush();)", result);
}

TEST(AlbaReplaceStringInFileTest, ReplaceCStylePrintWithCPlusPlusStylePrintWithPercentWithNumber) {
    string const result(alba::ReplaceStringInFiles::getCPlusPlusStylePrintFromC(
        R"(TLH_DEBUG_PRINT("Received LMS_FEATURE_NOTIFICATION_RESP_MSG (0x%04x), featureCode: %u, successCode: %s", LMS_FEATURE_NOTIFICATION_RESP_MSG, featureCode, (successCode == EBoolean_True ? "Success" : "Fail"));)"));
    EXPECT_EQ(
        R"(debug() << "Received LMS_FEATURE_NOTIFICATION_RESP_MSG (0x" << LMS_FEATURE_NOTIFICATION_RESP_MSG << "), featureCode: " << featureCode << ", successCode: " << (successCode == EBoolean_True ? "Success" : "Fail") << flush();)",
        result);
}

TEST(AlbaReplaceStringInFileTest, ReplaceCStylePrintWithCPlusPlusStylePrintWithNoParameters) {
    string const result(
        alba::ReplaceStringInFiles::getCPlusPlusStylePrintFromC(R"(TLH_DEBUG_PRINT("TLH::reset() ");)"));
    EXPECT_EQ("debug() << \"TLH::reset()\" << flush();", result);
}

TEST(AlbaReplaceStringInFileTest, DISABLED_ReplaceCStylePrintWithCPlusPlusStyleInDirectories) {
    alba::ReplaceStringInFiles::replaceCToCPlusPlusStylePrintOnDirectories(
        R"(D:\Branches\MODERNIZATION\TLH\C_Application\SC_TCOM\CP_TLH\)",
        R"(D:\Branches\MODERNIZATION\TLH\C_Application\SC_TCOM\NewTLH\)");
}

TEST(AlbaReplaceStringInFileTest, DISABLED_ReplaceCStylePrintWithCPlusPlusStyleInFile) {
    alba::ReplaceStringInFiles::replaceCToCPlusPlusStylePrintOnFile(
        R"(D:\Branches\MODERNIZATION\TLH\C_Application\SC_TCOM\CP_TLH\srcLegacy\TLHMasterState.cpp)",
        R"(D:\Branches\MODERNIZATION\TLH\C_Application\SC_TCOM\NewTLH\srcLegacy\TLHMasterState.cpp)");
}

}  // namespace alba
