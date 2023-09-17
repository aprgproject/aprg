#include <Common/Debug/AlbaDebug.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <Common/Time/AlbaLocalTimeHelper.hpp>
#include <Common/Time/AlbaLocalTimer.hpp>
#include <CommonTests/DirectoryConstants.hpp>
#include <CommonTestsUtilities/File/FileUtilities.hpp>

#include <gtest/gtest.h>

#include <filesystem>

using namespace alba::AlbaDateTimeConstants;
using namespace alba::stringHelper;
using namespace std;
using namespace std::filesystem;
using namespace std::chrono;

namespace alba {

namespace {
AlbaDateTime allowableDifference(0, 0, 0, 0, 1, 0, 0);  // 1 minute
}

TEST(AlbaLocalTimerHelperTest, DISABLED_SleepForWorks) {
    // this is unstable because its not precise
    AlbaLocalTimer timer;

    sleepFor(4321);

    timer.stopTimer();
    EXPECT_EQ(4321U, timer.getElapsedTimeInMilliseconds());
}

TEST(AlbaLocalTimerHelperTest, ConvertFileTimeToAlbaDateTimeTimeWorks) {
    clearContentsOfFile(APRG_COMMON_TEST_FILE_TO_WRITE);

    AlbaDateTime lastModifiedTime(convertFileTimeToAlbaDateTime(last_write_time(APRG_COMMON_TEST_FILE_TO_WRITE)));

    AlbaDateTime currentTime(getCurrentDateTime());
    AlbaDateTime difference(currentTime - lastModifiedTime);
    AlbaDateTime allowableDifference(0, 0, 0, 0, 1, 0, 0);  // 1 minute
    ALBA_DBG_PRINT1(lastModifiedTime);
    ALBA_DBG_PRINT1(currentTime);
    ALBA_DBG_PRINT1(difference);
    ALBA_DBG_PRINT1(allowableDifference);
    EXPECT_LT(difference, allowableDifference);
}

TEST(AlbaLocalTimerHelperTest, ConvertSystemTimeToAlbaDateTimeWorksOnCurrentTime) {
    AlbaDateTime const time1(convertSystemTimeToAlbaDateTime(getSystemTimeNow()));
    AlbaDateTime const time2(convertSystemTimeToAlbaDateTime(getSystemTimeNow()));

    EXPECT_FALSE(time1.isEmpty());
    EXPECT_FALSE(time2.isEmpty());
    AlbaDateTime difference(time1 - time2);
    EXPECT_LT(difference, allowableDifference);
    // EXPECT_EQ(" 1 * 2023-09-16 20:03:14.090847", convertToString(time1));
    // EXPECT_EQ(" 1 * 2023-09-16 20:03:14.106822", convertToString(time2));
}

TEST(AlbaLocalTimerHelperTest, GetCurrentDateTimeWorks) {
    AlbaDateTime const time1(getCurrentDateTime());
    AlbaDateTime const time2(getCurrentDateTime());

    EXPECT_FALSE(time1.isEmpty());
    EXPECT_FALSE(time2.isEmpty());
    AlbaDateTime difference(time1 - time2);
    EXPECT_LT(difference, allowableDifference);
    // EXPECT_EQ(" 1 * 2023-09-16 20:03:14.107620", convertToString(time1));
    // EXPECT_EQ(" 1 * 2023-09-16 20:03:14.122168", convertToString(time2));
}

TEST(AlbaLocalTimerHelperTest, ConvertSinceEpochTimeToAlbaDateTimeWorksForSteadyTime) {
    AlbaDateTime const time1(convertSinceEpochTimeToAlbaDateTime(getSteadyTimeNow()));
    AlbaDateTime const time2(convertSinceEpochTimeToAlbaDateTime(getSteadyTimeNow()));

    EXPECT_TRUE(time1.isEmpty());
    EXPECT_TRUE(time2.isEmpty());
    AlbaDateTime difference(time1 - time2);
    EXPECT_LT(difference, allowableDifference);
    // EXPECT_EQ(" 1 * 0000-00-00 04:03:00.436885", convertToString(time1));
    // EXPECT_EQ(" 1 * 0000-00-00 04:03:00.452127", convertToString(time2));
}

TEST(AlbaLocalTimerHelperTest, ConvertSinceEpochTimeToAlbaDateTimeWorksForSystemTime) {
    AlbaDateTime const time1(convertSinceEpochTimeToAlbaDateTime(getSystemTimeNow()));
    AlbaDateTime const time2(convertSinceEpochTimeToAlbaDateTime(getSystemTimeNow()));

    EXPECT_FALSE(time1.isEmpty());
    EXPECT_FALSE(time2.isEmpty());
    AlbaDateTime difference(time1 - time2);
    EXPECT_LT(difference, allowableDifference);
    // EXPECT_EQ(" 1 * 0053-09-14 12:03:14.138281", convertToString(time1));
    // EXPECT_EQ(" 1 * 0053-09-14 12:03:14.1534223", convertToString(time2));
}

TEST(AlbaLocalTimerHelperTest, DISABLED_SleepUntilWorks) {
    // this is unstable because time varies
    AlbaDateTime const inputTime(2021, 9, 13, 3, 17, 0, 0);
    AlbaLocalTimer timer;

    sleepUntil(inputTime);

    timer.stopTimer();
    EXPECT_EQ(0U, timer.getElapsedTimeInMilliseconds());
}

TEST(AlbaLocalTimerHelperTest, ConvertSystemTimeToAlbaDateTimeWorks) {
    tm timeInformation{};  // dont brace initialize values
    timeInformation.tm_sec = 11;
    timeInformation.tm_min = 22;
    timeInformation.tm_hour = 3;
    timeInformation.tm_mday = 4;
    timeInformation.tm_mon = 5;
    timeInformation.tm_year = 96;
    LibrarySystemTime systemTime(convertTimeInformationToSystemTime(timeInformation, nanoseconds(777'777'777)));

    AlbaDateTime const currentTime(convertSystemTimeToAlbaDateTime(systemTime));

    EXPECT_EQ(" 1 * 1996-06-04 03:22:11.777777", convertToString(currentTime));
}

TEST(AlbaLocalTimerHelperTest, ConvertTimeInformationToSystemTimeWorks) {
    tm timeInformation{};  // dont brace initialize values
    timeInformation.tm_sec = 11;
    timeInformation.tm_min = 22;
    timeInformation.tm_hour = 3;
    timeInformation.tm_mday = 4;
    timeInformation.tm_mon = 5;
    timeInformation.tm_year = 96;

    LibrarySystemTime systemTime(convertTimeInformationToSystemTime(timeInformation, nanoseconds(777'777'777)));

    auto durationSinceEpoch = systemTime.time_since_epoch();
    // EXPECT_EQ(9650U, duration_cast<days>(durationSinceEpoch).count());
    // EXPECT_EQ(19U, duration_cast<hours>(durationSinceEpoch).count() % NUMBER_OF_HOURS_IN_AN_DAY);
    EXPECT_EQ(22U, duration_cast<minutes>(durationSinceEpoch).count() % NUMBER_OF_MINUTES_IN_AN_HOUR);
    EXPECT_EQ(11U, duration_cast<seconds>(durationSinceEpoch).count() % NUMBER_OF_SECONDS_IN_A_MINUTE);
    EXPECT_EQ(777U, duration_cast<milliseconds>(durationSinceEpoch).count() % NUMBER_OF_MILLISECONDS_IN_A_SECOND);
}

TEST(AlbaLocalTimerHelperTest, ConvertAlbaDateTimeToSystemTimeWorks) {
    AlbaDateTime const inputTime(1990, 1, 22, 3, 44, 55, 666666);

    LibrarySystemTime const systemTime(convertAlbaDateTimeToSystemTime(inputTime));

    auto durationSinceEpoch = systemTime.time_since_epoch();
    // EXPECT_EQ(7325U, duration_cast<days>(durationSinceEpoch).count());
    // EXPECT_EQ(19U, duration_cast<hours>(durationSinceEpoch).count() % NUMBER_OF_HOURS_IN_AN_DAY);
    EXPECT_EQ(44U, duration_cast<minutes>(durationSinceEpoch).count() % NUMBER_OF_MINUTES_IN_AN_HOUR);
    EXPECT_EQ(55U, duration_cast<seconds>(durationSinceEpoch).count() % NUMBER_OF_SECONDS_IN_A_MINUTE);
    EXPECT_EQ(666U, duration_cast<milliseconds>(durationSinceEpoch).count() % NUMBER_OF_MILLISECONDS_IN_A_SECOND);
}

}  // namespace alba
