#include "CPlusPlusFixer.hpp"

#include <CodeUtilities/CPlusPlus/CPlusPlusTokenizer.hpp>
#include <CodeUtilities/Common/TermUtilities.hpp>
#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/Print/AlbaLogPrints.hpp>

#include <iostream>

using namespace std;

namespace alba::CodeUtilities::CPlusPlusFixer {

void processAprgDirectory(string const& aprgPath) {
    AlbaLocalPathHandler aprgPathHandler(aprgPath);
    ALBA_INF_PRINT1(cout, aprgPath);
    ListOfPaths directories;
    ListOfPaths files;
    aprgPathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", files, directories);
    for (auto const& file : files) {
        AlbaLocalPathHandler filePathHandler(file);
        if (filePathHandler.getFile() == "CppProjectIndicatorFile.txt") {
            processDirectory(filePathHandler.getDirectory());
        }
    }
}

void processPath(string const& path) {
    AlbaLocalPathHandler pathHandler(path);
    if (pathHandler.isFoundInLocalSystem()) {
        if (pathHandler.isDirectory()) {
            processDirectory(path);
        } else if (pathHandler.isFile()) {
            processFile(path);
        }
    }
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
    combinePrimitiveTypes(terms);
    // fixPostFixIncrementDecrement(terms);
    // fixConstReferenceOrder(terms);
    // fixCStyleStaticCast(terms);
    // fixNoConstPassByValue(terms);
}

void fixPostFixIncrementDecrement(Terms& terms) {
    fixPostFixIncrementDecrement(terms, "++");
    fixPostFixIncrementDecrement(terms, "--");
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
    fixConstReferenceOrder(terms, TermMatcher(TermType::Identifier));
    fixConstReferenceOrder(terms, TermMatcher(TermType::PrimitiveType));
    fixConstReferenceOrder(terms, TermMatcher("auto"));
}

void fixConstReferenceOrder(Terms& terms, TermMatcher const& typeMatcher) {
    findTermsAndSwapAt(
        terms, TermMatchers{TermMatcher("{"), TermMatcher("const"), typeMatcher, TermMatcher("&")}, 1, 2);
    findTermsAndSwapAt(
        terms, TermMatchers{TermMatcher(";"), TermMatcher("const"), typeMatcher, TermMatcher("&")}, 1, 2);
    findTermsAndSwapAt(
        terms, TermMatchers{TermMatcher("("), TermMatcher("const"), typeMatcher, TermMatcher("&")}, 1, 2);
    findTermsAndSwapAt(
        terms, TermMatchers{TermMatcher(","), TermMatcher("const"), typeMatcher, TermMatcher("&")}, 1, 2);
}

void fixCStyleStaticCast(Terms& terms) { fixCStyleStaticCast(terms, TermMatcher(TermType::PrimitiveType)); }

void fixCStyleStaticCast(Terms& terms, TermMatcher const& typeMatcher) {
    TermMatchers matchers{TermMatcher(TermType::Operator), TermMatcher("("), typeMatcher, TermMatcher(")")};
    int termIndex = 0;
    bool isFound(true);
    while (isFound) {
        PatternIndexes patternIndexes = findFirstPatternIgnoringSpacesAndComments(terms, matchers, termIndex);
        isFound = !patternIndexes.empty();
        if (isFound) {
            termIndex = patternIndexes.back();
            terms[patternIndexes[1]].setContent("static_cast<");
            terms[patternIndexes[3]].setContent(">(");
            ALBA_INF_PRINT3(cout, terms[patternIndexes[0]], terms[patternIndexes[1]], terms[patternIndexes[2]]);
        }
    }
}
void fixNoConstPassByValue(Terms& terms) {
    fixNoConstPassByValue(
        terms,
        TermMatchers{
            TermMatcher("("), TermMatcher(TermType::Identifier), TermMatcher(TermType::Identifier), TermMatcher(",")});
    fixNoConstPassByValue(
        terms,
        TermMatchers{
            TermMatcher(","), TermMatcher(TermType::Identifier), TermMatcher(TermType::Identifier), TermMatcher(",")});
    fixNoConstPassByValue(
        terms,
        TermMatchers{
            TermMatcher(","), TermMatcher(TermType::Identifier), TermMatcher(TermType::Identifier), TermMatcher(")")});
    fixNoConstPassByValue(
        terms, TermMatchers{
                   TermMatcher("("), TermMatcher(TermType::PrimitiveType), TermMatcher(TermType::Identifier),
                   TermMatcher(",")});
    fixNoConstPassByValue(
        terms, TermMatchers{
                   TermMatcher(","), TermMatcher(TermType::PrimitiveType), TermMatcher(TermType::Identifier),
                   TermMatcher(",")});
    fixNoConstPassByValue(
        terms, TermMatchers{
                   TermMatcher(","), TermMatcher(TermType::PrimitiveType), TermMatcher(TermType::Identifier),
                   TermMatcher(")")});
}

void fixNoConstPassByValue(Terms& terms, TermMatchers const& matchers) {
    int termIndex = 0;
    bool isFound(true);
    while (isFound) {
        PatternIndexes patternIndexes = findFirstPatternIgnoringSpacesAndComments(terms, matchers, termIndex);
        isFound = !patternIndexes.empty();
        if (isFound) {
            termIndex = patternIndexes.back();
            terms.insert(terms.begin() + patternIndexes[2], Term(TermType::Identifier, "const "));
            ALBA_INF_PRINT4(
                cout, terms[patternIndexes[0]], terms[patternIndexes[1]], terms[patternIndexes[2]],
                terms[patternIndexes[3]]);
        }
    }
}

void findTermsAndSwapAt(Terms& terms, TermMatchers const& matchers, int const index1, int const index2) {
    int termIndex = 0;
    bool isFound(true);
    while (isFound) {
        PatternIndexes patternIndexes = findFirstPatternIgnoringSpacesAndComments(terms, matchers, termIndex);
        isFound = !patternIndexes.empty();
        if (isFound) {
            termIndex = patternIndexes.back();
            std::swap(terms[patternIndexes[index1]], terms[patternIndexes[index2]]);
            ALBA_INF_PRINT2(cout, terms[patternIndexes[index1]], terms[patternIndexes[index2]]);
        }
    }
}

void combinePrimitiveTypes(Terms& terms) {
    int termIndex = 0;
    bool isFound(true);
    TermMatchers primitiveTypeMatchers{TermMatcher(TermType::PrimitiveType), TermMatcher(TermType::PrimitiveType)};
    while (isFound) {
        PatternIndexes patternIndexes =
            findFirstPatternIgnoringSpacesAndComments(terms, primitiveTypeMatchers, termIndex);
        isFound = !patternIndexes.empty();
        if (isFound) {
            termIndex = patternIndexes.front();
            combineTermsInPlace(terms, TermType::PrimitiveType, patternIndexes[0], patternIndexes[1]);
        }
    }
}

bool isCppFile(string const& extension) {
    return extension == "cpp" || extension == "c" || extension == "cc" || extension == "hpp" || extension == "h";
}

}  // namespace alba::CodeUtilities::CPlusPlusFixer
