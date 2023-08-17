/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2015 Nokia Networks. All rights reserved.
*******************************************************************************/ 
#ifndef _MCU_IFAASOCKET_H
#define _MCU_IFAASOCKET_H
#include "CcsCommon.h"

/* ---------------------LATEX----------------------------- */
/*
 *
\latexonly

\chapter {Introduction}

 The service AaSocket in CC\&S provides a standard BSD socket interface wrapper over various socket API implementations. Currently supported
 implemetations are:
 \begin{itemize}
    \item OSE INET and OSENET
    \item Interpeak IPLite
    \item Winsock (this one only exists, it isn't supported anymore)
    \item Linux (does not really need support)
    \item DSP IPDrive
  \end{itemize}
  User doesn't need to include these separately, only what he has to do is to include AaSocket and check according implementation through makefiles.
  Though, at the moment is possible to include these separately, but this will be deprecetaed in a future.

\section {Concepts}

\subsection {OSE Inet and OSENET}
OSE Inet comes within the OSE4.6.1. This OSE version is included in
Ultra and Flexi rel1 products. This IP stack is fairly compact and does not have any advanced interfaces
implemented and the BSD interface support is quite minimal.

OSENET comes with the OSE5.3. This OSE version is used in Flexi rel2
products and also in new RF modules.
This new OSE IP stack is much more BSD compliant and also has some more advanced interfaces implemented.


\subsection {IPlite}
Interpeak IPLite is only used in the Rel1 RF modules. In system module
side there are no products which are using this IP stack.

\subsection {Linux}
This is standard BSD socket interface.

\subsection {IPDriver}
This is used on DSP's.

\subsection {Windows}
Socket interface on windows platform - not supported anymore.

\chapter {Runtime Configuration}
Runtime configuration can be divided into pre- and post-configuration phases.
Pre-configuration takes place before CE startup has been done for a service.
Post-configuration takes place after CE, EE and EU startup.
Configuration tags are used for input direction i.e. feeding configuration to CC&S service.
However some tags can also be used for output direction i.e. for advertising CC&S service state or capabilities.

\section  {Pre-configuration}
AaSocket does not have any Pre-configuration tags.

\section  {Post-configuration}
AaSocket does not have any Post-configuration tags.

\section  {R\&D Parameter}
AaSocket does not have any R\&D Parameter tags.

\chapter {AaShell Commands}
AaSocket does not provide any shell commands

\chapter {API Service}

\section {Socket interface}
As it was previously said, AaSocket provides standard BSD socket interface in various enviroments.

\chapter {Message Functional Definition and Content}
AaSocket does not have any Message based communication.

\chapter {Examples}
Since AaSocket gives standard BSD socket interface, there are numerous examples over whole web. There are some examples also in CCS\_Demo,
and also in CCS\_Services (such as AaProdTest - especially testcases give some nice examples how to work with the service)

\chapter {Requirements}
This chapter contains requirements for AaSocket Service API in CC\&S. Requirements are taken from DOORS.

\begin{table}
  \vspace{3pt} \noindent
  \begin{tabular}{| p{.40\textwidth} | p{.25\textwidth} |p{.08\textwidth} | p{.08\textwidth} |}
    \hline
    \textbf{Requirement Name (Object text in DOORS)} & \textbf{Requirement Version (in DOORS)} & \textbf{Chapter} & \textbf{Note} \\ \hline
    BTSC\_CCS\_1105 AaSocket CC\&S SW offers standard BSD socket API compatible socket API. & 1.0  & 5.6 & N/A \\ \hline
    BTSC\_CCS\_1106 Following socket API extension are supported: (there is nothing more) & 1.0  & 5.6 & This one looks like it needs to be added something \\ \hline
    BTSC\_CCS\_1107 TBD & 1.0  & 5.6 & TBD! \\ \hline
  \end{tabular}
\end{table}

\chapter {Further Development  and open Issues}
Windows (winsock) isn't supported anymore. Long term idea is to apply API variability and
put all interfaces files in one common header, but in order to do this, all of the stakeholders need to be
contacted.

\chapter{References \& Abbreviations}

\textbf {Abbreviations }
\begin{table}[H]
 \begin{tabular}{ | p{.25\textwidth} | p{.70\textwidth} | }
 \hline
   -       &   - \\ \hline
   \end{tabular}
\end{table}


\textbf {References }
\begin{table}[H]
    \begin{tabular}{ | p{.30\textwidth} | p{.60\textwidth} |}
        \hline
        \textbf{Identifier} & \textbf{Information} \\
        \hline
        [CCS\_ARCH\_DOC] &
			\begin{list}{\labelitemi}{\leftmargin=1em}
				 \item Name of the document: CC\&S SW Architecture Specification
				 \item Author: Ahola Teemu
				 \item Location: https://sharenet-ims.inside.nokiasiemensnetworks.com/Overview/D-171111
			\end{list}  \\
        \hline
        [CCS\_API\_VARIABILITY] &
			\begin{list}{\labelitemi}{\leftmargin=1em}
				\item Name of the document: CC\&S SW API variations
				\item Location: https://sharenet-ims.inside.nokiasiemensnetworks.com/Properties/396840631
			\end{list} \\
        \hline
        [SERVICE\_REQ] &
  			\begin{list}{\labelitemi}{\leftmargin=1em}
				\item Name of the document: Chapter 5.6
				\item Author: DOORS
			\end{list} \\
        \hline
      \end{tabular}
\end{table}
\endlatexonly
 */

/*----------------------- DOXYGEN GROUPS --------------------------------------*/
/**
* @defgroup dgAaSocketApi API
* @ingroup dgAaSocket
*/
/*----------------------- INCLUDED FILES --------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/**
*@defgroup dgAaSocket Socket Service
*@ingroup dgBasicComputingSw
*
* CC&S Wiki for AaSocket:
*
*
* http://wikis.inside.nokiasiemensnetworks.com/bin/view/CSSWiki/AaSocket
*
*/


// Ignore names of the groups

 /**
 * @addtogroup dgAaSocketApiCommon AaSocket Inet API
 * @ingroup dgAaSocket
 */


 /**
 * @addtogroup dgAaSocketApiMcu AaSocket Linux API
 * @ingroup dgAaSocket
 */


 /**
 * @addtogroup dgAaSocketApiLinux AaSocket IPDriver API
 * @ingroup dgAaSocket
 */


 /**
 * @addtogroup dgAaSocketApiDsp AaSocket Windows API
 * @ingroup dgAaSocket
 */


 /**
 * @addtogroup dgAaSocketApiOse AaSocket IPlite API
 * @ingroup dgAaSocket
 */

  #define AASOCKET_LINUX_STACK /* using BSD compatible stack */
  #include <sys/socket.h>
  #include <unistd.h>
  #include <netinet/in.h>
  #include <sys/un.h>
  #include <net/if.h>
  #include <arpa/inet.h>
  #include <errno.h>
  #include <sys/ioctl.h>
  #include <sys/select.h>

#ifdef __cplusplus
}
#endif

/*----------------------- PUBLIC DECLARATIONS --------------------------------*/
#endif /* _MCU_IFAASOCKET_H */

