#pragma once

#include <Common/Randomizer/AlbaUniformNonDeterministicRandomizer.hpp>
#include <Common/Time/AlbaDateTime.hpp>

#include <array>
#include <string>
#include <vector>

namespace alba {

class RevisionEditor {
    struct RevisionEntry {
        std::string revisionHash;
        AlbaDateTime dateTime;
        std::string author;
        std::string message;
    };

    using RevisionEntries = std::vector<RevisionEntry>;
    using DaysInterval = std::pair<uint32_t, uint32_t>;
    using DaysIntervals = std::vector<DaysInterval>;

public:
    RevisionEditor();
    void saveNewRevisionHistory() const;
    void setRevisionDataFromFile();
    void editCommitDates();
    void editCommitMessages();

private:
    void saveCommitsPerHourToFile() const;
    void saveCommitsInADayToFile() const;
    void saveCommitMessagesToFile() const;
    void setDataFromGitHistory();
    void setDataOnCommitsPerDay();
    int getRandomCommitsOfADay(double const targetAverageCommitOfADay);
    int getRandomHour();
    static AlbaDateTime getDateTime(std::string const& date);

    static DaysInterval createDaysInterval(
        uint32_t const year1, uint32_t const month1, uint32_t const day1, uint32_t const year2, uint32_t const month2,
        uint32_t const day2);

    static RevisionEntry getRevisionEntry(std::string const& line);
    static constexpr int MAX_NUMBER_COMMITS_PER_DAY = 20;
    double m_originalAverageCommitPerDay{};
    std::array<int, MAX_NUMBER_COMMITS_PER_DAY> m_numberInstancesOfEachDayCommitCount{};
    std::array<int, 24> m_numberOfCommitsPerHour{};
    RevisionEntries m_revisionEntries;
    AlbaUniformNonDeterministicRandomizer<int> m_dayInstancesRandomizer;
    AlbaUniformNonDeterministicRandomizer<int> m_revisionRandomizer;
    AlbaUniformNonDeterministicRandomizer<int> m_sixtyRandomizer;
};

}  // namespace alba
