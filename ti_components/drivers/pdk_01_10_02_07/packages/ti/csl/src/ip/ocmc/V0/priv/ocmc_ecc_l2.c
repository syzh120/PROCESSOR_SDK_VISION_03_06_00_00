/*
 *  Copyright (C) 2013-2017 Texas Instruments Incorporated
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
 *  \file  ocmc_ecc_l2.c
 *
 *  \brief OCMC APIs
 *
 *   This file contains the OCMC HAL layer two APIs
 */

/****************************************************************
 *  INCLUDE FILES
 ****************************************************************/
#include "stdint.h"
#include "ti/csl/csl_ocmc_ecc.h"
#include "ti/csl/csl_ocmc_ecc.h"
#include "string.h"

/*Error return string*/
char errArr[50];

ocmc_inst_t OCMC_GetNumOCMC(void)
{
    return (ocmc_inst_t) OCMC_NUM_INSTANCE;
}

ocmc_buf_id_t OCMC_GetNumCBUF(void)
{
    return (ocmc_buf_id_t) NUM_CBUFS_PER_OCMC;
}

ocmc_ret_type_t OCMC_Get_GP_MemoryBaseAndSize(uint32_t     baseAddr,
                                              ocmc_addr_t *gp_mem_base,
                                              uint32_t    *gp_mem_size)
{
    uint32_t    ocmc_size;
    ocmc_addr_t max_base_found = 0U;
    uint32_t    size_max_base  = 0U;

    uint32_t    i;
    uint32_t    cbuf_start, cbuf_size;

    /*
     * algorithm is based on reading CBUF start address and size registers for
     * each of NUM_CBUFS_PER_OCMC CBUFs
     * maintain the maximum found thus far (start + size).
     * return the final maximum value.
     */

    ocmc_size = OCMCGetRAMSize(baseAddr);

    for (i = 0U; i < NUM_CBUFS_PER_OCMC; i++)
    {
        cbuf_start = OCMCCBufStartAddrGet(baseAddr, (ocmc_buf_id_t) i);
        cbuf_size  = OCMCCBufSizeGet(baseAddr, (ocmc_buf_id_t) i);

        if ((cbuf_start > max_base_found) || (cbuf_size > 0U))
        {
            max_base_found = cbuf_start;
            size_max_base  = cbuf_size;
        }
    }

    *gp_mem_size = ocmc_size - (max_base_found + size_max_base);
    *gp_mem_base = max_base_found + size_max_base;

    return e_ocmc_success;
}

ocmc_ret_type_t OCMC_Setup_VBUF(uint32_t baseAddr, ocmc_buf_id_t buf_id,
                                const vbuf_setup_raw_t *vbuf_setup_raw)
{
    uint32_t        q = 0U, r = 0U;

    ocmc_addr_t     vbuf_start = 0U, vbuf_end = 0U, cbuf_start = 0U;
    uint32_t        vbuf_size  = 0U, cbuf_size = 0U;
    ocmc_ret_type_t retval     = e_ocmc_success;

    if (vbuf_setup_raw == NULL)
    {
        retval = e_ocmc_null_pointer_in_argument;
    }
    if (e_ocmc_success == retval)
    {
        vbuf_start = vbuf_setup_raw->vbuf_start;
        vbuf_size  = vbuf_setup_raw->vbuf_size;
        cbuf_start = vbuf_setup_raw->cbuf_start;
        cbuf_size  = vbuf_setup_raw->cbuf_size;

        r = vbuf_size % 16U;
        if (r)
        {
            vbuf_size += (16U - r);
        }

        vbuf_end = (vbuf_start + vbuf_size) - 16U;
        /* align vbuf_end to a 16-byte multiple */
        vbuf_end = (vbuf_end >> 4U) << 4U;
    }
    /* In each condition check if any error came earlier. If yes, do not execute
     *the if, else execute it*/
    if ((buf_id >= OCMC_GetNumCBUF()) && (e_ocmc_success == retval))
    {
        retval = e_ocmc_invalid_cbuf_id;
    }

    /* check1: verify that VBUF start and end are inside the OCMC CBUF address
     * range.
     */
    if (e_ocmc_success == retval)
    {
        if (vbuf_start < OCMCCBUFBaseAddrGet(baseAddr))
        {
            retval = e_ocmc_illegal_vbuf_start_addr;
        }
    }

    if (e_ocmc_success == retval)
    {
        if (vbuf_start >= (OCMCCBUFBaseAddrGet(baseAddr) +
                           OCMCCBUFSizeGet(baseAddr)))
        {
            retval = e_ocmc_illegal_vbuf_start_addr;
        }
    }
    if (e_ocmc_success == retval)
    {
        if (vbuf_end > (OCMCCBUFBaseAddrGet(baseAddr) +
                        OCMCCBUFSizeGet(baseAddr)))
        {
            retval = e_ocmc_illegal_vbuf_end_addr;
        }
    }

    /* check2: verify that VBUF size is < 8 MB.*/
    if ((e_ocmc_success == retval) && (vbuf_size >= (8U * (1024U * 1024U))))
    {
        retval = e_ocmc_illegal_vbuf_size;
    }

    /* check3: verify that VBUF start, end and size are all 16-byte aligned.*/
    if ((e_ocmc_success == retval) && ((vbuf_start % 16U) != 0U))
    {
        retval = e_ocmc_vbuf_addr_not_16b_aligned;
    }
    if ((e_ocmc_success == retval) && ((vbuf_size % 16U) != 0U))
    {
        retval = e_ocmc_vbuf_size_not_16b_aligned;
    }

    /* check4: verify that OCMC Start and size fall in legal range.*/
    if (e_ocmc_success == retval)
    {
        if (cbuf_start < OCMCBaseAddrGet(baseAddr))
        {
            retval = e_ocmc_illegal_cbuf_start;
        }
    }
    if (e_ocmc_success == retval)
    {
        if (cbuf_start >= (OCMCBaseAddrGet(baseAddr) +
                           OCMCGetRAMSize(baseAddr)))
        {
            retval = e_ocmc_illegal_cbuf_start;
        }
    }
    if (e_ocmc_success == retval)
    {
        if ((cbuf_start + cbuf_size) > (OCMCBaseAddrGet(baseAddr) +
                                        OCMCGetRAMSize(baseAddr)))
        {
            retval = e_ocmc_illegal_cbuf_size;
        }
    }

    /* check5: verify that cbuf_size is < 1MB*/
    if ((e_ocmc_success == retval) && (cbuf_size >= (1024U * 1024U)))
    {
        retval = e_ocmc_illegal_cbuf_size;
    }

    /* check6: verify that cbuf_start, cbuf_size are multiples of 16*/
    if ((e_ocmc_success == retval) && ((cbuf_start % 16U) != 0U))
    {
        retval = e_ocmc_cbuf_addr_not_16b_aligned;
    }
    if ((e_ocmc_success == retval) && ((cbuf_size % 16U) != 0U))
    {
        retval = e_ocmc_cbuf_size_not_16b_aligned;
    }

    /*
     * check7: verify that VBUF start addresses are in increasing order, and
     * non-overlapping
     * How do we do this? We dont do this check here to allow flexibility in how
     * the VBUFs are set up.
     * We check this when circular buffering mode of operations is turned on for
     * this ocmc_inst.
     */

    /*
     * check8: vbuf size = n * cbuf_size + m where
     * if n == 1, then 0 < m < OCMC_cbuf_size
     * if n > 1, then 0 <= m < OCMC_cbuf_size
     * any other n is invalid
     *
     */
    if (e_ocmc_success == retval)
    {
        q = vbuf_size / cbuf_size;
        r = vbuf_size % cbuf_size;
    }

    if ((e_ocmc_success == retval) && (q == 0U))
    {
        retval = e_ocmc_vbuf_size_smaller_than_cbuf_size;
    }
    if ((e_ocmc_success == retval) && (q == 1U))
    {
        if (r == 0U)
        {
            retval = e_ocmc_reminder_vbuf_mod_cbuf_is_zero;
        }
    }

    /*
     * Now if retval is not changed anywhere in the program above
     * all that is left to do is program the virtual buffer.
     */
    if (e_ocmc_success == retval)
    {
        /* write vbuf start*/
        OCMCVBufStartAddrSet(baseAddr, buf_id, vbuf_start);

        /* write vbuf end*/
        OCMCVBufEndAddrSet(baseAddr, buf_id, vbuf_end);

        /* write cbuf start;*/
        OCMCCBufStartAddrSet(baseAddr, buf_id, cbuf_start);

        /* write cbuf size*/
        OCMCCBufSizeSet(baseAddr, buf_id, cbuf_size);
    }
    return retval;
}

ocmc_ret_type_t OCMC_Setup_VBUF_Address_Auto(
    uint32_t baseAddr, ocmc_buf_id_t buf_id,
    const vbuf_setup_raw_auto_addr_t *vbuf_setup_raw_auto_addr)
{
    vbuf_setup_raw_t vbuf_setup;
    ocmc_addr_t      prev_vbuf_end, prev_cbuf_start;
    uint32_t         prev_cbuf_size, prev_buf_id;
    ocmc_ret_type_t  retval = e_ocmc_success;

    if (vbuf_setup_raw_auto_addr == NULL)
    {
        retval = e_ocmc_null_pointer_in_argument;
    }

    if ((buf_id >= OCMC_GetNumCBUF()) && (e_ocmc_success == retval))
    {
        retval = e_ocmc_invalid_cbuf_id;
    }

    if (e_ocmc_success == retval)
    {
        vbuf_setup.vbuf_size = vbuf_setup_raw_auto_addr->vbuf_size;
        vbuf_setup.cbuf_size = vbuf_setup_raw_auto_addr->cbuf_size;

        if ((uint32_t) buf_id == 0U)
        {
            /* first buffer. Goes at the start of the CBUF address range.*/
            vbuf_setup.vbuf_start = OCMCCBUFBaseAddrGet(baseAddr);
            vbuf_setup.cbuf_start = OCMCBaseAddrGet(baseAddr);
            retval = OCMC_Setup_VBUF(baseAddr, buf_id, &vbuf_setup);
        }
    }

    if (e_ocmc_success == retval)
    {
        /* buf_id > 0.*/
        prev_buf_id   = (uint32_t) buf_id - 1U;
        prev_vbuf_end = OCMCVBufEndAddrGet(baseAddr,
                                           (ocmc_buf_id_t) prev_buf_id);
        prev_cbuf_start = OCMCCBufStartAddrGet(baseAddr,
                                               (ocmc_buf_id_t) prev_buf_id);
        prev_cbuf_size = OCMCCBufSizeGet(baseAddr, (ocmc_buf_id_t) prev_buf_id);

        if (prev_vbuf_end & 0x80000000U)
        {
            prev_vbuf_end = prev_vbuf_end ^ 0x80000000U;
        }

        vbuf_setup.vbuf_start = prev_vbuf_end + 16U;
        vbuf_setup.cbuf_start = prev_cbuf_start + prev_cbuf_size + 16U;
        retval = OCMC_Setup_VBUF(baseAddr, buf_id, &vbuf_setup);
    }
    return retval;
}

ocmc_ret_type_t OCMC_Setup_VBUF_With_Image_Params(
    uint32_t baseAddr, ocmc_buf_id_t buf_id,
    const vbuf_setup_image_params_t *vbuf_setup_image)
{
    ocmc_addr_t      vbuf_start, cbuf_start;
    uint32_t         vbuf_size;
    uint32_t         cbuf_size;
    uint32_t         image_height, image_width, lines_per_slice, num_slices,
                     bytes_per_pixel;
    uint32_t         r;
    vbuf_setup_raw_t vbuf_setup;
    ocmc_ret_type_t  retval = e_ocmc_success;

    if (vbuf_setup_image == NULL)
    {
        retval = e_ocmc_null_pointer_in_argument;
    }
    if (e_ocmc_success == retval)
    {
        vbuf_start      = vbuf_setup_image->vbuf_start;
        cbuf_start      = vbuf_setup_image->cbuf_start;
        image_height    = vbuf_setup_image->image_height;
        image_width     = vbuf_setup_image->image_width;
        lines_per_slice = vbuf_setup_image->lines_per_slice;
        num_slices      = vbuf_setup_image->num_slices;
        bytes_per_pixel = vbuf_setup_image->bytes_per_pixel;

        vbuf_size = image_width * image_height * bytes_per_pixel;

        r = vbuf_size % 16U;
        if (r)
        {
            vbuf_size += (16U - r);
        }
        cbuf_size = lines_per_slice * num_slices * bytes_per_pixel *
                    image_width;

        r = cbuf_size % 16U;
        if (0U != r)
        {
            cbuf_size += (16U - r);
        }
        vbuf_setup.vbuf_start = vbuf_start;
        vbuf_setup.vbuf_size  = vbuf_size;
        vbuf_setup.cbuf_start = cbuf_start;
        vbuf_setup.cbuf_size  = cbuf_size;
        retval = OCMC_Setup_VBUF(baseAddr, buf_id, &vbuf_setup);
    }
    return retval;
}

ocmc_ret_type_t OCMC_Setup_VBUF_With_Image_Params_Address_Auto(
    uint32_t baseAddr, ocmc_buf_id_t buf_id,
    const vbuf_setup_image_params_auto_addr_t *vbuf_setup_image_auto_addr)
{
    /*
     *  set up the new VBUF at the previous VBUF end, then aligned to 16-byte
     *  aligned address.
     */
    uint32_t                  bytes_per_pixel;
    uint32_t                  image_height;
    uint32_t                  image_width;
    uint32_t                  lines_per_slice;
    uint32_t                  num_slices;

    ocmc_addr_t               prev_vbuf_end;
    ocmc_addr_t               prev_cbuf_start;
    uint32_t                  prev_cbuf_size, prev_buf_id;
    vbuf_setup_image_params_t vbuf_setup_image;
    ocmc_ret_type_t           retval = e_ocmc_success;

    if (vbuf_setup_image_auto_addr == NULL)
    {
        retval = e_ocmc_null_pointer_in_argument;
    }
    else
    {
        bytes_per_pixel = vbuf_setup_image_auto_addr->bytes_per_pixel;
        image_height    = vbuf_setup_image_auto_addr->image_height;
        image_width     = vbuf_setup_image_auto_addr->image_width;
        lines_per_slice = vbuf_setup_image_auto_addr->lines_per_slice;
        num_slices      = vbuf_setup_image_auto_addr->num_slices;
    }

    if ((buf_id >= OCMC_GetNumCBUF()) && (e_ocmc_success == retval))
    {
        retval = e_ocmc_invalid_cbuf_id;
    }
    if (e_ocmc_success == retval)
    {
        vbuf_setup_image.bytes_per_pixel = bytes_per_pixel;
        vbuf_setup_image.image_height    = image_height;
        vbuf_setup_image.image_width     = image_width;
        vbuf_setup_image.lines_per_slice = lines_per_slice;
        vbuf_setup_image.num_slices      = num_slices;

        if ((uint32_t) buf_id == 0U)
        {
            /* first buffer. Goes at the start of the CBUF address range.*/
            vbuf_setup_image.vbuf_start = OCMCCBUFBaseAddrGet(baseAddr);
            vbuf_setup_image.cbuf_start = OCMCBaseAddrGet(baseAddr);
            retval = OCMC_Setup_VBUF_With_Image_Params(baseAddr, buf_id,
                                                       &vbuf_setup_image);
        }
    }

    if (e_ocmc_success == retval)
    {
        /* buf_id > 0.*/
        prev_buf_id   = (uint32_t) buf_id - 1U;
        prev_vbuf_end = OCMCVBufEndAddrGet(baseAddr,
                                           (ocmc_buf_id_t) prev_buf_id);
        prev_cbuf_start = OCMCCBufStartAddrGet(baseAddr,
                                               (ocmc_buf_id_t) prev_buf_id);
        prev_cbuf_size = OCMCCBufSizeGet(baseAddr, (ocmc_buf_id_t) prev_buf_id);

        vbuf_setup_image.vbuf_start = prev_vbuf_end + 16U;
        vbuf_setup_image.cbuf_start = prev_cbuf_start + prev_cbuf_size + 16U;
        retval = OCMC_Setup_VBUF_With_Image_Params(baseAddr, buf_id,
                                                   &vbuf_setup_image);
    }
    return retval;
}

ocmc_ret_type_t OCMC_Get_VBUF_Params(uint32_t baseAddr, ocmc_buf_id_t buf_id,
                                     vbuf_setup_raw_t *vbuf_setup_raw)
{
    uint32_t        vbuf_size, cbuf_size;
    ocmc_addr_t     vbuf_start, cbuf_start, vbuf_end;
    ocmc_ret_type_t retval = e_ocmc_success;

    if (buf_id >= OCMC_GetNumCBUF())
    {
        retval = e_ocmc_invalid_cbuf_id;
    }
    if (e_ocmc_success == retval)
    {
        vbuf_start = (ocmc_addr_t) OCMCVBufStartAddrGet(baseAddr, buf_id);
        vbuf_end   = (ocmc_addr_t) OCMCVBufEndAddrGet(baseAddr, buf_id);
        cbuf_start = (ocmc_addr_t) OCMCCBufStartAddrGet(baseAddr, buf_id);
        cbuf_size  = (ocmc_addr_t) OCMCCBufSizeGet(baseAddr, buf_id);

        /*
         * Adding 16 bytes to vbuf_size as 16 bytes was subtracted while setting
         * vbuf_end address due to 16 byte alignment
         */
        vbuf_size =
            ((uint32_t) vbuf_end - (uint32_t) vbuf_start) + (uint32_t) 16U;

        vbuf_setup_raw->vbuf_start = vbuf_start;
        vbuf_setup_raw->vbuf_size  = vbuf_size;
        vbuf_setup_raw->cbuf_start = cbuf_start;
        vbuf_setup_raw->cbuf_size  = cbuf_size;
    }

    return retval;
}

ocmc_ret_type_t OCMC_CBUF_Heap_Init(ocmc_inst_t ocmc_inst_id)
{
    uint32_t        baseAddr;
    ocmc_ret_type_t retval = e_ocmc_success;

    baseAddr = OCMC_Inst_AddrGet(ocmc_inst_id);
    OCMCCbufModeEnableCtrl(baseAddr, (uint8_t) OCMC_BUF_ENABLE);

    OCMCShortFrameDetectEnableCtrl(baseAddr, (uint8_t) 1U, (uint8_t) 1U);
    OCMCOverflowConfigure(baseAddr, (uint8_t) 1U, e_wr_overflow_no_disable,
                          e_overflow_reenable_after_next_write_read);
    OCMCUnderflowConfigure(baseAddr, (uint8_t) 1U, (uint8_t) 0U);

    return retval;
}

void *OCMC_CBUF_Heap_Alloc(
    ocmc_inst_t      ocmc_inst_id,
    const vbuf_setup_image_params_auto_addr_t *
    vbuf_setup_image_auto_addr,
    ocmc_ret_type_t *err)
{
    /*
     * need to program the next available VBUF/CBUF pair based off the image
     * params supplied here.
     * the implementation goes over each VBUF/CBUF pair that is disabled and
     * tries to set it up.
     * Successful if yes, err otherwise
     *
     */
    uint32_t         j, baseAddr;
    void            *retval = NULL;
    ocmc_ret_type_t  t_err;
    vbuf_setup_raw_t vbuf_raw;

    baseAddr = OCMC_Inst_AddrGet(ocmc_inst_id);
    for (j = 0U; j < (uint32_t) NUM_CBUFS_PER_OCMC; j++)
    {
        if ((OCMCCbufEnableStatusGet(baseAddr, (ocmc_buf_id_t) j)) == 0U)
        {
            /* buffer is free ... see if this can be used.*/
            t_err = OCMC_Setup_VBUF_With_Image_Params_Address_Auto(
                baseAddr, (ocmc_buf_id_t) j, vbuf_setup_image_auto_addr);
            if (t_err == e_ocmc_success)
            {
                *err = t_err;
                OCMC_Get_VBUF_Params(baseAddr, (ocmc_buf_id_t) j, &vbuf_raw);

                /* Enable this VBUF.*/
                OCMCCbufEnableCtrl(baseAddr, (ocmc_buf_id_t) j,
                                   (uint8_t) OCMC_BUF_ENABLE);
                retval = (void *)vbuf_raw.vbuf_start;
                break;
            }
        }
    }

    /* if we come here, that means we failed to allocate a buffer.*/
    if (retval == NULL)
    {
        *err = e_ocmc_insufficient_cbuf_mem;
    }
    return retval;
}

ocmc_ret_type_t OCMC_CBUF_Heap_Free(ocmc_inst_t ocmc_inst_id, const void *addr)
{
    /* disable the appropriate VBUF.*/
    uint32_t         j, baseAddr;
    vbuf_setup_raw_t vbuf_raw;
    ocmc_ret_type_t  retval = e_ocmc_illegal_vbuf_start_addr;

    baseAddr = OCMC_Inst_AddrGet(ocmc_inst_id);
    for (j = 0U; j < (uint32_t) NUM_CBUFS_PER_OCMC; j++)
    {
        OCMC_Get_VBUF_Params(baseAddr, (ocmc_buf_id_t) j, &vbuf_raw);
        if (vbuf_raw.vbuf_start == (uint32_t) addr)
        {
            /* Disble this VBUF.*/
            OCMCCbufEnableCtrl(baseAddr, (ocmc_buf_id_t) j,
                               (uint8_t) OCMC_BUF_DISABLE);
            retval = e_ocmc_success;
            break;
        }
    }
    return retval;
}

ocmc_ret_type_t OCMC_CBUF_Deinit(ocmc_inst_t ocmc_inst_id)
{
    uint32_t        baseAddr;
    ocmc_ret_type_t retval = e_ocmc_success;

    baseAddr = OCMC_Inst_AddrGet(ocmc_inst_id);
    OCMCCbufModeEnableCtrl(baseAddr, (uint8_t) OCMC_BUF_DISABLE);

    return retval;
}

uint32_t OCMC_Inst_AddrGet(ocmc_inst_t ocmc_inst)
{
    uint32_t baseAddr;
    switch ((uint32_t) ocmc_inst)
    {
        case 0U:
            baseAddr = (uint32_t) SOC_OCMC_RAM1_CFG_BASE;
            break;
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_AM572x) || defined (SOC_AM574x)
        case 1U:
            baseAddr = (uint32_t) SOC_OCMC_RAM2_CFG_BASE;
            break;
        case 2U:
            baseAddr = (uint32_t) SOC_OCMC_RAM3_CFG_BASE;
            break;
#endif
        default:
            baseAddr = (uint32_t) SOC_OCMC_RAM1_CFG_BASE;
            break;
    }

    return baseAddr;
}

char *OCMC_Get_Error_String(ocmc_ret_type_t err)
{
    switch (err)
    {
        case e_ocmc_null_pointer_in_argument:
            strcpy(errArr, "OCMC_NULL_PTR_IN_ARGUMENT");
            break;
        case e_ocmc_not_cbuf_capable:
            strcpy(errArr, "OCMC_NOT_CBUF_CAPABLE");
            break;
        case e_ocmc_insufficient_cbuf_mem:
            strcpy(errArr, "OCMC_INSUFFICIENT_CBUF_MEM_FOR_OPERATION");
            break;
        case e_ocmc_invalid_ocmc_inst:
            strcpy(errArr, "OCMC_INVALID_OCMC_INSTANCE_ID");
            break;
        case e_ocmc_invalid_cbuf_id:
            strcpy(errArr, "OCMC_INVALID_BUF_ID");
            break;
        case e_ocmc_illegal_vbuf_start_addr:
            strcpy(errArr, "OCMC_INVALID_VBUF_START_ADDRESS");
            break;
        case e_ocmc_illegal_vbuf_end_addr:
            strcpy(errArr, "OCMC_INVALID_VBUF_END_ADDRESS");
            break;
        case e_ocmc_illegal_vbuf_size:
            strcpy(errArr, "OCMC_INVALID_VBUF_SIZE");
            break;
        case e_ocmc_vbuf_addr_not_16b_aligned:
            strcpy(errArr, "OCMC_VBUF_ADDRESS_NOT_16BYTE_ALIGNED");
            break;
        case e_ocmc_vbuf_size_not_16b_aligned:
            strcpy(errArr, "OCMC_VBUF_SIZE_NOT_16BYTE_ALIGNED");
            break;
        case e_ocmc_illegal_cbuf_start:
            strcpy(errArr, "OCMC_INVALID_CBUF_START_ADDRESS");
            break;
        case e_ocmc_illegal_cbuf_size:
            strcpy(errArr, "OCMC_INVALID_CBUF_SIZE");
            break;
        case e_ocmc_cbuf_addr_not_16b_aligned:
            strcpy(errArr, "OCMC_CBUF_ADDRESS_NOT_16BYTE_ALIGNED");
            break;
        case e_ocmc_cbuf_size_not_16b_aligned:
            strcpy(errArr, "OCMC_CBUF_SIZE_NOT_16BYTE_ALIGNED");
            break;
        case e_ocmc_vbuf_size_smaller_than_cbuf_size:
            strcpy(errArr, "OCMC_VBUF_SIZE_SMALLER_THAN_CBUF_SIZE");
            break;
        case e_ocmc_reminder_vbuf_mod_cbuf_is_zero:
            strcpy(errArr, "OCMC_VBUF_MOD_CBUF_ZERO");
            break;
        case e_invalid_intr_group:
            strcpy(errArr, "OCMC_INVALID_INTERRUPT_GROUP");
            break;
        case e_invalid_intr_id:
            strcpy(errArr, "OCMC_INVALID_INTERRUPT_ID");
            break;
        case e_ocmc_success:
            strcpy(errArr, "OCMC_No_Error");
            break;
        case e_invalid_cbuf_err_type:
            strcpy(errArr, "OCMC_INVALID_CBUF_ERROR_TYPE");
            break;
        default:
            strcpy(errArr, "Unrecognized_Error_Code");
            break;
    }

    return errArr;
}

