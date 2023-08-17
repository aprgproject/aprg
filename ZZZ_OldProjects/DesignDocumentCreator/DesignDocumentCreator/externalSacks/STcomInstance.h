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
#ifndef _S_TCOM_INSTANCE_H
#define _S_TCOM_INSTANCE_H

#include <EControlUnitType.h>
#include <ETcomInstancePosition.h>
#include <IfAaSysCom.h>
#include <TBalancingWeight.h>
#include <TSubrackNbr.h>
#include <TTcomSubsystemBitString.h>
#include <ETcomSubsystemBitStringPosition.h>

struct STcomInstance
{
  TAaSysComNid             nid;
  TBalancingWeight         rlhBalancingWeight;
  EControlUnitType         controlUnitType;
  ETcomInstancePosition    position;
  TTcomSubsystemBitString  subsytemBitString;
  TSubrackNbr              subrackNbr;
};
typedef struct STcomInstance STcomInstance;

#endif /* _S_TCOM_INSTANCE_H */

/**
*******************************************************************************
* @struct STcomInstance
*
* Description         : Contains information of TCOM Instance
*
* Reference           : https://confluence.int.net.nokia.com/display/CpPta/Explicit+addresses+in+TC_WAM_ADDRESS_IND_MSG
*
* @param nid                : Node ID (board and CPU) of the TCOM instance
* @param rlhBalancingWeight : Indicates the balancing weight of a RLH instance.
* @param controlUnitType    : Indicates in what type of control unit the TCOM instance runs on
* @param position           : Indicates whether the TCOM instance runs as slave or master.
* @param subsytemBitString  : Each bit corresponds to a TCOM subsystem.
*                             If a bit is "ON", then the corresponding TCOM subsystem is active.
* @param subrackNbr         : Indicates the Node ID's ordinal number in terms of system module.
*                             Its value is set as 1 if it is on MSM.
*                             Otherwise, it is set as 2 for ESM.
*
* Additional Information :
*
* Definition Provided by : Telecom
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
*******************************************************************************/

