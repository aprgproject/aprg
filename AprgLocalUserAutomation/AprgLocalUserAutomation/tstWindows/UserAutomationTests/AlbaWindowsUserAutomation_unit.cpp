#include <UserAutomation/AlbaWindowsUserAutomation.hpp>

#include <gtest/gtest.h>

#include <windows.h>

#include <iostream>

using namespace std;

namespace alba::AlbaWindowsUserAutomation {

TEST(AlbaWindowsUserAutomationTest, DISABLED_ShowMousePositions) {
    while (true) {
        MousePosition const position(getMousePosition());
        cout << "X: " << position.getX() << " Y: " << position.getY() << "\n";
        cout.flush();
        if (isLetterPressed('s') || (0 == position.getX() && 0 == position.getY())) {
            break;
        }
        Sleep(100);
    }
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_GetClassNameOfForegroundWindow) {
    cout << getClassNameOfForegroundWindow() << "\n";
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_GetStringFromClipboard) { cout << getStringFromClipboard() << "\n"; }

TEST(AlbaWindowsUserAutomationTest, DISABLED_IsKeyPressedTest) {
    while (true) {
        auto key = VK_CONTROL;
        bool const isPressed = isKeyPressed(key);
        cout << " isPressed: " << isPressed << "\n";
        if (isPressed) {
            break;
        }
        Sleep(100);
    }
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_IsLetterPressedTest) {
    while (true) {
        constexpr char letter = 'q';
        bool const isPressed = isLetterPressed(letter);
        cout << "letter: " << letter << " isPressed: " << isPressed << "\n";
        if (isPressed) {
            break;
        }
        Sleep(100);
    }
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_TypeSmallLetterTest) {
    for (char c = 'a'; c <= 'z'; ++c) {
        typeCharacter(c);
    }
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_TypeCapitalLetterTest) {
    for (char c = 'A'; c <= 'Z'; ++c) {
        typeCharacter(c);
    }
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_TypeNumberTest) {
    for (char c = '0'; c <= '9'; ++c) {
        typeCharacter(c);
    }
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_TypeString) {
    typeString(R"(.......)");
    // typeString(R"(`~!@#$%^&*()_+-=[]\{}|;':",./<>?)");
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_SaveBitmapOnScreen) {
    string const bitmapFilePath = APRG_DIR R"(\AprgLocalUserAutomation\FilesForTests\BitmapFromScreen.bmp)";

    saveBitmapOnScreen(bitmapFilePath);
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_SetMouseTest) {
    for (int x = 0; x < 100; ++x) {
        MousePosition const position{x, x};
        setMousePosition(position);
    }
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_KeyPressDownAndUpSmallLetterTest) {
#define VK_CONTROL 0x11

    pressKey(VK_CONTROL);
    pressKey('A');
    releaseKey(VK_CONTROL);
    releaseKey('A');
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_SetActiveWindowBasedClassName) {
    setForegroundWindowWithClassName("Notepad");
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_SetActiveWindowBasedWindowName) {
    setForegroundWindowWithWindowName("Untitled - Notepad");
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_SetStringFromClipboard) { setStringToClipboard("TestString"); }

TEST(AlbaWindowsUserAutomationTest, DISABLED_SaveBitmapFromClipboard) {
    string const bitmapFilePath = APRG_DIR R"(\AprgLocalUserAutomation\FilesForTests\BitmapFromClipboard.bmp)";

    saveBitmapFromClipboard(bitmapFilePath);
}

}  // namespace alba::AlbaWindowsUserAutomation
