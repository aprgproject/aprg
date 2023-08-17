/** @file
 *  @brief R&D flags definitions for CCS domain
 *
 *  $HeadURL$
 *  $LastChangedRevision$
 *  $LastChangedDate$
 *  $Author$
 *  $Copyright: Copyright 2018 Nokia. All right reserved.$
 */
#ifndef _ERAD_CCS_H_
#define _ERAD_CCS_H_

#include <CcsCommon.h>
#include <ERadSwDomain.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
    INSTRUCTIONS FOR ADDING NEW R&D PARAMETER DESCRIPTION

    This file contains rad definitions with assigned doxygen and meta descriptions.
    The developer who is about to add new R&D parameter to this file is obligated
    to prepare short brief about the new R&D parameter and meta description as well.
    The meaning of each meta-description item has been explained below together
    with available options.

    modificationProperty - this item specifies the way in which the R&D parameter value is changed

    available options:

    - "changed by target"        - means that value is changed by SW components running on BTS,
    - "change on initialization" - means that value is changed only during initialization of BTS,
    - "change dynamically"       - means that value can be dynamically changed during a BTS life time,
    - "change on certain event"  - means that value can be changed only in case of specified event occurrence,
    - "no change"                - means that value is constant.

    ---

    typeOfParameterDefinition - this item specifies the type of R&D parameter

    available options:

    - "u32",
    - "boolean".

    ---

    minimumRADvalue - this item specifies the lower boundary of R&D parameter value

    available options:

    - value from range of <0, max(u32)> which specifies the boundary.

    ---

    maximumRADvalue - this item specifies the upper boundary of R&D parameter value

    available options:

    - value from range of <minimumRADvalue, max(u32)> which specifies the boundary.

    ---

    rangeRestriction - this item specifies if range restriction is applied to given R&D parameter

    available options:

    - "0" - no range restrictions,
    - "1" - range restriction present, minimum and maximum value defined by minimumRADvalue and maximumRADvalue.

    ---

    defaultValue - this item specifies default value of R&D parameter

    available options:

    - value from range of <minimumRADvalue, maximumRADvalue> value which specifies the default value.

    ---

   unit - this item specifies the unit of R&D parameter

    available options:

    - "ms",
    - "us",
    - "bytes",
    - "seconds",
    - "boolean",
    - "percents",
    - "index",
    - "bitmask",
    - "amount",
    - "lines",
    - "kilobytes",
    - "n/a".

    ---

    TypeOfEffect - this item specifies the role of selected R&D parameter.

    available options:

    - "target SW behaviour"  - means that R&D parameter is used to change settings affect on BTS behaviour,
    - "target accessability" - means that R&D parameter is used to enable/disable security options,
    - "loggin manipulation"  - means that R&D parameter is used to enable/disable logging/tracing functionalities,
    - "resource management"  - means that R&D parameter is used to enable/disable resources,
    - "feature enabling"     - means that R&D parameter is used to enable/disable certain features in an ad-hoc manner,
    - "status"               - means that R&D parameter is used to share an information about status of some functionality.

    ---

    shortDescription - this item specifies short description of R&D parameter

    available options:

    - any text describing R&D parameter behavior.

    ---

    R&D PARAMETER DESCRIPTION BLOCK SYNTAX:

    [modificationProperty=value][typeOfParameterDefinition=value][minimumRADvalue=value][maximumRADvalue=value][rangeRestriction=value][defaultValue=value][unit=value][TypeOfEffect=value][shortDescription=value]

    where the "value" is the option selected for each item.


**/

/************************** DOXYGEN GROUPS ************************************/

/**
 *  @defgroup dgRadCcs            CCS R&D parameters
 *
 *  Defines CC&S R&D parameters.
 *
 *  For detailed description of service specific parameters please refer to the according API Spec: <a href="https://sharenet-ims.inside.nokiasiemensnetworks.com/Open/396832787">https://sharenet-ims.inside.nokiasiemensnetworks.com/Open/396832787</a>
 *
 */
/*@{*/

/*!
 *  @brief  Macro combines domain and CC&S R&D parameters.
 */
#define RAD_CCS(value) RAD_SW_DOMAIN(ERadSwDomain_Ccs, value)

/************************** PUBLIC DECLARATIONS *********************************/



/*!
 *  @brief  CC&S R&D parameters.
 */
enum ERadCcs
{
    ERadCcs_PrintAaSysCom                 = RAD_CCS(0x0000),  /**< System Internal Communication debug print */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=System Internal Communication debug print] */

    ERadCcs_PrintAaSysLog                 = RAD_CCS(0x0001),  /**< System Logging debug print */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=System Logging debug print] */

    ERadCcs_PrintAaSysTime                = RAD_CCS(0x0002),  /**< System Time Service debug print */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=System Time Service debug print] */

    ERadCcs_PrintAaMem                    = RAD_CCS(0x0003),  /**< Dynamic Memory Management debug print */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=Dynamic Memory Management debug print] */

    ERadCcs_PrintAaPro                    = RAD_CCS(0x0004),  /**< Processs Management debug print */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=Processs Management debug print] */

    ERadCcs_PrintAaSem                    = RAD_CCS(0x0005),  /**< Semaphore Management debug print */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=Semaphore Management debug print] */

    ERadCcs_PrintAaStartup                = RAD_CCS(0x0006),  /**< Startup Service debug print */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=Startup Service debug print] */

    ERadCcs_PrintAaFile                   = RAD_CCS(0x0007),  /**< File Management debug print */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=File Management debug print] */

    ERadCcs_PrintAaUdpcpGen               = RAD_CCS(0x0008),  /**< UDPCP */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=UDPCP Gen debug prints] */

    ERadCcs_PrintAaUdpcpTx                = RAD_CCS(0x0009),  /**< UDPCP */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=UDPCP Tx debug prints] */

    ERadCcs_PrintAaUdpcpRx                = RAD_CCS(0x000A),  /**< UDPCP */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=UDPCP Rx debug prints] */

    ERadCcs_PrintAaMemAdapter             = RAD_CCS(0x000B),  /**< AaMemAdapter debug print */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=AaMemAdapter debug print] */

    ERadCcs_PrintAaSysComGw               = RAD_CCS(0x000C),  /**< SysCom Gw */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=SysCom Gw debug prints] */

    ERadCcs_AaMemAdapterMasterEnable      = RAD_CCS(0x000D),  /**< NOT IN USE ANYMORE! */
    /* [modificationProperty=deprecated][typeOfParameterDefinition=][minimumRADvalue=][maximumRADvalue=][rangeRestriction=][defaultValue=][unit=][TypeOfEffect=][shortDescription=NOT IN USE ANYMORE!] */

    ERadCcs_AaMemAdapterRtTrace           = RAD_CCS(0x000E),  /**< Genaral enabling for runtime tracing: 0 = disabled, 1 = enabled, 0xFFFFFFFF = transparent (for config tag) */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=4294967295][unit=n/a][TypeOfEffect=logging manipulation][shortDescription=General enabling for runtime tracing, 0 - off, 1 - on, (u32)-1 - transparent] */

    ERadCcs_AaMemAdapterRtObs             = RAD_CCS(0x000F),  /**< NOT IN USE ANYMORE! */
    /* [modificationProperty=deprecated][typeOfParameterDefinition=][minimumRADvalue=][maximumRADvalue=][rangeRestriction=][defaultValue=][unit=][TypeOfEffect=][shortDescription=NOT IN USE ANYMORE!] */


    ERadCcs_AaMemAdapterRtTraceTmo        = RAD_CCS(0x0010),  /**< NOT IN USE ANYMORE! */
    /* [modificationProperty=deprecated][typeOfParameterDefinition=][minimumRADvalue=][maximumRADvalue=][rangeRestriction=][defaultValue=][unit=][TypeOfEffect=][shortDescription=NOT IN USE ANYMORE!] */

    ERadCcs_AaMemAdapterRtObsTmo          = RAD_CCS(0x0011),  /**< NOT IN USE ANYMORE! */
    /* [modificationProperty=deprecated][typeOfParameterDefinition=][minimumRADvalue=][maximumRADvalue=][rangeRestriction=][defaultValue=][unit=][TypeOfEffect=][shortDescription=NOT IN USE ANYMORE!] */

    ERadCcs_AaMemAdapterListenerDisable   = RAD_CCS(0x0012),  /**< NOT IN USE ANYMORE! */
    /* [modificationProperty=deprecated][typeOfParameterDefinition=][minimumRADvalue=][maximumRADvalue=][rangeRestriction=][defaultValue=][unit=][TypeOfEffect=][shortDescription=NOT IN USE ANYMORE!] */

    ERadCcs_PrintAaProdTest               = RAD_CCS(0x0013),  /**< @deprecated NOT IN USE ANYMORE! */
    /* [modificationProperty=deprecated][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=NOT IN USE ANYMORE!] */

    ERadCcs_PrintAaProdTestCBist          = RAD_CCS(0x0014),  /**< @deprecated NOT IN USE ANYMORE! */
    /* [modificationProperty=deprecated][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=NOT IN USE ANYMORE!] */

    ERadCcs_AaProdTestEnable              = RAD_CCS(0x0015),  /**< @deprecated NOT IN USE ANYMORE! */
    /* [modificationProperty=deprecated][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=feature enabling][shortDescription=NOT IN USE ANYMORE!] */

    ERadCcs_PrintAaSysMb                  = RAD_CCS(0x0016),  /**< System Message Broker debug print */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=System Message Broker debug print] */

    ERadCcs_PrintAaConfigRaDSlave         = RAD_CCS(0x0017),  /**< Rad parameter Slave debug print */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=Rad parameter Slave debug print] */

    ERadCcs_PrintAaConfigRaDMaster        = RAD_CCS(0x0018),  /**< Rad parameter Master debug print */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=Rad parameter Master debug print] */

    ERadCcs_PrintAaConfigRad              = RAD_CCS(0x0019),  /**< Rad parameter general debug print */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=Rad parameter general debug print] */

    ERadCcs_PrintAaConfigTag              = RAD_CCS(0x001A),  /**< AaConfig Tag debug print */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=AaConfig Tag debug print] */

    ERadCcs_PrintAaPostmortem             = RAD_CCS(0x001B),  /**< Postmortem debug print */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=Postmortem debug print] */

    ERadCcs_PrintAaTrbl                   = RAD_CCS(0x001C),  /**< AaTrbl debug print */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=AaTrbl debug print] */

    ERadCcs_PrintAaError                  = RAD_CCS(0x001D),  /**< AaError debug print */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=AaError debug print] */

    ERadCcs_PrintAaTrblTechLogMasterEmu   = RAD_CCS(0x001E),  /**< AaTrbl Technical Log Master Eumlator debug print */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=AaTrbl Technical Log Master Eumlator debug print] */

    ERadCcs_AaMemAdapterPoolLimitThold    = RAD_CCS(0x001F),  /**< AaMemAdapter pool runtime utilization limit threshold value in percents */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=100][rangeRestriction=][defaultValue=0][unit=percents][TypeOfEffect=target SW behaviousr change][shortDescription=AaMemAdapter pool runtime utilization limit threshold value in percents] */


    ERadCcs_AaMemAdapterPoolLimitTmo      = RAD_CCS(0x0020),  /**< AaMemAdapter pool runtime utilization limit check enabling: 0 = Disabled, Other value = Value of check timeout in seconds */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=0][unit=seconds][TypeOfEffect=target SW behaviousr change][shortDescription=AaMemAdapter pool runtime utilization limit check enabling] */

    ERadCcs_AaMemAdapterPoolStatsTmo      = RAD_CCS(0x0021),  /**< AaMemAdapter pool runtime printing enabling: 0 = Disabled, Other value = Value of printing timeout in seconds */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=0][unit=seconds][TypeOfEffect=logging manipulation][shortDescription=AaMemAdapter pool runtime printing enabling] */

    ERadCcs_AaMemAdapterPoolTraceTmo      = RAD_CCS(0x0022),  /**< AaMemAdapter pool trace timeout in secs */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=0][unit=seconds][TypeOfEffect=logging manipulation][shortDescription=AaMemAdapter pool trace timeout in secs] */

    ERadCcs_PrintAaTrace                  = RAD_CCS(0x0023),  /**< AaTrace debug print */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=AaTrace debug print] */

    ERadCcs_PrintAaTestPort               = RAD_CCS(0x0024),  /**< AaTestPort debug print */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=AaTestPort debug print] */

    ERadCcs_AaSysMbStoragePrinterEnable   = RAD_CCS(0x0025),  /**< Enable SysMb storage printer */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=target SW behaviousr change][shortDescription=Enable SysMb storage printer] */

    ERadCcs_PrintSchedulerTrace           = RAD_CCS(0x0026),  /**< NOT IN USE ANYMORE! */
    /* [modificationProperty=deprecated][typeOfParameterDefinition=][minimumRADvalue=][maximumRADvalue=][rangeRestriction=][defaultValue=][unit=][TypeOfEffect=][shortDescription=NOT IN USE ANYMORE!] */

    ERadCcs_PrintProcessTrace             = RAD_CCS(0x0027),  /**< NOT IN USE ANYMORE! */
    /* [modificationProperty=deprecated][typeOfParameterDefinition=][minimumRADvalue=][maximumRADvalue=][rangeRestriction=][defaultValue=][unit=][TypeOfEffect=][shortDescription=NOT IN USE ANYMORE!] */

    ERadCcs_PrintMessageTrace             = RAD_CCS(0x0028),  /**< NOT IN USE ANYMORE! */
    /* [modificationProperty=deprecated][typeOfParameterDefinition=][minimumRADvalue=][maximumRADvalue=][rangeRestriction=][defaultValue=][unit=][TypeOfEffect=][shortDescription=NOT IN USE ANYMORE!] */

    ERadCcs_PrintAaHTTP                   = RAD_CCS(0x0029),  /**< NOT IN USE ANYMORE! */
    /* [modificationProperty=deprecated][typeOfParameterDefinition=][minimumRADvalue=][maximumRADvalue=][rangeRestriction=][defaultValue=][unit=][TypeOfEffect=][shortDescription=NOT IN USE ANYMORE!] */

    ERadCcs_AaTraceSwConfUsed             = RAD_CCS(0x002A),  /**< AaTrace SwConfig used flag: 0 = not used, 1 = used, 2 = used only SwConfig (ignore BTSLog) */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=2][rangeRestriction=][defaultValue=0][unit=bytes][TypeOfEffect=logging manipulation][shortDescription=AaTrace SwConfig used flag] */

    ERadCcs_AaTraceSwConfId1              = RAD_CCS(0x002B),  /**< AaTrace message ID 1 */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=0][unit=bytes][TypeOfEffect=logging manipulation][shortDescription=AaTrace message ID 1] */

    ERadCcs_AaTraceSwConfId2              = RAD_CCS(0x002C),  /**< AaTrace message ID 2 */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=0][unit=bytes][TypeOfEffect=logging manipulation][shortDescription=AaTrace message ID 2] */

    ERadCcs_AaTraceSwConfId3              = RAD_CCS(0x002D),  /**< AaTrace message ID 3 */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=0][unit=bytes][TypeOfEffect=logging manipulation][shortDescription=AaTrace message ID 3] */

    ERadCcs_AaTraceSwConfId4              = RAD_CCS(0x002E),  /**< AaTrace message ID 4 */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=0][unit=bytes][TypeOfEffect=logging manipulation][shortDescription=AaTrace message ID 4] */

    ERadCcs_AaTraceSwConfRange1           = RAD_CCS(0x002F),  /**< AaTrace range between message IDs 1 and 2: 0 = no range, 1 range used */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=AaTrace range between message IDs 1 and 2] */


    ERadCcs_AaTraceSwConfRange2           = RAD_CCS(0x0030),  /**< AaTrace range between message IDs 3 and 4: 0 = no range, 1 range used */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=AaTrace range between message IDs 3 and 4] */

    ERadCcs_PrintAaSysComUser             = RAD_CCS(0x0031),  /**< SysCom user related debug prints */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=SysCom user related debug prints] */

    ERadCcs_PrintAaSysComLink             = RAD_CCS(0x0032),  /**< SysCom link related debug prints */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=SysCom link related debug prints] */

    ERadCcs_PrintAaSysComHop              = RAD_CCS(0x0033),  /**< SysCom hop related debug prints */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=SysCom hop related debug prints] */

    ERadCcs_PrintAaSysComGwRoute          = RAD_CCS(0x0034),  /**< SysCom Gw route debug prints */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=SysCom Gw route debug prints] */

    ERadCcs_PrintAaSysComRtm              = RAD_CCS(0x0035),  /**< SysCom RTM debug prints */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=SysCom RTM debug prints] */

    ERadCcs_PoolAnalyzerDisable           = RAD_CCS(0x0036),  /**< Pool analyzer disabling */
    /* [modificationProperty=deprecated][typeOfParameterDefinition=][minimumRADvalue=][maximumRADvalue=][rangeRestriction=][defaultValue=][unit=][TypeOfEffect=][shortDescription=NOT IN USE ANYMORE!] */

    ERadCcs_PrintAaSNTP                   = RAD_CCS(0x0037),  /**< AaSNTP debug print */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=AaSNTP debug print] */

    ERadCcs_PrintAaDHCP                   = RAD_CCS(0x0038),  /**< AaDHCP debug print */
    /* [modificationProperty=deprecated][typeOfParameterDefinition=][minimumRADvalue=][maximumRADvalue=][rangeRestriction=][defaultValue=][unit=][TypeOfEffect=][shortDescription=NOT IN USE ANYMORE!] */

    ERadCcs_PrintAaSysComControl          = RAD_CCS(0x0039),  /**< SysCom Control debug print */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=SysCom Control debug print] */

    ERadCcs_PrintAaSysComEndian4Divisible = RAD_CCS(0x003A),  /**< SysCom Endianness message divisible by 4 debug print */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=SysCom Endianness message divisible by 4 debug print] */

    ERadCcs_PrintAaSysTimeBcn             = RAD_CCS(0x003B),  /**< AaSysTime BCN Sync debug print */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=AaSysTime BCN Sync debug print] */

    ERadCcs_HeapAnalyzerDisable           = RAD_CCS(0x003C),  /**< Heap analyzer disabling */
    /* [modificationProperty=deprecated][typeOfParameterDefinition=][minimumRADvalue=][maximumRADvalue=][rangeRestriction=][defaultValue=][unit=][TypeOfEffect=][shortDescription=NOT IN USE ANYMORE!] */

    ERadCcs_PrintAaNet                    = RAD_CCS(0x003D),  /**< AaNet debug print */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=AaNet debug print] */

    ERadCcs_AaSysComKernelErrorDisable    = RAD_CCS(0x003E),  /**< Fatal kernel error for DSP AaSysCom disabling */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=target SW behaviour change][shortDescription=Fatal kernel error for DSP AaSysCom disabling] */

    ERadCcs_AaSysLogInputLevel            = RAD_CCS(0x003F),  /**< Prints stored to RAM (postmortem): 0 = disable 1 = debug 2 = info 3 = warning 4 = error 5 = vip 6 = disable */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=6][rangeRestriction=][defaultValue=4294967295][unit=n/a][TypeOfEffect=target SW behaviousr change][shortDescription=Prints stored to RAM (postmortem)] */


    ERadCcs_AaSysLogOutputLevel           = RAD_CCS(0x0040),  /**< Prints forwarded to output devices: 0 = disable 1 = debug 2 = info 3 = warning 4 = error 5 = vip 6 = disable */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=6][rangeRestriction=][defaultValue=4294967295][unit=n/a][TypeOfEffect=target SW behaviousr change][shortDescription=Prints forwarded to output devices] */

    ERadCcs_AaSysLogOutputMode            = RAD_CCS(0x0041),  /**< Output mode which devices prints are forwarded: 0 = none 1 = deprecated 2 = udp 3 = sic 4 = standard output 5 = local 6 = remote 7 = compressed local 8 = compressed remote 9 = not valid */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=7][rangeRestriction=][defaultValue=4294967295][unit=n/a][TypeOfEffect=target SW behaviousr change][shortDescription=Output mode which devices prints are forwarded] */

    ERadCcs_AaSysLogUdpAddress            = RAD_CCS(0x0042),  /**< IP address where prints are forwarded, broadcast and unicast are supported: A.B.C.D -> 0xAABBCCDD */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=0][unit=bytes][TypeOfEffect=target SW behaviousr change][shortDescription=IP address where prints are forwarded] */

    ERadCcs_AaSysLogUdpPort               = RAD_CCS(0x0043),  /**< IP port where prints are forwarded */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=65535][rangeRestriction=][defaultValue=4294967295][unit=bytes][TypeOfEffect=target SW behaviousr change][shortDescription=IP port where prints are forwarded] */

    ERadCcs_AaSysLogSicAddress            = RAD_CCS(0x0044),  /**< AaSysCom address where prints are forwarded for output mode 3 = sic */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=0][unit=bytes][TypeOfEffect=target SW behaviousr change][shortDescription=AaSysCom address where prints are forwarded for output mode 3] */

    ERadCcs_AaSysLogStartupLogSize        = RAD_CCS(0x0045),  /**< Maximum startup log size to be collected */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=4294967295][unit=bytes][TypeOfEffect=logging manipulation][shortDescription=Maximum startup log size to be collected] */

    ERadCcs_AaSysLogSnapshotFreezeDisable = RAD_CCS(0x0046),  /**< Disable runtime log snapshot freeze */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=Disable runtime log snapshot freeze] */

    ERadCcs_PrintAaProSched               = RAD_CCS(0x0047),  /**< Process scheduling trace debug print */
    /* [modificationProperty=deprecated][typeOfParameterDefinition=][minimumRADvalue=][maximumRADvalue=][rangeRestriction=][defaultValue=][unit=][TypeOfEffect=][shortDescription=NOT IN USE ANYMORE!] */

    ERadCcs_AaProSchedControl             = RAD_CCS(0x0048),  /**< Postmortem calltrace: -1 = disable, 0 = default by sw, 1 = enable, 2 >= take snaphot to system log with seconds internal */
    /* [modificationProperty=deprecated][typeOfParameterDefinition=][minimumRADvalue=][maximumRADvalue=][rangeRestriction=][defaultValue=][unit=][TypeOfEffect=][shortDescription=NOT IN USE ANYMORE!] */

    ERadCcs_PrintAaFileSicFtp             = RAD_CCS(0x0049),  /**< SicFtp trace: 0 = default by SW, 1 = enable */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=SicFtp trace] */

    ERadCcs_AaProLinuxRealtimeScheduling  = RAD_CCS(0x004A),  /**< AaPro: 0 = SCHED_OTHER, 1 = SCHED_FIFO  */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=bytes][TypeOfEffect=target SW behaviousr change][shortDescription=Scheduler algorithm] */

    ERadCcs_PrintAaLteTime                = RAD_CCS(0x004B),  /**< AaLteTime debug print */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=AaLteTime debug print] */

    ERadCcs_AaSysComRtmDisable            = RAD_CCS(0x004C),  /**< 1 = disable RTM, 0 = RTM is enabled */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=target SW behaviour change][shortDescription=Disable RTM] */

    ERadCcs_AaSysComRtmTimeout            = RAD_CCS(0x004D),  /**< timeout for RTM resendings, 0 = default value will be used, otherwise time in ms */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=0][unit=ms][TypeOfEffect=target SW behaviour change][shortDescription=Timeout for RTM resendings, 0 = default value will be used, otherwise time in ms] */

    ERadCcs_AaSysComRtmResendings         = RAD_CCS(0x004E),  /**< Amount for RTM resendings, 0 = default value will be used */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=0][unit=amount][TypeOfEffect=target SW behaviour change][shortDescription=Amount for RTM resendings, 0 = default value will be used, otherwise resending count] */

    ERadCcs_PrintAaRTOS                   = RAD_CCS(0x004F),  /**< RTOS-related debug print */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=RTOS-related debug print] */


    ERadCcs_AaProDisableSafetyMarginFeature        = RAD_CCS(0x0050),  /**< 0 = disable feature, 1 = enable feature */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=target SW behaviousr change][shortDescription=Safety margin feature] */

    ERadCcs_AaProVirtStacksizeOffset               = RAD_CCS(0x0051),  /**< if feature is enabled (see above), this offset will be added to user provided stacksize and actual stacksize setting on Linux takes place*/
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=0][unit=bytes][TypeOfEffect=target SW behaviousr change][shortDescription=this offset will be added to user provided stacksize and actual stacksize setting on Linux takes place] */

    ERadCcs_PrintAaShell                           = RAD_CCS(0x0052),  /**< AaShell debug print */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=AaShell debug print] */

    ERadCcs_PrintAaGpuXml                          = RAD_CCS(0x0053),  /**< AaGpuXml debug print */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=AaGpuXml debug print] */

    ERadCcs_AaMemAdapterValidateAllocMaxBlockCount = RAD_CCS(0x0054),  /**< AaMemAdapter: splits memory validation into parts with max number of blocks to be checked. */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=50000][unit=bytes][TypeOfEffect=target SW behaviousr change][shortDescription=AaMemAdapter: splits memory validation into parts with max number of blocks to be checked.] */

    ERadCcs_AaFileDefaultVolume                    = RAD_CCS(0x0055),  /**< 0 = don't use default volume, 1 = "/ram", 2 = "/rom", 3 = "/safe", 4 = "/ffs", 5 = "/ffs1", 6 = "/ffs2", 7 = "/ffs3", 8 = "/ffs4", 9 = "/rpram", 10 = "/logs", 11 = "/stb", 12 = "/pns", 13 = "/raml", 14 = "/data" */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=14][rangeRestriction=1][defaultValue=1][unit=index][TypeOfEffect=target SW behaviour change][shortDescription=default volume] */

    ERadCcs_PrintAaFileTftp                        = RAD_CCS(0x0056),  /**< Debug print for Tftp */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=Debug print for Tftp] */

    ERadCcs_AaSysComMsgRerouteEnable               = RAD_CCS(0x0057),  /**< 0 = do not allow internal message redirection to TestPC */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=routing manipulation][shortDescription=internal message redirection to TestPC] */

    ERadCcs_AaMemAdapterHeapTracingDelay           = RAD_CCS(0x0058),  /**< AaMemAdapter: Delay for heap tracing in seconds after startup: 0 = start without delay, 0xFFFFFFFF = disable heap tracing */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=0][unit=seconds][TypeOfEffect=logging manipulation][shortDescription=AaMemAdapter: Delay for heap tracing in seconds after startup] */

    ERadCcs_AaMemAdapterHeapTracingEnable          = RAD_CCS(0x0059),  /**< AaMemAdapter: General enabling for heap tracing: 0 = disabled, 1 = enabled, 0xFFFFFFFF = transparent (for config tag) */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=4294967295][unit=bytes][TypeOfEffect=logging manipulation][shortDescription=AaMemAdapter: General enabling for heap tracing] */

    ERadCcs_AaTraceTracingMode                     = RAD_CCS(0x005A),  /**< AaTrace tracing mode (SF_MONITORED flag), 0 = default mode, a message is monitored only once, 1 = trace always mode, a message is monitored in all tracing points */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=bytes][TypeOfEffect=logging manipulation][shortDescription=AaTrace tracing mode (SF_MONITORED flag)] */

    ERadCcs_AaUDPCPTxMessageResendTimeout          = RAD_CCS(0x005B),  /**< AaUDPCP message fragment resending timeout (value in ms) */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=0][unit=ms][TypeOfEffect=target SW behaviousr change][shortDescription=AaUDPCP message fragment resending timeout] */

    ERadCcs_AaUDPCPTxMessageResendRetries          = RAD_CCS(0x005C),  /**< AaUDPCP amount of retries to be tried in case of failure in transmission */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=0][unit=bytes][TypeOfEffect=target SW behaviousr change][shortDescription=AaUDPCP amount of retries] */

    ERadCcs_AaUDPCPAckMode                         = RAD_CCS(0x005D),  /**< AaUDPCP single acknowledge mode setting, 1 = single acknowledge mode not used, 2 = single acknowledge mode used */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=1][maximumRADvalue=2][rangeRestriction=][defaultValue=0][unit=bytes][TypeOfEffect=target SW behaviousr change][shortDescription=AaUDPCP single acknowledge mode setting] */

    ERadCcs_AaUDPCPCrcInUse                        = RAD_CCS(0x005E),  /**< AaUDPCP message CRC32 setting, 1 = CRC not used, 2 = CRC used */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=1][maximumRADvalue=2][rangeRestriction=][defaultValue=0][unit=bytes][TypeOfEffect=target SW behaviousr change][shortDescription=AaUDPCP message CRC32 setting] */

    ERadCcs_AaMemAdapterHeapTracingMode            = RAD_CCS(0x005F),  /**< AaMemAdapter: Heap tracing mode (relevant only for LINUX; ignored for OSE): 0 = heap tracing only for AaMem allocation, 1 = heap tracing for malloc, 2 = heap tracing for malloc to file, 0xFFFFFFFF = transparent (for config tag) */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=4294967295][unit=bytes][TypeOfEffect=logging manipulation][shortDescription=AaMemAdapter: Heap tracing mode] */


    ERadCcs_AaMemAdapterQuarantineListLength           = RAD_CCS(0x0060), /**< AaMemAdapter: length of quarantine list */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=0][unit=bytes][TypeOfEffect=target SW behaviousr change][shortDescription=AaMemAdapter: length of quarantine list] */

    ERadCcs_PrintAaSysComNotifList                     = RAD_CCS(0x0061), /**< SysCom notification list related debug prints */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=SysCom notification list related debug prints] */

    ERadCcs_AaSysComCommErrNotifyDisabled              = RAD_CCS(0x0062), /**< SysCom communication failure notification reporting: 0 = enabled, 1 = disabled */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=SysCom communication failure notification reporting] */

    ERadCcs_SwAppDefCheckDisable                       = RAD_CCS(0x0063), /**< 1 = disable AppDef.txt checking, 0 = AppDef.txt checking is enabled */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=target SW behaviour change][shortDescription=Used to enable or disable AppDef.txt presence check and recovery action] */

    ERadCcs_AaFileSicFtpServerTimeout                  = RAD_CCS(0x0064), /**< AaFile timeout value for SICFTP server */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=0][unit=seconds][TypeOfEffect=target SW behaviousr change][shortDescription=AaFile timeout value for SICFTP server] */

    ERadCcs_AaFileSicFtpClientTimeout                  = RAD_CCS(0x0065), /**< AaFile timeout value for SICFTP client */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=0][unit=seconds][TypeOfEffect=target SW behaviousr change][shortDescription=AaFile timeout value for SICFTP client] */

    ERadCcs_AaMemAdapterPermanentQuarantineListLength  = RAD_CCS(0x0066), /**< AaMemAdapter: 0: permanent quarantine behaviour disabled, otherwise: no. of elements in permanent quarantine list */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=0][unit=bytes][TypeOfEffect=target SW behaviousr change][shortDescription=no. of elements in permanent quarantine list] */

    ERadCcs_AaMemAdapterQuarantineListBlockSizeMin     = RAD_CCS(0x0067), /**< AaMemAdapter: 0: this tag is not considered, otherwise: minimal block size for blocks to be put to quarantine list */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=0][unit=bytes][TypeOfEffect=target SW behaviousr change][shortDescription=minimal block size for blocks to be put to quarantine list] */

    ERadCcs_AaMemAdapterQuarantineListBlockSizeMax     = RAD_CCS(0x0068), /**< AaMemAdapter: 0: this tag is not considered, otherwise: maximal block size for blocks to be put to quarantine list */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=0][unit=bytes][TypeOfEffect=target SW behaviousr change][shortDescription=maximal block size for blocks to be put to quarantine list] */

    ERadCcs_AaMemAdapterQuarantineListStopAtCorruption = RAD_CCS(0x0069), /**< AaMemAdapter: 0: no stop at detection of corruption, 1: stop at detection of corruption */
    /* [modificationProperty=deprecated][typeOfParameterDefinition=][minimumRADvalue=][maximumRADvalue=][rangeRestriction=][defaultValue=][unit=][TypeOfEffect=][shortDescription=NOT IN USE ANYMORE!] */

    ERadCcs_AaMemAdapterCallStackFrameSkipCount        = RAD_CCS(0x006A), /**< AaMemAdapter: defines the amount of callstack frames skipped from the top */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=0][unit=n/a][TypeOfEffect=logging manipulation][shortDescription=the number of callstack frames skipped from the top] */

    ERadCcs_AaMemAdapterCorruptedBlockDumpPreBytes     = RAD_CCS(0x006B), /**< defines amount of bytes printed before the corrupted block in the hex dump */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=0][unit=bytes][TypeOfEffect=logging manipulation][shortDescription=the number of bytes printed before the corrupted block in the hex dump] */

    ERadCcs_AaMemAdapterCorruptedBlockDumpPostBytes    = RAD_CCS(0x006C), /**< defines amount of bytes printed after the corrupted block in the hex dump */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=0][unit=bytes][TypeOfEffect=logging manipulation][shortDescription=the number of bytes printed after the corrupted block in the hex dump] */

    ERadCcs_AaTestPortNagleDisable                     = RAD_CCS(0x006D), /**< 0 = Nagle algorithm is enabled, 1 = disabled */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=feature enabling][shortDescription=Nagle algorithm disabled] */

    ERadCcs_AaFileTftpLookupTableSize                  = RAD_CCS(0x006E), /**< AaFileTftp: 0: default size 16 is used, otherwise: size of lookup table (size is related to max allowed no. of parallel TFTP tasks */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=0][unit=bytes][TypeOfEffect=target SW behaviousr change][shortDescription=AaFileTftp: size of lookup table] */

    ERadCcs_PrintAaConfigSvcReg                        = RAD_CCS(0x006F), /**< AaConfig Service Registry debug print */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=AaConfig Service Registry debug print] */


    ERadCcs_CCSDaemonWaitTime                     = RAD_CCS(0x0070), /**< Waiting time for sys.hwapi.online config tag to be set by Hwapi, flag value sets wait time in ms */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=0][unit=ms][TypeOfEffect=target SW behaviousr change][shortDescription=Waiting time for sys.hwapi.online config tag to be set by Hwapi] */

    ERadCcs_PrintCCSDaemon                        = RAD_CCS(0x0071), /**< Debug print for CCSDaemon */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=Debug print for CCSDaemon] */

    ERadCcs_PrintAaFileFtpClient                  = RAD_CCS(0x0072), /**< Debug print for Ftp Client */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=Debug print for Ftp Client] */

    ERadCcs_AaSysComStatistics                    = RAD_CCS(0x0073), /**< Enable AaSysCom statistics gathering */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=Enable AaSysCom statistics gathering] */

    ERadCcs_AaSysComGwStatistics                  = RAD_CCS(0x0074), /**< Enable AaSysComGw statistics gathering */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=Enable AaSysComGw statistics gathering] */

    ERadCcs_PrintAaSysComStats                    = RAD_CCS(0x0075), /**< SysCom statistics related debug prints */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=SysCom statistics related debug prints] */

    ERadCcs_PrintStatistics                       = RAD_CCS(0x0076), /**< Statistics related debug prints */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=Statistics related debug prints] */

    ERadCcs_AaProWDRebootDisable                  = RAD_CCS(0x0077), /**< 1 = disable system resets, 0 = system resets are enabled */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=target SW behaviousr change][shortDescription=Disable system resets] */

    ERadCcs_AaRTOSApiFatalExceptionDisable        = RAD_CCS(0x0078), /**< Raising a fatal exception in AaRTOSApi disabling */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=target SW behaviousr change][shortDescription=Raising a fatal exception in AaRTOSApi disabling] */

    ERadCcs_AaErrorCoreDump                       = RAD_CCS(0x0079), /**< CoreDump: 0 = disabled, >0 size of compressed core dump in kbytes */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=0][unit=bytes][TypeOfEffect=logging manipulation][shortDescription=CoreDump: disabled or size of core dump] */

    ERadCcs_AaProMemoryOverloadCoefficient        = RAD_CCS(0x007A), /**< Coefficient used in memory overload formula */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=1][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=60][unit=bytes][TypeOfEffect=target SW behaviousr change][shortDescription=Coefficient used in memory overload formula] */

    ERadCcs_AaSysLogPrintLinuxDbgLogs             = RAD_CCS(0x007B), /**< Linux logs debug print */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=Linux logs debug print] */

    ERadCcs_AaSysLogLinuxListener                 = RAD_CCS(0x007C), /**< Linux Logs: 1 = enable (default value), 0 = disable*/
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=1][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=Linux logs listener] */

    ERadCcs_PrintAaRTOSApi                        = RAD_CCS(0x007D), /**< AaRTOSApi debug print */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=AaRTOSApi debug print] */

    ERadCcs_AaMemAdapterHeapTracingPoolSize       = RAD_CCS(0x007E), /**< AaMemAdapter: size of heap tracing pool in bytes: 0 = default size is taken, otherwise size in bytes */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=0][unit=bytes][TypeOfEffect=resource management][shortDescription=size of heap tracing pool] */

    ERadCcs_AaMemAdapterHeapTracingCallStackDepth = RAD_CCS(0x007F), /**< AaMemAdapter: depth of callstack in heap trace dumps: 0 = default depth is taken, otherwise depth in frames */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=0][unit=n/a][TypeOfEffect=resource management][shortDescription=depth of callstack in heap trace dump frames] */


    ERadCcs_AaLteTimeSimDrvFrameMultiplier          = RAD_CCS(0x0080), /**< LteTime SimDrv SFN duration multiplier */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=1][unit=bytes][TypeOfEffect=target SW behaviousr change][shortDescription=LteTime SimDrv SFN duration multiplier] */

    ERadCcs_PrintAaSysComGwTcp                      = RAD_CCS(0x0081), /**< Debug print for AaSysCom GW TCP route */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=Debug print for AaSysCom GW TCP route] */

    ERadCcs_AaSysComGwKeepAliveDisable              = RAD_CCS(0x0082), /**< AaSysComGw TCP route: 0 keep alive is enabled, 1 disabled */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=target SW behaviousr change][shortDescription=AaSysComGw TCP route: keep alive] */

    ERadCcs_AaSysComGwKeepCnt                       = RAD_CCS(0x0083), /**< AaSysComGw TCP route: maximum number of keepalive probes, default 1 */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=0][unit=bytes][TypeOfEffect=target SW behaviousr change][shortDescription=AaSysComGw TCP route: maximum number of keepalive probes] */

    ERadCcs_AaSysComGwKeepIdle                      = RAD_CCS(0x0084), /**< AaSysComGw TCP route: connection idle time before sending keepalive probes, default 60 */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=0][unit=seconds][TypeOfEffect=target SW behaviousr change][shortDescription=AaSysComGw TCP route: connection idle time before sending keepalive probes] */

    ERadCcs_AaSysComGwKeepIntvl                     = RAD_CCS(0x0085), /**< AaSysComGw TCP route: time between keepalive probes, default 2 */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=0][unit=seconds][TypeOfEffect=target SW behaviousr change][shortDescription=AaSysComGw TCP route: time between keepalive probes] */

    ERadCcs_AaSysComGwNagleDisable                  = RAD_CCS(0x0086), /**< AaSysComGw TCP route: 0 Nagle algorithm is enabled, 1 disabled */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=feature enabling][shortDescription=AaSysComGw TCP route: Nagle algorithm disabled] */

    ERadCcs_AaSysComGwTcpBufferSize                 = RAD_CCS(0x0087), /**< AaSysComGw TCP route: buffer size (default and minimum 128k) */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=131072][rangeRestriction=][defaultValue=0][unit=bytes][TypeOfEffect=resource management][shortDescription=AaSysComGw TCP route: buffer size] */

    ERadCcs_AaSysComGwUdpRxBufferSize               = RAD_CCS(0x0088), /**< AaSysComGw UDP route: receive socket buffer size in bytes */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=5000][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=0][unit=bytes][TypeOfEffect=resource management][shortDescription=AaSysComGw UDP route: receive socket buffer size] */

    ERadCcs_AaSysComGwUdpTxBufferSize               = RAD_CCS(0x0089), /**< AaSysComGw UDP route: send socket buffer size in bytes */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=5000][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=0][unit=bytes][TypeOfEffect=resource management][shortDescription=AaSysComGw UDP route: send socket buffer size] */

    ERadCcs_AaProNumberOfCPUMeasurementsPerLogLine  = RAD_CCS(0x008A), /**< AaPro: Number of CPU measurements for one log line in syslog */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=1][maximumRADvalue=24][rangeRestriction=][defaultValue=12][unit=bytes][TypeOfEffect=logging manipulation][shortDescription=Number of CPU measurements for one log line in syslog] */

    ERadCcs_AaSysMbNodeListDelayTimeout             = RAD_CCS(0x008B), /**< AaSysMb node list publication delay in microseconds */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=0][unit=us][TypeOfEffect=target SW behaviousr change][shortDescription=AaSysMb node list publication delay] */

    ERadCcs_AaSysLogFeatureLogRingBuffer            = RAD_CCS(0x008C), /**< AaSysLog feature log ring buffer: 1 enabled, 0 disabled; default 1 */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=1][unit=boolean][TypeOfEffect=target SW behaviousr change][shortDescription=AaSysLog feature log ring buffer] */

    ERadCcs_AaSysLogFeatureLogRingBufferOutputLevel = RAD_CCS(0x008D), /**< AaSysLog feature log ring buffer enable dump on output: 1 enabled, 0 disabled; default: 0 */
    /* [modificationProperty=deprecated][typeOfParameterDefinition=][minimumRADvalue=][maximumRADvalue=][rangeRestriction=][defaultValue=][unit=][TypeOfEffect=][shortDescription=NOT IN USE ANYMORE!] */

    ERadCcs_AaSysTimeBaseDisable                    = RAD_CCS(0x008E), /**< AaSysTime deBASE - Disable BASE functionality 0 = BASE enabled, 1 = BASE disabled*/
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=1][unit=boolean][TypeOfEffect=target SW behaviour change][shortDescription=AaSysTime deBASE - Disable BASE functionality] */

    ERadCcs_AaSysLogRAMDeviceFileSize               = RAD_CCS(0x008F), /**< AaSysLog size of RAM device file */
    /* [modificationProperty=deprecated][typeOfParameterDefinition=][minimumRADvalue=][maximumRADvalue=][rangeRestriction=][defaultValue=][unit=][TypeOfEffect=][shortDescription=NOT IN USE ANYMORE!] */


    ERadCcs_AaTraceAggBufferSize             = RAD_CCS(0x0090),  /**< Maximum size of aggregated monitor indication message in bytes, range: [512, 64000], default 4kB */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=64000][rangeRestriction=][defaultValue=0][unit=bytes][TypeOfEffect=target SW behaviousr change][shortDescription=Maximum size of aggregated monitor indication message in bytes] */

    ERadCcs_AaTraceAggTimeout                = RAD_CCS(0x0091),  /**< AaTrace message aggregation timeout in milliseconds, range [20, 20000], default 200 ms */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=20000][rangeRestriction=][defaultValue=0][unit=bytes][TypeOfEffect=target SW behaviousr change][shortDescription=AaTrace message aggregation timeout in milliseconds] */

    ERadCcs_AaSysLogPrintTrswDbgLogs         = RAD_CCS(0x0092),  /**< TRSW Linux logs debug print */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=TRSW Linux logs debug print] */

    ERadCcs_AaSNTPToPdSupport                = RAD_CCS(0x0093),  /**< enable/disable AaSNTP ToPd support*/
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=1][unit=boolean][TypeOfEffect=feature enabling][shortDescription=enable AaSNTP ToPd support] */

    ERadCcs_AaSysLogQuotaCheckDisable        = RAD_CCS(0x0094),  /**< Global quota check durig SC buffer registration: 0 = enabled, 1 = disabled */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=target SW behaviousr change][shortDescription=Global quota check durig SC buffer registration] */

    ERadCcs_PrintAaSysDispatcher             = RAD_CCS(0x0095),  /**< System Dispatcher debug print */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=System Dispatcher debug print] */

    ERadCcs_AaLogCollectorDbgLogs            = RAD_CCS(0x0096),  /**< AaLogCollector debug print */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=AaLogCollector debug print] */

    ERadCcs_AaLogCollectorFileSize           = RAD_CCS(0x0097),  /**< Maximum size of AaLogCollector log file */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=10485760][unit=bytes][TypeOfEffect=target SW behaviousr change][shortDescription=Maximum size of AaLogCollector log file] */

    ERadCcs_AaLogCollectorCompressionDisable = RAD_CCS(0x0098),  /**< Disable log files compression in AaLogCollector */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=target SW behaviousr change][shortDescription=Disable log files compression in AaLogCollector] */

    ERadCcs_AaSysLogRemoteServerMode         = RAD_CCS(0x0099),  /**< 0 - disabled; 1 - NSN format; 2 - RFC format */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=2][rangeRestriction=][defaultValue=0][unit=bytes][TypeOfEffect=logging manipulation][shortDescription=NSN or RFC format] */

    ERadCcs_AaSysLogRemoteSyslogAddress      = RAD_CCS(0x009A),  /**< @deprecated NOT IN USE ANYMORE!*/
    /* [modificationProperty=deprecated][typeOfParameterDefinition=][minimumRADvalue=][maximumRADvalue=][rangeRestriction=][defaultValue=][unit=][TypeOfEffect=][shortDescription=NOT IN USE ANYMORE!] */

    ERadCcs_AaSysLogRemoteSyslogPort         = RAD_CCS(0x009B),  /**< @deprecated NOT IN USE ANYMORE! */
    /* [modificationProperty=deprecated][typeOfParameterDefinition=][minimumRADvalue=][maximumRADvalue=][rangeRestriction=][defaultValue=][unit=][TypeOfEffect=][shortDescription=NOT IN USE ANYMORE!] */

    ERadCcs_AaSysLogRemoteMrBtsId            = RAD_CCS(0x009C),  /**< @deprecated NOT IN USE ANYMORE! */
    /* [modificationProperty=deprecated][typeOfParameterDefinition=][minimumRADvalue=][maximumRADvalue=][rangeRestriction=][defaultValue=][unit=][TypeOfEffect=][shortDescription=NOT IN USE ANYMORE!] */

    ERadCcs_AaSysLogRemoteBtsIpAddress       = RAD_CCS(0x009D),  /**< @deprecated NOT IN USE ANYMORE! */
    /* [modificationProperty=deprecated][typeOfParameterDefinition=][minimumRADvalue=][maximumRADvalue=][rangeRestriction=][defaultValue=][unit=][TypeOfEffect=][shortDescription=NOT IN USE ANYMORE!] */

    ERadCcs_PrintAaRedundancy                = RAD_CCS(0x009E),  /**< AaRedundancy debug prints */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=AaRedundancy debug prints] */

    ERadCcs_PrintAaConfig                    = RAD_CCS(0x009F),  /**< AaConfig general debug print */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=AaConfig general debug print] */


    ERadCcs_AaSysLogSicAddressLocal          = RAD_CCS(0x00A0),  /**< AaSysCom address where prints are forwarded for output mode 5 = local */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=0][unit=bytes][TypeOfEffect=target SW behaviousr change][shortDescription=AaSysCom address where prints are forwarded for output mode 5] */

    ERadCcs_AaSysLogSicAddressRemote         = RAD_CCS(0x00A1),  /**< AaSysCom address where prints are forwarded for output mode 6 = remote */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=0][unit=bytes][TypeOfEffect=target SW behaviousr change][shortDescription=AaSysCom address where prints are forwarded for output mode 6] */

    ERadCcs_AaSysLogCompressionDisable       = RAD_CCS(0x00A2),  /**< AaSysLog 1-disables runtime log compression*/
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=target SW behaviousr change][shortDescription=AaSysLog disables runtime log compression] */

    ERadCcs_AaSysComLiteLogLevel             = RAD_CCS(0x00A3),  /**< SysComLite log level: 0..2: disable, >=3: error, >=4: warning, >=6: info, >=7: debug */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=7][rangeRestriction=][defaultValue=0][unit=bytes][TypeOfEffect=logging manipulation][shortDescription=SysComLite log level] */

    ERadCcs_AaSysLogConsumerRate             = RAD_CCS(0x00A4),  /**< AaSysLog defines the number of iterations in log consumer from a single domain buffer. Values < 0 are slowing down consumer. 1 - default setting, valid values are in range <-100, 100> */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=1][unit=boolean][TypeOfEffect=target SW behaviousr change][shortDescription=AaSysLog defines the number of iterations in log consumer from a single domain buffer] */

    ERadCcs_AaSysLogLiteOutputMode           = RAD_CCS(0x00A5),  /**< AaSysLog lite output mode: 0: unix syslog, 1: stdout/stderr */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=bytes][TypeOfEffect=target SW behaviousr change][shortDescription=AaSysLog lite output mode] */

    ERadCcs_PrintAaWcdmaTime                 = RAD_CCS(0x00A6),  /**< AaWcdmaTime debug print */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=AaWcdmaTime debug print] */

    ERadCcs_PrintAaSysInfo                   = RAD_CCS(0x00A7),  /**< AaSysinfo debug print */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=AaSysinfo related debug prints] */


    ERadCcs_AaSysInfoMemoryStartupTime         = RAD_CCS(0x00A8),  /**< AaSysinfo memory defines time in seconds when first sample is collected */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=120][unit=seconds][TypeOfEffect=logging manipulation][shortDescription=AaSysinfo memory defines time in seconds when first sample is collected] */

    ERadCcs_AaSysInfoMemorySamplingTime        = RAD_CCS(0x00A9),  /**< AaSysinfo memory statistic sampling interval in seconds */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=1][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=900][unit=seconds][TypeOfEffect=logging manipulation][shortDescription=AaSysinfo memory statistic sampling interval in seconds] */

    ERadCcs_AaSysInfoMemoryMaxHistory          = RAD_CCS(0x00AA),  /**< AaSysinfo memory maximum number of files (days if compression interval=24h) for which history is saved */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=1][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=30][unit=n/a][TypeOfEffect=logging manipulation][shortDescription=AaSysinfo memory maximum number of files (days if compression interval=24h) for which history is saved. >= ERadCcs_AaSysInfoMemoryMinHistory] */

    ERadCcs_AaSysInfoMemoryMinHistory          = RAD_CCS(0x00AB),  /**< AaSysinfo memory minimum number of files (days if compression interval=24h) for which history is saved */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=1][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=3][unit=n/a][TypeOfEffect=logging manipulation][shortDescription=AaSysinfo memory minimum number of files (days if compression interval=24h) for which history is saved] */

    ERadCcs_AaSysInfoMemoryFileQuota           = RAD_CCS(0x00AC),  /**< AaSysinfo memory quota in B for all memory statistic logs*/
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=8192][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=0][unit=bytes][TypeOfEffect=logging manipulation][shortDescription=AaSysinfo memory quota in B for all memory statistic logs] */

    ERadCcs_AaSysInfoMemoryCompressionInterval = RAD_CCS(0x00AD),  /**< AaSysinfo memory compression interval*/
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=1][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=86400][unit=seconds][TypeOfEffect=logging manipulation][shortDescription=AaSysinfo memory compression interval] */


    ERadCcs_AaFileTraceConfig                = RAD_CCS(0X00AE),  /**< File debug-trace selection. Used only for debug, when instructed by developers. */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1013][rangeRestriction=][defaultValue=0][unit=bitmask][TypeOfEffect=logging manipulation][shortDescription=File debug-trace selection] */


    ERadCcs_AaSysInfoCpuStartupTime          = RAD_CCS(0x00AF),  /**< AaSysinfo cpu defines time in seconds when first sample is collected */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=120][unit=seconds][TypeOfEffect=logging manipulation][shortDescription=AaSysinfo cpu defines time in seconds when first sample is collected] */

    ERadCcs_AaSysInfoCpuSamplingTime         = RAD_CCS(0x00B0),  /**< AaSysinfo cpu statistic sampling interval in seconds */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=1][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=5][unit=seconds][TypeOfEffect=logging manipulation][shortDescription=AaSysinfo cpu statistic sampling interval in seconds] */

    ERadCcs_AaSysInfoCpuMaxHistory           = RAD_CCS(0x00B1),  /**< AaSysinfo cpu maximum number of files (hours if compression interval=1h) for which history is saved */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=1][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=9][unit=n/a][TypeOfEffect=logging manipulation][shortDescription=AaSysinfo cpu maximum number of files (hours if compression interval=1h) for which history is saved. >=ERadCcs_AaSysInfoCpuMinHistory] */

    ERadCcs_AaSysInfoCpuMinHistory           = RAD_CCS(0x00B2),  /**< AaSysinfo cpu minimum number of files (hours if compression interval=1h) for which history is saved */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=1][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=2][unit=n/a][TypeOfEffect=logging manipulation][shortDescription=AaSysinfo cpu minimum number of files (hours if compression interval=1h) for which history is saved] */

    ERadCcs_AaSysInfoCpuFileQuota            = RAD_CCS(0x00B3),  /**< AaSysinfo cpu quota in B for all cpu statistic logs*/
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=8192][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=0][unit=bytes][TypeOfEffect=logging manipulation][shortDescription=AaSysinfo cpu quota in B for all cpu statistic logs] */

    ERadCcs_AaSysInfoCpuCompressionInterval  = RAD_CCS(0x00B4),  /**< AaSysinfo cpu compression interval*/
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=1][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=3600][unit=seconds][TypeOfEffect=logging manipulation][shortDescription=AaSysinfo cpu compression interval] */

    ERadCcs_PrintAaConfigRadMasterChange     = RAD_CCS(0x00B5),  /**< Logging of RaD parameters changes in RadMaster: 0 -> disabled, 1 -> enabled*/
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=Logging of RaD parameters changes in RadMaster] */

    ERadCcs_PrintAaConfigRadShellChange      = RAD_CCS(0x00B6),  /**< Logging of RaD parameters changes through AaShell commands: 0 -> disabled, 1 -> enabled*/
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=Logging of RaD parameters changes through AaShell] */

    ERadCcs_AaErrorCoreDumpOamEnabled        = RAD_CCS(0x00B7),  /**< AaError; flag to enable/disable core dumps during runtime, 0 = disable core dumps, 1 = enable core dumps */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=feature enabling][shortDescription=enable core dumps during runtime] */


    ERadCcs_AaSysLogSubstringSearchEnabled          = RAD_CCS(0x00B8),  /**< AaSysLog substring search enable feature. 0 = disabled, 1 = enabled, 0xFFFFFFFF = not set*/
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=4294967295][unit=boolean][TypeOfEffect=feature enabling][shortDescription=AaSysLog substring search enable feature] */

    ERadCcs_AaSysLogSubstringSearchDelay            = RAD_CCS(0x00B9),  /**< AaSysLog substring search time in seconds between sending found indication message and next search */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=900][unit=seconds][TypeOfEffect=target SW behaviousr change][shortDescription=AaSysLog substring search time in seconds between sending found indication message and next search] */

    ERadCcs_AaSysLogSubstringSearchMaximumPatterns  = RAD_CCS(0x00BA),  /**< AaSysLog substring search maximum searching patterns */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=1][unit=bytes][TypeOfEffect=target SW behaviousr change][shortDescription=AaSysLog substring search maximum searching patterns] */

    ERadCcs_AaSysLogSubstringSearchActive           = RAD_CCS(0x00BB),  /**< AaSyslog substring search ongoing. 0 = not active, 1 = at least one search is active */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=target SW behaviousr change][shortDescription=AaSyslog substring search ongoing] */


    ERadCcs_PrintAaFileWrapper                      = RAD_CCS(0x00BC),  /**< @deprecated NOT IN USE ANYMORE! */
    /* [modificationProperty=deprecated][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=NOT IN USE ANYMORE!] */


    ERadCcs_AaSysLogUdpAddressLcp0                   = RAD_CCS(0x00BD),  /**< @deprecated NOT IN USE ANYMORE! */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=0][unit=bytes][TypeOfEffect=target SW behaviousr change][shortDescription=IP address where prints from LCP0 are forwarded(while it's active)] */

    ERadCcs_AaSysLogUdpAddressLcp1                   = RAD_CCS(0x00BE),  /**< @deprecated NOT IN USE ANYMORE! */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=0][unit=bytes][TypeOfEffect=target SW behaviousr change][shortDescription=IP address where prints from LCP1 are forwarded(while it's active)] */


    ERadCcs_AaSysInfoRadControlMode                 = RAD_CCS(0x00BF),  /**< AaSysinfo Rad Control over sysinfo parameters 0 = Full Rad Control 1 = Limited Rad Control*/
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=1][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=AaSysinfo Rad Control over sysinfo parameters] */

    ERadCcs_AaSysInfoVerboseMode                    = RAD_CCS(0x00C0),  /**< 1: AaSysInfo shall list all directories in the system on snapshot request. Memory monitoring shall be enabled for all processes.*/
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=AaSysInfo shall list all directories in the system on snapshot request] */

    ERadCcs_AaSysInfoProcessUssThreshold            = RAD_CCS(0x00C1),  /**< AaSysinfo USS memory threshold in bytes for processes not linked with CCS library */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=4194304][unit=bytes][TypeOfEffect=logging manipulation][shortDescription=AaSysinfo USS memory threshold in bytes for processes not linked with CCS library] */

    ERadCcs_AaSysInfoProcessDiscoveryInterval       = RAD_CCS(0x00C2),  /**< AaSysinfo full system scan interval in seconds*/
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=1][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=3600][unit=seconds][TypeOfEffect=logging manipulation][shortDescription=AaSysinfo full system scan interval in seconds] */


    ERadCcs_AaAllocationTraceDbgLogs                    = RAD_CCS(0x00C3),  /**< AaAllocationTrace debug prints. 0 = disabled (default), 1 = enabled */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=AaAllocationTrace debug prints] */

    ERadCcs_AaAllocationTraceMode                       = RAD_CCS(0x00C4),  /**< AaAllocationTrace trace mode. 0 = disabled, 1 = memory leak detection mode (default), 2 = heap profiler mode */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=2][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=target SW behaviour change][shortDescription=AaAllocationTrace trace mode] */

    ERadCcs_AaAllocationTracePoolMemoryQuota            = RAD_CCS(0x00C5),  /**< AaAllocationTrace memory quota for allocation pools (bytes), valid range <0x100000, 0xFFFFFFFF>, default = 0xA00000 */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=1048576][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=10485760][unit=bytes][TypeOfEffect=target SW behaviour change][shortDescription=AaAllocationTrace memory quota for allocation pools] */

    ERadCcs_AaAllocationTracePoolCount                  = RAD_CCS(0x00C6),  /**< AaAllocationTrace number of trace pools. Must be a prime number in range <1, 0xFFFFFFFF>, default = 29 */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=1][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=29][unit=n/a][TypeOfEffect=target SW behaviour change][shortDescription=AaAllocationTrace number of trace pools.] */

    ERadCcs_AaAllocationTraceCompressedPoolMemoryQuota  = RAD_CCS(0x00C7),  /**< AaAllocationTrace memory quota for compressed pool reports (bytes), valid range <0, 0xFFFFFFFF>, default = 0x100000 */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=1048576][unit=bytes][TypeOfEffect=target SW behaviour change][shortDescription=memory quota for compressed pool reports] */

    ERadCcs_AaAllocationTraceCallStackDepth             = RAD_CCS(0x00C8),  /**< AaAllocationTrace call stack depth, valid range <0, 100>, default = 10 */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=100][rangeRestriction=][defaultValue=10][unit=lines][TypeOfEffect=target SW behaviour change][shortDescription=AaAllocationTrace call stack depth] */

    ERadCcs_AaAllocationTraceAllocationTimestampEnabled = RAD_CCS(0x00C9),  /**< Enables allocation timestamp in memory leak detection mode. 0 = disabled (default), 1 = enabled */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=target SW behaviour change][shortDescription=Enables timestamp] */


    ERadCcs_AaTraceMaxPacketDumpSize                    = RAD_CCS(0x00CA),  /**< Limit dump size of packet to SysLog (dump will be truncated if packet bigger than limit). Supported only on MCU */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=0xFFFFFFFF][rangeRestriction=][defaultValue=0xFFFFFFFF][unit=bytes][TypeOfEffect=resource management][shortDescription=Limit dump size of packet to SysLog. Supported only on MCU] */


    ERadCcs_AaTrblServerParallelStoreRequestsPerNode    = RAD_CCS(0x00CB),  /**< Limits amount of AaTrblServer parallel store requests to registered nodes (clients per node), when set to 0, will use old sequential request sending. 0 = disable parallel requests, 1 = enabled, 1 per node (default), valid range <0,255> */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=255][rangeRestriction=][defaultValue=0xFFFFFFFF][unit=n/a][TypeOfEffect=resource management][shortDescription=Limits the number of AaTrblServer parallel store requests to registered nodes (in clients/threads per node)] */


    ERadCcs_AaMemIpcPoolTrackEnabled                    = RAD_CCS(0x00CC),  /**< RCP CC&S only: In AaMemIpcPool Alloc and dealloc function, 0 = disbale the alloc/dealloc track (default), 1 = enable the alloc/dealloc track*/
    /* [modificationProperty=deprecated][typeOfParameterDefinition=][minimumRADvalue=][maximumRADvalue=][rangeRestriction=][defaultValue=][unit=][TypeOfEffect=][shortDescription=NOT IN USE ANYMORE!] */


    ERadCcs_AaSysComUdtxDebug                           = RAD_CCS(0x00CD),  /**< AaSysCom uDTX related debug features */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=SysCom Udtx debug prints] */


    ERadCcs_AaTraceRestrictToOwnDomain                  = RAD_CCS(0x00CE),  /**< Restrict possible tracing message target to own domain. 0 - disable restriction, 0xFFFFFFFF - ignore flag, other - enable restriction */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=4294967295][unit=boolean][TypeOfEffect=tracing manipulation][shortDescription=Restrict possible tracing message target to own domain. 0 - disable restriction, 0xFFFFFFFF - ignore flag, other - enable restriction] */


    ERadCcs_AaSysLogInputLevelDspCluster0               = RAD_CCS(0x00CF),  /**< Prints stored to RAM (postmortem): 0 = disable 1 = debug 2 = info 3 = warning 4 = error 5 = vip 6 = disable */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=6][rangeRestriction=][defaultValue=4294967295][unit=bytes][TypeOfEffect=target SW behaviour change][shortDescription=Prints stored to RAM (postmortem) for CEVA cluster 0 (the flag is valid only for Lionfish environment)] */

    ERadCcs_AaSysLogInputLevelDspCluster1               = RAD_CCS(0x00D0),  /**< Prints stored to RAM (postmortem): 0 = disable 1 = debug 2 = info 3 = warning 4 = error 5 = vip 6 = disable */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=6][rangeRestriction=][defaultValue=4294967295][unit=bytes][TypeOfEffect=target SW behaviour change][shortDescription=Prints stored to RAM (postmortem) for CEVA cluster 1 (the flag is valid only for Lionfish environment)] */

    ERadCcs_AaSysLogInputLevelDspCluster2               = RAD_CCS(0x00D1),  /**< Prints stored to RAM (postmortem): 0 = disable 1 = debug 2 = info 3 = warning 4 = error 5 = vip 6 = disable */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=6][rangeRestriction=][defaultValue=4294967295][unit=bytes][TypeOfEffect=target SW behaviour change][shortDescription=Prints stored to RAM (postmortem) for CEVA cluster 2 (the flag is valid only for Lionfish environment)] */

    ERadCcs_AaSysLogInputLevelDspCluster3               = RAD_CCS(0x00D2),  /**< Prints stored to RAM (postmortem): 0 = disable 1 = debug 2 = info 3 = warning 4 = error 5 = vip 6 = disable */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=6][rangeRestriction=][defaultValue=4294967295][unit=bytes][TypeOfEffect=target SW behaviour change][shortDescription=Prints stored to RAM (postmortem) for CEVA cluster 3 (the flag is valid only for Lionfish environment)] */

    ERadCcs_AaSysLogOutputLevelDspCluster0              = RAD_CCS(0x00D3),  /**< Prints forwarded to output devices: 0 = disable 1 = debug 2 = info 3 = warning 4 = error 5 = vip 6 = disable */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=6][rangeRestriction=][defaultValue=4294967295][unit=bytes][TypeOfEffect=target SW behaviour change][shortDescription=Prints forwarded to output devices for CEVA cluster 0 (the flag is valid only for Lionfish environment)] */

    ERadCcs_AaSysLogOutputLevelDspCluster1              = RAD_CCS(0x00D4),  /**< Prints forwarded to output devices: 0 = disable 1 = debug 2 = info 3 = warning 4 = error 5 = vip 6 = disable */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=6][rangeRestriction=][defaultValue=4294967295][unit=bytes][TypeOfEffect=target SW behaviour change][shortDescription=Prints forwarded to output devices for CEVA cluster 1 (the flag is valid only for Lionfish environment)] */

    ERadCcs_AaSysLogOutputLevelDspCluster2              = RAD_CCS(0x00D5),  /**< Prints forwarded to output devices: 0 = disable 1 = debug 2 = info 3 = warning 4 = error 5 = vip 6 = disable */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=6][rangeRestriction=][defaultValue=4294967295][unit=bytes][TypeOfEffect=target SW behaviour change][shortDescription=Prints forwarded to output devices for CEVA cluster 2 (the flag is valid only for Lionfish environment)] */

    ERadCcs_AaSysLogOutputLevelDspCluster3              = RAD_CCS(0x00D6),  /**< Prints forwarded to output devices: 0 = disable 1 = debug 2 = info 3 = warning 4 = error 5 = vip 6 = disable */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=6][rangeRestriction=][defaultValue=4294967295][unit=bytes][TypeOfEffect=target SW behaviour change][shortDescription=Prints forwarded to output devices for CEVA cluster 3 (the flag is valid only for Lionfish environment)] */


    ERadCcs_AaSysInfoSyscomSamplingTime                 = RAD_CCS(0x00D7),  /**< AaSysInfo Syscom monitoring: sampling interval in seconds */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=1][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=1][unit=seconds][TypeOfEffect=logging manipulation][shortDescription=AaSysInfo Syscom monitoring: sampling interval] */

    ERadCcs_AaSysInfoSyscomSamplesInPeriod              = RAD_CCS(0x00D8),  /**< @deprecated NOT IN USE ANYMORE! */
    /* [modificationProperty=deprecated][typeOfParameterDefinition=][minimumRADvalue=][maximumRADvalue=][rangeRestriction=][defaultValue=][unit=][TypeOfEffect=][shortDescription=NOT IN USE ANYMORE!] */

    ERadCcs_AaSysInfoSyscomCompressionInterval          = RAD_CCS(0x00D9),  /**< AaSysInfo Syscom monitoring: file compression interval in seconds */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=1][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=1][unit=seconds][TypeOfEffect=logging manipulation][shortDescription=AaSysInfo Syscom monitoring: file compression interval] */

    ERadCcs_AaSysInfoSyscomMaxHistory                   = RAD_CCS(0x00DA),  /**< AaSysInfo Syscom monitoring: max number of log files kept */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=1][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=1][unit=n/a][TypeOfEffect=logging manipulation][shortDescription=AaSysInfo Syscom monitoring: max number of log files kept] */

    ERadCcs_AaSysInfoSyscomMinHistory                   = RAD_CCS(0x00DB),  /**< AaSysInfo Syscom monitoring: min number of log files kept */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=1][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=1][unit=n/a][TypeOfEffect=logging manipulation][shortDescription=AaSysInfo Syscom monitoring: min number of log files kept] */

    ERadCcs_AaSysInfoSyscomMaxReports                   = RAD_CCS(0x00DC),  /**< AaSysInfo Syscom monitoring: max number of Message Pool Usage Reports */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=1][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=1][unit=n/a][TypeOfEffect=logging manipulation][shortDescription=AaSysInfo Syscom monitoring: max number of Message Pool Usage Reports] */

    ERadCcs_AaSysInfoSyscomEntriesInReport              = RAD_CCS(0x00DD),  /**< AaSysInfo Syscom monitoring: number of entries in Message Pool Usage Report */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=1][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=1][unit=n/a][TypeOfEffect=logging manipulation][shortDescription=AaSysInfo Syscom monitoring: number of entries in Message Pool Usage Report] */

    ERadCcs_AaSysInfoSyscomReportThreshold              = RAD_CCS(0x00DE),  /**< AaSysInfo Syscom monitoring: reporting threshold value in percentage */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=1][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=1][unit=percents][TypeOfEffect=logging manipulation][shortDescription=AaSysInfo Syscom monitoring: reporting threshold value] */

    ERadCcs_AaSysInfoSyscomReportInterval               = RAD_CCS(0x00DF),  /**< AaSysInfo Syscom monitoring: reporting interval in seconds */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=1][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=1][unit=seconds][TypeOfEffect=logging manipulation][shortDescription=AaSysInfo Syscom monitoring: reporting interval] */

    ERadCcs_AaSysInfoSyscomFileQuota                    = RAD_CCS(0x00E0),  /**< AaSysInfo Syscom monitoring: log files disk quota in bytes */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=8192][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=0][unit=bytes][TypeOfEffect=logging manipulation][shortDescription=AaSysInfo Syscom monitoring: log files disk quota] */

    ERadCcs_AaSysinfoProcessCpuThreshold                = RAD_CCS(0x00E1), /**< Defines the CPU threshold in % from which we start to monitor a process/thread. Default value: 10 Valid range: 0, 100*/
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=100][rangeRestriction=][defaultValue=10][unit=amount][TypeOfEffect=feature enabling][shortDescription=Defines the CPU threshold in % from which we start to monitor a process/thread. Default value: 10 Valid range: 0, 100] */

    ERadCcs_AaSysinfoCpuThreadMonitoring                = RAD_CCS(0x00E2), /**< AaSysInfo CPU monitoring: activating cpu scan for threads:  0 = CPU load measured only for processes (default) 1 = CPU load measured for processes and threads*/
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=1][unit=boolean][TypeOfEffect=feature enabling][shortDescription=AaSysInfo CPU monitoring: activating cpu scan for threads:  0 = CPU load measured only for processes (default) 1 = CPU load measured for processes and threads] */

    ERadCcs_AaSysinfoProcessCpuCount                    = RAD_CCS(0x00E3), /**< Defines the number of top X CPU consuming processes to be monitored. CPU usage is measured within the process discovery interval. Default value: 10 Valid range: 0, 0xFFFFFFFF, 0 means all processes are to be monitored*/
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=10][unit=amount][TypeOfEffect=feature enabling][shortDescription=Defines the number of top X CPU consuming processes to be monitored. CPU usage is measured within the process discovery interval. Default value: 10 Valid range: 0, 0xFFFFFFFF, 0 means all processes are to be monitored] */

    ERadCcs_AaSysInfoUPLoadMaxHistory                   = RAD_CCS(0x00E4),  /**< AaSysInfo RT/DSP cores log collection monitoring: max number of log files kept */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=1][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=30][unit=n/a][TypeOfEffect=logging manipulation][shortDescription=AaSysInfo RT/DSP load: max number of log files kept] */

    ERadCcs_AaSysInfoUPLoadMinHistory                   = RAD_CCS(0x00E5),  /**< AaSysInfo RT/DSP cores log collection: min number of log files kept */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=3][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=3][unit=n/a][TypeOfEffect=logging manipulation][shortDescription=AaSysInfo RT/DSP load: min number of log files kept] */

    ERadCcs_AaSysInfoUPLoadFileQuota                    = RAD_CCS(0x00E6),  /**< AaSysInfo RT/DSP cores log collection: log files disk quota in bytes */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=8192][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=0][unit=bytes][TypeOfEffect=logging manipulation][shortDescription=AaSysInfo RT/DSP load: log files disk quota] */

    ERadCcs_AaSysLogPrintRcpDbgLogs                     = RAD_CCS(0x00E7),  /**< RCP Linux logs debug print */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=RCP Linux logs debug print] */

    ERadCcs_PrintAaStartupTime                          = RAD_CCS(0x00E8),  /**< Startup Time Service debug print */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=Startup Time Service debug print] */

    ERadCcs_AaSysInfoUPLoadCompressionInterval          = RAD_CCS(0x00E9),  /**< AaSysInfo RT/DSP cores log collection: compression interval in seconds */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=1][maximumRADvalue=4294967295][rangeRestriction=][defaultValue=3600][unit=seconds][TypeOfEffect=logging manipulation][shortDescription=AaSysInfo RT/DSP load: file compression interval in seconds] */

    ERadCcs_AaSysMessageOperationHistoryEnable         = RAD_CCS(0x00EA),  /**< Message operation history enabling. Initialized at startup */
    /* [modificationProperty=change on initialization][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=Message operation history enabling. Initialized at startup] */

    ERadCcs_PrintAaPoolMonitor                         = RAD_CCS(0x00EB),  /**< AaPoolMonitor debug print */
    /* [modificationProperty=change dynamically][typeOfParameterDefinition=u32][minimumRADvalue=0][maximumRADvalue=1][rangeRestriction=][defaultValue=0][unit=boolean][TypeOfEffect=logging manipulation][shortDescription=AaPoolMonitor debug print] */

    ERadCcs_Last /* Not usable value, do not move or touch! */


};

/*@}*/

#ifdef __cplusplus
}
#endif

#endif /* _ERAD_CCS_H_ */

