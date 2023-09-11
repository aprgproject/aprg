#include <TemplateMethod/TemplateMethod.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace std;

namespace TemplateMethod {

TEST(TemplateMethodTest, Test1) {
    unique_ptr<AbstractClass> const pointer = make_unique<ConcreteClass>();
    pointer->templateMethod();
}

}  // namespace TemplateMethod
