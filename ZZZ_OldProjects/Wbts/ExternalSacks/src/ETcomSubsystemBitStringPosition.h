/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Original author        <Iangelo Yee>
*
* Copyright 2016 Nokia. All rights reserved.
*******************************************************************************/
#ifndef _E_TCOM_SUBSYSTEM_BIT_STRING_POSITION_H
#define _E_TCOM_SUBSYSTEM_BIT_STRING_POSITION_H

typedef enum ETcomSubsystemBitStringPosition
{
  ETcomSubsystemBitStringPosition_BchSender       = 0,
  ETcomSubsystemBitStringPosition_CCHH            = 1,
  ETcomSubsystemBitStringPosition_CMEAS           = 2,
  ETcomSubsystemBitStringPosition_DMEAS           = 3,
  ETcomSubsystemBitStringPosition_DMGR            = 4,
  ETcomSubsystemBitStringPosition_GRM             = 5,
  ETcomSubsystemBitStringPosition_HSCH            = 6,
  ETcomSubsystemBitStringPosition_LRM             = 7,
  ETcomSubsystemBitStringPosition_RLH             = 8,
  ETcomSubsystemBitStringPosition_TcomSubscriber  = 9,
  ETcomSubsystemBitStringPosition_TLH             = 10,
  ETcomSubsystemBitStringPosition_TNR             = 11,
  ETcomSubsystemBitStringPosition_TOAM            = 12,
  ETcomSubsystemBitStringPosition_TTM             = 13,
  ETcomSubsystemBitStringPosition_WRC             = 14,
  ETcomSubsystemBitStringPosition_Invalid         = 31
} ETcomSubsystemBitStringPosition;

#endif /* _E_TCOM_SUBSYSTEM_BIT_STRING_POSITION_H */

/**
*******************************************************************************
* @enum ETcomSubsystemBitStringPosition
*
* Description         : Least significant bit position that corresponds to a TCOM subsystem in a TTcomSubsystemBitString
*
* Reference           : https://confluence.int.net.nokia.com/display/CpPta/Explicit+addresses+in+TC_WAM_ADDRESS_IND_MSG
*
* @param ETcomSubsystemBitStringPosition_BchSender : BCH Sender bit position
* @param ETcomSubsystemBitStringPosition_CCHH      : CCHH bit position
* @param ETcomSubsystemBitStringPosition_CMEAS     : CMEAS bit position
* @param ETcomSubsystemBitStringPosition_DMEAS     : DMEAS bit position
* @param ETcomSubsystemBitStringPosition_DMGR      : DMGR bit position
* @param ETcomSubsystemBitStringPosition_GRM       : GRM bit position
* @param ETcomSubsystemBitStringPosition_HSCH      : HSCH bit position
* @param ETcomSubsystemBitStringPosition_LRM       : LRM bit position
* @param ETcomSubsystemBitStringPosition_RLH       : RLH bit position
* @param ETcomSubsystemBitStringPosition_TcomSubscriber : Tcom Subscriber bit position
* @param ETcomSubsystemBitStringPosition_TLH       : TLH bit position
* @param ETcomSubsystemBitStringPosition_TNR       : TNR bit position
* @param ETcomSubsystemBitStringPosition_TOAM      : TOAM bit position
* @param ETcomSubsystemBitStringPosition_TTM       : TTM bit position
* @param ETcomSubsystemBitStringPosition_WRC       : WRC bit position
* @param ETcomSubsystemBitStringPosition_Invalid   : Invalid Task bit position
*
* Additional Information :
*
* Definition Provided by : Telecom
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
*******************************************************************************/

