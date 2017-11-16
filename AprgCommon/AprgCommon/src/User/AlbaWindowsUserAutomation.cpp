#include "AlbaWindowsUserAutomation.hpp"

#include <String/AlbaStringHelper.hpp>
#include <Windows/AlbaWindowsHelper.hpp>

#include <windows.h>

#include <iostream>
#include <cctype>

using namespace std;
namespace alba
{

bool AlbaWindowsUserAutomation::isLetterPressed(char const letter) const
{
    USHORT status = GetAsyncKeyState(::toupper(letter));
    return (( ( status & 0x8000 ) >> 15 ) == 1) || (( status & 1 ) == 1);
}

void AlbaWindowsUserAutomation::setStringToClipboard(std::string const& clipBoardText) const
{
    HANDLE hData;
    char *pointerData = NULL;//pointer to allow char copying

    hData = GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE,clipBoardText.length() + 1);//get handle to memory to hold phrase
    pointerData = (char*)GlobalLock(hData);//get pointer from handle
    memcpy(pointerData,clipBoardText.c_str(),clipBoardText.length() + 1);//copy over the phrase
    GlobalUnlock(hData);//free the handle
    OpenClipboard(NULL);//allow you to work with clipboard
    EmptyClipboard();//clear previous contents
    SetClipboardData(CF_TEXT,hData);//set our data
    CloseClipboard();//finished!!
}

string AlbaWindowsUserAutomation::getStringFromClipboard() const
{
    string stringInClipboard;    if(OpenClipboard(NULL))
    {
      HANDLE clipboardData = GetClipboardData(CF_TEXT);
      CloseClipboard();
      stringInClipboard = (char*)clipboardData;
    }
    return stringInClipboard;
}

MousePosition AlbaWindowsUserAutomation::getMousePosition() const
{
    MousePosition position;
    POINT mouse;
    GetCursorPos(&mouse);
    return MousePosition(mouse.x, mouse.y);
}

void AlbaWindowsUserAutomation::setMousePosition(MousePosition const& position) const
{
    long screenWidth = GetSystemMetrics( SM_CXSCREEN ) - 1;
    long screenHeight = GetSystemMetrics( SM_CYSCREEN ) - 1;    float ratioInX = position.getX() * ( 65535.0f / screenWidth  );
    float ratioInY = position.getY() * ( 65535.0f / screenHeight );

    doOperation([&](INPUT& input)
    {
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE;
        input.mi.dx = (long)ratioInX;
        input.mi.dy = (long)ratioInY;
    });
}

void AlbaWindowsUserAutomation::doLeftClick() const
{
    doOperation([](INPUT& input)
    {
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    });
    doOperation([](INPUT& input)
    {
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    });
}

void AlbaWindowsUserAutomation::doRightClick() const
{
    doOperation([](INPUT& input)
    {
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
    });
    doOperation([](INPUT& input)
    {
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
    });
}

void AlbaWindowsUserAutomation::typeString(string const& stringToType) const
{
    for(char const character : stringToType)
    {
        typeCharacter(character);
    }
}

void AlbaWindowsUserAutomation::typeCharacter(char const character) const
{
    doOperation([&](INPUT& input)
    {        input.type = INPUT_KEYBOARD;
        input.ki.wScan = 0;
        input.ki.time = 0;
        input.ki.dwExtraInfo = 0;
        input.ki.wVk = convertToVirtualKey(character);
        input.ki.dwFlags = 0;
    });
    doOperation([&](INPUT& input)
    {
        input.type = INPUT_KEYBOARD;
        input.ki.wScan = 0;
        input.ki.time = 0;
        input.ki.dwExtraInfo = 0;
        input.ki.wVk = convertToVirtualKey(character);
        input.ki.dwFlags = KEYEVENTF_KEYUP;
    });
}

string AlbaWindowsUserAutomation::getClassNameOfForegroundWindow() const
{
    int const LENGTH = 1000;
    char className[LENGTH];
    GetClassName (GetForegroundWindow(), className, LENGTH);
    return string(className);
}

void AlbaWindowsUserAutomation::setForegroundWindowWithClassName(std::string const& className) const
{
    int const LENGTH = 1000;
    char classNameTemp[LENGTH];
    GetClassName (GetForegroundWindow(), classNameTemp, LENGTH);
    cout<<"ClassName:["<<classNameTemp<<"]"<<endl;
    cout<<AlbaWindowsHelper::getLastFormattedErrorMessage()<<endl;

    HWND windowHandle = FindWindowEx(nullptr, nullptr, className.c_str(), nullptr);
    setForegroundWindowWithWindowHandle(windowHandle);
}

void AlbaWindowsUserAutomation::setForegroundWindowWithWindowName(std::string const& windowName) const
{
    HWND windowHandle = FindWindowEx(nullptr, nullptr, nullptr, windowName.c_str());
    setForegroundWindowWithWindowHandle(windowHandle);
}

unsigned int AlbaWindowsUserAutomation::convertToVirtualKey(char const character) const
{
    int virtualKey = character;
    if(stringHelper::isLetter(character))
    {        virtualKey = ::toupper(character);
    }
    else if('.' == character)
    {
        virtualKey = VK_OEM_PERIOD;
    }
    return virtualKey;
}

void AlbaWindowsUserAutomation::setForegroundWindowWithWindowHandle(HWND const windowHandle) const
{
    bool isSuccessful(false);
    if(windowHandle != nullptr)
    {
        isSuccessful = (bool)SetForegroundWindow(windowHandle);
    }
    if(!isSuccessful)
    {
        cout<<"Error in AlbaWindowsUserAutomation::setActiveWindow()"<<endl;
        cout<<AlbaWindowsHelper::getLastFormattedErrorMessage()<<endl;
    }
}

void AlbaWindowsUserAutomation::doOperation(AlbaWindowsUserAutomation::InputFunction inputFunction) const
{
    INPUT input;    memset(&input, 0, sizeof(INPUT));
    inputFunction(input);
    SendInput(1, &input, sizeof(INPUT));
    Sleep(REALISTIC_DELAY_IN_MILLISECONDS);
}

}
