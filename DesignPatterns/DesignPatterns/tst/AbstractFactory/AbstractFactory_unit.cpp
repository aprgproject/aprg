#include <AbstractFactory/AbstractFactory.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace AbstractFactory {

TEST(AbstractFactoryTest, Test1) {
    std::unique_ptr<AbstractFactory> const factoryX = make_unique<ConcreteFactoryX>();
    std::unique_ptr<AbstractFactory> const factoryY = make_unique<ConcreteFactoryY>();

    std::unique_ptr<ProductA> const productAX = factoryX->createProductA();
    std::unique_ptr<ProductB> const productBX = factoryX->createProductB();
    std::cout << "ProductAX: " << productAX->getName() << "\n";
    std::cout << "ProductBX: " << productBX->getName() << "\n";

    std::unique_ptr<ProductA> const productAY = factoryY->createProductA();
    std::unique_ptr<ProductB> const productBY = factoryY->createProductB();
    std::cout << "ProductAY: " << productAY->getName() << "\n";
    std::cout << "ProductBY: " << productBY->getName() << "\n";
}

}  // namespace AbstractFactory
