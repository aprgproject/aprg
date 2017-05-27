#pragma once

#include <set>
#include <string>
#include <vector>

namespace alba
{

class CPlusPlusFileFixer
{
public:
    void processDirectory(std::string const& path);
    void processFile(std::string const& path);

private:
    void clear();
    void checkFile(std::string const& path);
    void fix(std::string const& path);
    void writeFile(std::string const& path);
    void notifyIfThereAreCommentsInHeader(std::string const& path, std::string const& line) const;
    void notifyIfIostreamHeaderExistInProductionCode(std::string const& path) const;
    void notifyIfCAssertHeaderExistInProductionCode(std::string const& path) const;
    void fixHeaders(std::string const& path);
    void removeTrailingLinesInCode();
    void fixNamespaces();
    void addHeaderFileFromAngleBrackets(std::string const& header);
    void addHeaderFileFromQuotations(std::string const& header);
    bool isPathIgnored(std::string const& path) const;
    bool isCPlusPlusHeader(std::string const& header) const;
    bool isQtHeader(std::string const& header) const;
    bool isOtherLibraryHeaders(std::string const& header) const;
    bool isMainHeader(std::string const& headerFoundInFile, std::string const& filePath) const;

    std::vector<std::string> m_linesAfterTheHeader;
    std::vector<std::string> m_headerListFromAngleBrackets;
    std::set<std::string> m_headerListFromQuotations;
    bool m_isPragmaOnceFound;
};

}
