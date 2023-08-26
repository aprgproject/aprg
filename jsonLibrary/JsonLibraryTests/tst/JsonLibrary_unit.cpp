#include <nlohmann/json.hpp>

#include <gtest/gtest.h>

#include <fstream>

using namespace std;
using json = nlohmann::json;

namespace alba {

#define JSON_LIBRARY_TESTS_SAMPLE_FILE APRG_DIR R"(\jsonLibrary\FilesForTests\JsonSampleFile.txt)"

// Based from: https://github.com/nlohmann/json#examples

TEST(SampleTest, CreatingJsonObjectsFromJsonLiteralsTest) {
    // Creating json objects from JSON literals
    // Assume you want to create hard-code this literal JSON value in a file, as a json object:
    // {
    //   "pi": 3.141,
    //   "happy": true
    // }

    // There are various options:

    // Using (raw) string literals and json::parse
    json jsonObject1 = json::parse(R"({ "pi": 3.141, "happy": true })");

    // Using user-defined (raw) string literals
    using namespace nlohmann::literals;
    json jsonObject2 = R"({ "pi": 3.141, "happy": true })"_json;

    // Using initializer lists
    json jsonObject3 = {
        {"happy", true},
        {"pi", 3.141},
    };

    EXPECT_EQ(R"({"happy":true,"pi":3.141})", jsonObject1.dump());
    EXPECT_EQ(R"({"happy":true,"pi":3.141})", jsonObject2.dump());
    EXPECT_EQ(R"({"happy":true,"pi":3.141})", jsonObject3.dump());
}

TEST(SampleTest, JsonAsFirstClassDataTypeTest) {
    // JSON as first-class data type
    // Here are some examples to give you an idea how to use the class.
    // Assume you want to create the JSON object
    // {
    //   "pi": 3.141,
    //   "happy": true,
    //   "name": "Niels",
    //   "nothing": null,
    //   "answer": {
    //     "everything": 42
    //   },
    //   "list": [1, 0, 2],
    //   "object": {
    //     "currency": "USD",
    //     "value": 42.99
    //   }
    // }

    // With this library, you could write:

    // create an empty structure (null)
    json jsonObject1;

    // add a number that is stored as double (note the implicit conversion of j to an object)
    jsonObject1["pi"] = 3.141;

    // add a Boolean that is stored as bool
    jsonObject1["happy"] = true;

    // add a string that is stored as string
    jsonObject1["name"] = "Niels";

    // add another null object by passing nullptr
    jsonObject1["nothing"] = nullptr;

    // add an object inside the object
    jsonObject1["answer"]["everything"] = 42;

    // add an array that is stored as vector (using an initializer list)
    jsonObject1["list"] = {1, 0, 2};

    // add another object (using an initializer list of pairs)
    jsonObject1["object"] = {{"currency", "USD"}, {"value", 42.99}};

    // instead, you could also write (which looks very similar to the JSON above)
    json jsonObject2 = {
        {"pi", 3.141},
        {"happy", true},
        {"name", "Niels"},
        {"nothing", nullptr},
        {"answer", {{"everything", 42}}},
        {"list", {1, 0, 2}},
        {"object", {{"currency", "USD"}, {"value", 42.99}}}};

    EXPECT_EQ(
        R"({"answer":{"everything":42},"happy":true,"list":[1,0,2],"name":"Niels","nothing":null,"object":{"currency":"USD","value":42.99},"pi":3.141})",
        jsonObject1.dump());
    EXPECT_EQ(
        R"({"answer":{"everything":42},"happy":true,"list":[1,0,2],"name":"Niels","nothing":null,"object":{"currency":"USD","value":42.99},"pi":3.141})",
        jsonObject2.dump());
}

TEST(SampleTest, SerializationDeserializationTest) {
    auto jsonObject = json::parse(R"({"happy": true, "pi": 3.141})");

    EXPECT_EQ(R"({"happy":true,"pi":3.141})", jsonObject.dump());
    EXPECT_EQ("{\n    \"happy\": true,\n    \"pi\": 3.141\n}", jsonObject.dump(4));
}

TEST(SampleTest, SerializationDeserializationForFilesTest) {
    json jsonObject = {
        {"happy", true},
        {"pi", 3.141},
    };

    ofstream outputStream(JSON_LIBRARY_TESTS_SAMPLE_FILE);
    outputStream << setw(4) << jsonObject << "\n";
    outputStream.close();

    ifstream inputStream(JSON_LIBRARY_TESTS_SAMPLE_FILE);
    json jsonObjectFromFile;
    inputStream >> jsonObjectFromFile;

    EXPECT_EQ(jsonObject, jsonObjectFromFile);
}

}  // namespace alba
