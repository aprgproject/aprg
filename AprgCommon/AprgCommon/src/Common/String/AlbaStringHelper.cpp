#include "AlbaStringHelper.hpp"

#include <Common/Container/AlbaContainerHelper.hpp>
#include <Common/Math/Helpers/PowerHelpers.hpp>
#include <Common/Randomizer/AlbaUniformNonDeterministicRandomizer.hpp>

#include <algorithm>
#include <cstring>
#include <functional>
#include <numeric>
#include <set>
#include <sstream>

using namespace alba::mathHelper;
using namespace std;

namespace alba::stringHelper {

void copyBeforeStringAndAfterString(
    string_view const mainText, string_view const stringToSearch, string& beforeString, string& afterString,
    size_t const indexToStartTheSearch) {
    beforeString.clear();
    afterString.clear();
    size_t const firstIndexOfFirstString = mainText.find(stringToSearch, indexToStartTheSearch);
    if (isNotNpos(static_cast<int>(firstIndexOfFirstString))) {
        size_t const lastIndexOfFirstString = firstIndexOfFirstString + stringToSearch.length();
        beforeString = mainText.substr(0, firstIndexOfFirstString);
        afterString = mainText.substr(lastIndexOfFirstString);
    }
}

string getStringWithCapitalLetters(string_view const str) {
    string result;
    result.resize(str.length());
    transform(begin(str), end(str), begin(result), ::toupper);
    return result;
}

string getStringWithFirstNonWhiteSpaceCharacterToCapital(string_view const str) {
    string result(str);
    size_t const resultLength = result.length();
    for (size_t index1 = 0; index1 < resultLength; ++index1) {
        if (!isWhiteSpace(result[index1])) {
            result[index1] = static_cast<char>(::toupper(result[index1]));
            break;
        }
    }
    return result;
}

string getStringWithLowerCaseLetters(string_view const str) {
    string result;
    result.resize(str.length());
    transform(begin(str), end(str), begin(result), ::tolower);
    return result;
}

string getStringWithUrlDecodedString(string_view const str) {
    string result;
    size_t index = 0;
    size_t const length = str.length();
    while (index < length) {
        if (str[index] == '%' && (static_cast<int>(index) < static_cast<int>(length) - 2) &&
            isHexDigit(str[index + 1]) && isHexDigit(str[index + 2])) {
            result += convertHexStringToNumber<char>(str.substr(index + 1, 2));
            index += 3;
        } else {
            result += str[index++];
        }
    }
    return result;
}

string getStringThatContainsWhiteSpaceIndention(string_view const str) {
    string result;
    size_t const firstIndexOfNotOfCharacters(str.find_first_not_of(WHITESPACE_STRING));
    if (isNotNpos(static_cast<int>(firstIndexOfNotOfCharacters))) {
        result = str.substr(0, firstIndexOfNotOfCharacters);
    }
    return result;
}

string getStringWithoutStartingAndTrailingCharacters(string_view const str, string_view const characters) {
    string result(str);
    size_t const firstIndexOfNotOfCharacters(result.find_first_not_of(characters));
    if (isNotNpos(static_cast<int>(firstIndexOfNotOfCharacters))) {
        result.erase(0, firstIndexOfNotOfCharacters);
        size_t const lastIndexOfOfNotOfCharacters(result.find_last_not_of(characters));
        if (isNotNpos(static_cast<int>(lastIndexOfOfNotOfCharacters))) {
            result.erase(lastIndexOfOfNotOfCharacters + 1);
        }
    } else {
        result.clear();
    }
    return result;
}

string getStringWithoutStartingAndTrailingWhiteSpace(string_view const str) {
    return getStringWithoutStartingAndTrailingCharacters(str, WHITESPACE_STRING);
}

string getStringWithoutWhiteSpace(string_view const str) {
    string result;
    size_t index = 0;
    size_t const length = str.length();
    while (index < length) {
        if (!isWhiteSpace(str[index])) {
            result += str[index];
        }
        ++index;
    }
    return result;
}

string getStringWithoutRedundantWhiteSpace(string_view const str) {
    string result;
    size_t index = 0;
    size_t const length = str.length();
    while (index < length) {
        size_t const indexNotWhiteSpace = str.find_first_not_of(WHITESPACE_STRING, index);
        if (isNpos(static_cast<int>(indexNotWhiteSpace))) {
            break;
        }
        size_t const indexWhiteSpace = str.find_first_of(WHITESPACE_STRING, indexNotWhiteSpace);
        index = (isNotNpos(static_cast<int>(indexWhiteSpace))) ? indexWhiteSpace : length;
        result += (!result.empty()) ? " "s : string();
        result += str.substr(indexNotWhiteSpace, index - indexNotWhiteSpace);
    }
    return result;
}

string getStringWithoutQuotations(string_view const str) {
    size_t const length = str.length();
    if (length > 2 && str[0] == '\"' && str[length - 1] == '\"') {
        return string(str.substr(1, length - 2));
    }
    return string(str);
}

string getStringWithoutCharAtTheStartAndEnd(string_view const str, char const char1) {
    return getStringWithoutCharAtTheStart(getStringWithoutCharAtTheEnd(str, char1), char1);
}

string getStringWithoutCharAtTheStart(string_view const str, char const char1) {
    size_t const length = str.length();
    size_t const start = (str[0] == char1) ? 1 : 0;
    return string(str.substr(start, length - start));
}

string getStringWithoutCharAtTheEnd(string_view const str, char const char1) {
    size_t const length = str.length();
    size_t const end = (length == 0) ? 0 : (str[length - 1] == char1) ? length - 1 : length;
    return string(str.substr(0, end));
}

string getStringWithoutOpeningClosingOperators(
    string_view const str, char const openingOperator, char const closingOperator) {
    size_t const length = str.length();
    size_t const start = (str[0] == openingOperator) ? 1 : 0;
    size_t const end = (length == 0) ? 0 : (str[length - 1] == closingOperator) ? length - 1 : length;
    return string(str.substr(start, end - start));
}

string getLongestCommonPrefix(string_view const first, string_view const second) {
    size_t index1 = 0;
    for (; index1 < first.length() && index1 < second.length(); ++index1) {
        if (first[index1] != second[index1]) {
            break;
        }
    }
    return string(first.substr(0, index1));
}

string getStringBeforeThisString(
    string_view const mainText, string_view const stringToSearch, size_t const indexToStart) {
    string result;
    size_t const firstIndexOfFirstString = mainText.find(stringToSearch, indexToStart);
    if (isNotNpos(static_cast<int>(firstIndexOfFirstString))) {
        result = mainText.substr(indexToStart, firstIndexOfFirstString - indexToStart);
    }
    return result;
}

string getStringAfterThisString(
    string_view const mainText, string_view const stringToSearch, size_t const indexToStart) {
    string result;
    size_t const firstIndexOfFirstString = mainText.find(stringToSearch, indexToStart);
    if (isNotNpos(static_cast<int>(firstIndexOfFirstString))) {
        size_t const lastIndexOfFirstString = firstIndexOfFirstString + stringToSearch.length();
        result = mainText.substr(lastIndexOfFirstString);
    }
    return result;
}

string getStringInBetweenTwoStrings(
    string_view const mainText, string_view const firstString, string_view const secondString,
    size_t const indexToStart) {
    string result;
    size_t const firstIndexOfFirstString = mainText.find(firstString, indexToStart);
    if (isNotNpos(static_cast<int>(firstIndexOfFirstString))) {
        size_t const lastIndexOfFirstString = firstIndexOfFirstString + firstString.length();
        size_t const firstIndexOfSecondString = mainText.find(secondString, lastIndexOfFirstString);
        if (isNotNpos(static_cast<int>(firstIndexOfSecondString))) {
            result = mainText.substr(lastIndexOfFirstString, firstIndexOfSecondString - lastIndexOfFirstString);
        }
    }
    return result;
}

string getStringBeforeThisCharacters(
    string_view const mainText, string_view const characters, size_t const indexToStart) {
    string result;
    size_t const firstIndexOfNotOfCharacters(mainText.find_first_of(characters, indexToStart));
    if (isNotNpos(static_cast<int>(firstIndexOfNotOfCharacters))) {
        result = mainText.substr(indexToStart, firstIndexOfNotOfCharacters - indexToStart);
    }
    return result;
}

string getStringAndReplaceNonAlphanumericCharactersToUnderScore(string_view const path) {
    bool isPreviousCharacterNonAlphanumeric = false;
    string correctPath = accumulate(
        path.cbegin(), path.cend(), string(),
        [&isPreviousCharacterNonAlphanumeric](string_view const currentString, char const currentCharacter) {
            string partialResult(currentString);
            if (!isLetterOrNumber(currentCharacter)) {
                if (!isPreviousCharacterNonAlphanumeric) {
                    partialResult += "_"s;
                }
            } else {
                partialResult += currentCharacter;
            }
            isPreviousCharacterNonAlphanumeric = !isLetterOrNumber(currentCharacter);
            return partialResult;
        });
    return correctPath;
}

string getStringByRepeatingUntilDesiredLength(string_view const stringToRepeat, size_t const desiredLength) {
    string result;
    if (!stringToRepeat.empty()) {
        size_t const stringToRepeatLength = stringToRepeat.length();
        for (size_t index = 0; index <= desiredLength; index += stringToRepeatLength) {
            result += stringToRepeat;
        }
        result = result.substr(0, desiredLength);
    }
    return result;
}

string getNumberAfterThisString(string_view const mainText, string_view const stringToSearch) {
    string result;
    size_t const firstIndexOfFirstString = mainText.find(stringToSearch);
    if (isNotNpos(static_cast<int>(firstIndexOfFirstString))) {
        size_t const lastIndexOfFirstString = firstIndexOfFirstString + stringToSearch.length();
        size_t lastIndexOfNumber(lastIndexOfFirstString);
        for (; lastIndexOfNumber < mainText.length() && isNumber(mainText[lastIndexOfNumber]); ++lastIndexOfNumber) {
        }
        result = mainText.substr(lastIndexOfFirstString, lastIndexOfNumber - lastIndexOfFirstString);
    }
    return result;
}

string getHexNumberAfterThisString(string_view const mainText, string_view const stringToSearch) {
    string result;
    size_t const firstIndexOfFirstString = mainText.find(stringToSearch);
    if (isNotNpos(static_cast<int>(firstIndexOfFirstString))) {
        size_t const lastIndexOfFirstString = firstIndexOfFirstString + stringToSearch.length();
        size_t lastIndexOfNumber(lastIndexOfFirstString);
        for (; lastIndexOfNumber < mainText.length() && isHexDigit(mainText[lastIndexOfNumber]); ++lastIndexOfNumber) {
        }
        result = mainText.substr(lastIndexOfFirstString, lastIndexOfNumber - lastIndexOfFirstString);
    }
    return result;
}

string getHexEquivalentOfCharacters(string_view const stringToCheck) {
    stringstream bufferStream;
    for (unsigned char const character : stringToCheck) {
        bufferStream << hex << uppercase << setfill('0') << setw(2) << static_cast<uint64_t>(character);
    }
    return bufferStream.str();
}

string getQuotedString(string_view const stringToCheck) {
    stringstream bufferStream;
    bufferStream << quoted(string(stringToCheck));  // remove temporary string object when quoted has string view
    return bufferStream.str();
}

string constructFileLocator(string_view const file, int const lineNumber) {
    stringstream bufferStream;
    bufferStream << file.substr(file.find_last_of('\\') + 1) << "[" << lineNumber << "]";
    return bufferStream.str();
}

string getRandomAlphaNumericString(size_t const length) {
    constexpr auto ALPHA_NUMERIC_CHAR_MAP = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    string_view alphaNumericView{ALPHA_NUMERIC_CHAR_MAP};
    AlbaUniformNonDeterministicRandomizer randomizer(0, static_cast<int>(alphaNumericView.size()) - 1);
    string result;
    result.reserve(length);
    generate_n(back_inserter(result), length, [&]() {
        return alphaNumericView[static_cast<size_t>(randomizer.getRandomValue())];
    });
    return result;
}

// NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,hicpp-avoid-c-arrays,modernize-avoid-c-arrays)
strings getArgumentsToStringInMain(int const argc, char const* const argv[]) {
    strings result;
    for (int argumentIndex = 0; argumentIndex < argc; ++argumentIndex) {
        result.emplace_back(argv[argumentIndex]);
    }
    return result;
}

int getNumberOfNewLines(string_view const str) {
    return accumulate(cbegin(str), cend(str), 0, [](int const partialResult, char const character) {
        if (character == '\n') {
            return partialResult + 1;
        }
        return partialResult;
    });
}

int getRotationValue(string_view const str, string_view const rotation) {
    // A rotation can be generated by moving the characters of a string one by one from the beginning to the end (or
    // vice versa). For example, the rotations of ABCD are ABCD, BCDA, CDAB and DABC.
    int result = static_cast<int>(string::npos);
    if (str.length() == rotation.length()) {
        string doubleMainString(str);
        doubleMainString += doubleMainString;
        result = static_cast<int>(doubleMainString.find(rotation));
    }
    return result;
}

int getPeriodValue(string_view const str, string_view const period) {
    // A period is a prefix of a string such that the string can be constructed by repeating the period.
    // The last repetition may be partial and contain only a prefix of the period.
    // For example, the shortest period of ABCABCA is ABC.
    int periodCount(0);
    if (!period.empty()) {
        for (size_t index1(0U), index2(0U); index1 < str.length(); ++index1, ++index2) {
            if (index2 == period.length()) {
                index2 = 0;
                ++periodCount;
            }
            if (str[index1] != period[index2]) {
                periodCount = 0;
                break;
            }
        }
    }
    return (periodCount > 0) ? periodCount : static_cast<int>(string::npos);
}

size_t generateUniqueId(string_view const str) {
    return accumulate(begin(str), end(str), 1ULL, [](size_t const accumulatedChar, uint8_t const character) {
        return (accumulatedChar * character) + 1;
    });
}

size_t getLevenshteinDistance(string_view const otherString, string_view const basisString) {
    // The edit distance or Levenshtein distance is the minimum number of editing operations needed to transform a
    // string into another string. The allowed editing operations are as follows:
    // -> insert a character (e.g. ABC ! ABCA)
    // -> remove a character (e.g. ABC ! AC)
    // -> modify a character (e.g. ABC ! ADC)
    using Counts = vector<size_t>;

    vector<Counts> previousAndCurrentCounts(2, Counts(basisString.length() + 1));  // string1 as basis
    Counts& firstPrevious(previousAndCurrentCounts[0]);
    iota(begin(firstPrevious), end(firstPrevious), 0);  // first row
    for (size_t otherIndex = 1; otherIndex <= otherString.length(); ++otherIndex) {
        Counts& previousCounts(previousAndCurrentCounts[(otherIndex - 1) % 2]);
        Counts& currentCounts(previousAndCurrentCounts[otherIndex % 2]);

        currentCounts[0] = otherIndex;  // first column
        for (size_t basisIndex = 1; basisIndex <= basisString.length(); ++basisIndex) {
            size_t const cost = basisString[basisIndex - 1] == otherString[otherIndex - 1] ? 0 : 1;
            currentCounts[basisIndex] =
                min(min(currentCounts[basisIndex - 1] + 1, previousCounts[basisIndex] + 1),
                    previousCounts[basisIndex - 1] + cost);
        }
    }

    Counts const& lastCurrent(previousAndCurrentCounts[otherString.length() % 2]);
    return lastCurrent.back();
}

size_t getHammingDistance(string_view const string1, string_view const string2) {
    // The Hamming distance hamming(a,b) between two strings a and b of equal length is the number of positions where
    // the strings differ.
    size_t result(0);
    size_t const commonLength = min(string1.length(), string2.length());
    for (size_t index1 = 0; index1 < commonLength; ++index1) {
        if (string1[index1] != string2[index1]) {
            ++result;
        }
    }
    return result;
}

size_t getNumberOfSubStrings(string_view const str) {
    // A string of length n has n(n+1)/2 substrings.
    size_t const length = str.length();
    return length * (length + 1) / 2;
}

size_t getNumberOfSubsequences(string_view const str) {
    // A string of length n has 2^n - 1 subsequences.
    return static_cast<size_t>(get2ToThePowerOf(str.length()) - 1);
}

bool isNumber(string_view const str) {
    return any_of(begin(str), end(str), [](char const character) { return isNumber(character); });
}

bool isWhiteSpace(string_view const str) {
    return all_of(begin(str), end(str), [](char const character) { return isWhiteSpace(character); });
}

bool isNewLine(string_view const str) {
    return all_of(begin(str), end(str), [](char const character) { return isNewLine(character); });
}

bool hasNewLine(string_view const str) {
    return any_of(begin(str), end(str), [](char const character) { return isNewLine(character); });
}

bool isIdentifier(string_view const str) {
    bool isIdentifier(false);
    if (!str.empty()) {
        char const firstCharacter = str.front();
        isIdentifier = isLetter(firstCharacter) || isUnderscore(firstCharacter);
    }
    return isIdentifier;
}

bool isOneWord(string_view const str) {
    return (!str.empty()) &&
           none_of(begin(str), end(str), [](char const character) { return isWhiteSpace(character); });
}

bool isPalindrome(string_view const str) {
    bool result(false);
    if (!str.empty()) {
        result = true;
        size_t left(0);
        size_t right(str.length() - 1);
        while (left < right) {
            if (str[left++] != str[right--]) {
                result = false;
                break;
            }
        }
    }
    return result;
}

bool isSubstring(string_view const mainText, string_view const subString) {
    // A substring is a sequence of consecutive characters in a string.
    // We use the notation s[a...b] to refer to a substring of s that begins at position a and ends at position b.
    // A string of length n has n(n+1)/2 substrings.
    // For example, the substrings of ABCD are A, B, C, D, AB, BC, CD, ABC, BCD and ABCD.
    // NOTE: This is the same as: isStringFoundCaseSensitive
    return isNotNpos(static_cast<int>(mainText.find(subString)));
}

bool isSubsequence(string_view const mainText, string_view const subsequence) {
    // A subsequence is a sequence of (not necessarily consecutive) characters in a string in their original order.
    // A string of length n has 2n-1 subsequences.
    // For example, the subsequences of ABCD are A, B, C, D, AB, AC, AD, BC, BD, CD, ABC, ABD, ACD, BCD and ABCD.
    size_t index2(0U);
    for (size_t index1(0U); index1 < mainText.length() && index2 < subsequence.length(); ++index1) {
        if (mainText[index1] == subsequence[index2]) {
            ++index2;
        }
    }
    return index2 == subsequence.length();
}

bool isPrefix(string_view const mainText, string_view const prefix) {
    // A prefix is a substring that starts at the beginning of a string.
    // For example, the prefixes of ABCD are A, AB, ABC and ABCD.
    size_t index2(0U);
    for (size_t index1(0U); index1 < mainText.length() && index2 < prefix.length(); ++index1, ++index2) {
        if (mainText[index1] != prefix[index2]) {
            break;
        }
    }
    return index2 == prefix.length();
}

bool isSuffix(string_view const mainText, string_view const suffix) {
    // A suffix is a substring that ends at the end of a string.
    // For example, the suffixes of ABCD are D, CD, BCD and ABCD.
    int index2 = static_cast<int>(suffix.length()) - 1;
    for (int index1 = static_cast<int>(mainText.length()) - 1; index1 >= 0 && index2 >= 0; --index1, --index2) {
        if (mainText[index1] != suffix[index2]) {
            break;
        }
    }
    return index2 == -1;
}

bool isRotation(string_view const mainText, string_view const rotation) {
    // A rotation can be generated by moving the characters of a string one by one from the beginning to the end (or
    // vice versa). For example, the rotations of ABCD are ABCD, BCDA, CDAB and DABC.
    return isNotNpos(getRotationValue(mainText, rotation));
}

bool isPeriod(string_view const mainText, string_view const period) {
    // A period is a prefix of a string such that the string can be constructed by repeating the period.
    // The last repetition may be partial and contain only a prefix of the period.
    // For example, the shortest period of ABCABCA is ABC.
    return isNotNpos(getPeriodValue(mainText, period));
}

bool isBorder(string_view const text, string_view const border) {
    // A border is a string that is both a prefix and a suffix of a string.
    // For example, the borders of ABACABA are A, ABA and ABACABA.
    return isPrefix(text, border) && isSuffix(text, border);
}

bool isEqualNotCaseSensitive(string_view const str1, string_view const str2) {
    return getStringWithCapitalLetters(str1) == getStringWithCapitalLetters(str2);
}

bool isEqualWithLowestCommonLength(string_view const str1, string_view const str2) {
    size_t const length1 = str1.length();
    size_t const length2 = str2.length();
    size_t const lowestLength = (length1 > length2) ? length2 : length1;
    return str1.substr(0, lowestLength) == str2.substr(0, lowestLength);
}

bool isStringFoundCaseSensitive(string_view const mainText, string_view const stringToSearch) {
    return isNotNpos(static_cast<int>(mainText.find(stringToSearch)));
}

bool isStringFoundCaseSensitive(string_view const mainText, string_view const stringToSearch, int& runningOffset) {
    int const foundIndex = static_cast<int>(mainText.find(stringToSearch, runningOffset));
    bool const isFound = isNotNpos(foundIndex);
    if (isFound) {
        runningOffset = foundIndex + static_cast<int>(stringToSearch.length());
    }
    return isFound;
}

bool isStringFoundNotCaseSensitive(string_view const mainText, string_view const stringToSearch) {
    return isStringFoundCaseSensitive(
        getStringWithCapitalLetters(mainText), getStringWithCapitalLetters(stringToSearch));
}

bool isWildcardMatch(
    string_view const mainText, string_view const wildcard, size_t const mainTextIndex, size_t const wildcardIndex) {
    bool result(false);
    bool const isMainStringDone = mainTextIndex >= mainText.size();
    bool const isWildcardDone = wildcardIndex >= wildcard.size();
    if (isMainStringDone && isWildcardDone) {
        result = true;
    } else if (isWildcardDone) {
        result = false;
    } else if (isMainStringDone) {
        bool const isWildcardDoneOnNextIndex = wildcardIndex + 1 >= wildcard.size();
        result = wildcard[wildcardIndex] == '*' && isWildcardDoneOnNextIndex;
    } else if (wildcard[wildcardIndex] == mainText[mainTextIndex]) {
        result = isWildcardMatch(mainText, wildcard, mainTextIndex + 1, wildcardIndex + 1);
    } else if (wildcard[wildcardIndex] == '?') {
        result = isWildcardMatch(mainText, wildcard, mainTextIndex + 1, wildcardIndex + 1) ||
                 isWildcardMatch(mainText, wildcard, mainTextIndex, wildcardIndex + 1);
    } else if (wildcard[wildcardIndex] == '*') {
        result = isWildcardMatch(mainText, wildcard, mainTextIndex, wildcardIndex + 1) ||
                 isWildcardMatch(mainText, wildcard, mainTextIndex + 1, wildcardIndex);
    }
    return result;
}

bool isCamelCase(string_view const str) {
    if (!str.empty()) {
        return isLowerCaseLetter(str.front()) &&
               all_of(begin(str), end(str), [](char const character) { return isLetterOrNumber(character); });
    }
    return false;
}

bool isPascalCase(string_view const str) {
    if (!str.empty()) {
        return isCapitalLetter(str.front()) &&
               all_of(begin(str), end(str), [](char const character) { return isLetterOrNumber(character); });
    }
    return false;
}

bool isSnakeCase(string_view const str) {
    if (!str.empty()) {
        return isLowerCaseLetter(str.front()) && all_of(begin(str), end(str), [](char const character) {
                   return isLowerCaseLetter(character) || isUnderscore(character);
               });
    }
    return false;
}

bool isKebabCase(string_view const str) {
    if (!str.empty()) {
        return isLowerCaseLetter(str.front()) && all_of(begin(str), end(str), [](char const character) {
                   return isLowerCaseLetter(character) || '-' == character;
               });
    }
    return false;
}

bool isScreamingSnakeCase(string_view const str) {
    if (!str.empty()) {
        return isCapitalLetter(str.front()) && all_of(begin(str), end(str), [](char const character) {
                   return isCapitalLetter(character) || isUnderscore(character);
               });
    }
    return false;
}

bool replaceAllAndReturnIfFound(string& mainText, string_view const targetStr, string_view const replacementStr) {
    bool found = false;
    size_t const targetStrLength = targetStr.length();
    size_t const replacementStrLength = replacementStr.length();
    size_t index = mainText.find(targetStr);
    while (isNotNpos(static_cast<int>(index))) {
        found = true;
        mainText.replace(index, targetStrLength, replacementStr);
        index = mainText.find(targetStr, index + replacementStrLength);
    }
    return found;
}

template <SplitStringType splitStringType>
void splitToStrings(strings& listOfStrings, string_view const mainText, string_view const delimiters) {
    size_t startingIndexOfFind(0);
    size_t delimiterIndex = mainText.find_first_of(delimiters);
    constexpr size_t delimeterLength = 1;
    size_t const mainTextLength = mainText.length();
    while (isNotNpos(static_cast<int>(delimiterIndex))) {
        if (startingIndexOfFind != delimiterIndex) {
            listOfStrings.emplace_back(mainText.substr(startingIndexOfFind, delimiterIndex - startingIndexOfFind));
        }
        if constexpr (SplitStringType::WithDelimeters == splitStringType) {
            listOfStrings.emplace_back(mainText.substr(delimiterIndex, delimeterLength));
        }
        startingIndexOfFind = delimiterIndex + delimeterLength;
        delimiterIndex = mainText.find_first_of(delimiters, startingIndexOfFind);
    }
    if (startingIndexOfFind != mainTextLength) {
        listOfStrings.emplace_back(mainText.substr(startingIndexOfFind, mainTextLength - startingIndexOfFind));
    }
}

template void splitToStrings<SplitStringType::WithoutDelimeters>(
    strings& listOfStrings, string_view const mainText, string_view const delimiter);

template void splitToStrings<SplitStringType::WithDelimeters>(
    strings& listOfStrings, string_view const mainText, string_view const delimiter);

void splitLinesToAchieveTargetLength(strings& strings, string_view const mainText, size_t const targetLength) {
    set<size_t> transitionIndexes;
    size_t const mainTextLength = mainText.length();
    bool isPreviousCharacterAWhitespace(false);
    transitionIndexes.emplace(0);
    for (size_t index1 = 0; index1 < mainTextLength; ++index1) {
        char const currentCharacter = mainText[index1];
        if (isPreviousCharacterAWhitespace && !isWhiteSpace(currentCharacter)) {
            transitionIndexes.emplace(index1 - 1);
        } else if (!isPreviousCharacterAWhitespace && isWhiteSpace(currentCharacter)) {
            transitionIndexes.emplace(index1);
        }
        isPreviousCharacterAWhitespace = isWhiteSpace(currentCharacter);
    }
    transitionIndexes.emplace(mainTextLength);

    size_t previousSplittingIndex = 0;
    for (size_t splittingIndex = targetLength; splittingIndex < mainTextLength; splittingIndex += targetLength) {
        char const currentCharacter = mainText[splittingIndex];

        if (!isWhiteSpace(currentCharacter)) {
            auto [lowerTransitionIndex, upperTransitionIndex] =
                containerHelper::getLowerAndUpperValuesForSet(transitionIndexes, splittingIndex);
            ++lowerTransitionIndex;
            int const lowerDelta = static_cast<int>(splittingIndex - lowerTransitionIndex);
            int const upperDelta = static_cast<int>(upperTransitionIndex - splittingIndex);

            bool const isUpperValid(upperDelta >= 0);
            bool const isLowerValid(lowerDelta >= 0 && lowerTransitionIndex != previousSplittingIndex);
            if (isUpperValid && isLowerValid) {
                if (upperDelta < lowerDelta) {
                    splittingIndex = upperTransitionIndex;
                } else {
                    splittingIndex = lowerTransitionIndex;
                }
            } else if (isUpperValid) {
                splittingIndex = upperTransitionIndex;
            } else if (isLowerValid) {
                splittingIndex = lowerTransitionIndex;
            }
        }
        strings.emplace_back(mainText.substr(previousSplittingIndex, splittingIndex - previousSplittingIndex));
        previousSplittingIndex = splittingIndex;
    }
    if (previousSplittingIndex != mainTextLength) {
        strings.emplace_back(mainText.substr(previousSplittingIndex));
    }
}

void splitToStringsUsingASeriesOfDelimeters(
    strings& listOfStrings, string_view const mainText, strings const& seriesOfDelimiters) {
    if (!seriesOfDelimiters.empty()) {
        size_t startingIndexOfFind(0);
        size_t const mainTextLength = mainText.length();
        for (auto&& delimeter : seriesOfDelimiters) {
            size_t const delimiterIndex = mainText.find(delimeter, startingIndexOfFind);
            if (isNpos(static_cast<int>(delimiterIndex))) {
                break;
            }
            if (startingIndexOfFind != delimiterIndex) {
                listOfStrings.emplace_back(mainText.substr(startingIndexOfFind, delimiterIndex - startingIndexOfFind));
            }
            startingIndexOfFind = delimiterIndex + delimeter.length();
        }
        if (startingIndexOfFind != mainTextLength) {
            listOfStrings.emplace_back(mainText.substr(startingIndexOfFind, mainTextLength - startingIndexOfFind));
        }
    }
}

string combineStrings(strings const& listOfStrings, string_view const delimiters) {
    string delimeterString(delimiters);
    string result = accumulate(
        listOfStrings.cbegin(), listOfStrings.cend(), string(),
        [&delimeterString](string const& previousResult, string const& currentString) {
            return previousResult + currentString + delimeterString;
        });

    if (result.size() > delimiters.size()) {
        result = result.substr(0, result.size() - delimiters.size());
    }
    return result;
}

string getStringWithAlignment(
    string_view const mainText, size_t const targetLength, AlignmentType const alignmentType) {
    switch (alignmentType) {
        case AlignmentType::Justify:
            return getStringWithJustifyAlignment(mainText, targetLength);
        case AlignmentType::Center:
            return getStringWithCenterAlignment(mainText, targetLength);
        case AlignmentType::Right:
            return getStringWithRightAlignment(mainText, targetLength);
        case AlignmentType::Left:
            return getStringWithLeftAlignment(mainText, targetLength);
    }
    return {};
}

string getStringWithJustifyAlignment(string_view const mainText, size_t const targetLength) {
    string result;
    result.reserve(targetLength);
    string const noRedundantWhiteSpace(getStringWithoutRedundantWhiteSpace(mainText));
    string noWhiteSpace(getStringWithoutWhiteSpace(mainText));
    if (mainText.empty()) {
        string const gap(targetLength, ' ');
        result = gap;
    } else if (noRedundantWhiteSpace.length() >= targetLength) {
        result = noRedundantWhiteSpace;
    } else if (isOneWord(mainText)) {
        size_t const noWhiteSpaceLength = noWhiteSpace.length();
        size_t const numberOfSpaces = targetLength - noWhiteSpaceLength;
        size_t const gapLength = (noWhiteSpaceLength <= 1) ? 0
                                 : (numberOfSpaces >= noWhiteSpaceLength + 1)
                                     ? numberOfSpaces / (noWhiteSpaceLength + 1)
                                     : numberOfSpaces / (noWhiteSpaceLength - 1);
        size_t const remainingLengthAtTheEnds = numberOfSpaces - (gapLength * (noWhiteSpaceLength - 1));
        string const gap(gapLength, ' ');
        result += string(remainingLengthAtTheEnds / 2, ' ');
        for (size_t index = 0; index + 1 < noWhiteSpaceLength; ++index) {
            result += noWhiteSpace[index];
            result += gap;
        }
        result += noWhiteSpace.back();
        result += string(targetLength - result.length(), ' ');
    } else {
        strings actualStrings;
        splitToStrings<SplitStringType::WithoutDelimeters>(actualStrings, noRedundantWhiteSpace, WHITESPACE_STRING);
        size_t const numberOfStrings = actualStrings.size();
        size_t const noWhiteSpaceLength = noWhiteSpace.length();
        size_t const numberOfSpaces = targetLength - noWhiteSpaceLength;
        size_t const gapLength = (numberOfStrings <= 1)                    ? 0
                                 : (numberOfSpaces >= numberOfStrings + 1) ? numberOfSpaces / (numberOfStrings + 1)
                                                                           : numberOfSpaces / (numberOfStrings - 1);
        size_t const remainingLengthAtTheEnds = numberOfSpaces - (gapLength * (numberOfStrings - 1));
        string const gap(gapLength, ' ');
        result += string(remainingLengthAtTheEnds / 2, ' ');
        for (size_t index = 0; index + 1 < numberOfStrings; ++index) {
            result += actualStrings[index];
            result += gap;
        }
        result += actualStrings.back();
        result += string(targetLength - result.length(), ' ');
    }
    return result;
}

string getStringWithCenterAlignment(string_view const mainText, size_t const targetLength) {
    string result;
    string const noRedundantWhiteSpace(getStringWithoutRedundantWhiteSpace(mainText));
    if (mainText.empty()) {
        string const gap(targetLength, ' ');
        result = gap;
    } else if (noRedundantWhiteSpace.length() >= targetLength) {
        result = noRedundantWhiteSpace;
    } else {
        size_t const gapLength = (targetLength - noRedundantWhiteSpace.length()) / 2;
        result += string(gapLength, ' ');
        result += noRedundantWhiteSpace;
        result += string(targetLength - result.length(), ' ');
    }
    return result;
}

string getStringWithRightAlignment(string_view const mainText, size_t const targetLength) {
    string result;
    string const noRedundantWhiteSpace(getStringWithoutRedundantWhiteSpace(mainText));
    if (mainText.empty()) {
        string const gap(targetLength, ' ');
        result = gap;
    } else if (noRedundantWhiteSpace.length() >= targetLength) {
        result = noRedundantWhiteSpace;
    } else {
        size_t const gapLength = (targetLength - noRedundantWhiteSpace.length());
        result += string(gapLength, ' ');
        result += noRedundantWhiteSpace;
    }
    return result;
}

string getStringWithLeftAlignment(string_view const mainText, size_t const targetLength) {
    string result;
    string const noRedundantWhiteSpace(getStringWithoutRedundantWhiteSpace(mainText));
    if (mainText.empty()) {
        string const gap(targetLength, ' ');
        result = gap;
    } else if (noRedundantWhiteSpace.length() >= targetLength) {
        result = noRedundantWhiteSpace;
    } else {
        size_t const gapLength = (targetLength - noRedundantWhiteSpace.length());
        result += noRedundantWhiteSpace;
        result += string(gapLength, ' ');
    }
    return result;
}

string getCorrectPathWithoutUrlParameters(string_view const path) {
    string correctPathWithoutUrlParameters(path);
    size_t const indexOfQuestionMark = path.find_first_of('?');
    if (isNotNpos(static_cast<int>(indexOfQuestionMark))) {
        correctPathWithoutUrlParameters = path.substr(0, indexOfQuestionMark);
    }
    return correctPathWithoutUrlParameters;
}

string getUrlParameters(string_view const path) {
    string urlParameters;
    size_t const indexOfQuestionMark = path.find_first_of('?');
    if (isNotNpos(static_cast<int>(indexOfQuestionMark))) {
        urlParameters = path.substr(indexOfQuestionMark);
    }
    return urlParameters;
}

string getCorrectPathWithReplacedSlashCharacters(string_view const path, string_view const slashCharacterString) {
    bool wasSlashDetected = false;
    string correctPath = accumulate(
        path.cbegin(), path.cend(), string(),
        [&wasSlashDetected, slashCharacterString](string_view const currentString, char const currentCharacter) {
            string partialResult(currentString);
            if (isSlashCharacter(currentCharacter)) {
                if (!wasSlashDetected) {
                    partialResult += slashCharacterString;
                }
            } else {
                partialResult += currentCharacter;
            }
            wasSlashDetected = isSlashCharacter(currentCharacter);
            return partialResult;
        });
    return correctPath;
}

string getCorrectPathWithoutDoublePeriod(string_view const path, string_view const slashCharacterString) {
    string correctPath(path);
    bool isDirectoryChanged = true;
    while (isDirectoryChanged) {
        isDirectoryChanged = false;
        string stringToFind(slashCharacterString);
        stringToFind += ".."s;
        stringToFind += slashCharacterString;
        size_t const indexOfDoublePeriod = correctPath.find(stringToFind);
        if (isNotNpos(static_cast<int>(indexOfDoublePeriod))) {
            size_t const indexOfNearestSlash = correctPath.find_last_of(slashCharacterString, indexOfDoublePeriod - 1);
            if (isNotNpos(static_cast<int>(indexOfNearestSlash))) {
                isDirectoryChanged = true;
                correctPath.erase(indexOfNearestSlash, indexOfDoublePeriod + 3 - indexOfNearestSlash);
            }
        }
    }
    return correctPath;
}

string getStringBeforeDoublePeriod(string_view const path, string_view const slashCharacterString) {
    size_t const indexOfLastDoublePeriod = path.rfind(".."s + string(slashCharacterString));
    if (isNotNpos(static_cast<int>(indexOfLastDoublePeriod))) {
        return string(path.substr(indexOfLastDoublePeriod + 3));
    }
    return string(path);
}

string getImmediateDirectoryName(string_view const path, string_view const slashCharacterString) {
    size_t indexLastCharacterToSearch = path.length();
    string result;
    while (result.empty()) {
        size_t const indexOfLastSlashString = path.find_last_of(slashCharacterString, indexLastCharacterToSearch);
        if (isNpos(static_cast<int>(indexOfLastSlashString))) {
            break;
        }
        result = path.substr(indexOfLastSlashString + 1, indexLastCharacterToSearch - indexOfLastSlashString);
        indexLastCharacterToSearch = indexOfLastSlashString - 1;
    }
    return result;
}

template <char slashCharacter>
string getCorrectPathWithReplacedSlashCharacters(string_view const path) {
    return getCorrectPathWithReplacedSlashCharacters(path, string(1, slashCharacter));
}

template string getCorrectPathWithReplacedSlashCharacters<'\\'>(string_view const path);
template string getCorrectPathWithReplacedSlashCharacters<'/'>(string_view const path);

template <char slashCharacter>
string getCorrectPathWithoutDoublePeriod(string_view const path) {
    return getCorrectPathWithoutDoublePeriod(path, string(1, slashCharacter));
}

template string getCorrectPathWithoutDoublePeriod<'\\'>(string_view const path);
template string getCorrectPathWithoutDoublePeriod<'/'>(string_view const path);

template <char slashCharacter>
string getStringBeforeDoublePeriod(string_view const path) {
    return getStringBeforeDoublePeriod(path, string(1, slashCharacter));
}

template string getStringBeforeDoublePeriod<'\\'>(string_view const path);
template string getStringBeforeDoublePeriod<'/'>(string_view const path);

template <char slashCharacter>
string getImmediateDirectoryName(string_view const path) {
    return getImmediateDirectoryName(path, string(1, slashCharacter));
}

template string getImmediateDirectoryName<'\\'>(string_view const path);
template string getImmediateDirectoryName<'/'>(string_view const path);

bool convertStringToBool(string_view const stringToConvert) {
    string const allCapital(getStringWithCapitalLetters(stringToConvert));
    bool result(false);
    if ("TRUE" == allCapital) {
        result = true;
    } else if ("FALSE" == allCapital) {
        result = false;
    } else {
        result = (0 != convertStringToNumber<int>(stringToConvert));
    }
    return result;
}

AlbaNumber convertStringToAlbaNumber(string_view const stringToConvert) {
    AlbaNumber result;
    if (isStringFoundCaseSensitive(stringToConvert, ".")) {
        result = AlbaNumber(convertStringToNumber<double>(stringToConvert));
    } else {
        result = AlbaNumber(convertStringToNumber<int>(stringToConvert));
    }
    return result;
}

string convertBoolToString(bool const value) {
    stringstream temporaryStream;
    temporaryStream << boolalpha << value;
    return temporaryStream.str();
}

void StringConverterWithFormatting::setPrecision(int const precision) { m_precisionOptional = precision; }
void StringConverterWithFormatting::setFieldWidth(int const fieldWidth) { m_fieldWidthOptional = fieldWidth; }

void StringConverterWithFormatting::setFillCharacter(char const fillCharacter) {
    m_fillCharacterOptional = fillCharacter;
}

void StringConverterWithFormatting::setMaximumLength(size_t const maximumLength) {
    m_maximumLengthOptional = maximumLength;
}

void StringConverterWithFormatting::setFloatOutputType(FloatOutputType const floatOutputType) {
    m_floatOutputTypeOptional = floatOutputType;
}

}  // namespace alba::stringHelper
