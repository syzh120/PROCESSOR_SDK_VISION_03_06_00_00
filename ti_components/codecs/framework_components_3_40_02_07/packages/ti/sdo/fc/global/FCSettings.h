/*
 * Copyright (c) 2012, Texas Instruments Incorporated
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
 *
 */
/**
 *  @file       ti/sdo/fc/global/FCSettings.h
 *
 *  @brief      Framework Components global settings interface.
 */

/**
 *  @defgroup   ti_sdo_fc_global_FCSettings
 *
 */

#ifndef ti_sdo_fc_global_FCSETTINGS_H
#define ti_sdo_fc_global_FCSETTINGS_H

/** @ingroup    ti_sdo_fc_global */
/*@{*/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief       Name passed to Diags_setMask() for logging. This is used
 *              internal by FC components to determine how to initialize
 *              their Diags masks. The application can use this to set
 *              default Diags mask values for FC components by adding the
 *              following code before FC comonents are initialized. For
 *              exaple:
 *
 *              #include <xdc/std.h>
 *              #include <xdc/runtime/Diags.h>
 *              #include <xdc/runtime/Registry.h>
 *
 *              #include <ti/sdo/fc/global/FCSettings.h>
 *
 *              main()
 *              {
 *                  FCSettings_init();
 *
 *                  Diags_setMask(FCSETTINGS_MODNAME"+EX1234567");
 *
 *                  RMAN_init();
 *               }
 *
 * @sa FCSettings_init()
 */
#define FCSETTINGS_MODNAME "ti.sdo.fc.global.FCSettings"

/**
 *  @brief      De-initialize global settings
 *
 */
Void FCSettings_exit();

/**
 *  @brief      Initialize global settings
 *
 */
Void FCSettings_init();

/** @cond INTERNAL */
/*
 *  ======== FCSettings_getDiags ========
 */
/**
 *  @brief      Get the string that corresponds to the bits set in the Diags
 *              mask of FCSettings. For example, if Diags_ENTRY and Diags_USER1
 *              are enabled, this function returns "+E1"
 *
 *  @param[in]  curControl  Location to copy Diags string
 *  @param[in]  size        Length of curControl (bytes).
 *
 *  @pre        @c size must be >= 11 (For null-termintated "+EX1234567")
 */
Void FCSettings_getDiags(String curControl, Int size);

/*
 *  ======== FCSettings_setDiags ========
 */
/**
 *  @brief      Set the Diags mask for the module 'modName', based on the
 *              Diags mask for FCSettings. For example, if FCSettings has
 *              Diags_ENTRY and Diags_USER1 enabled, this function sets
 *              the Diags for modName to "+E1"
 *
 *  @param[in]  modName    Name of the module to set Diags mask for.
 *
 *  @pre        The string @c modName must not be longer than 128 characters
 */
Void FCSettings_setDiags(String modName);

/** @cond INTERNAL */

#ifdef __cplusplus
}
#endif /* extern "C" */

/*@}*/
#endif  /* ti_sdo_fc_global_FCSETTINGS_H */
