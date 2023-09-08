#pragma once

#include <WcdmaToolsBackend/BtsLogPrint.hpp>

#include <fstream>

namespace wcdmaToolsBackend {

class BtsPrintReaderWithRollback {
public:
    BtsPrintReaderWithRollback();
    bool isGood() const;
    double getCurrentLocation();
    BtsLogPrint getPrint();
    void clear();
    void rollBackPrint();
    void openIfNeeded(std::string const& filePath);

private:
    bool m_isRollbackActivated{false};
    BtsLogPrint m_previousPrint;
    std::ifstream m_inputStream;
};

}  // namespace wcdmaToolsBackend
