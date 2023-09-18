#pragma once

#include <GrepStringEvaluator/AlbaGrepStringEvaluator.hpp>

#include <filesystem>
#include <functional>
#include <optional>
#include <string>

namespace alba {

class AlbaGrepFile {
public:
    using UpdateFunctionWithPercentage = std::function<void(double)>;
    explicit AlbaGrepFile(std::string const& lineCondition);
    AlbaGrepFile(std::string const& lineCondition, UpdateFunctionWithPercentage const& function);
    [[nodiscard]] bool isOutputFileWritten() const;
    void processFile(std::filesystem::path const& inputFilePath, std::filesystem::path const& outputFilePath);
    AlbaGrepStringEvaluator& getGrepEvaluator();

private:
    void updateAfterOneIteration(double const percentage);
    bool m_isOutputFileWritten;
    AlbaGrepStringEvaluator m_lineGrepEvaluator;
    std::optional<UpdateFunctionWithPercentage> m_updateFunctionAfterOneIterationOptional;
};

}  // namespace alba
