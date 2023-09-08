#pragma once

#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <GrepStringEvaluator/AlbaGrepStringEvaluator.hpp>
#include <ProcessFiles/SackReader/AlbaSackReaderType.hpp>

#include <map>
#include <string>

namespace alba {

class AlbaSackReader {
public:
    enum class ReaderState {

        LookingForInitialKeyword,
        ClassStateLookingForClassName,
        ClassStateLookingForOpeningBraceOrSemiColon,
        ClassStateLookingForParameters,
        TypedefStateLookingForTypeName,
        TypedefStateLookingForSecondType,
        TypedefStateLookingForSemicolon,
        TypedefStructStateLookingForNameOrOpeningBraceOrSecondType,
        TypedefStructStateLookingForParameters,
        TypedefStructStateLookingForSecondType,
        TypedefEnumStateLookingForOpeningBrace,
        TypedefEnumStateLookingForClosingBrace,
        TypedefEnumStateLookingForType

    };

    struct ReaderTransactionData {
        ReaderState state;
        std::string typeName;
        std::string firstIdentifier;
        std::string secondIdentifier;
        AlbaSackReaderType type;
    };

    explicit AlbaSackReader(std::string const& inputFilePath);
    AlbaSackReader(std::string const& inputFilePath, std::string const& fileCondition);
    [[nodiscard]] AlbaSackReaderType getType(std::string const& typeName) const;
    void printAll() const;
    void process();

private:
    static std::string getReaderStateString(ReaderState const state);
    static void tokenize(stringHelper::strings& tokens, std::string const& line);
    static void combineWords(stringHelper::strings& tokens);
    static void combineArrayOperators(stringHelper::strings& tokens);
    void processDirectory(std::string const& path);
    void processFile(std::string const& path);
    void analyze(stringHelper::strings const& tokens);
    template <ReaderState readerState>
    void analyzeInReaderState(ReaderTransactionData& transactionData, std::string const& token);
    AlbaLocalPathHandler m_inputPathHandler;
    std::map<std::string, AlbaSackReaderType> m_types;
    AlbaGrepStringEvaluator m_fileEvaluator;
};

}  // namespace alba
