#include <CodeUtilities/CPlusPlus/CPlusPlusFixer.hpp>
#include <Common/String/AlbaStringHelper.hpp>

using namespace alba::CodeUtilities::CPlusPlusFixer;
using namespace alba::stringHelper;
using namespace alba;

int main(int const argc, char const* const argv[]) {
    strings arguments(getArgumentsToStringInMain(argc, argv));
    if (!arguments.empty()) {
        processPath(arguments.front());
    }
    return 0;
}
