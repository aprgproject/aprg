#include <Iterator/Iterator.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace Iterator {

TEST(IteratorTest, Test1) {
    constexpr int size = 5;
    ConcreteAggregate aggregate(size);

    auto it = aggregate.createIterator();
    for (; !it->isDone(); it->gotoNext()) {
        std::cout << "Item value: " << it->getCurrentItem() << "\n";
    }
}

}  // namespace Iterator
