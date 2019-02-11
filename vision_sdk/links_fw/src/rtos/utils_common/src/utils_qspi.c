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
 * \file utils_uart.c
 *
 * \brief  This file has the implementataion for QSPI
 *
 * \version 0.0 (Dec 2013) : [SS] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include <xdc/std.h>
#include <string.h>
#include <ti/csl/csl_qspi.h>
#include <ti/boot/sbl_auto/qspiflash/qspi_flash.h>
#include <ti/csl/cslr_qspi.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/drv/vps/include/boards/bsp_board.h>
#include <src/rtos/utils_common/include/utils_qspi.h>


/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/**
 *******************************************************************************
 * \brief Macro to enable/disable the Memory mapped mode with given chip select
 *        0: Data read from the Flash in cfg port mode
 *        1: Memory mapped mode with given chip select
 *******************************************************************************
 */
#define WRITE_MM_MODE_           (0U)

/**
 *******************************************************************************
 * \brief MAX size in bytes for a single QSPI read or write
 *******************************************************************************
 */
#define QSPI_READ_WRITE_SIZE      (256U)


/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Initializes the QSPI and sets the GIO handles for the Tx and Rx
 *
 * \return  None
 *
 *******************************************************************************
 */

Void System_qspiInit(void)
{
    uint32_t          device_Id;
    qspi_DeviceType_e DeviceType = DEVICE_TYPE_QSPI4;

#ifdef TDA3XX_BUILD
    Bsp_BoardId boardId;
    Bsp_BoardRev baseBoardRev;

    boardId = Bsp_boardGetId();

    switch (boardId)
    {
        case BSP_BOARD_BASE_TDA3XX:
            baseBoardRev = Bsp_boardGetBaseBoardRev();

            if (BSP_BOARD_REV_D == baseBoardRev)
            {
                DeviceType = DEVICE_TYPE_MICRON_QSPI4;
            }
            else
            {
                DeviceType = DEVICE_TYPE_QSPI4;
            }

            break;

        case BSP_BOARD_TDA3XX_RVP_ALPHA:
            DeviceType = DEVICE_TYPE_MICRON_QSPI4;
            break;

        case BSP_BOARD_TDA3XX_RVP_BETA:
        case BSP_BOARD_TDA3XX_RVP_A:
        case BSP_BOARD_TDA3XX_D3_SK:
            DeviceType = DEVICE_TYPE_MICRON_QSPI4;
            break;

        default:
            DeviceType = DEVICE_TYPE_QSPI4;
            break;
    }
#endif

    Vps_printf(" QSPI Init Started \n");

    /* Configure PADs. */
    PlatformQSPISetPinMux();

    QSPI_Initialize(DeviceType);

    /* Data read from the Flash in cfg port mode */
    QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                      (UInt8)QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);
    QSPI_ConfMAddrSpace((UInt8)QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT,(qspi_ChipSelect_e)QSPI_MMR);

    device_Id = QSPI_GetDeviceId();

    /* Change to Memory mapped mode with given chip select */
    QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                      (UInt8)QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT);
    QSPI_ConfMAddrSpace((UInt8)QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT,(qspi_ChipSelect_e)QSPI_CS0);

    Vps_printf (" MID - %x \n", device_Id & 0xFFU);
    Vps_printf (" DID - %x \n", (device_Id & 0xFF0000U) >> 16U);

    Vps_printf(" QSPI Init Completed Sucessfully \n");
}

/**
 *******************************************************************************
 *
 * \brief Read one or several sectors from the QSPI Memory described
 *        in the Device Descriptor.
 *        Note: API read from QSPI in sector vise & one sector size is 256
 *        bytes. So, you need to allocate the destination buffer size in
 *        multiple of QSPI_READ_WRITE_SIZE = 256 bytes
 *
 * \param dstAddr       [OUT] Destination address into
 *                            which the data to be read
 * \param srcOffsetAddr [IN]  Address Offset of QSPI from
 *                            which the data to be read
 * \param length        [IN]  Size of the data to be read in bytes
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 System_qspiReadSector(UInt32 dstAddr, UInt32 srcOffsetAddr, UInt32 length)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    /* Check if the  Dst buffer length a multiple of 256,
       This is done becuase QSPI_ReadSectors API read
       from QSPI in sector vise & one sector size is 256 bytes */

    if (0U != (length % QSPI_READ_WRITE_SIZE))
    {
        Vps_printf(
        " SYSTEM: QSPI Read - Dst buffer length must be a multiple of %d bytes! \n",
        QSPI_READ_WRITE_SIZE);
        status = SYSTEM_LINK_STATUS_EFAIL;
    }

    if (0U == dstAddr)
    {
        Vps_printf(" SYSTEM: QSPI Read - Dst Address is Null \n");
        status = SYSTEM_LINK_STATUS_EFAIL;
    }

    if (SYSTEM_LINK_STATUS_SOK == status)
    {
        Vps_printf(" QSPI Read Started, please wait! \n");

        while (length > 0)
        {
            if (WRITE_MM_MODE_)
            {
                QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                                  (UInt8)QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT);
                QSPI_ConfMAddrSpace(
                    (UInt8)QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT,(qspi_ChipSelect_e)QSPI_CS0);
                /* MISRA.CAST.PTR_TO_INT
                 * MISRAC_2004_Rule_11.3
                 * Casting between a pointer to an integral type
                 * KW State: Ignore -> Waiver -> Case by case
                 * MISRAC_WAIVER:
                 * Typecasting int to pointer as ReadSector API expects
                 * in void* format.
                 * There is a check to make sure that dstAddr is not null and
                 * caller of this api allocates buffer with the enough space.
                 */
                QSPI_ReadSectors((void *) dstAddr,
                    srcOffsetAddr, QSPI_READ_WRITE_SIZE);
            }
            else
            {
                QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                                  (UInt8)QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);
                QSPI_ConfMAddrSpace(
                    (UInt8)QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT,(qspi_ChipSelect_e)QSPI_MMR);

                QSPI_ReadCfgMode(dstAddr,
                    srcOffsetAddr, QSPI_READ_WRITE_SIZE/4U);
            }
            length -= QSPI_READ_WRITE_SIZE;
            dstAddr += QSPI_READ_WRITE_SIZE;
            srcOffsetAddr += QSPI_READ_WRITE_SIZE;
        }

        /* Change to Memory mapped mode with given chip select */
        QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                          (UInt8)QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT);
        QSPI_ConfMAddrSpace((UInt8)QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT,(qspi_ChipSelect_e)QSPI_CS0);

        Vps_printf(" QSPI Read Completed Sucessfully \n");
    }

    return (status);
}

/**
 *******************************************************************************
 *
 * \brief Writes one or several sectors to the QSPI Memory described
 *        in the Device Descriptor.
 *        Note: QSPI erase API erases at block level which is of size
 *        QSPIFLASH_BLOCKSIZE = 64k. So, the size of buffer/memory reserved
 *        in QSPI should be in multiple of QSPIFLASH_BLOCKSIZE = 64k bytes
 *
 * \param srcAddr       [IN]  Source address from which the data to be
 *                            written into the QSPI flash
 * \param dstOffsetAddr [OUT  Address Offset of QSPI from
 *                            which the data to be written.
 *                            dstOffsetAddr Should be 64KB aligned.
 *                            size of buffer/memory reserved in QSPI should be
 *                            in multiple of QSPIFLASH_BLOCKSIZE = 64k bytes
 * \param length        [IN]  Size of the data to be written in bytes
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 System_qspiWriteSector(UInt32 dstOffsetAddr,
    UInt32 srcAddr, UInt32 length)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    /* Check if the dstOffsetAddr is 64KB aligned & QSPI buffer length
       a multiple of 64k, This is done becuase EraseSector API erases
       at block level which is of size QSPIFLASH_BLOCKSIZE = 64k */
    if ((0U != (dstOffsetAddr % QSPIFLASH_BLOCKSIZE)) ||
        (0U != (length % QSPIFLASH_BLOCKSIZE)))
    {
        Vps_printf(
            " SYSTEM: QSPI Write - Dst address must be aligned to %d bytes! &"
            " QSPI buffer length must be a multiple of %d bytes! \n",
            QSPIFLASH_BLOCKSIZE, QSPIFLASH_BLOCKSIZE);
        status = SYSTEM_LINK_STATUS_EFAIL;
    }

    if (SYSTEM_LINK_STATUS_SOK == status)
    {
        Vps_printf(" QSPI Write Started, please wait! \n");

        /* Erase the block before any write operation */
        System_qspiEraseSector (dstOffsetAddr, length);

        while (length > 0)
        {
            if (WRITE_MM_MODE_)
            {
                QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                                  (UInt8)QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT);
                QSPI_ConfMAddrSpace(
                    (UInt8)QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT,(qspi_ChipSelect_e)QSPI_CS0);
                QSPI_WriteEnable();
                QSPI_WriteSectors(dstOffsetAddr, srcAddr, QSPI_READ_WRITE_SIZE);
            }
            else
            {
                QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                                  (UInt8)QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);
                QSPI_ConfMAddrSpace(
                    (UInt8)QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT,(qspi_ChipSelect_e)QSPI_MMR);
                QSPI_WriteEnable();
                QSPI_WriteCfgMode(dstOffsetAddr,
                    srcAddr, QSPI_READ_WRITE_SIZE/4U);
            }
            length -= QSPI_READ_WRITE_SIZE;
            srcAddr += QSPI_READ_WRITE_SIZE;
            dstOffsetAddr += QSPI_READ_WRITE_SIZE;
        }

        /* Change to Memory mapped mode with given chip select */
        QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                          (UInt8)QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT);
        QSPI_ConfMAddrSpace((UInt8)QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT,(qspi_ChipSelect_e)QSPI_CS0);

        Vps_printf(" QSPI Write Completed Sucessfully \n");
    }

    return (status);
}

/**
 *******************************************************************************
 *
 * \brief Function to erase the whole QSPI flash memory.
 *
 * \return  None
 *
 *******************************************************************************
 */
Void System_qspiEraseFull(void)
{

    Vps_printf(" QSPI Erase Full Started, Will take a couple of seconds \n");
    if(!System_isFastBootEnabled())
    {
        /* If this is not present, UART prints don't happen until after the
         * QSPI operations are completed
         */
        BspOsal_sleep(10U);
    }

    QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                      (UInt8)QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);
    QSPI_ConfMAddrSpace((UInt8)QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT,(qspi_ChipSelect_e)QSPI_MMR);

    QSPI_WriteEnable();
    QSPI_FlashFullErase();

    Vps_printf(" QSPI Erase Full Completed Sucessfully \n");
}

/**
 *******************************************************************************
 *
 * \brief API to erase a block or mutiple blocks (sector) from the QSPI flash.
 *
 * \param dstOffsetAddr [IN]  Address Offset of QSPI from
 *                            which the data to be erased.
 *                            dstOffsetAddr Should be 64KB aligned.
 * \param length        [IN]  Size of the data to be erased in bytes
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 System_qspiEraseSector(UInt32 dstOffsetAddr, UInt32 length)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 blkno;

    /* Check if the dstOffsetAddr is 64KB aligned & QSPI buffer length
       a multiple of 64k, This is done becuase EraseSector API erases
       at block level which is of size QSPIFLASH_BLOCKSIZE = 64k */
    if ((0U != (dstOffsetAddr % QSPIFLASH_BLOCKSIZE)) ||
        (0U != (length % QSPIFLASH_BLOCKSIZE)))
    {
        Vps_printf(
            " SYSTEM: QSPI Erase - Dst address must be aligned to %d bytes! &"
            " QSPI buffer length must be a multiple of %d bytes! \n",
            QSPIFLASH_BLOCKSIZE, QSPIFLASH_BLOCKSIZE);
        status = SYSTEM_LINK_STATUS_EFAIL;
    }

    if (SYSTEM_LINK_STATUS_SOK == status)
    {
        Vps_printf(" QSPI Erase Block Started, please wait! \n");
        if(!System_isFastBootEnabled())
        {
            /* If this is not present, UART prints don't happen until after the
             * QSPI operations are completed
             */
                BspOsal_sleep(10U);
        }

        QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                          (UInt8)QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);
        QSPI_ConfMAddrSpace((UInt8)QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT,(qspi_ChipSelect_e)QSPI_MMR);

        blkno     = dstOffsetAddr / QSPIFLASH_BLOCKSIZE;
        /* Size of one block QSPIFLASH_BLOCKSIZE = 64k */
        while (length > 0)
        {
            QSPI_WriteEnable();
            QSPI_FlashBlockErase(blkno);
            blkno++;
            length -= QSPIFLASH_BLOCKSIZE;
        }

        Vps_printf(" QSPI Erase Block Completed Sucessfully \n");
    }
    return (status);
}



/* Nothing past this point */
