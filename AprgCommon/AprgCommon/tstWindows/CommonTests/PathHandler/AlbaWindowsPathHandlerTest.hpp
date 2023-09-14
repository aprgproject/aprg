#include <gtest/gtest.h>

#include <string>

namespace alba {

struct AlbaWindowsPathHandlerTest : public testing::Test {
    AlbaWindowsPathHandlerTest();
    [[nodiscard]] std::string getDriveOfAprgDir() const;
    static std::string convertToSimplestPath(std::string_view const path);
    std::string pathOfAprgDirectory;
};

}  // namespace alba
