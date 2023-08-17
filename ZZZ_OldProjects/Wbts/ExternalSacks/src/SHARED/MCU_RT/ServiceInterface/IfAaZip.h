/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 ZLIB ZIP add-on for CC&S
* @module                Compressions
* @owner                 Ksenija Bischof 
*
* Copyright 2014 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_RT_IFAAZIP_H
#define _MCU_RT_IFAAZIP_H

/*----------------------- INCLUDED FILES -------------------------------------*/

#include <glo_def.h>
#include "CcsCommon.h"

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------- DOXYGEN GROUPS -------------------------------------*/

/**
* @defgroup dgAaZip Archive Service (AaZip)
* @ingroup  dgCompressionsApiMcu
*
*   Features
*   - Multiple file archive support
*   - Compression support
*   - Support to store archive to as file (file system)
*   - Support to store archive to memory 
*   - Archive ".zip" is natively supported in Windows and Linux PCs.
*/



/*----------------------- PUBLIC DECLARATIONS --------------------------------*/
/**
 * @addtogroup dgAaZip
 *
 * @{ */


/** @brief  Append defines from zip.h, use only additional AAZIP_ prefix!  */

#define AAZIP_APPEND_STATUS_CREATE      (0)
#define AAZIP_APPEND_STATUS_CREATEAFTER (1)
#define AAZIP_APPEND_STATUS_ADDINZIP    (2)

/** @brief Zip function return value */
typedef enum EAaZipErrors
{
 	EAaZip_OK		  = 0,
 	EAaZip_EOF		  = 0,
 	EAaZipError_Errno	  = (-1),	
     	EAaZipError_ParamError 	  = -102,
     	EAaZipError_BadZipFile	  = -103,
     	EAaZipError_InternalError = -104,     	
     	EAaZipError_Last
     	    
} EAaZipErrors;
    
typedef void* TAaZipFile;

/*----------------------- PUBLIC INTERFACES (MCU API) ------------------------*/



/**
*******************************************************************************
*
*   @brief      Open archive from file system.
*
*   @param[in] pathname     File path and name. 
*   @param[in] append       Method to open file.
*   @return                 Archive instance in success otherwise NULL.
*
*   @par Description:
*
*   Open zip archive for writing. File is opened from AaFile device.
*
*   @par Errors: NULL is returned if archive could not be opened
*
*   None
*
*   @par Restrictions:
*
*   None
*
*   @par Example:
*
*   @code
*
*   #include <IfAaZip.h>
*
*   TAaZipFile file;
*   
*   file = AaZipOpen("/ram/my.zip", AAZIP_APPEND_STATUS_CREATE);
*   
*   if( file != NULL )
*   {
*   
*   }
*
*   @endcode
*
*   @par Usage:
*
*   None
*
*   @par Rationale:
*
*   None
*
*   @par Future directions:
*
*   None
*
*   @see AaZipOpenFileInZip
*
*******************************************************************************/
TAaZipFile AaZipOpen(const char *pathname, int append);

/**
*******************************************************************************
*
*   @brief      Open new file in archive.
*   
*   @param[in]  file        Zip archive instance.
*   @param[in]  filename    New file to be added to zip archive.
*   @param[in]  method      Compression method (0 for store, Z_DEFLATED for deflate)
*   @param[in]  level       Level of compression (0, Z_DEFAULT_COMPRESSION etc)
*   @return                 Zero in success otherwise error.
*
*   @par Description:
*
*   @par Errors: 
*   - EAaZipError_ParamError
*   - EAaZipError_InternalError
*
*   None
*
*   @par Restrictions:
*
*   None
*
*   @par Example:
*
*   @code
*
*   #include <IfAaZip.h>
*
*   TAaZipFile file;
*   EAaZipErrors   error = EAaZip_OK;
*   
*   file = AaZipOpen("/ram/my.zip", APPEND_STATUS_ADDINZIP);
*   error = AaZipOpenNewFileInZip(file, "new.txt"); 
*
*   @endcode
*
*   @par Usage:
*
*   None
*
*   @par Rationale:
*
*   None
*
*   @par Future directions:
*
*   None
*
*   @see AaZipOpenFile
*
*******************************************************************************/
EAaZipErrors AaZipOpenNewFileInZip(TAaZipFile file, const char* filename, int method, int level);

/**
*******************************************************************************
*
*   @brief      Write to opened file in zip archive.
*   
*   @param[in]  file        Zip archive instance.
*   @param[in]  buf         Pointer to data to be written.
*   @param[in]  len         Length of data to be written.
*   @return                 Zero in success otherwise error.
*
*   @par Description:
*
*   @par Errors:  
*   - EAaZipError_ParamError
*   - EAaZipError_Errno
*
*   None
*
*   @par Restrictions:
*
*   None
*
*   @par Example: Refer to paragraph 6 Examples in CC&S Service API Specification Compressionss
*
*   @code
*
*   @endcode
*
*   @par Usage:
*
*   None
*
*   @par Rationale:
*
*   None
*
*   @par Future directions:
*
*   None
*
*   @see AaZipOpenFile
*   @see AaZipOpenNewFileInZip
*
*******************************************************************************/
EAaZipErrors AaZipWrite(TAaZipFile file, const void* buf, unsigned len);

/**
*******************************************************************************
*
*   @brief      Close opened file in zip archive.
*   
*   @param[in]  file        Zip archive instance.
*   @return                 Zero in success otherwise error.
*
*   @par Description:
*
*   @par Errors:  
*   - EAaZipError_ParamError
*   - EAaZipError_Errno
*
*   None
*
*   @par Restrictions:
*
*   None
*
*   @par Example: Refer to paragraph 6 Examples in CC&S Service API Specification Compressionss
*
*   @code
*
*   @endcode
*
*   @par Usage:
*
*   None
*
*   @par Rationale:
*
*   None
*
*   @par Future directions:
*
*   None
*
*   @see AaZipOpenFile
*   @see AaZipOpenNewFileInZip
*
*******************************************************************************/
EAaZipErrors AaZipCloseFileInZip(TAaZipFile file);

/**
*******************************************************************************
*
*   @brief      Close zip archive.
*   
*   @param[in]  file        Zip archive instance.
*   @return                 Zero in success otherwise error.
*
*   @par Description:
*
*   @par Errors:  
*   - EAaZipError_ParamError
*   - EAaZipError_Errno
*
*   None
*
*   @par Restrictions:
*
*   None
*
*   @par Example: Refer to paragraph 6 Examples in CC&S Service API Specification Compressionss
*
*   @code
*
*   @endcode
*
*   @par Usage:
*
*   None
*
*   @par Rationale:
*
*   None
*
*   @par Future directions:
*
*   None
*
*   @see AaZipOpenFile
*
*******************************************************************************/
EAaZipErrors AaZipClose(TAaZipFile file);

/*@}*/


/*----------------------- INTERNAL INTERFACES --------------------------------*/

/** @name Zip Private API to use with ZLIB minizip interface.
*@{
*/

/**
*******************************************************************************
*
*   @brief      Fill AaFile driver to ZLIB minizip device structure.
*   
*   @param[in]  filefunc    Pointer to minizip device instance.
*
*******************************************************************************/
void AaZipFillAaFileFunction(void* filefunc);

/**
*******************************************************************************
*
*   @brief      Fill Memory driver to ZLIB minizip device structure.
*
*   @param[in]  filefunc    Pointer to minizip device instance.
*   
*   @par Description:
*
*   Memory driver filenames are specified in the form :
*   <hex base of zip file>+<hex size of zip file>
*   
*
*   @par Errors:
*
*   None
*
*   @par Restrictions:
*
*   None
*
*   @par Example:
*
*   @code
*
*   #include <string.h>
*   #include <IfAaMem.h>
*   #include <IfAaZip.h>
*   #include <zip.h>

*   
*   zipFile           file;
*   zlib_filefunc_def device;
*   char*             memory;          
*   char              filename[48];
*   
*   //Reserve 128kB for zip files.
*   memory = (char*)AaMemMalloc(0x20000);
*
*   if( memory != NULL )
*   {
*      memset(memory, 0, 0x20000);
*      
*      AaZipFillMemoryFunction(&device);
*      
*      //Reserve 16kB for my first zip file
*      sprintf(filename, "%x+%x", memory, 0x4000);
*      
*      file = zipOpen2(filename, APPEND_STATUS_CREATE, NULL, &device);
*      
*      if( file != NULL )
*      {
*          //Open log file in zip archive and write data to log file.
*      }
*      
*      //Reserve 32kB for my second zip file
*      sprintf(filename, "%x+%x", memory + 0x4000, 0x8000);
*      
*      file = zipOpen2(filename, APPEND_STATUS_CREATE, NULL, &device);
*      
*      if( file != NULL )
*      {
*          //Open log file in zip archive and write data to log file.
*      }
*   }  
*
*   @endcode
*
*   @par Usage:
*
*   None
*
*   @par Rationale:
*
*   None
*
*   @par Future directions:
*
*   None
*
*   @see AaZipOpenFileInZip
*
*******************************************************************************/
void AaZipFillMemoryFunction(void* filefunc);


/*@}*/


#ifdef __cplusplus
}
#endif

#endif /* _MCU_RT_IFAAZIP_H */
