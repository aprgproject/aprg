#pragma once

#include <CodeUtilities/Common/CommonTypes.hpp>

#include <filesystem>

namespace alba::CodeUtilities {

class CPlusPlusFinder {
public:
    CPlusPlusFinder() = default;
    void processPath(std::filesystem::path const& path);
    void processDirectory(std::filesystem::path const& directory);
    void processFile(std::filesystem::path const& file);

private:
    void findTerms();
    void findTerms(Patterns const& searchPatterns);

private:
    std::filesystem::path m_currentFile;
    Terms m_currentTerms;
};

}  // namespace alba::CodeUtilities
