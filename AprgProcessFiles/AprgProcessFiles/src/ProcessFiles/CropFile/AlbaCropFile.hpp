#pragma once

#include <GrepStringEvaluator/AlbaGrepStringEvaluator.hpp>

#include <functional>
#include <optional>
#include <string>

namespace alba {

class AlbaCropFile {
public:
    struct LocationsInFile {
        double startLocation;
        double endLocation;
    };

    using UpdateFunctionWithPercentage = std::function<void(double)>;
    AlbaCropFile(std::string const& prioritizedLineCondition, double const cropSize);

    AlbaCropFile(
        std::string const& prioritizedLineCondition, double const cropSize,
        UpdateFunctionWithPercentage const& updateFunctionAfterOneIteration);

    [[nodiscard]] bool isOutputFileWritten() const;
    void processFile(std::string const& inputFilePath, std::string const& outputFilePath);

private:
    [[nodiscard]] LocationsInFile getLocationsInFile(double const foundLocation, double const fileSize) const;
    double getLocationOfPrioritizedPrint(std::string const& inputFilePath);
    void performCropForFile(
        std::string const& inputFilePath, std::string const& outputFilePath, double const foundLocation);
    void updateAfterOneIteration(double const percentage);
    bool m_isOutputFileWritten;
    double m_cropSize;
    AlbaGrepStringEvaluator m_prioritizedLineEvaluator;
    std::optional<UpdateFunctionWithPercentage> m_updateFunctionAfterOneIterationOptional;
};

}  // namespace alba
