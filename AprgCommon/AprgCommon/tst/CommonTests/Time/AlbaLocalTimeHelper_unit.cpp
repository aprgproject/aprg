#include <Common/String/AlbaStringHelper.hpp>
#include <Common/Time/AlbaLocalTimeHelper.hpp>
#include <Common/Time/AlbaLocalTimer.hpp>

#include <gtest/gtest.h>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

TEST(AlbaLocalTimerHelperTest, DISABLED_SleepForWorks) {
    // this is unstable because its not precise
    AlbaLocalTimer timer;

    sleepFor(4321);

    timer.stopTimer();
    EXPECT_EQ(4321U, timer.getElapsedTimeInMilliseconds());
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
    LibrarySystemTime systemTime(convertTimeInformationToSystemTime(timeInformation, chrono::nanoseconds(777'777'777)));

    AlbaDateTime const currentTime(convertSystemTimeToAlbaDateTime(systemTime));

    EXPECT_EQ(" 1 * 1996-06-04 03:22:11.777777", convertToString(currentTime));
}

TEST(AlbaLocalTimerHelperTest, ConvertSystemTimeToAlbaDateTimeWorksOnCurrentTime) {
    AlbaDateTime const time1(convertSystemTimeToAlbaDateTime(getSystemTimeNow()));
    sleepFor(1);
    AlbaDateTime const time2(convertSystemTimeToAlbaDateTime(getSystemTimeNow()));

    EXPECT_FALSE(time1.isEmpty());
    EXPECT_FALSE(time2.isEmpty());
    AlbaDateTime compare1(
        time1.getYears(), time1.getMonths(), time1.getDays(), time1.getHours(), time1.getMinutes(), 0U, 0U);
    AlbaDateTime compare2(
        time2.getYears(), time2.getMonths(), time2.getDays(), time2.getHours(), time2.getMinutes(), 0U, 0U);
    EXPECT_EQ(compare1, compare2);
    // EXPECT_EQ(" 1 * 2023-09-16 20:03:14.090847", convertToString(time1));
    // EXPECT_EQ(" 1 * 2023-09-16 20:03:14.106822", convertToString(time2));
}

TEST(AlbaLocalTimerHelperTest, ConvertTimeInformationToSystemTimeWorks) {
    tm timeInformation{};  // dont brace initialize values
    timeInformation.tm_sec = 11;
    timeInformation.tm_min = 22;
    timeInformation.tm_hour = 3;
    timeInformation.tm_mday = 4;
    timeInformation.tm_mon = 5;
    timeInformation.tm_year = 96;

    LibrarySystemTime systemTime(convertTimeInformationToSystemTime(timeInformation, chrono::nanoseconds(777'777'777)));

    EXPECT_EQ(833829731777777777, systemTime.time_since_epoch().count());
}

TEST(AlbaLocalTimerHelperTest, ConvertAlbaDateTimeToSystemTimeWorks) {
    AlbaDateTime const inputTime(1990, 1, 22, 3, 44, 55, 666666);

    LibrarySystemTime const systemTime(convertAlbaDateTimeToSystemTime(inputTime));

    EXPECT_EQ(632951095666666000, systemTime.time_since_epoch().count());
}

TEST(AlbaLocalTimerHelperTest, GetCurrentDateTimeWorks) {
    AlbaDateTime const time1(getCurrentDateTime());
    sleepFor(1);
    AlbaDateTime const time2(getCurrentDateTime());

    EXPECT_FALSE(time1.isEmpty());
    EXPECT_FALSE(time2.isEmpty());
    AlbaDateTime compare1(
        time1.getYears(), time1.getMonths(), time1.getDays(), time1.getHours(), time1.getMinutes(), 0U, 0U);
    AlbaDateTime compare2(
        time2.getYears(), time2.getMonths(), time2.getDays(), time2.getHours(), time2.getMinutes(), 0U, 0U);
    EXPECT_EQ(compare1, compare2);
    // EXPECT_EQ(" 1 * 2023-09-16 20:03:14.107620", convertToString(time1));
    // EXPECT_EQ(" 1 * 2023-09-16 20:03:14.122168", convertToString(time2));
}

TEST(AlbaLocalTimerHelperTest, ConvertSinceEpochTimeToAlbaDateTimeWorksForSteadyTime) {
    AlbaDateTime const time1(convertSinceEpochTimeToAlbaDateTime(getSteadyTimeNow()));
    sleepFor(1);
    AlbaDateTime const time2(convertSinceEpochTimeToAlbaDateTime(getSteadyTimeNow()));

    EXPECT_TRUE(time1.isEmpty());
    EXPECT_TRUE(time2.isEmpty());
    AlbaDateTime compare1(
        time1.getYears(), time1.getMonths(), time1.getDays(), time1.getHours(), time1.getMinutes(), 0U, 0U);
    AlbaDateTime compare2(
        time2.getYears(), time2.getMonths(), time2.getDays(), time2.getHours(), time2.getMinutes(), 0U, 0U);
    EXPECT_EQ(compare1, compare2);
    // EXPECT_EQ(" 1 * 0000-00-00 04:03:00.436885", convertToString(time1));
    // EXPECT_EQ(" 1 * 0000-00-00 04:03:00.452127", convertToString(time2));
}

TEST(AlbaLocalTimerHelperTest, ConvertSinceEpochTimeToAlbaDateTimeWorksForSystemTime) {
    AlbaDateTime const time1(convertSinceEpochTimeToAlbaDateTime(getSystemTimeNow()));
    sleepFor(1);
    AlbaDateTime const time2(convertSinceEpochTimeToAlbaDateTime(getSystemTimeNow()));

    EXPECT_FALSE(time1.isEmpty());
    EXPECT_FALSE(time2.isEmpty());
    AlbaDateTime compare1(
        time1.getYears(), time1.getMonths(), time1.getDays(), time1.getHours(), time1.getMinutes(), 0U, 0U);
    AlbaDateTime compare2(
        time2.getYears(), time2.getMonths(), time2.getDays(), time2.getHours(), time2.getMinutes(), 0U, 0U);
    EXPECT_EQ(compare1, compare2);
    // EXPECT_EQ(" 1 * 0053-09-14 12:03:14.138281", convertToString(time1));
    // EXPECT_EQ(" 1 * 0053-09-14 12:03:14.1534223", convertToString(time2));
}
}  // namespace alba
