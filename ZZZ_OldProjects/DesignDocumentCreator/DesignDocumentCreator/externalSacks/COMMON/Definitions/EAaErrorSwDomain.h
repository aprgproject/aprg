/** @file
 *  @brief Contains EAaErrorSwDomain enum
 *
 *  $HeadURL$
 *  $LastChangedRevision$
 *  $LastChangedDate$
 *  $Author$
 *  $Copyright: Copyright 2017 Nokia. All rights reserved.$
 */

#ifndef CCS_E_AA_ERROR_SW_DOMAIN_H
#define CCS_E_AA_ERROR_SW_DOMAIN_H

#define AAERROR_SW_DOMAIN_BITS  16
#define AAERROR_SW_DOMAIN(__domain, __code) ((__domain) << AAERROR_SW_DOMAIN_BITS | (__code))

/**
 * @brief Enumeration for AaError sw domains
 */
typedef enum EAaErrorSwDomain
{
    EAaErrorSwDomain_Internal = 0,      /*<< Domain for AaError internal codes */
    EAaErrorSwDomain_Ccs      = 1,      /*<< CCS error code domain */
    EAaErrorSwDomain_Hwapi    = 2,      /*<< HWAPI error code domain */
    EAaErrorSwDomain_Trs      = 3,      /*<< TRS Error */
    EAaErrorSwDomain_LteDlPhy    = 4,   /*<< DL_PHY error codes */
    EAaErrorSwDomain_LteUlPhy    = 5,   /*<< UL_PHY error codes */
    EAaErrorSwDomain_LteUlPhyTdd = 6,   /*<< UL_PHY_TDD error codes */
    EAaErrorSwDomain_LteLom      = 7,   /*<< LOM error codes */
    EAaErrorSwDomain_LteL2       = 8,   /*<< L2 error codes */
    EAaErrorSwDomain_LteMacData  = 9,   /*<< MAC_DATA_PHY error codes */
    EAaErrorSwDomain_LteTupu     = 10,  /*<< TUPU error codes */
    EAaErrorSwDomain_LteMacPsWmp = 11,  /*<< MAC_PS_WMP error codes */
    EAaErrorSwDomain_LteMacPsDcm = 12,  /*<< MAC_PS_DCM error codes */
    EAaErrorSwDomain_LteMacPsTdd = 13,  /*<< MAC_PS_TDD error codes */
    EAaErrorSwDomain_Uphwapi     = 14,  /*<< UPHWAPI error code domain */
    EAaErrorSwDomain_Last               /*<< Not usable value, leave always to last! */
} EAaErrorSwDomain;

#endif /* CCS_E_AA_ERROR_SW_DOMAIN_H */

