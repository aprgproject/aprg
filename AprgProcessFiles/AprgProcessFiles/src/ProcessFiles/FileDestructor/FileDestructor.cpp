#include "FileDestructor.hpp"

#include <Common/String/AlbaStringHelper.hpp>

#include <iostream>

using namespace std;
using namespace std::filesystem;

namespace alba {

FileDestructor::FileDestructor() : m_pathToDestroy(AlbaLocalPathHandler::createPathHandlerForDetectedPath()) {}
void FileDestructor::destroy() const { destroy(m_pathToDestroy.getPath()); }

void FileDestructor::destroy(path const& destroyPath) const {
    renameDirectoriesUnderneath(destroyPath);
    destroyFilesAndDirectories(destroyPath);
}

void FileDestructor::renameDirectoriesUnderneath(path const& directoryPath) const {
    AlbaLocalPathHandler const pathHandler(directoryPath);
    pathHandler.findFilesAndDirectoriesOneDepth(
        [&](AlbaLocalPathHandler::LocalPath const& directory) { renameDirectory(directory); },
        [](AlbaLocalPathHandler::LocalPath const&) {});
    pathHandler.findFilesAndDirectoriesOneDepth(
        [&](AlbaLocalPathHandler::LocalPath const& directory) { renameDirectoriesUnderneath(directory); },
        [](AlbaLocalPathHandler::LocalPath const&) {});
}

void FileDestructor::destroyFilesAndDirectories(path const& destroyPath) {
    cout << "Destroying files in: [" << destroyPath << "]\n";
    AlbaLocalPathHandler const pathHandler(destroyPath);
    if (pathHandler.isExistingDirectory()) {
        pathHandler.deleteDirectoryAndIsSuccessful();
    } else {
        pathHandler.deleteFileAndIsSuccessful();
    }
}

void FileDestructor::renameDirectory(path const& directoryPath) {
    cout << "Renaming directory: [" << directoryPath << "]\n";
    AlbaLocalPathHandler directoryPathHandler(directoryPath);
    unsigned int retries = 10;
    bool isNotSuccessful = true;
    while (retries > 0 && isNotSuccessful) {
        isNotSuccessful =
            !directoryPathHandler.renameDirectoryAndIsSuccessful(stringHelper::getRandomAlphaNumericString(10));
        if (!isNotSuccessful) {
            cout << "Renamed directory: [" << directoryPathHandler.getPath() << "]\n";
        }
        --retries;
    }
}

void FileDestructor::destroyFile(path const& filePath) {
    constexpr unsigned int MAX_CHARACTERS_ON_PATH = 100;
    cout << "Destroying File: [" << filePath << "]\n";
    AlbaLocalPathHandler filePathHandler(filePath);
    unsigned int retries = 10;
    bool isNotSuccessful = true;
    while (retries > 0 && isNotSuccessful) {
        if (filePathHandler.getPath().string().length() > MAX_CHARACTERS_ON_PATH) {
            isNotSuccessful = !filePathHandler.renameFileAndIsSuccessful(stringHelper::getRandomAlphaNumericString(10));
            if (!isNotSuccessful) {
                cout << "Renamed File: [" << filePathHandler.getPath() << "]\n";
            }
        }
        isNotSuccessful = !filePathHandler.deleteFileAndIsSuccessful();
        if (!isNotSuccessful) {
            cout << "Destroyed File: [" << filePathHandler.getPath() << "]\n";
        }
        --retries;
    }
}

}  // namespace alba
