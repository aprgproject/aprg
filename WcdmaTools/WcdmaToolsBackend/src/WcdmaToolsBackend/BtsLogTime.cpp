#include "BtsLogTime.hpp"

#include <Common/Stream/AlbaStreamParameterReader.hpp>
#include <Common/Stream/AlbaStreamParameterWriter.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <iomanip>
#include <sstream>
#include <vector>

using namespace alba;
using namespace alba::stringHelper;
using namespace std;

namespace wcdmaToolsBackend {

BtsLogTime::BtsLogTime(BtsLogTimeType const logTimeType, string const& timeStampString) {
    setTimeByTimeStamp(logTimeType, timeStampString);
}

BtsLogTime BtsLogTime::operator+(BtsLogTime const& btsLogTime2) const {
    BtsLogTime result;
    BtsLogTime const& btsLogTime1(*this);
    result.m_dateTime = btsLogTime1.m_dateTime + btsLogTime2.m_dateTime;
    return result;
}

BtsLogTime BtsLogTime::operator-(BtsLogTime const& btsLogTime2) const {
    BtsLogTime result;
    BtsLogTime const& btsLogTime1(*this);
    result.m_dateTime = btsLogTime1.m_dateTime - btsLogTime2.m_dateTime;
    return result;
}

bool BtsLogTime::operator<(BtsLogTime const& btsLogTimeToCompare) const {
    return m_dateTime < btsLogTimeToCompare.m_dateTime;
}

bool BtsLogTime::operator>(BtsLogTime const& btsLogTimeToCompare) const {
    return m_dateTime > btsLogTimeToCompare.m_dateTime;
}

bool BtsLogTime::operator==(BtsLogTime const& btsLogTimeToCompare) const {
    return m_dateTime == btsLogTimeToCompare.m_dateTime;
}

string BtsLogTime::getPrintableString() const {
    return convertToString(m_dateTime.getPrintObject<AlbaDateTime::PrintFormat::StandardWithSign>());
}

string BtsLogTime::getEquivalentStringPcTimeFormat() const {
    stringstream ss;
    ss << setw(2) << setfill('0') << getDays() << ".";
    ss << setw(2) << setfill('0') << getMonths() << " ";
    ss << setw(2) << setfill('0') << getHours() << ":";
    ss << setw(2) << setfill('0') << getMinutes() << ":";
    ss << setw(2) << setfill('0') << getSeconds() << ".";
    ss << setw(6) << setfill('0') << getMicroSeconds();
    return ss.str();
}

string BtsLogTime::getEquivalentStringBtsTimeFormat() const {
    stringstream ss;
    ss << "<";
    ss << m_dateTime.getPrintObject<AlbaDateTime::PrintFormat::Iso8601>();
    ss << "Z>";
    return ss.str();
}

unsigned int BtsLogTime::getYears() const { return m_dateTime.getYears(); }
unsigned int BtsLogTime::getMonths() const { return m_dateTime.getMonths(); }
unsigned int BtsLogTime::getDays() const { return m_dateTime.getDays(); }
unsigned int BtsLogTime::getHours() const { return m_dateTime.getHours(); }
unsigned int BtsLogTime::getMinutes() const { return m_dateTime.getMinutes(); }
unsigned int BtsLogTime::getSeconds() const { return m_dateTime.getSeconds(); }
unsigned int BtsLogTime::getTotalSeconds() const { return m_dateTime.getHourMinutesSecond().getTotalSeconds(); }
unsigned int BtsLogTime::getMicroSeconds() const { return m_dateTime.getMicroSeconds(); }
bool BtsLogTime::isEmpty() const { return m_dateTime.isEmpty(); }
bool BtsLogTime::isStartup() const { return m_dateTime.getYears() < 2010; }
void BtsLogTime::clear() { m_dateTime.clear(); }

void BtsLogTime::setTimeByTimeStamp(BtsLogTimeType const logTimeType, string const& timeStampString) {
    unsigned int years = 0;
    unsigned int months = 0;
    unsigned int days = 0;
    unsigned int hours = 0;
    unsigned int minutes = 0;
    unsigned int seconds = 0;
    unsigned int microseconds = 0;
    vector<unsigned int> timeValues;
    string timeValueString;

    for (char const character : timeStampString) {
        if (isNumber(character)) {
            timeValueString += character;
        } else if (!timeValueString.empty()) {
            timeValues.push_back(convertStringToNumber<unsigned int>(timeValueString));
            timeValueString.clear();
        }
    }
    if (!timeValueString.empty()) {
        timeValues.push_back(convertStringToNumber<unsigned int>(timeValueString));
    }

    if (BtsLogTimeType::PcTimeStamp == logTimeType) {
        if (6 == timeValues.size()) {
            months = timeValues[1];
            days = timeValues[0];
            hours = timeValues[2];
            minutes = timeValues[3];
            seconds = timeValues[4];
            microseconds = timeValues[5] * 1000;
        }
    } else {
        switch (timeValues.size()) {
            case 6:
                months = timeValues[1];
                days = timeValues[0];
                hours = timeValues[2];
                minutes = timeValues[3];
                seconds = timeValues[4];
                microseconds = timeValues[5];
                break;
            case 7:
                years = timeValues[0];
                months = timeValues[1];
                days = timeValues[2];
                hours = timeValues[3];
                minutes = timeValues[4];
                seconds = timeValues[5];
                microseconds = timeValues[6];
                break;
            default:
                break;
        }
    }
    m_dateTime.setTime(
        static_cast<uint16_t>(years), static_cast<uint8_t>(months), static_cast<uint8_t>(days),
        static_cast<uint8_t>(hours), static_cast<uint8_t>(minutes), static_cast<uint8_t>(seconds),
        static_cast<uint32_t>(microseconds));
}

void BtsLogTime::clearMicroSeconds() { m_dateTime.getMicroSecondsReference() = 0; }

istream& operator>>(istream& in, BtsLogTime& btsLogTime) {
    AlbaStreamParameterReader const reader(in);
    auto years(reader.readData<unsigned int>());
    auto months(reader.readData<unsigned int>());
    auto days(reader.readData<unsigned int>());
    auto hours(reader.readData<unsigned int>());
    auto minutes(reader.readData<unsigned int>());
    auto seconds(reader.readData<unsigned int>());
    auto microseconds(reader.readData<unsigned int>());
    btsLogTime.m_dateTime.setTime(
        static_cast<unsigned short int>(years), static_cast<uint8_t>(months), static_cast<uint8_t>(days),
        static_cast<uint8_t>(hours), static_cast<uint8_t>(minutes), static_cast<uint8_t>(seconds), microseconds);
    return in;
}

ostream& operator<<(ostream& out, BtsLogTime const& btsLogTime) {
    AlbaStreamParameterWriter writer(out);
    writer.writeData<unsigned int>(btsLogTime.getYears());
    writer.writeData<unsigned int>(btsLogTime.getMonths());
    writer.writeData<unsigned int>(btsLogTime.getDays());
    writer.writeData<unsigned int>(btsLogTime.getHours());
    writer.writeData<unsigned int>(btsLogTime.getMinutes());
    writer.writeData<unsigned int>(btsLogTime.getSeconds());
    writer.writeData<unsigned int>(btsLogTime.getMicroSeconds());
    writer.flush();
    return out;
}

}  // namespace wcdmaToolsBackend
