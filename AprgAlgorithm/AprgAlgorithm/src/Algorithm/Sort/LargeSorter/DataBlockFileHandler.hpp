#pragma once

#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <cassert>
#include <filesystem>
#include <fstream>
#include <optional>
#include <string>

namespace alba::algorithm {

template <typename ObjectToSort>
class DataBlockFileHandler {
public:
    DataBlockFileHandler() = default;
    DataBlockFileHandler(DataBlockFileHandler const &) = default;
    DataBlockFileHandler(DataBlockFileHandler &&) = default;
    DataBlockFileHandler &operator=(DataBlockFileHandler const &) = default;
    DataBlockFileHandler &operator=(DataBlockFileHandler &&) = default;

    ~DataBlockFileHandler() {
        releaseFileStream();
        AlbaLocalPathHandler(m_path).deleteFileAndIsSuccessful();
    }

    void openFileIfNeeded(std::filesystem::path const &path) {
        if (!m_fileOptional) {
            AlbaLocalPathHandler const filePathHandler(path);
            // filePathHandler.createDirectoriesForNonExisitingDirectories(); //is this needed?
            m_path = filePathHandler.getPath();
            m_fileOptional.emplace();
            std::ofstream &fileStream(m_fileOptional.value());
            fileStream.open(m_path, std::ios::ate | std::ios::app);
            assert(!fileStream.fail());
        }
    }

    void add(ObjectToSort const &objectToSort) { m_fileOptional.value() << objectToSort << "\n"; }

    void releaseFileStream() {
        // m_fileOptional->close(); // close does not work why?
        m_fileOptional.reset();
    }

    std::ofstream &getFileDumpStreamReference() { return m_fileOptional.value(); }

    bool isFileStreamOpened() {
        if (m_fileOptional) {
            return m_fileOptional->is_open();
        }
        return false;
    }

private:
    std::filesystem::path m_path;
    std::optional<std::ofstream> m_fileOptional;
};

}  // namespace alba::algorithm
