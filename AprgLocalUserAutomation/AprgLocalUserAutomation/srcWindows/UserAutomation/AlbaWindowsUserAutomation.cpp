#include "AlbaWindowsUserAutomation.hpp"

#include <Common/Macros/AlbaMacros.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <Common/Windows/AlbaWindowsHelper.hpp>

#include <cctype>
#include <fstream>
#include <iostream>

using namespace std;

namespace alba {

void AlbaWindowsUserAutomation::setMousePosition(MousePosition const& position) {
    long const screenWidth = GetSystemMetrics(SM_CXSCREEN) - 1;
    long const screenHeight = GetSystemMetrics(SM_CYSCREEN) - 1;
    float ratioInX = position.getX() * (65535.0F / screenWidth);
    float ratioInY = position.getY() * (65535.0F / screenHeight);

    doOperation([&](INPUT& input) {
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
        input.mi.dx = static_cast<long>(ratioInX);
        input.mi.dy = static_cast<long>(ratioInY);
    });
    sleepWithRealisticDelay();
}

void AlbaWindowsUserAutomation::pressLeftButtonOnMouse() {
    doOperation([](INPUT& input) {
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    });
}

void AlbaWindowsUserAutomation::releaseLeftButtonOnMouse() {
    doOperation([](INPUT& input) {
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    });
}

void AlbaWindowsUserAutomation::doLeftClick() const {
    pressLeftButtonOnMouse();
    sleepWithRealisticDelay();
    releaseLeftButtonOnMouse();
    sleepWithRealisticDelay();
}

void AlbaWindowsUserAutomation::doDoubleLeftClick() const {
    doLeftClick();
    doLeftClick();
}

void AlbaWindowsUserAutomation::doLeftClickAt(MousePosition const& position) const {
    setMousePosition(position);
    doLeftClick();
}

void AlbaWindowsUserAutomation::doDoubleLeftClickAt(MousePosition const& position) const {
    setMousePosition(position);
    doDoubleLeftClick();
}

void AlbaWindowsUserAutomation::pressRightButtonOnMouse() {
    doOperation([](INPUT& input) {
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
    });
}

void AlbaWindowsUserAutomation::releaseRightButtonOnMouse() {
    doOperation([](INPUT& input) {
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
    });
}

void AlbaWindowsUserAutomation::doRightClick() const {
    pressRightButtonOnMouse();
    sleepWithRealisticDelay();
    releaseRightButtonOnMouse();
    sleepWithRealisticDelay();
}

void AlbaWindowsUserAutomation::doRightClickAt(MousePosition const& position) const {
    setMousePosition(position);
    doRightClick();
}

void AlbaWindowsUserAutomation::pressKey(uint16_t const key) {
    doOperation([&](INPUT& input) {
        input.type = INPUT_KEYBOARD;
        input.ki.wScan = 0;
        input.ki.time = 0;
        input.ki.dwExtraInfo = 0;
        input.ki.wVk = static_cast<WORD>(key);
        input.ki.dwFlags = 0;
    });
}

void AlbaWindowsUserAutomation::releaseKey(uint16_t const key) {
    doOperation([&](INPUT& input) {
        input.type = INPUT_KEYBOARD;
        input.ki.wScan = 0;
        input.ki.time = 0;
        input.ki.dwExtraInfo = 0;
        input.ki.wVk = static_cast<WORD>(key);
        input.ki.dwFlags = KEYEVENTF_KEYUP;
    });
}

void AlbaWindowsUserAutomation::typeKey(uint16_t const key) const {
    pressKey(key);
    sleepWithRealisticDelay();
    releaseKey(key);
    sleepWithRealisticDelay();
}

void AlbaWindowsUserAutomation::typeCharacter(char const character) const { typeKey(convertToVirtualKey(character)); }

void AlbaWindowsUserAutomation::typeString(string_view const& stringToType) const {
    for (char const character : stringToType) {
        typeCharacter(character);
    }
}

void AlbaWindowsUserAutomation::performKeyCombination(
    vector<uint16_t> const& keys, std::vector<char> const& characters) const {
    for (auto const key : keys) {
        pressKey(key);
        sleepWithRealisticDelay();
    }
    for (auto const character : characters) {
        pressKey(convertToVirtualKey(character));
        sleepWithRealisticDelay();
    }
    sleepWithRealisticDelay();
    for (auto rit = characters.rbegin(); rit != characters.rend(); ++rit) {
        pressKey(convertToVirtualKey(*rit));
        sleepWithRealisticDelay();
    }
    for (auto rit = keys.rbegin(); rit != keys.rend(); ++rit) {
        pressKey(*rit);
        sleepWithRealisticDelay();
    }
}

void AlbaWindowsUserAutomation::setForegroundWindowWithClassName(string_view const& className) {
    Sleep(2000);
    int const LENGTH = 1000;
    char classNameTemp[LENGTH];
    GetClassName(GetForegroundWindow(), classNameTemp, LENGTH);
    cout << "ClassName:[" << classNameTemp << "]\n";

    HWND windowHandle = FindWindowEx(nullptr, nullptr, className.data(), nullptr);
    cout << "Error in " << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
    cout << AlbaWindowsHelper::getLastFormattedErrorMessage() << "\n";
    setForegroundWindowWithWindowHandle(windowHandle);
}

void AlbaWindowsUserAutomation::setForegroundWindowWithWindowName(string_view const& windowName) {
    HWND windowHandle = FindWindowEx(nullptr, nullptr, nullptr, windowName.data());
    setForegroundWindowWithWindowHandle(windowHandle);
}

void AlbaWindowsUserAutomation::sleepWithRealisticDelay() { Sleep(REALISTIC_DELAY_IN_MILLISECONDS); }
void AlbaWindowsUserAutomation::sleep(int const milliseconds) { Sleep(milliseconds); }

void AlbaWindowsUserAutomation::saveBitmapOnScreen(string_view const& filePath) const {
    // Note: the difference on partially capturing the screen is negligible
    typeKey(VK_SNAPSHOT);
    saveBitmapFromClipboard(filePath);
}

void AlbaWindowsUserAutomation::setStringToClipboard(string_view const& clipBoardText) {
    HANDLE hData = nullptr;
    char* pointerData = nullptr;
    hData = GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, clipBoardText.length() + 1);
    pointerData = static_cast<char*>(GlobalLock(hData));
    memcpy(pointerData, clipBoardText.data(), clipBoardText.length() + 1);
    GlobalUnlock(hData);
    OpenClipboard(nullptr);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hData);
    CloseClipboard();
}

void AlbaWindowsUserAutomation::saveBitmapFromClipboard(string_view const& filePath) {
    AlbaLocalPathHandler const pathHandler(filePath);
    ofstream outputBitmapFile(pathHandler.getFullPath(), ios::out | ios::binary);
    if (!outputBitmapFile) {
        return;
    }
    if (IsClipboardFormatAvailable(CF_DIB) == 0) {
        return;
    }
    if (OpenClipboard(nullptr) != 0) {
        HANDLE hClipboard = GetClipboardData(CF_DIB);
        if (hClipboard != nullptr && hClipboard != INVALID_HANDLE_VALUE) {
            void* dib = GlobalLock(hClipboard);
            if (dib != nullptr) {
                auto* bitmapInfoPointer = reinterpret_cast<BITMAPINFOHEADER*>(dib);
                BITMAPFILEHEADER fileHeader{};
                fileHeader.bfType = 0x4D42;
                fileHeader.bfOffBits = 54;
                fileHeader.bfSize = (((bitmapInfoPointer->biWidth * bitmapInfoPointer->biBitCount + 31) & ~31) / 8 *
                                     bitmapInfoPointer->biHeight) +
                                    fileHeader.bfOffBits;
                bitmapInfoPointer->biCompression = 0;

                outputBitmapFile.write(reinterpret_cast<char*>(&fileHeader), sizeof(BITMAPFILEHEADER));
                outputBitmapFile.write(reinterpret_cast<char*>(bitmapInfoPointer), sizeof(BITMAPINFOHEADER));

                unsigned long long const sizeOfBitmapData = bitmapInfoPointer->biSizeImage;
                char* startOfBitmapDataPointer = reinterpret_cast<char*>(++bitmapInfoPointer);
                outputBitmapFile.write(startOfBitmapDataPointer, sizeOfBitmapData);
                GlobalUnlock(dib);
            }
        }
        CloseClipboard();
    }
}

MousePosition AlbaWindowsUserAutomation::getMousePosition() {
    MousePosition const position;
    POINT mouse;
    GetCursorPos(&mouse);
    return MousePosition(mouse.x, mouse.y);
}

string AlbaWindowsUserAutomation::getClassNameOfForegroundWindow() {
    int const LENGTH = 1000;
    char className[LENGTH];
    GetClassName(GetForegroundWindow(), className, LENGTH);
    return string(className);
}

string AlbaWindowsUserAutomation::getStringFromClipboard() {
    string stringInClipboard;
    if (OpenClipboard(nullptr) != 0) {
        HANDLE clipboardData = GetClipboardData(CF_TEXT);
        stringInClipboard = static_cast<char*>(clipboardData);
        CloseClipboard();
    }
    return stringInClipboard;
}

bool AlbaWindowsUserAutomation::isKeyPressed(int const key) {
    // https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-getasynckeystate
    // If the function succeeds, the return value specifies whether the key was pressed since the last call to
    // GetAsyncKeyState, and whether the key is currently up or down. If the most significant bit is set, the key is
    // down. If the least significant bit is set, the key was pressed after the previous call to GetAsyncKeyState.
    // However, you should not rely on this last behavior; for more information, see the Remarks.
    USHORT const status = GetAsyncKeyState(key);
    return (status & 0x8000) >> 15 == 1;  // || (status & 1) == 1;
}

bool AlbaWindowsUserAutomation::isLetterPressed(char const letter) { return isKeyPressed(::toupper(letter)); }

void AlbaWindowsUserAutomation::setForegroundWindowWithWindowHandle(HWND const windowHandle) {
    bool isSuccessful(false);
    if (windowHandle != nullptr) {
        isSuccessful = static_cast<bool>(SetWindowPos(
            windowHandle,                             // handle to window
            HWND_TOPMOST,                             // placement-order handle
            0,                                        // horizontal position
            0,                                        // vertical position
            0,                                        // width
            0,                                        // height
            SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOMOVE  // window-positioning options
            ));
    }
    if (!isSuccessful) {
        cout << "Error in " << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
        cout << AlbaWindowsHelper::getLastFormattedErrorMessage() << "\n";
    }
}

void AlbaWindowsUserAutomation::doOperation(AlbaWindowsUserAutomation::InputFunction const& inputFunction) {
    INPUT input;
    memset(&input, 0, sizeof(INPUT));
    inputFunction(input);
    SendInput(1, &input, sizeof(INPUT));
}

uint16_t AlbaWindowsUserAutomation::convertToVirtualKey(char const character) {
    int virtualKey = character;
    if (stringHelper::isLetter(character)) {
        virtualKey = ::toupper(character);
    } else if ('.' == character) {
        virtualKey = VK_OEM_PERIOD;
    }
    return virtualKey;
}

}  // namespace alba
