/*
 *  Copyright (c) Texas Instruments Incorporated 2013-2016
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
 */

/**
 *  \file mmcsd_proto.c
 *
 *  \brief this file defines the MMC/SD standard operations
 *
 */

#include <stdint.h>
#include <string.h>
#include <ti/csl/soc.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/csl/csl_mmcsd.h>
#include <ti/drv/stw_lld/fatlib/mmcsd_proto.h>
#include <ti/drv/stw_lld/fatlib/hsmmcsd_edma.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>

#if defined (SOC_TDA3XX)
static uint32_t MMCSDvirt2phy(mmcsdCtrlInfo *ctrl, void *ptr);
#endif

/**
 * \brief   This function sends the command to MMCSD.
 *
 * \param    mmcsdCtrlInfo It holds the mmcsd control information.
 *
 * \param    mmcsdCmd It determines the mmcsd cmd
 *
 * \return   status of the command.
 *
 **/
uint32_t MMCSDCmdSend(mmcsdCtrlInfo *ctrl, mmcsdCmd *c)
{
    return ctrl->cmdSend(ctrl, c);
}

/**
 * \brief   This function sends the application command to MMCSD.
 *
 * \param    mmcsdCtrlInfo It holds the mmcsd control information.
 *
 * \param    mmcsdCmd It determines the mmcsd cmd
 *
 * \return   status of the command.
 *
 **/
uint32_t MMCSDAppCmdSend(mmcsdCtrlInfo *ctrl, mmcsdCmd *c)
{
    uint32_t status = 0;
    mmcsdCmd capp;

    /* APP cmd should be preceeded by a CMD55 */
    capp.idx   = SD_CMD(55);
    capp.flags = 0;
    capp.arg   = ctrl->card->rca << 16;
    status     = MMCSDCmdSend(ctrl, &capp);
    if (status == 0)
    {
        /* return safely, since we cannot continue if CMD55 fails */
        return 0;
    }

    status = MMCSDCmdSend(ctrl, c);

    return status;
}

uint32_t MMCSDBlockSizeSet(mmcsdCtrlInfo *ctrl)
{
    uint32_t       status = 0;
    mmcsdCmd       cmd;
    mmcsdCardInfo *card = ctrl->card;

    do
    {
        cmd.idx   = SD_CMD(16);
        cmd.flags = SD_CMDRSP_NONE;
        cmd.arg   = 1 << 10; /*1024*/
        status    = MMCSDCmdSend(ctrl, &cmd);

        if (status == 1)
        {
            ctrl->blocksize = 1024;
            card->blkLen    = ctrl->blocksize;
            card->nBlks     = card->size / card->blkLen;
            break;
        }

        cmd.idx   = SD_CMD(16);
        cmd.flags = SD_CMDRSP_NONE;
        cmd.arg   = 1 << 9; /*512*/
        status    = MMCSDCmdSend(ctrl, &cmd);
        if (status == 1)
        {
            ctrl->blocksize = 512;
            card->blkLen    = ctrl->blocksize;
            card->nBlks     = card->size / card->blkLen;
            break;
        }
    } while (0);

    return status;
}

/**
 * \brief   Configure the MMC/SD bus width
 *
 * \param    mmcsdCtrlInfo It holds the mmcsd control information.
 *
 * \param   buswidth   SD/MMC bus width.\n
 *
 *  buswidth can take the values.\n
 *     HS_MMCSD_BUS_WIDTH_4BIT.\n
 *     HS_MMCSD_BUS_WIDTH_1BIT.\n
 *
 * \return  None.
 *
 **/
uint32_t MMCSDBusWidthSet(mmcsdCtrlInfo *ctrl)
{
    uint32_t status = 0;
    mmcsdCmd capp;

    capp.idx   = SD_CMD(6);
    capp.arg   = SD_BUS_WIDTH_1BIT;
    capp.flags = 0;

    /* Set 4-bit bus width*/
    if (ctrl->busWidth & SD_BUS_WIDTH_4BIT)
    {
        capp.arg = SD_BUS_WIDTH_4BIT;
    }

    capp.arg = capp.arg >> 1;

    status = MMCSDAppCmdSend(ctrl, &capp);

    /*If 4-bit mode fails - set to 1-bit mode */
    if (status == 0)
    {
        if (ctrl->busWidth & SD_BUS_WIDTH_1BIT)
        {
            capp.arg = SD_BUS_WIDTH_1BIT;
        }

        capp.arg = capp.arg >> 1;

        status = MMCSDAppCmdSend(ctrl, &capp);
    }

    if (1 == status)
    {
        if (capp.arg == 0)
        {
            ctrl->busWidthConfig(ctrl, SD_BUS_WIDTH_1BIT);
        }
        else
        {
            ctrl->busWidthConfig(ctrl, SD_BUS_WIDTH_4BIT);
        }
    }
    return status;
}

/**
 * \brief    This function configures the transmission speed in MMCSD.
 *
 * \param    mmcsdCtrlInfo It holds the mmcsd control information.
 *
 * \returns  1 - successfull.
 *           0 - failed.
 **/
uint32_t MMCSDTranSpeedSet(mmcsdCtrlInfo *ctrl)
{
    mmcsdCardInfo *card = ctrl->card;
    uint32_t       speed;
    int status;

    speed = card->tranSpeed;

    if (speed == SD_TRANSPEED_50MBPS)
    {
        status      = ctrl->busFreqConfig(ctrl, 50000000);
        ctrl->opClk = 50000000;
    }
    else
    {
        status      = ctrl->busFreqConfig(ctrl, 25000000);
        ctrl->opClk = 25000000;
    }

    if (status <= 0)
    {
        return 0;
    }

    return 1;
}

/**
 * \brief   This function resets the MMCSD card.
 *
 * \param    mmcsdCtrlInfo It holds the mmcsd control information.
 *
 * \returns  1 - successfull reset of card.
 *           0 - fails to reset the card.
 **/
uint32_t MMCSDCardReset(mmcsdCtrlInfo *ctrl)
{
    uint32_t status = 0;
    mmcsdCmd cmd;

    cmd.idx   = SD_CMD(0);
    cmd.flags = SD_CMDRSP_NONE;
    cmd.arg   = 0;

    status = MMCSDCmdSend(ctrl, &cmd);

    return status;
}

/**
 * \brief   This function sends the stop command to MMCSD card.
 *
 * \param    mmcsdCtrlInfo It holds the mmcsd control information.
 *
 * \returns  1 - successfully sends stop command to card.
 *           0 - fails to send stop command to card.
 **/
uint32_t MMCSDStopCmdSend(mmcsdCtrlInfo *ctrl)
{
    uint32_t status = 0;
    mmcsdCmd cmd;

    cmd.idx   = SD_CMD(12);
    cmd.flags = SD_CMDRSP_BUSY;
    cmd.arg   = 0;

    MMCSDCmdSend(ctrl, &cmd);

    /* Get transfer status */
    status = ctrl->xferStatusGet(ctrl);

    return status;
}

/**
 * \brief   This function determines the type of MMCSD card.
 *
 * \param    mmcsdCtrlInfo It holds the mmcsd control information.
 *
 * \returns  type of the MMCSD card
 *
 **/
uint32_t MMCSDCardTypeCheck(mmcsdCtrlInfo *ctrl)
{
    uint32_t status;
    mmcsdCmd cmd;

    /*
     * Card type can be found by sending CMD55. If the card responds,
     * it is a SD card. Else, we assume it is a MMC Card
     */

    cmd.idx   = SD_CMD(55);
    cmd.flags = 0;
    cmd.arg   = 0;
    status    = MMCSDAppCmdSend(ctrl, &cmd);

    return status;
}

/**
 * \brief   This function intializes the mmcsdcontroller.
 *
 * \param    mmcsdCtrlInfo It holds the mmcsd control information.
 *
 * \returns  1 - Intialization is successfull.
 *           0 - Intialization is failed.
 **/
uint32_t MMCSDCtrlInit(mmcsdCtrlInfo *ctrl)
{
    return ctrl->ctrlInit(ctrl);
}

/**
 * \brief   This function determines whether card is persent or not.
 *
 * \param    mmcsdCtrlInfo It holds the mmcsd control information.
 *
 * \returns  1 - Card is present.
 *           0 - Card is not present.
 **/
uint32_t MMCSDCardPresent(mmcsdCtrlInfo *ctrl)
{
    return ctrl->cardPresent(ctrl);
}

/**
 * \brief   Enables the controller events to generate a h/w interrupt request
 *
 * \param    mmcsdCtrlInfo It holds the mmcsd control information.
 *
 * \return   none
 *
 **/
void MMCSDIntEnable(mmcsdCtrlInfo *ctrl)
{
    ctrl->intrEnable(ctrl);

    return;
}

/**
 * \brief   This function intializes the MMCSD Card.
 *
 * \param    mmcsdCtrlInfo It holds the mmcsd control information.
 *
 * \returns  1 - Intialization is successfull.
 *           0 - Intialization is failed.
 **/
uint32_t MMCSDCardInit(mmcsdCtrlInfo *ctrl)
{
    mmcsdCardInfo *card   = ctrl->card;
    uint32_t       retry  = 0xFFFF;
    uint32_t       status = 0;
    mmcsdCmd       cmd;

    card->ctrl = ctrl;

    /* CMD0 - reset card */
    status = MMCSDCardReset(ctrl);
    if (status == 0)
    {
        return 0;
    }

    /* Returns 1 for a SD card, 0 for a non-SD card */
    status = MMCSDCardTypeCheck(ctrl);

    if (status == 1)
    {
        /* SD Card */
        ctrl->card->cardType = MMCSD_CARD_SD;

        /* CMD0 - reset card */
        status = MMCSDCardReset(ctrl);
        if (status == 0)
        {
            return 0;
        }

        /* CMD8 - send oper voltage */
        cmd.idx   = SD_CMD(8);
        cmd.flags = 0;
        cmd.arg   = (SD_CHECK_PATTERN | SD_VOLT_2P7_3P6);

        status = MMCSDCmdSend(ctrl, &cmd);
        if (status == 0)
        {
            /* If the cmd fails, it can be due to version < 2.0, since
             * we are currently supporting high voltage cards only
             */
        }

        /* Go ahead and send ACMD41, with host capabilities */
        cmd.idx   = SD_CMD(41);
        cmd.flags = 0;
        cmd.arg   = SD_OCR_HIGH_CAPACITY | SD_OCR_VDD_WILDCARD;

        status = MMCSDAppCmdSend(ctrl, &cmd);
        if (status == 0)
        {
            return 0;
        }

#ifndef ZEBU
        /* Poll until we get the card status (BIT31 of OCR) is powered up */
        do {
            cmd.idx   = SD_CMD(41);
            cmd.flags = 0;
            cmd.arg   = SD_OCR_HIGH_CAPACITY | SD_OCR_VDD_WILDCARD;

            status = MMCSDAppCmdSend(ctrl, &cmd);
            if (status == 0)
            {
                retry = 0;
            }
        } while (!(cmd.rsp[0] & ((uint32_t) BIT(31))) && retry--);

        if (retry == 0)
        {
            /* No point in continuing */
            return 0;
        }
#endif

        card->ocr = cmd.rsp[0];

        card->highCap = (card->ocr & SD_OCR_HIGH_CAPACITY) ? 1 : 0;

        /* Send CMD2, to get the card identification register */
        cmd.idx   = SD_CMD(2);
        cmd.flags = SD_CMDRSP_136BITS;
        cmd.arg   = 0;

        status = MMCSDCmdSend(ctrl, &cmd);

        memcpy(card->raw_cid, cmd.rsp, 16);

        if (status == 0)
        {
            return 0;
        }

        /* Send CMD3, to get the card relative address */
        cmd.idx   = SD_CMD(3);
        cmd.flags = 0;
        cmd.arg   = 0;

        status = MMCSDCmdSend(ctrl, &cmd);

        card->rca = SD_RCA_ADDR(cmd.rsp[0]);

        if (status == 0)
        {
            return 0;
        }

        /*set the block size*/
        MMCSDBlockSizeSet(ctrl);

        /* Send CMD9, to get the card specific data */
        cmd.idx   = SD_CMD(9);
        cmd.flags = SD_CMDRSP_136BITS;
        cmd.arg   = card->rca << 16;

        status = MMCSDCmdSend(ctrl, &cmd);

        memcpy(card->raw_csd, cmd.rsp, 16);

        if (status == 0)
        {
            return 0;
        }

        if (SD_CARD_CSD_VERSION(card))
        {
            card->tranSpeed = SD_CARD1_TRANSPEED(card);
            card->blkLen    = 1 << (SD_CARD1_RDBLKLEN(card));
            card->size      = SD_CARD1_SIZE(card);
            card->nBlks     = card->size / card->blkLen;
            ctrl->blocksize = card->blkLen;
        }
        else
        {
            card->tranSpeed = SD_CARD0_TRANSPEED(card);
            card->blkLen    = 1 << (SD_CARD0_RDBLKLEN(card));
            card->nBlks     = SD_CARD0_NUMBLK(card);
            card->size      = SD_CARD0_SIZE(card);
            ctrl->blocksize = card->blkLen;
        }

        /* Set data block length to 512 (for byte addressing cards) */
        if (!(card->highCap))
        {
            cmd.idx   = SD_CMD(16);
            cmd.flags = SD_CMDRSP_NONE;
            cmd.arg   = 512;
            status    = MMCSDCmdSend(ctrl, &cmd);

            if (status == 0)
            {
                return 0;
            }
            else
            {
                ctrl->blocksize = 512;
                card->blkLen    = ctrl->blocksize;
            }
        }

        /* Select the card */
        cmd.idx   = SD_CMD(7);
        cmd.flags = SD_CMDRSP_BUSY;
        cmd.arg   = card->rca << 16;

        status = MMCSDCmdSend(ctrl, &cmd);
        if (status == 0)
        {
            return 0;
        }

        /*
         * Send ACMD51, to get the SD Configuration register details.
         * Note, this needs data transfer (on data lines).
         */
        cmd.idx   = SD_CMD(55);
        cmd.flags = 0;
        cmd.arg   = card->rca << 16;

        status = MMCSDCmdSend(ctrl, &cmd);
        if (status == 0)
        {
            return 0;
        }

        ctrl->xferSetup(ctrl, 1, ctrl->card->raw_scr, 8, 1);

        cmd.idx   = SD_CMD(51);
        cmd.flags = SD_CMDRSP_READ | SD_CMDRSP_DATA;
        cmd.arg   = card->rca << 16;
        cmd.nblks = 1;
        cmd.data  = (signed char *) card->raw_scr;

        status = MMCSDCmdSend(ctrl, &cmd);
        ctrl->xferStatusGet(ctrl);
        if (status == 0)
        {
            return 0;
        }

        card->sd_ver   = SD_CARD_VERSION(card);
        card->busWidth = SD_CARD_BUSWIDTH(card);
    }
    else
    {
        /*Return fail if non-SD card*/
        return 0;
    }

    return 1;
}

/**
 * \brief   This function sends the write command to MMCSD card.
 *
 * \param    mmcsdCtrlInfo It holds the mmcsd control information.
 * \param    ptr           It determines the address from where data has to
 *                         written
 * \param    block         It determines to which block data to be written
 * \param    nblks         It determines the number of blocks to be written
 *
 * \returns  1 - successfull written of data.
 *           0 - failure to write the data.
 **/
uint32_t MMCSDWriteCmdSend(mmcsdCtrlInfo *ctrl, void *ptr,
                           uint32_t block,
                           uint32_t nblks)
{
    mmcsdCardInfo     *card   = ctrl->card;
    uint32_t           status = 0;
    uint32_t           address;
    uint32_t           offset = 0U;
    mmcsdCmd           cmd;
    hsmmcsdEdmaParam_t edmaParam;

#if defined (SOC_TDA3XX)
    /* For tda3xx, translate virtual address to physical address (L3's view)
     * before doing EDMA
     */
    offset = MMCSDvirt2phy(ctrl, ptr);
#endif

    /*
     * Address is in blks for high cap cards and in actual bytes
     * for standard capacity cards
     */
    if (card->highCap)
    {
        address = block;
    }
    else
    {
        address = block * card->blkLen;
    }

    ctrl->xferSetup(ctrl, 0, ptr, card->blkLen, nblks);

    cmd.flags = SD_CMDRSP_WRITE | SD_CMDRSP_DATA;
    cmd.arg   = address;
    cmd.nblks = nblks;

    if (nblks > 1)
    {
        cmd.idx    = SD_CMD(25);
        cmd.flags |= SD_CMDRSP_ABORT;
    }
    else
    {
        cmd.idx = SD_CMD(24);
    }

    /*Enable the EDMA channel*/
    ctrl->dmaEnable     = 1;
    edmaParam.baseAddr  = SOC_EDMA_TPCC_BASE_VIRT;
    edmaParam.srcBfr    = (uint32_t) ptr + offset;
    edmaParam.dstBfr    = ctrl->memBase + MMC_DATA;
    edmaParam.chan      = ctrl->edmaTxChan;
    edmaParam.rwflag    = FLAG_WRITE;
    edmaParam.length    = card->blkLen * nblks;
    edmaParam.blockSize = card->blkLen;
    edmaParam.dreq      = ctrl->edmaTxDreq; /*event src*/

    /* Write back buffer from cache to DDR before EDMA transfer */
    BspOsal_cacheWb(
        ptr,
        (card->blkLen * nblks),
        BSP_OSAL_CT_ALLD,
        BSP_OSAL_WAIT_FOREVER);

    status = HSMMCSDEdmaTransfer(&edmaParam);
    if (status == 0)
    {
        return 0;
    }

    status = MMCSDCmdSend(ctrl, &cmd);
    if (status == 0)
    {
        return 0;
    }

    /*If DMA Mode*/
    if (ctrl->dmaEnable == 1)
    {
        HSMMCSDEdmaWaitTransfer(ctrl->edmaTxChan);
    }

    status = ctrl->xferStatusGet(ctrl);
    if (status == 0)
    {
        return 0;
    }

    /* Send a STOP */
    if (cmd.nblks > 1)
    {
        status = MMCSDStopCmdSend(ctrl);
        if (status == 0)
        {
            return 0;
        }
    }

    if (ctrl->dmaEnable == 1)
    {
        /*Close the EDMA channel*/
        HSMMCSDEdmaClose(&edmaParam);
        ctrl->dmaEnable = 0;
    }

    return 1;
}

/**
 * \brief   This function sends the write command to MMCSD card.
 *
 * \param    mmcsdCtrlInfo It holds the mmcsd control information.
 * \param    ptr           It determines the address to where data has to read
 * \param    block         It determines from which block data to be read
 * \param    nblks         It determines the number of blocks to be read
 *
 * \returns  1 - successful reading of data.
 *           0 - failure to the data.
 **/
uint32_t MMCSDReadCmdSend(mmcsdCtrlInfo *ctrl, void *ptr,
                          uint32_t block,
                          uint32_t nblks)
{
    mmcsdCardInfo     *card   = ctrl->card;
    uint32_t           status = 0;
    uint32_t           address;
    uint32_t           offset = 0U;
    mmcsdCmd           cmd;
    hsmmcsdEdmaParam_t edmaParam;

#if defined (SOC_TDA3XX)
    /* For tda3xx, translate virtual address to physical address (L3's view)
     * before doing EDMA
     */
    offset = MMCSDvirt2phy(ctrl, ptr);
#endif

    /*
     * Address is in blks for high cap cards and in actual bytes
     * for standard capacity cards
     */
    if (card->highCap)
    {
        address = block;
    }
    else
    {
        address = block * card->blkLen;
    }

    ctrl->xferSetup(ctrl, 1, ptr, card->blkLen, nblks);

    cmd.flags = SD_CMDRSP_READ | SD_CMDRSP_DATA;
    cmd.arg   = address;
    cmd.nblks = nblks;

    if (nblks > 1)
    {
        cmd.flags |= SD_CMDRSP_ABORT;
        cmd.idx    = SD_CMD(18);
    }
    else
    {
        cmd.idx = SD_CMD(17);
    }

    /*Enable the EDMA channel*/
    ctrl->dmaEnable     = 1;
    edmaParam.baseAddr  = SOC_EDMA_TPCC_BASE_VIRT;
    edmaParam.srcBfr    = ctrl->memBase + MMC_DATA;
    edmaParam.dstBfr    = (uint32_t) ptr + offset;
    edmaParam.chan      = ctrl->edmaRxChan;
    edmaParam.rwflag    = FLAG_READ;
    edmaParam.length    = card->blkLen * nblks;
    edmaParam.blockSize = card->blkLen;
    edmaParam.dreq      = ctrl->edmaRxDreq; /*event src*/

    /* Write back edges of buffer to DDR before EDMA transfer */
    /* NOTE: If it were guaranteed that the buffer was aligned to cache
     * lines, then this wouldn't be required, but since we can not guarantee
     * this (the buffer is a sub-element of the fatFs structures) we should
     * write back the edges of the buffer before the transfer so that when
     * we invalidate after the transfer, we don't loose any state data from
     * the other part of the surrounding data structures. */
    BspOsal_cacheWb(ptr, 1, BSP_OSAL_CT_ALLD, BSP_OSAL_WAIT_FOREVER);
    BspOsal_cacheWb(
        (void *) ((uint32_t) ptr + (card->blkLen * nblks) - 1),
        1,
        BSP_OSAL_CT_ALLD,
        BSP_OSAL_WAIT_FOREVER);

    status = HSMMCSDEdmaTransfer(&edmaParam);
    if (status == 0)
    {
        return 0;
    }

    status = MMCSDCmdSend(ctrl, &cmd);
    if (status == 0)
    {
        return 0;
    }

    /*If DMA Mode*/
    if (ctrl->dmaEnable == 1)
    {
        HSMMCSDEdmaWaitTransfer(ctrl->edmaRxChan);
    }

    status = ctrl->xferStatusGet(ctrl);
    if (status == 0)
    {
        return 0;
    }

    /* Send a STOP */
    if (cmd.nblks > 1)
    {
        status = MMCSDStopCmdSend(ctrl);
        if (status == 0)
        {
            return 0;
        }
    }

    /* Invalidate buffer from cache after EDMA transfer */
    BspOsal_cacheInv(
        ptr,
        (card->blkLen * nblks),
        BSP_OSAL_CT_ALLD,
        BSP_OSAL_WAIT_FOREVER);

    if (ctrl->dmaEnable == 1)
    {
        /*Close the EDMA channel*/
        HSMMCSDEdmaClose(&edmaParam);
        ctrl->dmaEnable = 0;
    }

    return 1;
}

/**
 * \brief   This function copies data between buffers like a memcpy(), except
 **uses DMA.
 *
 * \param    mmcsdCtrlInfo It holds the mmcsd control information.
 * \param    dst         Destination starting address
 * \param    src         Source starting address
 * \param    cnt         Number of byte to copy
 *
 **/
void MMCSDMemCopy(mmcsdCtrlInfo *ctrl, void *dst, const void *src, uint32_t cnt)
{
    hsmmcsdEdmaParam_t edmaParam;
    uint32_t           dstOffset = 0U;
    uint32_t           srcOffset = 0U;

#if defined (SOC_TDA3XX)
    /* For tda3xx, translate virtual address to physical address (L3's view)
     * before doing EDMA
     */
    dstOffset = MMCSDvirt2phy(ctrl, dst);
    srcOffset = MMCSDvirt2phy(ctrl, (void *) src);
#endif

    /*Enable the EDMA channel*/
    edmaParam.baseAddr = SOC_EDMA_TPCC_BASE_VIRT;
    edmaParam.srcBfr   = (uint32_t) src + srcOffset;
    edmaParam.dstBfr   = (uint32_t) dst + dstOffset;
    edmaParam.chan     = EDMA_MMCSD_CH;
    edmaParam.length   = cnt;
    edmaParam.dreq     = ctrl->edmaRxDreq;

    /* Write back edges of buffer to DDR before EDMA transfer */
    /* NOTE: If it were guaranteed that the buffer was aligned to cache
     * lines, then this wouldn't be required, but since we can not guarantee
     * this (the buffer is a sub-element of the fatFs structures) we should
     * write back the edges of the buffer before the transfer so that when
     * we invalidate after the transfer, we don't loose any state data from
     * the other part of the surrounding data structures. */
    BspOsal_cacheWb(dst, 1, BSP_OSAL_CT_ALLD, BSP_OSAL_WAIT_FOREVER);
    BspOsal_cacheWb(
        (void *) ((uint32_t) dst + cnt - 1),
        1,
        BSP_OSAL_CT_ALLD,
        BSP_OSAL_WAIT_FOREVER);

    HSMMCSDEdmaCopy(&edmaParam);

    /* Invalidate buffer from cache after EDMA transfer */
    BspOsal_cacheInv(dst, cnt, BSP_OSAL_CT_ALLD, BSP_OSAL_WAIT_FOREVER);

    return;
}

#if defined (SOC_TDA3XX)
/* Translate virtual address to physical address (L3's view) */
static uint32_t MMCSDvirt2phy(mmcsdCtrlInfo *ctrl, void *ptr)
{
    uint32_t       offset = 0U;
    uint32_t       index  = 0U;
    mmcsdCardInfo *card   = ctrl->card;

    if (0U != card->numConv)
    {
        for (index = 0U; index < card->numConv; index++)
        {
            if ((((uint32_t) ptr) >= card->addrConv[index].virtualAddr) &&
                (((uint32_t) ptr) < card->addrConv[index].virtualAddr +
                 card->addrConv[index].addrSize))
            {
                offset = card->addrConv[index].phyAddrOffset;
                break;
            }
        }
    }
    return offset;
}

#endif
