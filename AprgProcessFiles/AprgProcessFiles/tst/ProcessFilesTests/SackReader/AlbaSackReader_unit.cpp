#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <ProcessFiles/SackReader/AlbaSackReader.hpp>
#include <ProcessFilesTests/DirectoryConstants.hpp>

#include <gtest/gtest.h>

#include <fstream>
#include <string>

using namespace std;

namespace alba {

TEST(AlbaSackReaderTest, ClassesAreRecognized) {
    AlbaLocalPathHandler const file1ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE1);
    ofstream testFile(file1ToReadPathHandler.getPath());
    ASSERT_TRUE(testFile.is_open());
    testFile << "class myClass\n";
    testFile << "{\n";
    testFile << "unsigned long int integerParameter;\n";
    testFile << "double doubleParameter;\n";
    testFile << "};\n";
    testFile.close();

    AlbaSackReader sackReader(file1ToReadPathHandler.getPath());
    sackReader.process();
    AlbaSackReaderType const myClass = sackReader.getType("myClass");
    AlbaSackReaderType::Parameters myClassParameters = myClass.getParameters();
    ASSERT_EQ(2U, myClassParameters.size());
    EXPECT_EQ("unsigned long int", myClassParameters[0].getTypeName());
    EXPECT_EQ("integerParameter", myClassParameters[0].getParameterName());
    EXPECT_EQ("double", myClassParameters[1].getTypeName());
    EXPECT_EQ("doubleParameter", myClassParameters[1].getParameterName());
}

TEST(AlbaSackReaderTest, ClassesAreRecognizedInForwardDeclaration) {
    AlbaLocalPathHandler const file1ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE1);
    ofstream testFile(file1ToReadPathHandler.getPath());
    ASSERT_TRUE(testFile.is_open());
    testFile << "class myClass;\n";
    testFile.close();

    AlbaSackReader sackReader(file1ToReadPathHandler.getPath());
    sackReader.process();
    AlbaSackReaderType const myClass = sackReader.getType("myClass");
    AlbaSackReaderType::Parameters const myClassParameters = myClass.getParameters();
    ASSERT_EQ(0U, myClassParameters.size());
}

TEST(AlbaSackReaderTest, TypedefAreRecognized) {
    AlbaLocalPathHandler const file1ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE1);
    ofstream testFile(file1ToReadPathHandler.getPath());
    ASSERT_TRUE(testFile.is_open());
    testFile << "typedef type1 type2;\n";
    testFile.close();

    AlbaSackReader sackReader(file1ToReadPathHandler.getPath());
    sackReader.process();
    AlbaSackReaderType const type1 = sackReader.getType("type1");
    AlbaSackReaderType::Parameters const type1Parameters = type1.getParameters();
    AlbaSackReaderType::TypeNames type1OtherTypes = type1.getOtherTypes();
    AlbaSackReaderType const type2 = sackReader.getType("type2");
    AlbaSackReaderType::Parameters const type2Parameters = type2.getParameters();
    AlbaSackReaderType::TypeNames type2OtherTypes = type2.getOtherTypes();
    ASSERT_EQ(0U, type1Parameters.size());
    ASSERT_EQ(1U, type1OtherTypes.size());
    EXPECT_EQ("type2", *(type1OtherTypes.begin()));
    ASSERT_EQ(0U, type2Parameters.size());
    ASSERT_EQ(1U, type2OtherTypes.size());
    EXPECT_EQ("type1", *(type2OtherTypes.begin()));
}

TEST(AlbaSackReaderTest, TypedefArrayAreRecognized) {
    AlbaLocalPathHandler const file1ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE1);
    ofstream testFile(file1ToReadPathHandler.getPath());
    ASSERT_TRUE(testFile.is_open());
    testFile << "typedef type1 type2 [ 5 ] ;\n";
    testFile.close();

    AlbaSackReader sackReader(file1ToReadPathHandler.getPath());
    sackReader.process();
    AlbaSackReaderType const type1 = sackReader.getType("type1");
    AlbaSackReaderType::Parameters const type1Parameters = type1.getParameters();
    AlbaSackReaderType::TypeNames type1OtherTypes = type1.getOtherTypes();
    AlbaSackReaderType const type2 = sackReader.getType("type2[5]");
    AlbaSackReaderType::Parameters const type2Parameters = type2.getParameters();
    AlbaSackReaderType::TypeNames type2OtherTypes = type2.getOtherTypes();
    ASSERT_EQ(0U, type1Parameters.size());
    ASSERT_EQ(1U, type1OtherTypes.size());
    EXPECT_EQ("type2[5]", *(type1OtherTypes.begin()));
    ASSERT_EQ(0U, type2Parameters.size());
    ASSERT_EQ(1U, type2OtherTypes.size());
    EXPECT_EQ("type1", *(type2OtherTypes.begin()));
}

TEST(AlbaSackReaderTest, TypedefWithStructAreRecognized) {
    AlbaLocalPathHandler const file1ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE1);
    ofstream testFile(file1ToReadPathHandler.getPath());
    ASSERT_TRUE(testFile.is_open());
    testFile << "typedef struct type1 type2;\n";
    testFile.close();

    AlbaSackReader sackReader(file1ToReadPathHandler.getPath());
    sackReader.process();
    AlbaSackReaderType const type2 = sackReader.getType("type2");
    AlbaSackReaderType::Parameters const type2Parameters = type2.getParameters();
    AlbaSackReaderType::TypeNames const type2OtherTypes = type2.getOtherTypes();
    ASSERT_EQ(0U, type2Parameters.size());
    ASSERT_EQ(0U, type2OtherTypes.size());
}

TEST(AlbaSackReaderTest, TypedefWithStructWithParametersAreRecognized) {
    AlbaLocalPathHandler const file1ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE1);
    ofstream testFile(file1ToReadPathHandler.getPath());
    ASSERT_TRUE(testFile.is_open());
    testFile << "typedef struct myStruct1\n";
    testFile << "{\n";
    testFile << "unsigned long int integerParameter;\n";
    testFile << "double doubleParameter;\n";
    testFile << "} myStruct2;\n";
    testFile.close();

    AlbaSackReader sackReader(file1ToReadPathHandler.getPath());
    sackReader.process();
    AlbaSackReaderType const myClass = sackReader.getType("myStruct2");
    AlbaSackReaderType::Parameters myClassParameters = myClass.getParameters();
    AlbaSackReaderType::TypeNames const myClassOtherTypes = myClass.getOtherTypes();
    ASSERT_EQ(2U, myClassParameters.size());
    EXPECT_EQ("unsigned long int", myClassParameters[0].getTypeName());
    EXPECT_EQ("integerParameter", myClassParameters[0].getParameterName());
    EXPECT_EQ("double", myClassParameters[1].getTypeName());
    EXPECT_EQ("doubleParameter", myClassParameters[1].getParameterName());
    ASSERT_EQ(0U, myClassOtherTypes.size());
}

TEST(AlbaSackReaderTest, TypedefWithSingleStructWithParametersAreRecognized) {
    AlbaLocalPathHandler const file1ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE1);
    ofstream testFile(file1ToReadPathHandler.getPath());
    ASSERT_TRUE(testFile.is_open());
    testFile << "typedef struct\n";
    testFile << "{\n";
    testFile << "unsigned long int integerParameter;\n";
    testFile << "double doubleParameter;\n";
    testFile << "} myStruct1;\n";
    testFile.close();

    AlbaSackReader sackReader(file1ToReadPathHandler.getPath());
    sackReader.process();
    AlbaSackReaderType const myClass = sackReader.getType("myStruct1");
    AlbaSackReaderType::Parameters myClassParameters = myClass.getParameters();
    AlbaSackReaderType::TypeNames const myClassOtherTypes = myClass.getOtherTypes();
    ASSERT_EQ(2U, myClassParameters.size());
    EXPECT_EQ("unsigned long int", myClassParameters[0].getTypeName());
    EXPECT_EQ("integerParameter", myClassParameters[0].getParameterName());
    EXPECT_EQ("double", myClassParameters[1].getTypeName());
    EXPECT_EQ("doubleParameter", myClassParameters[1].getParameterName());
    ASSERT_EQ(0U, myClassOtherTypes.size());
    EXPECT_FALSE(myClass.isUnion());
}

TEST(AlbaSackReaderTest, TypedefWithUnionWithParametersAreRecognized) {
    AlbaLocalPathHandler const file1ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE1);
    ofstream testFile(file1ToReadPathHandler.getPath());
    ASSERT_TRUE(testFile.is_open());
    testFile << "typedef union myUnion1\n";
    testFile << "{\n";
    testFile << "unsigned long int integerParameter;\n";
    testFile << "double doubleParameter;\n";
    testFile << "} myUnion2;\n";
    testFile.close();

    AlbaSackReader sackReader(file1ToReadPathHandler.getPath());
    sackReader.process();
    AlbaSackReaderType const myClass = sackReader.getType("myUnion2");
    AlbaSackReaderType::Parameters myClassParameters = myClass.getParameters();
    AlbaSackReaderType::TypeNames const myClassOtherTypes = myClass.getOtherTypes();
    ASSERT_EQ(2U, myClassParameters.size());
    EXPECT_EQ("unsigned long int", myClassParameters[0].getTypeName());
    EXPECT_EQ("integerParameter", myClassParameters[0].getParameterName());
    EXPECT_EQ("double", myClassParameters[1].getTypeName());
    EXPECT_EQ("doubleParameter", myClassParameters[1].getParameterName());
    ASSERT_EQ(0U, myClassOtherTypes.size());
    EXPECT_TRUE(myClass.isUnion());
}

TEST(AlbaSackReaderTest, TypedefWithEnumAreRecognized) {
    AlbaLocalPathHandler const file1ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE1);
    ofstream testFile(file1ToReadPathHandler.getPath());
    ASSERT_TRUE(testFile.is_open());
    testFile << "typedef enum {\n";
    testFile << "MyEnum_Value0  = 0,\n";
    testFile << "MyEnum_Value2  = 2,\n";
    testFile << "MyEnum_Value5  = 5\n";
    testFile << "} MyEnum;\n";
    testFile << "\n";
    testFile.close();

    AlbaSackReader sackReader(file1ToReadPathHandler.getPath());
    sackReader.process();
    AlbaSackReaderType const myClass = sackReader.getType("MyEnum");
    AlbaSackReaderType::Parameters const myClassParameters = myClass.getParameters();
    ASSERT_EQ(0U, myClassParameters.size());
}

TEST(AlbaSackReaderTest, SackTest) {
    AlbaSackReader sackReader(R"(D:\W\trunk\I_Interface)", "[.cpp] || [.hpp] || [.c] || [.h]");
    sackReader.process();
    sackReader.printAll();
}

}  // namespace alba
