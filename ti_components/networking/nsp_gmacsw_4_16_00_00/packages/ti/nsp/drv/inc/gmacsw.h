/*
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*!
 *   \file  gmacsw.h
 *
 *   \brief
 *      Header file for GMACSW hardware driver.
 *
 */


#ifndef GMACSW_H_
#define GMACSW_H_

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */
#include <stdlib.h>
#include <stdint.h>

/* Project dependency headers */
#include "cpdma.h"
#include "ale.h"
#include "mac.h"
#include "mdio.h"
#include "stats.h"
#include "port.h"
#include "cpts.h"
#include "gmacsw_config.h"
#include "gmacsw_al.h"


/*---------------------------------------------------------------------------*\
|                           Global Macros/Defines                             |
\*---------------------------------------------------------------------------*/

/*! Define success and error status values */
#define GMACSW_SUCCESS                              ((uint32_t)0x00000000U)
#define GMACSW_FAILURE                              ((uint32_t)0xFFFFFFFFU)
#define GMACSW_UNKNOWN_IOCTL                        ((uint32_t)0x00000001U)
#define GMACSW_MALFORMED_IOCTL                      ((uint32_t)0x00000002U)
/*! \brief Function or calling parameter is invalid  */
#define GMACSW_INVALID_PARAM                        ((uint32_t)0x00000003U)
#define GMACSW_TOO_MANY_TICK_FXNS                   ((uint32_t)0x00000004U)


/*---------------------------------------------------------------------------*\
|                           Global Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/

/*! \mainpage GMACSW_NSP API Reference
 *
 * \section intro Introduction
 * This documentation provides information on how to use and interact with the
 * GMACSW_NSP driver for the 3-port Gigabit Switch peripheral (the GMACSW)
 * available on a number of Texas Instruments embedded processors. The
 * public interface exposed by the driver are used by the various networking
 * stacks that send or receive data via the Ethernet hardware.

 * The driver, as currently written, sets the GMACSW hardware to act as a
 * a simple MAC. It does not expose or make use of any significant switch
 * functionality.
 *
 * \section modules Modules
 *
 * The following modules are included in this documentation:
 * \li \ref GMACSW_APIS "API Definitions"
 * \li \ref GMACSW_CONFIG_DEFINTIONS "Driver Configuration Definitions"
 * \li \ref GMACSW_IOCTLS "IOCTL Defintions"
 * \li \ref CPDMA_HELPERS "Helper Routines for CPDMA Packets and Buffer Descriptors"
 * \li \ref TFDTP_APIS  "TFDTP API Definitions"
 * \li \ref TFDTP_CONFIG_DEFINTIONS  "TFDTP Configuration Definitions"
 *
 */

/*!
 *  \defgroup  GMACSW_IOCTLS  GMACSW IOCTL Definitions
 *
 *  The definition of structures, enums, and other information needed
 *  for calling the GMACSW_ioctl() API.
 *
 *  @{
 */

typedef struct GMACSW_TICK_FXN_ *GMACSW_RegisteredTickFxnHandle;

typedef void (*GMACSW_TickFxnCallback)(void *hCallbackArg);

typedef void (*GMACSW_PrintFxnCallback)(const char *arg);

enum GMACSW_IOCTL_
{
    GMACSW_IOCTL_BASE                   = 0x00000000,
    /*! GMACSW register tick function IOCTL value. IOCTL param should be a structure of type GMACSW_TickFxnIoctlCmd. */
    GMACSW_IOCTL_REGISTER_TICK_FXN      = 0x00000000,
    /*! GMACSW unregister tick function IOCTL value. IOCTL param should be a handle of type GMACSW_RegisteredTickFxnHandle, returned from the register IOCTL. */
    GMACSW_IOCTL_UNREGISTER_TICK_FXN    = 0x00000001,
    /*! GMACSW register debug print function IOCTL value. IOCTL param should be a structure of type GMACSW_PrintFxnIoctlCmd.
    Note: To unregister debug print function call register IOCTL with NULL function pointer*/
    GMACSW_IOCTL_REGISTER_PRINT_FXN      = 0x00000002
};

/*! Param structure for the GMACSW_IOCTL_REGISTER_TICK_FXN IOCTL*/
typedef struct GMACSW_TICK_FXN_IOCTL_CMD_
{
    /*!
     * \brief  Tick function that this stack will register with the driver
     */
    GMACSW_TickFxnCallback          pTickFxnCallback;
    /*!
     * \brief  Argument to be used for the tick fxn callback routine
     */
    void                            *hTickFxnCallbackArg;
    /*!
     * \brief  Pointer to output tick function handle
     */
    GMACSW_RegisteredTickFxnHandle  *hRegisteredTickFxn;
}
GMACSW_TickFxnIoctlCmd;

/*! Param structure for the GMACSW_IOCTL_REGISTER_TICK_FXN IOCTL*/
typedef struct GMACSW_PRINT_FXN_IOCTL_CMD_
{
    /*!
     * \brief  Print function that this stack will register with the driver
     *  Note: To unregister debug print function call register IOCTL with NULL function pointer
     */
    GMACSW_PrintFxnCallback          pPrintFxnCallback;
}
GMACSW_PrintFxnIoctlCmd;

/*! Param structure for Get/Set Multicast IOCTLs */
typedef struct GMACSW_MULTICAST_IOCTL_CMD_
{
    /*!
     * \brief  Count of addresses to add
     */
    uint32_t    addrCount;
    /*!
     * \brief  Pointer to multicast address list (contains 'addrCount' * 6 bytes)
     */
    uint8_t     *pMCastList;
}
GMACSW_MulticastIoctlCmd;

/*!
 *  @}
 */

/*!
 * Definition of opaque handle for GMACSW_DEVICE_ object
 */
typedef struct GMACSW_DEVICE_ *GMACSW_DeviceHandle;


/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                   Global Inline Function Definitions                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                         Global Function Declarations                        |
\*---------------------------------------------------------------------------*/

/*!
 *  \defgroup   GMACSW_APIS   GMACSW Driver Top-level APIs
 *
 *  Programming interfaces for GMACSW hardware device driver.
 *
 *  @{
 */

/*!
 *  @b Description
 *  @n Opens the GMACSW peripheral at the given physical index and initializes
 *     it to an embryonic state.
 *
 *     This GMACSW_open() API keeps
 *     a reference count that increments for every call and which is decremented
 *     for every GMACSW_close call. For the first call to this functions, when the
 *     reference count is zero, the application must supply a valid configuration
 *     structure or the open call will fail. When the reference count is non-zero, the
 *     configuration structure parameter is not required and can be NULL.
 *
 *     Data from the config structure is
 *     copied into the device's internal instance structure so the structure
 *     may be discarded after GMACSW_open() returns. In order to change an item
 *     in the configuration, the GMACSW device must be closed and then
 *     re-opened with the new configuration. A driver reset is achieved by calling
 *     GMACSW_close() until the reference count is zero, followed by GMACSW_open().
 *
 *     An GMACSW device handle is returned to the caller. This handle must be saved
 *     by the caller and then passed to other GMACSW device functions.
 *
 *
 *  <b> Pre Condition </b>
 *  @n  None
 *
 *  <b> Post Condition </b>
 *  @n  Opens the GMACSW peripheral at the given physical index and initializes it.
 *
 *  \param[in] pGMACSWConfig
 *      Pointer to configuration structure of type GMACSW_Config
 *
 *  \return
 *      @n Non-NULL pointer to a GMACSW_DeviceHandle instance
 *      @n If open call fails, the return value is NULL.
 *
 */
extern GMACSW_DeviceHandle GMACSW_open(GMACSW_Config *pGMACSWConfig);

/*!
 *  @b Description
 *  @n Close the GMACSW peripheral indicated by the supplied instance handle.
 *     Calling this API will decrement the outstanding reference counter for
 *     the driver. If the reference count becomes zero, the GMACSW device
 *     will shutdown both send and receive operations, and free all pending
 *     transmit and receive packets for all channels.
 *
 *     The function returns zero on success, or an error code on failure.
 *
 *  <b> Pre Condition </b>
 *  @n GMACSW_open function must be called and have returned a valid handle before calling this API.
 *
 *  <b> Post Condition </b>
 *  @n The GMACSW device will shutdown both send and receive
 *     operations, and free all pending transmit and receive packets.
 *
 *  \param[in]  hGMACSW
 *      Handle to opened the GMACSW device.
 *
 *  \return
 *      @n GMACSW_SUCCESS (0) - close operation completed with no error
 *      @n Any other returned value represents an error
 *
 */
extern uint32_t GMACSW_close( GMACSW_DeviceHandle hGMACSW );

/*!
 *  @b Description
 *  @n Call the hardware driver to perform special commands. See \ref GMACSW_IOCTLS here for valid command values and related definitions.
 *
 *     The function returns zero on success, or an error code on failure.
 *
 *  <b> Pre Condition </b>
 *  @n GMACSW_open function must be called and have returned a valid handle before calling this API.
 *
 *  <b> Post Condition </b>
 *  @n The selected command is executed.
 *
 *  \param[in]  hGMACSW
 *      Handle to opened GMACSW_DeviceHandle device handle.
 *  \param[in]  cmd
 *      Ioctl command value
 *  \param[in]  param
 *      Pointer to the ioctl buffer, which contains parameters, structures, etc.
 *  \param[in]  size
 *      Size of the ioctl buffer pointed to by the param pointer
 *
 *  \return
 *      @n GMACSW_SUCCESS (0) - IOCTL completed with no error
 *      @n Any other returned value represents an error
 *
 */
extern uint32_t GMACSW_ioctl(GMACSW_DeviceHandle hGMACSW, uint32_t cmd, void *param, uint32_t size);

/*!
 *  @b Description
 *  @n The driver periodic tick function, which should be scheduled to be
 *     called by the OS, stack, or application on a periodic basis (currently
 *     recommended period is 100ms).
 *
 *     Possible error code include:
 *         GMACSW_INVALID_PARAM   - A calling parameter is invalid
 *
 *  <b> Pre Condition </b>
 *  @n  GMACSW_open function must be called before calling this API.
 *
 *  <b> Post Condition </b>
 *  @n  The GMACSW device will shutdown both send and receive
 *      operations, and free all pending transmit and receive packets.
 *
 *  \param[in]  hGMACSW
 *      Handle to opened the GMACSW device.
 *
 *  \return
 *      @n None
 *
 */
extern void GMACSW_periodicTick( GMACSW_DeviceHandle hGMACSW );

/*!
 *  @b Description
 *  @n Query the GMACSW driver to determine the current PHY link status. The
 *     driver is written assuming that only one port will be linked at a time
 *
 *  <b> Pre Condition </b>
 *  @n  GMACSW_open function must be called before calling this API.
 *
 *  <b> Post Condition </b>
 *  @n  None
 *
 *  \param[in]  hGMACSW
 *      Handle to opened the GMACSW device.
 *  \param[out]  linkState
 *      Integer returned representing the link state (speed and duplex) (0-7).
 *  \param[out]  linkedInterface
 *      Integer returned representing the interface number currently linked (0 or 1).
 *
 *  \return
 *      @n None
 *
 */
extern void GMACSW_getLinkStatus( GMACSW_DeviceHandle hGMACSW, uint32_t *linkState, uint32_t devIdx);

/*!
 *  @}
 */



/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* GMACSW_H_ */

