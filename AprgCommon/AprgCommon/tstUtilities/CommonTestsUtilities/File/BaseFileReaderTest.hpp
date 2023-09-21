#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>

namespace alba {

struct BaseFileReaderTest : public testing::Test {
    explicit BaseFileReaderTest(std::filesystem::path const& testFilePath);
    void SetUp() override;
    void TearDown() override;
    void clearContentsOfTestFile() const;
    AlbaLocalPathHandler testFilePathHandler;
    std::ofstream testFileWriteStream;
};

}  // namespace alba
