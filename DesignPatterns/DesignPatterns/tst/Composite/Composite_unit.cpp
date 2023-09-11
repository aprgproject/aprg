#include <Composite/Composite.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace Composite {

TEST(CompositeTest, Test1) {
    int id = 1;
    unique_ptr<Component> composite1(make_unique<Composite>());
    unique_ptr<Component> composite2(make_unique<Composite>());
    unique_ptr<Component> const topComposite(make_unique<Composite>());

    topComposite->add(make_unique<Leaf>(0));
    composite1->add(make_unique<Leaf>(id++));
    composite1->add(make_unique<Leaf>(id++));
    composite2->add(make_unique<Leaf>(id++));
    composite2->add(make_unique<Leaf>(id++));
    topComposite->add(std::move(composite1));
    topComposite->add(std::move(composite2));

    topComposite->removeAtIndex(0);

    topComposite->operation();
}

}  // namespace Composite
