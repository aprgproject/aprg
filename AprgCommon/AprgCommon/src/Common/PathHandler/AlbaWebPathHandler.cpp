#include "AlbaWebPathHandler.hpp"

#include <Common/String/AlbaStringHelper.hpp>

#include <functional>
#include <string>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

AlbaWebPathHandler::AlbaWebPathHandler(string_view const path) : AlbaPathHandler("/") { setPath(path); }

string AlbaWebPathHandler::getProtocol() const {
    string protocol;
    int const index = static_cast<int>(m_protocolWithSymbols.find_first_of(R"(:/\)"));
    if (isNotNpos(index) && m_protocolWithSymbols[static_cast<string::size_type>(index)] == ':') {
        protocol =
            getStringWithLowerCaseLetters(m_protocolWithSymbols.substr(0, static_cast<string::size_type>(index)));
    }
    return protocol;
}

bool AlbaWebPathHandler::hasProtocol() const { return m_hasProtocol; }

void AlbaWebPathHandler::gotoLink(string_view const newPath) {
    AlbaWebPathHandler const newPathHandler(newPath);
    if (newPathHandler.hasProtocol()) {
        input(newPath);
    } else {
        input(getDirectory() + string(newPath));
    }
}

void AlbaWebPathHandler::setProtocolWithSymbols(string_view const protocolWithSymbols) {
    m_protocolWithSymbols = protocolWithSymbols;
    int const index = static_cast<int>(protocolWithSymbols.find_first_of(R"(:/\)"));
    if (isNotNpos(index) && protocolWithSymbols[static_cast<string::size_type>(index)] == ':') {
        m_hasProtocol = true;
    }
}

void AlbaWebPathHandler::save(string_view const path) { setPath(path); }

void AlbaWebPathHandler::setPath(string_view const path) {
    string protocolWithSymbols;
    string pathAfterProtocol;
    splitPathToBeforeAndAfterProtocol(path, protocolWithSymbols, pathAfterProtocol);
    string const correctPathAfterProtocol(
        getCorrectPathWithReplacedSlashCharacters(pathAfterProtocol, m_slashCharacterString));
    string const correctPathAfterProtocolWithoutUrlParameters(
        getCorrectPathWithoutUrlParameters(correctPathAfterProtocol));
    setProtocolWithSymbols(protocolWithSymbols);
    setExtensionFromPath(correctPathAfterProtocolWithoutUrlParameters);
    setDirectoryAndFileFromPath(correctPathAfterProtocolWithoutUrlParameters);
    setFileType();
    setUrlParameters(getUrlParameters(correctPathAfterProtocol));
}

void AlbaWebPathHandler::splitPathToBeforeAndAfterProtocol(
    string_view const path, string& protocolWithSymbols, string& pathAfterProtocol) {
    int const indexBeforeProtocol = static_cast<int>(path.find("://"));
    int const indexBeforeSlash = static_cast<int>(path.find_first_of(m_slashCharacterString));
    if (isNotNpos(indexBeforeProtocol) && isNotNpos(indexBeforeSlash) && indexBeforeProtocol < indexBeforeSlash) {
        protocolWithSymbols = path.substr(0, static_cast<string::size_type>(indexBeforeProtocol) + 3);
        pathAfterProtocol = path.substr(static_cast<string::size_type>(indexBeforeProtocol) + 3);
    } else {
        protocolWithSymbols.clear();
        pathAfterProtocol = path;
    }
}

void AlbaWebPathHandler::setUrlParameters(string_view const urlParameters) { m_urlParameters = urlParameters; }

string AlbaWebPathHandler::getPath() const { return m_protocolWithSymbols + m_directory + m_file + m_urlParameters; }

string AlbaWebPathHandler::getDirectory() const { return m_protocolWithSymbols + m_directory; }

void AlbaWebPathHandler::clear() {
    AlbaPathHandler::clear();
    m_protocolWithSymbols.clear();
    m_urlParameters.clear();
    m_hasProtocol = false;
}

}  // namespace alba
