#include "CPlusPlusFixer.hpp"

#include <CodeUtilities/CPlusPlus/CPlusPlusUtilities.hpp>
#include <CodeUtilities/Common/TermUtilities.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/Print/AlbaLogPrints.hpp>

#include <fstream>
#include <iostream>

using namespace std;
using namespace alba::CodeUtilities::CPlusPlusUtilities;

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

void fixTerms(Terms& terms) {
    combinePrimitiveTypes(terms);
    // fixPostFixIncrementDecrement(terms);
    // fixConstReferenceOrder(terms);
    // fixCStyleStaticCast(terms);
    // fixNoConstPassByValue(terms);
    fixCommentsPositionOfBraces(terms);
}

void fixPostFixIncrementDecrement(Terms& terms) {
    fixPostFixIncrementDecrement(terms, "++");
    fixPostFixIncrementDecrement(terms, "--");
}

void fixPostFixIncrementDecrement(Terms& terms, string const& crementOperator) {
    fixPostFixIncrementDecrementInLine(terms, crementOperator);
    fixPostFixIncrementDecrementInForLoop(terms, crementOperator);
}

void fixPostFixIncrementDecrementInLine(Terms& terms, string const& crementOperator) {
    findTermsAndSwapAt(terms, {{M("{"), M(TermType::Identifier), M(crementOperator), M(";")}}, 1, 2);
    findTermsAndSwapAt(terms, {{M("}"), M(TermType::Identifier), M(crementOperator), M(";")}}, 1, 2);
    findTermsAndSwapAt(terms, {{M(";"), M(TermType::Identifier), M(crementOperator), M(";")}}, 1, 2);
    findTermsAndSwapAt(terms, {{M(","), M(TermType::Identifier), M(crementOperator), M(";")}}, 1, 2);
    findTermsAndSwapAt(terms, {{M(";"), M(TermType::Identifier), M(crementOperator), M(",")}}, 1, 2);
    findTermsAndSwapAt(terms, {{M(";"), M(TermType::Identifier), M(crementOperator), M(")")}}, 1, 2);
}

void fixPostFixIncrementDecrementInForLoop(Terms& terms, string const& crementOperator) {
    findTermsAndCheckForLoopAndSwapAt(terms, {{M(","), M(TermType::Identifier), M(crementOperator), M(")")}}, 1, 2);
    findTermsAndCheckForLoopAndSwapAt(terms, {{M(","), M(TermType::Identifier), M(crementOperator), M(",")}}, 1, 2);
}

void fixConstReferenceOrder(Terms& terms) {
    fixConstReferenceOrder(terms, M(TermType::Identifier));
    fixConstReferenceOrder(terms, M(TermType::PrimitiveType));
    fixConstReferenceOrder(terms, M("auto"));
}

void fixConstReferenceOrder(Terms& terms, TermMatcher const& typeMatcher) {
    findTermsAndSwapAt(terms, {{M("{"), M("const"), typeMatcher, M("&")}}, 1, 2);
    findTermsAndSwapAt(terms, {{M("}"), M("const"), typeMatcher, M("&")}}, 1, 2);
    findTermsAndSwapAt(terms, {{M(";"), M("const"), typeMatcher, M("&")}}, 1, 2);
    findTermsAndSwapAt(terms, {{M("("), M("const"), typeMatcher, M("&")}}, 1, 2);
    findTermsAndSwapAt(terms, {{M(","), M("const"), typeMatcher, M("&")}}, 1, 2);
}

void fixCStyleStaticCast(Terms& terms) { fixCStyleStaticCast(terms, M(TermType::PrimitiveType)); }

void fixCStyleStaticCast(Terms& terms, TermMatcher const& typeMatcher) {
    Patterns searchPatterns{{M(TermType::Operator), M("("), typeMatcher, M(")"), M(MatcherType::NotAWhiteSpace)}};
    int termIndex = 0;
    bool isFound(true);
    while (isFound) {
        Indexes hitIndexes = searchForPatternsForwards(terms, termIndex, searchPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            termIndex = hitIndexes.back();
            if (terms[hitIndexes[4]].getContent() != "=") {
                changeTerm(terms[hitIndexes[1]], TermType::Aggregate, "static_cast<");
                changeTerm(terms[hitIndexes[3]], TermType::Aggregate, ">(");
                ALBA_INF_PRINT3(cout, terms[hitIndexes[0]], terms[hitIndexes[1]], terms[hitIndexes[2]]);
            }
        }
    }
}

void fixNoConstPassByValue(Terms& terms) {
    fixNoConstPassByValue(terms, M(MatcherType::IdentifierAndNotAScreamingSnakeCase));
    fixNoConstPassByValue(terms, M(TermType::PrimitiveType));
}

void fixNoConstPassByValue(Terms& terms, TermMatcher const& typeMatcher) {
    fixNoConstPassByValue(terms, {{M("("), typeMatcher, M(TermType::Identifier), M(")")}});
    fixNoConstPassByValue(terms, {{M("("), typeMatcher, M(TermType::Identifier), M(",")}});
    fixNoConstPassByValue(terms, {{M(","), typeMatcher, M(TermType::Identifier), M(",")}});
    fixNoConstPassByValue(terms, {{M(","), typeMatcher, M(TermType::Identifier), M(")")}});
    fixNoConstPassByValue(terms, {{M("::"), typeMatcher, M(TermType::Identifier), M(",")}});
    fixNoConstPassByValue(terms, {{M("::"), typeMatcher, M(TermType::Identifier), M(")")}});
}

void fixNoConstPassByValue(Terms& terms, Patterns const& searchPatterns) {
    int termIndex = 0;
    bool isFound(true);
    while (isFound) {
        Indexes hitIndexes = searchForPatternsForwards(terms, termIndex, searchPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            termIndex = hitIndexes.back();
            terms.insert(terms.begin() + hitIndexes[2], Term(TermType::Identifier, "const "));
            ALBA_INF_PRINT4(
                cout, terms[hitIndexes[0]], terms[hitIndexes[1]], terms[hitIndexes[2]], terms[hitIndexes[3]]);
        }
    }
}

void fixCommentsPositionOfBraces(Terms& terms) {
    Patterns searchPatterns{{M(MatcherType::Comment), M("{")}};
    int termIndex = 0;
    bool isFound(true);
    while (isFound) {
        Indexes hitIndexes = searchForPatternsForwards(terms, termIndex, searchPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            termIndex = hitIndexes.back();
            std::swap(terms[hitIndexes[0]], terms[hitIndexes[1]]);
            Term nextTermAfterComment = terms[hitIndexes[1] + 1];
            if (!hasNewLine(nextTermAfterComment)) {
                terms.insert(terms.begin() + hitIndexes[1] + 1, Term(TermType::WhiteSpace, "\n"));
            }
            ALBA_INF_PRINT2(cout, terms[hitIndexes[0]], terms[hitIndexes[1]]);
        }
    }
}

void findTermsAndSwapAt(Terms& terms, Patterns const& searchPatterns, int const index1, int const index2) {
    int termIndex = 0;
    bool isFound(true);
    while (isFound) {
        Indexes hitIndexes = searchForPatternsForwards(terms, termIndex, searchPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            termIndex = hitIndexes.back();
            std::swap(terms[hitIndexes[index1]], terms[hitIndexes[index2]]);
            ALBA_INF_PRINT2(cout, terms[hitIndexes[index1]], terms[hitIndexes[index2]]);
        }
    }
}

void findTermsAndCheckForLoopAndSwapAt(
    Terms& terms, Patterns const& searchPatterns, int const index1, int const index2) {
    int termIndex = 0;
    bool isFound(true);
    while (isFound) {
        Indexes hitIndexes = searchForPatternsForwards(terms, termIndex, searchPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            termIndex = hitIndexes.back();
            Patterns forLoopPatterns{{M("for"), M("(")}, {M(";")}, {M("{")}, {M("}")}};
            Indexes forLoopHitIndexes = searchForPatternsBackwards(terms, hitIndexes.front(), forLoopPatterns);
            if (forLoopHitIndexes.size() == 2 && terms[forLoopHitIndexes[0]].getContent() == "for" &&
                terms[forLoopHitIndexes[1]].getContent() == "(") {
                std::swap(terms[hitIndexes[index1]], terms[hitIndexes[index2]]);
                ALBA_INF_PRINT2(cout, terms[hitIndexes[index1]], terms[hitIndexes[index2]]);
            }
        }
    }
}

void combinePrimitiveTypes(Terms& terms) {
    int termIndex = 0;
    bool isFound(true);
    Patterns primitiveTypesPatterns{{M(TermType::PrimitiveType), M(TermType::PrimitiveType)}};
    while (isFound) {
        Indexes hitIndexes = searchForPatternsForwards(terms, termIndex, primitiveTypesPatterns);
        isFound = !hitIndexes.empty();
        if (isFound) {
            termIndex = hitIndexes.front();
            combineTermsInPlace(terms, TermType::PrimitiveType, hitIndexes[0], hitIndexes[1]);
        }
    }
}

}  // namespace alba::CodeUtilities::CPlusPlusFixer
