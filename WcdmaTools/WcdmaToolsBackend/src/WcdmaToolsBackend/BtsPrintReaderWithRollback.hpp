#pragma once

#include <WcdmaToolsBackend/BtsLogPrint.hpp>

#include <fstream>

namespace wcdmaToolsBackend {

class BtsPrintReaderWithRollback {
public:
    BtsPrintReaderWithRollback() = default;
    [[nodiscard]] bool isGood() const;
    void clear();
    void rollBackPrint();
    void openIfNeeded(std::string const& filePath);
    BtsLogPrint getPrint();
    double getCurrentLocation();

private:
    bool m_isRollbackActivated{false};
    BtsLogPrint m_previousPrint;
    std::ifstream m_inputStream;
};

}  // namespace wcdmaToolsBackend
