/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/SEDchDlCtrlChChangeInfo.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Michal Grodzki
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _S_EDCH_DL_CTRL_CH_CHANGE_INFO_H
#define _S_EDCH_DL_CTRL_CH_CHANGE_INFO_H

#include <TRadioLinkId.h>

struct SEDchDlCtrlChChangeInfo
{
    TRadioLinkId    eDchRlId;
};

typedef struct SEDchDlCtrlChChangeInfo SEDchDlCtrlChChangeInfo;

#endif /* _S_EDCH_DL_CTRL_CH_CHANGE_INFO_H */

/**
*******************************************************************************
* @struct SEDchDlCtrlChChangeInfo
* Description         : E-DCH DL Control Channel Change Information
*
* Reference           : WCDMA BTS SW DSP SW - MCU SW INTERFACE SPECIFICATION
*
* @param eDchRlId               : E-DCH RL ID
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : DSP
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
********************************************************************************/


