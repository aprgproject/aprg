#pragma once

#include <GrepStringEvaluator/AlbaGrepStringEvaluator.hpp>

#include <filesystem>
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
    void processFile(std::filesystem::path const& inputFilePath, std::filesystem::path const& outputFilePath);

private:
    [[nodiscard]] LocationsInFile getLocationsInFile(double const foundLocation, double const fileSize) const;
    void performCropForFile(
        std::filesystem::path const& inputFilePath, std::filesystem::path const& outputFilePath,
        double const foundLocation);
    void updateAfterOneIteration(double const percentage);
    double getLocationOfPrioritizedPrint(std::filesystem::path const& inputFilePath);
    bool m_isOutputFileWritten;
    double m_cropSize;
    AlbaGrepStringEvaluator m_prioritizedLineEvaluator;
    std::optional<UpdateFunctionWithPercentage> m_updateFunctionAfterOneIterationOptional;
};

}  // namespace alba
