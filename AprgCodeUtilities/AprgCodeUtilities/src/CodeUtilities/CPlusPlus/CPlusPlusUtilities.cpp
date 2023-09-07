#include "CPlusPlusUtilities.hpp"

#include <CodeUtilities/CPlusPlus/CPlusPlusTokenizer.hpp>
#include <CodeUtilities/Common/Pattern.hpp>
#include <CodeUtilities/Common/TermUtilities.hpp>
#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <iostream>

using namespace alba::stringHelper;
using namespace std;

namespace alba::CodeUtilities::CPlusPlusUtilities {

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

Terms getTermsFromString(string const& code) {
    Terms result;
    CPlusPlusTokenizer tokenizer(result);
    tokenizer.processCode(code);
    tokenizer.processLeftoverCode();
    return result;
}

std::string getFunctionSignature(std::string const& functionText) {
    Terms terms(getTermsFromString(functionText));
    Patterns terminatingPatterns{{M(";")}, {M("{")}, {M(":")}};
    Indexes terminatingIndexes = searchForPatternsForwards(terms, 0, terminatingPatterns);
    if (!terminatingIndexes.empty()) {
        terms.erase(terms.cbegin() + terminatingIndexes.front(), terms.cend());
    }

    Patterns removePatterns{
        {M(MatcherType::Comment)},
        {M("explicit")},
        {M("inline")},
        {M("static")},
        {M("constexpr")},
        {M("volatile")},
        {M(TermType::Attribute)},
        {M("friend")},
        {M(TermType::Identifier), M("::")}};
    replaceAllForwards(terms, 0, removePatterns, {});

    replaceAllForwards(
        terms, 0, Patterns{{M(TermType::WhiteSpace), M(TermType::WhiteSpace)}, {M(TermType::WhiteSpace)}},
        {Term(TermType::WhiteSpace, " ")});

    Indexes whiteSpaceStartIndexes = checkPatternAt(terms, 0, Patterns{{M(TermType::WhiteSpace)}});
    if (!whiteSpaceStartIndexes.empty()) {
        terms.erase(terms.cbegin(), terms.cbegin() + whiteSpaceStartIndexes.back() + 1);
    }
    Indexes whiteSpaceEndIndexes =
        checkPatternAt(terms, static_cast<int>(terms.size()) - 1, Patterns{{M(TermType::WhiteSpace)}});
    if (!whiteSpaceEndIndexes.empty()) {
        terms.erase(terms.cbegin() + whiteSpaceEndIndexes.front(), terms.cend());
    }

    return getCombinedContents(terms);
}

}  // namespace alba::CodeUtilities::CPlusPlusUtilities
