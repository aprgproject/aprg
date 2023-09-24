#pragma once

#include <Common/String/AlbaStringHelper.hpp>

#include <map>

namespace alba {

struct PidSimulatorConfiguration {
    using StringToStringMap = std::map<std::string, std::string>;
    explicit PidSimulatorConfiguration(stringHelper::strings const& argumentsInMain);
    void print() const;
    void saveArgumentValues(StringToStringMap& argumentsToValuesMap);

    static void processArgumentsWithEqualDelimeter(
        StringToStringMap& argumentsToValuesMap, stringHelper::strings const& argumentsInMain);

    static void processOneArgumentWithEqualDelimeter(
        StringToStringMap& argumentsToValuesMap, std::string const& argument);

    unsigned int numberOfLoopsOfPeriodicInputDemand{0};
    unsigned int amplitudeOfInputDemand{0};
    unsigned int numberOfSamplesOfInputDemandInOnePeriod{0};
    int addedOffsetOfInputDemand{0};
    double targetInPidCalculation{0};
    double maxCellTxPower{0};
    double kp{0};
    double ki{0};
    double kd{0};
    std::string inputType;
    std::string machsModelType;
};

}  // namespace alba
