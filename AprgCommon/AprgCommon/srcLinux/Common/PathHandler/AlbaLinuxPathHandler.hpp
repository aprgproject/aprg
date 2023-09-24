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
    explicit AlbaLinuxPathHandler(std::string_view const path);
    void clear() override;
    [[nodiscard]] AlbaDateTime getFileCreationTime() const;
    [[nodiscard]] double getFileSizeEstimate() const;
    [[nodiscard]] bool doesExist() const;
    [[nodiscard]] bool isRelativePath() const;
    void createDirectoriesForNonExisitingDirectories() const;

    void findFilesAndDirectoriesOneDepth(
        std::string_view const wildCardSearch, ListOfPaths& listOfFiles, ListOfPaths& listOfDirectories) const;

    void findFilesAndDirectoriesMultipleDepth(
        std::string_view const wildCardSearch, ListOfPaths& listOfFiles, ListOfPaths& listOfDirectories,
        int const depth) const;

    void findFilesAndDirectoriesUnlimitedDepth(
        std::string_view const wildCardSearch, ListOfPaths& listOfFiles, ListOfPaths& listOfDirectories) const;

    void deleteFilesInDirectory();                  // do tests
    void deleteInnerFilesAndDirectories();          // do tests
    void deleteDirectoryWithFilesAndDirectories();  // do tests
    bool deleteFile();
    bool deleteDirectoryWithoutFilesAndDirectories();  // do tests
    bool copyToNewFile(std::string_view const newFilePath);
    bool renameFile(std::string_view const newFileName);
    bool renameImmediateDirectory(std::string_view const newDirectoryName);
    // no need for virtual destructor because base destructor is virtual (similar to other virtual functions)
    static AlbaLinuxPathHandler createPathHandlerForDetectedPath();

private:
    void save(std::string_view const path) override;
    [[nodiscard]] bool isPathADirectory(std::string_view const fileOrDirectoryName) const;

    [[nodiscard]] bool isSlashNeededAtTheEnd(
        std::string_view const correctedPath, std::string_view const originalPath) const;

    void findFilesAndDirectoriesWithDepth(
        std::string_view const currentDirectory, std::string_view const wildCardSearch, ListOfPaths& listOfFiles,
        ListOfPaths& listOfDirectories, int const depth) const;

    void loopAllFilesAndDirectoriesInDirectoryStream(
        DIR* directoryStream, std::string_view const currentDirectory, std::string_view const wildCardSearch,
        std::set<std::string>& listOfFiles, std::set<std::string>& listOfDirectories, int const depth) const;

    void setPath(std::string_view const path);
    static std::string getCurrentDetectedPath();
    static bool canBeLocated(std::string_view const fullPath);
    bool m_foundInLocalSystem{false};
    bool m_relativePath{false};
};

}  // namespace alba
