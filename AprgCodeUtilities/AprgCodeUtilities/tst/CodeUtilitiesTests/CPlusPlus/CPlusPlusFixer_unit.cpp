#include <CodeUtilities/CPlusPlus/CPlusPlusFixer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::CodeUtilities::CPlusPlusFixer {

TEST(CPlusPlusFixerTest, DISABLED_AprgDirectoryTest) {
    processAprgDirectory(R"(F:\Branches\aprg_project\aprg_semi_clean\aprg)");
}

TEST(CPlusPlusFixerTest, DISABLED_FileTest) {
    processPath(
        R"(F:\Branches\aprg_project\aprg_semi_clean\aprg\AprgAlgebra\AprgAlgebra\src\Algebra\Solution\Solver\MultipleLinearEquations\LinearEquationsEqualitySolver.cpp)");
    // processPath(
    //     R"(F:\Branches\aprg_project\aprg\aprg\AprgCommon\AprgCommon\src\Common\Container\AlbaContainerHelper.hpp)");
}

}  // namespace alba::CodeUtilities::CPlusPlusFixer
