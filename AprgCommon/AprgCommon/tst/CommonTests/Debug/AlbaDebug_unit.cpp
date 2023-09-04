
// Set external output stream file path
// #define ALBA_DBG_PRINT_EXTERNAL_OUTPUT_STREAM_FILE_PATH APRG_DIR "/Log.txt"

// Set external output stream object
#include <sstream>
namespace {
std::stringstream s_debugStringStream;  // clazy:exclude=non-pod-global-static
}  // namespace
#define ALBA_DBG_PRINT_EXTERNAL_OUTPUT_STREAM_OBJECT s_debugStringStream

// Start of test file
#include <Common/Debug/AlbaDebug.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <CommonTests/Print/PrintUtilities.hpp>

#include <gtest/gtest.h>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

TEST(AlbaDebugTest, DebugPrintingWorks) {
    s_debugStringStream.str(string());
    s_debugStringStream.clear();
    performASimplePrintingTest(
        s_debugStringStream,
        [](stringstream&, int const singleParameter1, int const singleParameter2, int const singleParameter3) {
            // NOLINTNEXTLINE(bugprone-lambda-function-name)
            ALBA_DBG_PRINT3(singleParameter1, singleParameter2, singleParameter3);
        });
}

TEST(AlbaDebugTest, ManipulateOutputStreamsWorks) {
    s_debugStringStream.str(string());
    s_debugStringStream.clear();
    int singleParameter1 = 12;
    int singleParameter2 = 345;
    int singleParameter3 = 6789;

    ALBA_DBG_PRINT_MANIPULATE_OUTPUT(uppercase);
    ALBA_DBG_PRINT_MANIPULATE_OUTPUT(hex);
    ALBA_DBG_PRINT3(singleParameter1, singleParameter2, singleParameter3);
    ALBA_DBG_PRINT_MANIPULATE_OUTPUT(dec);

    string actualPrintString(s_debugStringStream.str());
    int runningIndex = 0;
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "singleParameter1", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "C", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "singleParameter2", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "159", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "singleParameter3", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "1A85", runningIndex));
}

namespace {
class SampleClass {
public:
    SampleClass(int const parameter1, int const parameter2) : m_parameter1(parameter1), m_parameter2(parameter2) {}

    [[nodiscard]] int getSum() const { return m_parameter1 + m_parameter2; }

    // Note that "friend" keyword is added here.
    friend ALBA_DBG_CLASS_OUTPUT_OPERATOR_DEFINITION(
        SampleClass const& object, "(parameter1:" << object.m_parameter1 << ",parameter2:" << object.m_parameter2
                                                  << ",sum:" << object.getSum() << ")");

private:
    int m_parameter1;
    int m_parameter2;
};
}  // namespace

TEST(AlbaDebugTest, DebugClassOutputOperatorsWorks) {
    s_debugStringStream.str(string());
    s_debugStringStream.clear();

    SampleClass object(1234, 7777);

    ALBA_DBG_PRINT1(object);

    string actualPrintString(s_debugStringStream.str());
    int runningIndex = 0;
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "parameter1", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "1234", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "parameter2", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "7777", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "sum", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "9011", runningIndex));
}

#if defined(__clang__) || defined(__GNUC__) || defined(__GNUG__)

TEST(AlbaDebugTest, PrintingWithoutSpecifyNumberOfParametersWorks) {
    s_debugStringStream.str(string());
    s_debugStringStream.clear();
    performASimplePrintingTest(
        s_debugStringStream,
        [](stringstream&, int const singleParameter1, int const singleParameter2, int const singleParameter3) {
            // NOLINTNEXTLINE(bugprone-lambda-function-name)
            ALBA_DBG_PRINT(singleParameter1, singleParameter2, singleParameter3);
        });
}

#endif

}  // namespace alba
