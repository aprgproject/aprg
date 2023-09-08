#pragma once

#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

namespace alba {

class FileDestructor {
public:
    FileDestructor();
    static void destroyFilesAndDirectories(std::string const& filePath);
    static void renameDirectory(std::string const& directoryPath);
    static void destroyFile(std::string const& filePath);
    void destroy() const;
    void destroy(std::string const& path) const;
    void renameDirectoriesUnderneath(std::string const& directoryPath) const;

private:
    AlbaLocalPathHandler m_pathToDestroy;
};

}  // namespace alba
