/** @file
*   @brief Common defintions for CC&S
*   @copyright 2016 Nokia Networks. All rights reserved.
*   @copyright 2019 Nokia. All rights reserved.
*/

#ifndef _NEW_CCSCOMMON_H
#define _NEW_CCSCOMMON_H

#define CCS_NEW_IF_STRUCTURE 1 /* User is compiling with new include paths */

/**
*@defgroup dgCommonDefs Common definitions
*@ingroup dgCcs
*
*/
/*@{*/

/* cast macros:
 * CCS_STATIC_CAST used to call static_cast in c++
 * CCS_CONST_CAST used to call const_cast in c++
 * CCS_REINTERPRET_CAST used to call reinterpret_cast in C++
 *
 * Inside C all macros just cast to provided type
 */
#ifdef __cplusplus
    #define CCS_STATIC_CAST(type__, arg__)      (static_cast<type__>(arg__))
    #define CCS_CONST_CAST(type__, arg__)       (const_cast<type__>(arg__))
    #define CCS_REINTERPRET_CAST(type__, arg__) (reinterpret_cast<type__>(arg__))
#else
    #define CCS_STATIC_CAST(type__, arg__)      ((type__)(arg__))
    #define CCS_CONST_CAST(type__, arg__)       ((type__)(arg__))
    #define CCS_REINTERPRET_CAST(type__, arg__) ((type__)(arg__))
#endif


#ifdef __cplusplus
extern "C" {
#endif

/* CCS version check */
/* increment every time there is a modification in CCS which is not backward compatible */
/* version numbers will be checked during domain registration from RadSlave to RadMaster in AaConfig */
#define CCS_VERSION 11
/* Version history
 * version  3: first number of version check, older values 1 and 2 used for file access (obsolete)
 *          4: implementation of service registry (new messages added)
 *          5: SAaConfigRadSyncParams in AaConfig_RadDomainRegistrationReq message modified
 *          6: new public config tag distribution mechanism
 *          7: SvcRegistry update (LBT1504-a2 BTSOM LTE Redesign & Refactoring)
 *          8: add config tag types
 *          9: AACONFIG_SVC_REG_PUBLIC_REG_MSG structure modified)
 *         10: add redundancy implementation
 *         11: AACONFIG_RAD_PARAMS_EXT_GET_REQ_MSG, AACONFIG_RAD_PARAMS_EXT_GET_RESP_MSG,
 *             AACONFIG_RAD_PARAMS_NON_DEFAULT_GET_REQ_MSG, AACONFIG_RAD_PARAMS_NON_DEFAULT_GET_RESP_MSG,
 *             AACONFIG_RAD_PARAMS_EXT_SET_REQ_MSG, AACONFIG_RAD_PARAMS_EXT_SET_RESP_MSG messages added
 */

/** Compiler independent inline defintion
* @def __CCS_INLINE__
*/
#ifndef __CCS_INLINE__
# ifdef _TMS320C6X
#  define __CCS_INLINE__ inline
# else
#  define __CCS_INLINE__ __inline__
# endif
#endif

/*!
 * \def CCS_DEPRECATED(message)
 * \brief A macro that can be used in ddal headers to mark functions and types as deprecated.
 *
 * Unless CCS_DISABLE_DEPRECATED_WARNING is defined, the macro expands to
 * the GNU C "deprecated" attribute that will cause compilation warnings
 * each time the function or type marked with the macro is used
 * (if "-Wdeprecated-declarations" or equivalent option is in effect).
 *
 * If CCS_DISABLE_DEPRECATED_WARNING is defined, the macro expands to nothing,
 * which allows ddal users to selectively disable deprecation warnings, e.g.
 * enable them only for own code.
 *
 * \param message string literal to be included in deprecation warning message
 *
 * The macro should be placed at the end of function declaration or type definition,
 * just before the semicolon.
 */
#ifdef CCS_DISABLE_DEPRECATED_WARNING
  #define CCS_DEPRECATED(message)
#else
  #if !defined(__TCC__)
    #if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 5)
      #define CCS_DEPRECATED(message) \
              __attribute__((__deprecated__(message " (use -DCCS_DISABLE_DEPRECATED_WARNING to disable this warning)")))
    #elif __GNUC__ >= 4
      #define CCS_DEPRECATED(message) \
              __attribute__((__deprecated__))
    #else
      #define CCS_DEPRECATED(message)
    #endif /* __GNUC__ */
  #else
    #define CCS_DEPRECATED(message)
  #endif /* __TCC__ */
#endif /* CCS_DISABLE_DEPRECATED_WARNING */

/*!
 * \def __has_feature(feature)
 * \brief A macro which evaluates to 1 if the feature is both supported by Clang and standardized
 *        in the current language standard or 0 if not.
 *
 * This macro is defined here for compatibility with non-clang compilers.
 */
#if !defined(__TCC__)
  #ifndef __has_feature
      #define __has_feature(x) 0
  #endif /* __has_feature */
#endif /* __TCC__ */

/*!
 * \def CLANG_ANALYZER_NORETURN
 * \brief A macro that can be used to inform clang analyser that function is an assertion handler
 *
 * Macro adds the Clang-specific 'analyzer_noreturn' attribute which is almost identical to 'noreturn'
 * except that it is ignored by the compiler for the purposes of code generation.
 *
 * This attribute is useful for annotating assertion handlers that actually can return, but for the purpose
 * of using the analyzer we want to pretend that such functions do not return.
 *
 * Because this attribute is Clang-specific, its use should be conditioned with the use of preprocessor macros
 */
#ifndef CLANG_ANALYZER_NORETURN
  #if !defined(__TCC__)
    #if __has_feature(attribute_analyzer_noreturn)
      #define CLANG_ANALYZER_NORETURN __attribute__((analyzer_noreturn))
    #else
      #define CLANG_ANALYZER_NORETURN
    #endif /* __has_feature(attribute_analyzer_noreturn) */
  #else
    #define CLANG_ANALYZER_NORETURN
  #endif /* __TCC__ */
#endif /* CLANG_ANALYZER_NORETURN */

/*!
 * \def CCS_NORETURN
 * \brief The macro is used to indicate the function does not return.
 *
 * Unless CCS_NORETURN is defined, since C11 standard the macro
 * expands to noreturn and includes stdnoreturn.h, since C++11
 * the macro expands to noreturn attribute.
 *
 * If CCS_NORETURN is defined or older standards than C11 and C++11 are used,
 * the macro expands to nothing.
 *
 * The macro should be placed at the beginning of function declaration.
 */
#ifndef CCS_NORETURN
  #if defined(__TCC__)
    #define CCS_NORETURN
  #elif defined(__cplusplus) && (__cplusplus >= 201103L)
    #define CCS_NORETURN [[noreturn]] /**< C++ noreturn attribute. */
  #elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
    #include <stdnoreturn.h>
    #define CCS_NORETURN noreturn /**< C noreturn macro. */
  #elif defined(_MSC_VER) && (_MSC_VER >= 1900)
    #define CCS_NORETURN [[noreturn]] /**< C++ noreturn attribute. */
  #else
    #define CCS_NORETURN
  #endif
#endif

#ifdef __cplusplus
}
#endif

/*@}*/

#endif /* _NEW_CCSCOMMON_H */
