/** @file
*   @brief AaPostmortem MCU API.
*   @copyright 2015 Nokia Networks. All rights reserved.
*   @copyright 2019 Nokia. All rights reserved.
*/

#ifndef _MCU_IFAAPOSTMORTEM_H
#define _MCU_IFAAPOSTMORTEM_H

/************************** INCLUDED FILES ************************************/
#include "CcsCommon.h"
#ifdef CCS_NEW_IF_STRUCTURE
#include <../../SHARED/MCU_RT/Definitions/IfAaPostmortem_Defs.h>
#include <../../MCU/Definitions/IfAaPostmortem_Defs.h>
#endif
#ifdef __cplusplus
extern "C"{
#endif

/************************** DOXYGEN GROUPS ************************************/
/**
* @defgroup dgAaPostmortem AaPostmortem API
* @ingroup dgAaPostmortem
*
*/
/*@{*/

/*!
 *  @name Configuration IDs.
 */
/*@{*/


/*@}*/

/************************** PUBLIC DECLARATIONS *******************************/
/**
*******************************************************************************
*
*   @brief      Function adds file to back up list.
*
*   @param[in] filePath  AaFile path notation, for example /ram/example.txt.
*
*   @return     Indicates if the function was executed successfully.
*
*   @par Description:
*   The function adds file to backup list. Once AaPostmortemGenerateBackUpScript is called
*   AaPostmortem generates backup script (coldResetBackup.sh) with directories
*   and files from backup list.
*
*   @par Errors:
*        EAaPostmortemRetVal_Error - in case of some internal error.
*        EAaPostmortemRetVal_InvalidParameter - while invalid parameter is given.
*
*   @par Restrictions:
*   Service configured and running (able to handle messages) before calling this function.
*
*   @par Example:
*   @code
*       EAaPostmortemRetVal retVal = AaPostmortemAddFileToBackUpList("/ram/example.log");
*
*       if (EAaPostmortemRetVal_Ok != retVal)
*       {
*           AaSysLogPrint(EAaSysLogSeverityLevel_Error,
*                         "AaPostmortemAddFileToBackUpList failed, retVal=%d",
*                         retVal);
*       }
*
*   @endcode
*
*   @par Usage:
*   None
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*******************************************************************************/
EAaPostmortemRetVal AaPostmortemAddFileToBackUpList(const char* filePath);

/**
*******************************************************************************
*
*   @brief      Function adds directory to back up list.
*
*   @param[in] dirPath  AaFile path notation, for example /ram/exampleDir.
*
*   @return     Indicates if the function was executed successfully.
*
*   @par Description:
*   The function adds directory to backup list. Once AaPostmortemGenerateBackUpScript is called
*   AaPostmortem generates backup script (coldResetBackup.sh) with directories
*   and files from backup list.
*
*   @par Errors:
*        EAaPostmortemRetVal_Error - in case of some internal error.
*        EAaPostmortemRetVal_InvalidParameter - while invalid parameter is given.
*
*   @par Restrictions:
*   Service configured and running (able to handle messages) before calling this function.
*
*   @par Example:
*
*   @code
*
*   EAaPostmortemRetVal retVal = AaPostmortemAddDirectoryToBackUpList("/ram/exampleDir");
*
*   if (EAaPostmortemRetVal_Ok != retVal)
*   {
*       AaSysLogPrint(EAaSysLogSeverityLevel_Error,
*                     "AaPostmortemAddDirectoryToBackUpList failed, retVal=%d",
*                     retVal);
*   }
*
*   @endcode
*
*   @par Usage:
*   None
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*******************************************************************************/
EAaPostmortemRetVal AaPostmortemAddDirectoryToBackUpList(const char* dirPath);

/**
*******************************************************************************
*
*   @brief      Function triggers  back up script (coldResetBackup.sh)
*               generation under /ram AaFile directory.
*
*   @return     Indicates if the function was executed successfully.
*
*   @par Description:
*   The function triggers AaPostmortem to generate and execute coldResetBackup.sh.
*   The script copies registered files and directories to reset proof memory.
*
*   @par Errors:
*        EAaPostmortemRetVal_Error - in case of some internal error.
*
*   @par Restrictions:
*   Service configured and running (able to handle messages) before calling this function.
*
*   @par Example:
*   @code
*   EAaPostmortemRetVal retVal = AaPostmortemGenerateBackUpScript();
*
*   if (EAaPostmortemRetVal_Ok != retVal)
*   {
*       AaSysLogPrint(EAaSysLogSeverityLevel_Error,
*                     "AaPostmortemGenerateBackUpScript failed, retVal=%d",
*                     retVal);
*   }
*
*   @endcode
*
*   @par Usage:
*   None
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*******************************************************************************/
EAaPostmortemRetVal AaPostmortemGenerateBackUpScript(void);

/*@}*/

#ifdef __cplusplus
}
#endif
#endif /* _MCU_IFAAPOSTMORTEM_H */
