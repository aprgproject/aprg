#include <Proxy/Proxy.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace Proxy {

TEST(ProxyTest, Test1) {
    auto *proxy = new Proxy();
    proxy->request();

    delete proxy;
}

}  // namespace Proxy
