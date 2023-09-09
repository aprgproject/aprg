#pragma once

#include <set>
#include <string>
#include <vector>

namespace alba {

class CPlusPlusFileFixer {
public:
    void processDirectory(std::string const& path);
    void processFile(std::string const& path);

private:
    [[nodiscard]] static bool isOtherLibraryHeaders(std::string const& header);
    static void notifyIfThereAreCommentsInHeader(std::string const& path, std::string const& line);
    static bool isLineWithALoopStart(std::string const& line);
    static bool isLineWithALoopEnd(std::string const& line);
    static bool isPathIgnored(std::string const& path);
    static bool isCPlusPlusHeader(std::string const& header);
    static bool isLinuxHeader(std::string const& header);
    static bool isWindowsHeader(std::string const& header);
    static bool isGtestHeader(std::string const& header);
    static bool isQtHeader(std::string const& header);
    void notifyIfAlbaDebugHeaderExistInProductionCode(std::string const& path) const;
    void notifyIfIostreamHeaderExistInProductionCode(std::string const& path) const;
    void notifyIfCAssertHeaderExistInProductionCode(std::string const& path) const;
    void notifyIfMoreThanLoopsAreCascaded(std::string const& path) const;
    void writeHeadersWithQuotations(std::ofstream& outputLogFileStream) const;
    void writeHeadersWithAngleBrackets(std::ofstream& outputLogFileStream) const;
    void clear();
    void checkFile(std::string const& path);
    void readContentsFromFile(std::string const& path);
    void readLineWithSharpInclude(std::string const& line, std::string const& path);
    void fix(std::string const& path);
    void fixHeaders(std::string const& path);
    void removeTrailingLinesInCode();
    void fixNamespaces();
    void fixSmallUToCapitalUInNumbers();
    void addHeaderFileFromAngleBrackets(std::string const& header);
    void addHeaderFileFromQuotations(std::string const& header);
    void writeFile(std::string const& path);
    std::vector<std::string> m_linesAfterTheHeader;
    std::vector<std::string> m_headerListFromAngleBrackets;
    std::set<std::string> m_headerListFromQuotations;
    bool m_isPragmaOnceFound{};
};

}  // namespace alba
