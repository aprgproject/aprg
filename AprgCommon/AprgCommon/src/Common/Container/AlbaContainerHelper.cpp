#include "AlbaContainerHelper.hpp"

using namespace std;

namespace alba::containerHelper {

string getDelimeterBasedOnFormat(StreamFormat const streamFormat) {
    return (StreamFormat::File == streamFormat) ? "\n"s : ", "s;
}

}  // namespace alba::containerHelper
