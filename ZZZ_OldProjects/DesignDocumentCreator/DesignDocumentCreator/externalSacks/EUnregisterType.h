/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Ppc_Env/Definitions/EUnregisterType.h $
* @version               $LastChangedRevision: 4159 $
* @date                  $LastChangedDate: 2014-06-23 15:57:39 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: kacperki $
*
* Original author        Bartosz Kacperkiewicz
*
* Copyright 2014 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _E_UNREGISTER_TYPE_H
#define _E_UNREGISTER_TYPE_H

typedef enum EUnregisterType
{
    EUnregisterType_TransportBearer                                          = 0,
    EUnregisterType_TransactionReset                                         = 1,
    EUnregisterType_NbccReset                                                = 2,
    EUnregisterType_CellReset                                                = 3
} EUnregisterType;

#endif /* _E_UNREGISTER_TYPE_H */

/**
*******************************************************************************
* @enum EUnregisterType
*
* Description         : Unregister type for TUPC-RLH Transport Bearer Unrgister Message
*
* Reference           :
*
* @param EUnregisterType_TransportBearer  : normal unregister
* @param EUnregisterType_TransactionReset : transaction reset
* @param EUnregisterType_NbccReset  : reset users by nbccId
* @param EUnregisterType_CellReset  : reset users by cellId
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : TUPC
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
*******************************************************************************/


