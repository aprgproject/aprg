#include <CodeUtilities/CPlusPlus/CPlusPlusUtilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::CodeUtilities::CPlusPlusUtilities {

TEST(CPlusPlusUtilitiesTest, GetTermsFromStringWorks) {
    Terms actualTerms(getTermsFromString("identifier1 identifier2 identifier3"));

    Terms expectedTerms{
        Term(TermType::Identifier, "identifier1"), Term(TermType::WhiteSpace, " "),
        Term(TermType::Identifier, "identifier2"), Term(TermType::WhiteSpace, " "),
        Term(TermType::Identifier, "identifier3")};

    EXPECT_EQ(expectedTerms, actualTerms);
}

TEST(CPlusPlusUtilitiesTest, GetFunctionSignatureWorks) {
    string wholeFunction =
        "/*Comment*/ \t\t\n friend static name::AlbaOptional::AlbaOptional(AlbaOptional<ContentType&> const& optional) "
        ":  m_hasContent(optional.m_hasContent),  {}";

    string functionSignature(getFunctionSignature(wholeFunction));

    EXPECT_EQ("AlbaOptional(AlbaOptional<ContentType&> const& optional)", functionSignature);
}

}  // namespace alba::CodeUtilities::CPlusPlusUtilities
