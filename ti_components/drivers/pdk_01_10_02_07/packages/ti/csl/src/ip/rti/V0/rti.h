/*
 *   Copyright (c) Texas Instruments Incorporated 2015
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/**
 *  \ingroup CSL_IP_MODULE
 *  \defgroup CSL_RTI RTI
 *
 *  @{
 */
/**
 *  \file     rti.h
 *
 *  \brief    This file contains the prototypes of the APIs present in the
 *            device abstraction layer file of RTI.
 *            This also contains some related macros.
 */

/**
 *         Digital Windowed Watchdog(DWWD) Overview :
 *         The Digital Watchdog Timer(DWT) generates reset after a programmable
 *         period, if not serviced within that period. In DWT, time-out
 *         boundary is configurable.
 *         In DWWD, along with configurable time-out boundary, the start time
 *         boundary is also configurable. The DWWD can generate Reset or
 *         Interrupt, if not serviced within window(Open Window) defined by
 *         start time and time-out boundary. Also the DWWD can generate Reset or
 *         Interrupt if serviced outside Open Window (within Closed Window).
 *         Generation of Reset or Interrupt depends on the DWWD Reaction
 *         configuration.
 */
/**
 *         DWWD Down Counter Overview :
 *         24............................................2 1 0
 *         |                25 bit down counter              |
 *         |_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|
 *         |  12 bit preload value |1|1|1|1|1|1|1|1|1|1|1|1|1|
 *         |-----------------------|-|-|-|-|-|-|-|-|-|-|-|-|-|
 *         Upper 12 bit part of the down counter is configurable and
 *         remaining 13 bit are always 1.
 *         Minimum possible time-out value is 2^13 RTI clock cycles.
 *         Maximum possible time-out value is 2^25 RTI clock cycles.
 *         Example :
 *         RTI frequency : 32kHz
 *         12 bit preload value : 0x004
 *         25 bit preload value : 0x0009FFF
 *         time-out value(in RTI clock cycles) : 40959.
 *         time-out value(in seconds) : 40959 / 32000 = 1.26859375 seconds.
 */
/**
 *         DWWD Window Sizes Overview :
 *          time-out value...........................................3 2 1 0
 *    (100%)|___________________________Open Window________________________|
 *     (50%)|         Closed Window         |________Open Window___________|
 *     (25%)|            Closed Window                      |___OW_________|
 *   (12.5%)|                 Closed Window                         |_OW___|
 *   (6.25%)|                     Closed Window                         |OW|
 *  (3.125%)|                         Closed Window                      |O|
 *                                                                       |W|
 *         For time-out value calculation refer DWWD Down Counter Overview.
 */
#ifndef RTI_H_
#define RTI_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/csl/cslr_rti.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/**
 * \brief  Minimum possible preload value for RTI DWD counter (2^13).
 */
#define RTI_DWD_MIN_PRELOAD_VAL             (0x1FFFU)
/**
 * \brief  Maximum possible preload value for RTI DWD counter(2^25).
 */
#define RTI_DWD_MAX_PRELOAD_VAL             (0x1FFFFFFU)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 * \brief  Enum to select the DWWD reaction after violation or
 *         expiration of DWWD timer.
 *
 *         DWWD can either generate reset or interrupt.
 */
typedef enum rtiDwwdReaction
{
    RTI_DWWD_REACTION_GENERATE_RESET = RTI_RTIDWWDRXNCTRL_DWWDRXN_RESET,
    /**< Configure DWWD reaction to generate reset */
    RTI_DWWD_REACTION_GENERATE_NMI = RTI_RTIDWWDRXNCTRL_DWWDRXN_INTERRUPT
                                     /**< Configure DWWD reaction to generate
                                      * interrupt. The actual interrupt
                                      * used depends on the SOC and cross bar
                                      * mapping. */
}rtiDwwdReaction_t;

/**
 * \brief  Enum to select the DWWD window size.
 *
 *         Window Size : In what percentage of time-out value i.e open window,
 *         servicing DWWD is allowed.
 *         Configurable Window Sizes : 100%, 50%, 25%, 12.5%, 6.25%, 3.125%.
 *         Refer to DWWD Window Sizes Overview.
 */
typedef enum rtiDwwdWindowSize
{
    RTI_DWWD_WINDOWSIZE_100_PERCENT = RTI_RTIDWWDSIZECTRL_DWWDSIZE_100_PERCENT,
    /**< Configure DWWD window size to 100% */
    RTI_DWWD_WINDOWSIZE_50_PERCENT = RTI_RTIDWWDSIZECTRL_DWWDSIZE_50_PERCENT,
    /**< Configure DWWD window size to 50% */
    RTI_DWWD_WINDOWSIZE_25_PERCENT = RTI_RTIDWWDSIZECTRL_DWWDSIZE_25_PERCENT,
    /**< Configure DWWD window size to 25% */
    RTI_DWWD_WINDOWSIZE_12_5_PERCENT =
        RTI_RTIDWWDSIZECTRL_DWWDSIZE_12_5_PERCENT,
    /**< Configure DWWD window size to 12.5`% */
    RTI_DWWD_WINDOWSIZE_6_25_PERCENT =
        RTI_RTIDWWDSIZECTRL_DWWDSIZE_6_25_PERCENT,
    /**< Configure DWWD window size to 6.25% */
    RTI_DWWD_WINDOWSIZE_3_125_PERCENT =
        RTI_RTIDWWDSIZECTRL_DWWDSIZE_3_125_PERCENT
        /**< Configure DWWD window size to 3.125% */
}rtiDwwdWindowSize_t;

/**
 * \brief  Enum to report the DWWD status.
 *
 *         Violations(Following bit-field will get set) :
 *         DWWD Status : If last reset is generated by DWWD.
 *         Key sequence violation : If wrong sequence is written to enable DWWD.
 *         Start Time Violation : If DWWD is serviced within closed window.
 *         End Time Violation : If DWWD is not serviced.
 *         Time Window Violation : If any of Start/End Time Violation happened.
 */
typedef enum rtiDwwdStatus
{
    RTI_DWWD_STATUS_KEY_SEQ_VIOLATION = RTI_RTIWDSTATUS_KEYST_MASK,
    /**< Key sequence violation mask */
    RTI_DWWD_STATUS_TIME_WINDOW_VIOLATION = RTI_RTIWDSTATUS_DWWD_ST_MASK,
    /**< Window violation mask */
    RTI_DWWD_STATUS_ENDTIME_WINDOW_VIOLATION =
        RTI_RTIWDSTATUS_END_TIME_VIOL_MASK,
    /**< End time window violation mask */
    RTI_DWWD_STATUS_STARTTIME_WINDOW_VIOLATION =
        RTI_RTIWDSTATUS_START_TIME_VIOL_MASK,
    /**< End time window violation mask */
    RTI_DWWD_STATUS_LAST_RESET = RTI_RTIWDSTATUS_DWDST_MASK
                                 /**< DWWD last reset status mask */
}rtiDwwdStatus_t;

/**
 * \brief  Enum to get the status of last reset.
 */
typedef enum rtiDwwdResetStatus
{
    RTI_DWWD_RESET_STATUS_GENERATED,
    /**< Last reset is generated by DWWD */
    RTI_DWWD_RESET_STATUS_NOT_GENERATED
    /**< Last reset is not generated by DWWD */
}rtiDwwdResetStatus_t;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   Configure DWWD before enabling.
 *
 * \param   baseAddr        Base Address of the RTI instance.
 *
 * \param   dwwdReaction    DWWD reaction for violation/expiration.
 *                          Values given by enum #rtiDwwdReaction_t
 *
 * \param   dwwdPreloadVal  Down counter preload value. This preload value is
 *                          time-out period in terms of number of clock cycles
 *                          of RTI clock source. This is 25 bit value
 *                          in the range 0x1FFFU to 0x1FFFFFFU.
 *                          - Refer DWWD Down Counter Overview.
 *
 * \param   dwwdWindowSize  DWWD window size
 *                          Values given by enum #rtiDwwdWindowSize_t
 *
 * \return  status          Success of the window configuration
 */
int32_t RTIDwwdWindowConfig(uint32_t baseAddr,
                            uint32_t dwwdReaction,
                            uint32_t dwwdPreloadVal,
                            uint32_t dwwdWindowSize);

/**
 * \brief   Enable DWWD down counter
 *
 * \param   baseAddr        Base Address of the RTI instance.
 *
 * \return  None.
 *
 * \note    This API should be called after configuration of DWWD Window.
 */

void RTIDwwdCounterEnable(uint32_t baseAddr);

/**
 * \brief   Check if DWWD down counter was enabled
 *
 * \param   baseAddr        Base Address of the RTI instance.
 *
 * \return  status          TRUE if counter is enabled.
 *                          FALSE if counter is not enabled.
 *
 * \note    This API should be called after configuration of DWWD Window.
 */

uint32_t RTIDwwdIsCounterEnabled(uint32_t baseAddr);

/**
 * \brief   Service DWWD.
 *
 * \param   baseAddr        Base Address of the RTI instance.
 *
 * \return  None.
 */
void RTIDwwdService(uint32_t baseAddr);

/**
 * \brief   Get DWWD Reset status.
 *          Last reset is generated by DWWD or not.
 *
 * \param   baseAddr        Base Address of the RTI instance.
 *
 * \return  status          Last reset status.
 *                          Values given by enum #rtiDwwdResetStatus_t
 */
rtiDwwdResetStatus_t RTIDwwdGetLastResetStatus(uint32_t baseAddr);

/**
 * \brief   Set DWWD preload value.
 *          From this value down counter starts down counting.
 *
 * \param   baseAddr        Base Address of the RTI instance.
 *
 * \param   dwwdPreloadVal  Down counter preload value.
 *                          Refer DWWD Down Counter Overview.
 *
 * \return  status          Success of DWWD preload value setting.
 */
int32_t RTIDwwdSetPreload(uint32_t baseAddr, uint32_t dwwdPreloadVal);

/**
 * \brief   Set DWWD reaction.
 *
 * \param   baseAddr        Base Address of the RTI instance.
 *
 * \param   dwwdReaction   DWWD reaction for violation/expiration.
 *                         Values given by enum #rtiDwwdReaction_t
 *
 * \return  None.
 *
 * \note:   1. DWWD need to be serviced if Reaction is changed when DWWD is
 *          enabled and Window is Open,to take immediate effect. If not
 *          serviced, DWWD will generated previously configured Reaction
 *          irrespective of current configuration.
 *          2. If DWWD is enabled and Window is Close then any change in
 *          Reaction will take immediate effect. DWWD need not to be serviced
 *          in this case.
 */
void RTIDwwdSetReaction(uint32_t baseAddr, uint32_t dwwdReaction);

/**
 * \brief   Set DWWD Window Size.
 *
 * \param   baseAddr        Base Address of the RTI instance.
 *
 * \param   dwwdWindowSize  DWWD Window Size.
 *                          Values given by enum #rtiDwwdWindowSize_t
 *
 * \return  None.
 *
 * \note:   1. DWWD need to be serviced if Window Size is changed when DWWD is
 *          enabled and Window is Open,to take immediate effect. If not
 *          serviced, DWWD Window Size will not be changed
 *          irrespective of current configuration.
 *          2. If DWWD is enabled and Window is Close then any change in
 *          Window Size will take immediate effect. DWWD need not to be serviced
 *          in this case.
 */
void RTIDwwdSetWindowSize(uint32_t baseAddr, uint32_t dwwdWindowSize);

/**
 * \brief   Check for Closed Window.
 *
 * \param   baseAddr        Base Address of the RTI instance.
 *
 * \return  status          Closed Window Status
 *                          TRUE if Window is Closed. FALSE if Window is Open.
 */
uint32_t RTIDwwdIsClosedWindow(uint32_t baseAddr);

/**
 * \brief   Generate forced system reset/interrupt.
 *          Depends upon DWWD reaction what to generate
 *
 * \param   baseAddr        Base Address of the RTI instance.
 *
 * \return  None.
 */
void RTIDwwdGenerateSysReset(uint32_t baseAddr);

/**
 * \brief   Get DWWD status.
 *
 * \param   baseAddr        Base Address of the RTI instance.
 *
 * \return  DWWD status     DWWD status. Refer enum #rtiDwwdStatus_t for
 *                          possible bitwise or of all return values.
 */
uint32_t RTIDwwdGetStatus(uint32_t baseAddr);

/**
 * \brief   Clear DWWD status.
 *
 * \param   baseAddr        Base Address of the RTI instance.
 *
 * \param   status          Violation status to clear.
 *                          Values given by bitwise or of enum #rtiDwwdStatus_t
 *
 * \return  None.
 */
void RTIDwwdClearStatus(uint32_t baseAddr, uint32_t status);

/**
 * \brief   Get current value of DWWD down counter.
 *
 * \param   baseAddr        Base Address of the RTI instance.
 *
 * \return  counter value   DWWD down counter register value.
 */
uint32_t RTIDwwdGetCurrentDownCounter(uint32_t baseAddr);

/**
 * \brief   Check for correct sequence write to DWWD key Register.
 *
 * \param   baseAddr        Base Address of the RTI instance.
 *
 * \return  status          RTI key sequence status.
 */
uint32_t RTIIsDwwdKeySequenceCorrect(uint32_t baseAddr);

/* ========================================================================== */
/*                          Advance Functions                                 */
/* ========================================================================== */
/**
 * \brief   This API will return current configured Preload value.
 *
 * \param   baseAddr        Base Address of the RTI instance.
 *
 * \return  Preload         Configured preload value.
 */
uint32_t RTIDwwdGetPreload(uint32_t baseAddr);

/**
 * \brief   This API will return current configured Window Size.
 *
 * \param   baseAddr        Base Address of the RTI instance.
 *
 * \return  Window Size     Configured Window Size.
 *                          Refer enum #rtiDwwdWindowSize_t
 */
uint32_t RTIDwwdGetWindowSize(uint32_t baseAddr);

/**
 * \brief   This API will return current configured time out
 *          (number of clock cycles of RTI clock) value.
 *
 * \param   baseAddr        Base Address of the RTI instance.
 *
 * \return  time-out        Configured time out value.
 */
uint32_t RTIDwwdGetTimeOut(uint32_t baseAddr);

/**
 * \brief   This API will return current configured Reaction.
 *
 * \param   baseAddr        Base Address of the RTI instance.
 *
 * \return  Reaction        Configured Reaction.
 *                          Refer enum #rtiDwwdReaction_t
 */
uint32_t RTIDwwdGetReaction(uint32_t baseAddr);

/**
 * \brief   This API returns the number of clock cycles of RTI clock remaining
 *          for the Window to Open.
 *
 * \param   baseAddr        Base Address of the RTI instance.
 *
 * \return  Clock cycles    Clock cycles remaining for Open Window.
 *                          Returns '0' if Window is already Open.
 *
 * \note    Number of clock cycles returned by this API may differ from actual
 *          clock cycles needed for Window to open, User should also check
 *          if window is open or not before doing any further operation.
 *          For this purpose user can use RTIDwwdIsClosedWindow() API.
 */
uint32_t RTIDwwdGetTicksToOpenWindow(uint32_t baseAddr);

#ifdef __cplusplus
}
#endif

#endif /* RTI_H_ */
 /** @} */
