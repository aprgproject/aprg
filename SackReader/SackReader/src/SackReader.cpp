#include "SackReader.hpp"

#include <File/AlbaFileReader.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>
#include <SackFileReader/SackFileReader.hpp>
#include <String/AlbaStringHelper.hpp>

#include <algorithm>
#include <fstream>


#include <Debug/AlbaDebug.hpp>


using namespace alba::stringHelper;
using namespace std;

namespace alba
{

SackReader::SackReader(string const& path)
    : m_path(path)
{
    m_path = AlbaLocalPathHandler(path).getFullPath();
}

void SackReader::readFileUsingFileNameOnly(string const& fileName)
{
    SackFileReader sackFileReader(m_database);
    ALBA_PRINT1(m_database.getFileFullPath(fileName));
    sackFileReader.readFile(m_database.getFileFullPath(fileName));
}

void SackReader::checkAllFiles()
{
    AlbaLocalPathHandler pathHandler(m_path);
    ListOfPaths files;
    ListOfPaths directories;
    pathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", files, directories);
    for(string const& file : files)
    {
        AlbaLocalPathHandler filePathHandler(file);
        string extension(filePathHandler.getExtension());
        if("c" == extension || "cpp" == extension || "h" == extension || "hpp" == extension || "sig" == extension)
        {
            m_database.fileToPathMap.emplace(filePathHandler.getFile(), filePathHandler.getFullPath());
        }
    }
}

string SackReader::getFileFullPath(string const& fileName) const
{
    return m_database.getFileFullPath(fileName);
}

void SackReader::saveDatabaseToFile(string const& path)
{
    m_database.saveDatabaseToFile(path);
}

void SackReader::loadDatabaseFromFile(string const& path)
{
    m_database.loadDatabaseFromFile(path);
}

void SackReader::checkOamTcomTupcMessages()
{
    readFileUsingFileNameOnly("MessageId_OamAtm.sig");
    readFileUsingFileNameOnly("MessageId_OamTcom.sig");
    readFileUsingFileNameOnly("MessageId_TassuTtm.sig");
    readFileUsingFileNameOnly("MessageId_OamFault.h");
    readFileUsingFileNameOnly("MessageId_Platform.h");
    readFileUsingFileNameOnly("Oam_Atm.h");
    readFileUsingFileNameOnly("oam_tcom.h");
    readFileUsingFileNameOnly("Oam_Tcom_TestModelService.h");
    readFileUsingFileNameOnly("Oam_Tcom_LoopTestService.h");
    readFileUsingFileNameOnly("tassu_ttm.h");
    readFileUsingFileNameOnly("SFaultInd.h");
    readFileUsingFileNameOnly("SModeChangeReq.h");
    readFileUsingFileNameOnly("SModeChangeResp.h");
    //constants
    readFileUsingFileNameOnly("IfAaSysComGw_Defs.h");
    readFileUsingFileNameOnly("DBtsomTcomConstants.h");
    readFileUsingFileNameOnly("DOpenIUBCommonDefs.h");
    readFileUsingFileNameOnly("Glo_bs.h");
    readFileUsingFileNameOnly("DTechLogDef.h");
    for(MessageNameToStructureNamePair const& pair: m_database.messageNameToStructureNameMap)
    {
        if(!pair.second.empty())
        {
            string structureFileName(pair.second+".h");
            readDefinitionFileFromRecursively(structureFileName);
        }
    }
}

void SackReader::readDefinitionFileFromRecursively(string const& typeFileName)
{
    readFileUsingFileNameOnly(typeFileName);
    AlbaLocalPathHandler pathHandler(typeFileName);
    string typeName(pathHandler.getFilenameOnly());
    if(m_database.doesThisStructureExists(typeName))
    {
        for(StructureDetails::ParameterPair const& parameterPair: m_database.structureNameToStructureDetailsMap[typeName].parameters)
        {
            if(!parameterPair.second.type.empty())
            {
                string structureFileNameInStructure(parameterPair.second.type+".h");
                readDefinitionFileFromRecursively(structureFileNameInStructure);
            }
        }
    }
    if(m_database.doesThisUnionExists(typeName))
    {
        for(UnionDetails::ParameterPair const& parameterPair: m_database.unionNameToUnionDetailsMap[typeName].parameters)
        {
            if(!parameterPair.second.type.empty())
            {
                string unionFileNameInUnion(parameterPair.second.type+".h");
                readDefinitionFileFromRecursively(unionFileNameInUnion);
            }
        }
    }
}

void SackReader::saveSubsection(string const& subsectionName, ofstream & lyxOutputFileStream) const
{
    ifstream subsectionStream(R"(C:\APRG\SackReader\SackReader\LyxTemplates\Subsection.txt)");
    AlbaFileReader subsectionReader(subsectionStream);

    while(subsectionReader.isNotFinished())
    {
        string subsectionLine(subsectionReader.getLine());
        if(isStringFoundInsideTheOtherStringCaseSensitive(subsectionLine,"LYX_SUBSECTION_NAME_REPLACE"))
        {
            lyxOutputFileStream << subsectionName << endl;
        }
        else
        {
            lyxOutputFileStream << subsectionLine << endl;
        }
    }
}

void SackReader::saveMessageDefinitions(ofstream & lyxOutputFileStream)
{
    saveSubsection("Message Definitions", lyxOutputFileStream);
    for(string const& messageName : m_database.messagesToGenerate)
    {
        saveMessageDefinitionSubsubsection(messageName, lyxOutputFileStream);
    }
}

void SackReader::saveStructureDefinitions(ofstream & lyxOutputFileStream)
{
    saveSubsection("Structure Definitions", lyxOutputFileStream);
    for(StructureNameToStructureDetailsPair const& pair : m_database.structureNameToStructureDetailsMap)
    {
        if(!pair.second.isMessage && pair.second.isUsedInIfs)
        {
            saveStructureDefinitionSubsubsection(pair.first, lyxOutputFileStream);
        }
    }
}

void SackReader::saveEnumDefinitions(ofstream & lyxOutputFileStream)
{
    saveSubsection("Enum Definitions", lyxOutputFileStream);
    for(EnumNameToEnumDetailsPair const& pair : m_database.enumNameToEnumDetailsMap)
    {
        if(pair.second.isUsedInIfs)
        {
            saveEnumDefinitionSubsubsection(pair.first, lyxOutputFileStream);
        }
    }
}

void SackReader::saveUnionDefinitions(ofstream & lyxOutputFileStream)
{
    saveSubsection("Union Definitions", lyxOutputFileStream);
    for(UnionNameToUnionDetailsPair const& pair : m_database.unionNameToUnionDetailsMap)
    {
        if(pair.second.isUsedInIfs)
        {
            saveUnionDefinitionSubsubsection(pair.first, lyxOutputFileStream);
        }
    }
}

void SackReader::saveConstantDefinitions(ofstream & lyxOutputFileStream)
{
    saveSubsection("Constant Definitions", lyxOutputFileStream);
    for(ConstantNameToConstantDetailsPair const& pair : m_database.constantNameToConstantDetailsMap)
    {
        if(!pair.first.empty())
        {
            char firstCharacter = pair.first[0];
            if(firstCharacter!='E' && isCapitalLetter(firstCharacter))
            {
                if(pair.second.isUsedInIfs)
                {
                    ALBA_PRINT1(pair.first);
                    saveConstantDefinitionSubsubsection(pair.first, lyxOutputFileStream);
                }
            }
        }
    }
}

void SackReader::saveMessageDefinitionSubsubsection(string const& messageName, ofstream & messageDefinitionsStream)
{
    ifstream messageSubsubsectionStream(R"(C:\APRG\SackReader\SackReader\LyxTemplates\MessageSubsubsection.txt)");
    AlbaFileReader messageSubsubsectionReader(messageSubsubsectionStream);

    while(messageSubsubsectionReader.isNotFinished())
    {
        string messageSubsubsectionLine(messageSubsubsectionReader.getLine());
        if(isStringFoundInsideTheOtherStringCaseSensitive(messageSubsubsectionLine,"LYX_TABLE_MESSAGE_NAME_REPLACE"))
        {
            transformReplaceStringIfFound(messageSubsubsectionLine, "LYX_TABLE_MESSAGE_NAME_REPLACE", messageName);
            messageDefinitionsStream << messageSubsubsectionLine << endl;
        }
        else if(isStringFoundInsideTheOtherStringCaseSensitive(messageSubsubsectionLine,"LYX_TABLE_MESSAGE_STRUCTURE_NAME_REPLACE"))
        {
            transformReplaceStringIfFound(messageSubsubsectionLine, "LYX_TABLE_MESSAGE_STRUCTURE_NAME_REPLACE", m_database.getMessageStructure(messageName));
            messageDefinitionsStream << messageSubsubsectionLine << endl;
        }
        else if(isStringFoundInsideTheOtherStringCaseSensitive(messageSubsubsectionLine,"LYX_TABLE_REPLACE"))
        {
            saveMessageTable(messageName, messageDefinitionsStream);
        }
        else
        {
            messageDefinitionsStream << messageSubsubsectionLine << endl;
        }
    }
}

void SackReader::saveStructureDefinitionSubsubsection(string const& structureName, ofstream & structureDefinitionsStream)
{
    ifstream structureSubsubsectionStream(R"(C:\APRG\SackReader\SackReader\LyxTemplates\StructureSubsubsection.txt)");
    AlbaFileReader structureSubsubsectionReader(structureSubsubsectionStream);

    while(structureSubsubsectionReader.isNotFinished())
    {
        string structureSubsubsectionLine(structureSubsubsectionReader.getLine());
        if(isStringFoundInsideTheOtherStringCaseSensitive(structureSubsubsectionLine,"LYX_TABLE_STRUCTURE_NAME_REPLACE"))
        {
            transformReplaceStringIfFound(structureSubsubsectionLine, "LYX_TABLE_STRUCTURE_NAME_REPLACE", structureName);
            structureDefinitionsStream << structureSubsubsectionLine << endl;
        }
        else if(isStringFoundInsideTheOtherStringCaseSensitive(structureSubsubsectionLine,"LYX_TABLE_REPLACE"))
        {
            saveStructureTable(structureName, structureDefinitionsStream);
        }
        else
        {
            structureDefinitionsStream << structureSubsubsectionLine << endl;
        }
    }
}

void SackReader::saveEnumDefinitionSubsubsection(string const& enumName, ofstream & enumDefinitionsStream)
{
    ifstream enumSubsubsectionStream(R"(C:\APRG\SackReader\SackReader\LyxTemplates\EnumSubsubsection.txt)");
    AlbaFileReader enumSubsubsectionReader(enumSubsubsectionStream);

    while(enumSubsubsectionReader.isNotFinished())
    {
        string enumSubsubsectionLine(enumSubsubsectionReader.getLine());
        if(isStringFoundInsideTheOtherStringCaseSensitive(enumSubsubsectionLine,"LYX_TABLE_ENUM_NAME_REPLACE"))
        {
            transformReplaceStringIfFound(enumSubsubsectionLine, "LYX_TABLE_ENUM_NAME_REPLACE", enumName);
            enumDefinitionsStream << enumSubsubsectionLine << endl;
        }
        else if(isStringFoundInsideTheOtherStringCaseSensitive(enumSubsubsectionLine,"LYX_TABLE_REPLACE"))
        {
            saveEnumTable(enumName, enumDefinitionsStream);
        }
        else
        {
            enumDefinitionsStream << enumSubsubsectionLine << endl;
        }
    }
}

void SackReader::saveUnionDefinitionSubsubsection(string const& unionName, ofstream & unionDefinitionsStream)
{
    ifstream unionSubsubsectionStream(R"(C:\APRG\SackReader\SackReader\LyxTemplates\UnionSubsubsection.txt)");
    AlbaFileReader unionSubsubsectionReader(unionSubsubsectionStream);

    while(unionSubsubsectionReader.isNotFinished())
    {
        string unionSubsubsectionLine(unionSubsubsectionReader.getLine());
        if(isStringFoundInsideTheOtherStringCaseSensitive(unionSubsubsectionLine,"LYX_TABLE_UNION_NAME_REPLACE"))
        {
            transformReplaceStringIfFound(unionSubsubsectionLine, "LYX_TABLE_UNION_NAME_REPLACE", unionName);
            unionDefinitionsStream << unionSubsubsectionLine << endl;
        }
        else if(isStringFoundInsideTheOtherStringCaseSensitive(unionSubsubsectionLine,"LYX_TABLE_REPLACE"))
        {
            saveUnionTable(unionName, unionDefinitionsStream);
        }
        else
        {
            unionDefinitionsStream << unionSubsubsectionLine << endl;
        }
    }
}

void SackReader::saveConstantDefinitionSubsubsection(string const& constantName, ofstream & constantDefinitionsStream)
{
    ifstream constantSubsubsectionStream(R"(C:\APRG\SackReader\SackReader\LyxTemplates\CommentSubsubsection.txt)");
    AlbaFileReader constantSubsubsectionReader(constantSubsubsectionStream);

    while(constantSubsubsectionReader.isNotFinished())
    {
        string constantSubsubsectionLine(constantSubsubsectionReader.getLine());
        if(isStringFoundInsideTheOtherStringCaseSensitive(constantSubsubsectionLine,"LYX_TABLE_COMMENT_NAME_REPLACE"))
        {
            transformReplaceStringIfFound(constantSubsubsectionLine, "LYX_TABLE_COMMENT_NAME_REPLACE", constantName);
            constantDefinitionsStream << constantSubsubsectionLine << endl;
        }
        else if(isStringFoundInsideTheOtherStringCaseSensitive(constantSubsubsectionLine,"LYX_TABLE_REPLACE"))
        {
            saveConstantTable(constantName, constantDefinitionsStream);
        }
        else
        {
            constantDefinitionsStream << constantSubsubsectionLine << endl;
        }
    }
}

void SackReader::generateLyxDocument(string const& templatePath, string const& finalDocumentPath)
{
    ifstream lyxDocumentTemplate(templatePath);
    ofstream lyxFinalDocumentStream(finalDocumentPath);
    AlbaFileReader lyxDocumentTemplateReader(lyxDocumentTemplate);

    bool isInsideGeneratedCode(false);
    while(lyxDocumentTemplateReader.isNotFinished())
    {
        string line(lyxDocumentTemplateReader.getLine());
        if(isStringFoundInsideTheOtherStringCaseSensitive(line,"LYX_START_GENERATED_CODE"))
        {
            isInsideGeneratedCode = true;
            lyxFinalDocumentStream << line << endl;
        }
        else if(isStringFoundInsideTheOtherStringCaseSensitive(line,"LYX_END_GENERATED_CODE"))
        {
            isInsideGeneratedCode = false;
            saveMessageDefinitions(lyxFinalDocumentStream);
            saveStructureDefinitions(lyxFinalDocumentStream);
            saveUnionDefinitions(lyxFinalDocumentStream);
            saveEnumDefinitions(lyxFinalDocumentStream);
            saveConstantDefinitions(lyxFinalDocumentStream);
            lyxFinalDocumentStream << line << endl;
        }
        else if(!isInsideGeneratedCode)
        {
            lyxFinalDocumentStream << line << endl;
        }
    }
}

void SackReader::loadMessagesToGenerate(string const& path)
{
    ifstream messageToGenerateStream(path);
    AlbaFileReader messageToGenerateReader(messageToGenerateStream);
    while(messageToGenerateReader.isNotFinished())
    {
        string line(messageToGenerateReader.getLine());
        if(!line.empty())
        {
            m_database.messagesToGenerate.emplace(line);
        }
    }
}

void SackReader::loadDescriptionToAdd(string const& path)
{
    ifstream messageToGenerateStream(path);
    AlbaFileReader messageToGenerateReader(messageToGenerateStream);
    string structureName, parameterName;
    while(messageToGenerateReader.isNotFinished())
    {
        string line(messageToGenerateReader.getLine());
        if(!line.empty())
        {
            if(isStringFoundInsideTheOtherStringCaseSensitive(line, "&&&struct:"))
            {
                structureName = getStringAfterThisString(line, "&&&struct:");
            }
            else if(isStringFoundInsideTheOtherStringCaseSensitive(line, "&&&param:"))
            {
                parameterName = getStringAfterThisString(line, "&&&param:");
            }
            else if(isStringFoundInsideTheOtherStringCaseSensitive(line, "&&&description:"))
            {
                string description(getStringAfterThisString(line, "&&&description:"));
                m_database.structureNameToStructureDetailsMap[structureName].parameters[parameterName].name = parameterName;
                m_database.structureNameToStructureDetailsMap[structureName].parameters[parameterName].descriptionFromUser = description;
            }
        }
    }
}

void SackReader::saveMessageTable(string const& messageName, ofstream & messageTableStream)
{
    DisplayTable messageTable;
    messageTable.setBorders("-"," | ");
    messageTable.addRow();
    messageTable.getLastRow().addCell("\\series bold \nIE/Group Name");
    messageTable.getLastRow().addCell("\\series bold \nIE Type");
    messageTable.getLastRow().addCell("\\series bold \nDescription");
    generateStructureForDisplayTablesIfNeeded(m_database.getMessageStructure(messageName), messageTable, "", true);
    //cout<<messageTable.drawOutput()<<endl;
    saveDisplayTable(messageTable, messageTableStream);
}

void SackReader::saveStructureTable(string const& structureName, ofstream & structureTableStream)
{
    DisplayTable structureTable;
    structureTable.setBorders("-"," | ");
    structureTable.addRow();
    structureTable.getLastRow().addCell("\\series bold \nIE/Group Name");
    structureTable.getLastRow().addCell("\\series bold \nIE Type");
    structureTable.getLastRow().addCell("\\series bold \nDescription");
    generateStructureForDisplayTablesIfNeeded(structureName, structureTable, "", false);
    if(structureTable.getTotalRows()>1)
    {
        //cout<<structureTable.drawOutput()<<endl;
        saveDisplayTable(structureTable, structureTableStream);
    }
}

void SackReader::saveEnumTable(string const& enumName, ofstream & enumTableStream)
{
    DisplayTable enumTable;
    enumTable.setBorders("-"," | ");
    enumTable.addRow();
    enumTable.getLastRow().addCell("\\series bold \nIE/Group Name");
    enumTable.getLastRow().addCell("\\series bold \n Value");
    enumTable.getLastRow().addCell("\\series bold \nDescription");
    generateEnumForDisplayTablesIfNeeded(enumName, enumTable);
    //cout<<enumTable.drawOutput()<<endl;
    saveDisplayTable(enumTable, enumTableStream);
}

void SackReader::saveUnionTable(string const& unionName, ofstream & unionTableStream)
{
    DisplayTable unionTable;
    unionTable.setBorders("-"," | ");
    unionTable.addRow();
    unionTable.getLastRow().addCell("\\series bold \nIE/Group Name");
    unionTable.getLastRow().addCell("\\series bold \nIE Type");
    unionTable.getLastRow().addCell("\\series bold \nDescription");
    generateUnionForDisplayTablesIfNeeded(unionName, unionTable, "", false);
    if(unionTable.getTotalRows()>1)
    {
        //cout<<unionTable.drawOutput()<<endl;
        saveDisplayTable(unionTable, unionTableStream);
    }
}

void SackReader::saveConstantTable(string const& constantName, ofstream & constantTableStream)
{
    DisplayTable constantTable;
    constantTable.setBorders("-"," | ");
    constantTable.addRow();
    constantTable.getLastRow().addCell("\\series bold \nIE/Group Name");
    constantTable.getLastRow().addCell("\\series bold \nIE Value");
    constantTable.getLastRow().addCell("\\series bold \nDescription");
    generateConstantForDisplayTablesIfNeeded(constantName, constantTable);
    if(constantTable.getTotalRows()>1)
    {
        //cout<<constantTable.drawOutput()<<endl;
        saveDisplayTable(constantTable, constantTableStream);
    }
}

void SackReader::saveDisplayTable(DisplayTable const& displayTable, ofstream & displayTableStream) const
{
    ifstream tableTemplateStream(R"(C:\APRG\SackReader\SackReader\LyxTemplates\Table.txt)");
    AlbaFileReader tableTemplateReader(tableTemplateStream);
    while(tableTemplateReader.isNotFinished())
    {
        string tableTemplateLine(tableTemplateReader.getLine());
        if(isStringFoundInsideTheOtherStringCaseSensitive(tableTemplateLine,"LYX_TABLE_REPLACE"))
        {
            for(unsigned int row=0; row<displayTable.getTotalRows(); row++)
            {
                ifstream tableRowTemplateStream(R"(C:\APRG\SackReader\SackReader\LyxTemplates\TableRow.txt)");
                AlbaFileReader tableRowTemplateReader(tableRowTemplateStream);
                while(tableRowTemplateReader.isNotFinished())
                {
                    string tableRowTemplateLine(tableRowTemplateReader.getLine());
                    if(isStringFoundInsideTheOtherStringCaseSensitive(tableRowTemplateLine,"LYX_TABLE_ROW_REPLACE"))
                    {
                        for(unsigned int column=0; column<displayTable.getTotalColumns(); column++)
                        {
                            ifstream tableCellTemplateStream(R"(C:\APRG\SackReader\SackReader\LyxTemplates\TableCell.txt)");
                            AlbaFileReader tableCellTemplateReader(tableCellTemplateStream);
                            while(tableCellTemplateReader.isNotFinished())
                            {
                                string tableCellTemplateLine(tableCellTemplateReader.getLine());
                                if(isStringFoundInsideTheOtherStringCaseSensitive(tableCellTemplateLine,"LYX_TABLE_CELL_REPLACE"))
                                {
                                    displayTableStream << displayTable.getCellConstReference(row, column).getText()<<endl;
                                }
                                else
                                {
                                    displayTableStream << tableCellTemplateLine << endl;
                                }
                            }
                        }
                    }
                    else
                    {
                        displayTableStream << tableRowTemplateLine << endl;
                    }
                }
            }
        }
        else if(isStringFoundInsideTheOtherStringCaseSensitive(tableTemplateLine,"LYX_TABLE_NUM_ROW_REPLACE")
                || isStringFoundInsideTheOtherStringCaseSensitive(tableTemplateLine,"LYX_TABLE_NUM_COLUMN_REPLACE"))
        {
            NumberToStringConverter converter;
            transformReplaceStringIfFound(tableTemplateLine, "LYX_TABLE_NUM_ROW_REPLACE", converter.convert(displayTable.getTotalRows()));
            transformReplaceStringIfFound(tableTemplateLine, "LYX_TABLE_NUM_COLUMN_REPLACE", converter.convert(displayTable.getTotalColumns()));
            displayTableStream << tableTemplateLine << endl;
        }
        else if(isStringFoundInsideTheOtherStringCaseSensitive(tableTemplateLine,"LYX_TABLE_COLUMN_REPLACE"))
        {
            for(unsigned int i=0; i<displayTable.getTotalColumns()-1; i++) //until description
            {
                displayTableStream << tableTemplateLine << endl;
            }
        }
        else if(isStringFoundInsideTheOtherStringCaseSensitive(tableTemplateLine,"LYX_TABLE_DESCRIPTION_COLUMN_REPLACE"))
        {
            displayTableStream << tableTemplateLine << endl; //for description
        }
        else
        {
            displayTableStream << tableTemplateLine << endl;
        }
    }
}

void SackReader::generateStructureForDisplayTablesIfNeeded(string const& structureName, DisplayTable & displayTable, string const& indentionInType, bool const areInnerStructuresGenerated)
{
    string smallTextModifier("\\size footnotesize\n");
    if(m_database.doesThisStructureExists(structureName))
    {
        m_database.structureNameToStructureDetailsMap[structureName].isUsedInIfs=true;
        StructureDetails structureDetails(m_database.getStructureDetails(structureName));
        for(string const& parameterName : structureDetails.parametersWithCorrectOrder)
        {
            ParameterDetails parameterDetails = m_database.getParameterDetails(structureName, parameterName);
            displayTable.addRow();
            displayTable.getLastRow().addCell(smallTextModifier+indentionInType+" "+parameterDetails.name);
            string finalType(parameterDetails.type);
            if(parameterDetails.isAnArray)
            {
                finalType = finalType+" ["+parameterDetails.arraySize+"]";
                //if(m_database.doesThisConstantExists(parameterDetails.arraySize))
                //{
                m_database.constantNameToConstantDetailsMap[parameterDetails.arraySize].isUsedInIfs = true;
                //}
            }
            displayTable.getLastRow().addCell(smallTextModifier+finalType);

            string sackDescription(getStringWithFirstNonWhiteSpaceCharacterToCapital(getStringWithoutStartingAndTrailingWhiteSpace(parameterDetails.description)));
            string userDescription(getStringWithFirstNonWhiteSpaceCharacterToCapital(getStringWithoutStartingAndTrailingWhiteSpace(parameterDetails.descriptionFromUser)));
            string finalDescription;
            if(!userDescription.empty())
            {
                if(sackDescription!=userDescription)
                {
                    //cout <<"The description needs to be aligned with sack."<<endl;
                    /*cout<<"Structure: "<<structureName<<" Parameter: "<<parameterDetails.name<<endl;
                    cout<<"sackDescription: ["<<sackDescription<<"]"<<endl;
                    cout<<"userDescription: ["<<userDescription<<"]"<<endl;*/
                }
                finalDescription = userDescription;
            }
            else
            {
                finalDescription = sackDescription;
            }
            displayTable.getLastRow().addCell(smallTextModifier+finalDescription);
            if(areInnerStructuresGenerated)
            {
                string typeName(parameterDetails.type);
                if(m_database.doesThisEnumExists(typeName))
                {
                    m_database.enumNameToEnumDetailsMap[typeName].isUsedInIfs=true;
                }
                if(m_database.doesThisUnionExists(typeName))
                {
                    m_database.unionNameToUnionDetailsMap[typeName].isUsedInIfs=true;
                }
                generateStructureForDisplayTablesIfNeeded(parameterDetails.type, displayTable, indentionInType+">", true);
            }
        }
    }
}

void SackReader::generateEnumForDisplayTablesIfNeeded(string const& enumName, DisplayTable & displayTable)
{
    string smallTextModifier("\\size footnotesize\n");
    if(m_database.doesThisEnumExists(enumName))
    {
        EnumDetails enumDetails(m_database.getEnumDetails(enumName));

        vector<string> sortedEnumParameterNamesByValue;
        for(EnumDetails::ParameterPair const& parameterPair : enumDetails.parameters)
        {
            sortedEnumParameterNamesByValue.emplace_back(parameterPair.first);
        }
        sort(sortedEnumParameterNamesByValue.begin(), sortedEnumParameterNamesByValue.end(), [&](string const& parameterName1, string const& parameterName2)
        {
            EnumParameterDetails parameterDetails1 = m_database.getEnumParameterDetails(enumName, parameterName1);
            EnumParameterDetails parameterDetails2 = m_database.getEnumParameterDetails(enumName, parameterName2);
            return convertHexStringToNumber<unsigned int>(parameterDetails1.value)<convertHexStringToNumber<unsigned int>(parameterDetails2.value);
        });

        for(string const& parameterName : sortedEnumParameterNamesByValue)
        {
            EnumParameterDetails parameterDetails = m_database.getEnumParameterDetails(enumName, parameterName);
            displayTable.addRow();
            displayTable.getLastRow().addCell(smallTextModifier+" "+parameterDetails.name);
            displayTable.getLastRow().addCell(smallTextModifier+parameterDetails.value);
            string sackDescription(getStringWithFirstNonWhiteSpaceCharacterToCapital(getStringWithoutStartingAndTrailingWhiteSpace(parameterDetails.description)));
            string userDescription(getStringWithFirstNonWhiteSpaceCharacterToCapital(getStringWithoutStartingAndTrailingWhiteSpace(parameterDetails.descriptionFromUser)));
            string finalDescription;
            if(!userDescription.empty())
            {
                if(sackDescription!=userDescription)
                {
                    //cout <<"The description needs to be aligned with sack."<<endl;
                    /*cout<<"Enum: "<<enumName<<" Parameter: "<<parameterDetails.name<<endl;
                    cout<<"sackDescription: ["<<sackDescription<<"]"<<endl;
                    cout<<"userDescription: ["<<userDescription<<"]"<<endl;*/
                }
                finalDescription = userDescription;
            }
            else
            {
                finalDescription = sackDescription;
            }
            displayTable.getLastRow().addCell(smallTextModifier+finalDescription);
        }
    }
}

void SackReader::generateUnionForDisplayTablesIfNeeded(string const& unionName, DisplayTable & displayTable, string const& indentionInType, bool const areInnerStructuresGenerated)
{
    string smallTextModifier("\\size footnotesize\n");
    if(m_database.doesThisUnionExists(unionName))
    {
        m_database.unionNameToUnionDetailsMap[unionName].isUsedInIfs=true;
        UnionDetails unionDetails(m_database.getUnionDetails(unionName));
        for(string const& parameterName : unionDetails.parametersWithCorrectOrder)
        {
            ParameterDetails parameterDetails = m_database.getUnionParameterDetails(unionName, parameterName);
            displayTable.addRow();
            displayTable.getLastRow().addCell(smallTextModifier+indentionInType+" "+parameterDetails.name);
            string finalType(parameterDetails.type);
            if(parameterDetails.isAnArray)
            {
                finalType = finalType+" ["+parameterDetails.arraySize+"]";
                //if(m_database.doesThisConstantExists(parameterDetails.arraySize))
                //{
                m_database.constantNameToConstantDetailsMap[parameterDetails.arraySize].isUsedInIfs = true;
                //}
            }
            displayTable.getLastRow().addCell(smallTextModifier+finalType);

            string sackDescription(getStringWithFirstNonWhiteSpaceCharacterToCapital(getStringWithoutStartingAndTrailingWhiteSpace(parameterDetails.description)));
            string userDescription(getStringWithFirstNonWhiteSpaceCharacterToCapital(getStringWithoutStartingAndTrailingWhiteSpace(parameterDetails.descriptionFromUser)));
            string finalDescription;
            if(!userDescription.empty())
            {
                if(sackDescription!=userDescription)
                {
                    //cout <<"The description needs to be aligned with sack."<<endl;
                    /*cout<<"Union: "<<unionName<<" Parameter: "<<parameterDetails.name<<endl;
                    cout<<"sackDescription: ["<<sackDescription<<"]"<<endl;
                    cout<<"userDescription: ["<<userDescription<<"]"<<endl;*/
                }
                finalDescription = userDescription;
            }
            else
            {
                finalDescription = sackDescription;
            }
            displayTable.getLastRow().addCell(smallTextModifier+finalDescription);
            if(areInnerStructuresGenerated)
            {
                string typeName(parameterDetails.type);
                if(m_database.doesThisEnumExists(typeName))
                {
                    m_database.enumNameToEnumDetailsMap[typeName].isUsedInIfs=true;
                }
                if(m_database.doesThisUnionExists(typeName))
                {
                    m_database.unionNameToUnionDetailsMap[typeName].isUsedInIfs=true;
                }
                generateUnionForDisplayTablesIfNeeded(parameterDetails.type, displayTable, indentionInType+">", true);
            }
        }
    }
}

void SackReader::generateConstantForDisplayTablesIfNeeded(string const& constantName, DisplayTable & displayTable)
{
    string smallTextModifier("\\size footnotesize\n");
    if(m_database.doesThisConstantExists(constantName))
    {
        ConstantDetails constantDetails(m_database.getConstantDetails(constantName));
        displayTable.addRow();
        displayTable.getLastRow().addCell(smallTextModifier+constantDetails.name);
        displayTable.getLastRow().addCell(smallTextModifier+constantDetails.value);
        string sackDescription(getStringWithFirstNonWhiteSpaceCharacterToCapital(getStringWithoutStartingAndTrailingWhiteSpace(constantDetails.description)));
        string userDescription(getStringWithFirstNonWhiteSpaceCharacterToCapital(getStringWithoutStartingAndTrailingWhiteSpace(constantDetails.descriptionFromUser)));
        string finalDescription;
        if(!userDescription.empty())
        {
            if(sackDescription!=userDescription)
            {
                //cout <<"The description needs to be aligned with sack."<<endl;
                /*cout<<"Constant: "<<constantName<<" Parameter: "<<parameterDetails.name<<endl;
                    cout<<"sackDescription: ["<<sackDescription<<"]"<<endl;
                    cout<<"userDescription: ["<<userDescription<<"]"<<endl;*/
            }
            finalDescription = userDescription;
        }
        else
        {
            finalDescription = sackDescription;
        }
        displayTable.getLastRow().addCell(smallTextModifier+finalDescription);
    }
}

void SackReader::performHacks()
{
    //This should be hacked because syscom defines causes a different definition.
    StructureDetails & structureDetails(m_database.structureNameToStructureDetailsMap["SMessageAddress"]);
    structureDetails.name = "SMessageAddress";
    structureDetails.isMessage = false;
    structureDetails.isUsedInIfs = true;
    structureDetails.parametersWithCorrectOrder.clear();
    structureDetails.parametersWithCorrectOrder.emplace_back("board");
    structureDetails.parametersWithCorrectOrder.emplace_back("cpu");
    structureDetails.parametersWithCorrectOrder.emplace_back("task");
    structureDetails.parameters["board"].name = "board";
    structureDetails.parameters["board"].type = "TBoard";
    structureDetails.parameters["board"].isAnArray = false;
    structureDetails.parameters["board"].descriptionFromUser = "Board in SMessageAddress";
    structureDetails.parameters["cpu"].name = "cpu";
    structureDetails.parameters["cpu"].type = "TCpu";
    structureDetails.parameters["cpu"].isAnArray = false;
    structureDetails.parameters["cpu"].descriptionFromUser = "Cpu in SMessageAddress";
    structureDetails.parameters["task"].name = "task";
    structureDetails.parameters["task"].type = "TTask";
    structureDetails.parameters["task"].isAnArray = false;
    structureDetails.parameters["task"].descriptionFromUser = "Task in SMessageAddress";
}



}
