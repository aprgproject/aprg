/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Ppc_Env/Definitions/ETransportBearerCause.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Lukasz Haracz
*
* Copyright 2013 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _E_TRANSPORT_BEARER_CAUSE_H
#define _E_TRANSPORT_BEARER_CAUSE_H

typedef enum ETransportBearerCause
{
  ETransportBearerCause_NoCause       = 0,
  ETransportBearerCause_CACRejection  = 1,
  ETransportBearerCause_TRSFailure    = 2,
  ETransportBearerCause_TRSTimeout    = 3,
  ETransportBearerCause_TRSOverloaded = 4,
  ETransportBearerCause_InvalidParametersNack = 5,
  ETransportBearerCause_NoConnectionNack = 6,
  ETransportBearerCause_NoResourcesNack = 7,
  ETransportBearerCause_ErrorinRollbackNack = 8,
  /*TransportBearer Reallocation Nacks */
  ETransportBearerCause_ReallocationNoReallocationFoundNack = 9,
  ETransportBearerCause_ReallocationNoBearerFoundNack = 10,
  ETransportBearerCause_ReallocationRollbackNack = 11,
  ETransportBearerCause_ReallocationResetNack = 12,
  ETransportBearerCause_UnsuccessfulReallocationNack = 13,
  ETransportBearerCause_ReallocationCancelInProgressNack = 14,
  ETransportBearerCause_ReallocationAlreadyCommittedNack = 15,
  ETransportBearerCause_ReallocationCleanupCausedbyTimeoutInProgressNack = 16,
  /* TransportBearer Sec Carrier Nacks */
  ETransportBearerCause_NoPrimaryConnectionRegistered = 17,
  ETransportBearerCause_AlreadyUsedConnection = 18,
  ETransportBearerCause_Other = 19
} ETransportBearerCause;

#endif /* _E_TRANSPORT_BEARER_CAUSE_H */

/**
*******************************************************************************
* @enum ETransportBearerCause
*
* Description         : Used in Telecom internal messages
*
* Reference           : WCDMA BTS TCOM SW
*
* @param ETransportBearerCause_NoCause                                            :  No cause
* @param ETransportBearerCause_CACRejection                                       :  CAC Rejection
* @param ETransportBearerCause_TRSFailure                                         :  TRS Failure
* @param ETransportBearerCause_TRSTimeout                                         :  TRS Timeout
* @param ETransportBearerCause_TRSOverloaded                                      :  TRS Overloaded
* @param ETransportBearerCause_InvalidParametersNack                              :  Invalid parameters
* @param ETransportBearerCause_NoConnectionNack                                   :  No Connection
* @param ETransportBearerCause_NoResourcesNack                                    :  No Resources
* @param ETransportBearerCause_ErrorinRollbackNack                                :  Error in rollack
* @param ETransportBearerCause_ReallocationNoReallocationFoundNack                :  No reallocation found
* @param ETransportBearerCause_ReallocationNoBearerFoundNack                      :  No bearer for reallocation found
* @param ETransportBearerCause_ReallocationRollbackNack                           :  Reallocation rollback nack
* @param ETransportBearerCause_ReallocationResetNack                              :  Reallocation reset
* @param ETransportBearerCause_UnsuccessfulReallocationNack                       :  Unsuccessful reallocation
* @param ETransportBearerCause_ReallocationCancelInProgressNack                   :  Reallocation cancel in progress
* @param ETransportBearerCause_ReallocationAlreadyCommittedNack                   :  Reallocation aready comitted
* @param ETransportBearerCause_ReallocationCleanupCausedbyTimeoutInProgressNack   :  Cleanup caused by timeout
* @param ETransportBearerCause_NoPrimaryConnectionRegistered                      :  No primary connection
* @param ETransportBearerCause_AlreadyUsedConnection                              :  Already used connection
* @param ETransportBearerCause_Other                                              :  Other
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : Telecom
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
*******************************************************************************/

