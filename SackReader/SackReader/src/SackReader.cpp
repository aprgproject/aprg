#include "SackReader.hpp"

#include <File/AlbaFileReader.hpp>
#include <LyxGenerator.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>
#include <SackFileReader/SackFileReader.hpp>
#include <String/AlbaStringHelper.hpp>

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

string SackReader::getFileFullPath(string const& fileName) const
{
    return m_database.getFileFullPath(fileName);
}

void SackReader::gatherAllFiles()
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

void SackReader::readFilesNeededForIfs()
{
    readConstantFiles();
    readOamTcomTupcMessageFiles();
}

void SackReader::readAndMarkFilesNecessaryForIfs()
{
    for(string const& messageName : m_database.messagesToGenerate)
    {
        string typeName(m_database.getMessageStructure(messageName));
        readAndMarkTypeAsNeededInIfs(typeName);
    }
}

void SackReader::saveDatabaseToFile(string const& path)
{
    m_database.saveDatabaseToFile(path);
}

void SackReader::loadDatabaseFromFile(string const& path)
{
    m_database.loadDatabaseFromFile(path);
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

void SackReader::generateLyxDocument(string const& ifsTemplatePath, string const& finalDocumentPath)
{
    LyxGenerator generator(m_database);
    generator.generateLyxDocument(ifsTemplatePath, finalDocumentPath);
}

void SackReader::readAndMarkTypeAsNeededInIfs(string const& typeName)
{
    if(!m_database.doesThisFullDetailedStructureExists(typeName) && !m_database.doesThisUnionExists(typeName) && !m_database.doesThisEnumExists(typeName))
    {
        readFileUsingTypeName(typeName);
    }
    if(m_database.doesThisStructureExists(typeName))
    {
        markStructureAsNeededForIfs(typeName);
    }
    else if(m_database.doesThisUnionExists(typeName))
    {
        markUnionAsNeededForIfs(typeName);
    }
    else if(m_database.doesThisEnumExists(typeName))
    {
        markEnumAsNeededForIfs(typeName);
    }
}

void SackReader::markStructureAsNeededForIfs(string const& structureName)
{
    m_database.structureNameToStructureDetailsMap[structureName].isUsedInIfs=true;
    StructureDetails structureDetails(m_database.getStructureDetails(structureName));
    for(string const& parameterName : structureDetails.parametersWithCorrectOrder)
    {
        ParameterDetails parameterDetails = m_database.getParameterDetails(structureName, parameterName);
        if(parameterDetails.isAnArray)
        {
            markConstantAsNeededForIfs(parameterDetails.arraySize);
        }
        readAndMarkTypeAsNeededInIfs(parameterDetails.type);
    }
}

void SackReader::markUnionAsNeededForIfs(string const& unionName)
{
    m_database.unionNameToUnionDetailsMap[unionName].isUsedInIfs=true;
    UnionDetails unionDetails(m_database.getUnionDetails(unionName));
    for(string const& parameterName : unionDetails.parametersWithCorrectOrder)
    {
        ParameterDetails parameterDetails = m_database.getUnionParameterDetails(unionName, parameterName);
        if(parameterDetails.isAnArray)
        {
            markConstantAsNeededForIfs(parameterDetails.arraySize);
        }
        readAndMarkTypeAsNeededInIfs(parameterDetails.type);
    }
}

void SackReader::markEnumAsNeededForIfs(string const& enumName)
{
    m_database.enumNameToEnumDetailsMap[enumName].isUsedInIfs=true;
}

void SackReader::markConstantAsNeededForIfs(string const& constantName)
{
    if(!constantName.empty())
    {
        char firstCharacter = constantName[0];
        if(firstCharacter!='E' && isCapitalLetter(firstCharacter))
        {
            m_database.constantNameToConstantDetailsMap[constantName].isUsedInIfs = true;
        }
    }
}

void SackReader::readOamTcomTupcMessageFiles()
{
    readFileUsingTypeFileName("MessageId_OamAtm.sig");
    readFileUsingTypeFileName("MessageId_OamTcom.sig");
    readFileUsingTypeFileName("MessageId_TassuTtm.sig");
    readFileUsingTypeFileName("MessageId_OamFault.h");
    readFileUsingTypeFileName("MessageId_Platform.h");
    readFileUsingTypeFileName("Oam_Atm.h");
    readFileUsingTypeFileName("oam_tcom.h");
    readFileUsingTypeFileName("Oam_Tcom_TestModelService.h");
    readFileUsingTypeFileName("Oam_Tcom_LoopTestService.h");
    readFileUsingTypeFileName("tassu_ttm.h");
    readFileUsingTypeFileName("SFaultInd.h");
    readFileUsingTypeFileName("SModeChangeReq.h");
    readFileUsingTypeFileName("SModeChangeResp.h");
}

void SackReader::readConstantFiles()
{
    readFileUsingTypeFileName("IfAaSysComGw_Defs.h");
    readFileUsingTypeFileName("DBtsomTcomConstants.h");
    readFileUsingTypeFileName("DOpenIUBCommonDefs.h");
    readFileUsingTypeFileName("Glo_bs.h");
    readFileUsingTypeFileName("DTechLogDef.h");
}

void SackReader::readFileUsingTypeName(string const& typeName)
{
    readFileUsingTypeFileName(typeName+".h");
}

void SackReader::readFileUsingTypeFileName(string const& typeFileName)
{
    SackFileReader sackFileReader(m_database);
    sackFileReader.readFile(m_database.getFileFullPath(typeFileName));
}



}
