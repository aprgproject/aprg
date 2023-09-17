#pragma once

#include <Common/Time/AlbaDateTime.hpp>

#include <filesystem>
#include <functional>

namespace alba {

class AlbaLocalPathHandlerStd {
public:
    using LocalPath = std::filesystem::path;
    using PathFunction = std::function<void(LocalPath const&)>;
    explicit AlbaLocalPathHandlerStd(LocalPath const& path);
    explicit AlbaLocalPathHandlerStd(LocalPath&& path);
    [[nodiscard]] AlbaDateTime getLastModifiedDateTime() const;
    [[nodiscard]] LocalPath getPath() const;
    [[nodiscard]] LocalPath getRoot() const;
    [[nodiscard]] LocalPath getDirectory() const;
    [[nodiscard]] LocalPath getFile() const;
    [[nodiscard]] LocalPath getFilenameOnly() const;
    [[nodiscard]] LocalPath getExtension() const;
    [[nodiscard]] LocalPath getRelativePathFrom(LocalPath const& source) const;
    [[nodiscard]] LocalPath getRelativePathTo(LocalPath const& destination) const;
    [[nodiscard]] LocalPath getProximatePathFrom(LocalPath const& source) const;
    [[nodiscard]] LocalPath getProximatePathTo(LocalPath const& destination) const;
    [[nodiscard]] uintmax_t getFileSize() const;
    [[nodiscard]] bool doesExist() const;
    [[nodiscard]] bool isExistingDirectory() const;
    [[nodiscard]] bool isExistingFile() const;
    [[nodiscard]] bool isSymbolicLink() const;
    [[nodiscard]] bool isBlockDevice() const;
    [[nodiscard]] bool isCharacterDevice() const;
    [[nodiscard]] bool isNamedPipe() const;
    [[nodiscard]] bool isNamedSocket() const;
    [[nodiscard]] bool isRelativePath() const;
    [[nodiscard]] bool isAbsolutePath() const;
    [[nodiscard]] bool createDirectoriesAndIsSuccessful() const;
    [[nodiscard]] bool deleteDirectoryAndIsSuccessful() const;
    [[nodiscard]] bool deleteAllDirectoryContentsAndIsSuccessful() const;
    [[nodiscard]] bool deleteFileAndIsSuccessful() const;
    [[nodiscard]] bool copyFileToAndIsSuccessful(LocalPath const& destination) const;
    [[nodiscard]] bool copyDirectoryToAndIsSuccessful(LocalPath const& destination) const;
    void findFilesAndDirectoriesOneDepth(PathFunction const& directoryFunction, PathFunction const& fileFunction) const;
    void findFilesAndDirectoriesMultipleDepth(
        int const depth, PathFunction const& directoryFunction, PathFunction const& fileFunction) const;
    void findFilesAndDirectoriesUnlimitedDepth(
        PathFunction const& directoryFunction, PathFunction const& fileFunction) const;
    void clear();
    void input(LocalPath const& path);
    void input(LocalPath&& path);
    bool renameFileAndIsSuccessful(LocalPath const& newFileName);
    bool renameDirectoryAndIsSuccessful(LocalPath const& newDirectoryName);
    [[nodiscard]] static AlbaLocalPathHandlerStd createPathHandlerForDetectedPath();

private:
    [[nodiscard]] static LocalPath fixPath(LocalPath const& path);

    static void findFilesAndDirectories(
        LocalPath const& currentDirectory, int const depth, PathFunction const& directoryFunction,
        PathFunction const& fileFunction);

    LocalPath m_path;
};

}  // namespace alba
