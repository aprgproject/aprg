#include "FileUtilities.hpp"

#include <fstream>

using namespace std;

namespace alba {

void clearContentsOfFile(std::filesystem::path const& filePath) {
    ofstream fileStream(filePath);
    fileStream.close();
}

void createEmptyFile(std::filesystem::path const& filePath) {
    ofstream fileStream(filePath);
    fileStream.close();
}

}  // namespace alba
