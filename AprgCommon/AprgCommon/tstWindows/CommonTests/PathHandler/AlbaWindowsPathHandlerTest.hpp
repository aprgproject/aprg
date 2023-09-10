#include <gtest/gtest.h>

#include <string>

namespace alba {

struct AlbaWindowsPathHandlerTest : public testing::Test {
    AlbaWindowsPathHandlerTest();
    static std::string convertToSimplestPath(std::string_view const path);
    [[nodiscard]] std::string getDriveOfAprgDir() const;
    std::string pathOfAprgDirectory;
};

}  // namespace alba
