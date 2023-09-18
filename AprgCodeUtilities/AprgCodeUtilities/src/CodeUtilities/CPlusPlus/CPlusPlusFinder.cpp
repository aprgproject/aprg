#include "CPlusPlusFinder.hpp"

#include <CodeUtilities/CPlusPlus/CPlusPlusUtilities.hpp>
#include <CodeUtilities/Common/TermUtilities.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <iostream>

using namespace alba::CodeUtilities::CPlusPlusUtilities;
using namespace std;

namespace alba::CodeUtilities {

void CPlusPlusFinder::processPath(string const& path) {
    AlbaLocalPathHandler const pathHandler(path);
    if (pathHandler.doesExist()) {
        if (pathHandler.isDirectory()) {
            processDirectory(path);
        } else if (pathHandler.isFile()) {
            processFile(path);
        }
    }
}

void CPlusPlusFinder::processDirectory(string const& directory) {
    AlbaLocalPathHandler const directoryPathHandler(directory);
    ListOfPaths directories;
    ListOfPaths files;
    directoryPathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", files, directories);
    for (auto const& file : files) {
        AlbaLocalPathHandler const filePathHandler(file);
        if (isCppFileExtension(filePathHandler.getExtension())) {
            processFile(file);
        }
    }
}

void CPlusPlusFinder::processFile(string const& file) {
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
            cout << "Found file: [" << m_currentFile << "] pattern found at: ["
                 << getLocatorString(m_currentTerms, hitIndexes.front()) << "]\n";
        }
    }
}

}  // namespace alba::CodeUtilities
