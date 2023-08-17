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
#ifndef _E_TCOM_INSTANCE_POSITION_H
#define _E_TCOM_INSTANCE_POSITION_H

typedef enum ETcomInstancePosition
{
  ETcomInstancePosition_Slave   = 0,
  ETcomInstancePosition_Master  = 1
} ETcomInstancePosition;

#endif /* _E_TCOM_INSTANCE_POSITION_H */

/**
*******************************************************************************
* @enum ETcomInstancePosition
*
* Description         : Indicates whether the TCOM instance runs as slave or master.
*
* Reference           : https://confluence.int.net.nokia.com/display/CpPta/Explicit+addresses+in+TC_WAM_ADDRESS_IND_MSG
*
* @param ETcomInstancePosition_Slave  : Slave TCOM Instance
* @param ETcomInstancePosition_Master : Master TCOM Instance
*
* Additional Information :
*
* Definition Provided by : Telecom
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
*******************************************************************************/

