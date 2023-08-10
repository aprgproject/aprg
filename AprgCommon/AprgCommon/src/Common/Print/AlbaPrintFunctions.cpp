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

void printLogHeader(ostream& out, string_view fileName, int lineNumber, string_view functionName) {
    out << "| ";
    printCurrentDateTime(out);
    out << " | ";
    printStringAndShortenIfPossible(out, fileName, 10, 20);
    out << ":" << lineNumber << " | ";
    printStringAndShortenIfPossible(out, functionName, 10, 40);
    out << "(...) | ";
}

void printCurrentDateTime(ostream& out) {
    AlbaDateTime currentTime(convertSystemTimeToAlbaDateTime(getSystemTimeNow()));
    out << currentTime.getPrintObject<AlbaDateTime::PrintFormat::Standard>();
}

void printStringAndShortenIfPossible(
    ostream& out, string_view longStr, size_t const prefixLength, size_t const suffixLength) {
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
