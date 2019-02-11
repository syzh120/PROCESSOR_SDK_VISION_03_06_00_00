/*
 * Copyright (c) 2014, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
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
 * */
/*
 *  ======== mytime.h ========
 */
/**
 *  @file       mytime.h
 *
 *  The MYTIME module uses the SYS/BIOS Clock module to keep track of system
 *  time for hardware platforms that do not have a Real Time Clock.
 *
 *  The module internally tracks the time by keeping count of the
 *  number of seconds since the Epoch, which is defined to be January 1, 1970.
 *
 *  Users of the MYTIME module can access its internal time value using supplied
 *  getter and setter functions.
 *
 *  # Example Usage #
 *
 *  The MYTIME module is part of the NDK nettools library.  An application
 *  should include its header file as follows:
 *  @code
 *  #include <ti/ndk/nettools/mytime/mytime.h>
 *  @endcode
 *
 *  ## Initializing The MYTIME Module ##
 *
 *  To initialize and start the MYTIME module clock, call the following
 *  function:
 *  @code
 *  MYTIME_init();
 *  @endcode
 *
 *  ## Getting The Current Time ##
 *
 *  The internal time value can be obtained by calling the MYTIME_gettime()
 *  function:
 *  @code
 *  uint32_t currentTime = MYTIME_gettime();
 *  @endcode
 *
 *  ## Setting The Current Time ##
 *
 *  The internal time value can be set by calling the MYTIME_settime()
 *  function:
 *  @code
 *  uint32_t newTime = 100;
 *  MYTIME_settime(newTime);
 *  @endcode
 *
 *  ## Deinitializing The MYTIME Module ##
 *  The following function can be called to stop the MYTIME Clock and free its
 *  resources:
 *  @code
 *  MYTIME_exit();
 *  @endcode
 *
 *  ============================================================================
 */

#ifndef MYTIME_
#define MYTIME_

#include <xdc/std.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== MYTIME_init ========
 */
/*!
 *  @brief Create a new Clock instance that ticks every second.
 */
void MYTIME_init(void);

/*
 *  ======== MYTIME_exit ========
 */
/*! @brief Stops and deletes the Clock instance created in the init function. */
void MYTIME_exit(void);

/*
 *  ======== MYTIME_gettime ========
 */
/*!
 *  @brief Returns the number of seconds since the Epoch (January 1, 1970).
 *
 *  @return The number of seconds since January 1, 1970
 */
uint32_t MYTIME_gettime(void);

/*
 *  ======== MYTIME_settime ========
 */
/*!
 *  @brief Sets the time to the value passed in via the newtime parameter (units
 *         in seconds).
 *
 *  @param newtime Time in seconds since the Epoch to set the time to
 */
void MYTIME_settime(uint32_t newtime);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* MYTIME_ */
