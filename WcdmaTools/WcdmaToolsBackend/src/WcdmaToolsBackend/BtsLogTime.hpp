#pragma once

#include <Common/Time/AlbaDateTime.hpp>

#include <string>

namespace wcdmaToolsBackend {

enum class BtsLogTimeType { BtsTimeStamp, PcTimeStamp };

class BtsLogTime {
public:
    BtsLogTime() = default;
    BtsLogTime(BtsLogTimeType const logTimeType, std::string const& timeStampString);
    BtsLogTime operator+(BtsLogTime const& btsLogTime) const;
    BtsLogTime operator-(BtsLogTime const& btsLogTime) const;
    bool operator<(BtsLogTime const& btsLogTimeToCompare) const;
    bool operator>(BtsLogTime const& btsLogTimeToCompare) const;
    bool operator==(BtsLogTime const& btsLogTimeToCompare) const;
    [[nodiscard]] std::string getPrintableString() const;
    [[nodiscard]] std::string getEquivalentStringPcTimeFormat() const;
    [[nodiscard]] std::string getEquivalentStringBtsTimeFormat() const;
    [[nodiscard]] unsigned int getYears() const;
    [[nodiscard]] unsigned int getMonths() const;
    [[nodiscard]] unsigned int getDays() const;
    [[nodiscard]] unsigned int getHours() const;
    [[nodiscard]] unsigned int getMinutes() const;
    [[nodiscard]] unsigned int getSeconds() const;
    [[nodiscard]] unsigned int getTotalSeconds() const;
    [[nodiscard]] unsigned int getMicroSeconds() const;
    [[nodiscard]] bool isEmpty() const;
    [[nodiscard]] bool isStartup() const;
    void clear();
    void setTimeByTimeStamp(BtsLogTimeType const logTimeType, std::string const& timeStampString);
    void clearMicroSeconds();
    friend std::istream& operator>>(std::istream& in, BtsLogTime& btsLogTime);
    friend std::ostream& operator<<(std::ostream& out, BtsLogTime const& btsLogTime);

private:
    alba::AlbaDateTime m_dateTime;
};

}  // namespace wcdmaToolsBackend
