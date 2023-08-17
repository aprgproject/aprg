/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/STransaction.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Jukka Sakkinen
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _S_TRANSACTION_H
#define _S_TRANSACTION_H

#include <TTransactionID.h>
#include <EStatus.h>

struct STransaction
{
    TTransactionID        transactionId;
    EStatus               status;
};
typedef struct STransaction STransaction;

#endif /* _S_TRANSACTION_H */

/******************************************************************************
* @struct STransaction
* Description         : Transaction parameters.
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location: Sharenet
*
* @param transactionId  The Transaction ID is used to associate all the messages
*                       belonging to the same procedure. Messages belonging to
*                       the same procedure shall use the same transaction ID.*
*
* @param status         The status of the transaction.
*
* Additional Information :
*
* Definition Provided by : DSP
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
*******************************************************************************/

