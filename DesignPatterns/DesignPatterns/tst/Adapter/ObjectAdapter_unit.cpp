#include <Adapter/ObjectAdapter.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace ObjectAdapter {

TEST(ObjectAdapterTest, Test1) {
    std::unique_ptr<Target> const t = std::make_unique<Adapter>();

    t->request();
}

}  // namespace ObjectAdapter
