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

size_t generateUniqueId(string_view str) {
    return accumulate(begin(str), end(str), 1ULL, [](size_t c1, uint8_t c2) { return (c1 * c2) + 1; });
}

size_t getLevenshteinDistance(string_view otherString, string_view basisString) {
    // The edit distance or Levenshtein distance is the minimum number of editing operations needed to transform a
    // string into another string. The allowed editing operations are as follows:
    // -> insert a character (e.g. ABC ! ABCA)
    // -> remove a character (e.g. ABC ! AC)
    // -> modify a character (e.g. ABC ! ADC)

    using Counts = vector<size_t>;

    vector<Counts> previousAndCurrentCounts(2, Counts(basisString.length() + 1));  // string1 as basis
    Counts& firstPrevious(previousAndCurrentCounts[0]);
    iota(begin(firstPrevious), end(firstPrevious), 0);  // first row

    for (size_t otherIndex = 1; otherIndex <= otherString.length(); otherIndex++) {
        Counts& previousCounts(previousAndCurrentCounts[(otherIndex - 1) % 2]);
        Counts& currentCounts(previousAndCurrentCounts[otherIndex % 2]);

        currentCounts[0] = otherIndex;  // first column
        for (size_t basisIndex = 1; basisIndex <= basisString.length(); basisIndex++) {
            size_t cost = basisString[basisIndex - 1] == otherString[otherIndex - 1] ? 0 : 1;
            currentCounts[basisIndex] =
                min(min(currentCounts[basisIndex - 1] + 1, previousCounts[basisIndex] + 1),
                    previousCounts[basisIndex - 1] + cost);
        }
    }

    Counts const& lastCurrent(previousAndCurrentCounts[otherString.length() % 2]);
    return lastCurrent.back();
}

size_t getHammingDistance(string_view string1, string_view string2) {
    // The Hamming distance hamming(a,b) between two strings a and b of equal length is the number of positions where
    // the strings differ.
    size_t result(0);
    size_t commonLength = min(string1.length(), string2.length());
    for (size_t i = 0; i < commonLength; i++) {
        if (string1[i] != string2[i]) {
            result++;
        }
    }
    return result;
}

size_t getNumberOfSubStrings(string_view str) {
    // A string of length n has n(n+1)/2 substrings.

    size_t n = str.length();
    return n * (n + 1) / 2;
}

size_t getNumberOfSubsequences(string_view str) {
    // A string of length n has 2^n - 1 subsequences.

    return static_cast<size_t>(get2ToThePowerOf(str.length()) - 1);
}

int getRotationValue(string_view str, string_view rotation) {
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

int getPeriodValue(string_view str, string_view period) {
    // A period is a prefix of a string such that the string can be constructed by repeating the period.
    // The last repetition may be partial and contain only a prefix of the period.
    // For example, the shortest period of ABCABCA is ABC.

    int periodCount(0);
    if (!period.empty()) {
        for (size_t i(0U), j(0U); i < str.length(); i++, j++) {
            if (j == period.length()) {
                j = 0;
                periodCount++;
            }
            if (str[i] != period[j]) {
                periodCount = 0;
                break;
            }
        }
    }
    return (periodCount > 0) ? periodCount : static_cast<int>(string::npos);
}

bool isNumber(string_view str) {
    return any_of(begin(str), end(str), [](char const character) { return isNumber(character); });
}

bool isWhiteSpace(string_view str) {
    return all_of(begin(str), end(str), [](char const character) { return isWhiteSpace(character); });
}

bool isNewline(string_view str) {
    return all_of(begin(str), end(str), [](char const character) { return isNewline(character); });
}

bool isIdentifier(string_view str) {
    bool isIdentifier(false);
    if (!str.empty()) {
        char firstCharacter = str[0];
        isIdentifier = isLetter(firstCharacter) || isUnderscore(firstCharacter);
    }
    return isIdentifier;
}

bool isOneWord(string_view str) {
    return (!str.empty()) &&
           none_of(begin(str), end(str), [](char const character) { return isWhiteSpace(character); });
}

bool isPalindrome(string_view str) {
    bool result(false);
    if (!str.empty()) {
        result = true;
        size_t left(0), right(str.length() - 1);
        while (left < right) {
            if (str[left++] != str[right--]) {
                result = false;
                break;
            }
        }
    }
    return result;
}

bool isSubstring(string_view mainText, string_view subString) {
    // A substring is a sequence of consecutive characters in a string.
    // We use the notation s[a...b] to refer to a substring of s that begins at position a and ends at position b.
    // A string of length n has n(n+1)/2 substrings.
    // For example, the substrings of ABCD are A, B, C, D, AB, BC, CD, ABC, BCD and ABCD.
    // NOTE: This is the same as: isStringFoundCaseSensitive

    return isNotNpos(static_cast<int>(mainText.find(subString)));
}

bool isSubsequence(string_view mainText, string_view subsequence) {
    // A subsequence is a sequence of (not necessarily consecutive) characters in a string in their original order.
    // A string of length n has 2n-1 subsequences.
    // For example, the subsequences of ABCD are A, B, C, D, AB, AC, AD, BC, BD, CD, ABC, ABD, ACD, BCD and ABCD.

    size_t j(0U);
    for (size_t i(0U); i < mainText.length() && j < subsequence.length(); i++) {
        if (mainText[i] == subsequence[j]) {
            j++;
        }
    }
    return j == subsequence.length();
}

bool isPrefix(string_view mainText, string_view prefix) {
    // A prefix is a substring that starts at the beginning of a string.
    // For example, the prefixes of ABCD are A, AB, ABC and ABCD.

    size_t j(0U);
    for (size_t i(0U); i < mainText.length() && j < prefix.length(); i++, j++) {
        if (mainText[i] != prefix[j]) {
            break;
        }
    }
    return j == prefix.length();
}

bool isSuffix(string_view mainText, string_view suffix) {
    // A suffix is a substring that ends at the end of a string.
    // For example, the suffixes of ABCD are D, CD, BCD and ABCD.

    int j = static_cast<int>(suffix.length()) - 1;
    for (int i = static_cast<int>(mainText.length()) - 1; i >= 0 && j >= 0; i--, j--) {
        if (mainText[i] != suffix[j]) {
            break;
        }
    }
    return j == -1;
}

bool isRotation(string_view mainText, string_view rotation) {
    // A rotation can be generated by moving the characters of a string one by one from the beginning to the end (or
    // vice versa). For example, the rotations of ABCD are ABCD, BCDA, CDAB and DABC.

    return isNotNpos(getRotationValue(mainText, rotation));
}

bool isPeriod(string_view mainText, string_view period) {
    // A period is a prefix of a string such that the string can be constructed by repeating the period.
    // The last repetition may be partial and contain only a prefix of the period.
    // For example, the shortest period of ABCABCA is ABC.

    return isNotNpos(getPeriodValue(mainText, period));
}

bool isBorder(string_view text, string_view border) {
    // A border is a string that is both a prefix and a suffix of a string.
    // For example, the borders of ABACABA are A, ABA and ABACABA.

    return isPrefix(text, border) && isSuffix(text, border);
}

bool isEqualNotCaseSensitive(string_view str1, string_view str2) {
    return getStringWithCapitalLetters(str1) == getStringWithCapitalLetters(str2);
}

bool isEqualWithLowestCommonLength(string_view str1, string_view str2) {
    size_t length1 = str1.length();
    size_t length2 = str2.length();
    size_t lowestLength = (length1 > length2) ? length2 : length1;
    return str1.substr(0, lowestLength) == str2.substr(0, lowestLength);
}

bool isStringFoundCaseSensitive(string_view mainText, string_view stringToSearch) {
    return isNotNpos(static_cast<int>(mainText.find(stringToSearch)));
}

bool isStringFoundCaseSensitive(string_view mainText, string_view stringToSearch, int& runningOffset) {
    int foundIndex = static_cast<int>(mainText.find(stringToSearch, runningOffset));
    bool isFound = isNotNpos(foundIndex);
    if (isFound) {
        runningOffset = foundIndex + stringToSearch.length();
    }
    return isFound;
}

bool isStringFoundNotCaseSensitive(string_view mainText, string_view stringToSearch) {
    return isStringFoundCaseSensitive(
        getStringWithCapitalLetters(mainText), getStringWithCapitalLetters(stringToSearch));
}

bool isWildcardMatch(
    string_view mainText, string_view wildcard, size_t const mainTextIndex, size_t const wildcardIndex) {
    bool result(false);
    bool isMainStringDone = mainTextIndex >= mainText.size();
    bool isWildcardDone = wildcardIndex >= wildcard.size();
    if (isMainStringDone && isWildcardDone) {
        result = true;
    } else if (isWildcardDone) {
        result = false;
    } else if (isMainStringDone) {
        bool isWildcardDoneOnNextIndex = wildcardIndex + 1 >= wildcard.size();
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

string getStringWithCapitalLetters(string_view str) {
    string result;
    result.resize(str.length());
    transform(begin(str), end(str), begin(result), ::toupper);
    return result;
}

string getStringWithFirstNonWhiteSpaceCharacterToCapital(string_view str) {
    string result(str);
    size_t resultLength = result.length();
    for (size_t i = 0; i < resultLength; ++i) {
        if (!isWhiteSpace(result[i])) {
            result[i] = static_cast<char>(::toupper(result[i]));
            break;
        }
    }
    return result;
}

string getStringWithLowerCaseLetters(string_view str) {
    string result;
    result.resize(str.length());
    transform(begin(str), end(str), begin(result), ::tolower);
    return result;
}

string getStringWithUrlDecodedString(string_view str) {
    string result;
    size_t index = 0, length = str.length();
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

string getStringThatContainsWhiteSpaceIndention(string_view str) {
    string result;
    size_t firstIndexOfNotOfCharacters(str.find_first_not_of(WHITESPACE_STRING));
    if (isNotNpos(static_cast<int>(firstIndexOfNotOfCharacters))) {
        result = str.substr(0, firstIndexOfNotOfCharacters);
    }
    return result;
}

string getStringWithoutStartingAndTrailingCharacters(string_view str, string_view characters) {
    string result(str);
    size_t firstIndexOfNotOfCharacters(result.find_first_not_of(characters));
    if (isNotNpos(static_cast<int>(firstIndexOfNotOfCharacters))) {
        result.erase(0, firstIndexOfNotOfCharacters);
        size_t lastIndexOfOfNotOfCharacters(result.find_last_not_of(characters));
        if (isNotNpos(static_cast<int>(lastIndexOfOfNotOfCharacters))) {
            result.erase(lastIndexOfOfNotOfCharacters + 1);
        }
    } else {
        result.clear();
    }
    return result;
}

string getStringWithoutStartingAndTrailingWhiteSpace(string_view str) {
    return getStringWithoutStartingAndTrailingCharacters(str, WHITESPACE_STRING);
}

string getStringWithoutWhiteSpace(string_view str) {
    string result;
    size_t index = 0, length = str.length();
    while (index < length) {
        if (!isWhiteSpace(str[index])) {
            result += str[index];
        }
        index++;
    }
    return result;
}

string getStringWithoutRedundantWhiteSpace(string_view str) {
    string result;
    size_t index = 0, length = str.length();
    while (index < length) {
        size_t indexNotWhiteSpace = str.find_first_not_of(WHITESPACE_STRING, index);
        if (isNpos(static_cast<int>(indexNotWhiteSpace))) {
            break;
        }
        size_t indexWhiteSpace = str.find_first_of(WHITESPACE_STRING, indexNotWhiteSpace);
        index = (isNotNpos(static_cast<int>(indexWhiteSpace))) ? indexWhiteSpace : length;
        result += (!result.empty()) ? " "s : string();
        result += str.substr(indexNotWhiteSpace, index - indexNotWhiteSpace);
    }
    return result;
}

string getStringWithoutQuotations(string_view str) {
    size_t length = str.length();
    if (length > 2 && str[0] == '\"' && str[length - 1] == '\"') {
        return string(str.substr(1, length - 2));
    }
    return string(str);
}

string getStringWithoutCharAtTheStartAndEnd(string_view str, char const char1) {
    return getStringWithoutCharAtTheStart(getStringWithoutCharAtTheEnd(str, char1), char1);
}

string getStringWithoutCharAtTheStart(string_view str, char const char1) {
    size_t length = str.length();
    size_t start = (str[0] == char1) ? 1 : 0;
    return string(str.substr(start, length - start));
}

string getStringWithoutCharAtTheEnd(string_view str, char const char1) {
    size_t length = str.length();
    size_t end = (length == 0) ? 0 : (str[length - 1] == char1) ? length - 1 : length;
    return string(str.substr(0, end));
}

string getStringWithoutOpeningClosingOperators(
    string_view str, char const openingOperator, char const closingOperator) {
    size_t length = str.length();
    size_t start = (str[0] == openingOperator) ? 1 : 0;
    size_t end = (length == 0) ? 0 : (str[length - 1] == closingOperator) ? length - 1 : length;
    return string(str.substr(start, end - start));
}

string getLongestCommonPrefix(string_view first, string_view second) {
    size_t i = 0;
    for (; i < first.length() && i < second.length(); i++) {
        if (first[i] != second[i]) {
            break;
        }
    }
    return string(first.substr(0, i));
}

void copyBeforeStringAndAfterString(
    string_view mainText, string_view stringToSearch, string& beforeString, string& afterString,
    size_t const indexToStartTheSearch) {
    beforeString.clear();
    afterString.clear();
    size_t firstIndexOfFirstString = mainText.find(stringToSearch, indexToStartTheSearch);
    if (isNotNpos(static_cast<int>(firstIndexOfFirstString))) {
        size_t lastIndexOfFirstString = firstIndexOfFirstString + stringToSearch.length();
        beforeString = mainText.substr(0, firstIndexOfFirstString);
        afterString = mainText.substr(lastIndexOfFirstString);
    }
}

string getStringBeforeThisString(string_view mainText, string_view stringToSearch, size_t const indexToStart) {
    string result;
    size_t firstIndexOfFirstString = mainText.find(stringToSearch, indexToStart);
    if (isNotNpos(static_cast<int>(firstIndexOfFirstString))) {
        result = mainText.substr(indexToStart, firstIndexOfFirstString - indexToStart);
    }
    return result;
}

string getStringAfterThisString(string_view mainText, string_view stringToSearch, size_t const indexToStart) {
    string result;
    size_t firstIndexOfFirstString = mainText.find(stringToSearch, indexToStart);
    if (isNotNpos(static_cast<int>(firstIndexOfFirstString))) {
        size_t lastIndexOfFirstString = firstIndexOfFirstString + stringToSearch.length();
        result = mainText.substr(lastIndexOfFirstString);
    }
    return result;
}

string getStringInBetweenTwoStrings(
    string_view mainText, string_view firstString, string_view secondString, size_t const indexToStart) {
    string result;
    size_t firstIndexOfFirstString = mainText.find(firstString, indexToStart);
    if (isNotNpos(static_cast<int>(firstIndexOfFirstString))) {
        size_t lastIndexOfFirstString = firstIndexOfFirstString + firstString.length();
        size_t firstIndexOfSecondString = mainText.find(secondString, lastIndexOfFirstString);
        if (isNotNpos(static_cast<int>(firstIndexOfSecondString))) {
            result = mainText.substr(lastIndexOfFirstString, firstIndexOfSecondString - lastIndexOfFirstString);
        }
    }
    return result;
}

string getStringBeforeThisCharacters(string_view mainText, string_view characters, size_t const indexToStart) {
    string result;
    size_t firstIndexOfNotOfCharacters(mainText.find_first_of(characters, indexToStart));
    if (isNotNpos(static_cast<int>(firstIndexOfNotOfCharacters))) {
        result = mainText.substr(indexToStart, firstIndexOfNotOfCharacters - indexToStart);
    }
    return result;
}

string getStringAndReplaceNonAlphanumericCharactersToUnderScore(string_view path) {
    bool isPreviousCharacterNonAlphanumeric = false;
    string correctPath = accumulate(
        path.cbegin(), path.cend(), string(),
        [&isPreviousCharacterNonAlphanumeric](string_view currentString, char const currentCharacter) {
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

string getStringByRepeatingUntilDesiredLength(string_view stringToRepeat, size_t desiredLength) {
    string result;
    if (!stringToRepeat.empty()) {
        size_t stringToRepeatLength = stringToRepeat.length();
        for (size_t index = 0; index <= desiredLength; index += stringToRepeatLength) {
            result += stringToRepeat;
        }
        result = result.substr(0, desiredLength);
    }
    return result;
}

string getNumberAfterThisString(string_view mainText, string_view stringToSearch) {
    string result;
    size_t firstIndexOfFirstString = mainText.find(stringToSearch);
    if (isNotNpos(static_cast<int>(firstIndexOfFirstString))) {
        size_t lastIndexOfFirstString = firstIndexOfFirstString + stringToSearch.length();
        size_t lastIndexOfNumber;
        for (lastIndexOfNumber = lastIndexOfFirstString;
             lastIndexOfNumber < mainText.length() && isNumber(mainText[lastIndexOfNumber]); ++lastIndexOfNumber)
            ;
        result = mainText.substr(lastIndexOfFirstString, lastIndexOfNumber - lastIndexOfFirstString);
    }
    return result;
}

string getHexNumberAfterThisString(string_view mainText, string_view stringToSearch) {
    string result;
    size_t firstIndexOfFirstString = mainText.find(stringToSearch);
    if (isNotNpos(static_cast<int>(firstIndexOfFirstString))) {
        size_t lastIndexOfFirstString = firstIndexOfFirstString + stringToSearch.length();
        size_t lastIndexOfNumber(lastIndexOfFirstString);
        for (; lastIndexOfNumber < mainText.length() && isHexDigit(mainText[lastIndexOfNumber]); ++lastIndexOfNumber)
            ;
        result = mainText.substr(lastIndexOfFirstString, lastIndexOfNumber - lastIndexOfFirstString);
    }
    return result;
}

string getHexEquivalentOfCharacters(string_view stringToCheck) {
    stringstream ss;
    for (unsigned char const c : stringToCheck) {
        ss << hex << uppercase << setfill('0') << setw(2) << static_cast<unsigned long long>(c);
    }
    return ss.str();
}

string getQuotedString(string_view stringToCheck) {
    stringstream ss;
    ss << std::quoted(string(stringToCheck));  // remove temporary string object when quoted has string view
    return ss.str();
}

string constructFileLocator(string_view file, int const lineNumber) {
    stringstream ss;
    ss << file.substr(file.find_last_of('\\') + 1) << "[" << lineNumber << "]";
    return ss.str();
}

string getRandomAlphaNumericString(size_t const length) {
    constexpr auto ALPHA_NUMERIC_CHAR_MAP = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    int alphaNumericCharMapIndexMax = static_cast<int>(strlen(ALPHA_NUMERIC_CHAR_MAP)) - 1;
    AlbaUniformNonDeterministicRandomizer randomizer(0, alphaNumericCharMapIndexMax);
    string result;
    result.reserve(length);
    generate_n(back_inserter(result), length, [&]() {
        return ALPHA_NUMERIC_CHAR_MAP[static_cast<size_t>(randomizer.getRandomValue())];
    });
    return result;
}

strings getArgumentsToStringInMain(int const argc, char const* const argv[]) {
    strings result;
    for (int argumentIndex = 0; argumentIndex < argc; argumentIndex++) {
        result.emplace_back(argv[argumentIndex]);
    }
    return result;
}

bool replaceAllAndReturnIfFound(string& mainText, string_view targetStr, string_view replacementStr) {
    bool found = false;
    size_t targetStrLength = targetStr.length();
    size_t replacementStrLength = replacementStr.length();
    size_t index = mainText.find(targetStr);
    while (isNotNpos(static_cast<int>(index))) {
        found = true;
        mainText.replace(index, targetStrLength, replacementStr);
        index = mainText.find(targetStr, index + replacementStrLength);
    }
    return found;
}

template <SplitStringType splitStringType>
void splitToStrings(strings& listOfStrings, string_view mainText, string_view delimiters) {
    size_t startingIndexOfFind(0);
    size_t delimiterIndex = mainText.find_first_of(delimiters);
    size_t delimeterLength = 1;
    size_t mainTextLength = mainText.length();
    while (isNotNpos(static_cast<int>(delimiterIndex))) {
        if (startingIndexOfFind != delimiterIndex) {
            listOfStrings.emplace_back(mainText.substr(startingIndexOfFind, delimiterIndex - startingIndexOfFind));
        }
        if (SplitStringType::WithDelimeters == splitStringType) {
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
    strings& listOfStrings, string_view mainText, string_view delimiter);
template void splitToStrings<SplitStringType::WithDelimeters>(
    strings& listOfStrings, string_view mainText, string_view delimiter);

string combineStrings(strings const& listOfStrings, string_view delimiters) {
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

void splitLinesToAchieveTargetLength(strings& strings, string_view mainText, size_t const targetLength) {
    set<size_t> transitionIndexes;
    size_t mainTextLength = mainText.length();
    bool isPreviousCharacterAWhitespace(false);
    transitionIndexes.emplace(0);
    for (size_t i = 0; i < mainTextLength; i++) {
        char currentCharacter = mainText[i];
        if (isPreviousCharacterAWhitespace && !isWhiteSpace(currentCharacter)) {
            transitionIndexes.emplace(i - 1);
        } else if (!isPreviousCharacterAWhitespace && isWhiteSpace(currentCharacter)) {
            transitionIndexes.emplace(i);
        }
        isPreviousCharacterAWhitespace = isWhiteSpace(currentCharacter);
    }
    transitionIndexes.emplace(mainTextLength);

    size_t previousSplittingIndex = 0;
    for (size_t splittingIndex = targetLength; splittingIndex < mainTextLength; splittingIndex += targetLength) {
        char currentCharacter = mainText[splittingIndex];

        if (!isWhiteSpace(currentCharacter)) {
            auto [lowerTransitionIndex, upperTransitionIndex] =
                containerHelper::getLowerAndUpperValuesForSet(transitionIndexes, splittingIndex);
            ++lowerTransitionIndex;
            int lowerDelta = static_cast<int>(splittingIndex - lowerTransitionIndex);
            int upperDelta = static_cast<int>(upperTransitionIndex - splittingIndex);

            bool isUpperValid(upperDelta >= 0);
            bool isLowerValid(lowerDelta >= 0 && lowerTransitionIndex != previousSplittingIndex);
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
    strings& listOfStrings, string_view mainText, strings const& seriesOfDelimiters) {
    if (!seriesOfDelimiters.empty()) {
        size_t startingIndexOfFind(0);
        size_t mainTextLength = mainText.length();
        for (auto&& delimeter : seriesOfDelimiters) {
            size_t delimiterIndex = mainText.find(delimeter, startingIndexOfFind);
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

string getStringWithJustifyAlignment(string_view mainText, size_t const targetLength) {
    string result;
    result.reserve(targetLength);
    string noRedundantWhiteSpace(getStringWithoutRedundantWhiteSpace(mainText));
    string noWhiteSpace(getStringWithoutWhiteSpace(mainText));
    if (mainText.empty()) {
        string gap(targetLength, ' ');
        result = gap;
    } else if (noRedundantWhiteSpace.length() >= targetLength) {
        result = noRedundantWhiteSpace;
    } else if (isOneWord(mainText)) {
        size_t noRedundantWhiteSpaceLength = noRedundantWhiteSpace.length();
        size_t gapLength = (targetLength - noWhiteSpace.length()) / (noRedundantWhiteSpaceLength + 1);
        string gap(gapLength, ' ');
        result += gap;
        for (size_t i = 0; i < noRedundantWhiteSpaceLength; i++) {
            result += noRedundantWhiteSpace[i];
            result += gap;
        }
        result += string(targetLength - result.length(), ' ');
    } else {
        strings actualStrings;
        splitToStrings<SplitStringType::WithoutDelimeters>(actualStrings, noRedundantWhiteSpace, " ");
        size_t numberOfStrings = actualStrings.size();
        size_t gapLength = (targetLength - noWhiteSpace.length()) / (numberOfStrings - 1);
        string gap(gapLength, ' ');
        for (size_t i = 0; i < numberOfStrings; i++) {
            result += actualStrings[i];
            if (i < numberOfStrings - 1) {
                result += gap;
            }
        }
        result += string(targetLength - result.length(), ' ');
    }
    return result;
}

string getStringWithCenterAlignment(string_view mainText, size_t const targetLength) {
    string result;
    string noRedundantWhiteSpace(getStringWithoutRedundantWhiteSpace(mainText));
    if (mainText.empty()) {
        string gap(targetLength, ' ');
        result = gap;
    } else if (noRedundantWhiteSpace.length() >= targetLength) {
        result = noRedundantWhiteSpace;
    } else {
        size_t gapLength = (targetLength - noRedundantWhiteSpace.length()) / 2;
        result += string(gapLength, ' ');
        result += noRedundantWhiteSpace;
        result += string(targetLength - result.length(), ' ');
    }
    return result;
}

string getStringWithRightAlignment(string_view mainText, size_t const targetLength) {
    string result;
    string noRedundantWhiteSpace(getStringWithoutRedundantWhiteSpace(mainText));
    if (mainText.empty()) {
        string gap(targetLength, ' ');
        result = gap;
    } else if (noRedundantWhiteSpace.length() >= targetLength) {
        result = noRedundantWhiteSpace;
    } else {
        size_t gapLength = (targetLength - noRedundantWhiteSpace.length());
        result += string(gapLength, ' ');
        result += noRedundantWhiteSpace;
    }
    return result;
}

string getStringWithLeftAlignment(string_view mainText, size_t const targetLength) {
    string result;
    string noRedundantWhiteSpace(getStringWithoutRedundantWhiteSpace(mainText));
    if (mainText.empty()) {
        string gap(targetLength, ' ');
        result = gap;
    } else if (noRedundantWhiteSpace.length() >= targetLength) {
        result = noRedundantWhiteSpace;
    } else {
        size_t gapLength = (targetLength - noRedundantWhiteSpace.length());
        result += noRedundantWhiteSpace;
        result += string(gapLength, ' ');
    }
    return result;
}

string getCorrectPathWithoutUrlParameters(string_view path) {
    string correctPathWithoutUrlParameters(path);
    size_t indexOfQuestionMark = path.find_first_of('?');
    if (isNotNpos(static_cast<int>(indexOfQuestionMark))) {
        correctPathWithoutUrlParameters = path.substr(0, indexOfQuestionMark);
    }
    return correctPathWithoutUrlParameters;
}

string getUrlParameters(string_view path) {
    string urlParameters;
    size_t indexOfQuestionMark = path.find_first_of('?');
    if (isNotNpos(static_cast<int>(indexOfQuestionMark))) {
        urlParameters = path.substr(indexOfQuestionMark);
    }
    return urlParameters;
}

string getCorrectPathWithReplacedSlashCharacters(string_view path, string_view slashCharacterString) {
    bool wasSlashDetected = false;
    string correctPath = accumulate(
        path.cbegin(), path.cend(), string(),
        [&wasSlashDetected, slashCharacterString](string_view currentString, char const currentCharacter) {
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

string getCorrectPathWithoutDoublePeriod(string_view path, string_view slashCharacterString) {
    string correctPath(path);
    bool isDirectoryChanged = true;
    while (isDirectoryChanged) {
        isDirectoryChanged = false;
        string stringToFind(slashCharacterString);
        stringToFind += ".."s;
        stringToFind += slashCharacterString;
        size_t indexOfDoublePeriod = correctPath.find(stringToFind);
        if (isNotNpos(static_cast<int>(indexOfDoublePeriod))) {
            size_t indexOfNearestSlash = correctPath.find_last_of(slashCharacterString, indexOfDoublePeriod - 1);
            if (isNotNpos(static_cast<int>(indexOfNearestSlash))) {
                isDirectoryChanged = true;
                correctPath.erase(indexOfNearestSlash, indexOfDoublePeriod + 3 - indexOfNearestSlash);
            }
        }
    }
    return correctPath;
}

string getStringBeforeDoublePeriod(string_view path, string_view slashCharacterString) {
    size_t indexOfLastDoublePeriod = path.rfind(".."s + string(slashCharacterString));
    if (isNotNpos(static_cast<int>(indexOfLastDoublePeriod))) {
        return string(path.substr(indexOfLastDoublePeriod + 3));
    }
    return string(path);
}

string getImmediateDirectoryName(string_view path, string_view slashCharacterString) {
    size_t indexLastCharacterToSearch = path.length();
    string result;
    while (result.empty()) {
        size_t indexOfLastSlashString = path.find_last_of(slashCharacterString, indexLastCharacterToSearch);
        if (isNpos(static_cast<int>(indexOfLastSlashString))) {
            break;
        }
        result = path.substr(indexOfLastSlashString + 1, indexLastCharacterToSearch - indexOfLastSlashString);
        indexLastCharacterToSearch = indexOfLastSlashString - 1;
    }
    return result;
}

template <char slashCharacter>
string getCorrectPathWithReplacedSlashCharacters(string_view path) {
    return getCorrectPathWithReplacedSlashCharacters(path, string(1, slashCharacter));
}
template string getCorrectPathWithReplacedSlashCharacters<'\\'>(string_view path);
template string getCorrectPathWithReplacedSlashCharacters<'/'>(string_view path);

template <char slashCharacter>
string getCorrectPathWithoutDoublePeriod(string_view path) {
    return getCorrectPathWithoutDoublePeriod(path, string(1, slashCharacter));
}
template string getCorrectPathWithoutDoublePeriod<'\\'>(string_view path);
template string getCorrectPathWithoutDoublePeriod<'/'>(string_view path);

template <char slashCharacter>
string getStringBeforeDoublePeriod(string_view path) {
    return getStringBeforeDoublePeriod(path, string(1, slashCharacter));
}
template string getStringBeforeDoublePeriod<'\\'>(string_view path);
template string getStringBeforeDoublePeriod<'/'>(string_view path);

template <char slashCharacter>
string getImmediateDirectoryName(string_view path) {
    return getImmediateDirectoryName(path, string(1, slashCharacter));
}
template string getImmediateDirectoryName<'\\'>(string_view path);
template string getImmediateDirectoryName<'/'>(string_view path);

bool convertStringToBool(string_view stringToConvert) {
    string allCapital(getStringWithCapitalLetters(stringToConvert));
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

AlbaNumber convertStringToAlbaNumber(string_view stringToConvert) {
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
