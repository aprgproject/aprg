#pragma once

#include <Common/Time/AlbaDateTime.hpp>

#include <string>

namespace wcdmaToolsBackend {

enum class BtsLogTimeType { BtsTimeStamp, PcTimeStamp };

class BtsLogTime {
public:
    BtsLogTime();
    BtsLogTime(BtsLogTimeType logTimeType, std::string const& timeStampString);
    void clear();
    void setTimeByTimeStamp(BtsLogTimeType logTimeType, std::string const& timeStampString);
    [[nodiscard]] bool isEmpty() const;
    [[nodiscard]] bool isStartup() const;
    [[nodiscard]] unsigned int getYears() const;
    [[nodiscard]] unsigned int getMonths() const;
    [[nodiscard]] unsigned int getDays() const;
    [[nodiscard]] unsigned int getHours() const;
    [[nodiscard]] unsigned int getMinutes() const;
    [[nodiscard]] unsigned int getSeconds() const;
    [[nodiscard]] unsigned int getTotalSeconds() const;
    [[nodiscard]] unsigned int getMicroSeconds() const;
    void clearMicroSeconds();
    [[nodiscard]] std::string getPrintableString() const;
    [[nodiscard]] std::string getEquivalentStringPcTimeFormat() const;
    [[nodiscard]] std::string getEquivalentStringBtsTimeFormat() const;
    bool operator<(BtsLogTime const& btsLogTimeToCompare) const;
    bool operator>(BtsLogTime const& btsLogTimeToCompare) const;
    bool operator==(BtsLogTime const& btsLogTimeToCompare) const;
    BtsLogTime operator+(BtsLogTime const& btsLogTime) const;
    BtsLogTime operator-(BtsLogTime const& btsLogTime) const;
    friend std::ostream& operator<<(std::ostream& out, BtsLogTime const& btsLogTime);
    friend std::istream& operator>>(std::istream& in, BtsLogTime& btsLogTime);

private:
    alba::AlbaDateTime m_dateTime;
};

}  // namespace wcdmaToolsBackend
