#pragma once

#include <Common/File/AlbaFileReader.hpp>
#include <FileDirectoryDatabase/CMake/CMakeDatabase.hpp>

#include <fstream>
#include <functional>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

using std::function;
using std::ifstream;
using std::set;
using std::string;
using std::unordered_map;
using std::vector;

using alba::AlbaFileReader;

namespace codeReview {
typedef unordered_map<string, set<string>> VariableMapType;
typedef unordered_map<string, set<string>>::iterator VariableMapIterator;

class CMakeReader {
public:
    explicit CMakeReader(string const& fileName, CMakeDatabase& fileDirectoryDatabase);
    bool isFileValid();
    VariableMapType& getVariableMapReference();
    void printVariables();
    void addVariable(string const& variableName, string const& contents);
    void clearVariable(string const& variableName);
    void copyVariableMap(VariableMapType const& inputVariableMap);
    void copyVariableMapExceptCMakeDirectory(VariableMapType const& inputVariableMap);
    void addToFilesAndDirectoriesDatabase(string const& filesAndDirectories);
    void readFile();

private:
    void processProjectCommand(string& lineString, int& index);
    void processSetCommand(string& lineString, int& index);
    void processIncludeDirectoriesCommand(string& lineString, int& index);
    void processIncludeCommand(string& lineString, int& index);
    void processAddSubDirectoryCommand(string& lineString, int& index);
    void includeSecondArgumentToFilesAndDirectories(string& lineString, int& index);
    void replaceVariableWithRealValuesInStringAndDoOperation(
        VariableMapIterator startIterator, string const& contents, function<void(string)> operationIfFound);
    static void separateStringsUsingWhiteSpaceAndDoOperation(
        string const& string1, function<void(string)> operationForEachString);
    void addCMakeDirectoryIfNeededAndDoOperation(string const& string1, function<void(string)> operationForEachString);
    string getNextCMakeIdentifier(string& lineString, int& index);
    void findOpeningParenthesisAndProceed(string& lineString, int& index);
    string extractContentsUntilCloseParenthesis(string& lineString, int& index);
    void findAndProceedNotWhiteSpaceMultiLineSearch(string& lineString, int& index);
    bool readAnotherLineIfPossible(string& lineString, int& index);
    static bool checkAndProceedIfCharacterIsFound(string const& string1, string const& characters, int& index);
    static bool checkIfCharacterIsFound(string const& string1, string const& characters, int& index);
    static void ignoreEntireLine(string const& string1, int& index);
    static bool isIgnorable(string const& string1);
    static bool hasCMakeVariables(string const& string1);
    ifstream m_fileStream;
    AlbaFileReader m_albaFileReader;
    CMakeDatabase& m_fileDirectoryDatabase;
    VariableMapType m_variableMap;
    string m_fullPathOfFile;
    bool m_isFileValid{false};
};

}  // namespace codeReview
