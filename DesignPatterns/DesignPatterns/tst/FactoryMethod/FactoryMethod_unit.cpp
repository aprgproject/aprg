#include <FactoryMethod/FactoryMethod.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace FactoryMethod {

TEST(FactoryMethodTest, Test1) {
    unique_ptr<Creator> const creatorA(make_unique<ConcreteCreatorA>());
    std::unique_ptr<Product> const product1 = creatorA->createProduct();
    std::cout << "Product: " << product1->getName() << "\n";

    unique_ptr<Creator> const creatorB(make_unique<ConcreteCreatorB>());
    std::unique_ptr<Product> const product2 = creatorB->createProduct();
    std::cout << "Product: " << product2->getName() << "\n";
}

}  // namespace FactoryMethod
