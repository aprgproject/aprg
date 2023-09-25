#include "AlbaWindowsScreenMonitoring.hpp"

#include <Common/Bit/AlbaBitManipulation.hpp>
#include <Common/Macros/AlbaMacros.hpp>
#include <Common/Windows/AlbaWindowsHelper.hpp>

#include <iostream>

using namespace std;

// NOLINTBEGIN(misc-misplaced-const)
namespace alba {

AlbaWindowsScreenMonitoring::AlbaWindowsScreenMonitoring()
    : m_screenWidth{}, m_screenHeight{}, m_screenHandler(nullptr), m_bitmapInfo{} {
    initialize();
}

AlbaWindowsScreenMonitoring::~AlbaWindowsScreenMonitoring() { cleanup(); }

uint32_t AlbaWindowsScreenMonitoring::getColorAt(int const x, int const y) const {
    uint32_t result{};
    int const index = (x + (m_screenHeight - y - 1) * m_screenWidth) * 4;
    if (index >= 0 && index + 2 < static_cast<int>(m_pixelData.getSize())) {
        uint8_t const* bufferPointer = static_cast<uint8_t const*>(m_pixelData.getConstantBufferPointer()) + index;
        result = AlbaBitManipulation<uint32_t>::concatenateBytes(bufferPointer[2], bufferPointer[1], bufferPointer[0]);
    }
    return result;
}

void AlbaWindowsScreenMonitoring::capturePixelsFromScreen() {
    HBITMAP bitmapHandler = createBitmapHandlerFromScreen(m_screenHandler);
    savePixelsFromBitmapScreen(m_screenHandler, bitmapHandler, m_bitmapInfo);
    DeleteObject(bitmapHandler);
}

void AlbaWindowsScreenMonitoring::initialize() {
    initializeScreenParameters();

    HBITMAP bitmapHandler = createBitmapHandlerFromScreen(m_screenHandler);
    saveBitmapInfo(m_screenHandler, bitmapHandler);
    DeleteObject(bitmapHandler);

    m_pixelData.resize(m_bitmapInfo.bmiHeader.biSizeImage);  // create the bitmap buffer
}

void AlbaWindowsScreenMonitoring::cleanup() { ReleaseDC(nullptr, m_screenHandler); }

void AlbaWindowsScreenMonitoring::initializeScreenParameters() {
    m_screenWidth = GetSystemMetrics(SM_CXVIRTUALSCREEN);
    m_screenHeight = GetSystemMetrics(SM_CYVIRTUALSCREEN);
    m_screenHandler = GetDC(nullptr);
}

void AlbaWindowsScreenMonitoring::saveBitmapInfo(HDC const screenHandler, HBITMAP const bitmapHandler) {
    m_bitmapInfo.bmiHeader.biSize = sizeof(m_bitmapInfo.bmiHeader);

    if (0 == GetDIBits(screenHandler, bitmapHandler, 0, 0, nullptr, &m_bitmapInfo, DIB_RGB_COLORS)) {
        cout << "Error in " << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
        cout << AlbaWindowsHelper::getLastFormattedErrorMessage() << "\n";
    }

    // Better do this here - the original bitmap might have BI_BITFILEDS, which makes it
    // necessary to read the color table - you might not want this.
    if (m_bitmapInfo.bmiHeader.biBitCount < 24) {
        cout << "Problem in " << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
        cout << "The number of bits per pixel needs to 24 or 32.\n";
        cout << "The value encountered instead: " << m_bitmapInfo.bmiHeader.biBitCount << "\n";
        // For more info: https://docs.microsoft.com/en-us/windows/win32/wmdm/-bitmapinfoheader
    }
    m_bitmapInfo.bmiHeader.biCompression = BI_RGB;
}

void AlbaWindowsScreenMonitoring::savePixelsFromBitmapScreen(
    HDC const screenHandler, HBITMAP const bitmapHandler, BITMAPINFO& bitmapInfo) {
    if (0 == GetDIBits(
                 screenHandler, bitmapHandler, 0, bitmapInfo.bmiHeader.biHeight,
                 static_cast<LPVOID>(m_pixelData.getBufferPointer()), &bitmapInfo, DIB_RGB_COLORS)) {
        cout << "Error in " << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
        cout << AlbaWindowsHelper::getLastFormattedErrorMessage() << "\n";
    }
}

HBITMAP AlbaWindowsScreenMonitoring::createBitmapHandlerFromScreen(HDC const screenHandler) const {
    // Create compatible DC, create a compatible bitmap and copy the screen using BitBlt()
    HDC memoryHandler = CreateCompatibleDC(screenHandler);
    HBITMAP bitmapHandler = CreateCompatibleBitmap(screenHandler, m_screenWidth, m_screenHeight);
    HGDIOBJ oldHandler = SelectObject(memoryHandler, bitmapHandler);
    BOOL const isOkay =
        BitBlt(memoryHandler, 0, 0, m_screenWidth, m_screenHeight, screenHandler, 0, 0, SRCCOPY | CAPTUREBLT);

    if (isOkay == 0) {
        cout << "Error in " << ALBA_MACROS_GET_PRETTY_FUNCTION << "\n";
        cout << AlbaWindowsHelper::getLastFormattedErrorMessage() << "\n";
    }

    SelectObject(memoryHandler, oldHandler);  // always select the previously selected object once done
    DeleteDC(memoryHandler);
    return bitmapHandler;
}

}  // namespace alba
// NOLINTEND(misc-misplaced-const)
