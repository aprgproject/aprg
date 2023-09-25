#include "CPlusPlusTokenizer.hpp"

#include <CodeUtilities/CPlusPlus/CPlusPlusConstants.hpp>
#include <CodeUtilities/Common/Term/TermCreateHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <algorithm>

using namespace alba;
using namespace alba::stringHelper;
using namespace std;

namespace {

using RecognizedItems = vector<string>;
RecognizedItems const recognizedKeywords{CPLUSPLUS_KEYWORDS, KEYWORD_OPERATORS};
RecognizedItems const recognizedPrimitiveTypes{PRIMITIVE_TYPES};
RecognizedItems const recognizedThreeCharOperators{THREE_CHAR_OPERATORS};
RecognizedItems const recognizedTwoCharOperators{TWO_CHAR_OPERATORS};
RecognizedItems const recognizedOneCharOperators{ONE_CHAR_OPERATORS};

bool isRecognized(RecognizedItems const& recognizedItems, string const& searchString) {
    return any_of(recognizedItems.cbegin(), recognizedItems.cend(), [searchString](string const& recognizedItem) {
        return recognizedItem == searchString;
    });
}

bool isRecognizedKeyword(string const& searchString) { return isRecognized(recognizedKeywords, searchString); }

bool isRecognizedPrimitiveType(string const& searchString) {
    return isRecognized(recognizedPrimitiveTypes, searchString);
}

bool isRecognizedThreeCharOperators(string const& searchString) {
    return isRecognized(recognizedThreeCharOperators, searchString);
}

bool isRecognizedTwoCharOperators(string const& searchString) {
    return isRecognized(recognizedTwoCharOperators, searchString);
}

bool isRecognizedOneCharOperators(string const& searchString) {
    return isRecognized(recognizedOneCharOperators, searchString);
}

}  // namespace

namespace alba::CodeUtilities {

CPlusPlusTokenizer::CPlusPlusTokenizer(Terms& terms) : m_terms(terms) {}

void CPlusPlusTokenizer::processCode(string const& code) {
    m_code.append(code);
    processCode();
}

void CPlusPlusTokenizer::processLeftoverCode() {
    switch (getCurrentScope()) {
        case ScopeType::SingleLineComment:
            m_terms.emplace_back(createCommentSingleLine(m_scopeContent));
            break;
        case ScopeType::MultiLineComment:
            m_terms.emplace_back(createCommentMultiLine(m_scopeContent));
            break;
        case ScopeType::StringLiteral:
        case ScopeType::RawStringLiteral:
            m_terms.emplace_back(createStringLiteral(m_scopeContent));
            break;
        case ScopeType::CharLiteral:
            m_terms.emplace_back(createCharacterLiteral(m_scopeContent));
            break;
        case ScopeType::Attribute:
            m_terms.emplace_back(createAttribute(m_scopeContent));
            break;
        case ScopeType::WhiteSpace:
            m_terms.emplace_back(createWhiteSpace(m_scopeContent));
            break;
        default:
            break;
    }
    m_scopeContent.clear();
    m_scopes.clear();
}

CPlusPlusTokenizer::ScopeType CPlusPlusTokenizer::getCurrentScope() const {
    return !m_scopes.empty() ? m_scopes.back() : ScopeType::NoScope;
}

string CPlusPlusTokenizer::getIndentifierAt(int const index) const {
    string result;
    if (isLetterOrUnderscore(m_code[index])) {
        result += m_code[index];
        result += getAlphaNumericUnderscoreStringAt(index + 1);
    }
    return result;
}

string CPlusPlusTokenizer::getNumberAt(int const index) const {
    string result;
    if (isNumber(m_code[index])) {
        result += m_code[index];
        result += getContinuousDigitsAt(index + 1);
    }
    return result;
}

string CPlusPlusTokenizer::getAlphaNumericUnderscoreStringAt(int const index) const {
    string result;
    for (int identifierIndex = index;
         identifierIndex < static_cast<int>(m_code.length()) && isLetterOrNumberOrUnderscore(m_code[identifierIndex]);
         ++identifierIndex) {
        result += m_code[identifierIndex];
    }
    return result;
}

string CPlusPlusTokenizer::getContinuousDigitsAt(int const index) const {
    string result;
    for (int identifierIndex = index;
         identifierIndex < static_cast<int>(m_code.length()) &&
         (isLetterOrNumberOrUnderscore(m_code[identifierIndex]) || m_code[identifierIndex] == '\'');
         ++identifierIndex) {
        result += m_code[identifierIndex];
    }
    return result;
}

bool CPlusPlusTokenizer::isNextString(string const& expectedString) const {
    if (m_index + expectedString.length() <= m_code.length()) {
        return expectedString == m_code.substr(m_index, expectedString.length());
    }
    return false;
}

bool CPlusPlusTokenizer::isIndentifierStartAt(int const index) const {
    if (index < static_cast<int>(m_code.length())) {
        return isLetterOrUnderscore(m_code[index]);
    }
    return false;
}

bool CPlusPlusTokenizer::isNumberAt(int const index) const {
    if (index < static_cast<int>(m_code.length())) {
        return isNumber(m_code[index]);
    }
    return false;
}

bool CPlusPlusTokenizer::isOperatorAt(int const index) const {
    if (index < static_cast<int>(m_code.length())) {
        char const character = m_code[index];
        return isDisplayableCharacter(character) && !isLetterOrNumberOrUnderscore(character) &&
               !isWhiteSpace(character);
    }
    return false;
}

bool CPlusPlusTokenizer::isThreeCharOperatorAt(int const index) const {
    if (index + 2 < static_cast<int>(m_code.length())) {
        string const possibleOperator = m_code.substr(index, 3);
        return isRecognizedThreeCharOperators(possibleOperator);
    }
    return false;
}

bool CPlusPlusTokenizer::isTwoCharOperatorAt(int const index) const {
    if (index + 1 < static_cast<int>(m_code.length())) {
        string const possibleOperator = m_code.substr(index, 2);
        return isRecognizedTwoCharOperators(possibleOperator);
    }
    return false;
}

bool CPlusPlusTokenizer::isOneCharOperatorAt(int const index) const {
    if (index < static_cast<int>(m_code.length())) {
        string const possibleOperator = m_code.substr(index, 1);
        return isRecognizedOneCharOperators(possibleOperator);
    }
    return false;
}

bool CPlusPlusTokenizer::isWhiteSpaceAt(int const index) const {
    if (index < static_cast<int>(m_code.length())) {
        return isWhiteSpace(m_code[index]);
    }
    return false;
}

void CPlusPlusTokenizer::processCode() {
    while (m_index < static_cast<int>(m_code.length())) {
        processScope();
    }
}

void CPlusPlusTokenizer::processScope() {
    switch (getCurrentScope()) {
        case ScopeType::SingleLineComment:
            processInSingleLineCommentScope();
            break;
        case ScopeType::MultiLineComment:
            processInMultiLineCommentScope();
            break;
        case ScopeType::StringLiteral:
            processInStringLiteralScope();
            break;
        case ScopeType::RawStringLiteral:
            processInRawStringLiteralScope();
            break;
        case ScopeType::CharLiteral:
            processInCharLiteralScope();
            break;
        case ScopeType::Attribute:
            processInAttributeScope();
            break;
        case ScopeType::WhiteSpace:
            processInWhiteSpaceScope();
            break;
        default:
            processInCodeScope();
            break;
    }
}

void CPlusPlusTokenizer::processInCodeScope() {
    // NOLINTBEGIN(bugprone-branch-clone)
    if (hasProcessedASingleLineComment()) {
        ;
    } else if (hasProcessedAMultiLineComment()) {
        ;
    } else if (hasProcessedAStringLiteral()) {
        ;
    } else if (hasProcessedARawStringLiteral()) {
        ;
    } else if (hasProcessedACharLiteral()) {
        ;
    } else if (hasProcessedAnAttribute()) {
        ;
    } else if (hasProcessedAWhiteSpace()) {
        ;
    } else if (hasProcessedAMacro()) {
        ;
    } else if (hasProcessedANumber()) {
        ;
    } else if (hasProcessedAnIdentifier()) {
        ;
    } else if (hasProcessedAnOperator()) {
        ;
    } else {
        m_terms.emplace_back(createUnknown(m_code.substr(m_index++)));
    }
    // NOLINTEND(bugprone-branch-clone)
}

void CPlusPlusTokenizer::processInSingleLineCommentScope() {
    if (isTerminatedWhileCheckingTerminatingString("\n")) {
        m_terms.emplace_back(createCommentSingleLine(m_scopeContent));
        exitScope();
    }
}

void CPlusPlusTokenizer::processInMultiLineCommentScope() {
    if (isTerminatedWhileCheckingTerminatingString("*/")) {
        m_scopeContent.append("*/");
        m_index += 2;
        m_terms.emplace_back(createCommentMultiLine(m_scopeContent));
        exitScope();
    }
}

void CPlusPlusTokenizer::processInStringLiteralScope() {
    if (isTerminatedWhileCheckingALiteralWithEscape('\"')) {
        m_terms.emplace_back(createStringLiteral(m_scopeContent));
        exitScope();
    }
}

void CPlusPlusTokenizer::processInRawStringLiteralScope() {
    if (isTerminatedWhileCheckingTerminatingString(")\"")) {
        m_scopeContent.append(")\"");
        m_index += 2;
        m_terms.emplace_back(createStringLiteral(m_scopeContent));
        exitScope();
    }
}

void CPlusPlusTokenizer::processInCharLiteralScope() {
    if (isTerminatedWhileCheckingALiteralWithEscape('\'')) {
        m_terms.emplace_back(createCharacterLiteral(m_scopeContent));
        exitScope();
    }
}

void CPlusPlusTokenizer::processInAttributeScope() {
    if (isTerminatedWhileCheckingTerminatingString("]]")) {
        m_scopeContent.append("]]");
        m_index += 2;
        m_terms.emplace_back(createAttribute(m_scopeContent));
        exitScope();
    }
}

void CPlusPlusTokenizer::processInWhiteSpaceScope() {
    if (isTerminatedWhileCheckingWhiteSpace()) {
        m_terms.emplace_back(createWhiteSpace(m_scopeContent));
        exitScope();
    }
}

void CPlusPlusTokenizer::enterScope(ScopeType const scopeType) { m_scopes.emplace_back(scopeType); }

void CPlusPlusTokenizer::exitScope() {
    m_scopeContent.clear();
    m_scopes.pop_back();
}

bool CPlusPlusTokenizer::hasProcessedASingleLineComment() {
    if (isNextString("//")) {
        m_scopeContent.append("//");
        m_index += 2;
        enterScope(ScopeType::SingleLineComment);
        processInSingleLineCommentScope();
        return true;
    }
    return false;
}

bool CPlusPlusTokenizer::hasProcessedAMultiLineComment() {
    if (isNextString("/*")) {
        m_scopeContent.append("/*");
        m_index += 2;
        enterScope(ScopeType::MultiLineComment);
        processInMultiLineCommentScope();
        return true;
    }
    return false;
}

bool CPlusPlusTokenizer::hasProcessedAStringLiteral() {
    if (isNextString(R"(")")) {
        m_scopeContent += '\"';
        ++m_index;
        enterScope(ScopeType::StringLiteral);
        processInStringLiteralScope();
        return true;
    }
    return false;
}

bool CPlusPlusTokenizer::hasProcessedARawStringLiteral() {
    if (isNextString("R\"(")) {
        m_scopeContent += "R\"(";
        m_index += 3;
        enterScope(ScopeType::RawStringLiteral);
        processInRawStringLiteralScope();
        return true;
    }
    return false;
}

bool CPlusPlusTokenizer::hasProcessedACharLiteral() {
    if (isNextString(R"(')")) {
        m_scopeContent += '\'';
        ++m_index;
        enterScope(ScopeType::CharLiteral);
        processInCharLiteralScope();
        return true;
    }
    return false;
}

bool CPlusPlusTokenizer::hasProcessedAnAttribute() {
    if (isNextString("[[")) {
        m_scopeContent.append("[[");
        m_index += 2;
        enterScope(ScopeType::Attribute);
        processInAttributeScope();
        return true;
    }
    return false;
}

bool CPlusPlusTokenizer::hasProcessedAWhiteSpace() {
    if (isWhiteSpaceAt(m_index)) {
        enterScope(ScopeType::WhiteSpace);
        processInWhiteSpaceScope();
        return true;
    }
    return false;
}

bool CPlusPlusTokenizer::hasProcessedAMacro() {
    if (isNextString("#") && isIndentifierStartAt(m_index + 1)) {
        string const termString = string("#") + getIndentifierAt(m_index + 1);
        m_index += static_cast<int>(termString.length());
        m_terms.emplace_back(createMacro(termString));
        return true;
    }
    return false;
}

bool CPlusPlusTokenizer::hasProcessedANumber() {
    if (isNumberAt(m_index)) {
        string const termString = getNumberAt(m_index);
        m_index += static_cast<int>(termString.length());
        m_terms.emplace_back(createNumber(termString));
        return true;
    }
    return false;
}

bool CPlusPlusTokenizer::hasProcessedAnIdentifier() {
    if (isIndentifierStartAt(m_index)) {
        string const termString = getIndentifierAt(m_index);
        m_index += static_cast<int>(termString.length());
        if (isRecognizedPrimitiveType(termString)) {
            m_terms.emplace_back(createPrimitiveType(termString));
        } else if (termString == "true" || termString == "false") {
            m_terms.emplace_back(createBoolean(termString));
        } else if (isRecognizedKeyword(termString)) {
            m_terms.emplace_back(createKeyword(termString));
        } else {
            m_terms.emplace_back(createIdentifier(termString));
        }
        return true;
    }
    return false;
}

bool CPlusPlusTokenizer::hasProcessedAnOperator() {
    if (isOperatorAt(m_index)) {
        string termString;
        if (isThreeCharOperatorAt(m_index)) {
            termString = m_code.substr(m_index, 3);
        } else if (isTwoCharOperatorAt(m_index)) {
            termString = m_code.substr(m_index, 2);
        } else {
            termString = m_code.substr(m_index, 1);
        }
        m_index += static_cast<int>(termString.length());
        m_terms.emplace_back(createOperator(termString));
        return true;
    }
    return false;
}

bool CPlusPlusTokenizer::isTerminatedWhileCheckingWhiteSpace() {
    for (; m_index < static_cast<int>(m_code.length()) && isWhiteSpace(m_code[m_index]); ++m_index) {
        m_scopeContent += m_code[m_index];
    }
    return m_index < static_cast<int>(m_code.length()) && !isWhiteSpace(m_code[m_index]);
}

bool CPlusPlusTokenizer::isTerminatedWhileCheckingALiteralWithEscape(char const terminatingCharacter) {
    bool isTerminated(false);
    int numberSlashes = 0;
    for (; m_index < static_cast<int>(m_code.length()); ++m_index) {
        char const character = m_code[m_index];
        if (character == '\\') {
            ++numberSlashes;
            if (numberSlashes == 2) {
                m_scopeContent.append("\\\\");
                numberSlashes = 0;
            }
        } else if (character == terminatingCharacter) {
            if (numberSlashes == 1) {
                m_scopeContent += '\\';
                m_scopeContent += character;
                numberSlashes = 0;
            } else {
                m_scopeContent += character;
                isTerminated = true;
                ++m_index;
                break;
            }
        } else {
            if (numberSlashes == 1) {
                m_scopeContent += '\\';
                numberSlashes = 0;
            }
            m_scopeContent += character;
        }
    }
    if (numberSlashes == 1) {
        m_scopeContent += '\\';
    }
    return isTerminated;
}

bool CPlusPlusTokenizer::isTerminatedWhileCheckingTerminatingString(string const& terminatingString) {
    auto searchIndex = static_cast<int>(m_code.find(terminatingString, m_index));
    if (isNotNpos(searchIndex)) {
        m_scopeContent.append(m_code.substr(m_index, searchIndex - m_index));
        m_index = searchIndex;
        return true;
    }
    m_scopeContent.append(m_code.substr(m_index, m_code.length() - m_index));
    m_index = static_cast<int>(m_code.length());
    return false;
}

}  // namespace alba::CodeUtilities
