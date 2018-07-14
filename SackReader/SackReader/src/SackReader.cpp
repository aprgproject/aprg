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
    StructureDetails & structureDetailsSMessageAddress(m_database.structureNameToStructureDetailsMap["SMessageAddress"]);
    structureDetailsSMessageAddress.name = "SMessageAddress";
    structureDetailsSMessageAddress.isMessage = false;
    structureDetailsSMessageAddress.isUsedInIfs = true;
    structureDetailsSMessageAddress.parametersWithCorrectOrder.clear();
    structureDetailsSMessageAddress.parametersWithCorrectOrder.emplace_back("board");
    structureDetailsSMessageAddress.parametersWithCorrectOrder.emplace_back("cpu");
    structureDetailsSMessageAddress.parametersWithCorrectOrder.emplace_back("task");
    structureDetailsSMessageAddress.parameters["board"].name = "board";
    structureDetailsSMessageAddress.parameters["board"].type = "TBoard";
    structureDetailsSMessageAddress.parameters["board"].isAnArray = false;
    structureDetailsSMessageAddress.parameters["board"].descriptionFromUser = "Board in SMessageAddress";
    structureDetailsSMessageAddress.parameters["cpu"].name = "cpu";
    structureDetailsSMessageAddress.parameters["cpu"].type = "TCpu";
    structureDetailsSMessageAddress.parameters["cpu"].isAnArray = false;
    structureDetailsSMessageAddress.parameters["cpu"].descriptionFromUser = "Cpu in SMessageAddress";
    structureDetailsSMessageAddress.parameters["task"].name = "task";
    structureDetailsSMessageAddress.parameters["task"].type = "TTask";
    structureDetailsSMessageAddress.parameters["task"].isAnArray = false;
    structureDetailsSMessageAddress.parameters["task"].descriptionFromUser = "Task in SMessageAddress";
    /*performHackPrimitiveType("u8");
    performHackPrimitiveType("u16");
    performHackPrimitiveType("u32");
    performHackPrimitiveType("i8");
    performHackPrimitiveType("i16");
    performHackPrimitiveType("i32");
    performHackPrimitiveType("r32");
    performHackPrimitiveType("r64");
    performHackPrimitiveType("r128");*/
    m_database.constantNameToConstantDetailsMap["MAX_NUM_OF_HSPA_SCHEDULERS"].value = "16";
}

void SackReader::performHackPrimitiveType(string const& primitiveType)
{
    m_database.typedefNameToTypedefDetailsMap[primitiveType].name = primitiveType;
    m_database.typedefNameToTypedefDetailsMap[primitiveType].typedefDerivedName = primitiveType;
}

void SackReader::generateLyxDocument(string const& ifsTemplatePath, string const& finalDocumentPath)
{
    LyxGenerator generator(m_database);
    generator.generateLyxDocument(ifsTemplatePath, finalDocumentPath);
}

void SackReader::readAndMarkTypeAsNeededInIfs(string const& typeName)
{
    if(!m_database.doesThisFullDetailedStructureExists(typeName) &&
            !m_database.doesThisUnionExists(typeName) &&
            !m_database.doesThisEnumExists(typeName) &&
            !m_database.doesThisTypedefExists(typeName))
    {
        readFileUsingTypeName(typeName);
    }
    markStructureAsNeededForIfs(typeName);
    markUnionAsNeededForIfs(typeName);
    markEnumAsNeededForIfs(typeName);
    markTypedefAsNeededForIfs(typeName);
}

void SackReader::markStructureAsNeededForIfs(string const& structureName)
{
    if(m_database.doesThisStructureExists(structureName))
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
}

void SackReader::markUnionAsNeededForIfs(string const& unionName)
{
    if(m_database.doesThisUnionExists(unionName))
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
}

void SackReader::markEnumAsNeededForIfs(string const& enumName)
{
    if(m_database.doesThisEnumExists(enumName))
    {
        m_database.enumNameToEnumDetailsMap[enumName].isUsedInIfs=true;
        EnumDetails::ParameterMap const& parameters(m_database.enumNameToEnumDetailsMap[enumName].parameters);
        for(EnumDetails::ParameterPair pair : parameters)
        {
            markConstantAsNeededForIfs(pair.second.value);
        }
    }
}

void SackReader::markTypedefAsNeededForIfs(string const& typedefName)
{
    if(m_database.doesThisTypedefExists(typedefName))
    {
        m_database.typedefNameToTypedefDetailsMap[typedefName].isUsedInIfs=true;
    }
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
    readFileUsingTypeFileName("DFromTc_dsp.h");
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
