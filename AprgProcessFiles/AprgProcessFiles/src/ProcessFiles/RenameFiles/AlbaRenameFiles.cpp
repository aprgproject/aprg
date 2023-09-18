#include "AlbaRenameFiles.hpp"

#include <Common/String/AlbaStringHelper.hpp>

using namespace alba::stringHelper;
using namespace std;
using namespace std::filesystem;

namespace alba {

AlbaRenameFiles::AlbaRenameFiles(path const& directoryPath) : m_directoryPathHandler(directoryPath) {}

void AlbaRenameFiles::renameWithIncreasingNumbers(
    string const& prefix, int const startingNumber, int const fieldWidth) const {
    StringConverterWithFormatting const converter(fieldWidth, '0');

    int count = startingNumber;
    m_directoryPathHandler.findFilesAndDirectoriesOneDepth(
        [](AlbaLocalPathHandler::LocalPath const&) {},
        [&](AlbaLocalPathHandler::LocalPath const& filePath) {
            AlbaLocalPathHandler filePathHandler(filePath);
            filePathHandler.renameFileAndIsSuccessful(
                prefix + converter.convertToString(count++) + string(".") + filePathHandler.getExtension().string());
        });
}

}  // namespace alba
