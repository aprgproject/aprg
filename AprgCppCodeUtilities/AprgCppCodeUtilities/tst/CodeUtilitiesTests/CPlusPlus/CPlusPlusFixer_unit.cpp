#include <CodeUtilities/CPlusPlus/CPlusPlusFixer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::CodeUtilities::CPlusPlusFixer {

TEST(CPlusPlusFixerTest, DISABLED_ActualTest) {
    processDirectory(R"(F:\Branches\aprg_project\aprg\aprg\AprgCommon\AprgCommon)");
    // processFile(
    //     R"(F:\Branches\aprg_project\aprg\aprg\AprgCommon\AprgCommon\src\Common\Container\AlbaContainerHelper.hpp)");
}

}  // namespace alba::CodeUtilities::CPlusPlusFixer
