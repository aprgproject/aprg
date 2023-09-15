#pragma once

#include <Common/Container/AlbaXY.hpp>

#include <windows.h>

#include <functional>
#include <string>
#include <vector>

namespace alba {

using MousePosition = AlbaXY<int>;

class AlbaWindowsUserAutomation {
public:
    static void doDoubleLeftClick();
    static void doLeftClickAt(MousePosition const& position);
    static void doDoubleLeftClickAt(MousePosition const& position);
    static void doRightClickAt(MousePosition const& position);
    static void typeCharacter(char const character);
    static void typeString(std::string_view const& stringToType);
    static void saveBitmapOnScreen(std::string_view const& filePath);
    [[nodiscard]] static MousePosition getMousePosition();
    [[nodiscard]] static std::string getClassNameOfForegroundWindow();
    [[nodiscard]] static std::string getStringFromClipboard();
    [[nodiscard]] static bool isKeyPressed(int const key);
    [[nodiscard]] static bool isLetterPressed(char const letter);
    static void setMousePosition(MousePosition const& position);
    static void pressLeftButtonOnMouse();
    static void releaseLeftButtonOnMouse();
    static void doLeftClick();
    static void pressRightButtonOnMouse();
    static void releaseRightButtonOnMouse();
    static void doRightClick();
    static void pressKey(uint16_t const key);
    static void releaseKey(uint16_t const key);
    static void typeKey(uint16_t const key);
    static void performKeyCombination(std::vector<uint16_t> const& keys, std::vector<char> const& characters);
    static void setForegroundWindowWithClassName(std::string_view const& className);
    static void setForegroundWindowWithWindowName(std::string_view const& windowName);
    static void sleepWithRealisticDelay();
    static void sleep(int const milliseconds);
    static void setStringToClipboard(std::string_view const& clipBoardText);
    static void saveBitmapFromClipboard(std::string_view const& filePath);
    using InputFunction = std::function<void(INPUT&)>;

private:
    [[nodiscard]] static uint16_t convertToVirtualKey(char const character);
    static void setForegroundWindowWithWindowHandle(HWND const windowHandle);
    static void doOperation(InputFunction const& inputFunction);
    static constexpr int REALISTIC_DELAY_IN_MILLISECONDS = 100;
};

}  // namespace alba
