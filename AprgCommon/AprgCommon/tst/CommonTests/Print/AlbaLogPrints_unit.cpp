#include <Common/Print/AlbaLogPrints.hpp>
#include <CommonTests/Print/PrintUtilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(AlbaLogPrintsTest, InfLogPrintingWorks) {
    stringstream ssToVerify;
    performASimplePrintingTest(
        ssToVerify, [](stringstream &ssToVerify, int singleParameter1, int singleParameter2, int singleParameter3) {
            ALBA_INF_PRINT3(ssToVerify, singleParameter1, singleParameter2, singleParameter3);
        });
}

TEST(AlbaLogPrintsTest, WrnLogPrintingWorks) {
    stringstream ssToVerify;
    performASimplePrintingTest(
        ssToVerify, [](stringstream &ssToVerify, int singleParameter1, int singleParameter2, int singleParameter3) {
            ALBA_WRN_PRINT3(ssToVerify, singleParameter1, singleParameter2, singleParameter3);
        });
}

TEST(AlbaLogPrintsTest, ErrLogPrintingWorks) {
    stringstream ssToVerify;
    performASimplePrintingTest(
        ssToVerify, [](stringstream &ssToVerify, int singleParameter1, int singleParameter2, int singleParameter3) {
            ALBA_ERR_PRINT3(ssToVerify, singleParameter1, singleParameter2, singleParameter3);
        });
}

#if defined(__clang__) || defined(__GNUC__) || defined(__GNUG__)

TEST(AlbaLogPrintsTest, InfLogPrintingWithoutSpecifyNumberOfParametersWorks) {
    stringstream ssToVerify;
    performASimplePrintingTest(
        ssToVerify, [](stringstream &ssToVerify, int singleParameter1, int singleParameter2, int singleParameter3) {
            ALBA_INF_PRINT(ssToVerify, singleParameter1, singleParameter2, singleParameter3);
        });
}

TEST(AlbaLogPrintsTest, WrnLogPrintingWithoutSpecifyNumberOfParametersWorks) {
    stringstream ssToVerify;
    performASimplePrintingTest(
        ssToVerify, [](stringstream &ssToVerify, int singleParameter1, int singleParameter2, int singleParameter3) {
            ALBA_WRN_PRINT(ssToVerify, singleParameter1, singleParameter2, singleParameter3);
        });
}

TEST(AlbaLogPrintsTest, ErrLogPrintingWithoutSpecifyNumberOfParametersWorks) {
    stringstream ssToVerify;
    performASimplePrintingTest(
        ssToVerify, [](stringstream &ssToVerify, int singleParameter1, int singleParameter2, int singleParameter3) {
            ALBA_ERR_PRINT(ssToVerify, singleParameter1, singleParameter2, singleParameter3);
        });
}

#endif

}  // namespace alba
