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
    void setMousePosition(MousePosition const& position) const;
    void pressLeftButtonOnMouse() const;
    void releaseLeftButtonOnMouse() const;
    void doLeftClick() const;
    void doDoubleLeftClick() const;
    void doLeftClickAt(MousePosition const& position) const;
    void doDoubleLeftClickAt(MousePosition const& position) const;
    void pressRightButtonOnMouse() const;
    void releaseRightButtonOnMouse() const;
    void doRightClick() const;
    void doRightClickAt(MousePosition const& position) const;
    void pressKey(uint16_t const key) const;
    void releaseKey(uint16_t const key) const;
    void typeKey(uint16_t const key) const;
    void typeCharacter(char const character) const;
    void typeString(std::string_view const& stringToType) const;
    void performKeyCombination(std::vector<uint16_t> const& keys, std::vector<char> const& characters) const;
    void setForegroundWindowWithClassName(std::string_view const& className) const;
    void setForegroundWindowWithWindowName(std::string_view const& windowName) const;
    static void sleepWithRealisticDelay();
    static void sleep(int const milliseconds);
    void saveBitmapOnScreen(std::string_view const& filePath) const;
    static void setStringToClipboard(std::string_view const& clipBoardText);
    static void saveBitmapFromClipboard(std::string_view const& filePath);
    [[nodiscard]] static MousePosition getMousePosition();
    [[nodiscard]] static std::string getClassNameOfForegroundWindow();
    [[nodiscard]] static std::string getStringFromClipboard();
    [[nodiscard]] static bool isKeyPressed(int const key);
    [[nodiscard]] bool isLetterPressed(char const letter) const;
    using InputFunction = std::function<void(INPUT&)>;

private:
    static void setForegroundWindowWithWindowHandle(HWND const windowHandle);
    static void doOperation(InputFunction const& inputFunction);
    [[nodiscard]] static uint16_t convertToVirtualKey(char const character);
    static constexpr int REALISTIC_DELAY_IN_MILLISECONDS = 100;
};

}  // namespace alba
