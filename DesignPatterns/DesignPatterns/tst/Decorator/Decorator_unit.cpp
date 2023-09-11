#include <Decorator/Decorator.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace Decorator {

TEST(DecoratorTest, Test1) {
    auto coreComponent = make_unique<ConcreteComponent>();
    auto coreComponentWithA = make_unique<ConcreteDecoratorA>(std::move(coreComponent));
    auto coreComponentWithAAndB = make_unique<ConcreteDecoratorB>(std::move(coreComponentWithA));

    Component* component = coreComponentWithAAndB.get();
    component->operation();
}

}  // namespace Decorator
