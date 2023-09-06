#include <CodeUtilities/CPlusPlus/CPlusPlusTokenizer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::CodeUtilities {

TEST(CPlusPlusTokenizerTest, CheckWhiteSpace) {
    Terms terms;
    CPlusPlusTokenizer tokenizer(terms);

    tokenizer.processCode("   ABC   DE  GH  I JK  L MN  OPQ   \n");
    tokenizer.processCode("\t\t ABC\t\t\tDE\t GH \tI\tJK\t L\tMN \tOPQ \t \n");
    tokenizer.processCode("1   2\t\t\t3 \t \t  \t\t4\n");
    tokenizer.processLeftoverCode();

    ASSERT_EQ(terms.size(), 41U);
    auto termIterator = terms.begin();
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, "   "));
    EXPECT_EQ(*termIterator++, Term(TermType::Identifier, "ABC"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, "   "));
    EXPECT_EQ(*termIterator++, Term(TermType::Identifier, "DE"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, "  "));
    EXPECT_EQ(*termIterator++, Term(TermType::Identifier, "GH"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, "  "));
    EXPECT_EQ(*termIterator++, Term(TermType::Identifier, "I"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::Identifier, "JK"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, "  "));
    EXPECT_EQ(*termIterator++, Term(TermType::Identifier, "L"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::Identifier, "MN"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, "  "));
    EXPECT_EQ(*termIterator++, Term(TermType::Identifier, "OPQ"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, "   \n\t\t "));
    EXPECT_EQ(*termIterator++, Term(TermType::Identifier, "ABC"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, "\t\t\t"));
    EXPECT_EQ(*termIterator++, Term(TermType::Identifier, "DE"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, "\t "));
    EXPECT_EQ(*termIterator++, Term(TermType::Identifier, "GH"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " \t"));
    EXPECT_EQ(*termIterator++, Term(TermType::Identifier, "I"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, "\t"));
    EXPECT_EQ(*termIterator++, Term(TermType::Identifier, "JK"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, "\t "));
    EXPECT_EQ(*termIterator++, Term(TermType::Identifier, "L"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, "\t"));
    EXPECT_EQ(*termIterator++, Term(TermType::Identifier, "MN"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " \t"));
    EXPECT_EQ(*termIterator++, Term(TermType::Identifier, "OPQ"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " \t \n"));
    EXPECT_EQ(*termIterator++, Term(TermType::Number, "1"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, "   "));
    EXPECT_EQ(*termIterator++, Term(TermType::Number, "2"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, "\t\t\t"));
    EXPECT_EQ(*termIterator++, Term(TermType::Number, "3"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " \t \t  \t\t"));
    EXPECT_EQ(*termIterator++, Term(TermType::Number, "4"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, "\n"));
}

TEST(CPlusPlusTokenizerTest, CheckIncludeFiles) {
    Terms terms;
    CPlusPlusTokenizer tokenizer(terms);

    tokenizer.processCode("#include<iostream>\n");
    tokenizer.processCode("#INCLUDE<main1.cpp>\n");
    tokenizer.processCode(" #include < main11.cpp > \n");
    tokenizer.processLeftoverCode();

    ASSERT_EQ(terms.size(), 22U);
    auto termIterator = terms.begin();
    EXPECT_EQ(*termIterator++, Term(TermType::Macro, "#include"));
    EXPECT_EQ(*termIterator++, Term(TermType::Operator, "<"));
    EXPECT_EQ(*termIterator++, Term(TermType::Identifier, "iostream"));
    EXPECT_EQ(*termIterator++, Term(TermType::Operator, ">"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, "\n"));
    EXPECT_EQ(*termIterator++, Term(TermType::Macro, "#INCLUDE"));
    EXPECT_EQ(*termIterator++, Term(TermType::Operator, "<"));
    EXPECT_EQ(*termIterator++, Term(TermType::Identifier, "main1"));
    EXPECT_EQ(*termIterator++, Term(TermType::Operator, "."));
    EXPECT_EQ(*termIterator++, Term(TermType::Identifier, "cpp"));
    EXPECT_EQ(*termIterator++, Term(TermType::Operator, ">"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, "\n "));
    EXPECT_EQ(*termIterator++, Term(TermType::Macro, "#include"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::Operator, "<"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::Identifier, "main11"));
    EXPECT_EQ(*termIterator++, Term(TermType::Operator, "."));
    EXPECT_EQ(*termIterator++, Term(TermType::Identifier, "cpp"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::Operator, ">"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " \n"));
}

TEST(CPlusPlusTokenizerTest, CheckIdentifiersAndConstants) {
    Terms terms;
    CPlusPlusTokenizer tokenizer(terms);

    tokenizer.processCode("aBcdwXyZ def1 2ghi jkl_3 4_mnop true false\n");
    tokenizer.processLeftoverCode();

    ASSERT_EQ(terms.size(), 14U);
    auto termIterator = terms.begin();
    EXPECT_EQ(*termIterator++, Term(TermType::Identifier, "aBcdwXyZ"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::Identifier, "def1"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::Number, "2ghi"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::Identifier, "jkl_3"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::Number, "4_mnop"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::Boolean, "true"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::Boolean, "false"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, "\n"));
}

TEST(CPlusPlusTokenizerTest, CheckMacros) {
    Terms terms;
    CPlusPlusTokenizer tokenizer(terms);

    tokenizer.processCode("#define # undef #  ifdef #nottrue #\tifndef #\nendif #   if #\t \tinclude ");
    tokenizer.processLeftoverCode();

    // This test shows that macro handling is not aligned with specification
    // Spaces between sharp and identifier are still macros, but clang-format already removes the spaces.
    // So there is no need to process it.
    ASSERT_EQ(terms.size(), 28U);
    auto termIterator = terms.begin();
    EXPECT_EQ(*termIterator++, Term(TermType::Macro, "#define"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::Operator, "#"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::Identifier, "undef"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::Operator, "#"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, "  "));
    EXPECT_EQ(*termIterator++, Term(TermType::Identifier, "ifdef"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::Macro, "#nottrue"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::Operator, "#"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, "\t"));
    EXPECT_EQ(*termIterator++, Term(TermType::Identifier, "ifndef"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::Operator, "#"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, "\n"));
    EXPECT_EQ(*termIterator++, Term(TermType::Identifier, "endif"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::Operator, "#"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, "   "));
    EXPECT_EQ(*termIterator++, Term(TermType::Keyword, "if"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::Operator, "#"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, "\t \t"));
    EXPECT_EQ(*termIterator++, Term(TermType::Identifier, "include"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
}

TEST(CPlusPlusTokenizerTest, CheckOperatorWords) {
    Terms terms;
    CPlusPlusTokenizer tokenizer(terms);

    tokenizer.processCode("typeid const_cast static_cast reinterpret_cast static_cast sizeof new delete throw\n");
    tokenizer.processLeftoverCode();

    ASSERT_EQ(terms.size(), 18U);
    auto termIterator = terms.begin();
    EXPECT_EQ(*termIterator++, Term(TermType::Keyword, "typeid"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::Keyword, "const_cast"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::Keyword, "static_cast"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::Keyword, "reinterpret_cast"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::Keyword, "static_cast"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::Keyword, "sizeof"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::Keyword, "new"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::Keyword, "delete"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::Keyword, "throw"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, "\n"));
}

TEST(CPlusPlusTokenizerTest, CheckTypeWords) {
    Terms terms;
    CPlusPlusTokenizer tokenizer(terms);

    tokenizer.processCode("bool char char16_t char32_t double float int long short signed unsigned void wchar_t\n");
    tokenizer.processLeftoverCode();

    ASSERT_EQ(terms.size(), 26U);
    auto termIterator = terms.begin();
    EXPECT_EQ(*termIterator++, Term(TermType::PrimitiveType, "bool"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::PrimitiveType, "char"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::PrimitiveType, "char16_t"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::PrimitiveType, "char32_t"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::PrimitiveType, "double"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::PrimitiveType, "float"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::PrimitiveType, "int"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::PrimitiveType, "long"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::PrimitiveType, "short"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::PrimitiveType, "signed"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::PrimitiveType, "unsigned"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::PrimitiveType, "void"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::PrimitiveType, "wchar_t"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, "\n"));
}

TEST(CPlusPlusTokenizerTest, CheckMultipleCharacterOperators) {
    Terms terms;
    CPlusPlusTokenizer tokenizer(terms);

    tokenizer.processCode("->* <<= >>=\n");
    tokenizer.processLeftoverCode();

    ASSERT_EQ(terms.size(), 6U);
    auto termIterator = terms.begin();
    EXPECT_EQ(*termIterator++, Term(TermType::Operator, "->*"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::Operator, "<<="));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::Operator, ">>="));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, "\n"));
}

TEST(CPlusPlusTokenizerTest, CheckPeriod) {
    Terms terms;
    CPlusPlusTokenizer tokenizer(terms);

    tokenizer.processCode(". .. ...\n");
    tokenizer.processLeftoverCode();

    ASSERT_EQ(terms.size(), 9U);
    auto termIterator = terms.begin();
    EXPECT_EQ(*termIterator++, Term(TermType::Operator, "."));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::Operator, "."));
    EXPECT_EQ(*termIterator++, Term(TermType::Operator, "."));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::Operator, "."));
    EXPECT_EQ(*termIterator++, Term(TermType::Operator, "."));
    EXPECT_EQ(*termIterator++, Term(TermType::Operator, "."));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, "\n"));
}

TEST(CPlusPlusTokenizerTest, CheckSingleLineComment) {
    Terms terms;
    CPlusPlusTokenizer tokenizer(terms);

    tokenizer.processCode("aBcdwXyZ //This is @ 1 line comment\n");
    tokenizer.processCode("         \t\t    //This is @ 1 line comment with spaces and tabs before");
    tokenizer.processLeftoverCode();

    ASSERT_EQ(terms.size(), 5U);
    auto termIterator = terms.begin();
    EXPECT_EQ(*termIterator++, Term(TermType::Identifier, "aBcdwXyZ"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::CommentSingleLine, "//This is @ 1 line comment"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, "\n         \t\t    "));
    EXPECT_EQ(
        *termIterator++, Term(TermType::CommentSingleLine, "//This is @ 1 line comment with spaces and tabs before"));
}

TEST(CPlusPlusTokenizerTest, CheckMultiLineComment) {
    Terms terms;
    CPlusPlusTokenizer tokenizer(terms);

    tokenizer.processCode("aBcdwXyZ /*This is @\n");
    tokenizer.processCode("  Multiline\n");
    tokenizer.processCode("  Comment*/ deFsTUv\n");
    tokenizer.processLeftoverCode();

    ASSERT_EQ(terms.size(), 6U);
    auto termIterator = terms.begin();
    EXPECT_EQ(*termIterator++, Term(TermType::Identifier, "aBcdwXyZ"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::CommentMultiline, "/*This is @\n  Multiline\n  Comment*/"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::Identifier, "deFsTUv"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, "\n"));
}

TEST(CPlusPlusTokenizerTest, CheckString) {
    Terms terms;
    CPlusPlusTokenizer tokenizer(terms);

    tokenizer.processCode("aBcdwXyZ \"This is @ simple string\" deFsTUv\n");
    tokenizer.processCode("aBcdwXyZ \"This is @ string with \\\"quotation\\\"\" deFsTUv\n");
    tokenizer.processCode("\'Q\' \'\"\' \'\\\'\' \'This is @character\'\n");
    tokenizer.processCode("R\"(Space   \\\" \' Space)\"\n");
    tokenizer.processLeftoverCode();

    ASSERT_EQ(terms.size(), 22U);
    auto termIterator = terms.begin();
    EXPECT_EQ(*termIterator++, Term(TermType::Identifier, "aBcdwXyZ"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::StringLiteral, "\"This is @ simple string\""));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::Identifier, "deFsTUv"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, "\n"));
    EXPECT_EQ(*termIterator++, Term(TermType::Identifier, "aBcdwXyZ"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::StringLiteral, "\"This is @ string with \\\"quotation\\\"\""));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::Identifier, "deFsTUv"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, "\n"));
    EXPECT_EQ(*termIterator++, Term(TermType::CharacterLiteral, "\'Q\'"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::CharacterLiteral, "\'\"\'"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::CharacterLiteral, "\'\\\'\'"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::CharacterLiteral, "\'This is @character\'"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, "\n"));
    EXPECT_EQ(*termIterator++, Term(TermType::StringLiteral, "R\"(Space   \\\" \' Space)\""));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, "\n"));
}

TEST(CPlusPlusTokenizerTest, CheckStringWithSlashes) {
    Terms terms;
    CPlusPlusTokenizer tokenizer(terms);

    tokenizer.processCode("aBcdwXyZ1 \"\\\\\" deFsTUv2\n");
    tokenizer.processCode("aBcdwXyZ3 \"\\\\\\\\\" deFsTUv4\n");
    tokenizer.processCode("aBcdwXyZ5 \"\\\\\\\"\\\"\\\\\" deFsTUv6\n");
    tokenizer.processCode("aBcdwXyZ5 R\"(\\\\\\\"\\\"\\\\)\" deFsTUv6\n");
    tokenizer.processLeftoverCode();

    ASSERT_EQ(terms.size(), 24U);
    auto termIterator = terms.begin();
    EXPECT_EQ(*termIterator++, Term(TermType::Identifier, "aBcdwXyZ1"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::StringLiteral, "\"\\\\\""));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::Identifier, "deFsTUv2"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, "\n"));
    EXPECT_EQ(*termIterator++, Term(TermType::Identifier, "aBcdwXyZ3"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::StringLiteral, "\"\\\\\\\\\""));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::Identifier, "deFsTUv4"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, "\n"));
    EXPECT_EQ(*termIterator++, Term(TermType::Identifier, "aBcdwXyZ5"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::StringLiteral, "\"\\\\\\\"\\\"\\\\\""));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::Identifier, "deFsTUv6"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, "\n"));
    EXPECT_EQ(*termIterator++, Term(TermType::Identifier, "aBcdwXyZ5"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::StringLiteral, "R\"(\\\\\\\"\\\"\\\\)\""));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::Identifier, "deFsTUv6"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, "\n"));
}

TEST(CPlusPlusTokenizerTest, CheckKeyword) {
    Terms terms;
    CPlusPlusTokenizer tokenizer(terms);

    tokenizer.processCode("for while if\n");
    tokenizer.processLeftoverCode();

    ASSERT_EQ(terms.size(), 6U);
    auto termIterator = terms.begin();
    EXPECT_EQ(*termIterator++, Term(TermType::Keyword, "for"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::Keyword, "while"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::Keyword, "if"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, "\n"));
}

TEST(CPlusPlusTokenizerTest, CheckAttibute) {
    Terms terms;
    CPlusPlusTokenizer tokenizer(terms);

    tokenizer.processCode("[[nodiscard]] [[gnu::unused]] [[deprecated(\"because\")]]\n");
    tokenizer.processLeftoverCode();

    ASSERT_EQ(terms.size(), 6U);
    auto termIterator = terms.begin();
    EXPECT_EQ(*termIterator++, Term(TermType::Attribute, "[[nodiscard]]"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::Attribute, "[[gnu::unused]]"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, " "));
    EXPECT_EQ(*termIterator++, Term(TermType::Attribute, "[[deprecated(\"because\")]]"));
    EXPECT_EQ(*termIterator++, Term(TermType::WhiteSpace, "\n"));
}

}  // namespace alba::CodeUtilities
