#include "ReplaceStringInFiles.hpp"

#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

using namespace alba::stringHelper;
using namespace std;
using namespace std::filesystem;

namespace alba {

string ReplaceStringInFiles::getCPlusPlusStylePrintFromC(string const& inputString) {
    string result;
    strings splittedStrings;
    strings const delimeters{R"((")", R"(",)", ");"};
    splitToStringsUsingASeriesOfDelimeters(splittedStrings, inputString, delimeters);

    if (splittedStrings.size() == 2) {
        strings const delimetersForTwo{R"((")", "\");"};
        splittedStrings.clear();
        splitToStringsUsingASeriesOfDelimeters(splittedStrings, inputString, delimetersForTwo);
        string const printFunction(splittedStrings[0]);
        string const newPrintStream(getNewPrintStreamBasedFromOldPrintFunction(printFunction));
        result += newPrintStream;
        result += R"( << ")";
        result += getStringWithoutStartingAndTrailingWhiteSpace(splittedStrings[1]);
        result += R"(" << flush();)";
    } else if (splittedStrings.size() >= 3) {
        string const printFunction(getStringWithoutStartingAndTrailingWhiteSpace(splittedStrings[0]));
        string const printString(splittedStrings[1]);
        strings printParameters;
        splitToStrings<SplitStringType::WithoutDelimeters>(printParameters, splittedStrings[2], ",");
        string const newPrintStream(getNewPrintStreamBasedFromOldPrintFunction(printFunction));
        removeStartingAndTrailingWhiteSpaceInPrintParameters(printParameters);
        result = constructCPlusPlusPrint(newPrintStream, "flush()", printString, printParameters);
    }
    return result;
}

void ReplaceStringInFiles::replaceStringWithStringOnDirectories(
    path const& inputDirectory, path const& outputDirectory, StringPairs const& replacePairs) {
    AlbaLocalPathHandler const inputPathHandler(inputDirectory);
    AlbaLocalPathHandler const outputPathHandler(outputDirectory);
    inputPathHandler.findFilesAndDirectoriesUnlimitedDepth(
        [](AlbaLocalPathHandler::LocalPath const&) {},
        [&](AlbaLocalPathHandler::LocalPath const& filePath) {
            AlbaLocalPathHandler const inputFilePathHandler(filePath);
            if (isCOrCPlusPlusFile(inputFilePathHandler.getExtension().string())) {
                string outputFilePathString(inputFilePathHandler.getPath().string());
                replaceAllAndReturnIfFound(
                    outputFilePathString, inputPathHandler.getPath().string(), outputPathHandler.getPath().string());
                AlbaLocalPathHandler const outputFilePathHandler(outputFilePathString);
                replaceStringWithStringOnFile(
                    inputFilePathHandler.getPath(), outputFilePathHandler.getPath(), replacePairs);
            }
        });
}

void ReplaceStringInFiles::replaceStringWithStringOnFile(
    path const& inputFilePath, path const& outputFilePath, StringPairs const& replacePairs) {
    AlbaLocalPathHandler const outputFilePathHandler(outputFilePath);
    if (outputFilePathHandler.createDirectoriesAndIsSuccessful()) {
        ifstream inputFile(inputFilePath);
        ofstream outputFile(outputFilePath);
        if (inputFile.is_open()) {
            AlbaFileReader inputFileReader(inputFile);
            while (inputFileReader.isNotFinished()) {
                string line(inputFileReader.getLine());
                for (auto const& replacePair : replacePairs) {
                    replaceAllAndReturnIfFound(line, replacePair.first, replacePair.second);
                }
                outputFile << getStringWithoutStartingAndTrailingWhiteSpace(line) << "\n";
            }
        }
    }
}

void ReplaceStringInFiles::replaceCToCPlusPlusStylePrintOnDirectories(
    path const& inputDirectory, path const& outputDirectory) {
    AlbaLocalPathHandler const inputPathHandler(inputDirectory);
    AlbaLocalPathHandler const outputPathHandler(outputDirectory);
    inputPathHandler.findFilesAndDirectoriesUnlimitedDepth(
        [](AlbaLocalPathHandler::LocalPath const&) {},
        [&](AlbaLocalPathHandler::LocalPath const& filePath) {
            AlbaLocalPathHandler const inputFilePathHandler(filePath);
            if (isCOrCPlusPlusFile(inputFilePathHandler.getExtension().string())) {
                string outputFilePathString(inputFilePathHandler.getPath().string());
                replaceAllAndReturnIfFound(
                    outputFilePathString, inputPathHandler.getPath().string(), outputPathHandler.getPath().string());
                AlbaLocalPathHandler const outputFilePathHandler(outputFilePathString);
                replaceCToCPlusPlusStylePrintOnFile(inputFilePathHandler.getPath(), outputFilePathHandler.getPath());
            }
        });
}

void ReplaceStringInFiles::replaceCToCPlusPlusStylePrintOnFile(path const& inputFilePath, path const& outputFilePath) {
    AlbaLocalPathHandler const outputFilePathHandler(outputFilePath);
    if (outputFilePathHandler.createDirectoriesAndIsSuccessful()) {
        ifstream inputFile(inputFilePath);
        ofstream outputFile(outputFilePath);
        if (inputFile.is_open()) {
            AlbaFileReader inputFileReader(inputFile);
            string print;
            bool isOnPrint(false);
            while (inputFileReader.isNotFinished()) {
                string const lineInInputFile(inputFileReader.getLine());
                bool const hasPrintInLineInInputFile = hasPrintInLine(lineInInputFile);
                bool const hasSemiColonInLineInInputFile = hasEndOfPrintInLine(lineInInputFile);
                if (isOnPrint) {
                    if (hasPrintInLineInInputFile && hasSemiColonInLineInInputFile) {
                        outputFile << getCPlusPlusStylePrintFromC(getStringWithoutStartingAndTrailingWhiteSpace(print))
                                   << "\n";
                        print = lineInInputFile;
                        print.clear();
                        isOnPrint = false;
                    } else if (hasPrintInLineInInputFile) {
                        outputFile << getCPlusPlusStylePrintFromC(getStringWithoutStartingAndTrailingWhiteSpace(print))
                                   << "\n";
                        print = lineInInputFile;
                    } else if (hasSemiColonInLineInInputFile) {
                        print += " ";
                        print += lineInInputFile;
                        outputFile << getCPlusPlusStylePrintFromC(getStringWithoutStartingAndTrailingWhiteSpace(print))
                                   << "\n";
                        print.clear();
                        isOnPrint = false;
                    } else {
                        print += " ";
                        print += lineInInputFile;
                    }
                } else {
                    if (hasPrintInLineInInputFile && hasSemiColonInLineInInputFile) {
                        print += lineInInputFile;
                        outputFile << getCPlusPlusStylePrintFromC(getStringWithoutStartingAndTrailingWhiteSpace(print))
                                   << "\n";
                        print.clear();
                    } else if (hasPrintInLineInInputFile) {
                        print += lineInInputFile;
                        isOnPrint = true;
                    } else {
                        outputFile << lineInInputFile << "\n";
                    }
                }
            }
        }
    }
}

string ReplaceStringInFiles::constructCPlusPlusPrint(
    string const& newPrintStream, string const& endPrintStream, string const& printString,
    strings const& printParameters) {
    string result(newPrintStream);
    bool isPercentEncountered(false);
    bool isOnStringLiteral(false);
    int printParameterIndex = 0;
    for (char const c : printString) {
        bool isParameterAppended(false);
        if (isPercentEncountered) {
            if (isLetter(c)) {
                if (printParameterIndex < static_cast<int>(printParameters.size())) {
                    appendParameterToResult(result, isOnStringLiteral, printParameters[printParameterIndex++]);
                    isParameterAppended = true;
                }
            } else if (!isNumber(c)) {
                appendCharacterToResult(result, isOnStringLiteral, '%');
            }
        }
        isPercentEncountered = ('%' == c) || (isNumber(c) && isPercentEncountered);
        if (!isPercentEncountered && !isParameterAppended) {
            appendCharacterToResult(result, isOnStringLiteral, c);
        }
    }
    appendParameterToResult(result, isOnStringLiteral, endPrintStream);
    result += ";";
    return result;
}

void ReplaceStringInFiles::removeStartingAndTrailingWhiteSpaceInPrintParameters(strings& printParameters) {
    for (string& printParameter : printParameters) {
        printParameter = getStringWithoutStartingAndTrailingWhiteSpace(printParameter);
    }
}

void ReplaceStringInFiles::appendCharacterToResult(string& result, bool& isOnStringLiteral, char const c) {
    if (isOnStringLiteral) {
        result += c;
    } else {
        result += R"( << ")";
        result += c;
    }
    isOnStringLiteral = true;
}

void ReplaceStringInFiles::appendParameterToResult(string& result, bool& isOnStringLiteral, string const& parameter) {
    if (isOnStringLiteral) {
        result += R"(" << )";
        result += parameter;
    } else {
        result += R"( << )";
        result += parameter;
    }
    isOnStringLiteral = false;
}

string ReplaceStringInFiles::getNewPrintStreamBasedFromOldPrintFunction(string const& printFunction) {
    string newPrintStream;
    if ("TLH_DEBUG_PRINT" == printFunction) {
        newPrintStream = "debug()";
    } else if ("TLH_INFO_PRINT" == printFunction) {
        newPrintStream = "info()";
    } else if ("TLH_WARNING_PRINT" == printFunction) {
        newPrintStream = "warning()";
    } else if ("TLH_ERROR_PRINT" == printFunction) {
        newPrintStream = "error()";
    }
    return newPrintStream;
}

bool ReplaceStringInFiles::isCOrCPlusPlusFile(string const& extensionString) {
    return "cpp" == extensionString || "hpp" == extensionString || "c" == extensionString || "h" == extensionString;
}

bool ReplaceStringInFiles::hasPrintInLine(string const& line) {
    return isStringFoundCaseSensitive(line, "TLH_DEBUG_PRINT") || isStringFoundCaseSensitive(line, "TLH_INFO_PRINT") ||
           isStringFoundCaseSensitive(line, "TLH_WARNING_PRINT") || isStringFoundCaseSensitive(line, "TLH_ERROR_PRINT");
}

bool ReplaceStringInFiles::hasEndOfPrintInLine(string const& line) { return isStringFoundCaseSensitive(line, ");"); }

}  // namespace alba
