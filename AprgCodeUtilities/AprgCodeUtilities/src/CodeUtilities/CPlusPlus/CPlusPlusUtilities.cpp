#include "CPlusPlusUtilities.hpp"

#include <CodeUtilities/CPlusPlus/CPlusPlusTokenizer.hpp>
#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <iostream>

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

Terms getTermsFromString(string const& code) {
    Terms result;
    CPlusPlusTokenizer tokenizer(result);
    tokenizer.processCode(code);
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

}  // namespace alba::CodeUtilities::CPlusPlusUtilities
