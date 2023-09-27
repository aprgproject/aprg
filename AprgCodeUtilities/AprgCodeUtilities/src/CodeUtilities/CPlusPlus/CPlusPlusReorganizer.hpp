#pragma once

#include <CodeUtilities/CPlusPlus/CPlusPlusTypes.hpp>
#include <CodeUtilities/Common/CommonTypes.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <filesystem>

namespace alba::CodeUtilities {

class CPlusPlusReorganizer {
public:
    enum class Purpose { Unknown, Reorganize, GatherInformation };

    struct ScopeDetail {
        int scopeHeaderStart;
        int openingBraceIndex;
        int scopeEnd;
        ScopeType scopeType;
        std::string name;
        stringHelper::strings items;
    };

    struct HeaderInformation {
        stringHelper::strings functionSignatures;
        Patterns functionNamePatterns;
    };

    struct CppFiles {
        std::filesystem::path headerFile;
        std::filesystem::path implementationFile;
        std::filesystem::path testFile;
        bool isHeaderFileProcessed{false};
        bool isImplementationFileProcessed{false};
        bool isTestFileProcessed{false};
    };

    CPlusPlusReorganizer() = default;
    void processDirectory(std::filesystem::path const& directory);
    void processHeaderFile(std::filesystem::path const& headerFile);

    void processImplementationFile(
        std::filesystem::path const& headerFile, std::filesystem::path const& implementationFile);

private:
    [[nodiscard]] ScopeDetail constructScopeDetails(int const scopeHeaderStart, int const openingBraceIndex) const;
    [[nodiscard]] std::string getFormattedContent(int const start, int const end) const;
    [[nodiscard]] stringHelper::strings getScopeNames() const;
    [[nodiscard]] stringHelper::strings getSavedSignatures() const;
    [[nodiscard]] int getIndexAtSameLineComment(int const index) const;
    void reorganizeFile(std::filesystem::path const& file);
    void gatherInformationFromFile(std::filesystem::path const& file);
    void processTerms();
    void processMacro(int& nextIndex, int const macroStartIndex);
    void processSemiColon(int& nextIndex, int const semiColonIndex);

    void processOpeningAndClosingBrace(
        int& nextIndex, int const openingBraceIndex, int const closingBraceSemiColonIndex);

    void processOpeningBrace(int& nextIndex, int const openingBraceIndex);
    void processClosingBrace(int& nextIndex, int const closingBraceIndex, int const closingBraceSemiColonIndex);
    void processRecognizedItem(int& nextIndex, int const recognizedItemEndIndex);
    void enterAndSetTopLevelScope();
    void exitTopLevelScope();
    void enterScope(int const scopeHeaderStart, int const openingBraceIndex);
    void exitScope(int& nextIndex, int const closingBraceIndex, int const endIndex);
    void addItemIfNeeded(int const startIndex, int const endIndex);
    ScopeDetail& getCurrentScope();
    [[nodiscard]] static bool shouldReorganizeInThisScope(ScopeDetail const& scope);
    [[nodiscard]] static bool shouldConnectToPreviousItem(Terms const& scopeHeaderTerms);
    [[nodiscard]] static bool hasEndBrace(std::string const& content);
    static void makeIsolatedCommentsStickWithNextLine(Terms& terms);
    static void removeStartingAndTrailingWhiteSpace(Terms& terms);
    CppFileType m_fileType{CppFileType::Unknown};
    Purpose m_purpose{Purpose::Unknown};
    std::vector<ScopeDetail> m_scopeDetails;
    HeaderInformation m_headerInformation;
    Terms m_terms;
};

}  // namespace alba::CodeUtilities
