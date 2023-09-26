#include "AlbaLocalPathHandler.hpp"

#include <Common/Time/AlbaLocalTimeHelper.hpp>

#include <iostream>

using namespace std;
using namespace std::filesystem;

namespace alba {

namespace {

using StringType = path::string_type;
using CharacterType = StringType::value_type;
constexpr CharacterType SLASH_STRING = static_cast<CharacterType>('/');
constexpr CharacterType BACK_SLASH_STRING = static_cast<CharacterType>('\\');
constexpr CharacterType PREFERRED_SLASH_STRING = static_cast<CharacterType>(path::preferred_separator);

void replaceAllSlashes(StringType& mainText, CharacterType const& targetSlash, CharacterType const& replacementSlash) {
    replace(mainText.begin(), mainText.end(), targetSlash, replacementSlash);
}

}  // namespace

AlbaLocalPathHandler::AlbaLocalPathHandler(LocalPath const& path) : m_path(fixPath(path)) {}
AlbaLocalPathHandler::AlbaLocalPathHandler(LocalPath&& path) : m_path(fixPath(path)) {}

AlbaDateTime AlbaLocalPathHandler::getLastModifiedDateTime() const {
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

AlbaLocalPathHandler::LocalPath AlbaLocalPathHandler::getPath() const { return m_path; }
AlbaLocalPathHandler::LocalPath AlbaLocalPathHandler::getRoot() const { return m_path.root_name(); }

AlbaLocalPathHandler::LocalPath AlbaLocalPathHandler::getDirectory() const {
    if (m_path.has_filename()) {
        return (m_path.parent_path() / "");
    }
    return m_path;
}

AlbaLocalPathHandler::LocalPath AlbaLocalPathHandler::getDirectoryName() const {
    return m_path.parent_path().filename();
}

AlbaLocalPathHandler::LocalPath AlbaLocalPathHandler::getFile() const { return m_path.filename(); }
AlbaLocalPathHandler::LocalPath AlbaLocalPathHandler::getFilenameOnly() const { return m_path.stem(); }

AlbaLocalPathHandler::LocalPath AlbaLocalPathHandler::getExtension() const {
    auto const& extension(m_path.extension());
    if (!extension.empty()) {
        auto const& extensionInNative(extension.native());
        if (!extensionInNative.empty() && extensionInNative[0] == static_cast<decltype(extensionInNative[0])>('.')) {
            return {cbegin(extensionInNative) + 1, cend(extensionInNative)};
        }
    }
    return extension;
}

// "relative" is a function that computes the relative path from one path to another.
// It takes two path arguments, the first being the "from" path and the second being the "to" path.
// It then computes the relative path from the "from" path to the "to" path.
AlbaLocalPathHandler::LocalPath AlbaLocalPathHandler::getRelativePathFrom(LocalPath const& source) const {
    return relative(m_path, source);
}

AlbaLocalPathHandler::LocalPath AlbaLocalPathHandler::getRelativePathTo(LocalPath const& destination) const {
    return relative(destination, m_path);
}

// "proximate" is a convenience function that computes the shortest relative path between two paths.
// It takes two path arguments, similar to "relative", and returns the shortest relative path between those two paths.
AlbaLocalPathHandler::LocalPath AlbaLocalPathHandler::getProximatePathFrom(LocalPath const& source) const {
    return proximate(m_path, source);
}

AlbaLocalPathHandler::LocalPath AlbaLocalPathHandler::getProximatePathTo(LocalPath const& destination) const {
    return proximate(destination, m_path);
}

uintmax_t AlbaLocalPathHandler::getFileSize() const {
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

bool AlbaLocalPathHandler::isEmpty() const { return m_path.empty(); }
bool AlbaLocalPathHandler::doesExist() const { return exists(m_path); }
bool AlbaLocalPathHandler::isExistingDirectory() const { return is_directory(m_path); }
bool AlbaLocalPathHandler::isExistingFile() const { return is_regular_file(m_path); }
bool AlbaLocalPathHandler::isSymbolicLink() const { return is_symlink(m_path); }
bool AlbaLocalPathHandler::isBlockDevice() const { return is_block_file(m_path); }
bool AlbaLocalPathHandler::isCharacterDevice() const { return is_character_file(m_path); }
bool AlbaLocalPathHandler::isNamedPipe() const { return is_fifo(m_path); }
bool AlbaLocalPathHandler::isNamedSocket() const { return is_socket(m_path); }
bool AlbaLocalPathHandler::isRelativePath() const { return m_path.is_relative(); }
bool AlbaLocalPathHandler::isAbsolutePath() const { return m_path.is_absolute(); }

void AlbaLocalPathHandler::findFilesAndDirectoriesOneDepth(
    PathFunction const& directoryFunction, PathFunction const& fileFunction) const {
    try {
        // NOLINTNEXTLINE(readability-suspicious-call-argument)
        findFilesAndDirectories(m_path, 1, directoryFunction, fileFunction);
    } catch (exception const& capturedException) {
        cerr << "Error while finding files and directories: [" << capturedException.what() << "]\n";
    }
}

void AlbaLocalPathHandler::findFilesAndDirectoriesMultipleDepth(
    int const depth, PathFunction const& directoryFunction, PathFunction const& fileFunction) const {
    try {
        // NOLINTNEXTLINE(readability-suspicious-call-argument)
        findFilesAndDirectories(m_path, depth, directoryFunction, fileFunction);
    } catch (exception const& capturedException) {
        cerr << "Error while finding files and directories: [" << capturedException.what() << "]\n";
    }
}

void AlbaLocalPathHandler::findFilesAndDirectoriesUnlimitedDepth(
    PathFunction const& directoryFunction, PathFunction const& fileFunction) const {
    try {
        for (directory_entry const& directoryEntry : recursive_directory_iterator(m_path)) {
            if (directoryEntry.is_directory()) {
                directoryFunction(directoryEntry.path() / "");
            } else {
                fileFunction(directoryEntry.path());
            }
        }
    } catch (exception const& capturedException) {
        cerr << "Error while finding files and directories: [" << capturedException.what() << "]\n";
    }
}

bool AlbaLocalPathHandler::createDirectoriesAndIsSuccessful() const {
    try {
        create_directories(m_path.parent_path());
    } catch (exception const& capturedException) {
        cerr << "Error while creating directories: [" << capturedException.what() << "]\n";
        return false;
    }
    return true;
}

bool AlbaLocalPathHandler::deleteDirectoryAndIsSuccessful() const {
    try {
        remove_all(m_path.parent_path());
    } catch (exception const& capturedException) {
        cerr << "Error deleting directory: [" << capturedException.what() << "]\n";
        return false;
    }
    return true;
}

bool AlbaLocalPathHandler::deleteAllDirectoryContentsAndIsSuccessful() const {
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

bool AlbaLocalPathHandler::deleteFileAndIsSuccessful() const {
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

bool AlbaLocalPathHandler::copyFileToAndIsSuccessful(LocalPath const& destination) const {
    try {
        if (!isExistingFile()) {
            cerr << "File does not exist during copy: [" << m_path << "]\n";
            return false;
        }
#ifdef OS_WINDOWS
        remove(destination);  // overwrite does not work on windows
#endif
        copy_file(m_path, destination, copy_options::overwrite_existing);
    } catch (exception const& capturedException) {
        cerr << "Error copying file: [" << capturedException.what() << "]\n";
        return false;
    }
    return true;
}

bool AlbaLocalPathHandler::copyDirectoryToAndIsSuccessful(LocalPath const& destination) const {
    try {
        if (!isExistingDirectory()) {
            cerr << "Directory does not exist during copy: [" << m_path << "]\n";
            return false;
        }
        for (directory_entry const& directoryEntry : recursive_directory_iterator(m_path)) {
            LocalPath const destinationEntry = destination / relative(directoryEntry, m_path);
            if (directoryEntry.is_directory()) {
                create_directories(destinationEntry);
            } else {
#ifdef OS_WINDOWS
                remove(destinationEntry);  // overwrite does not work on windows
#endif
                copy_file(directoryEntry, destinationEntry, copy_options::overwrite_existing);
            }
        }
    } catch (exception const& capturedException) {
        cerr << "Error copying directory: [" << capturedException.what() << "]\n";
        return false;
    }
    return true;
}

void AlbaLocalPathHandler::clear() { m_path.clear(); }
void AlbaLocalPathHandler::input(LocalPath const& path) { m_path = fixPath(path); }
void AlbaLocalPathHandler::input(LocalPath&& path) { m_path = fixPath(path); }
void AlbaLocalPathHandler::moveUpADirectory() { input(m_path.parent_path().parent_path() / ""); }

bool AlbaLocalPathHandler::renameFileAndIsSuccessful(LocalPath const& newFileName) {
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

bool AlbaLocalPathHandler::renameDirectoryAndIsSuccessful(LocalPath const& newDirectoryName) {
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

AlbaLocalPathHandler AlbaLocalPathHandler::createPathHandlerForDetectedPath() {
    return AlbaLocalPathHandler{current_path()};
}

AlbaLocalPathHandler::LocalPath AlbaLocalPathHandler::fixPath(LocalPath const& path) {
    auto pathString(path.native());
    replaceAllSlashes(pathString, SLASH_STRING, PREFERRED_SLASH_STRING);
    replaceAllSlashes(pathString, BACK_SLASH_STRING, PREFERRED_SLASH_STRING);
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

void AlbaLocalPathHandler::findFilesAndDirectories(
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
