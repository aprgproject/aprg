#include <NullObject/NullObject.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace NullObject {

TEST(NullObjectTest, Test1) {
    std::unique_ptr<AbstractObject> const realObject(make_unique<RealObject>());
    realObject->doSomething();

    std::unique_ptr<AbstractObject> const nullObject(make_unique<NullObject>());
    nullObject->doSomething();
}

}  // namespace NullObject
