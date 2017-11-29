#include "Downloaders.hpp"

#include <CrawlConfiguration/CrawlConfiguration.hpp>
#include <CrawlHelpers/AutomatedFirefoxBrowser.hpp>
#include <CurlInterface.hpp>

#include <windows.h>

#include <iostream>
#include <string>

using namespace alba;
using namespace curl::CurlInterface;
using namespace std;

namespace aprgWebCrawler
{

bool Downloaders::downloadBinaryFile(
        AlbaWebPathHandler const& fileToDownloadWebPathHandler,
        AlbaLocalPathHandler const& downloadPathHandler,
        CrawlMode mode)
{
    bool isSuccessful(false);
    CrawlConfiguration configuration(mode);
    DownloadLowSpeedLimitConfigurationOptional downloadLowSpeedLimitConfigurationOptional(configuration.getDownloadLowSpeedLimitConfigurationOptional());
    if(downloadLowSpeedLimitConfigurationOptional)
    {
        curl::CurlInterface::lowSpeedLimit = downloadLowSpeedLimitConfigurationOptional.getReference().m_lowSpeedLimit;
        curl::CurlInterface::lowSpeedTime = downloadLowSpeedLimitConfigurationOptional.getReference().m_lowSpeedTime;
    }
    if(configuration.isFileToBeDownloadUntilSuccessful())
    {
        isSuccessful = downloadBinaryFileUntilSuccessful<DownloadType::LowSpeedLimit, DownloadType::MozillaFireFox, DownloadType::PrintDownloadProgress>(fileToDownloadWebPathHandler, downloadPathHandler);
    }
    else
    {
        isSuccessful = downloadBinaryFileWithFiniteNumberOfTries<DownloadType::LowSpeedLimit, DownloadType::MozillaFireFox, DownloadType::PrintDownloadProgress>(fileToDownloadWebPathHandler, downloadPathHandler, configuration.getNumberOfRetries());
    }
    return isSuccessful;
}
/*
bool Downloaders::downloadFileWithDefaultSettings(
        AlbaWebPathHandler const& fileToDownloadWebPathHandler,
        AlbaLocalPathHandler const& downloadPathHandler)
{
    return downloadUntilSuccessful<DownloadType::LowSpeedLimit, DownloadType::MozillaFireFox>(fileToDownloadWebPathHandler, downloadPathHandler);
}
*/

bool Downloaders::downloadFileWithDefaultSettings(
        AlbaWebPathHandler const& fileToDownloadWebPathHandler,
        AlbaLocalPathHandler const& downloadPathHandler)
{
    AutomatedFirefoxBrowser::getInstance().downloadFileWithDefaultSettings(fileToDownloadWebPathHandler.getFullPath(), downloadPathHandler.getFullPath());
    return true;
}

}
