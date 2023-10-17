#include <Adapter/ClassAdapter.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace ClassAdapter {

TEST(ClassAdapterTest, Test1) {
    std::unique_ptr<Target> const t = std::make_unique<Adapter>();

    t->request();
}

}  // namespace ClassAdapter
