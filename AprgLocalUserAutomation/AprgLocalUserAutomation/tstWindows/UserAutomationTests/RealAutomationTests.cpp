#include <Common/Debug/AlbaDebug.hpp>
#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <UserAutomation/AlbaLocalUserAutomation.hpp>

#include <gtest/gtest.h>

#include <windows.h>

#include <sstream>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

TEST(RealAutomationTest, DISABLED_TraverseTalonRoShops)  // DISABLED_
{
    AlbaWindowsUserAutomation userAutomation;
    // AlbaLocalPathHandler itemDatabaseFolder(R"(C:\Users\detectivemark7\Desktop\RO\TalonRO\BuyingShops\)");
    AlbaLocalPathHandler itemDatabaseFolder(R"(C:\Users\detectivemark7\Desktop\RO\TalonRO\SellingShops\)");

    userAutomation.doLeftClickAt(MousePosition(2368, 52));

    // string talonRoPath(R"(https://panel.talonro.com/whobuy/)");
    string talonRoPath(R"(https://panel.talonro.com/whosell/)");
    userAutomation.sleepWithRealisticDelay();
    userAutomation.typeKey(VK_DELETE);
    userAutomation.setStringToClipboard(talonRoPath);
    userAutomation.typeControlAndLetterSimultaneously('V');
    userAutomation.sleepWithRealisticDelay();
    userAutomation.typeKey(VK_RETURN);

    userAutomation.sleep(3000);

    for (int page = 1; page <= 1000; page++) {
        userAutomation.typeControlAndLetterSimultaneously('S');
        userAutomation.sleep(2000);

        stringstream fileName;
        fileName << "page_" << page << ".html";
        AlbaLocalPathHandler filePathHandler(itemDatabaseFolder.getFullPath() + fileName.str());
        userAutomation.setStringToClipboard(filePathHandler.getFullPath());
        userAutomation.typeControlAndLetterSimultaneously('V');
        userAutomation.sleepWithRealisticDelay();
        userAutomation.typeKey(VK_RETURN);
        userAutomation.sleepWithRealisticDelay();
        userAutomation.typeKey(VK_RETURN);
        userAutomation.sleepWithRealisticDelay();
        userAutomation.typeKey(VK_RETURN);
        userAutomation.sleepWithRealisticDelay();
        userAutomation.typeKey(VK_RETURN);

        userAutomation.sleep(2000);

        ifstream savedWebPage(filePathHandler.getFullPath());
        AlbaFileReader fileReader(savedWebPage);
        fileReader.setMaxBufferSize(100000);
        bool isNextDisabled(false);
        while (fileReader.isNotFinished()) {
            string line(fileReader.getLineAndIgnoreWhiteSpaces());
            if (isStringFoundCaseSensitive(line, R"(class="paginate_button page-item next disabled")")) {
                isNextDisabled = true;
                break;
            }
        }
        if (isNextDisabled) {
            break;
        } else {
            userAutomation.doLeftClickAt(MousePosition(3398, 514));
            userAutomation.doLeftClickAt(MousePosition(2368, 52));
            userAutomation.sleep(2000);
        }
    }
}

TEST(RealAutomationTest, DISABLED_TraverseDatabaseOnRms) {
    AlbaWindowsUserAutomation userAutomation;
    AlbaLocalPathHandler itemDatabaseFolder(R"(C:\Users\detectivemark7\Desktop\RO\RMS\MonsterDatabaseTraversal\)");

    for (char letter = 'a'; letter <= 'z'; letter++) {
        for (int pageNumber = 1; pageNumber <= 100; pageNumber++) {
            userAutomation.doLeftClickAt(MousePosition(2368, 52));

            stringstream rmsPath;
            rmsPath << R"(https://ratemyserver.net/index.php?page=mob_db&list=1&letter=)" << letter << R"(&page_num=)"
                    << pageNumber;
            userAutomation.sleepWithRealisticDelay();
            userAutomation.typeKey(VK_DELETE);
            userAutomation.setStringToClipboard(rmsPath.str());
            userAutomation.typeControlAndLetterSimultaneously('V');
            userAutomation.sleepWithRealisticDelay();
            userAutomation.typeKey(VK_RETURN);

            userAutomation.sleep(3000);

            userAutomation.typeControlAndLetterSimultaneously('S');
            stringstream fileName;
            fileName << "monsterWithLetter_" << letter << "_pageNumber_" << pageNumber << ".html";
            AlbaLocalPathHandler filePathHandler(itemDatabaseFolder.getFullPath() + fileName.str());
            userAutomation.setStringToClipboard(filePathHandler.getFullPath());
            userAutomation.typeControlAndLetterSimultaneously('V');
            userAutomation.sleepWithRealisticDelay();
            userAutomation.typeKey(VK_RETURN);
            userAutomation.sleepWithRealisticDelay();
            userAutomation.typeKey(VK_RETURN);
            userAutomation.sleepWithRealisticDelay();
            userAutomation.typeKey(VK_RETURN);
            userAutomation.sleepWithRealisticDelay();
            userAutomation.typeKey(VK_RETURN);

            ifstream savedWebPage(filePathHandler.getFullPath());
            AlbaFileReader fileReader(savedWebPage);
            bool isNextPageTextFound(false);
            while (fileReader.isNotFinished()) {
                string line(fileReader.getLineAndIgnoreWhiteSpaces());
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
    AlbaWindowsUserAutomation userAutomation;
    AlbaLocalPathHandler mp3FilesPathHandler(R"(N:\MUSIC\111_DoAutomationHere)");

    while (1) {
        if (userAutomation.isLetterPressed('s'))  // s for start
        {
            ListOfPaths filePaths;
            ListOfPaths directoryPaths;
            mp3FilesPathHandler.findFilesAndDirectoriesOneDepth("*.*", filePaths, directoryPaths);

            for (string const& filePath : filePaths) {
                AlbaLocalPathHandler filePathHandler(filePath);
                if (filePathHandler.getExtension() == "mp3" &&
                    filePathHandler.getFileSizeEstimate() < 100000000)  // 100MB
                {
                    // close previous file
                    userAutomation.typeControlAndLetterSimultaneously('W');
                    userAutomation.sleep(1000);
                    userAutomation.typeKey(VK_RIGHT);
                    userAutomation.typeKey(VK_RETURN);
                    userAutomation.sleep(2000);

                    // open file
                    userAutomation.typeControlAndLetterSimultaneously('O');
                    userAutomation.sleep(1000);

                    // paste file name
                    userAutomation.setStringToClipboard(filePathHandler.getFile());
                    userAutomation.typeControlAndLetterSimultaneously('V');

                    // type enter key
                    userAutomation.typeKey(VK_RETURN);

                    // wait for the file to load
                    userAutomation.sleep(10000);

                    // select all track
                    userAutomation.typeControlAndLetterSimultaneously('A');

                    // click effect
                    userAutomation.doDoubleLeftClickAt(MousePosition(344, 33));

                    // click normalization
                    userAutomation.doDoubleLeftClickAt(MousePosition(433, 443));

                    // type enter key
                    userAutomation.typeKey(VK_RETURN);

                    // wait for normalization process
                    userAutomation.sleep(10000);

                    // export
                    userAutomation.pressKey(VK_CONTROL);
                    userAutomation.pressKey(VK_SHIFT);
                    userAutomation.pressKey('E');
                    userAutomation.sleepWithRealisticDelay();
                    userAutomation.releaseKey('E');
                    userAutomation.releaseKey(VK_SHIFT);
                    userAutomation.releaseKey(VK_CONTROL);
                    userAutomation.sleep(2000);

                    // type enter key multiple times
                    userAutomation.sleep(1000);
                    userAutomation.typeKey(VK_RETURN);  // save
                    userAutomation.sleep(1000);
                    userAutomation.typeKey('Y');  // yes to replace
                    userAutomation.sleep(1000);
                    userAutomation.doDoubleLeftClickAt(MousePosition(1074, 687));  // click ok
                    userAutomation.typeKey(VK_RIGHT);                              // type right to avoid stop button

                    // wait for export process
                    userAutomation.sleep(15000);

                    // type enter key multiple times to ensure everything is closed
                    userAutomation.sleep(250);
                    userAutomation.typeKey(VK_RETURN);
                    userAutomation.sleep(250);
                    userAutomation.typeKey(VK_RETURN);
                    userAutomation.sleep(250);
                    userAutomation.typeKey(VK_RETURN);
                    userAutomation.sleep(250);
                    userAutomation.typeKey(VK_RETURN);

                    // close file
                    userAutomation.typeControlAndLetterSimultaneously('W');
                    userAutomation.sleep(1000);
                    userAutomation.typeKey(VK_RIGHT);
                    userAutomation.typeKey(VK_RETURN);
                    userAutomation.sleep(2000);

                    // break;
                } else {
                    cout << "Ignored file: " << filePath << ": size: " << filePathHandler.getFileSizeEstimate() << "\n";
                }
            }
            break;
        }
        Sleep(100);
    }
}

TEST(RealAutomationTest, GetOutputFromChatGpt) {
    AlbaWindowsUserAutomation userAutomation;
    ifstream commitMessagesStream(R"(F:\Branches\aprg_test\Migrate\git_old_repo\commitMessagesNoQuotations.txt)");
    ofstream newCommitMessagesStream(
        R"(F:\Branches\aprg_test\Migrate\git_old_repo\newCommitMessages.txt)", ios_base::app);
    AlbaFileReader commitMessagesReader(commitMessagesStream);

    constexpr int NUMBER_OF_LINES_TO_SEND = 20;
    int lineCount = 1, lineCountToStart = 1641, pendingNumberOfLines = 0;
    string requestHeader =
        "improve each commit message (in each line) to be more professional and short (and dont put numbers per each "
        "line and maintain line ordering):\r\n";
    string requestToChatGpt = requestHeader;

    userAutomation.sleep(3000);

    while (commitMessagesReader.isNotFinished()) {
        // PAUSE for stop
        if (userAutomation.isLetterPressed(VK_PAUSE)) {
            break;
        }
        string line(commitMessagesReader.getLineAndIgnoreWhiteSpaces());
        if (lineCountToStart > lineCount) {
            ALBA_PRINT3("skipping", lineCountToStart, lineCount);
        } else {
            if (pendingNumberOfLines < NUMBER_OF_LINES_TO_SEND) {
                requestToChatGpt += line;
                requestToChatGpt += "\r\n";
                ++pendingNumberOfLines;
            } else {
                // loop until its confirm that request is in the text box (PAUSE for stop)
                ALBA_PRINT1(lineCount);
                int retries = 0;
                string fromClipboard;
                while (!userAutomation.isLetterPressed(VK_PAUSE)) {
                    ++retries;
                    ALBA_PRINT1(retries);
                    if (retries > 10) {
                        userAutomation.pressKey(VK_F5);
                        userAutomation.sleep(10000);
                    } else if (retries > 3) {
                        userAutomation.doLeftClickAt(MousePosition(2030, 110));
                        userAutomation.sleep(2000);
                    }

                    // Click at Chat GPT text box
                    userAutomation.setStringToClipboard(requestToChatGpt);
                    userAutomation.doLeftClickAt(MousePosition(2990, 955));
                    userAutomation.sleep(2000);

                    // Select All
                    userAutomation.pressKey(VK_CONTROL);
                    userAutomation.pressKey('A');
                    userAutomation.sleepWithRealisticDelay();
                    userAutomation.releaseKey('A');
                    userAutomation.releaseKey(VK_CONTROL);
                    userAutomation.sleep(2000);

                    // Paste
                    userAutomation.pressKey(VK_CONTROL);
                    userAutomation.pressKey('V');
                    userAutomation.sleepWithRealisticDelay();
                    userAutomation.releaseKey('V');
                    userAutomation.releaseKey(VK_CONTROL);
                    userAutomation.sleep(2000);

                    // Select All
                    userAutomation.pressKey(VK_CONTROL);
                    userAutomation.pressKey('A');
                    userAutomation.sleepWithRealisticDelay();
                    userAutomation.releaseKey('A');
                    userAutomation.releaseKey(VK_CONTROL);
                    userAutomation.sleep(2000);

                    // Double check if text is really on the text box
                    userAutomation.setStringToClipboard("");
                    userAutomation.pressKey(VK_CONTROL);
                    userAutomation.pressKey('C');
                    userAutomation.sleepWithRealisticDelay();
                    userAutomation.releaseKey('C');
                    userAutomation.releaseKey(VK_CONTROL);
                    userAutomation.sleep(2000);

                    fromClipboard = userAutomation.getStringFromClipboard();

                    ALBA_PRINT1(requestToChatGpt);
                    ALBA_PRINT1(fromClipboard);
                    if (requestToChatGpt != fromClipboard) {
                        continue;
                    }

                    // Send request to chat gpt by pressing enter
                    userAutomation.typeKey(VK_RETURN);

                    // Wait for chat gpt
                    userAutomation.sleep(20000);

                    // Clear clipboard, press copy button
                    userAutomation.setStringToClipboard("");
                    for (int yClick = 100; yClick <= 400; yClick += 5) {
                        userAutomation.doLeftClickAt(MousePosition(3345, yClick));
                    }
                    userAutomation.sleep(2000);

                    // Save output to file
                    string outputOfChatGpt = userAutomation.getStringFromClipboard();
                    ALBA_PRINT1(outputOfChatGpt);
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

}  // namespace alba
