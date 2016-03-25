#include "WebCrawler.hpp"

#include <CrawlConfiguration/CrawlConfiguration.hpp>
#include <CurlInterface.hpp>
using namespace curl::CurlInterface;

namespace alba
{

bool WebCrawler::downloadBinaryFile(
        AlbaWebPathHandler const& fileToDownloadWebPathHandler,
        AlbaWindowsPathHandler const& downloadPathHandler) const
{    bool isSuccessful(false);
    CrawlConfiguration configuration(m_mode);
    if(configuration.isFileToBeDownloadUntilSuccessful())
    {
        isSuccessful = downloadBinaryFileUntilSuccessful<ConfigType::LowSpeedLimitAndMozillaFireFoxAndPrintDownloadProgress>(fileToDownloadWebPathHandler, downloadPathHandler);
    }
    else
    {
        isSuccessful = downloadBinaryFileWithFiniteNumberOfTries<ConfigType::LowSpeedLimitAndMozillaFireFoxAndPrintDownloadProgress>(fileToDownloadWebPathHandler, downloadPathHandler, configuration.getNumberOfRetries());
    }
    return isSuccessful;
}

bool WebCrawler::downloadFileAsText(
        AlbaWebPathHandler const& fileToDownloadWebPathHandler,
        AlbaWindowsPathHandler const& downloadPathHandler) const
{    return downloadUntilSuccessful<ConfigType::LowSpeedLimitAndMozillaFireFox>(fileToDownloadWebPathHandler, downloadPathHandler);
}

}
