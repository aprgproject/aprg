#pragma once

#include <Common/String/AlbaStringHelper.hpp>

#include <filesystem>
#include <string>

namespace alba {

class ReplaceStringInFiles {
public:
    using StringPair = std::pair<std::string, std::string>;
    using StringPairs = std::vector<StringPair>;
    ReplaceStringInFiles() = default;
    [[nodiscard]] static std::string getCPlusPlusStylePrintFromC(std::string const& inputString);

    static void replaceStringWithStringOnDirectories(
        std::filesystem::path const& inputDirectory, std::filesystem::path const& outputDirectory,
        StringPairs const& replacePairs);

    static void replaceStringWithStringOnFile(
        std::filesystem::path const& inputFilePath, std::filesystem::path const& outputFilePath,
        StringPairs const& replacePairs);

    static void replaceCToCPlusPlusStylePrintOnDirectories(
        std::filesystem::path const& inputDirectory, std::filesystem::path const& outputDirectory);

    static void replaceCToCPlusPlusStylePrintOnFile(
        std::filesystem::path const& inputFilePath, std::filesystem::path const& outputFilePath);

private:
    [[nodiscard]] static std::string constructCPlusPlusPrint(
        std::string const& newPrintStream, std::string const& endPrintStream, std::string const& printString,
        stringHelper::strings const& printParameters);

    static void removeStartingAndTrailingWhiteSpaceInPrintParameters(stringHelper::strings& printParameters);
    static void appendCharacterToResult(std::string& result, bool& isOnStringLiteral, char const c);
    static void appendParameterToResult(std::string& result, bool& isOnStringLiteral, std::string const& parameter);
    static std::string getNewPrintStreamBasedFromOldPrintFunction(std::string const& printFunction);
    static bool isCOrCPlusPlusFile(std::string const& extensionString);
    static bool hasPrintInLine(std::string const& line);
    static bool hasEndOfPrintInLine(std::string const& line);
};

}  // namespace alba
