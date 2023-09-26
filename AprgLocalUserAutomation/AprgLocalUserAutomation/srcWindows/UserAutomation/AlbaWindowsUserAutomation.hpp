#pragma once

#include <Common/Container/AlbaXY.hpp>

#include <windows.h>

#include <functional>
#include <string>
#include <vector>

namespace alba::AlbaWindowsUserAutomation {
using MousePosition = AlbaXY<int>;
using InputFunction = std::function<void(INPUT&)>;
inline constexpr int REALISTIC_DELAY_IN_MILLISECONDS = 100;
[[nodiscard]] MousePosition getMousePosition();
[[nodiscard]] std::string getClassNameOfForegroundWindow();
[[nodiscard]] std::string getStringFromClipboard();
[[nodiscard]] bool isKeyPressed(int const key);
[[nodiscard]] bool isLetterPressed(char const letter);
void doDoubleLeftClick();
void doLeftClickAt(MousePosition const& position);
void doDoubleLeftClickAt(MousePosition const& position);
void doRightClickAt(MousePosition const& position);
void typeCharacter(char const character);
void typeString(std::string_view const& stringToType);
void saveBitmapOnScreen(std::string_view const& filePath);
void setMousePosition(MousePosition const& position);
void pressLeftButtonOnMouse();
void releaseLeftButtonOnMouse();
void doLeftClick();
void pressRightButtonOnMouse();
void releaseRightButtonOnMouse();
void doRightClick();
void pressKey(uint16_t const key);
void releaseKey(uint16_t const key);
void typeKey(uint16_t const key);
void performKeyCombination(std::vector<uint16_t> const& keys, std::vector<char> const& characters);
void setForegroundWindowWithClassName(std::string_view const& className);
void setForegroundWindowWithWindowName(std::string_view const& windowName);
void sleepWithRealisticDelay();
void sleep(int const milliseconds);
void setStringToClipboard(std::string_view const& clipBoardText);
void saveBitmapFromClipboard(std::string_view const& filePath);
}  // namespace alba::AlbaWindowsUserAutomation
