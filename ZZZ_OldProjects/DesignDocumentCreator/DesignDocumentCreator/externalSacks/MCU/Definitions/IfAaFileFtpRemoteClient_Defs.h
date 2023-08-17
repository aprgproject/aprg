/** @file
*   @brief AaFile Remote Ftp Client definitions.
*
*   $HeadURL$
*   $LastChangedRevision$
*   $LastChangedDate$
*   $Author$
*   $Copyright: 2016 Nokia. All rights reserved.$
*/

#ifndef _MCU_IF_AAFILEFTP_REMOTE_CLIENT_DEFS_H_
#define _MCU_IF_AAFILEFTP_REMOTE_CLIENT_DEFS_H_

#include <CcsCommon.h>
#include "IfAaFileFtpClient_Defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup dgAaFileApiMcu
 * @ingroup dgAaFile
 */

/** @{ */

/**
******************************************************************************
* @verbatim
*  Tag name:        ccs.service.aafile.ftp.client.proxy.enable
*
*  Description:     The tag is meant to trigger start of AaFileClientProxy thread.
*
*  Effect analysis: If this tag is set to value greater than 0 AaFileClientProxy thread
*                   is started.
*
*  Restriction:     None
*
*  Value:           IE Type:     Size:     Range:
*                   number       u32       >= 0
*
*  Define:          AAFILE_FTP_REMOTE_CLIENT_PROXY_ENABLE
*
*  See:             None
* @endverbatim
******************************************************************************/
#define AAFILE_FTP_REMOTE_CLIENT_PROXY_ENABLE "ccs.service.aafile.ftp.client.proxy.enable"

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _MCU_IF_AAFILEFTP_REMOTE_CLIENT_DEFS_H_ */
