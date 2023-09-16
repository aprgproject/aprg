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
    [[nodiscard]] LocalPath getPath() const;
    [[nodiscard]] LocalPath getRoot() const;
    [[nodiscard]] LocalPath getDirectory() const;
    [[nodiscard]] LocalPath getFile() const;
    [[nodiscard]] LocalPath getFilenameOnly() const;
    [[nodiscard]] LocalPath getExtension() const;
    [[nodiscard]] AlbaDateTime getFileCreationTime() const;
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
    void input(LocalPath const& path);
    void input(LocalPath&& path);
    bool createDirectoriesAndIsSuccessful();           // do tests
    bool deleteDirectoryAndIsSuccessful();             // do tests
    bool deleteAllDirectoryContentsAndIsSuccessful();  // do tests
    bool deleteFileAndIsSuccessful();
    bool copyFileToAndIsSuccessful(LocalPath const& destination);
    bool renameFileAndIsSuccessful(LocalPath const& newFileName);
    bool renameDirectoryAndIsSuccessful(LocalPath const& newDirectoryName);
    void findFilesAndDirectoriesOneDepth(PathFunction const& directoryFunction, PathFunction const& fileFunction) const;
    void findFilesAndDirectoriesMultipleDepth(
        int const depth, PathFunction const& directoryFunction, PathFunction const& fileFunction) const;
    void findFilesAndDirectoriesUnlimitedDepth(
        PathFunction const& directoryFunction, PathFunction const& fileFunction) const;
    [[nodiscard]] static AlbaLocalPathHandlerStd createPathHandlerForDetectedPath();

private:
    static void findFilesAndDirectories(
        LocalPath const& currentDirectory, int const depth, PathFunction const& directoryFunction,
        PathFunction const& fileFunction);
    [[nodiscard]] static LocalPath fixPath(LocalPath const& path);
    LocalPath m_path;
};

}  // namespace alba
