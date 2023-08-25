#pragma once

#include <string>

namespace alba {

enum class PathType { Empty, Directory, File };

class AlbaPathHandler {
public:
    explicit AlbaPathHandler(std::string_view slashCharacterString);
    explicit AlbaPathHandler(std::string_view path, std::string_view slashCharacterString);
    virtual ~AlbaPathHandler() = default;  // virtual destructor because of virtual functions (vtable exists)
    AlbaPathHandler(AlbaPathHandler const &pathHandler) = default;
    AlbaPathHandler(AlbaPathHandler &&pathHandler) = default;
    AlbaPathHandler &operator=(AlbaPathHandler const &pathHandler) = default;
    AlbaPathHandler &operator=(AlbaPathHandler &&pathHandler) = default;

    virtual void clear();
    [[nodiscard]] virtual std::string getFullPath() const;
    [[nodiscard]] virtual std::string getDirectory() const;
    void input(std::string_view path);
    void reInput();
    void goUp();
    [[nodiscard]] std::string getImmediateDirectoryName() const;
    [[nodiscard]] std::string getFile() const;
    [[nodiscard]] std::string getFilenameOnly() const;
    [[nodiscard]] std::string getExtension() const;
    [[nodiscard]] PathType getPathType() const;
    [[nodiscard]] bool isDirectory() const;
    [[nodiscard]] bool isFile() const;
    [[nodiscard]] bool isEmpty() const;

protected:
    virtual void save(std::string_view path);
    void setPath(std::string_view path);  // non virtual because used by constructor
    void setExtensionFromPath(std::string_view path);
    void setDirectoryAndFileFromPath(std::string_view path);
    void setFileType();
    // NOLINTBEGIN(cppcoreguidelines-non-private-member-variables-in-classes,misc-non-private-member-variables-in-classes)
    PathType m_pathType;
    std::string m_slashCharacterString;
    std::string m_directory;
    std::string m_file;
    std::string m_extension;
    // NOLINTEND(cppcoreguidelines-non-private-member-variables-in-classes,misc-non-private-member-variables-in-classes)
};

}  // namespace alba
