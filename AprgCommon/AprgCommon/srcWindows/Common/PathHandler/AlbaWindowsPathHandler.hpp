#pragma once

#include <Common/PathHandler/AlbaPathHandler.hpp>
#include <Common/PathHandler/PathContantsAndTypes.hpp>
#include <Common/Time/AlbaDateTime.hpp>

#include <functional>
#include <string>

namespace alba {

class AlbaWindowsPathHandler : public AlbaPathHandler {
public:
    AlbaWindowsPathHandler(std::string_view const path);
    // no need for virtual destructor because base destructor is virtual (similar to other virtual functions)
    static AlbaWindowsPathHandler createPathHandlerForDetectedPath();
    bool isFoundInLocalSystem() const;
    bool isRelativePath() const;
    std::string getDriveOrRoot() const;
    void createDirectoriesForNonExisitingDirectories() const;
    void findFilesAndDirectoriesOneDepth(
        std::string_view const wildCardSearch, ListOfPaths& listOfFiles, ListOfPaths& listOfDirectories) const;

    void findFilesAndDirectoriesMultipleDepth(
        std::string_view const wildCardSearch, ListOfPaths& listOfFiles, ListOfPaths& listOfDirectories,
        int const depth) const;

    void findFilesAndDirectoriesUnlimitedDepth(
        std::string_view const wildCardSearch, ListOfPaths& listOfFiles, ListOfPaths& listOfDirectories) const;
    bool deleteFile();
    bool deleteDirectoryWithoutFilesAndDirectories();  // do tests
    bool copyToNewFile(std::string_view const newFilePath);
    bool renameFile(std::string_view const newFileName);
    bool renameImmediateDirectory(std::string_view const newDirectoryName);
    double getFileSizeEstimate();
    AlbaDateTime getFileCreationTime();
    void clear() override;
    void deleteFilesInDirectory();                  // do tests
    void deleteInnerFilesAndDirectories();          // do tests
    void deleteDirectoryWithFilesAndDirectories();  // do tests
private:
    static std::string getCurrentDetectedPath();
    bool canBeLocated(std::string_view const fullPath) const;
    bool isSlashNeededAtTheEnd(std::string_view const correctedPath, std::string_view const originalPath) const;

    void findFilesAndDirectoriesWithDepth(
        std::string_view const currentDirectory, std::string_view const wildCardSearch, ListOfPaths& listOfFiles,
        ListOfPaths& listOfDirectories, int const depth) const;

    void save(std::string_view const path) override;
    void setPath(std::string_view const path);
    void setDriveOrRoot();
    std::string m_driveOrRoot;
    bool m_foundInLocalSystem;
    bool m_relativePath;
};

}  // namespace alba
