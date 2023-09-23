#pragma once

#include <GrepStringEvaluator/AlbaGrepStringEvaluator.hpp>

#include <filesystem>
#include <set>
#include <string>

namespace alba {

class AprgFileExtractor {
public:
    using SetOfPaths = std::set<std::filesystem::path>;
    explicit AprgFileExtractor(std::string const& condition);
    AprgFileExtractor();

    AprgFileExtractor(
        std::string const& condition, std::filesystem::path const& pathOf7zExecutable,
        std::filesystem::path const& pathOf7zTempFile);

    AprgFileExtractor(
        std::string&& condition, std::filesystem::path&& pathOf7zExecutable, std::filesystem::path&& pathOf7zTempFile);

    void copyRelativeFilePathsFromCompressedFile(
        std::filesystem::path const& filePathOfCompressedFile, SetOfPaths& files) const;
    // NOLINTNEXTLINE(modernize-use-nodiscard)
    std::filesystem::path extractOnceForAllFiles(std::filesystem::path const& filePathOfCompressedFile) const;
    // NOLINTNEXTLINE(modernize-use-nodiscard)
    std::filesystem::path extractOneFile(
        std::filesystem::path const& filePathOfCompressedFile, std::filesystem::path const& relativePathOfFile) const;
    void extractAllRelevantFiles(std::filesystem::path const& pathOfFileOrDirectory);
    static bool isRecognizedCompressedFile(std::string const& extensionString);

private:
    void extractAllRelevantFilesInThisDirectory(std::filesystem::path const& directoryPath);
    void extractAllRelevantFilesInThisCompressedFile(std::filesystem::path const& filePathOfCompressedFile);
    void extractAllFilesRecursively(std::filesystem::path const& filePathOfCompressedFile);
    void extractAllRelevantFilesRecursively(std::filesystem::path const& filePathOfCompressedFile);
    static void runInConsole(std::string const& command);
    static bool isTheExtensionXzOrGzOrTar(std::string const& extensionString);
    AlbaGrepStringEvaluator m_grepEvaluator;
    std::filesystem::path m_pathOf7zExecutable;
    std::filesystem::path m_pathOf7zTempFile;
    std::string m_nullDevice;
};

}  // namespace alba
