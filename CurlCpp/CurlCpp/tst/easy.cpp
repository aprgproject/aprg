#include <AlbaWebPathHandler.hpp>
#include <AlbaWindowsPathHandler.hpp>
#include "curl_easy.h"
#include "curl_option.h"
#include "CurlInterface.hpp"

using curl::CurlInterface::downloadBinaryFile;
using curl::curl_easy;
using curl::make_option;

#include <set>
using namespace std;

int main()
{
    /*AlbaWebPathHandler webPathHandler();
    AlbaWindowsPathHandler windowPathHandler("hello.mp4");
    downloadBinaryFile<ConfigType::LowSpeedLimitAndMozillaFireFoxAndPrintDownloadProgress>(windowPathHandler);*/

    AlbaWindowsPathHandler libArchive;
    libArchive.inputPath(R"(C:\APRG\libarchive-3.1.2\libarchive-3.1.2)");
    set<string> listOfFiles;
    set<string> listOfDirectories;
    libArchive.findFilesAndDirectoriesUnlimitedDepth("*.*", listOfFiles, listOfDirectories);

    for(string const& file:listOfFiles)
    {
        cout<<file<<endl;
    }
    return 0;
}

int main_curl_easy()
{
    curl_easy easy;

    easy.add<CURLOPT_URL>("http://mangafox.me/manga/kateikyoushi_hitman_reborn/v02/c014/4.html");
    easy.add<CURLOPT_FOLLOWLOCATION>(1L);

    try {
        easy.perform();
    }
    catch (curl_easy_exception error) {
        // If you want to get the entire error stack we can do:
        auto errors = error.what();
        // Otherwise we could print the stack like this:
        error.print_traceback();
        // Note that the printing the stack will erase it
    }

    return 0;
}
