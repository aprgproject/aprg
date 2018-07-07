#pragma once

#include <CommonTypes.hpp>
#include <Database.hpp>
#include <State/AlbaBaseStateMachine.hpp>

namespace alba
{

namespace SackFileReaderStateMachineNamespace
{

enum class State
{
    Idle,
    SharpDefineForConstant,
    SharpDefineForMessageId,
    AtDefDescription,
    StructKeyword,
    AtParamDescription,
    AtStructDescription,
    AtEnumDescription,
    EnumKeyword
};

//#define MAX_NR_OF_CODES 2                /* 3GPP 10 Nokia 2*/
enum class StateForConstant
{
    BeforeName,
    AfterNameBeforeValue
};

//@def MAX_NR_OF_CODES :                  3GPP 10 Nokia 2.
enum class StateForAtDefDescription
{
    BeforeName,
    AfterNameBeforeColon,
    AfterColon
};

/*
struct SWamUnit
{
    TBoard                    logUnitAddr;
    TCpu                      cpuAddr;
    u8                        pad1;
    u8                        numOfFspUnits;
    EControlUnitType          unitType;
    EAvailability             isUnitAvailable;
    EMcuSwDeployment          swDeployment;
};
typedef struct SWamUnit SWamUnit;
*/
enum class StateForStruct
{
    BeforeName,
    AfterName,
    AfterOpeningBraces,
};

enum class StateForStructAfterOpeningBraces
{
    BeforeParameterType,
    AfterParameterTypeBeforeParameterName,
    AfterParameterName,
    AfterOpeningBracket,
    AfterClosingBracket
};

//@param logUnitAddr                : logical unit address (e.g. WAM10)
enum class StateForAtParamDescription
{
    BeforeName,
    AfterNameBeforeColon,
    AfterColon
};

/*
typedef enum EHspaMapping
{
    EHspaMapping_EmptyValue            = 0,
    EHspaMapping_Fsm1                  = 1,
    EHspaMapping_Fsm2                  = 2,
    EHspaMapping_Subrack1              = 3,
    EHspaMapping_SubrackUltra          = 4
} EHspaMapping;
 */
enum class StateForEnum
{
    BeforeName,
    AfterName,
    AfterOpeningBraces,
};

enum class StateForEnumAfterOpeningBraces
{
    BeforeEnumParameterName,
    AfterEnumParameterNameBeforeEqualSymbol,
    AfterEqualSymbolBeforeValue,
    AfterValue
};


enum class ParameterDescriptionType
{
    None,
    Structure,
    Enum
};


struct InputToken
{
    bool isInMultilineComment;
    bool isNotInComment;
    std::string token;
    std::string line;
};

struct InnerStates
{
    InnerStates();
    void reset();
    StateForConstant stateForConstant;
    StateForStruct stateForStruct;
    StateForStructAfterOpeningBraces stateForStructAfterOpeningBraces;
    StateForEnum stateForEnum;
    StateForEnumAfterOpeningBraces stateForEnumAfterOpeningBraces;
    StateForAtDefDescription stateForAtDefDescription;
    StateForAtParamDescription stateForAtParamDescription;
};

using BaseSackFileReaderStateMachine = AlbaBaseStateMachine<State, InputToken>;
class SackFileReaderStateMachine : public BaseSackFileReaderStateMachine
{
public:
    SackFileReaderStateMachine(Database & database);
    bool isNextLineNeeded() const;
    bool isMessageIdFile() const;
    void setIsMessageIdFileFlag(bool const isMessageIdFile);

    void processInput(InputToken const& inputToken);
private:
    void processStateIdle(InputToken const& inputToken);
    void processStateSharpDefineForConstant(InputToken const& inputToken);
    void processStateSharpDefineForMessageId(InputToken const& inputToken);
    void processStateAtDefDescription(InputToken const& inputToken);
    void processStateStructKeyword(InputToken const& inputToken);
    void processStateAtParamDescription(InputToken const& inputToken);
    void processStateAtStructDescription(InputToken const& inputToken);
    void processStateAtEnumDescription(InputToken const& inputToken);
    void processStateEnumKeyword(InputToken const& inputToken);
    void saveNextStateAndResetInnerStates(State const& state);
    bool isNotWhiteSpaceAndNotInComment(InputToken const& inputToken) const;
    bool m_isMessageIdFile;
    bool m_isNextLineNeeded;
    InnerStates m_innerStates;
    ConstantDetails m_commentDetails;
    StructureDetails m_structureDetails;
    ParameterDetails m_parameterDetails;
    EnumDetails m_enumDetails;
    EnumParameterDetails m_enumParameterDetails;
    std::string m_arraySize;
    std::string m_previousStructureName;
    std::string m_previousEnumName;
    ParameterDescriptionType m_parameterDescriptionType;
    Database & m_database;
};

}

}//namespace alba
