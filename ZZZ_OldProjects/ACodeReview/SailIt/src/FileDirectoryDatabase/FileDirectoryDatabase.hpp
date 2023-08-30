#pragma once

#include <FileDirectoryDatabase/DatabaseTypes.hpp>

#include <ostream>

namespace codeReview {
using SetOfFiles = set<string>;
using SetOfDirectories = set<string>;

class FileDirectoryDatabase {
public:
    void printFilesAndDirectories(std::ostream& outputStream) const;
    [[nodiscard]] bool isFileIncluded(string const& baseDirectory, string const& fileName) const;
    [[nodiscard]] string getFullPathOfFile(string const& baseDirectory, string const& fileName) const;
    SetOfFiles& getSetOfFilesReference();
    SetOfDirectories& getSetOfDirectoriesReference();
    [[nodiscard]] static bool isFileInFullPath(string const& fullPathFromDatabase, string const& fileName);

    void allowNonExistentDirectories();
    void addFileOrDirectory(string const& fileOrDirectory);

private:
    SetOfDirectories m_directories;
    SetOfFiles m_files;
    bool m_isNonExistentDirectoriesAllowed{};
};

}  // namespace codeReview
