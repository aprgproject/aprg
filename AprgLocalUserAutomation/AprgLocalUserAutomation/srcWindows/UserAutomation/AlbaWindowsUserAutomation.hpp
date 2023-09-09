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
    void sleepWithRealisticDelay() const;
    void sleep(int const milliseconds) const;
    void saveBitmapOnScreen(std::string_view const& filePath) const;
    void setStringToClipboard(std::string_view const& clipBoardText) const;
    void saveBitmapFromClipboard(std::string_view const& filePath) const;
    MousePosition getMousePosition() const;
    std::string getClassNameOfForegroundWindow() const;
    std::string getStringFromClipboard() const;
    bool isKeyPressed(int const key) const;
    bool isLetterPressed(char const letter) const;
    typedef std::function<void(INPUT&)> InputFunction;

private:
    void setForegroundWindowWithWindowHandle(HWND const windowHandle) const;
    void doOperation(InputFunction const& inputFunction) const;
    uint16_t convertToVirtualKey(char const character) const;
    static constexpr int REALISTIC_DELAY_IN_MILLISECONDS = 100;
};

}  // namespace alba
