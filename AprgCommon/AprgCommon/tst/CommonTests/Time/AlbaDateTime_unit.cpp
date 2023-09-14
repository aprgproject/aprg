#include <Common/String/AlbaStringHelper.hpp>
#include <Common/Time/AlbaDateTime.hpp>

#include <gtest/gtest.h>

using namespace alba::stringHelper;
using namespace std;
using PrintFormat = alba::AlbaDateTime::PrintFormat;

namespace alba {

TEST(AlbaDateTimeTest, LessThanOperatorWorksAsIntended) {
    AlbaDateTime const dateTime1(2015, 8, 20, 18, 14, 51, 565172);
    AlbaDateTime const dateTime2(2015, 8, 20, 18, 14, 51, 565173);
    AlbaDateTime const dateTime3(2015, 8, 20, 18, 14, 52, 565172);
    AlbaDateTime const dateTime4(2015, 8, 20, 18, 15, 51, 565172);
    AlbaDateTime const dateTime5(2015, 8, 20, 19, 14, 51, 565172);
    AlbaDateTime const dateTime6(2015, 8, 21, 18, 14, 51, 565172);
    AlbaDateTime const dateTime7(2015, 9, 20, 18, 14, 51, 565172);
    AlbaDateTime const dateTime8(2016, 8, 20, 18, 14, 51, 565172);

    EXPECT_TRUE(dateTime1 < dateTime2);
    EXPECT_TRUE(dateTime1 < dateTime3);
    EXPECT_TRUE(dateTime1 < dateTime4);
    EXPECT_TRUE(dateTime1 < dateTime5);
    EXPECT_TRUE(dateTime1 < dateTime6);
    EXPECT_TRUE(dateTime1 < dateTime7);
    EXPECT_TRUE(dateTime1 < dateTime8);

    EXPECT_FALSE(dateTime2 < dateTime1);
    EXPECT_FALSE(dateTime3 < dateTime1);
    EXPECT_FALSE(dateTime4 < dateTime1);
    EXPECT_FALSE(dateTime5 < dateTime1);
    EXPECT_FALSE(dateTime6 < dateTime1);
    EXPECT_FALSE(dateTime7 < dateTime1);
    EXPECT_FALSE(dateTime8 < dateTime1);

    EXPECT_FALSE(dateTime1 < dateTime1);
    EXPECT_FALSE(dateTime8 < dateTime8);
}

TEST(AlbaDateTimeTest, GreaterThanOperatorWorksAsIntended) {
    AlbaDateTime const dateTime1(2015, 8, 20, 18, 14, 51, 565172);
    AlbaDateTime const dateTime2(2015, 8, 20, 18, 14, 51, 565173);
    AlbaDateTime const dateTime3(2015, 8, 20, 18, 14, 52, 565172);
    AlbaDateTime const dateTime4(2015, 8, 20, 18, 15, 51, 565172);
    AlbaDateTime const dateTime5(2015, 8, 20, 19, 14, 51, 565172);
    AlbaDateTime const dateTime6(2015, 8, 21, 18, 14, 51, 565172);
    AlbaDateTime const dateTime7(2015, 9, 20, 18, 14, 51, 565172);
    AlbaDateTime const dateTime8(2016, 8, 20, 18, 14, 51, 565172);

    EXPECT_TRUE(dateTime8 > dateTime1);
    EXPECT_TRUE(dateTime8 > dateTime2);
    EXPECT_TRUE(dateTime8 > dateTime3);
    EXPECT_TRUE(dateTime8 > dateTime4);
    EXPECT_TRUE(dateTime8 > dateTime5);
    EXPECT_TRUE(dateTime8 > dateTime6);
    EXPECT_TRUE(dateTime8 > dateTime7);

    EXPECT_FALSE(dateTime1 > dateTime8);
    EXPECT_FALSE(dateTime2 > dateTime8);
    EXPECT_FALSE(dateTime3 > dateTime8);
    EXPECT_FALSE(dateTime4 > dateTime8);
    EXPECT_FALSE(dateTime5 > dateTime8);
    EXPECT_FALSE(dateTime6 > dateTime8);
    EXPECT_FALSE(dateTime7 > dateTime8);

    EXPECT_FALSE(dateTime1 > dateTime1);
    EXPECT_FALSE(dateTime8 > dateTime8);
}

TEST(AlbaDateTimeTest, EqualityOperatorWorksAsIntended) {
    AlbaDateTime const dateTime1(2015, 8, 20, 18, 14, 51, 565172);
    AlbaDateTime const dateTime2(2015, 8, 20, 18, 14, 51, 565173);
    AlbaDateTime const dateTime3(2015, 8, 20, 18, 14, 52, 565172);
    AlbaDateTime const dateTime4(2015, 8, 20, 18, 15, 51, 565172);
    AlbaDateTime const dateTime5(2015, 8, 20, 19, 14, 51, 565172);
    AlbaDateTime const dateTime6(2015, 8, 21, 18, 14, 51, 565172);
    AlbaDateTime const dateTime7(2015, 9, 20, 18, 14, 51, 565172);
    AlbaDateTime const dateTime8(2016, 8, 20, 18, 14, 51, 565172);

    EXPECT_FALSE(dateTime8 == dateTime1);
    EXPECT_FALSE(dateTime8 == dateTime2);
    EXPECT_FALSE(dateTime8 == dateTime3);
    EXPECT_FALSE(dateTime8 == dateTime4);
    EXPECT_FALSE(dateTime8 == dateTime5);
    EXPECT_FALSE(dateTime8 == dateTime6);
    EXPECT_FALSE(dateTime8 == dateTime7);

    EXPECT_TRUE(dateTime1 == dateTime1);
    EXPECT_TRUE(dateTime2 == dateTime2);
    EXPECT_TRUE(dateTime3 == dateTime3);
    EXPECT_TRUE(dateTime4 == dateTime4);
    EXPECT_TRUE(dateTime5 == dateTime5);
    EXPECT_TRUE(dateTime6 == dateTime6);
    EXPECT_TRUE(dateTime7 == dateTime7);
    EXPECT_TRUE(dateTime8 == dateTime8);
}

TEST(AlbaDateTimeTest, AdditionOperatorWorksAsIntended) {
    AlbaDateTime const dateTime1(0000, 00, 01, 01, 01, 01, 000001);
    AlbaDateTime const dateTime2(2000, 01, 02, 02, 02, 02, 000002);
    AlbaDateTime const expectedAnswer(2000, 01, 03, 03, 03, 03, 000003);

    AlbaDateTime const actualAnswer = dateTime1 + dateTime2;
    EXPECT_EQ(expectedAnswer, actualAnswer);
}

TEST(AlbaDateTimeTest, AdditionOperatorWorksWithOverflowValuesAfterYear1970) {
    AlbaDateTime const dateTime1(0000, 00, 00, 00, 00, 00, 000001);
    AlbaDateTime const dateTime2(1970, 12, 31, 23, 59, 59, 999999);
    AlbaDateTime const expectedAnswer(1971, 01, 01, 00, 00, 00, 000000);

    AlbaDateTime const actualAnswer = dateTime1 + dateTime2;
    EXPECT_EQ(expectedAnswer, actualAnswer);
}

TEST(AlbaDateTimeTest, AdditionOperatorWorksWithOverflowValuesBeforeYear1970) {
    AlbaDateTime const dateTime1(0000, 00, 00, 00, 00, 00, 000001);
    AlbaDateTime const dateTime2(1969, 12, 31, 23, 59, 59, 999999);
    AlbaDateTime const expectedAnswer(1970, 01, 01, 00, 00, 00, 000000);

    AlbaDateTime const actualAnswer = dateTime1 + dateTime2;
    EXPECT_EQ(expectedAnswer, actualAnswer);
}

TEST(AlbaDateTimeTest, AdditionOperatorWithDateOverflow) {
    AlbaDateTime const dateTime1(2000, 12, 31, 00, 00, 00, 000000);
    AlbaDateTime const dateTime2(2000, 12, 31, 00, 00, 0, 000000);
    AlbaDateTime const expectedAnswer(4002, 01, 01, 00, 00, 00, 000000);

    AlbaDateTime const actualAnswer = dateTime1 + dateTime2;
    EXPECT_EQ(expectedAnswer, actualAnswer);
}

TEST(AlbaDateTimeTest, SubtractionOperatorWorksAsIntended) {
    AlbaDateTime const dateTime1(0000, 00, 01, 01, 01, 01, 000001);
    AlbaDateTime const dateTime2(2000, 01, 02, 02, 02, 02, 000002);
    AlbaDateTime const expectedAnswer(2000, 01, 01, 01, 01, 01, 000001);

    AlbaDateTime const actualAnswer = dateTime2 - dateTime1;
    EXPECT_EQ(expectedAnswer, actualAnswer);
}

TEST(AlbaDateTimeTest, SubtractionOperatorWithUnderflowValues) {
    AlbaDateTime const dateTime1(0000, 00, 00, 00, 00, 00, 000001);
    AlbaDateTime const dateTime2(2000, 01, 01, 00, 00, 00, 000000);
    AlbaDateTime const expectedAnswer(1999, 12, 31, 23, 59, 59, 999999);

    AlbaDateTime const actualAnswer = dateTime2 - dateTime1;
    EXPECT_EQ(expectedAnswer, actualAnswer);
}

TEST(AlbaDateTimeTest, SubtractionOperatorWorksInRealScenario) {
    AlbaDateTime const dateTime1(2018, 9, 30, 9, 55, 50, 110000);
    AlbaDateTime const dateTime2(2018, 9, 30, 9, 55, 42, 91000);
    AlbaDateTime const expectedAnswer(0000, 0, 0, 00, 00, 8, 19000);

    AlbaDateTime const actualAnswer = dateTime1 - dateTime2;
    EXPECT_EQ(expectedAnswer, actualAnswer);
}

TEST(AlbaDateTimeTest, OutputStreamOperatorWorks) {
    AlbaDateTime const dateTime(2017, 10, 6, 4, 59, 44, 32487);

    EXPECT_EQ(" 1 * 2017-10-06 04:59:44.032487", convertToString(dateTime));
}

TEST(AlbaDateTimeTest, ConstructorWithYearMonthDayAndHourMinuteSecondAndMicrosecondWorks) {
    AlbaDateTime const dateTime(AlbaYearMonthDay(2017, 10, 6), AlbaHourMinuteSecond(4, 59, 44), 32487);

    EXPECT_FALSE(dateTime.isEmpty());
    EXPECT_EQ(2017U, dateTime.getYears());
    EXPECT_EQ(10U, dateTime.getMonths());
    EXPECT_EQ(6U, dateTime.getDays());
    EXPECT_EQ(4U, dateTime.getHours());
    EXPECT_EQ(59U, dateTime.getMinutes());
    EXPECT_EQ(44U, dateTime.getSeconds());
    EXPECT_EQ(32487U, dateTime.getMicroSeconds());
}

TEST(AlbaDateTimeTest, GetYearMonthDayWorks) {
    AlbaDateTime const dateTime(2017, 10, 6, 4, 59, 44, 32487);

    EXPECT_EQ(AlbaYearMonthDay(2017, 10, 6), dateTime.getYearMonthDay());
}

TEST(AlbaDateTimeTest, GetYearsWorks) {
    AlbaDateTime const dateTime(2017, 10, 6, 4, 59, 44, 32487);

    EXPECT_EQ(2017U, dateTime.getYears());
}

TEST(AlbaDateTimeTest, DefaultConstructorWorks) {
    AlbaDateTime const dateTime;

    EXPECT_TRUE(dateTime.isEmpty());
    EXPECT_EQ(0U, dateTime.getYears());
    EXPECT_EQ(0U, dateTime.getMonths());
    EXPECT_EQ(0U, dateTime.getDays());
    EXPECT_EQ(0U, dateTime.getHours());
    EXPECT_EQ(0U, dateTime.getMinutes());
    EXPECT_EQ(0U, dateTime.getSeconds());
    EXPECT_EQ(0U, dateTime.getMicroSeconds());
}

TEST(AlbaDateTimeTest, ConstructorWithAllParametersWorks) {
    AlbaDateTime const dateTime(2017, 10, 6, 4, 59, 44, 32487);

    EXPECT_FALSE(dateTime.isEmpty());
    EXPECT_EQ(2017U, dateTime.getYears());
    EXPECT_EQ(10U, dateTime.getMonths());
    EXPECT_EQ(6U, dateTime.getDays());
    EXPECT_EQ(4U, dateTime.getHours());
    EXPECT_EQ(59U, dateTime.getMinutes());
    EXPECT_EQ(44U, dateTime.getSeconds());
    EXPECT_EQ(32487U, dateTime.getMicroSeconds());
}

TEST(AlbaDateTimeTest, NamedConstructorWithTotalDaysAndTotalSecondsAndTotalMicrosecondsWorks) {
    AlbaDateTime const dateTime(AlbaDateTime::createFromTotalDaysAndSecondsAndMicroSeconds(736974U, 17984U, 32487U));

    EXPECT_FALSE(dateTime.isEmpty());
    EXPECT_EQ(2017U, dateTime.getYears());
    EXPECT_EQ(10U, dateTime.getMonths());
    EXPECT_EQ(6U, dateTime.getDays());
    EXPECT_EQ(4U, dateTime.getHours());
    EXPECT_EQ(59U, dateTime.getMinutes());
    EXPECT_EQ(44U, dateTime.getSeconds());
    EXPECT_EQ(32487U, dateTime.getMicroSeconds());
}

TEST(AlbaDateTimeTest, GetMonthsWorks) {
    AlbaDateTime const dateTime(2017, 10, 6, 4, 59, 44, 32487);

    EXPECT_EQ(10U, dateTime.getMonths());
}

TEST(AlbaDateTimeTest, GetDaysWorks) {
    AlbaDateTime const dateTime(2017, 10, 6, 4, 59, 44, 32487);

    EXPECT_EQ(6U, dateTime.getDays());
}

TEST(AlbaDateTimeTest, IsEmptyWorks) {
    AlbaDateTime const emptyDateTime;
    AlbaDateTime const nonEmptyDateTime(2017, 10, 6, 4, 59, 44, 32487);

    EXPECT_TRUE(emptyDateTime.isEmpty());
    EXPECT_FALSE(nonEmptyDateTime.isEmpty());
}

TEST(AlbaDateTimeTest, GetHourMinutesSecondWorks) {
    AlbaDateTime const dateTime(2017, 10, 6, 4, 59, 44, 32487);

    EXPECT_EQ(AlbaHourMinuteSecond(4, 59, 44), dateTime.getHourMinutesSecond());
}

TEST(AlbaDateTimeTest, GetHoursWorks) {
    AlbaDateTime const dateTime(2017, 10, 6, 4, 59, 44, 32487);

    EXPECT_EQ(4U, dateTime.getHours());
}

TEST(AlbaDateTimeTest, GetMinutesWorks) {
    AlbaDateTime const dateTime(2017, 10, 6, 4, 59, 44, 32487);

    EXPECT_EQ(59U, dateTime.getMinutes());
}

TEST(AlbaDateTimeTest, GetSecondsWorks) {
    AlbaDateTime const dateTime(2017, 10, 6, 4, 59, 44, 32487);

    EXPECT_EQ(44U, dateTime.getSeconds());
}

TEST(AlbaDateTimeTest, GetMicroSecondsWorks) {
    AlbaDateTime const dateTime(2017, 10, 6, 4, 59, 44, 32487);

    EXPECT_EQ(32487U, dateTime.getMicroSeconds());
}

TEST(AlbaDateTimeTest, SubtractionOperatorWithNegativeResult) {
    AlbaDateTime const dateTime1(0000, 00, 00, 00, 00, 00, 000001);
    AlbaDateTime const dateTime2(2000, 01, 01, 00, 00, 00, 000000);
    AlbaDateTime expectedAnswer(1999, 12, 31, 23, 59, 59, 999999);
    expectedAnswer.negate();

    AlbaDateTime const actualAnswer = dateTime1 - dateTime2;
    EXPECT_EQ(expectedAnswer, actualAnswer);
}

TEST(AlbaDateTimeTest, OutputStreamOperatorWorksForPrintObjectWithDifferentTypes) {
    AlbaDateTime const dateTime(2017, 10, 6, 4, 59, 44, 32487);

    EXPECT_EQ(" 1 * 2017-10-06 04:59:44.032487", convertToString(dateTime));
    EXPECT_EQ("2017-10-06 04:59:44.032487", convertToString(dateTime.getPrintObject<PrintFormat::Standard>()));
    EXPECT_EQ(
        " 1 * 2017-10-06 04:59:44.032487", convertToString(dateTime.getPrintObject<PrintFormat::StandardWithSign>()));
    EXPECT_EQ("2017-10-06T04:59:44.032487", convertToString(dateTime.getPrintObject<PrintFormat::Iso8601>()));
    EXPECT_EQ(
        "October 6, 2017 04:59:44.032487 AM", convertToString(dateTime.getPrintObject<PrintFormat::HumanReadable>()));
    EXPECT_EQ(
        "736974 days, 4 hours, 59 minutes, 44 seconds, 32487 microseconds from now",
        convertToString(dateTime.getPrintObject<PrintFormat::RelativeTime>()));
    EXPECT_EQ("04:59:44", convertToString(dateTime.getPrintObject<PrintFormat::TimeWithColon>()));
    EXPECT_EQ(
        "04:59:44.032487", convertToString(dateTime.getPrintObject<PrintFormat::TimeWithColonWithMicroSeconds>()));
}

}  // namespace alba
