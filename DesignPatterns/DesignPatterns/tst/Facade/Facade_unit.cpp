#include <Facade/Facade.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace Facade {

TEST(FacadeTest, Test1) {
    auto facade = std::make_unique<Facade>();

    facade->operation1();
    facade->operation2();
}

}  // namespace Facade
