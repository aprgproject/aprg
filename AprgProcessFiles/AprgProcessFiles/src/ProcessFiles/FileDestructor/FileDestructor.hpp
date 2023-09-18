#pragma once

#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <filesystem>

namespace alba {

class FileDestructor {
public:
    FileDestructor();
    void destroy() const;
    void destroy(std::filesystem::path const& path) const;
    void renameDirectoriesUnderneath(std::filesystem::path const& directoryPath) const;
    static void destroyFilesAndDirectories(std::filesystem::path const& filePath);
    static void renameDirectory(std::filesystem::path const& directoryPath);
    static void destroyFile(std::filesystem::path const& filePath);

private:
    AlbaLocalPathHandler m_pathToDestroy;
};

}  // namespace alba
