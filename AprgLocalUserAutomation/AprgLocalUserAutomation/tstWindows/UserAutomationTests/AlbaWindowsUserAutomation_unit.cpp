#include <UserAutomation/AlbaWindowsUserAutomation.hpp>

#include <gtest/gtest.h>

#include <windows.h>

#include <iostream>

using namespace std;

namespace alba {

TEST(AlbaWindowsUserAutomationTest, DISABLED_TypeSmallLetterTest) {
    AlbaWindowsUserAutomation const userAutomation;
    for (char c = 'a'; c <= 'z'; ++c) {
        alba::AlbaWindowsUserAutomation::typeCharacter(c);
    }
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_TypeCapitalLetterTest) {
    AlbaWindowsUserAutomation const userAutomation;
    for (char c = 'A'; c <= 'Z'; ++c) {
        alba::AlbaWindowsUserAutomation::typeCharacter(c);
    }
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_TypeNumberTest) {
    AlbaWindowsUserAutomation const userAutomation;
    for (char c = '0'; c <= '9'; ++c) {
        alba::AlbaWindowsUserAutomation::typeCharacter(c);
    }
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_TypeString) {
    AlbaWindowsUserAutomation const userAutomation;
    userAutomation.typeString(R"(.......)");
    // userAutomation.typeString(R"(`~!@#$%^&*()_+-=[]\{}|;':",./<>?)");
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_SaveBitmapOnScreen) {
    string const bitmapFilePath = APRG_DIR R"(\AprgLocalUserAutomation\FilesForTests\BitmapFromScreen.bmp)";
    AlbaWindowsUserAutomation const userAutomation;
    alba::AlbaWindowsUserAutomation::saveBitmapOnScreen(bitmapFilePath);
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_ShowMousePositions) {
    AlbaWindowsUserAutomation const userAutomation;
    while (1) {
        MousePosition const position(alba::AlbaWindowsUserAutomation::getMousePosition());
        cout << "X: " << position.getX() << " Y: " << position.getY() << "\n";
        cout.flush();
        if (alba::AlbaWindowsUserAutomation::isLetterPressed('s') || (0 == position.getX() && 0 == position.getY())) {
            break;
        }
        Sleep(100);
    }
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_GetClassNameOfForegroundWindow) {
    AlbaWindowsUserAutomation const userAutomation;
    cout << alba::AlbaWindowsUserAutomation::getClassNameOfForegroundWindow() << "\n";
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_GetStringFromClipboard) {
    AlbaWindowsUserAutomation const userAutomation;
    cout << alba::AlbaWindowsUserAutomation::getStringFromClipboard() << "\n";
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_IsKeyPressedTest) {
    AlbaWindowsUserAutomation const userAutomation;
    while (1) {
        auto key = VK_CONTROL;
        bool const isPressed = alba::AlbaWindowsUserAutomation::isKeyPressed(key);
        cout << " isPressed: " << isPressed << "\n";
        if (isPressed) {
            break;
        }
        Sleep(100);
    }
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_IsLetterPressedTest) {
    AlbaWindowsUserAutomation const userAutomation;
    while (1) {
        char const letter = 'q';
        bool const isPressed = alba::AlbaWindowsUserAutomation::isLetterPressed(letter);
        cout << "letter: " << letter << " isPressed: " << isPressed << "\n";
        if (isPressed) {
            break;
        }
        Sleep(100);
    }
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_SetMouseTest) {
    AlbaWindowsUserAutomation const userAutomation;
    for (int x = 0; x < 100; ++x) {
        MousePosition const position{x, x};
        alba::AlbaWindowsUserAutomation::setMousePosition(position);
    }
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_KeyPressDownAndUpSmallLetterTest) {
#define VK_CONTROL 0x11
    AlbaWindowsUserAutomation const userAutomation;
    alba::AlbaWindowsUserAutomation::pressKey(VK_CONTROL);
    alba::AlbaWindowsUserAutomation::pressKey('A');
    alba::AlbaWindowsUserAutomation::releaseKey(VK_CONTROL);
    alba::AlbaWindowsUserAutomation::releaseKey('A');
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_SetActiveWindowBasedClassName) {
    AlbaWindowsUserAutomation const userAutomation;
    alba::AlbaWindowsUserAutomation::setForegroundWindowWithClassName("Notepad");
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_SetActiveWindowBasedWindowName) {
    AlbaWindowsUserAutomation const userAutomation;
    alba::AlbaWindowsUserAutomation::setForegroundWindowWithWindowName("Untitled - Notepad");
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_SetStringFromClipboard) {
    AlbaWindowsUserAutomation const userAutomation;
    alba::AlbaWindowsUserAutomation::setStringToClipboard("TestString");
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_SaveBitmapFromClipboard) {
    string const bitmapFilePath = APRG_DIR R"(\AprgLocalUserAutomation\FilesForTests\BitmapFromClipboard.bmp)";
    AlbaWindowsUserAutomation const userAutomation;
    alba::AlbaWindowsUserAutomation::saveBitmapFromClipboard(bitmapFilePath);
}

}  // namespace alba
