#include "SackFileReaderStateMachine.hpp"

#include <String/AlbaStringHelper.hpp>

#include <Debug/AlbaDebug.hpp>

using namespace alba::stringHelper;
using namespace std;

namespace alba
{

namespace SackFileReaderStateMachineNamespace
{

InnerStates::InnerStates()
    : stateForConstant(StateForConstant::BeforeName)
    , stateForStruct(StateForStruct::BeforeName)
    , stateForStructAfterOpeningBraces(StateForStructAfterOpeningBraces::BeforeParameterType)
    , stateForEnum(StateForEnum::BeforeName)
    , stateForEnumAfterOpeningBraces(StateForEnumAfterOpeningBraces::BeforeEnumParameterName)
    , stateForAtDefDescription(StateForAtDefDescription::BeforeName)
    , stateForAtParamDescription(StateForAtParamDescription::BeforeName)
{}

void InnerStates::reset()
{
    stateForConstant = StateForConstant::BeforeName;
    stateForStruct = StateForStruct::BeforeName;
    stateForStructAfterOpeningBraces = StateForStructAfterOpeningBraces::BeforeParameterType;
    stateForEnum = StateForEnum::BeforeName;
    stateForEnumAfterOpeningBraces = StateForEnumAfterOpeningBraces::BeforeEnumParameterName;
    stateForAtDefDescription = StateForAtDefDescription::BeforeName;
    stateForAtParamDescription = StateForAtParamDescription::BeforeName;
}

SackFileReaderStateMachine::SackFileReaderStateMachine(Database & database)
    : BaseSackFileReaderStateMachine(State::Idle)
    , m_isMessageIdFile(false)
    , m_isNextLineNeeded(false)
    , m_database(database)
{}

bool SackFileReaderStateMachine::isNextLineNeeded() const
{
    return m_isNextLineNeeded;
}

bool SackFileReaderStateMachine::isMessageIdFile() const
{
    return m_isMessageIdFile;
}

void SackFileReaderStateMachine::setIsMessageIdFileFlag(bool const isMessageIdFile)
{
    m_isMessageIdFile = isMessageIdFile;
}

void SackFileReaderStateMachine::processInput(InputToken const& inputToken)
{
    m_isNextLineNeeded = false;
    switch(m_state)
    {
    case State::Idle:
        processStateIdle(inputToken);
        break;
    case State::EnumKeyword:
        processStateEnumKeyword(inputToken);
        break;
    case State::SharpDefineForConstant:
        processStateSharpDefineForConstant(inputToken);
        break;
    case State::SharpDefineForMessageId:
        processStateSharpDefineForMessageId(inputToken);
        break;
    case State::StructKeyword:
        processStateStructKeyword(inputToken);
        break;
    case State::AtDefDescription:
        processStateAtDefDescription(inputToken);
        break;
    case State::AtEnumDescription:
        processStateAtEnumDescription(inputToken);
        break;
    case State::AtParamDescription:
        processStateAtParamDescription(inputToken);
        break;
    case State::AtStructDescription:
        processStateAtStructDescription(inputToken);
        break;
    default:
        assert(false);
        break;
    }
}

void SackFileReaderStateMachine::processStateIdle(InputToken const& inputToken)
{
    //refactor this
    string const& token(inputToken.token);
    if(token == "#define" && inputToken.isNotInComment)
    {
        if(m_isMessageIdFile)
        {
            saveNextStateAndResetInnerStates(State::SharpDefineForMessageId);
        }
        else
        {
            saveNextStateAndResetInnerStates(State::SharpDefineForConstant);
        }
    }
    else if(token == "@def" && inputToken.isInMultilineComment)
    {
        saveNextStateAndResetInnerStates(State::AtDefDescription);
    }
    else if(token == "struct" && inputToken.isNotInComment)
    {
        saveNextStateAndResetInnerStates(State::StructKeyword);
    }
    else if(token == "@param" && inputToken.isInMultilineComment)
    {
        saveNextStateAndResetInnerStates(State::AtParamDescription);
    }
    else if(token == "@struct" && inputToken.isInMultilineComment)
    {
        saveNextStateAndResetInnerStates(State::AtStructDescription);
    }
    else if(token == "@enum" && inputToken.isInMultilineComment)
    {
        saveNextStateAndResetInnerStates(State::AtEnumDescription);
    }
    else if(token == "enum" && inputToken.isNotInComment)
    {
        saveNextStateAndResetInnerStates(State::EnumKeyword);
    }
}

void SackFileReaderStateMachine::processStateSharpDefineForConstant(InputToken const& inputToken)
{
    string const& token(inputToken.token);
    if(isNotWhiteSpaceAndNotInComment(inputToken))
    {
        if(StateForConstant::BeforeName == m_innerStates.stateForConstant)
        {
            m_commentDetails.name = token;
            m_innerStates.stateForConstant = StateForConstant::AfterNameBeforeValue;
        }
        else if(StateForConstant::AfterNameBeforeValue == m_innerStates.stateForConstant)
        {
            m_commentDetails.value = token;
            m_database.constantNameToConstantDetailsMap[m_commentDetails.name].name = m_commentDetails.name;
            m_database.constantNameToConstantDetailsMap[m_commentDetails.name].value = m_commentDetails.value;
            saveNextState(State::Idle);
        }
    }
}

void SackFileReaderStateMachine::processStateSharpDefineForMessageId(InputToken const& inputToken)
{
    string const& token(inputToken.token);
    if(isNotWhiteSpaceAndNotInComment(inputToken))
    {
        m_database.messageNameToStructureNameMap.emplace(token, getStringInBetweenTwoStrings(inputToken.line, "/* !- SIGNO(struct ", ") -! */"));
        m_isNextLineNeeded = true;
        saveNextState(State::Idle);
    }
}

void SackFileReaderStateMachine::processStateAtDefDescription(InputToken const& inputToken)
{
    static string partialString;
    string const& token(inputToken.token);
    if(token == "@def" || token == "Additional")
    {
        m_database.constantNameToConstantDetailsMap[m_commentDetails.name].name = m_commentDetails.name;
        m_database.constantNameToConstantDetailsMap[m_commentDetails.name].description = getStringWithoutRedundantWhiteSpace(partialString);
        partialString.clear();
        m_innerStates.stateForAtDefDescription = StateForAtDefDescription::BeforeName;
        if(token == "Additional")
        {
            saveNextState(State::Idle);
        }
    }
    else if(StateForAtDefDescription::BeforeName == m_innerStates.stateForAtDefDescription)
    {
        if(!isWhiteSpace(token))
        {
            m_commentDetails.name = token;
            m_innerStates.stateForAtDefDescription = StateForAtDefDescription::AfterNameBeforeColon;
        }
    }
    else if(StateForAtDefDescription::AfterNameBeforeColon == m_innerStates.stateForAtDefDescription)
    {
        if(":" == token)
        {
            partialString.clear();
            m_innerStates.stateForAtDefDescription = StateForAtDefDescription::AfterColon;
        }
    }
    else if(StateForAtDefDescription::AfterColon == m_innerStates.stateForAtDefDescription)
    {
        if("*" != token)
        {
            partialString+=token;
        }
    }
}

void SackFileReaderStateMachine::processStateStructKeyword(InputToken const& inputToken)
{
    static string partialString;
    string const& token(inputToken.token);
    if(isNotWhiteSpaceAndNotInComment(inputToken) && token!="/")
    {
        if(StateForStruct::BeforeName == m_innerStates.stateForStruct)
        {
            m_structureDetails.name = token;
            m_innerStates.stateForStruct=StateForStruct::AfterName;
        }
        else if(StateForStruct::AfterName == m_innerStates.stateForStruct)
        {
            if("{" == token)
            {
                m_innerStates.stateForStruct = StateForStruct::AfterOpeningBraces;
                m_innerStates.stateForStructAfterOpeningBraces = StateForStructAfterOpeningBraces::BeforeParameterType;
            }
            else if(";" == token)
            {
                m_structureDetails.clear();
                saveNextState(State::Idle);
            }
        }
        else if(StateForStruct::AfterOpeningBraces == m_innerStates.stateForStruct)
        {
            if("MESSAGEHEADER" == token)
            {
                m_database.structureNameToStructureDetailsMap[m_structureDetails.name].isMessage = true;
                m_isNextLineNeeded = true;
            }
            else if("}" == token)
            {
                m_previousStructureName=m_structureDetails.name;
                m_structureDetails.clear();
                saveNextState(State::Idle);
            }
            else if(";" == token)
            {
                m_innerStates.stateForStructAfterOpeningBraces = StateForStructAfterOpeningBraces::BeforeParameterType;
                if(!m_parameterDetails.name.empty())
                {
                    if(!m_database.doesThisStructureAndParameterExistsInVector(m_structureDetails.name, m_parameterDetails.name))
                    {
                        m_database.structureNameToStructureDetailsMap[m_structureDetails.name].parametersWithCorrectOrder.emplace_back(m_parameterDetails.name);
                    }
                    m_database.structureNameToStructureDetailsMap[m_structureDetails.name].parameters[m_parameterDetails.name].name = m_parameterDetails.name;
                    m_database.structureNameToStructureDetailsMap[m_structureDetails.name].parameters[m_parameterDetails.name].type = m_parameterDetails.type;
                    if(!m_arraySize.empty())
                    {
                        m_database.structureNameToStructureDetailsMap[m_structureDetails.name].parameters[m_parameterDetails.name].isAnArray = true;
                        m_database.structureNameToStructureDetailsMap[m_structureDetails.name].parameters[m_parameterDetails.name].arraySize = m_arraySize;
                        m_arraySize.clear();
                    }
                    m_parameterDetails.clear();
                }
            }
            else
            {
                if(StateForStructAfterOpeningBraces::BeforeParameterType == m_innerStates.stateForStructAfterOpeningBraces)
                {
                    m_parameterDetails.type = token;
                    m_innerStates.stateForStructAfterOpeningBraces = StateForStructAfterOpeningBraces::AfterParameterTypeBeforeParameterName;
                }
                else if(StateForStructAfterOpeningBraces::AfterParameterTypeBeforeParameterName == m_innerStates.stateForStructAfterOpeningBraces)
                {
                    m_parameterDetails.name = token;
                    m_innerStates.stateForStructAfterOpeningBraces = StateForStructAfterOpeningBraces::AfterParameterName;
                }
                else if(StateForStructAfterOpeningBraces::AfterParameterName == m_innerStates.stateForStructAfterOpeningBraces)
                {
                    if("[" == token)
                    {
                        m_innerStates.stateForStructAfterOpeningBraces = StateForStructAfterOpeningBraces::AfterOpeningBracket;
                    }
                }
                else if(StateForStructAfterOpeningBraces::AfterOpeningBracket == m_innerStates.stateForStructAfterOpeningBraces)
                {
                    if("]" == token)
                    {
                        m_arraySize = partialString;
                        partialString.clear();
                        m_innerStates.stateForStructAfterOpeningBraces = StateForStructAfterOpeningBraces::AfterClosingBracket;
                    }
                    else
                    {
                        partialString += token;
                    }
                }
            }
        }
    }
}

void SackFileReaderStateMachine::processStateAtParamDescription(InputToken const& inputToken)
{
    static string partialString;
    string const& token(inputToken.token);
    if(token == "@param" || token == "Additional")
    {
        if(ParameterDescriptionType::Structure == m_parameterDescriptionType)
        {
            if(m_database.doesThisStructureAndParameterExists(m_previousStructureName, m_parameterDetails.name))
            {
                m_database.structureNameToStructureDetailsMap[m_previousStructureName].parameters[m_parameterDetails.name].description = getStringWithoutRedundantWhiteSpace(partialString);
            }
        }
        else if(ParameterDescriptionType::Enum == m_parameterDescriptionType)
        {
            if(m_database.doesThisEnumAndParameterExists(m_previousEnumName, m_parameterDetails.name))
            {
                m_database.enumNameToEnumDetailsMap[m_previousEnumName].parameters[m_parameterDetails.name].description = getStringWithoutRedundantWhiteSpace(partialString);
            }
            string anotherParameterName = m_previousEnumName+"_"+m_parameterDetails.name;
            if(m_database.doesThisEnumAndParameterExists(m_previousEnumName, anotherParameterName))
            {
                m_database.enumNameToEnumDetailsMap[m_previousEnumName].parameters[anotherParameterName].description = getStringWithoutRedundantWhiteSpace(partialString);
            }
        }

        partialString.clear();
        m_innerStates.stateForAtParamDescription = StateForAtParamDescription::BeforeName;
        if(token == "Additional")
        {
            m_parameterDescriptionType = ParameterDescriptionType::None;
            saveNextState(State::Idle);
        }
    }
    else if(StateForAtParamDescription::BeforeName == m_innerStates.stateForAtParamDescription)
    {
        if(!isWhiteSpace(token))
        {
            m_parameterDetails.name = token;
            m_innerStates.stateForAtParamDescription = StateForAtParamDescription::AfterNameBeforeColon;
        }
    }
    else if(StateForAtParamDescription::AfterNameBeforeColon == m_innerStates.stateForAtParamDescription)
    {
        if(":" == token)
        {
            m_innerStates.stateForAtParamDescription = StateForAtParamDescription::AfterColon;
            partialString.clear();
        }
    }
    else if(StateForAtParamDescription::AfterColon == m_innerStates.stateForAtParamDescription)
    {
        if("*" != token)
        {
            partialString+=token;
        }
    }
}

void SackFileReaderStateMachine::processStateAtStructDescription(InputToken const& inputToken)
{
    string const& token(inputToken.token);
    if(!isWhiteSpace(token) && inputToken.isInMultilineComment)
    {
        m_previousStructureName = token;
        m_parameterDescriptionType = ParameterDescriptionType::Structure;
        saveNextState(State::Idle);
    }
}

void SackFileReaderStateMachine::processStateAtEnumDescription(InputToken const& inputToken)
{
    string const& token(inputToken.token);
    if(!isWhiteSpace(token) && inputToken.isInMultilineComment)
    {
        m_previousEnumName = token;
        m_parameterDescriptionType = ParameterDescriptionType::Enum;
        saveNextState(State::Idle);
    }
}

void SackFileReaderStateMachine::processStateEnumKeyword(InputToken const& inputToken)
{
    string const& token(inputToken.token);
    if(isNotWhiteSpaceAndNotInComment(inputToken) && token!="/")
    {
        if(StateForEnum::BeforeName == m_innerStates.stateForEnum)
        {
            m_enumDetails.name = token;
            m_innerStates.stateForEnum = StateForEnum::AfterName;
        }
        else if(StateForEnum::AfterName == m_innerStates.stateForEnum)
        {
            if("{" == token)
            {
                m_innerStates.stateForEnum = StateForEnum::AfterOpeningBraces;
            }
            else if(";" == token)
            {
                m_enumDetails.clear();
                saveNextState(State::Idle);
            }
        }
        else if(StateForEnum::AfterOpeningBraces == m_innerStates.stateForEnum)
        {
            if("}" == token || "," == token)
            {
                m_innerStates.stateForEnumAfterOpeningBraces = StateForEnumAfterOpeningBraces::BeforeEnumParameterName;
                if(!m_enumParameterDetails.name.empty())
                {
                    m_database.enumNameToEnumDetailsMap[m_enumDetails.name].parameters[m_enumParameterDetails.name].name = m_enumParameterDetails.name;
                    m_database.enumNameToEnumDetailsMap[m_enumDetails.name].parameters[m_enumParameterDetails.name].value = m_enumParameterDetails.value;
                    m_database.enumNameToEnumDetailsMap[m_enumDetails.name].parameters[m_enumParameterDetails.name].description = m_enumParameterDetails.description;
                    m_enumParameterDetails.clear();
                }
                if("}" == token)
                {
                    m_previousEnumName=m_enumDetails.name;
                    m_enumDetails.clear();
                    saveNextState(State::Idle);
                }
            }
            else
            {
                if(StateForEnumAfterOpeningBraces::BeforeEnumParameterName == m_innerStates.stateForEnumAfterOpeningBraces)
                {
                    m_enumParameterDetails.name = token;
                    m_innerStates.stateForEnumAfterOpeningBraces = StateForEnumAfterOpeningBraces::AfterEnumParameterNameBeforeEqualSymbol;
                }
                else if(StateForEnumAfterOpeningBraces::AfterEnumParameterNameBeforeEqualSymbol == m_innerStates.stateForEnumAfterOpeningBraces)
                {
                    if("=" == token)
                    {
                        m_innerStates.stateForEnumAfterOpeningBraces = StateForEnumAfterOpeningBraces::AfterEqualSymbolBeforeValue;
                    }
                }
                else if(StateForEnumAfterOpeningBraces::AfterEqualSymbolBeforeValue == m_innerStates.stateForEnumAfterOpeningBraces)
                {
                    m_enumParameterDetails.value = token;
                    m_innerStates.stateForEnumAfterOpeningBraces = StateForEnumAfterOpeningBraces::AfterValue;
                }
            }
        }
    }
}

void SackFileReaderStateMachine::saveNextStateAndResetInnerStates(State const& state)
{
    m_innerStates.reset();
    saveNextState(state);
}


bool SackFileReaderStateMachine::isNotWhiteSpaceAndNotInComment(InputToken const& inputToken) const
{
    return !isWhiteSpace(inputToken.token) && inputToken.isNotInComment;
}

}


}//namespace alba
