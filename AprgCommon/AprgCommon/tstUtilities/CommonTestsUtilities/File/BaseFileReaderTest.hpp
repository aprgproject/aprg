#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <gtest/gtest.h>

#include <fstream>
#include <string_view>

namespace alba {

struct BaseFileReaderTest : public testing::Test {
    explicit BaseFileReaderTest(std::string_view const testFilePath);

    void SetUp() override;
    void TearDown() override;
    void clearContentsOfTestFile();

    AlbaLocalPathHandler testFilePathHandler;
    std::ofstream testFileWriteStream;
};

}  // namespace alba
