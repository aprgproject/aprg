#pragma once

#include <CommonTypes.hpp>
#include <Database.hpp>
#include <User/AlbaDisplayTable.hpp>

namespace alba
{

class SackReader
{
public:
    SackReader(std::string const& path);
    void readFileUsingFileNameOnly(std::string const& fileName);
    void checkAllFiles();
    std::string getFileFullPath(std::string const& fileName) const;
    void saveDatabaseToFile(std::string const& path);
    void loadDatabaseFromFile(std::string const& path);
    void checkOamTcomTupcMessages();
    void readDefinitionFileFromStructureRecursively(std::string const& structureFileName);
    void saveSubsection(std::string const& subsectionName, std::ofstream & lyxOutputFileStream) const;
    void saveMessageDefinitions(std::ofstream & lyxOutputFileStream);
    void saveStructureDefinitions(std::ofstream & lyxOutputFileStream);
    void saveEnumDefinitions(std::ofstream & lyxOutputFileStream);
    void saveMessageDefinitionSubsubsection(std::string const& messageName, std::ofstream & messageTableStream);
    void saveStructureDefinitionSubsubsection(std::string const& structureName, std::ofstream & structureDefinitionsStream);
    void saveEnumDefinitionSubsubsection(std::string const& enumName, std::ofstream & enumDefinitionsStream);
    void saveMessageTable(std::string const& messageName, std::ofstream & messageTableStream);
    void saveStructureTable(std::string const& structureName, std::ofstream & structureTableStream);
    void saveEnumTable(std::string const& enumName, std::ofstream & enumTableStream);
    void saveDisplayTable(DisplayTable const& messageTable, std::ofstream & messageTableStream) const;
    void generateStructureForDisplayTablesIfNeeded(std::string const& structureName, DisplayTable & messageTable, std::string const& indentionInType, bool const areInnerStructuresGenerated);
    void generateEnumForDisplayTablesIfNeeded(std::string const& enumName, DisplayTable & displayTable);
    void generateLyxDocument(std::string const& templatePath, std::string const& finalDocumentPath);
    void loadMessagesToGenerate(std::string const& path);
    void loadDescriptionToAdd(std::string const& path);
    void performHacks();

private:
    std::string m_path;
    Database m_database;
};

}
