#pragma once

#include <Common/PathHandler/AlbaPathHandler.hpp>

#include <string>

namespace alba {

class AlbaWebPathHandler : public AlbaPathHandler {
public:
    explicit AlbaWebPathHandler(std::string_view path);
    // no need for virtual destructor because base destructor is virtual (similar to other virtual functions)

    void clear() override;
    [[nodiscard]] std::string getFullPath() const override;
    [[nodiscard]] std::string getDirectory() const override;
    [[nodiscard]] bool hasProtocol() const;
    [[nodiscard]] std::string getProtocol() const;
    void gotoLink(std::string_view newPath);
    void setProtocolWithSymbols(std::string_view protocolWithSymbols);

private:
    void save(std::string_view path) override;
    void setPath(std::string_view path);
    void splitPathToBeforeAndAfterProtocol(
        std::string_view path, std::string& protocolWithSymbols, std::string& pathAfterProtocol);
    void setUrlParameters(std::string_view urlParameters);
    std::string m_protocolWithSymbols;
    std::string m_urlParameters;
    bool m_hasProtocol{false};
};

}  // namespace alba
