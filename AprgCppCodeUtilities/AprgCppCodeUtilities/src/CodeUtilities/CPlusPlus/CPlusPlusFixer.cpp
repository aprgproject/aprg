#include "CPlusPlusFixer.hpp"

#include <CodeUtilities/CPlusPlus/CPlusPlusTokenizer.hpp>
#include <CodeUtilities/Common/FindPatterns.hpp>
#include <Common/Debug/AlbaDebug.hpp>
#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/Print/AlbaLogPrints.hpp>

#include <iostream>

using namespace std;

namespace alba::CodeUtilities::CPlusPlusFixer {

bool isCppFile(string const& extension) {
    return extension == "cpp" || extension == "c" || extension == "cc" || extension == "hpp" || extension == "h";
}

void processDirectory(string const& path) {
    AlbaLocalPathHandler directoryPathHandler(path);
    ListOfPaths directories;
    ListOfPaths files;
    directoryPathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", files, directories);
    for (auto const& file : files) {
        AlbaLocalPathHandler filePathHandler(file);
        if (isCppFile(filePathHandler.getExtension())) {
            processFile(file);
        }
    }
}

void processFile(string const& path) {
    ALBA_INF_PRINT1(cout, path);
    Terms terms(getTermsFromFile(path));
    fixTerms(terms);
    writeAllTerms(path, terms);
}

Terms getTermsFromFile(string const& path) {
    Terms result;
    CPlusPlusTokenizer tokenizer(result);
    AlbaLocalPathHandler filePathHandler(path);
    ifstream inputStream(filePathHandler.getFullPath());
    AlbaFileReader fileReader(inputStream);
    while (fileReader.isNotFinished()) {
        tokenizer.processCode(fileReader.getLine());
        tokenizer.processCode("\n");
    }
    tokenizer.processLeftoverCode();
    return result;
}

void writeAllTerms(string const& path, Terms const& terms) {
    AlbaLocalPathHandler filePathHandler(path);
    ofstream outputStream(filePathHandler.getFullPath(), ios::binary);
    for (Term const& term : terms) {
        outputStream << term.getContent();
    }
}

void fixTerms(Terms& terms) {
    fixPostFixIncrementDecrement(terms, "++");
    fixPostFixIncrementDecrement(terms, "--");
    fixConstReferenceOrder(terms);
}

void fixPostFixIncrementDecrement(Terms& terms, string const& crementOperator) {
    findTermsAndSwapAt(
        terms,
        TermMatchers{
            TermMatcher("{"), TermMatcher(TermType::Identifier), TermMatcher(crementOperator), TermMatcher(";")},
        1, 2);
    findTermsAndSwapAt(
        terms,
        TermMatchers{
            TermMatcher(";"), TermMatcher(TermType::Identifier), TermMatcher(crementOperator), TermMatcher(";")},
        1, 2);
    findTermsAndSwapAt(
        terms,
        TermMatchers{
            TermMatcher(";"), TermMatcher(TermType::Identifier), TermMatcher(crementOperator), TermMatcher(")")},
        1, 2);
    findTermsAndSwapAt(
        terms,
        TermMatchers{
            TermMatcher(";"), TermMatcher(TermType::Identifier), TermMatcher(crementOperator), TermMatcher(",")},
        1, 2);
    findTermsAndSwapAt(
        terms,
        TermMatchers{
            TermMatcher(","), TermMatcher(TermType::Identifier), TermMatcher(crementOperator), TermMatcher(",")},
        1, 2);
    findTermsAndSwapAt(
        terms,
        TermMatchers{
            TermMatcher(","), TermMatcher(TermType::Identifier), TermMatcher(crementOperator), TermMatcher(")")},
        1, 2);
}

void fixConstReferenceOrder(Terms& terms) {
    findTermsAndSwapAt(
        terms,
        TermMatchers{TermMatcher("{"), TermMatcher("const"), TermMatcher(TermType::Identifier), TermMatcher("&")}, 1,
        2);
    findTermsAndSwapAt(
        terms,
        TermMatchers{TermMatcher(";"), TermMatcher("const"), TermMatcher(TermType::Identifier), TermMatcher("&")}, 1,
        2);
    findTermsAndSwapAt(
        terms,
        TermMatchers{TermMatcher("("), TermMatcher("const"), TermMatcher(TermType::Identifier), TermMatcher("&")}, 1,
        2);
    findTermsAndSwapAt(
        terms,
        TermMatchers{TermMatcher(","), TermMatcher("const"), TermMatcher(TermType::Identifier), TermMatcher("&")}, 1,
        2);
}

void findTermsAndSwapAt(Terms& terms, TermMatchers const& matchers, int const index1, int const index2) {
    int termIndex = 0;
    bool isFound(true);
    while (isFound) {
        PatternIndexes patternIndexes = findFirstPatternIgnoringSpacesAndComments(terms, matchers, termIndex);
        isFound = !patternIndexes.empty();
        if (isFound) {
            ALBA_DBG_PRINT(patternIndexes);
            ALBA_DBG_PRINT(
                terms[patternIndexes[0]], terms[patternIndexes[1]], terms[patternIndexes[2]], terms[patternIndexes[3]]);
            termIndex = patternIndexes.back();
            std::swap(terms[patternIndexes[index1]], terms[patternIndexes[index2]]);
        }
    }
}

}  // namespace alba::CodeUtilities::CPlusPlusFixer
