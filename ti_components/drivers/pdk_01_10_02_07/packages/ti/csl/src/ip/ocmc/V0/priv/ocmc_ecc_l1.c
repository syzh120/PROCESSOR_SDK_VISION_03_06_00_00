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
 *  \file  ocmc_ecc_l1.c
 *
 *  \brief OCMC APIs
 *
 *   This file contains the OCMC HAL layer one APIs
 */

/****************************************************************
 *  INCLUDE FILES
 ****************************************************************/
#include "stdint.h"
#include "ti/csl/csl_ocmc_ecc.h"
#include "ti/csl/hw_types.h"

/* OCMC_VBUF_SIZE is (8 * 1024 * 1024) */
#define OCMC_VBUF_SIZE (8388608U)

/*TI_INSPECTED 65 D : MISRAC_2012_R_2.2
 *"Tool Issue - Unable to process HW_WR MACROS " */
void OCMCModeSet(uint32_t baseAddr,
                 ocmc_sysconfig_mode mode)
{
    HW_WR_FIELD32(
        baseAddr + OCMC_RAM_OCMC_SYSCONFIG_PM,
        OCMC_RAM_OCMC_SYSCONFIG_PM_IDLEMODE,
        mode);
}

/*TI_INSPECTED 65 D : MISRAC_2012_R_2.2
 *"Tool Issue - Unable to process HW_WR MACROS " */
void OCMCSoftReset(uint32_t baseAddr)
{
    /* reset */
    HW_WR_FIELD32(
        baseAddr + OCMC_RAM_OCMC_SYSCONFIG_RST,
        OCMC_RAM_OCMC_SYSCONFIG_RST_SW_RST,
        OCMC_RAM_OCMC_SYSCONFIG_RST_SW_RST_RESET);

    /* restore normal operations */
    HW_WR_FIELD32(
        baseAddr + OCMC_RAM_OCMC_SYSCONFIG_RST,
        OCMC_RAM_OCMC_SYSCONFIG_RST_SW_RST,
        OCMC_RAM_OCMC_SYSCONFIG_RST_SW_RST_NORMAL_OP);
}

uint32_t OCMCGetRAMSize(uint32_t baseAddr)
{
    uint32_t ramSize;
    ramSize = HW_RD_FIELD32(
        baseAddr + OCMC_RAM_OCMC_MEM_SIZE_READ,
        OCMC_RAM_OCMC_MEM_SIZE_READ_MEM_SIZE_128K_CNT);

    ramSize = ramSize * 128U * 1024U; /* since the value is specified in terms
                                       * of
                                       *number of 128K chunks */
    return ramSize;
}

/*Check the Cbuf capability for the OCMC instance passed*/
uint32_t OCMCCbufCapabilityGet(uint32_t baseAddr)
{
    uint32_t regVal;

    regVal = HW_RD_REG32(baseAddr + OCMC_RAM_OCMC_MEM_SIZE_READ);

    regVal = regVal & OCMC_RAM_OCMC_MEM_SIZE_READ_MEM_CBUF_ENABLE_MASK;

    return regVal;
}

/*Check the ECC capability for the OCMC instance passed*/
uint32_t OCMCEccCapabilityGet(uint32_t baseAddr)
{
    uint32_t regVal;

    regVal = HW_RD_REG32(baseAddr + OCMC_RAM_OCMC_MEM_SIZE_READ);

    regVal = regVal & OCMC_RAM_OCMC_MEM_SIZE_READ_MEM_ECC_ENABLE_MASK;

    return regVal;
}

uint32_t OCMCIntStatusRawGet(uint32_t baseAddr,
                             uint8_t intr_group,
                             uint32_t intFlag)
{
    uint32_t status;

    if (intr_group == 0U)
    {
        status = HW_RD_REG32(baseAddr + OCMC_RAM_INTR0_STATUS_RAW_SET);
    }
    else
    {
        status = HW_RD_REG32(baseAddr + OCMC_RAM_INTR1_STATUS_RAW_SET);
    }

    status &= intFlag;
    return status;
}

/*Setting this register will generate a soft interrupt for corresponding
 *interrupt bit*/
void OCMCIntStatusRawSet(uint32_t baseAddr,
                         uint8_t intr_group,
                         uint32_t intFlag)
{
    if (intr_group == 0U)
    {
        HW_WR_REG32(baseAddr + OCMC_RAM_INTR0_STATUS_RAW_SET, intFlag);
    }
    else
    {
        HW_WR_REG32(baseAddr + OCMC_RAM_INTR1_STATUS_RAW_SET, intFlag);
    }
}

uint32_t OCMCIntStatusEnableGet(uint32_t baseAddr,
                                uint8_t intr_group,
                                uint32_t intFlag)
{
    uint32_t status;

    if (intr_group == 0U)
    {
        status = HW_RD_REG32(baseAddr + OCMC_RAM_INTR0_STATUS_ENABLED_CLEAR);
    }
    else
    {
        status = HW_RD_REG32(baseAddr + OCMC_RAM_INTR1_STATUS_ENABLED_CLEAR);
    }

    status &= intFlag;
    return status;
}

void OCMCIntStatusEnableClear(uint32_t baseAddr,
                              uint8_t intr_group,
                              uint32_t intFlag)
{
    if (intr_group == 0U)
    {
        HW_WR_REG32(baseAddr + OCMC_RAM_INTR0_STATUS_ENABLED_CLEAR, intFlag);
    }
    else
    {
        HW_WR_REG32(baseAddr + OCMC_RAM_INTR1_STATUS_ENABLED_CLEAR, intFlag);
    }
}

void OCMCIntEnable(uint32_t baseAddr,
                   uint8_t intr_group,
                   uint32_t intFlag)
{
    if (intr_group == 0U)
    {
        HW_WR_REG32(baseAddr + OCMC_RAM_INTR0_ENABLE_SET, intFlag);
    }
    else
    {
        HW_WR_REG32(baseAddr + OCMC_RAM_INTR1_ENABLE_SET, intFlag);
    }
}

void OCMCIntDisable(uint32_t baseAddr,
                    uint8_t intr_group,
                    uint32_t intFlag)
{
    if (intr_group == 0U)
    {
        HW_WR_REG32(baseAddr + OCMC_RAM_INTR0_ENABLE_CLEAR, intFlag);
    }
    else
    {
        HW_WR_REG32(baseAddr + OCMC_RAM_INTR1_ENABLE_CLEAR, intFlag);
    }
}

uint32_t OCMCIntEnableGet(uint32_t baseAddr,
                          uint8_t intr_group,
                          uint32_t intFlag)
{
    uint32_t status;
    if (intr_group == 0U)
    {
        status = HW_RD_REG32(baseAddr + OCMC_RAM_INTR0_ENABLE_SET);
    }
    else
    {
        status = HW_RD_REG32(baseAddr + OCMC_RAM_INTR1_ENABLE_SET);
    }

    status &= intFlag;

    return status;
}

void OCMCEccConfig(uint32_t baseAddr,
                   ocmc_cfg_ecc_mode ocmc_ecc_mode_cfg,
                   uint32_t cfgEccSecAutoCorrectEn,
                   uint32_t cfgEccErrSrespEn,
                   uint32_t cfgEccOptNonEccReadEn)
{
    uint32_t eccConfig;

    eccConfig = HW_RD_REG32(baseAddr + OCMC_RAM_CFG_OCMC_ECC);

    HW_SET_FIELD32(
        eccConfig,
        OCMC_RAM_CFG_OCMC_ECC_CFG_OCMC_MODE,
        ocmc_ecc_mode_cfg);

    HW_SET_FIELD32(
        eccConfig,
        OCMC_RAM_CFG_OCMC_ECC_CFG_ECC_SEC_AUTO_CORRECT,
        cfgEccSecAutoCorrectEn);

    HW_SET_FIELD32(
        eccConfig,
        OCMC_RAM_CFG_OCMC_ECC_CFG_ECC_ERR_SRESP_EN,
        cfgEccErrSrespEn);

    HW_SET_FIELD32(
        eccConfig,
        OCMC_RAM_CFG_OCMC_ECC_CFG_ECC_OPT_NON_ECC_READ,
        cfgEccOptNonEccReadEn);

    HW_WR_REG32(baseAddr + OCMC_RAM_CFG_OCMC_ECC, eccConfig);
}

uint32_t OCMCRAMBlockEnableStatusGet(uint32_t baseAddr)
{
    uint32_t temp;
    temp = HW_RD_REG32(baseAddr + OCMC_RAM_CFG_OCMC_ECC_MEM_BLK);
    return temp;
}

/*
 * enable = 1 enable block
 * enable = 0 disable block*/
void OCMCRAMBlockEnableCtrl(uint32_t baseAddr,
                            uint32_t enable,
                            uint32_t blockNum)
{
    uint32_t temp;
    temp = HW_RD_REG32(baseAddr + OCMC_RAM_CFG_OCMC_ECC_MEM_BLK);
    if (0U != enable)
    {
        temp |= ((uint32_t) 1U << blockNum);
    }
    else
    {
        temp &= (~((uint32_t) 1U << blockNum));
    }

    HW_WR_REG32(baseAddr + OCMC_RAM_CFG_OCMC_ECC_MEM_BLK, temp);
}

void OCMCEccErrTraceConfig(uint32_t baseAddr,
                           uint32_t secErrCnt,
                           uint32_t dedErrCnt,
                           uint32_t addrErrCnt,
                           uint32_t discardDupErrAddr)
{
    uint32_t value;

    value = HW_RD_REG32(baseAddr + OCMC_RAM_CFG_OCMC_ECC_ERROR);

    HW_SET_FIELD32(value, OCMC_RAM_CFG_OCMC_ECC_ERROR_CFG_SEC_CNT_MAX,
                   secErrCnt);

    HW_SET_FIELD32(value, OCMC_RAM_CFG_OCMC_ECC_ERROR_CFG_DED_CNT_MAX,
                   dedErrCnt);

    HW_SET_FIELD32(
        value,
        OCMC_RAM_CFG_OCMC_ECC_ERROR_CFG_ADDR_ERR_CNT_MAX,
        addrErrCnt);

    HW_SET_FIELD32(
        value,
        OCMC_RAM_CFG_OCMC_ECC_ERROR_CFG_DISCARD_DUP_ADDR,
        discardDupErrAddr);

    HW_WR_REG32(baseAddr + OCMC_RAM_CFG_OCMC_ECC_ERROR, value);
}

void OCMCEccErrClearTraceHist(uint32_t baseAddr,
                              uint32_t errFlag)
{
    HW_WR_REG32(baseAddr + OCMC_RAM_CFG_OCMC_ECC_CLEAR_HIST, errFlag);
}

uint32_t OCMCErrCntStatusGet(uint32_t baseAddr,
                             ocmc_err_cnt_type errType)
{
    uint32_t errCnt;

    errCnt = HW_RD_REG32(baseAddr + OCMC_RAM_STATUS_ERROR_CNT);
    if (OCMC_ECC_SEC_ERR_CNT == errType)
    {
        errCnt =
            (errCnt &
             OCMC_RAM_STATUS_ERROR_CNT_SEC_ERROR_CNT_MASK) >>
            OCMC_RAM_STATUS_ERROR_CNT_SEC_ERROR_CNT_SHIFT;
    }

    if (OCMC_ECC_DED_ERR_CNT == errType)
    {
        errCnt =
            (errCnt &
             OCMC_RAM_STATUS_ERROR_CNT_DED_ERROR_CNT_MASK) >>
            OCMC_RAM_STATUS_ERROR_CNT_DED_ERROR_CNT_SHIFT;
    }

    if (OCMC_ECC_ADDR_ERR_CNT == errType)
    {
        errCnt =
            (errCnt &
             OCMC_RAM_STATUS_ERROR_CNT_ADDR_ERROR_CNT_MASK) >>
            OCMC_RAM_STATUS_ERROR_CNT_ADDR_ERROR_CNT_SHIFT;
    }

    return errCnt;
}

void OCMCCbufEnableCtrl(uint32_t baseAddr,
                        ocmc_buf_id_t buf_id,
                        uint8_t buf_enable)
{
    uint32_t buf_val;

    buf_val = HW_RD_REG32(baseAddr + OCMC_RAM_CFG_OCMC_CBUF_EN);

    if (0U != buf_enable)
    {
        buf_val |=
            ((uint32_t) 1U <<
             ((uint32_t) buf_id + OCMC_RAM_CFG_OCMC_CBUF_EN_CBUF_EN_0_SHIFT));
    }
    else
    {
        buf_val &=
            (~((uint32_t) 1U <<
               ((uint32_t) buf_id + OCMC_RAM_CFG_OCMC_CBUF_EN_CBUF_EN_0_SHIFT)));
    }

    HW_WR_REG32(baseAddr + OCMC_RAM_CFG_OCMC_CBUF_EN, buf_val);
}

uint32_t OCMCCbufEnableStatusGet(uint32_t baseAddr,
                                 ocmc_buf_id_t buf_id)
{
    uint32_t buf_val, ena_status = 1U;

    buf_val = HW_RD_REG32(baseAddr + OCMC_RAM_CFG_OCMC_CBUF_EN);

    buf_val &=
        (ena_status <<
         ((uint32_t) buf_id + OCMC_RAM_CFG_OCMC_CBUF_EN_CBUF_EN_0_SHIFT));

    return buf_val;
}

/*TI_INSPECTED 65 D : MISRAC_2012_R_2.2
 *"Tool Issue - Unable to process HW_WR MACROS " */
void OCMCCbufModeEnableCtrl(uint32_t baseAddr,
                            uint8_t cbuf_enable)
{
    if ((uint8_t) 0U != cbuf_enable)
    {
        HW_WR_FIELD32(
            baseAddr + OCMC_RAM_CFG_OCMC_CBUF_EN,
            OCMC_RAM_CFG_OCMC_CBUF_EN_CBUF_MODE_EN,
            1U);
    }
    else
    {
        HW_WR_FIELD32(
            baseAddr + OCMC_RAM_CFG_OCMC_CBUF_EN,
            OCMC_RAM_CFG_OCMC_CBUF_EN_CBUF_MODE_EN,
            0U);
    }
}

/*
 * Reset circular buffer for the buffer id passed
 */
void OCMCCBufReset(uint32_t baseAddr,
                   ocmc_buf_id_t buf_id)
{
    HW_WR_REG32(
        baseAddr + OCMC_RAM_CFG_OCMC_CBUF_RESET,
        (uint32_t) 1U <<
        ((uint32_t) buf_id +
         OCMC_RAM_CFG_OCMC_CBUF_RESET_CBUF_RESET_0_SHIFT));
}

/*TI_INSPECTED 65 D : MISRAC_2012_R_2.2
 *"Tool Issue - Unable to process HW_WR MACROS " */
void OCMCShortFrameDetectEnableCtrl(uint32_t baseAddr,
                                    uint8_t  short_frame_detect,
                                    uint8_t  prev_eof_sel)
{
    if ((uint8_t) 0U != short_frame_detect)
    {
        /* note that this bit works reverse of normal: is enabled when 0,
         *disabled when 1.*/
        HW_WR_FIELD32(
            baseAddr + OCMC_RAM_CFG_OCMC_CBUF_ERR_HANDLER,
            OCMC_RAM_CFG_OCMC_CBUF_ERR_HANDLER_SHORT_FRAME_DETECT_CHECK_EN,
            0U);
    }
    else
    {
        /* functionality to be disabled.
         * write 1 to disable
         */
        HW_WR_FIELD32(
            baseAddr + OCMC_RAM_CFG_OCMC_CBUF_ERR_HANDLER,
            OCMC_RAM_CFG_OCMC_CBUF_ERR_HANDLER_SHORT_FRAME_DETECT_CHECK_EN,
            1U);
    }

    /* setup prev_eof_sel history bit*/
    if ((uint8_t) 0U != prev_eof_sel)
    {
        HW_WR_FIELD32(
            baseAddr + OCMC_RAM_CFG_OCMC_CBUF_ERR_HANDLER,
            OCMC_RAM_CFG_OCMC_CBUF_ERR_HANDLER_SHORT_FRAME_PREV_EOF_SEL,
            1U);
    }
    else
    {
        HW_WR_FIELD32(
            baseAddr + OCMC_RAM_CFG_OCMC_CBUF_ERR_HANDLER,
            OCMC_RAM_CFG_OCMC_CBUF_ERR_HANDLER_SHORT_FRAME_PREV_EOF_SEL,
            0U);
    }
}

void OCMCOverflowConfigure(uint32_t baseAddr,
                           uint8_t overflow_detect,
                           ocmc_wr_overflow_handler_t overflow_handler,
                           ocmc_wr_overflow_reenable_t overflow_check_reenable)
{
    uint32_t buf_val;

    buf_val = HW_RD_REG32(baseAddr + OCMC_RAM_CFG_OCMC_CBUF_ERR_HANDLER);
    if ((uint8_t) 0U != overflow_detect)
    {
        /* note that this bit works reverse of normal: is enabled when 0,
         *disabled when 1.*/
        HW_SET_FIELD32(
            buf_val,
            OCMC_RAM_CFG_OCMC_CBUF_ERR_HANDLER_OVERFLOW_ERR_CHECK_EN,
            0U);
    }
    else
    {
        /* functionality to be disabled.*/
        /* write 1 to disable */
        HW_SET_FIELD32(
            buf_val,
            OCMC_RAM_CFG_OCMC_CBUF_ERR_HANDLER_OVERFLOW_ERR_CHECK_EN,
            1U);
    }

    /* configure write handler selection.*/
    HW_SET_FIELD32(
        buf_val,
        OCMC_RAM_CFG_OCMC_CBUF_ERR_HANDLER_OVERFLOW_WRITE_HANDLER_SEL,
        overflow_handler);

    /* configure overflow check re_enable selection.*/
    HW_SET_FIELD32(
        buf_val,
        OCMC_RAM_CFG_OCMC_CBUF_ERR_HANDLER_OVERFLOW_CHECK_REENABLE_SEL,
        overflow_check_reenable);

    HW_WR_REG32(baseAddr + OCMC_RAM_CFG_OCMC_CBUF_ERR_HANDLER, buf_val);
}

void OCMCUnderflowConfigure(uint32_t baseAddr,
                            uint8_t underflow_detect,
                            uint8_t underflow_last_cbuf_slice_disable)
{
    uint32_t buf_val;

    buf_val = HW_RD_REG32(baseAddr + OCMC_RAM_CFG_OCMC_CBUF_ERR_HANDLER);
    if ((uint8_t) 0U != underflow_detect)
    {
        /* note that this bit works reverse of normal: is enabled when 0,
         * disabled when 1.*/
        HW_SET_FIELD32(
            buf_val,
            OCMC_RAM_CFG_OCMC_CBUF_ERR_HANDLER_UNDERFLOW_ERR_CHECK_EN,
            0U);
    }
    else
    {
        /* functionality to be disabled.*/
        /* write 1 to disable */
        HW_SET_FIELD32(
            buf_val,
            OCMC_RAM_CFG_OCMC_CBUF_ERR_HANDLER_UNDERFLOW_ERR_CHECK_EN,
            1U);
    }

    /* configure underflow_last_cbuf_slice_disable.*/
    if ((uint8_t) 0U != underflow_last_cbuf_slice_disable)
    {
        /* note reverse operation: 0 to enable, 1 to disable*/
        HW_SET_FIELD32(
            buf_val,
            OCMC_RAM_CFG_OCMC_CBUF_ERR_HANDLER_UNDERFLOW_LAST_CBUF_SLICE_DISABLE,
            1U);
    }
    else
    {
        HW_SET_FIELD32(
            buf_val,
            OCMC_RAM_CFG_OCMC_CBUF_ERR_HANDLER_UNDERFLOW_LAST_CBUF_SLICE_DISABLE,
            0U);
    }

    HW_WR_REG32(baseAddr + OCMC_RAM_CFG_OCMC_CBUF_ERR_HANDLER, buf_val);
}

/*OCMC_Get_CBUF_Error_Status for error type and buffer id passed*/
uint32_t OCMCCbufErrorStatusGet(uint32_t        baseAddr,
                                ocmc_cbuf_err_t cbuf_err_type,
                                uint32_t        cBufId)
{
    uint32_t regVal;

    regVal =
        HW_RD_REG32(baseAddr + OCMC_RAM_STATUS_CBUF_WR_OUT_OF_RANGE_ERR +
                    (((uint32_t) cbuf_err_type -
                      e_cbuf_stat_wr_out_of_range) * 4U));
    regVal &= ((uint32_t) 1U << cBufId);

    return regVal;
}

/*OCMC_CLear c_buf Error status for error type and buffer id passed*/
void OCMCCbufErrorStatusClear(uint32_t baseAddr,
                              ocmc_cbuf_err_t cbuf_err_type,
                              uint32_t cBufId)
{
    HW_WR_REG32(
        baseAddr + OCMC_RAM_STATUS_CBUF_WR_OUT_OF_RANGE_ERR +
        (((uint32_t) cbuf_err_type -
          e_cbuf_stat_wr_out_of_range) * 4U),
        (uint32_t) 1U << cBufId);
}

void OCMCVBufStartAddrSet(uint32_t baseAddr,
                          ocmc_buf_id_t buf_id,
                          ocmc_addr_t vbuf_start)
{
    uint32_t vbuf_start_addr;
    vbuf_start_addr = vbuf_start - OCMCCBUFBaseAddrGet(baseAddr);

    HW_WR_REG32(
        baseAddr + OCMC_RAM_CBUF_VBUF_START_ADDR((uint32_t) buf_id),
        vbuf_start_addr);
}

uint32_t OCMCVBufStartAddrGet(uint32_t baseAddr,
                              ocmc_buf_id_t buf_id)
{
    uint32_t vbuf_start;

    vbuf_start = HW_RD_REG32(
        baseAddr + OCMC_RAM_CBUF_VBUF_START_ADDR((uint32_t) buf_id));

    /* remove the upper most MSB '1' to avoid chip level confusion with address
     *range >= 0x80000000 (EMIF range)*/
    if (0U != (vbuf_start & 0x80000000U))
    {
        vbuf_start = vbuf_start ^ 0x80000000U;
    }
    vbuf_start += OCMCCBUFBaseAddrGet(baseAddr);
    return vbuf_start;
}

void OCMCVBufEndAddrSet(uint32_t baseAddr,
                        ocmc_buf_id_t buf_id,
                        ocmc_addr_t vbuf_end)
{
    uint32_t vbuf_end_addr;
    vbuf_end_addr = vbuf_end - OCMCCBUFBaseAddrGet(baseAddr);

    HW_WR_REG32(
        baseAddr + OCMC_RAM_CBUF_VBUF_END_ADDR((uint32_t) buf_id),
        vbuf_end_addr);
}

uint32_t OCMCVBufEndAddrGet(uint32_t baseAddr,
                            ocmc_buf_id_t buf_id)
{
    uint32_t vbuf_end;
    vbuf_end = HW_RD_REG32(
        baseAddr + OCMC_RAM_CBUF_VBUF_END_ADDR((uint32_t) buf_id));

    /* remove the upper most MSB '1' to avoid chip level confusion with address
     *range >= 0x80000000 (EMIF range)*/
    if (0U != (vbuf_end & 0x80000000U))
    {
        vbuf_end = vbuf_end ^ 0x80000000U;
    }
    vbuf_end += OCMCCBUFBaseAddrGet(baseAddr);
    return vbuf_end;
}

void OCMCCBufStartAddrSet(uint32_t baseAddr,
                          ocmc_buf_id_t buf_id,
                          ocmc_addr_t cbuf_start)
{
    uint32_t ocmc_start_addr;
    ocmc_start_addr = cbuf_start - OCMCBaseAddrGet(baseAddr);

    HW_WR_REG32(
        baseAddr + OCMC_RAM_CBUF_OCMC_START_ADDR((uint32_t) buf_id),
        ocmc_start_addr);
}

uint32_t OCMCCBufStartAddrGet(uint32_t baseAddr,
                              ocmc_buf_id_t buf_id)
{
    uint32_t cbuf_start;

    cbuf_start = HW_RD_REG32(
        baseAddr + OCMC_RAM_CBUF_OCMC_START_ADDR((uint32_t) buf_id));

    cbuf_start += OCMCBaseAddrGet(baseAddr);
    return cbuf_start;
}

void OCMCCBufSizeSet(uint32_t baseAddr,
                     ocmc_buf_id_t buf_id,
                     uint32_t cbuf_size)
{
    HW_WR_REG32(
        baseAddr + OCMC_RAM_CBUF_OCMC_BUF_SIZE((uint32_t) buf_id),
        cbuf_size);
}

uint32_t OCMCCBufSizeGet(uint32_t baseAddr,
                         ocmc_buf_id_t buf_id)
{
    uint32_t cbuf_size;

    cbuf_size = HW_RD_REG32(
        baseAddr + OCMC_RAM_CBUF_OCMC_BUF_SIZE((uint32_t) buf_id));
    return cbuf_size;
}

uint32_t OCMCCBufLastRdAddrGet(uint32_t baseAddr,
                               ocmc_buf_id_t buf_id)
{
    uint32_t regVal;

    regVal =
        HW_RD_REG32(baseAddr + OCMC_RAM_CBUF_LAST_RD_ADDR((uint32_t) buf_id));

    if (0U != (regVal & 0x80000000U))
    {
        regVal = regVal ^ 0x80000000U;
    }
    regVal += OCMCCBUFBaseAddrGet(baseAddr);
    return regVal;
}

uint32_t OCMCCBufLastWrAddrGet(uint32_t baseAddr,
                               ocmc_buf_id_t buf_id)
{
    uint32_t regVal;

    regVal =
        HW_RD_REG32(baseAddr + OCMC_RAM_CBUF_LAST_WR_ADDR((uint32_t) buf_id));

    if (0U != (regVal & 0x80000000U))
    {
        regVal = regVal ^ 0x80000000U;
    }
    regVal += OCMCCBUFBaseAddrGet(baseAddr);
    return regVal;
}

uint32_t OCMCBaseAddrGet(uint32_t baseAddr)
{
    uint32_t ocmcBase;
    switch (baseAddr)
    {
        case (uint32_t) SOC_OCMC_RAM1_CFG_BASE:
            ocmcBase = (uint32_t) SOC_OCMC_RAM1_BASE;
            break;
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_AM572x) || defined (SOC_AM574x)
        case (uint32_t) SOC_OCMC_RAM2_CFG_BASE:
            ocmcBase = (uint32_t) SOC_OCMC_RAM2_BASE;
            break;

        case (uint32_t) SOC_OCMC_RAM3_CFG_BASE:
            ocmcBase = (uint32_t) SOC_OCMC_RAM3_BASE;
            break;
#endif
        default:
            ocmcBase = (uint32_t) SOC_OCMC_RAM1_BASE;
            break;
    }
    return ocmcBase;
}

uint32_t OCMCCBUFBaseAddrGet(uint32_t baseAddr)
{
    uint32_t vbufBase;
    switch (baseAddr)
    {
        case (uint32_t) SOC_OCMC_RAM1_CFG_BASE:
            vbufBase = (uint32_t) SOC_OCMC_RAM1_CBUF_BASE;
            break;
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_AM572x) || defined (SOC_AM574x)
        case (uint32_t) SOC_OCMC_RAM2_CFG_BASE:
            vbufBase = (uint32_t) SOC_OCMC_RAM2_CBUF_BASE;
            break;

        case (uint32_t) SOC_OCMC_RAM3_CFG_BASE:
            vbufBase = (uint32_t) SOC_OCMC_RAM3_CBUF_BASE;
            break;
#endif
        default:
            vbufBase = (uint32_t) SOC_OCMC_RAM1_CBUF_BASE;
            break;
    }

    return vbufBase;
}

uint32_t OCMCCBUFSizeGet(uint32_t baseAddr)
{
    uint32_t ocmcVBufSize;

    switch (baseAddr)
    {
        case (uint32_t) SOC_OCMC_RAM1_CFG_BASE:
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_AM572x) || defined (SOC_AM574x)
        case (uint32_t) SOC_OCMC_RAM2_CFG_BASE:
        case (uint32_t) SOC_OCMC_RAM3_CFG_BASE:
#endif
            ocmcVBufSize = (uint32_t) OCMC_VBUF_SIZE;
            break;

        default:
            ocmcVBufSize = (uint32_t) OCMC_VBUF_SIZE;
            break;
    }

    return ocmcVBufSize;
}

uint32_t OCMCEccErrTraceAddrGet(uint32_t baseAddr,
                                ocmc_ecc_err_t errType)
{
    uint32_t errTraceAddr;

    if (OCMC_ECC_SEC_ERR == errType)
    {
        errTraceAddr = HW_RD_FIELD32(
            baseAddr + OCMC_RAM_STATUS_SEC_ERROR_TRACE,
            OCMC_RAM_STATUS_SEC_ERROR_TRACE_ADDRESS_128BIT);
    }
    else if (OCMC_ECC_DED_ERR == errType)
    {
        errTraceAddr = HW_RD_FIELD32(
            baseAddr + OCMC_RAM_STATUS_DED_ERROR_TRACE,
            OCMC_RAM_STATUS_DED_ERROR_TRACE_ADDRESS_128BIT);
    }
    else if (OCMC_ECC_ADDR_ERR == errType)
    {
        errTraceAddr = HW_RD_FIELD32(
            baseAddr + OCMC_RAM_STATUS_ADDR_TRANSLATION_ERROR_TRACE,
            OCMC_RAM_STATUS_ADDR_TRANSLATION_ERROR_TRACE_ADDRESS_128BIT);
    }
    else
    {
        /* Invalid case */
        errTraceAddr = 0U;
    }

    return errTraceAddr;
}

uint32_t OCMCSecEccErrDistributionStatusGet(uint32_t                baseAddr,
                                            ocmc_sec_ecc_err_dist_t errType)
{
    uint32_t errBitDistStatus;

    if (OCMC_ECC_SEC_ERR_DIST_0 == errType)
    {
        errBitDistStatus = HW_RD_REG32(
            baseAddr + OCMC_RAM_STATUS_SEC_ERROR_DISTR_0);
    }
    else if (OCMC_ECC_SEC_ERR_DIST_1 == errType)
    {
        errBitDistStatus = HW_RD_REG32(
            baseAddr + OCMC_RAM_STATUS_SEC_ERROR_DISTR_1);
    }
    else if (OCMC_ECC_SEC_ERR_DIST_2 == errType)
    {
        errBitDistStatus = HW_RD_REG32(
            baseAddr + OCMC_RAM_STATUS_SEC_ERROR_DISTR_2);
    }
    else if (OCMC_ECC_SEC_ERR_DIST_3 == errType)
    {
        errBitDistStatus = HW_RD_REG32(
            baseAddr + OCMC_RAM_STATUS_SEC_ERROR_DISTR_3);
    }
    else
    {
        /* Invalid case */
        errBitDistStatus = 0U;
    }

    return errBitDistStatus;
}

