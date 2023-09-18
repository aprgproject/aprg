#include "CPlusPlusUtilities.hpp"

#include <CodeUtilities/CPlusPlus/CPlusPlusTokenizer.hpp>
#include <CodeUtilities/Common/CommonTypes.hpp>
#include <CodeUtilities/Common/TermUtilities.hpp>
#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <iostream>

using namespace alba::stringHelper;
using namespace std;

namespace alba::CodeUtilities::CPlusPlusUtilities {

void writeAllTerms(string const& path, Terms const& terms) {
    AlbaLocalPathHandler const filePathHandler(path);
    ofstream outputStream(filePathHandler.getPath(), ios::binary);
    for (Term const& term : terms) {
        outputStream << term.getContent();
    }
}

CppFileType getFileType(string const& extension) {
    return isHeaderFileExtension(extension) ? CppFileType::HeaderFile
           : isCppFileExtension(extension)  ? CppFileType::CppFile
                                            : CppFileType::Unknown;
}

Terms getTermsFromFile(string const& path) {
    Terms result;
    CPlusPlusTokenizer tokenizer(result);
    AlbaLocalPathHandler const filePathHandler(path);
    ifstream inputStream(filePathHandler.getPath());
    AlbaFileReader fileReader(inputStream);
    while (fileReader.isNotFinished()) {
        tokenizer.processCode(fileReader.getLine());
        tokenizer.processCode("\n");
    }
    tokenizer.processLeftoverCode();
    return result;
}

Terms getTermsFromString(string const& code) {
    Terms result;
    CPlusPlusTokenizer tokenizer(result);
    tokenizer.processCode(code);
    tokenizer.processLeftoverCode();
    return result;
}

string getFunctionSignature(string const& functionText) {
    Terms terms(getTermsFromString(functionText));
    Patterns const terminatingPatterns{{M(TermType::Macro)}, {M(";")}, {M("{")}, {M(":")}};
    Indexes terminatingIndexes = searchForwardsForPatterns(terms, 0, terminatingPatterns);
    if (!terminatingIndexes.empty()) {
        terms.erase(terms.cbegin() + terminatingIndexes.front(), terms.cend());
    }

    Patterns const removePatterns{
        {M(MatcherType::Comment)},
        {M("explicit")},
        {M("inline")},
        {M("static")},
        {M("virtual")},
        {M("constexpr")},
        {M("volatile")},
        {M(TermType::Attribute)},
        {M("friend")},
        {M(TermType::Identifier), M("::")}};
    replaceAllForwards(terms, 0, removePatterns, {});

    replaceAllForwards(
        terms, 0, Patterns{{M(TermType::WhiteSpace), M(TermType::WhiteSpace)}, {M(TermType::WhiteSpace)}},
        {Term(TermType::WhiteSpace, " ")});

    return getStringWithoutStartingAndTrailingWhiteSpace(getCombinedContents(terms));
}

string getFunctionName(string const& functionSignature) {
    Terms terms(getTermsFromString(functionSignature));
    Patterns const searchPatterns{{M(TermType::Identifier), M("(")}};
    Indexes hitIndexes = searchForwardsForPatterns(terms, 0, searchPatterns);
    if (!hitIndexes.empty()) {
        return terms[hitIndexes.front()].getContent();
    }
    return {};
}

string getTextWithoutCommentsWithNewLine(Terms const& terms) {
    Terms revisedTerms(terms);
    Patterns const removePatterns{{M(MatcherType::Comment), M(MatcherType::WhiteSpaceWithNewLine)}};
    replaceAllForwards(revisedTerms, 0, removePatterns, {});
    return getCombinedContents(revisedTerms);
}

bool isCppFileExtension(string const& extension) {
    return extension == "cpp" || extension == "c" || extension == "cc" || extension == "hpp" || extension == "h";
}

bool isHeaderFileExtension(string const& extension) { return extension == "hpp" || extension == "h"; }

bool isImplementationFileExtension(string const& extension) {
    return extension == "cpp" || extension == "c" || extension == "cc";
}

}  // namespace alba::CodeUtilities::CPlusPlusUtilities
