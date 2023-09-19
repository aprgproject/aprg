#pragma once

#include <CodeUtilities/Common/CommonTypes.hpp>

#include <filesystem>

namespace alba::CodeUtilities {

class CPlusPlusFinder {
public:
    CPlusPlusFinder() = default;
    void processDirectory(std::filesystem::path const& directory);
    void processFile(std::filesystem::path const& file);

private:
    void findTerms();
    void findTerms(Patterns const& searchPatterns);
    std::filesystem::path m_currentFile;
    Terms m_currentTerms;
};

}  // namespace alba::CodeUtilities
