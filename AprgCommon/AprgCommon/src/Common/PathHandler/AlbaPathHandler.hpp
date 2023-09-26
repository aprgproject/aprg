#pragma once

#include <Common/PathHandler/PathType.hpp>

#include <string>

namespace alba {

class AlbaPathHandler {
public:
    explicit AlbaPathHandler(std::string_view const slashCharacterString);
    explicit AlbaPathHandler(std::string_view const path, std::string_view const slashCharacterString);
    virtual ~AlbaPathHandler() = default;  // virtual destructor because of virtual functions (vtable exists)
    AlbaPathHandler(AlbaPathHandler const &pathHandler) = default;
    AlbaPathHandler(AlbaPathHandler &&pathHandler) noexcept = default;
    AlbaPathHandler &operator=(AlbaPathHandler const &pathHandler) = default;
    AlbaPathHandler &operator=(AlbaPathHandler &&pathHandler) noexcept = default;
    [[nodiscard]] virtual std::string getPath() const;
    [[nodiscard]] virtual std::string getDirectory() const;
    virtual void clear();
    [[nodiscard]] PathType getPathType() const;
    [[nodiscard]] std::string getImmediateDirectoryName() const;
    [[nodiscard]] std::string getFile() const;
    [[nodiscard]] std::string getFilenameOnly() const;
    [[nodiscard]] std::string getExtension() const;
    [[nodiscard]] bool isDirectory() const;
    [[nodiscard]] bool isFile() const;
    [[nodiscard]] bool isEmpty() const;
    void input(std::string_view const path);
    void reInput();
    void goUp();

protected:
    virtual void save(std::string_view const path);
    void setPath(std::string_view const path);  // non virtual because used by constructor
    void setExtensionFromPath(std::string_view const path);
    void setDirectoryAndFileFromPath(std::string_view const path);
    void setFileType();
    PathType m_pathType;
    std::string m_slashCharacterString;
    std::string m_directory;
    std::string m_file;
    std::string m_extension;
};

}  // namespace alba
