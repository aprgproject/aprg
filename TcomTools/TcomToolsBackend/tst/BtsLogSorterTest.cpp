#include <BtsLogSorterTest.hpp>

using namespace alba;
using namespace std;

namespace tcomToolsBackend
{

BtsLogSorterTest::BtsLogSorterTest()
{
    m_configuration.m_pathOfTempFiles = APRG_DIR R"(TcomTools\TcomToolsBackend\tst\TempFiles\)";
    m_configuration.m_condition = R"( ([syslog]&&[.log]) || [ccns.log] || [tcom.log] || (([startup]||[runtime]||[system])&&[.log]) || ([UDP]&&([.log]||[.txt])) )";
    m_configuration.m_configurationWithPcTime.m_directoryForBlocks = APRG_DIR R"(TcomTools\TcomToolsBackend\tst\TempFiles\WithPcTimeBlocks)";
    m_configuration.m_configurationWithPcTime.m_minimumNumberOfObjectsPerBlock = 10000;
    m_configuration.m_configurationWithPcTime.m_maximumNumberOfObjectsPerBlock = 100000;
    m_configuration.m_configurationWithPcTime.m_maximumNumberOfObjectsInMemory = 200000;
    m_configuration.m_configurationWithPcTime.m_maximumFileStreams = 70;
    m_configuration.m_configurationWithoutPcTime.m_directoryForBlocks = APRG_DIR R"(TcomTools\TcomToolsBackend\tst\TempFiles\WithoutPcTimeBlocks)";
    m_configuration.m_configurationWithoutPcTime.m_minimumNumberOfObjectsPerBlock = 10000;
    m_configuration.m_configurationWithoutPcTime.m_maximumNumberOfObjectsPerBlock = 100000;
    m_configuration.m_configurationWithoutPcTime.m_maximumNumberOfObjectsInMemory = 200000;
    m_configuration.m_configurationWithoutPcTime.m_maximumFileStreams = 70;
}

}
