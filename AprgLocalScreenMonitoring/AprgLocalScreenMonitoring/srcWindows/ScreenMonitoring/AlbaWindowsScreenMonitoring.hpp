#pragma once

#include <Common/Memory/AlbaMemoryBuffer.hpp>

#include <windows.h>

#include <string>

namespace alba {

class AlbaWindowsScreenMonitoring {
public:
    AlbaWindowsScreenMonitoring();
    ~AlbaWindowsScreenMonitoring();

    uint32_t getColorAt(int const x, int const y) const;
    void capturePixelsFromScreen();

private:
    void initialize();
    void cleanup();

    void initializeScreenParameters();
    HBITMAP createBitmapHandlerFromScreen(HDC const deviceContextHandler) const;
    void saveBitmapInfo(HDC const screenHandler, HBITMAP const bitmapHandler);
    void savePixelsFromBitmapScreen(HDC const screenHandler, HBITMAP const bitmapHandler, BITMAPINFO& bitmapInfo);
    int m_screenWidth;
    int m_screenHeight;
    HDC m_screenHandler;
    BITMAPINFO m_bitmapInfo;
    AlbaMemoryBuffer m_pixelData;
};

}  // namespace alba
