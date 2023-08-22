#pragma once

#include <Common/PathHandler/AlbaPathHandler.hpp>
#include <Common/PathHandler/PathContantsAndTypes.hpp>
#include <Common/Time/AlbaDateTime.hpp>

#include <dirent.h>

#include <functional>
#include <string>

namespace alba {

class AlbaLinuxPathHandler : public AlbaPathHandler {
public:
    explicit AlbaLinuxPathHandler(std::string_view path);
    // no need for virtual destructor because base destructor is virtual (similar to other virtual functions)

    static AlbaLinuxPathHandler createPathHandlerForDetectedPath();

    void clear() override;
    [[nodiscard]] bool isFoundInLocalSystem() const;
    [[nodiscard]] bool isRelativePath() const;
    [[nodiscard]] double getFileSizeEstimate() const;
    [[nodiscard]] AlbaDateTime getFileCreationTime() const;
    void createDirectoriesForNonExisitingDirectories() const;

    bool deleteFile();
    bool deleteDirectoryWithoutFilesAndDirectories();  // do tests
    void deleteFilesInDirectory();                     // do tests
    void deleteInnerFilesAndDirectories();             // do tests
    void deleteDirectoryWithFilesAndDirectories();     // do tests
    bool copyToNewFile(std::string_view newFilePath);
    bool renameFile(std::string_view newFileName);
    bool renameImmediateDirectory(std::string_view newDirectoryName);

    void findFilesAndDirectoriesOneDepth(
        std::string_view wildCardSearch, ListOfPaths& listOfFiles, ListOfPaths& listOfDirectories) const;
    void findFilesAndDirectoriesMultipleDepth(
        std::string_view wildCardSearch, ListOfPaths& listOfFiles, ListOfPaths& listOfDirectories, int depth) const;
    void findFilesAndDirectoriesUnlimitedDepth(
        std::string_view wildCardSearch, ListOfPaths& listOfFiles, ListOfPaths& listOfDirectories) const;

private:
    static std::string getCurrentDetectedPath();
    void save(std::string_view path) override;
    void setPath(std::string_view path);
    void findFilesAndDirectoriesWithDepth(
        std::string_view currentDirectory, std::string_view wildCardSearch, ListOfPaths& listOfFiles,
        ListOfPaths& listOfDirectories, int depth) const;
    void loopAllFilesAndDirectoriesInDirectoryStream(
        DIR* directoryStream, std::string_view currentDirectory, std::string_view wildCardSearch,
        std::set<std::string>& listOfFiles, std::set<std::string>& listOfDirectories, int depth) const;
    [[nodiscard]] bool isPathADirectory(std::string_view fileOrDirectoryName) const;
    static bool canBeLocated(std::string_view fullPath);
    [[nodiscard]] bool isSlashNeededAtTheEnd(std::string_view correctedPath, std::string_view originalPath) const;
    bool m_foundInLocalSystem{false};
    bool m_relativePath{false};
};

}  // namespace alba
