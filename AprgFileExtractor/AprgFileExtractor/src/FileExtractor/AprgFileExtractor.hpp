#pragma once

#include <GrepStringEvaluator/AlbaGrepStringEvaluator.hpp>

#include <set>
#include <string>

namespace alba {

class AprgFileExtractor {
    using SetOfFilePaths = std::set<std::string>;

public:
    explicit AprgFileExtractor(std::string const& condition);
    AprgFileExtractor();
    AprgFileExtractor(
        std::string const& condition, std::string const& pathOf7zExecutable, std::string const& pathOf7zTempFile);
    void copyRelativeFilePathsFromCompressedFile(
        std::string const& filePathOfCompressedFile, SetOfFilePaths& files) const;
    // NOLINTNEXTLINE(modernize-use-nodiscard)
    std::string extractOnceForAllFiles(std::string const& filePathOfCompressedFile) const;
    // NOLINTNEXTLINE(modernize-use-nodiscard)
    std::string extractOneFile(
        std::string const& filePathOfCompressedFile, std::string const& relativePathOfFile) const;
    void extractAllRelevantFiles(std::string const& pathOfFileOrDirectory);
    static bool isRecognizedCompressedFile(std::string const& extension);

private:
    void extractAllRelevantFilesInThisDirectory(std::string const& directoryPath);
    void extractAllRelevantFilesInThisCompressedFile(std::string const& filePathOfCompressedFile);
    void extractAllFilesRecursively(std::string const& filePathOfCompressedFile);
    void extractAllRelevantFilesRecursively(std::string const& filePathOfCompressedFile);
    static void runInConsole(std::string const& command);
    static bool isTheExtensionXzOrGzOrTar(std::string const& extension);
    AlbaGrepStringEvaluator m_grepEvaluator;
    std::string m_pathOf7zExecutable;
    std::string m_pathOf7zTempFile;
    std::string m_nullDevice;
};

}  // namespace alba
