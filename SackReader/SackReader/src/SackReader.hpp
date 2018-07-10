#pragma once

//Todo
//typedefs
//introduction dag dag from DSP MCU IFS
//refactor to LyxGenerator
//put directory location in Lyx

#include <Database.hpp>

namespace alba
{

class SackReader
{
public:
    SackReader(std::string const& path);
    std::string getFileFullPath(std::string const& fileName) const;
    void gatherAllFiles();
    void readFilesNeededForIfs();
    void readAndMarkFilesNecessaryForIfs();
    void saveDatabaseToFile(std::string const& path);
    void loadDatabaseFromFile(std::string const& path);
    void loadMessagesToGenerate(std::string const& path);
    void loadDescriptionToAdd(std::string const& path);
    void performHacks();
    void generateLyxDocument(std::string const& ifsTemplatePath, std::string const& finalDocumentPath);

private:
    void readAndMarkTypeAsNeededInIfs(std::string const& typeName);
    void markStructureAsNeededForIfs(std::string const & structureName);
    void markUnionAsNeededForIfs(std::string const & unionName);
    void markEnumAsNeededForIfs(std::string const& enumName);
    void markConstantAsNeededForIfs(std::string const& enumName);
    void readOamTcomTupcMessageFiles();
    void readConstantFiles();
    void readFileUsingTypeName(std::string const& fileName);
    void readFileUsingTypeFileName(std::string const& typeFileName);

private:
    std::string m_path;
    Database m_database;
};

}
