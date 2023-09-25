#include "CPlusPlusFinder.hpp"

#include <CodeUtilities/CPlusPlus/CPlusPlusUtilities.hpp>
#include <CodeUtilities/Common/CommonUtilities.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <iostream>

using namespace alba::CodeUtilities::CPlusPlusUtilities;
using namespace std;
using namespace std::filesystem;

namespace alba::CodeUtilities {

void CPlusPlusFinder::processDirectory(path const& directory) {
    AlbaLocalPathHandler const directoryPathHandler(directory);
    directoryPathHandler.findFilesAndDirectoriesUnlimitedDepth(
        [](AlbaLocalPathHandler::LocalPath const&) {},
        [&](AlbaLocalPathHandler::LocalPath const& filePath) {
            AlbaLocalPathHandler const filePathHandler(filePath);
            if (isCppFileExtension(filePathHandler.getExtension().string())) {
                processFile(filePathHandler.getPath());
            }
        });
}

void CPlusPlusFinder::processFile(path const& file) {
    m_currentFile = file;
    m_currentTerms = getTermsFromFile(file);
    findTerms();
    writeAllTerms(file, m_currentTerms);
}

void CPlusPlusFinder::findTerms() { findTerms({{M("emplace_back"), M("("), M("Polynomial"), M("{")}}); }

void CPlusPlusFinder::findTerms(Patterns const& searchPatterns) {
    int termIndex = 0;
    bool isFound(true);
    while (isFound) {
        Indexes hitIndexes = searchForwardsForPatterns(m_currentTerms, termIndex, searchPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            termIndex = hitIndexes.back();
            cout << "Found file: [" << m_currentFile << "]\n";
            cout << "Found pattern found at: [" << getLocatorString(m_currentTerms, hitIndexes.front()) << "]\n";
        }
    }
}

}  // namespace alba::CodeUtilities
