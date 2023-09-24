#include "BaseFileReaderTest.hpp"

#include <Common/String/AlbaStringHelper.hpp>
#include <CommonTestsUtilities/File/FileUtilities.hpp>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

BaseFileReaderTest::BaseFileReaderTest(std::filesystem::path const& testFilePath)
    : testFilePathHandler(testFilePath), testFileWriteStream(testFilePathHandler.getPath()) {}

void BaseFileReaderTest::clearContentsOfTestFile() const { clearContentsOfFile(testFilePathHandler.getPath()); }
void BaseFileReaderTest::SetUp() { ASSERT_TRUE(testFileWriteStream.is_open()); }
void BaseFileReaderTest::TearDown() { clearContentsOfTestFile(); }

}  // namespace alba
