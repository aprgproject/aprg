/** @file
*   @brief Contains ERadSwDomain enum
*   @copyright 2018, 2019 Nokia. All rights reserved.
*/

#ifndef CCS_ERAD_SW_DOMAIN_H
#define CCS_ERAD_SW_DOMAIN_H

#include <ERadDomain.h>

#define RAD_SW_DOMAIN_BITS              16
#define RAD_SW_DOMAIN(domain, radValue) (domain << RAD_SW_DOMAIN_BITS | radValue)

/**
 * @brief Enumeration for R&D sw domains
 */
typedef enum ERadSwDomain
{
    ERadSwDomain_Legacy              = ERadDomain_Legacy,       /*<< BTS old R&D parameter (sw_conf_table) */
    ERadSwDomain_Ccs                 = ERadDomain_Ccs,          /*<< CCS depended parameters */
    ERadSwDomain_HwApi               = ERadDomain_HwApi,        /*<< HWAPI depended parameters */
    ERadSwDomain_Dft                 = ERadDomain_Dft,          /*<< DFT depended parameters */
    ERadSwDomain_Telecom             = ERadDomain_Telecom,
    ERadSwDomain_TUP                 = ERadDomain_TUP,
    ERadSwDomain_DSPCodec            = ERadDomain_DSPCodec,
    ERadSwDomain_DSPRake             = ERadDomain_DSPRake,
    ERadSwDomain_DSPMac_hs           = ERadDomain_DSPMac_hs,
    ERadSwDomain_DSPHsupaL2          = ERadDomain_DSPHsupaL2,
    ERadSwDomain_LteMac              = ERadDomain_LteMac,
    ERadSwDomain_LteMacUl            = ERadDomain_LteMacUl,
    ERadSwDomain_LteMacDl            = ERadDomain_LteMacDl,
    ERadSwDomain_LteTupUl            = ERadDomain_LteTupUl,
    ERadSwDomain_LteTupDl            = ERadDomain_LteTupDl,
    ERadSwDomain_LteCellC            = ERadDomain_LteCellC,
    ERadSwDomain_LteCommon           = ERadDomain_LteCommon,
    ERadSwDomain_LteEnbc             = ERadDomain_LteEnbc,
    ERadSwDomain_LteRrom             = ERadDomain_LteRrom,
    ERadSwDomain_LteUec              = ERadDomain_LteUec,
    ERadSwDomain_LteLom              = ERadDomain_LteLom,
    ERadSwDomain_LteTupC             = ERadDomain_LteTupC,
    ERadSwDomain_LteUlPhy            = ERadDomain_LteUlPhy,
    ERadSwDomain_LteDlPhy            = ERadDomain_LteDlPhy,
    ERadSwDomain_LteSmc              = ERadDomain_LteSmc,
    ERadSwDomain_Oam                 = ERadDomain_Oam,          /*<< OAM domain for O&M internal usage*/
    ERadSwDomain_Trs                 = ERadDomain_Trs,
    ERadSwDomain_DspHwApi            = ERadDomain_DspHwApi,     /*<< DSP HWAPI depended parameters */
    ERadSwDomain_Lom                 = ERadDomain_Lom,
    ERadSwDomain_LteMacTddPs         = ERadDomain_LteMacTddPs,
    ERadSwDomain_LteMacFddPs         = ERadDomain_LteMacFddPs,
    ERadSwDomain_LteMacDcmPs         = ERadDomain_LteMacDcmPs,
    ERadSwDomain_LteMacPsCommon      = ERadDomain_LteMacPsCommon,
    ERadSwDomain_BM                  = ERadDomain_BM,
    ERadSwDomain_HwApiState          = ERadDomain_HwApiState,
    ERadSwDomain_ExtLogging          = ERadDomain_ExtLogging,
    ERadSwDomain_DspLtcom            = ERadDomain_DspLtcom,
    ERadSwDomain_DspMm               = ERadDomain_DspMm,
    ERadSwDomain_DspRakeDch          = ERadDomain_DspRakeDch,
    ERadSwDomain_DspRakeRach         = ERadDomain_DspRakeRach,
    ERadSwDomain_DspFp               = ERadDomain_DspFp,
    ERadSwDomain_DspHsTup            = ERadDomain_DspHsTup,
    ERadSwDomain_DspPic              = ERadDomain_DspPic,
    ERadSwDomain_DspW1PLRx           = ERadDomain_DspW1PLRx,
    ERadSwDomain_DspW1PLTx           = ERadDomain_DspW1PLTx,
    ERadSwDomain_TupC                = ERadDomain_TupC,
    ERadSwDomain_HwApiOmIface        = ERadDomain_HwApiOmIface,
    ERadSwDomain_LIM                 = ERadDomain_LIM,
    ERadSwDomain_LteCellP            = ERadDomain_LteCellP,
    ERadSwDomain_LteFaReCo           = ERadDomain_LteFaReCo,
    ERadSwDomain_LteSysAdapter       = ERadDomain_LteSysAdapter,
    ERadSwDomain_LteMOAM             = ERadDomain_LteMOAM,
    ERadSwDomain_LteBSTAT            = ERadDomain_LteBSTAT,
    ERadSwDomain_Rfsw                = ERadDomain_Rfsw,
    ERadSwDomain_SWIM                = ERadDomain_SWIM,
    ERadSwDomain_TddCpri             = ERadDomain_TddCpri,
    ERadSwDomain_LteMcec             = ERadDomain_LteMcec,
    ERadSwDomain_RtHwApi             = ERadDomain_RtHwApi,      /*<< RT HWAPI depended parameters */
    ERadSwDomain_InfoModelGw         = ERadDomain_InfoModelGw,
    ERadSwDomain_FjRhPhy             = ERadDomain_FjRhPhy,
    ERadSwDomain_UpHwApi             = ERadDomain_UpHwApi,
    ERadSwDomain_LteEnbson           = ERadDomain_LteEnbson,
    ERadSwDomain_LteCellson          = ERadDomain_LteCellson,
    ERadSwDomain_CcsMcu              = ERadDomain_CcsMcu,
    ERadSwDomain_EmServices          = ERadDomain_EmServices,
    ERadSwDomain_LteTupCommon        = ERadDomain_LteTupCommon,
    ERadSwDomain_LteDCS              = ERadDomain_LteDCS,
    ERadSwDomain_LteMCTRL            = ERadDomain_LteMCTRL,
    ERadSwDomain_PhyProxy            = ERadDomain_PhyProxy,
    ERadSwDomain_OamUri              = ERadDomain_OamUri,
    ERadSwDomain_OamCci              = ERadDomain_OamCci,
    ERadSwDomain_OamMci              = ERadDomain_OamMci,
    ERadSwDomain_OamDem              = ERadDomain_OamDem,
    ERadSwDomain_OamCem              = ERadDomain_OamCem,
    ERadSwDomain_OamRem              = ERadDomain_OamRem,
    ERadSwDomain_OamSwm              = ERadDomain_OamSwm,
    ERadSwDomain_OamCas              = ERadDomain_OamCas,
    ERadSwDomain_OamLts              = ERadDomain_OamLts,
    ERadSwDomain_OamGts              = ERadDomain_OamGts,
    ERadSwDomain_OamHas              = ERadDomain_OamHas,
    ERadSwDomain_OamFri              = ERadDomain_OamFri,
    ERadSwDomain_OamSds              = ERadDomain_OamSds,
    ERadSwDomain_OamTas              = ERadDomain_OamTas,
    ERadSwDomain_OamWts              = ERadDomain_OamWts,
    ERadSwDomain_LteSasProxy         = ERadDomain_LteSasProxy,
    ERadSwDomain_OamInct             = ERadDomain_OamInct,
    ERadSwDomain_LteL1Low            = ERadDomain_LteL1Low,
    ERadSwDomain_5GL2LO              = ERadDomain_5GL2LO,
    ERadSwDomain_5GL2PS              = ERadDomain_5GL2PS,
    ERadSwDomain_5GCPRT              = ERadDomain_5GCPRT,
    ERadSwDomain_5GL2HiCu            = ERadDomain_5GL2HiCu,
    ERadSwDomain_5GL2HiDu            = ERadDomain_5GL2HiDu,
    ERadSwDomain_5GAirphone          = ERadDomain_5GAirphone,
    ERadSwDomain_NodeOAM             = ERadDomain_NodeOAM,
    ERadSwDomain_RACOAM              = ERadDomain_RACOAM,
    ERadSwDomain_SiteOAM             = ERadDomain_SiteOAM,
    ERadSwDomain_OamNrts             = ERadDomain_OamNrts,
    ERadSwDomain_OamNe3sAdapter      = ERadDomain_OamNe3sAdapter,
    ERadSwDomain_SMALiteXoh          = ERadDomain_SMALiteXoh,
    ERadSwDomain_SMALiteFileTransfer = ERadDomain_SMALiteFileTransfer,
    ERadSwDomain_5GCpuDataCollector  = ERadDomain_5GCpuDataCollector,
    ERadSwDomain_DSPGsm              = ERadDomain_DSPGsm,
    ERadSwDomain_5GCPNRT             = ERadDomain_5GCPNRT,
    ERadSwDomain_CRM                 = ERadDomain_CRM,
    ERadSwDomain_DspSlaveRach        = ERadDomain_DspSlaveRach,
    ERadSwDomain_Last                /*<< Not usable value, leave always to last! */
} ERadSwDomain;

#endif /* CCS_ERAD_SW_DOMAIN_H */

