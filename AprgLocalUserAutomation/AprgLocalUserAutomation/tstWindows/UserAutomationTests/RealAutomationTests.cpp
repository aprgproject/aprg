#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/Print/AlbaLogPrints.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <UserAutomation/AlbaLocalUserAutomation.hpp>

#include <gtest/gtest.h>

#include <windows.h>

#include <sstream>

using namespace alba::stringHelper;
using namespace std;

namespace alba::AlbaWindowsUserAutomation {

TEST(RealAutomationTest, DISABLED_TraverseTalonRoShops) {
    // DISABLED_
    // AlbaLocalPathHandler itemDatabaseFolder(R"(C:\Users\detectivemark7\Desktop\RO\TalonRO\BuyingShops\)");
    AlbaLocalPathHandler const itemDatabaseFolder(R"(C:\Users\detectivemark7\Desktop\RO\TalonRO\SellingShops\)");

    doLeftClickAt(MousePosition(2368, 52));

    // string talonRoPath(R"(https://panel.talonro.com/whobuy/)");
    string const talonRoPath(R"(https://panel.talonro.com/whosell/)");
    typeKey(VK_DELETE);
    setStringToClipboard(talonRoPath);
    performKeyCombination({VK_CONTROL}, {'V'});
    typeKey(VK_RETURN);

    sleep(3000);

    for (int page = 1; page <= 1000; ++page) {
        performKeyCombination({VK_CONTROL}, {'S'});
        sleep(2000);

        stringstream fileName;
        fileName << "page_" << page << ".html";
        AlbaLocalPathHandler const filePathHandler(itemDatabaseFolder.getPath() / fileName.str());
        setStringToClipboard(filePathHandler.getPath().string());
        performKeyCombination({VK_CONTROL}, {'V'});
        typeKey(VK_RETURN);
        typeKey(VK_RETURN);
        typeKey(VK_RETURN);
        typeKey(VK_RETURN);

        sleep(2000);

        ifstream savedWebPage(filePathHandler.getPath());
        AlbaFileReader fileReader(savedWebPage);
        fileReader.setMaxBufferSize(100000);
        bool isNextDisabled(false);
        while (fileReader.isNotFinished()) {
            string const line(fileReader.getLineAndIgnoreWhiteSpaces());
            if (isStringFoundCaseSensitive(line, R"(class="paginate_button page-item next disabled")")) {
                isNextDisabled = true;
                break;
            }
        }
        if (isNextDisabled) {
            break;
        }
        doLeftClickAt(MousePosition(3398, 514));
        doLeftClickAt(MousePosition(2368, 52));
        sleep(2000);
    }
}

TEST(RealAutomationTest, DISABLED_TraverseDatabaseOnRms) {
    AlbaLocalPathHandler const itemDatabaseFolder(
        R"(C:\Users\detectivemark7\Desktop\RO\RMS\MonsterDatabaseTraversal\)");

    for (char letter = 'a'; letter <= 'z'; ++letter) {
        for (int pageNumber = 1; pageNumber <= 100; ++pageNumber) {
            doLeftClickAt(MousePosition(2368, 52));

            stringstream rmsPath;
            rmsPath << R"(https://ratemyserver.net/index.php?page=mob_db&list=1&letter=)" << letter << R"(&page_num=)"
                    << pageNumber;
            typeKey(VK_DELETE);
            setStringToClipboard(rmsPath.str());
            performKeyCombination({VK_CONTROL}, {'V'});
            typeKey(VK_RETURN);

            sleep(3000);

            performKeyCombination({VK_CONTROL}, {'S'});
            stringstream fileName;
            fileName << "monsterWithLetter_" << letter << "_pageNumber_" << pageNumber << ".html";
            AlbaLocalPathHandler const filePathHandler(itemDatabaseFolder.getPath() / fileName.str());
            setStringToClipboard(filePathHandler.getPath().string());
            performKeyCombination({VK_CONTROL}, {'V'});
            typeKey(VK_RETURN);
            typeKey(VK_RETURN);
            typeKey(VK_RETURN);
            typeKey(VK_RETURN);

            ifstream savedWebPage(filePathHandler.getPath());
            AlbaFileReader fileReader(savedWebPage);
            bool isNextPageTextFound(false);
            while (fileReader.isNotFinished()) {
                string const line(fileReader.getLineAndIgnoreWhiteSpaces());
                if (isStringFoundCaseSensitive(line, R"(title="Next page")")) {
                    isNextPageTextFound = true;
                    break;
                }
            }
            if (!isNextPageTextFound) {
                break;
            }
        }
    }
}

TEST(RealAutomationTest, DISABLED_NormalizeAudioForMp3Files) {
    AlbaLocalPathHandler const mp3FilesPathHandler(R"(N:\MUSIC\111_DoAutomationHere)");

    while (true) {
        if (isLetterPressed('s')) {
            // s for start
            mp3FilesPathHandler.findFilesAndDirectoriesOneDepth(
                [](AlbaLocalPathHandler::LocalPath const&) {},
                [&](AlbaLocalPathHandler::LocalPath const& filePath) {
                    AlbaLocalPathHandler const filePathHandler(filePath);
                    if (filePathHandler.getExtension() == "mp3" && filePathHandler.getFileSize() < 100000000) {
                        // 100MB
                        // close previous file
                        performKeyCombination({VK_CONTROL}, {'W'});
                        sleep(1000);
                        typeKey(VK_RIGHT);
                        typeKey(VK_RETURN);
                        sleep(2000);

                        // open file
                        performKeyCombination({VK_CONTROL}, {'O'});
                        sleep(1000);

                        // paste file name
                        setStringToClipboard(filePathHandler.getFile().string());
                        performKeyCombination({VK_CONTROL}, {'V'});

                        // type enter key
                        typeKey(VK_RETURN);

                        // wait for the file to load
                        sleep(10000);

                        // select all track
                        performKeyCombination({VK_CONTROL}, {'A'});

                        // click effect
                        doDoubleLeftClickAt(MousePosition(344, 33));

                        // click normalization
                        doDoubleLeftClickAt(MousePosition(433, 443));

                        // type enter key
                        typeKey(VK_RETURN);

                        // wait for normalization process
                        sleep(10000);

                        // export
                        performKeyCombination({VK_CONTROL, VK_SHIFT}, {'E'});
                        sleep(2000);

                        // type enter key multiple times
                        sleep(1000);
                        typeKey(VK_RETURN);  // save
                        sleep(1000);
                        typeKey('Y');  // yes to replace
                        sleep(1000);
                        doDoubleLeftClickAt(MousePosition(1074, 687));  // click ok
                        typeKey(VK_RIGHT);                              // type right to avoid stop button
                                                                        // wait for export process
                        sleep(15000);

                        // type enter key multiple times to ensure everything is closed
                        typeKey(VK_RETURN);
                        typeKey(VK_RETURN);
                        typeKey(VK_RETURN);
                        typeKey(VK_RETURN);
                        typeKey(VK_RETURN);

                        // close file
                        performKeyCombination({VK_CONTROL}, {'W'});
                        sleep(1000);
                        typeKey(VK_RIGHT);
                        typeKey(VK_RETURN);
                        sleep(2000);

                        // break;
                    } else {
                        cout << "Ignored file: " << filePath << ": size: " << filePathHandler.getFileSize() << "\n";
                    }
                });
            break;
        }
        Sleep(100);
    }
}

TEST(RealAutomationTest, DISABLED_DownloadFacebookImagesFromFirefox) {
    while (true) {
        ALBA_INF_PRINT1(cout, "next image");
        performKeyCombination({VK_CONTROL}, {'L'});
        sleep(1000);

        performKeyCombination({VK_CONTROL}, {'C'});
        sleep(1000);

        ALBA_INF_PRINT1(cout, "check for exit");
        string const url = getStringFromClipboard();
        if (isLetterPressed('a') ||
            url == R"(https://www.facebook.com/photo?fbid=10227411012716536&set=t.100000122270987)") {
            break;
        }

        doLeftClickAt(MousePosition(3377, 116));
        sleep(1000);
        doLeftClickAt(MousePosition(3377, 116));
        sleep(1000);

        ALBA_INF_PRINT1(cout, "clicks");
        doRightClickAt(MousePosition(2740, 592));
        sleep(1000);
        doLeftClickAt(MousePosition(2794, 643));
        sleep(3000);
        typeKey(VK_RETURN);
        sleep(1000);
        typeKey('Y');
        sleep(1000);
        typeKey(VK_RIGHT);
        sleep(5000);
    }
}

TEST(RealAutomationTest, DISABLED_GetOutputFromChatGpt) {
    ifstream commitMessagesStream(R"(F:\Branches\aprg_test\Migrate\git_old_repo\commitMessagesNoQuotations.txt)");
    ofstream newCommitMessagesStream(
        R"(F:\Branches\aprg_test\Migrate\git_old_repo\newCommitMessages.txt)", ios_base::app);
    AlbaFileReader commitMessagesReader(commitMessagesStream);

    constexpr int NUMBER_OF_LINES_TO_SEND = 20;
    int lineCount = 1;
    constexpr int lineCountToStart = 1641;
    int pendingNumberOfLines = 0;
    string const requestHeader =
        "improve each commit message (in each line) to be more professional and short (and dont put numbers per each "
        "line and maintain line ordering):\r\n";
    string requestToChatGpt = requestHeader;

    sleep(3000);

    while (commitMessagesReader.isNotFinished()) {
        // PAUSE for stop
        if (isLetterPressed(VK_PAUSE)) {
            break;
        }
        string const line(commitMessagesReader.getLineAndIgnoreWhiteSpaces());
        if (lineCountToStart > lineCount) {
            ALBA_INF_PRINT3(cout, "skipping", lineCountToStart, lineCount);
        } else {
            if (pendingNumberOfLines < NUMBER_OF_LINES_TO_SEND) {
                requestToChatGpt += line;
                requestToChatGpt += "\r\n";
                ++pendingNumberOfLines;
            } else {
                // loop until its confirm that request is in the text box (PAUSE for stop)
                ALBA_INF_PRINT1(cout, lineCount);
                int retries = 0;
                string fromClipboard;
                while (!isLetterPressed(VK_PAUSE)) {
                    ++retries;
                    ALBA_INF_PRINT1(cout, retries);
                    if (retries > 10) {
                        typeKey(VK_F5);
                        sleep(10000);
                    } else if (retries > 3) {
                        doLeftClickAt(MousePosition(2030, 110));
                        sleep(2000);
                    }

                    // Click at Chat GPT text box
                    setStringToClipboard(requestToChatGpt);
                    doLeftClickAt(MousePosition(2990, 955));
                    sleep(2000);

                    // Select All
                    performKeyCombination({VK_CONTROL}, {'A'});
                    sleep(2000);

                    // Paste
                    performKeyCombination({VK_CONTROL}, {'V'});
                    sleep(2000);

                    // Select All
                    performKeyCombination({VK_CONTROL}, {'A'});
                    sleep(2000);

                    // Double check if text is really on the text box
                    setStringToClipboard("");
                    performKeyCombination({VK_CONTROL}, {'C'});
                    sleep(2000);

                    fromClipboard = getStringFromClipboard();

                    ALBA_INF_PRINT1(cout, requestToChatGpt);
                    ALBA_INF_PRINT1(cout, fromClipboard);
                    if (requestToChatGpt != fromClipboard) {
                        continue;
                    }

                    // Send request to chat gpt by pressing enter
                    typeKey(VK_RETURN);

                    // Wait for chat gpt
                    sleep(20000);

                    // Clear clipboard, press copy button
                    setStringToClipboard("");
                    for (int yClick = 100; yClick <= 400; yClick += 5) {
                        doLeftClickAt(MousePosition(3345, yClick));
                    }
                    sleep(2000);

                    // Save output to file
                    string outputOfChatGpt = getStringFromClipboard();
                    ALBA_INF_PRINT1(cout, outputOfChatGpt);
                    if (outputOfChatGpt.empty()) {
                        continue;
                    }
                    newCommitMessagesStream << outputOfChatGpt;
                    if (outputOfChatGpt.back() != '\n') {
                        newCommitMessagesStream << "\n";
                    }
                    break;
                }

                requestToChatGpt = requestHeader + line + "\r\n";
                pendingNumberOfLines = 1;
            }
        }
        ++lineCount;
    }
}

}  // namespace alba::AlbaWindowsUserAutomation
