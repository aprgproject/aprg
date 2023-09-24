#include "FileDestructor.hpp"

#include <Common/String/AlbaStringHelper.hpp>

#include <iostream>

using namespace std;
using namespace std::filesystem;

namespace alba {

FileDestructor::FileDestructor() : m_pathToDestroy(AlbaLocalPathHandler::createPathHandlerForDetectedPath()) {}
void FileDestructor::destroy() const { destroy(m_pathToDestroy.getPath()); }

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

void FileDestructor::destroy(path const& destroyPath) {
    cout << "Destroying files in: [" << destroyPath << "]\n";
    AlbaLocalPathHandler const pathHandler(destroyPath);
    if (pathHandler.isExistingDirectory()) {
        pathHandler.deleteAllDirectoryContentsAndIsSuccessful();
    } else {
        pathHandler.deleteFileAndIsSuccessful();
    }
}

}  // namespace alba
