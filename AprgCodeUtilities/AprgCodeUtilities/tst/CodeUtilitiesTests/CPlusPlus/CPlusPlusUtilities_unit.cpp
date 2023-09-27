#include <CodeUtilities/CPlusPlus/CPlusPlusUtilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::CodeUtilities::CPlusPlusUtilities {

TEST(CPlusPlusUtilitiesTest, GetTermsFromStringWorks) {
    Terms const actualTerms(getTermsFromString("identifier1 identifier2 identifier3"));

    Terms const expectedTerms{
        Term(TermType::Identifier, "identifier1"), Term(TermType::WhiteSpace, " "),
        Term(TermType::Identifier, "identifier2"), Term(TermType::WhiteSpace, " "),
        Term(TermType::Identifier, "identifier3")};

    EXPECT_EQ(expectedTerms, actualTerms);
}

TEST(CPlusPlusUtilitiesTest, GetTextWithoutCommentsWithNewLineWorks) {
    string const codeWithComments = "Code\n /*MultilineComment*/\n //SingleLineComment\n Code\n";
    Terms const termsWithComments(getTermsFromString(codeWithComments));

    string const codeWithoutComments(getTextWithoutCommentsWithNewLine(termsWithComments));

    EXPECT_EQ("Code\n Code\n", codeWithoutComments);
}

TEST(CPlusPlusUtilitiesTest, GetFunctionSignatureWorks) {
    string const wholeFunction =
        "/*Comment*/ \t\t\n friend static name::AlbaOptional::AlbaOptional(AlbaOptional<ContentType&> const& optional) "
        ":  m_hasContent(optional.m_hasContent),  {}";

    string const functionSignature(getFunctionSignature(wholeFunction));

    EXPECT_EQ("AlbaOptional(AlbaOptional<ContentType&> const& optional)", functionSignature);
}

TEST(CPlusPlusUtilitiesTest, GetFunctionSignatureWorksWithEqualsDefault) {
    string const wholeFunction = "AlbaOptional(AlbaOptional<ContentType&> const& optional) =   default;";

    string const functionSignature(getFunctionSignature(wholeFunction));

    EXPECT_EQ("AlbaOptional(AlbaOptional<ContentType&> const& optional)", functionSignature);
}

TEST(CPlusPlusUtilitiesTest, GetFunctionNameWorks) {
    string const functionSignature = "AlbaOptional(AlbaOptional<ContentType&> const& optional)";

    string const functionName(getFunctionName(functionSignature));

    EXPECT_EQ("AlbaOptional", functionName);
}

}  // namespace alba::CodeUtilities::CPlusPlusUtilities
