#pragma once

#include <Common/PathHandler/AlbaPathHandler.hpp>
#include <Common/PathHandler/PathContantsAndTypes.hpp>
#include <Common/Time/AlbaDateTime.hpp>

#include <functional>
#include <string>

namespace alba {

class AlbaWindowsPathHandler : public AlbaPathHandler {
public:
    explicit AlbaWindowsPathHandler(std::string_view const path);
    void clear() override;
    [[nodiscard]] std::string getDriveOrRoot() const;
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
    AlbaDateTime getFileCreationTime();
    double getFileSizeEstimate();
    bool deleteFile();
    bool deleteDirectoryWithoutFilesAndDirectories();  // do tests
    bool copyToNewFile(std::string_view const newFilePath);
    bool renameFile(std::string_view const newFileName);
    bool renameImmediateDirectory(std::string_view const newDirectoryName);
    // no need for virtual destructor because base destructor is virtual (similar to other virtual functions)
    static AlbaWindowsPathHandler createPathHandlerForDetectedPath();

private:
    void save(std::string_view const path) override;

    [[nodiscard]] bool isSlashNeededAtTheEnd(
        std::string_view const correctedPath, std::string_view const originalPath) const;

    void findFilesAndDirectoriesWithDepth(
        std::string_view const currentDirectory, std::string_view const wildCardSearch, ListOfPaths& listOfFiles,
        ListOfPaths& listOfDirectories, int const depth) const;

    void setPath(std::string_view const path);
    void setDriveOrRoot();
    [[nodiscard]] static bool canBeLocated(std::string_view const fullPath);
    static std::string getCurrentDetectedPath();
    std::string m_driveOrRoot;
    bool m_foundInLocalSystem{};
    bool m_relativePath{};
};

}  // namespace alba
