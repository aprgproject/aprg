#include "AlbaPrintFunctions.hpp"

#include <Common/Time/AlbaLocalTimeHelper.hpp>
#include <Common/Time/AlbaLocalTimer.hpp>

#include <iomanip>

using namespace std;

namespace alba {

// put this when quoted has string_view definition
// void printParameter(ostream& out, string_view parameter) {
//    out << "string view" << quoted(string(parameter));
// }
void printLogHeader(ostream& out, string_view const fileName, int const lineNumber, string_view const functionName) {
    constexpr int MAX_FILENAME_PREFIX_LENGTH = 0;
    constexpr int MAX_FILENAME_SUFFIX_LENGTH = 30;
    constexpr int MAX_FUNCTION_NAME_PREFIX_LENGTH = 10;
    constexpr int MAX_FUNCTION_NAME_SUFFIX_LENGTH = 40;
    out << "| ";
    printCurrentDateTime(out);
    out << " | ";
    printStringAndShortenIfPossible(out, fileName, MAX_FILENAME_PREFIX_LENGTH, MAX_FILENAME_SUFFIX_LENGTH);
    out << ":" << lineNumber << " | ";
    printStringAndShortenIfPossible(
        out, functionName, MAX_FUNCTION_NAME_PREFIX_LENGTH, MAX_FUNCTION_NAME_SUFFIX_LENGTH);
    out << "(...) | ";
}

void printCurrentDateTime(ostream& out) {
    AlbaDateTime const currentTime(convertSystemTimeToAlbaDateTime(getSystemTimeNow()));
    out << currentTime.getPrintObject<AlbaDateTime::PrintFormat::Standard>();
}

void printStringAndShortenIfPossible(
    ostream& out, string_view const longStr, size_t const prefixLength, size_t const suffixLength) {
    size_t const length = longStr.length();
    if (prefixLength + suffixLength + 3 < length) {
        out << longStr.substr(0, prefixLength) << "..." << longStr.substr(length - suffixLength, suffixLength);
    } else {
        out << longStr;
    }
}

void printParameter(ostream& out, string const& parameter) { out << quoted(parameter); }
void printParameter(ostream& out, char const* const parameter) { out << quoted(parameter); }

template <>
void printParameterWithName(ostream& out, string_view, char const* const parameter) {
    // the name is not printing to avoid printing the same string literal twice
    out << R"([")" << parameter << R"("])";
}

}  // namespace alba
