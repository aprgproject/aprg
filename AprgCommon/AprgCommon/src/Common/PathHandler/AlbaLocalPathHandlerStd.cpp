#include "AlbaLocalPathHandlerStd.hpp"

#include <Common/Time/AlbaLocalTimeHelper.hpp>

#include <iostream>

using namespace std;
using namespace std::filesystem;

namespace alba {

namespace {
using StringType = path::string_type;
using CharacterType = StringType::value_type;
StringType slashString(1, static_cast<CharacterType>('/'));
StringType backSlashString(1, static_cast<CharacterType>('\\'));
StringType pathSlashString(1, static_cast<CharacterType>(path::preferred_separator));

void replaceAll(StringType& mainText, StringType const& targetStr, StringType const& replacementStr) {
    auto const targetStrLength = targetStr.length();
    auto const replacementStrLength = replacementStr.length();
    auto index = mainText.find(targetStr);
    while (index != std::string::npos) {
        mainText.replace(index, targetStrLength, replacementStr);
        index = mainText.find(targetStr, index + replacementStrLength);
    }
}
}  // namespace

AlbaLocalPathHandlerStd::AlbaLocalPathHandlerStd(LocalPath const& path) : m_path(fixPath(path)) {}
AlbaLocalPathHandlerStd::AlbaLocalPathHandlerStd(LocalPath&& path) : m_path(fixPath(path)) {}
AlbaDateTime AlbaLocalPathHandlerStd::getLastModifiedDateTime() const {
    try {
        if (doesExist()) {
            file_time_type const fileTime = last_write_time(m_path);
            return convertFileTimeToAlbaDateTime(fileTime);
        }
        cerr << "Path does not exist while getting modified date time: [" << m_path << "]\n";
    } catch (exception const& capturedException) {
        cerr << "Error getting file size: [" << capturedException.what() << "]\n";
    }
    return {};
}
AlbaLocalPathHandlerStd::LocalPath AlbaLocalPathHandlerStd::getPath() const { return m_path; }
AlbaLocalPathHandlerStd::LocalPath AlbaLocalPathHandlerStd::getRoot() const { return m_path.root_name(); }

AlbaLocalPathHandlerStd::LocalPath AlbaLocalPathHandlerStd::getDirectory() const {
    if (m_path.has_filename()) {
        return (m_path.parent_path() / "");
    }
    return m_path;
}

AlbaLocalPathHandlerStd::LocalPath AlbaLocalPathHandlerStd::getFile() const { return m_path.filename(); }
AlbaLocalPathHandlerStd::LocalPath AlbaLocalPathHandlerStd::getFilenameOnly() const { return m_path.stem(); }

AlbaLocalPathHandlerStd::LocalPath AlbaLocalPathHandlerStd::getExtension() const {
    auto const& extension(m_path.extension());
    if (!extension.empty()) {
        auto const& extensionInNative(extension.native());
        if (!extensionInNative.empty() && extensionInNative[0] == static_cast<decltype(extensionInNative[0])>('.')) {
            return {cbegin(extensionInNative) + 1, cend(extensionInNative)};
        }
    }
    return extension;
}

uintmax_t AlbaLocalPathHandlerStd::getFileSize() const {
    try {
        if (isExistingFile()) {
            return file_size(m_path);
        }
        cerr << "File does not exist while getting file size: [" << m_path << "]\n";
    } catch (exception const& capturedException) {
        cerr << "Error getting file size: [" << capturedException.what() << "]\n";
    }
    return {};
}

bool AlbaLocalPathHandlerStd::doesExist() const { return exists(m_path); }
bool AlbaLocalPathHandlerStd::isExistingDirectory() const { return is_directory(m_path); }
bool AlbaLocalPathHandlerStd::isExistingFile() const { return is_regular_file(m_path); }
bool AlbaLocalPathHandlerStd::isSymbolicLink() const { return is_symlink(m_path); }
bool AlbaLocalPathHandlerStd::isBlockDevice() const { return is_block_file(m_path); }
bool AlbaLocalPathHandlerStd::isCharacterDevice() const { return is_character_file(m_path); }
bool AlbaLocalPathHandlerStd::isNamedPipe() const { return is_fifo(m_path); }
bool AlbaLocalPathHandlerStd::isNamedSocket() const { return is_socket(m_path); }
bool AlbaLocalPathHandlerStd::isRelativePath() const { return m_path.is_relative(); }
bool AlbaLocalPathHandlerStd::isAbsolutePath() const { return m_path.is_absolute(); }

void AlbaLocalPathHandlerStd::findFilesAndDirectoriesOneDepth(
    PathFunction const& directoryFunction, PathFunction const& fileFunction) const {
    // NOLINTNEXTLINE(readability-suspicious-call-argument)
    findFilesAndDirectories(m_path, 1, directoryFunction, fileFunction);
}

void AlbaLocalPathHandlerStd::findFilesAndDirectoriesMultipleDepth(
    int const depth, PathFunction const& directoryFunction, PathFunction const& fileFunction) const {
    // NOLINTNEXTLINE(readability-suspicious-call-argument)
    findFilesAndDirectories(m_path, depth, directoryFunction, fileFunction);
}

void AlbaLocalPathHandlerStd::findFilesAndDirectoriesUnlimitedDepth(
    PathFunction const& directoryFunction, PathFunction const& fileFunction) const {
    for (directory_entry const& directoryEntry : recursive_directory_iterator(m_path)) {
        if (directoryEntry.is_directory()) {
            directoryFunction(directoryEntry.path() / "");
        } else {
            fileFunction(directoryEntry.path());
        }
    }
}

void AlbaLocalPathHandlerStd::clear() { m_path.clear(); }
void AlbaLocalPathHandlerStd::input(LocalPath const& path) { m_path = fixPath(path); }
void AlbaLocalPathHandlerStd::input(LocalPath&& path) { m_path = fixPath(path); }

bool AlbaLocalPathHandlerStd::createDirectoriesAndIsSuccessful() const {
    try {
        create_directories(m_path);
    } catch (exception const& capturedException) {
        cerr << "Error while creating directories: [" << capturedException.what() << "]\n";
        return false;
    }
    return true;
}

bool AlbaLocalPathHandlerStd::deleteDirectoryAndIsSuccessful() const {
    try {
        remove_all(m_path.parent_path());
    } catch (exception const& capturedException) {
        cerr << "Error deleting directory: [" << capturedException.what() << "]\n";
        return false;
    }
    return true;
}

bool AlbaLocalPathHandlerStd::deleteAllDirectoryContentsAndIsSuccessful() const {
    try {
        for (directory_entry const& directoryEntry : directory_iterator(m_path.parent_path())) {
            if (directoryEntry.is_directory()) {
                remove_all(directoryEntry.path());
            } else {
                remove(directoryEntry.path());
            }
        }
    } catch (exception const& capturedException) {
        cerr << "Error deleting directory: [" << capturedException.what() << "]\n";
        return false;
    }
    return true;
}

bool AlbaLocalPathHandlerStd::deleteFileAndIsSuccessful() {
    try {
        if (!isExistingFile()) {
            cerr << "File does not exist during deletion: [" << m_path << "]\n";
            return false;
        }
        remove(m_path);
    } catch (exception const& capturedException) {
        cerr << "Error deleting file: [" << capturedException.what() << "]\n";
        return false;
    }
    return true;
}

bool AlbaLocalPathHandlerStd::copyFileToAndIsSuccessful(LocalPath const& destination) {
    try {
        if (!isExistingFile()) {
            cerr << "File does not exist during copy: [" << m_path << "]\n";
            return false;
        }
        copy_file(m_path, destination);
    } catch (exception const& capturedException) {
        cerr << "Error copying file: [" << capturedException.what() << "]\n";
        return false;
    }
    return true;
}

bool AlbaLocalPathHandlerStd::renameFileAndIsSuccessful(LocalPath const& newFileName) {
    try {
        if (!isExistingFile()) {
            cerr << "File does not exist during rename: [" << m_path << "]\n";
            return false;
        }
        LocalPath const newPath(m_path.parent_path() / newFileName);
        rename(m_path, newPath);
        input(newPath);
    } catch (exception const& capturedException) {
        cerr << "Error renaming file: [" << capturedException.what() << "]\n";
        return false;
    }
    return true;
}

bool AlbaLocalPathHandlerStd::renameDirectoryAndIsSuccessful(LocalPath const& newDirectoryName) {
    try {
        if (!isExistingDirectory()) {
            cerr << "Directory does not exist during rename: [" << m_path << "]\n";
            return false;
        }
        LocalPath const newPath(m_path.parent_path().parent_path() / newDirectoryName);
        rename(m_path, newPath);
        input(newPath);
    } catch (exception const& capturedException) {
        cerr << "Error renaming directory: [" << capturedException.what() << "]\n";
        return false;
    }
    return true;
}

AlbaLocalPathHandlerStd AlbaLocalPathHandlerStd::createPathHandlerForDetectedPath() {
    return AlbaLocalPathHandlerStd{current_path()};
}

AlbaLocalPathHandlerStd::LocalPath AlbaLocalPathHandlerStd::fixPath(LocalPath const& path) {
    auto pathString(path.native());
    replaceAll(pathString, slashString, pathSlashString);
    replaceAll(pathString, backSlashString, pathSlashString);
    LocalPath const replacedStringPath(pathString);
    LocalPath fixedPath(replacedStringPath.root_path());
    bool isLastASlash(false);
    for (LocalPath const& subPath : replacedStringPath) {
        if (subPath.has_filename()) {
            fixedPath /= subPath;
            isLastASlash = false;
        } else {
            isLastASlash = true;
        }
    }
    fixedPath.make_preferred();
    fixedPath = fixedPath.lexically_normal();
    if (isLastASlash || (path.has_filename() && is_directory(fixedPath))) {
        fixedPath /= "";
    }
    return fixedPath;
}

void AlbaLocalPathHandlerStd::findFilesAndDirectories(
    LocalPath const& currentDirectory, int const depth, PathFunction const& directoryFunction,
    PathFunction const& fileFunction) {
    if (depth == 0) {
        return;
    }
    for (directory_entry const& directoryEntry : directory_iterator(currentDirectory)) {
        if (directoryEntry.is_directory()) {
            directoryFunction(directoryEntry.path() / "");
            findFilesAndDirectories(directoryEntry.path(), depth - 1, directoryFunction, fileFunction);
        } else {
            fileFunction(directoryEntry.path());
        }
    }
}

}  // namespace alba
