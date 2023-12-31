#include <Mediator/Mediator.hpp>

#include <gtest/gtest.h>

#include <memory>

using namespace std;

namespace Mediator {

TEST(MediatorTest, Test1) {
    unique_ptr<Mediator> const mediatorPointer = make_unique<ConcreteMediator>();
    unique_ptr<Colleague> const colleaguePointer1 = make_unique<ConcreteColleague>(*mediatorPointer, 1);
    unique_ptr<Colleague> const colleaguePointer2 = make_unique<ConcreteColleague>(*mediatorPointer, 2);
    unique_ptr<Colleague> const colleaguePointer3 = make_unique<ConcreteColleague>(*mediatorPointer, 3);

    mediatorPointer->add(*colleaguePointer1);
    mediatorPointer->add(*colleaguePointer2);
    mediatorPointer->add(*colleaguePointer3);

    colleaguePointer1->send("Hi!");
    colleaguePointer3->send("Hello!");
}

}  // namespace Mediator
