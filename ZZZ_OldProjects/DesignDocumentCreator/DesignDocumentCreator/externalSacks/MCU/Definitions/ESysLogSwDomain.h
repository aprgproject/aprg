/** @file
 *  @brief Contains enumeration for AaSysLog sw domains
 *
 *  $HeadURL$
 *  $LastChangedRevision$
 *  $LastChangedDate$
 *  $Author$
 *  $Copyright: Copyright 2019 Nokia. All rights reserved.$
 */

#ifndef CCS_E_SYS_LOG_SW_DOMAIN_H
#define CCS_E_SYS_LOG_SW_DOMAIN_H

/**
 * @brief Enumeration for AaSysLog sw domains
 */
typedef enum ESysLogSwDomain
{
    ESysLogSwDomain_Default                 = 0,  /*<< default log domain */
    ESysLogSwDomain_Telecom                 = 1,  /*<< Telecom log domain */
    ESysLogSwDomain_CPlane                  = 2,  /*<< COMMON CPlane log domain */
    ESysLogSwDomain_Oam                     = 3,  /*<< O&M log domain */
    ESysLogSwDomain_Trs                     = 4,  /*<< TRSW log domain */
    ESysLogSwDomain_CPlaneCentral           = 5,  /*<< LTE CPlane log domain for UEC/CELLC application */
    ESysLogSwDomain_CPlaneDistributed       = 6,  /*<< LTE CPlane log domain for RROM/ENBC/TUPC/MCEC application */
    ESysLogSwDomain_Bm                      = 7,  /*<< BM log domain */
    ESysLogSwDomain_Rfsw                    = 8,  /*<< RF SW log domain on FSM (FZM/FlexiLite) */
    ESysLogSwDomain_Tupc                    = 9,  /*<< TUPC log domain */
    ESysLogSwDomain_Zson                    = 10, /*<< ZSON log domain */
    ESysLogSwDomain_System                  = 11, /*<< System log domain. Reserved for SYSTEM level log prints */
    ESysLogSwDomain_SnapshotFreeze          = 12, /*<< Snapshot freeze log domain. Reserved for backup syslog buffer during snapshot collection */
    ESysLogSwDomain_OamState                = 13, /*<< O&M state change log domain */
    ESysLogSwDomain_Rcp                     = 14, /*<< RCP log domain */
    ESysLogSwDomain_RcpFm                   = 15, /*<< RCP_fm log domain */
    ESysLogSwDomain_RcpPm                   = 16, /*<< RCP_pm log domain */
    ESysLogSwDomain_RcpGivaxi               = 17, /*<< RCP_givaxi log domain */
    ESysLogSwDomain_RcpLwsd                 = 18, /*<< RCP_lwsd log domain */
    ESysLogSwDomain_RcpProvider             = 19, /*<< RCP_provider log domain */
    ESysLogSwDomain_Lfs                     = 20, /*<< LFS log domain */
    ESysLogSwDomain_Hwapi                   = 21, /*<< HWAPI log domain */
    ESysLogSwDomain_CPlaneIfSctp            = 22, /*<< 5G CPlane sctp interface log domain */
    ESysLogSwDomain_CPlaneIfX2              = 23, /*<< 5G CPlane x2 interface log domain */
    ESysLogSwDomain_CPlaneIfXn              = 24, /*<< 5G CPlane xn interface log domain */
    ESysLogSwDomain_CPlaneIfF1              = 25, /*<< 5G CPlane f1 interface log domain */
    ESysLogSwDomain_CPlaneIfE1              = 26, /*<< 5G CPlane e1 interface log domain */
    ESysLogSwDomain_CPlaneIfNg              = 27, /*<< 5G CPlane ng interface log domain */
    ESysLogSwDomain_CPlaneSb                = 28, /*<< 5G CPlane sb log domain */
    ESysLogSwDomain_Smalite                 = 29, /*<< SMALite log domain */
    ESysLogSwDomain_TraceControllerMaster   = 30, /*<< Trace controller master domain */
    ESysLogSwDomain_RcpSysComDataProvider   = 31, /*<< RCP_SysComDataProvider log domain */
    ESysLogSwDomain_RcpLwsdl                = 32, /*<< RCP_lwsdl log domain */
    ESysLogSwDomain_NotValid                /*<< Last enum entry */
} ESysLogSwDomain;

#endif /* CCS_E_SYS_LOG_SW_DOMAIN_H */

