#pragma once

#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <filesystem>
#include <string>

namespace alba {

class AlbaRenameFiles {
public:
    explicit AlbaRenameFiles(std::filesystem::path const& directoryPath);
    void renameWithIncreasingNumbers(std::string const& prefix, int const startingNumber, int const fieldWidth) const;

private:
    AlbaLocalPathHandler m_directoryPathHandler;
};

}  // namespace alba
