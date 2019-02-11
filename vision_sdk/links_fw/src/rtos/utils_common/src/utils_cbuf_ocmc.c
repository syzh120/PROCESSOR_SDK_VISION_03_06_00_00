/*
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/**
 *******************************************************************************
 *
 * \file utils_cbuf_ocmc.c
 *
 * \brief Utility functions for allocating on chip memory as circular buffers
 * Used for subframe capture and processing
 *
 * \version 0.0 (July 2014) : [VT] First version
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include <src/rtos/utils_common/include/utils_cbuf_ocmc.h>

/**
 *******************************************************************************
 *
 * \brief Initialize and configure OCMC for allocation as CBUF
 *
 * \param  ocmcInstId       [IN] OCMC instance ID
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Utils_cbufOcmcInit(Utils_OcmcInstanceId ocmcInstId)
{
    UInt32 baseAddr;
    ocmc_ret_type_t retval;

    /* Get base address of OCMC based on instance */
    baseAddr = OCMC_Inst_AddrGet((ocmc_inst_t)ocmcInstId);

    /* Soft reset on the OCMC */
    OCMCSoftReset(baseAddr);

    /* Initialise OCMC region as circula buffer */
    retval = (ocmc_ret_type_t)OCMC_CBUF_Heap_Init((ocmc_inst_t)baseAddr);
    UTILS_assert(retval == e_ocmc_success);

    OCMCModeSet(baseAddr, NO_IDLE);

    /*Configure OCMC to Non ECC Code access mode*/
    OCMCEccConfig(baseAddr, OCMC_NON_ECC_DATA_ACCESS, 0, 0, 0);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Allocate a circular buffer from OCMC region
 *
 * \param  ocmcInstId       [IN] OCMC instance ID
 * \param  bpp              [IN] Bits per pixel, this is based on image format
 * \param  width            [IN] Image width
 * \param  height           [IN] Image height
 * \param  numLinesPerSlice [IN] number of lines per subframe
 * \param  numSlicesPerCbuf [IN] number of subframes per circular buffer
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Ptr Utils_cbufOcmcAlloc(Utils_OcmcInstanceId ocmcInstId,
    UInt32 bpp,UInt32 width, UInt32 height, UInt32 numLinesPerSlice, UInt32 numSlicesPerCbuf)
{
    Ptr virtStartAddr = NULL;
    vbuf_setup_image_params_auto_addr_t iParam;
    ocmc_ret_type_t err;

    /* Initialise structure used to setup a VBUF config using Image parameters */
    iParam.bytes_per_pixel = bpp;
    iParam.image_height    = height;
    iParam.image_width     = width;
    iParam.lines_per_slice = numLinesPerSlice;
    iParam.num_slices      = numSlicesPerCbuf;

    /* Allocate the circular buffer */
    virtStartAddr = (Ptr)OCMC_CBUF_Heap_Alloc((ocmc_inst_t)ocmcInstId,
                          (const vbuf_setup_image_params_auto_addr_t *)&iParam,
                          (ocmc_ret_type_t *)&err);
    UTILS_assert(virtStartAddr != NULL);

    return virtStartAddr;
}

/**
 *******************************************************************************
 *
 * \brief Initialize and configure OCMC for allocation as CBUF
 *
 * \param  ocmcInstId   [IN] OCMC instance ID
 * \param  addr         [IN] OCMC address to be freed
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Utils_cbufOcmcFree(Utils_OcmcInstanceId ocmcInstId, Ptr addr)
{
    ocmc_ret_type_t retval;

    retval = (ocmc_ret_type_t)OCMC_CBUF_Heap_Free((ocmc_inst_t)ocmcInstId, addr);
    UTILS_assert(retval == e_ocmc_success);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Deinitialize the OCMC region specified
 *
 * \param  ocmcInstId       [IN] OCMC instance ID
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Utils_cbufOcmcDeInit(Utils_OcmcInstanceId ocmcInstId)
{
    ocmc_ret_type_t retval;

    /*  disable the CBUF mode */
    retval = OCMC_CBUF_Deinit((ocmc_inst_t)ocmcInstId);
    UTILS_assert(retval == e_ocmc_success);

    return SYSTEM_LINK_STATUS_SOK;
}
