#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <WcdmaToolsBackendTests/BtsLogSorterTest.hpp>

using namespace alba;
using namespace std;

namespace wcdmaToolsBackend {

BtsLogSorterTest::BtsLogSorterTest() {
    m_configuration.m_pathOfTempFiles =
        AlbaLocalPathHandler(APRG_DIR R"(\WcdmaTools\WcdmaToolsBackend\FilesForTests\TempFiles\)").getPath();
    m_configuration.m_isFilterGrepOn = false;
    m_configuration.m_acceptedFilesGrepCondition =
        R"( ([syslog]&&[.log]) || [ccns.log] || [tcom.log] || (([startup]||[runtime]||[system])&&[.log]) || ([UDP]&&([.log]||[.txt])) )";
    m_configuration.m_filterGrepCondition = "";
    m_configuration.m_configurationWithPcTime.m_directoryForBlocks =
        AlbaLocalPathHandler(APRG_DIR R"(\WcdmaTools\WcdmaToolsBackend\FilesForTests\TempFiles\WithPcTimeBlocks)")
            .getPath();
    m_configuration.m_configurationWithPcTime.m_minimumNumberOfObjectsPerBlock = 10000;
    m_configuration.m_configurationWithPcTime.m_maximumNumberOfObjectsPerBlock = 100000;
    m_configuration.m_configurationWithPcTime.m_maximumNumberOfObjectsInMemory = 200000;
    m_configuration.m_configurationWithPcTime.m_maximumFileStreams = 70;
    m_configuration.m_configurationWithoutPcTime.m_directoryForBlocks =
        AlbaLocalPathHandler(APRG_DIR R"(\WcdmaTools\WcdmaToolsBackend\FilesForTests\TempFiles\WithoutPcTimeBlocks)")
            .getPath();
    m_configuration.m_configurationWithoutPcTime.m_minimumNumberOfObjectsPerBlock = 10000;
    m_configuration.m_configurationWithoutPcTime.m_maximumNumberOfObjectsPerBlock = 100000;
    m_configuration.m_configurationWithoutPcTime.m_maximumNumberOfObjectsInMemory = 200000;
    m_configuration.m_configurationWithoutPcTime.m_maximumFileStreams = 70;
}

}  // namespace wcdmaToolsBackend
