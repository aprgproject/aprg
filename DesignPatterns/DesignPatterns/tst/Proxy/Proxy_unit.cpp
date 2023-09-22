#include <Proxy/Proxy.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace Proxy {

TEST(ProxyTest, Test1) {
    auto proxy = std::make_unique<Proxy>();

    proxy->request();
}

}  // namespace Proxy
