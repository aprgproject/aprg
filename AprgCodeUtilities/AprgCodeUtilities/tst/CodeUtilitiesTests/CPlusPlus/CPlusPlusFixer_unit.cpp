#include <CodeUtilities/CPlusPlus/CPlusPlusFixer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::CodeUtilities::CPlusPlusFixer {

TEST(CPlusPlusFixerTest, DISABLED_ActualTest) {
    processPath(R"(F:\Branches\aprg_project\aprg\aprg\AprgCommon\AprgCommon)");
    // processPath(
    //     R"(F:\Branches\aprg_project\aprg\aprg\AprgCommon\AprgCommon\src\Common\Container\AlbaContainerHelper.hpp)");
}

TEST(CPlusPlusFixerTest, AprgDirectoryTest) {
    processAprgDirectory(R"(F:\Branches\aprg_project\aprg_semi_clean\aprg)");
}

}  // namespace alba::CodeUtilities::CPlusPlusFixer
