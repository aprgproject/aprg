#include "RevisionEditor.hpp"

#include <Common/File/AlbaFileReader.hpp>
#include <Common/Math/Helpers/ComputationHelpers.hpp>
#include <Common/Math/Helpers/PrecisionHelpers.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/Print/AlbaLogPrints.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace alba::mathHelper;
using namespace alba::stringHelper;
using namespace std;

namespace {
std::string const START_ENTRY_PATTERN = "([{";
std::string const END_ENTRY_PATTERN = "}])";
}  // namespace

namespace alba {

RevisionEditor::RevisionEditor() : m_sixtyRandomizer(1, 59) {}

void RevisionEditor::setRevisionDataFromFile() {
    setDataFromGitHistory();
    setDataOnCommitsPerDay();
    // saveCommitsPerHourToFile();
    // saveCommitsInADayToFile();
    // saveCommitMessagesToFile();
}

void RevisionEditor::editCommitDates() {
    AlbaUniformNonDeterministicRandomizer<int> maxCommitRandomizer(19, 26);
    AlbaYearMonthDay startDate(2020, 10, 1);
    AlbaYearMonthDay endDate(2023, 8, 1);  // not a strict end date
    DaysIntervals gaps{createDaysInterval(2020, 10, 3, 2020, 10, 8),   createDaysInterval(2020, 11, 1, 2020, 11, 14),
                       createDaysInterval(2020, 12, 12, 2020, 12, 31), createDaysInterval(2021, 1, 1, 2021, 1, 12),
                       createDaysInterval(2021, 2, 12, 2021, 2, 28),   createDaysInterval(2021, 4, 3, 2021, 4, 15),
                       createDaysInterval(2021, 5, 1, 2021, 5, 25),    createDaysInterval(2021, 7, 10, 2021, 7, 15),
                       createDaysInterval(2021, 9, 22, 2021, 9, 30),   createDaysInterval(2021, 10, 1, 2021, 10, 15),
                       createDaysInterval(2021, 11, 7, 2021, 11, 13),  createDaysInterval(2021, 12, 12, 2021, 12, 31),
                       createDaysInterval(2022, 1, 1, 2022, 1, 14),    createDaysInterval(2022, 2, 17, 2021, 2, 24),
                       createDaysInterval(2022, 3, 1, 2022, 3, 9),     createDaysInterval(2022, 4, 9, 2021, 4, 17),
                       createDaysInterval(2022, 6, 1, 2022, 6, 28),    createDaysInterval(2022, 7, 22, 2021, 7, 26),
                       createDaysInterval(2022, 8, 7, 2022, 8, 11),    createDaysInterval(2022, 10, 7, 2021, 10, 12),
                       createDaysInterval(2022, 11, 11, 2022, 11, 14), createDaysInterval(2022, 12, 14, 2021, 12, 31),
                       createDaysInterval(2023, 1, 1, 2023, 1, 14),    createDaysInterval(2023, 4, 4, 2023, 4, 17),
                       createDaysInterval(2023, 6, 1, 2023, 6, 23),    createDaysInterval(2023, 7, 13, 2023, 7, 20),
                       createDaysInterval(2023, 8, 8, 2023, 8, 11),    createDaysInterval(2023, 10, 7, 2023, 10, 12),
                       createDaysInterval(2023, 11, 11, 2023, 11, 14), createDaysInterval(2023, 12, 14, 2023, 12, 31)};
    uint32_t startDayCount = startDate.getTotalDays();
    uint32_t endDayCount = endDate.getTotalDays();
    int revisionIndex = 0, gapIndex = 0;
    int const numberOfRevisions = static_cast<int>(m_revisionEntries.size());
    for (uint32_t currentDayCount = startDayCount; revisionIndex < numberOfRevisions; ++currentDayCount) {
        uint32_t remainingNumberOfDays = (endDayCount > currentDayCount) ? endDayCount - currentDayCount : 1;
        while (gapIndex < static_cast<int>(gaps.size()) && gaps[gapIndex].second < currentDayCount) {
            ++gapIndex;
        }
        if (gapIndex < static_cast<int>(gaps.size())) {
            DaysInterval const currentGap(gaps[gapIndex]);
            if (currentGap.first <= currentDayCount && currentDayCount <= currentGap.second) {
                continue;
            }
        }
        auto targetAverageCommit = clampHigherBound<double>(
            clampLowerBound<double>(
                static_cast<double>(numberOfRevisions - revisionIndex) / remainingNumberOfDays, 3.4),
            4.5);
        int numberOfCommits = getRandomCommitsOfADay(targetAverageCommit);
        numberOfCommits =
            (numberOfCommits > numberOfRevisions - revisionIndex) ? numberOfRevisions - revisionIndex : numberOfCommits;
        numberOfCommits = clampHigherBound<int>(numberOfCommits, maxCommitRandomizer.getRandomValue());

        AlbaYearMonthDay ymd = AlbaYearMonthDay::createFromTotalDays(currentDayCount);
        ALBA_INF_PRINT5(cout, ymd.getYears(), ymd.getMonths(), ymd.getDays(), targetAverageCommit, numberOfCommits);
        vector<AlbaHourMinuteSecond> hmses;
        for (int commitNumber = 0; commitNumber < numberOfCommits; ++commitNumber) {
            hmses.emplace_back(getRandomHour(), m_sixtyRandomizer.getRandomValue(), m_sixtyRandomizer.getRandomValue());
        }
        sort(hmses.begin(), hmses.end());

        for (AlbaHourMinuteSecond const& hms : hmses) {
            AlbaDateTime revisedDateTime(ymd, hms, 0U);
            m_revisionEntries[revisionIndex++].dateTime = revisedDateTime;
        }
    }
}

void RevisionEditor::editCommitMessages() {
    ifstream newMessagesStream(R"(F:\Branches\GitMigration\git_old_repo\newCommitMessages.txt)");
    AlbaFileReader newMessageReader(newMessagesStream);
    int revisionIndex = 0;
    while (newMessageReader.isNotFinished() && revisionIndex < static_cast<int>(m_revisionEntries.size())) {
        string line(newMessageReader.getLineAndIgnoreWhiteSpaces());
        m_revisionEntries[revisionIndex++].message = line;
    }
}

void RevisionEditor::saveNewRevisionHistory() const {
    ofstream newGitHistoryStream(R"(F:\Branches\GitMigration\git_old_repo\newGitHistory.txt)");
    for (RevisionEntry const& revisionEntry : m_revisionEntries) {
        newGitHistoryStream << START_ENTRY_PATTERN << revisionEntry.revisionHash << END_ENTRY_PATTERN << " ";
        newGitHistoryStream << START_ENTRY_PATTERN << setfill('0');
        newGitHistoryStream << setw(4) << revisionEntry.dateTime.getYears() << "-";
        newGitHistoryStream << setw(2) << revisionEntry.dateTime.getMonths() << "-";
        newGitHistoryStream << setw(2) << revisionEntry.dateTime.getDays() << "T";
        newGitHistoryStream << setw(2) << revisionEntry.dateTime.getHours() << ":";
        newGitHistoryStream << setw(2) << revisionEntry.dateTime.getMinutes() << ":";
        newGitHistoryStream << setw(2) << revisionEntry.dateTime.getSeconds() << "+08:00";
        newGitHistoryStream << END_ENTRY_PATTERN << " ";
        newGitHistoryStream << START_ENTRY_PATTERN << "mevalba <markearvinalba@gmail.com>" << END_ENTRY_PATTERN << " ";
        newGitHistoryStream << START_ENTRY_PATTERN << revisionEntry.message << END_ENTRY_PATTERN << "\n";
    }
}

RevisionEditor::RevisionEntry RevisionEditor::getRevisionEntry(string const& line) {
    int index = 0;
    string revisionHash = getStringInBetweenTwoStrings(line, START_ENTRY_PATTERN, END_ENTRY_PATTERN, index);
    index = line.find(END_ENTRY_PATTERN, index) + 3;
    string date = getStringInBetweenTwoStrings(line, START_ENTRY_PATTERN, END_ENTRY_PATTERN, index);
    index = line.find(END_ENTRY_PATTERN, index) + 3;
    string author = getStringInBetweenTwoStrings(line, START_ENTRY_PATTERN, END_ENTRY_PATTERN, index);
    index = line.find(END_ENTRY_PATTERN, index) + 3;
    string message = getStringInBetweenTwoStrings(line, START_ENTRY_PATTERN, END_ENTRY_PATTERN, index);
    // ALBA_PRINT4(revisionHash, date, author, message);
    return {revisionHash, getDateTime(date), author, message};
}

AlbaDateTime RevisionEditor::getDateTime(string const& date) {
    int index = 0;
    int year = convertStringToNumber<int>(getStringBeforeThisString(date, "-", index));
    index = date.find("-", index) + 1;
    int month = convertStringToNumber<int>(getStringBeforeThisString(date, "-", index));
    index = date.find("-", index) + 1;
    int day = convertStringToNumber<int>(getStringBeforeThisString(date, "T", index));
    index = date.find("T", index) + 1;
    int hour = convertStringToNumber<int>(getStringBeforeThisString(date, ":", index));
    index = date.find(":", index) + 1;
    int minute = convertStringToNumber<int>(getStringBeforeThisString(date, ":", index));
    index = date.find(":", index) + 1;
    int second = convertStringToNumber<int>(getStringBeforeThisString(date, "+", index));

    return AlbaDateTime(year, month, day, hour, minute, second, 0U);
}

RevisionEditor::DaysInterval RevisionEditor::createDaysInterval(
    uint32_t const year1, uint32_t const month1, uint32_t const day1, uint32_t const year2, uint32_t const month2,
    uint32_t const day2) {
    return {AlbaYearMonthDay(year1, month1, day1).getTotalDays(), AlbaYearMonthDay(year2, month2, day2).getTotalDays()};
}

void RevisionEditor::setDataFromGitHistory() {
    ifstream revisionHistoryStream(R"(F:\Branches\GitMigration\git_old_repo\formattedGitHistory.txt)");
    AlbaFileReader revisionHistoryReader(revisionHistoryStream);
    AlbaYearMonthDay dayToCheck;
    int numberOfCommitsOnThisDay = 1, totalNumberOfInstances = 0;
    bool isFirst = true;
    while (revisionHistoryReader.isNotFinished()) {
        string line(revisionHistoryReader.getLineAndIgnoreWhiteSpaces());
        if (!line.empty()) {
            m_revisionEntries.emplace_back(getRevisionEntry(line));
            RevisionEntry const& currentRevision(m_revisionEntries.back());
            AlbaDateTime const& currentDateTime(currentRevision.dateTime);
            if (isFirst) {
                dayToCheck = currentDateTime.getYearMonthDay();
                isFirst = false;
            } else if (dayToCheck != currentDateTime.getYearMonthDay()) {
                if (numberOfCommitsOnThisDay < MAX_NUMBER_COMMITS_PER_DAY) {
                    ++m_numberInstancesOfEachDayCommitCount[numberOfCommitsOnThisDay];
                    ++totalNumberOfInstances;
                } else {
                    ALBA_INF_PRINT2(cout, currentDateTime, numberOfCommitsOnThisDay);
                }
                numberOfCommitsOnThisDay = 1;
                dayToCheck = currentDateTime.getYearMonthDay();
            } else {
                ++numberOfCommitsOnThisDay;
            }
            ++m_numberOfCommitsPerHour[currentDateTime.getHours()];
        }
    }
    // add fake data of days with no commits
    m_numberInstancesOfEachDayCommitCount[0] = totalNumberOfInstances * 0.5;
    m_revisionRandomizer.setMinimumAndMaximum(m_revisionEntries.empty() ? 0 : 1, m_revisionEntries.size());
}

void RevisionEditor::setDataOnCommitsPerDay() {
    int numberOfCommitsOfADay = 0;
    int totalWeight = 0;
    int totalNumberOfInstances = 0;
    for (int const numberOfInstances : m_numberInstancesOfEachDayCommitCount) {
        totalWeight += numberOfCommitsOfADay * numberOfInstances;
        totalNumberOfInstances += numberOfInstances;
        ++numberOfCommitsOfADay;
    }
    m_dayInstancesRandomizer.setMinimumAndMaximum(totalNumberOfInstances > 0 ? 1 : 0, totalNumberOfInstances);
    m_originalAverageCommitPerDay = static_cast<double>(totalWeight) / totalNumberOfInstances;
    ALBA_INF_PRINT3(cout, totalWeight, totalNumberOfInstances, m_originalAverageCommitPerDay);
}

void RevisionEditor::saveCommitsPerHourToFile() const {
    ofstream commitsPerHourStream(R"(F:\Branches\GitMigration\git_old_repo\commitsPerHour.csv)");
    int hour = 0;
    for (int const numberOfCommitsAtThisHour : m_numberOfCommitsPerHour) {
        commitsPerHourStream << hour << "," << numberOfCommitsAtThisHour << ",\n";
        ++hour;
    }
}

void RevisionEditor::saveCommitsInADayToFile() const {
    ofstream commitsInADayStream(R"(F:\Branches\GitMigration\git_old_repo\commitsInADay.csv)");
    int numberOfCommitsOfADay = 0;
    for (int const numberOfInstancesOfThisDayCommitCount : m_numberInstancesOfEachDayCommitCount) {
        commitsInADayStream << numberOfCommitsOfADay << "," << numberOfInstancesOfThisDayCommitCount << ",\n";
        ++numberOfCommitsOfADay;
    }
}

void RevisionEditor::saveCommitMessagesToFile() const {
    ofstream commitMessagesStream(R"(F:\Branches\GitMigration\git_old_repo\commitMessages.txt)");
    for (RevisionEntry const& revisionEntry : m_revisionEntries) {
        commitMessagesStream << revisionEntry.message << "\n";
    }
}

int RevisionEditor::getRandomCommitsOfADay(double const targetAverageCommitOfADay) {
    int remainingNumberOfInstances = m_dayInstancesRandomizer.getRandomValue();
    int numberOfCommitsPerDay = 0;
    for (int const numberOfInstances : m_numberInstancesOfEachDayCommitCount) {
        if (remainingNumberOfInstances <= numberOfInstances) {
            return getIntegerAfterRoundingADoubleValue<int>(
                numberOfCommitsPerDay * targetAverageCommitOfADay / m_originalAverageCommitPerDay);
        }
        remainingNumberOfInstances -= numberOfInstances;
        ++numberOfCommitsPerDay;
    }
    return 0;
}

int RevisionEditor::getRandomHour() {
    int remainingRevisionCount = m_revisionRandomizer.getRandomValue();
    int hour = 0;
    for (int const numberOfCommitsAtThisHour : m_numberOfCommitsPerHour) {
        if (remainingRevisionCount <= numberOfCommitsAtThisHour) {
            return hour;
        }
        remainingRevisionCount -= numberOfCommitsAtThisHour;
        ++hour;
    }
    return 0;
}

}  // namespace alba
