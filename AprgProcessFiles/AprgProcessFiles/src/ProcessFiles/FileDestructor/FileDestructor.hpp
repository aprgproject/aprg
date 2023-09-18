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
    static void renameDirectory(std::filesystem::path const& directoryPath);

private:
    AlbaLocalPathHandler m_pathToDestroy;
};

}  // namespace alba
