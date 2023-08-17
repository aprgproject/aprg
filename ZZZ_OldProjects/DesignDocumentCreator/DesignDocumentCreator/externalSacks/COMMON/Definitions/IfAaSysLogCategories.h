#ifndef _LOGGING_CATEGORIES_H
#define _LOGGING_CATEGORIES_H

#include <ERadSwDomain.h>

/**
 * @brief  Macro combines domain and CC&S R&D parameters.
 */
#define RAD_EXTLOG(value) RAD_SW_DOMAIN(ERadSwDomain_ExtLogging, value)

/**
 * @brief Extended Logging Categories names
 */
enum ERadLoggingCategory
{
    ERadLoggingCategory_Startup                 = RAD_EXTLOG(0),
    ERadLoggingCategory_Commissionin            = RAD_EXTLOG(1),
    ERadLoggingCategory_Baseband                = RAD_EXTLOG(2),
    ERadLoggingCategory_Testing                 = RAD_EXTLOG(3),
    ERadLoggingCategory_TechnicalReporting      = RAD_EXTLOG(4),
    ERadLoggingCategory_SoftwareUpdate          = RAD_EXTLOG(5),
    ERadLoggingCategory_StateManagement         = RAD_EXTLOG(6),
    ERadLoggingCategory_Recovery                = RAD_EXTLOG(7),
    ERadLoggingCategory_Synchronization         = RAD_EXTLOG(8),
    ERadLoggingCategory_InternalCommunication   = RAD_EXTLOG(9),
    ERadLoggingCategory_ClimateControl          = RAD_EXTLOG(10),
    ERadLoggingCategory_AntennaDeviceManagement = RAD_EXTLOG(11),
    ERadLoggingCategory_DDAL                    = RAD_EXTLOG(12),
    ERadLoggingCategory_Last // end of enum
};

/**
 * @brief Extended Logging Categories levels
 */
enum ERadLoggingLevel
{
    ERadLoggingLevel_Off,
    ERadLoggingLevel_Basic,
    ERadLoggingLevel_Extended,
    ERadLoggingLevel_Full
};

#endif
