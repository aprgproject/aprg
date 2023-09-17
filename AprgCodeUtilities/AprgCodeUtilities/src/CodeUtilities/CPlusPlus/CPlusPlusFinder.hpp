#pragma once

#include <CodeUtilities/Common/CommonTypes.hpp>

namespace alba::CodeUtilities {

class CPlusPlusFinder {
public:
    CPlusPlusFinder() = default;
    void processPath(std::string const& path);
    void processDirectory(std::string const& directory);
    void processFile(std::string const& file);

private:
    void findTerms();
    void findTerms(Patterns const& searchPatterns);

private:
    std::string m_currentFile;
    Terms m_currentTerms;
};

}  // namespace alba::CodeUtilities
