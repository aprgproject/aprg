#pragma once

#include <SymbolTableFileType.hpp>

#include <map>
#include <string>

namespace alba {

class BtsTraceDecoder {
public:
    using SymbolMapType = std::map<unsigned int, std::string>;
    BtsTraceDecoder();
    void saveSymbolTableFromObjdump(std::string const& symbolTableFilePath);
    void saveSymbolTableFromMappedFile(std::string const& symbolTableFilePath);
    void processInputTraceFile(std::string const& inputTraceFilePath);
    std::string getNearestLowerSymbol(int const address, int const offset = 0);

private:
    void saveSymbolTable(std::string const& symbolTableFilePath, SymbolTableFileType const filetype);
    void saveLineInSymbolMapIfValid(int const address, std::string const& lineInFile);
    static int getAddressFromLineInFile(std::string const& lineInFile, SymbolTableFileType const filetype);
    SymbolMapType m_symbolMap;
};

}  // namespace alba
