#pragma once

//Todo
//typedefs
//introduction dag dag from DSP MCU IFS
//refactor to LyxGenerator
//put directory location in Lyx


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
    void readDefinitionFileFromRecursively(std::string const& structureFileName);

    void loadMessagesToGenerate(std::string const& path);
    void loadDescriptionToAdd(std::string const& path);
    void performHacks();


    //lipat eto
    void saveSubsection(std::string const& subsectionName, std::ofstream & lyxOutputFileStream) const;
    void saveMessageDefinitions(std::ofstream & lyxOutputFileStream);
    void saveStructureDefinitions(std::ofstream & lyxOutputFileStream);
    void saveEnumDefinitions(std::ofstream & lyxOutputFileStream);
    void saveUnionDefinitions(std::ofstream & lyxOutputFileStream);
    void saveConstantDefinitions(std::ofstream & lyxOutputFileStream);
    void saveMessageDefinitionSubsubsection(std::string const& messageName, std::ofstream & messageTableStream);
    void saveStructureDefinitionSubsubsection(std::string const& structureName, std::ofstream & structureDefinitionsStream);
    void saveEnumDefinitionSubsubsection(std::string const& enumName, std::ofstream & enumDefinitionsStream);
    void saveUnionDefinitionSubsubsection(std::string const& unionName, std::ofstream & unionDefinitionsStream);
    void saveConstantDefinitionSubsubsection(std::string const& constantName, std::ofstream & unionDefinitionsStream);
    void saveMessageTable(std::string const& messageName, std::ofstream & messageTableStream);
    void saveStructureTable(std::string const& structureName, std::ofstream & structureTableStream);
    void saveEnumTable(std::string const& enumName, std::ofstream & enumTableStream);
    void saveUnionTable(std::string const& unionName, std::ofstream & unionTableStream);
    void saveConstantTable(std::string const& constantName, std::ofstream & constantTableStream);
    void saveDisplayTable(DisplayTable const& messageTable, std::ofstream & messageTableStream) const;
    void generateStructureForDisplayTablesIfNeeded(std::string const& structureName, DisplayTable & messageTable, std::string const& indentionInType, bool const areInnerStructuresGenerated);
    void generateEnumForDisplayTablesIfNeeded(std::string const& enumName, DisplayTable & displayTable);
    void generateUnionForDisplayTablesIfNeeded(std::string const& unionName, DisplayTable & displayTable, std::string const& indentionInType, bool const areInnerStructuresGenerated);
    void generateConstantForDisplayTablesIfNeeded(std::string const& constantName, DisplayTable & displayTable);
    void generateLyxDocument(std::string const& templatePath, std::string const& finalDocumentPath);

private:
    std::string m_path;
    Database m_database;
};

}
