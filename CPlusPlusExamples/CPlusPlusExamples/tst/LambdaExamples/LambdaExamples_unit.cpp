#include <Common/Print/AlbaPrintFunctions.hpp>

#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Taken from Arthur O' Dwyer's lecture ("Lambdas from First Principles- A Whirlwind Tour of C++")

namespace alba {

namespace TestStaticLocalVariableInFunctionTemplates {

template <class T>
auto kitten(T const t) {
    static int x = 0;
    return (++x) + t;
}

TEST(LambdaExamplesTest, TestStaticLocalVariableInFunctionTemplates) {
    cout << "kitten with int:[" << kitten(1) << "]\n";        // This returns 2
    cout << "kitten with double:[" << kitten(3.14) << "]\n";  // This returns 4.14
    // Note that compiler generates two kitten functions and there is a static local variable x in each.
}

}  // namespace TestStaticLocalVariableInFunctionTemplates

namespace TestCapturingByValueVsByReference {

TEST(LambdaExamplesTest, TestCapturingByValueVsByReference) {
    auto goodIncrement5 = goodIncrementBy(5);
    cout << "goodIncrement5:[" << goodIncrement5(2) << "]\n";  // This returns 7.
    // auto badIncrement5 = badIncrementBy(5);
    // cout << "badIncrement5:[" << badIncrement5(2) << "]\n"; // This returns garbage.
    // Note: This returns garbage because reference in the badIncrementBy parameter is gone by the time the lambda gets
    // called.
}

auto goodIncrementBy(int const y) {
    return [=](int const x) { return x + y; };
}

auto badIncrementBy(int const y) {
    // NOLINTNEXTLINE(clang-diagnostic-return-stack-address)
    return [&](int const x) { return x + y; };
}

}  // namespace TestCapturingByValueVsByReference

namespace CapturingGlobalVariablesWorks {

int g = 10;

TEST(LambdaExamplesTest, CapturingGlobalVariablesWorks) {
    auto kitten = [=]() { return g + 1; };
    auto cat = [g = g]() { return g + 1; };
    // auto catAbomination = [g]() { return g + 1; };
    // This "catAbomination" is an issue because capturing g does not have an automatic storage duration.
    // This is warning in gcc but a compilation error in clang.
    cout << "To avoid warnings, initial global g:[" << g << "]\n";

    g = 20;
    cout << "kitten:[" << kitten() << "]\n";  // This returns 21
    cout << "cat:[" << cat() << "]\n";        // This returns 11
    // Note: Global variables are not captured by value unless explicitly captured by value.
    // Note: Globals and statics in general are not captured by value because we already know its address.
    // -> "Capture everything by copy if we dont already see it".
    // The "catAbomination" is ill-formed and requires a diagnostic.
    // -> 5.1.2 [expr.prim.lambda]/10:
    // ---> The identifier in a simple-capture is looked up using the usual rules for unqualified name lookup (3.4.1);
    // -----> each such lookup shall find an entity.
    // ---> An entity that is designated by a simple-capture is said to be explicitly captured,
    //----->  and shall be this or a variable with automatic storage duration declared in the reaching soper of the
    // lambda expression.
}

}  // namespace CapturingGlobalVariablesWorks

namespace CapturingStaticVariablesWorks {

TEST(LambdaExamplesTest, CapturingStaticVariablesWorks) {
    auto kitten1 = makeKitten(1);
    auto kitten2 = makeKitten(2);

    cout << "kitten1:[" << kitten1(20) << "]\n";  // This returns 0+0+1+20 = 21
    cout << "kitten1:[" << kitten1(30) << "]\n";  // This returns 1+1+1+30 = 33
    cout << "kitten2:[" << kitten2(20) << "]\n";  // This returns 2+2+2+20 = 26
    cout << "kitten2:[" << kitten2(30) << "]\n";  // This returns 3+3+2+30 = 38
    // staticOutsideTheLambda has only one instance, because its a static local variable of makeKitten
    // staticInsideTheLambda has also only one instance, because its static local variable of operator() of the
    // anonymous class generated by lambda function
    auto kitten3 = makeKittenWithEachHasStatic(1);
    auto kitten4 = makeKittenWithEachHasStatic(2);

    cout << "kitten3:[" << kitten3(20) << "]\n";  // This returns 0+0+1+20 = 21
    cout << "kitten3:[" << kitten3(30) << "]\n";  // This returns 1+1+1+30 = 33
    cout << "kitten4:[" << kitten4(20) << "]\n";  // This returns 2+0+2+20 = 24
    cout << "kitten4:[" << kitten4(30) << "]\n";  // This returns 3+1+2+30 = 36
    // Note: Globals and statics in general are not captured by value because we already know its address.
    // -> "Capture everything by copy if we dont already see it".
    // Note: There is only one static.
    // -> There is only one static local variable (whether its outside or inside the lambda).
    // Note: "mutable" is all-or-nothing
    // -> operation() of the anonymous class generated by lambda function is const
    // ---> "mutable" makes the captured values non const.
    // ---> Generally speaking captures aren't modifiable... and you wouldn't want them to be.
}

auto makeKitten(int const capturedByValue) {
    static int staticOutsideTheLambda = 0;
    return [=](int const lambdaArgument) {
        static int staticInsideTheLambda = 0;
        return (staticOutsideTheLambda++) + (staticInsideTheLambda++) + capturedByValue + lambdaArgument;
    };
}

auto makeKittenWithEachHasStatic(int const capturedByValue) {
    static int staticOutsideTheLambda = 0;
    return [capturedByValue, staticInsideTheLambda = 0](int const lambdaArgument) mutable {
        return (staticOutsideTheLambda++) + (staticInsideTheLambda++) + capturedByValue + lambdaArgument;
    };
}

}  // namespace CapturingStaticVariablesWorks

namespace ClassMemberFunctionTemplatesWorks {

class Kitten {
public:
    explicit Kitten(int const value) : m_value(value) {}

    template <class T>
    [[nodiscard]] [[nodiscard]] auto plusMe(T const x) const {
        return x + m_value;
    }

    template <class T>
    auto operator()(T const x) const {
        return x + m_value;
    }

private:
    int m_value;
};

TEST(LambdaExamplesTest, ClassMemberFunctionTemplatesWorks) {
    // C++11 approach:
    Kitten kitten(1);
    cout << "kitten plusMe with int:[" << kitten.plusMe(42) << "]\n";       // This returns 43
    cout << "kitten plusMe with double:[" << kitten.plusMe(3.14) << "]\n";  // This returns 4.14
    cout << "kitten operator() with int:[" << kitten(42) << "]\n";          // This returns 43
    cout << "kitten operator() with double:[" << kitten(3.14) << "]\n";     // This returns 4.14
    // C++14 approach: Simplified version using generic lambdas
    auto plusMe = [value = 1](auto&& x) { return x + value; };
    cout << "plusMe with int:[" << plusMe(42) << "]\n";       // This returns 43
    cout << "plusMe with double:[" << plusMe(3.14) << "]\n";  // This returns 4.14
    // Note: Generic lambdas (lambdas with auto keyword as an argument type) were introduced in C++14.
    // -> Simply, the closure type defined by the lambda expression
    // ---> will have a templated call operator rather than the regular,
    // ---> non-template call operator of C++11's lambdas
    // -----> (of course, when auto appears at least once in the parameter list).
    // -> So for example:
    // ---> auto sampleLambda = [] (auto a) { return a; };
    // -> Will make sampleLambda an instance of this type:
    // ---> class /* unnamed */
    // ---> {
    // ---> public:
    // --->     template<typename T>
    // --->     T operator () (T a) const { return a; }
    // ---> };
    // Note: Notice that generic lambdas are just templates under the hood.
    // Note: Notice that generic lambdas reduce boilerplate.
}

}  // namespace ClassMemberFunctionTemplatesWorks

namespace ClassMemberFunctionVariadicTemplatesWorks {

class Kitten {
public:
    explicit Kitten(int const value) : m_value(value) {}

    template <class... Ts>
    auto operator()(Ts... xs) const {
        return m_value + (... + xs);  // Folding expressions
    }

private:
    int m_value;
};

TEST(LambdaExamplesTest, ClassMemberFunctionVariadicTemplatesWorks) {
    // C++11 approach:
    Kitten kitten(1);
    cout << "kitten operator():[" << kitten(42, 3.14, 1) << "]\n";  // This returns 46.14
    // C++14 approach: Simplified version using variadic generic lambdas
    auto plusMe = [value = 1](auto&&... xs) { return value + (... + xs); };
    cout << "plusMe:[" << plusMe(42, 3.14, 1) << "]\n";  // This returns 47.14
}

}  // namespace ClassMemberFunctionVariadicTemplatesWorks

namespace WholeParameterPackCaptureWorks {

using ObjectWithProperties = map<string, int>;
using ObjectsWithProperties = vector<ObjectWithProperties>;

template <typename... P>
void sortByProperties(vector<ObjectWithProperties>& v, P... properties) {
    auto comparator = [properties...](ObjectWithProperties const& a, ObjectWithProperties const& b) {
        return tie(a.at(properties)...) < tie(b.at(properties)...);  // parameter pack expansion
    };

    // Note: Copying cost too much
    // -> Moving is not possible: auto comparator = [p=std::move(properties)...]
    sort(v.begin(), v.end(), comparator);
}

TEST(LambdaExamplesTest, WholeParameterPackCaptureWorks) {
    ObjectsWithProperties objects{
        {{"property1", 1}, {"property2", 2}, {"property3", 3}},
        {{"property1", 3}, {"property2", 2}, {"property3", 1}},
        {{"property1", 26}, {"property2", 422}, {"property3", 0}}};

    sortByProperties(objects, "property1", "property2", "property3");
    printParameter(cout, objects);
    cout << "\n";

    sortByProperties(objects, "property3", "property2", "property1");
    printParameter(cout, objects);
    cout << "\n";
}

}  // namespace WholeParameterPackCaptureWorks

}  // namespace alba

// Notes:
// -> Other features for lambdas
// ---> Convertible to raw function pointer (when there are no capture involved)
// ---> Variables with file/global scope are not captured
// ---> Lambdas may have local state (but not in the way you think)

// Many redundant shorthands:
// -> [t=title](){decltype(title)... use(t);}
// -> [title](){decltype(title)... use(title);} // no array decay!
// -> [&t=title](){use(t);}
// -> [&title](){use(title);}
// -> To capture only what is "needed":
// ---> [=](){use(title);}
// ---> [&](){use(title);} // the most useful
// ---> Globals/statics arent captured; neither are unevaluated operands
// -> Special cases:
// ---> [pt=&title](){decltype(title)... use(pt);} // capturing by pointer
// ---> [t=std::move(title)](){decltype(title)... use(pt);} // capturing by move
