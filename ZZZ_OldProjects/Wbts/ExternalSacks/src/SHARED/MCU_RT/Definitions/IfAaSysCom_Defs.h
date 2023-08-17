/** @file
 * @brief Describes common AaSysCom definitions
 * @copyright 2015 Nokia Networks. All rights reserved.
 * @copyright 2019 Nokia. All rights reserved.
 */

#ifndef IF_MCU_RT_AASYSCOM_DEF_H_
#define IF_MCU_RT_AASYSCOM_DEF_H_

#include <CcsCommon.h>

#ifdef CCS_NEW_IF_STRUCTURE
#include "../../../COMMON/ServiceInterface/IfAaSem.h"
#include "../../../COMMON/ServiceInterface/IfAaPro.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------- DOXYGEN GROUPS --------------------------------------*/

/**
 * @addtogroup dgAaSysComMcuRt AaSysCom MCU_RT
 * @ingroup dgAaSysCom
 *
 * Common Computer and Support SW System Communication Configuration.
 *
 * @{
 */

/**
 *
 * Runtime configuration can be divided into pre- and post-configuration phases.
 * Pre-configuration takes place before CE startup has been done for a service.
 * Post-configuration takes place after CE, EE and EU startup. Configuration is
 * handled using so called configuration tags. Data and keys are variable
 * width in size so they are quite flexible to use.
 * \n\n
 * Usually configuration tags are used for input direction i.e. feeding
 * configuration to CC&S service. However some tags can also be used for output
 * direction i.e. for advertising CC&S service state or capabilities. Configuration
 * tag description should state wether the tag is inteded for feeding information
 * (input) to the service or the service uses the tag for capability and state
 * advertisement (output).
 *
 * @verbatim
 *  Tag name:        ccs.service.aasyscom.dyncpidstart
 *
 *  Direction:       input
 *
 *  Context:         CE
 *
 *  Description:     Sets start of dynamic cpIds, value type is TAaSysComCpid,
 *                   both start and end has to be set before syscom is able to
 *                   return a dynamic cpId.
 *
 *  Effect analysis: N/A
 *
 *  Restriction:     From SysCom viepoint reserved values AASYSCOM_CP_ANY,
 *                   AASYSCOM_CP_NONE, AASYSCOM_CP_INVALID (defined in
 *                   IfAaSysCom.h).
 *                   From system viepoint there are cpId spaces for each subsytem.
 *                   dyncpidstart must be < dyncpidend (see below)
 *
 *  Value:           IE Type:     Size:     Range:
 *                   number       u16       0...0xFFFF (see restriction)
 *
 *  Define:          AASYSCOM_CONFIG_TAG_DYNCPID_START
 *
 *  See:             None
 * @endverbatim
 *
 *
 * @verbatim
 *  Tag name:        ccs.service.aasyscom.dyncpidend
 *
 *  Direction:       input
 *
 *  Context:         CE
 *
 *  Description:     Sets end of CPIDs in the system, value type is TAaSysComCpid,
 *                   value will be read by syscom at the time AaSysComInit() is
 *                   called, if not set a default value will be used.
 *
 *  Effect analysis: N/A
 *
 *  Restriction:     From SysCom viepoint reserved values AASYSCOM_CP_ANY,
 *                   AASYSCOM_CP_NONE, AASYSCOM_CP_INVALID (defined in
 *                   IfAaSysCom.h).
 *                   From system viepoint there are cpId spaces for each subsytem.
 *                   dyncpidend must be > dyncpidstart (see above)
 *
 *  Value:           IE Type:     Size:     Range:
 *                   number       u16       0...0xFFFF (see restriction)
 *
 *  Define:          AASYSCOM_CONFIG_TAG_DYNCPID_END
 *
 *  See:             None
 * @endverbatim
 *
 *
 * @verbatim
 *  Tag name:        ccs.service.aasyscom.maxcpids
 *
 *  Direction:       input
 *
 *  Context:         CE
 *
 *  Description:     Sets max number of CPIDs in the system, value type is
 *                   TAaSysComCpid, value will be read by syscom at the time
 *                   AaSysComInit() is called, if not set a default value will
 *                   be used. (In principal optional but in practise mandatory,
 *                   because the default value is so small.)
 *
 *  Effect analysis: N/A
 *
 *  Restriction:     From SysCom viepoint range and reserved values restrict the
 *                   value.
 *                   From system viepoint there are cpId spaces for each subsytem
 *                   and these restrict also value for maxcpids.
 *
 *  Value:           IE Type:     Size:     Range:
 *                   number       u16       0...0xFFFF (see restriction)
 *
 *  Define:          AASYSCOM_CONFIG_TAG_MAXCPIDS
 *
 *  See:             None
 * @endverbatim
 *
 *
 * @verbatim
 *  Tag name:        ccs.service.aasyscom.priority
 *
 *  Direction:       input
 *
 *  Context:         CE
 *
 *  Description:     Sets priority for syscom Eus, value type is u32, value will
 *                   be read by syscom at the time AaSysComInit() is called, if
 *                   not set a default value will be used.
 *
 *  Effect analysis: N/A
 *
 *  Restriction:     IfAaPro.h defines the abstract value which are finally mapped
 *                   to OS dependent priority values.
 *
 *  Value:           IE Type:     Size:     Range:
 *                   number       u32       abstract value range 0..32 (see restriction)
 *
 *  Define:          AASYSCOM_CONFIG_TAG_PRI
 *
 *  See:             None
 * @endverbatim
 *
 *
 * @verbatim
 *  Tag name:        ccs.service.aasyscom.stacksize
 *
 *  Direction:       input
 *
 *  Context:         CE
 *
 *  Description:     Sets stacksize for syscom eus, value type is u32, value
 *                   will be read by syscom at the time AaSysComInit() is called,
 *                   if not set a default value will be used.
 *
 *  Effect analysis: N/A
 *
 *  Restriction:     None.
 *
 *  Value:           IE Type:     Size:     Range:
 *                   number       u16       0...0xFFFF (see restriction)
 *
 *  Define:          AASYSCOM_CONFIG_TAG_STACKSIZE
 *
 *  See:             None
 * @endverbatim
 *
 *
 * @verbatim
 *  Tag name:        ccs.service.aasyscom.remote.ready
 *
 *  Direction:       input
 *
 *  Context:         EE
 *
 *  Description:     AaSysCom own NID is set. Value type is u32. Before this tag
 *                   is set to 1, AaSysCom will not be able to route messages
 *                   outside and AaSysComGetOwnNid() will return
 *                   AASYSCOM_NODE_INVALID.
 *
 *  Effect analysis: N/A
 *
 *
 *  Value:           IE Type:     Size:     Range:
 *                   number       u32       0 - AaSysCom does not know own NID
 *                                          1 - AaSysCom knows own NID
 *
 *  Define:          AASYSCOM_CONFIG_TAG_REMOTE_READY
 *
 *  See:             None
 * @endverbatim
 *
 *
 * @verbatim
 *  Tag name:        ccs.service.aasyscom.register.dynamic.ready
 *
 *  Direction:       input
 *
 *  Context:         EE
 *
 *  Description:     AaSysCom dynamic CPID range is set. Value type is u32.
 *                   AaSysCom will not be able to register dynamic CPID before
 *                   this tag is set to 1.
 *
 *  Effect analysis: N/A
 *
 *
 *  Value:           IE Type:     Size:     Range:
 *                   number       u32       0 - dynamic CPID range is not set
 *                                          1 - dynamic CPID range is set
 *
 *  Define:          AASYSCOM_CONFIG_TAG_DYNAMIC_READY
 *
 *  See:             None
 * @endverbatim
 */


/*----------------------- INCLUDED FILES -------------------------------------*/

#include <glo_def.h>

/*----------------------- PRIVATE DECLARATIONS -------------------------------*/

/*----------------------- PUBLIC DECLARATIONS --------------------------------*/

/** @name Following AaConfig tags are supported by the AaSysCom MCU
 *
 * @{
 */

/** Sets start of dynamic CPIDs. Value type is TAaSysComCpid. Both start and
    end have to be set before SysCom is able to return a dynamic CPID. */
#define AASYSCOM_CONFIG_TAG_DYNCPID_START "ccs.service.aasyscom.dyncpidstart"
/** Sets end of dynamic CPIDs. Value type is TAaSysComCpid. Both start and end
    have to be set before SysCom is able to return a dynamic CPID. */
#define AASYSCOM_CONFIG_TAG_DYNCPID_END "ccs.service.aasyscom.dyncpidend"
/** Sets max number of CPIDs in the system. Value type is TAaSysComCpid. Value
    will be read by SysCom when AaSysComInit() is called. If not set, default
    value will be used. */
#define AASYSCOM_CONFIG_TAG_MAXCPIDS "ccs.service.aasyscom.maxcpids"
/** Sets priority for SysCom EUs. Value type is u32. Value will be read by
    SysCom when AaSysComInit() is called. If not set, default value will be
    used. */
#define AASYSCOM_CONFIG_TAG_PRI "ccs.service.aasyscom.priority"
/** Sets stacksize for SysCom EUs. Value type is u32. Value will be read by
    SysCom when AaSysComInit() is called. If not set, default value will be
    used. */
#define AASYSCOM_CONFIG_TAG_STACKSIZE "ccs.service.aasyscom.stacksize"
/**
    Tag for CCS role. Defines if the system module contains CCS master
    functionality. Type string. Possible values "TRUE" or tag does not exist.
    @deprecated Not supported due to PR490226.
*/
#define AASYSCOM_CONFIG_TAG_CCSMASTER "ccs.service.aasyscom.ccs.master"

/** AaSysCom own NID is set. Value type is u32. Before this tag is set to 1,
    AaSysCom will not be able to route messages outside and AaSysComGetOwnNid()
    will return AASYSCOM_NODE_INVALID. */
#define AASYSCOM_CONFIG_TAG_REMOTE_READY "ccs.service.aasyscom.remote.ready"
/** AaSysCom dynamic CPID range is set. Value type is u32. AaSysCom will not be
    able to register dynamic CPID before this tag is set to 1. */
#define AASYSCOM_CONFIG_TAG_DYNAMIC_READY "ccs.service.aasyscom.register.dynamic.ready"

/** @} */


typedef struct SAaSysComCreateAndStartInfo {
    TAaProEuEntryPoint *euEntryPoint;
    void*              euArgPtr;
    u32                sizeOfEuArg;
    TAaSem             *syncSem; /**< Sync semaphore for ensuring proper execution sequence */
} SAaSysComCreateAndStartInfo;


/** @} end: @addtogroup dgAaSysComMcuRt AaSysCom MCU_RT */

#ifdef __cplusplus
}
#endif

#endif  //IF_MCU_RT_AASYSCOM_DEF_H_
