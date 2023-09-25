#pragma once

#include <Common/Memory/AlbaMemoryBuffer.hpp>

#include <windows.h>

#include <string>

// NOLINTBEGIN(misc-misplaced-const)
namespace alba {

class AlbaWindowsScreenMonitoring {
public:
    AlbaWindowsScreenMonitoring(AlbaWindowsScreenMonitoring const &) = default;
    AlbaWindowsScreenMonitoring(AlbaWindowsScreenMonitoring &&) = default;
    AlbaWindowsScreenMonitoring &operator=(AlbaWindowsScreenMonitoring const &) = default;
    AlbaWindowsScreenMonitoring &operator=(AlbaWindowsScreenMonitoring &&) = default;
    AlbaWindowsScreenMonitoring();
    ~AlbaWindowsScreenMonitoring();
    [[nodiscard]] uint32_t getColorAt(int const x, int const y) const;
    void capturePixelsFromScreen();

private:
    HBITMAP createBitmapHandlerFromScreen(HDC const screenHandler) const;
    void initialize();
    void cleanup();
    void initializeScreenParameters();
    void saveBitmapInfo(HDC const screenHandler, HBITMAP const bitmapHandler);
    void savePixelsFromBitmapScreen(HDC const screenHandler, HBITMAP const bitmapHandler, BITMAPINFO &bitmapInfo);
    int m_screenWidth;
    int m_screenHeight;
    HDC m_screenHandler;
    BITMAPINFO m_bitmapInfo;
    AlbaMemoryBuffer m_pixelData;
};

}  // namespace alba
// NOLINTEND(misc-misplaced-const)
