/******************************************************************************
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
******************************************************************************/


#include "network_ctrl_priv.h"

#define NETWORK_MEM_RDWR_START_ADDR1      (0x40000000U)
#define NETWORK_MEM_RDWR_END_ADDR1        (0x60000000U)
#define NETWORK_MEM_RDWR_START_ADDR2      (0x80000000U)
#define NETWORK_MEM_RDWR_END_ADDR2        (0xC0000000U)

#define ISS_BASE_ADDR_MASK                (0xFFF00000U)
#define ISS_BASE_ADDR_ON_TDA3XX           (0x52000000U)
#define ISS_BASE_ADDR_ON_TDA2PX_IPU       (0x62200000U)
#define ISS_BASE_ADDR_ON_TDA2PX           (0x42200000U)

#define CHECK_ADDR(addr, a, b)  \
    (((addr) >= (a)) && ((addr) < (b)))


static UInt32 *NetworkCtrl_MapIssAddress(UInt32 *pAddr);

Void NetworkCtrl_cmdHandlerMemRd(char *cmd, UInt32 prmSize)
{
    UInt32 *pBuf, *pBufVirtAddr, *pAddr, *pVirtAddr;
    Int32 status = 0;
    UInt32 prm[2], size, i;

    memset((void*) prm, 0U, sizeof(prm));

    /* alloc tmp buffer for parameters */
    if(prmSize == sizeof(prm))
    {
        /* read parameters */
        NetworkCtrl_readParams((UInt8*)prm, sizeof(prm));

        pAddr = (UInt32*)prm[0];
        size = prm[1];

        /* Check for errors */
        if (!
             (CHECK_ADDR(((UInt32)pAddr), NETWORK_MEM_RDWR_START_ADDR1,
                            NETWORK_MEM_RDWR_END_ADDR1) ||
              CHECK_ADDR(((UInt32)pAddr), NETWORK_MEM_RDWR_START_ADDR2,
                            NETWORK_MEM_RDWR_END_ADDR2))
           )
        {
            Vps_printf(" NetworkCtrl: Out of Range Address\n");
            status = -1;
        }

        if (!
             (CHECK_ADDR((((UInt32)pAddr)+size), NETWORK_MEM_RDWR_START_ADDR1,
                            NETWORK_MEM_RDWR_END_ADDR1) ||
              CHECK_ADDR((((UInt32)pAddr)+size), NETWORK_MEM_RDWR_START_ADDR2,
                            NETWORK_MEM_RDWR_END_ADDR2))
            )
        {
            Vps_printf(" NetworkCtrl: Incorrect size for this address\n");
            status = -1;
        }

        pAddr = NetworkCtrl_MapIssAddress(pAddr);

        if (0 == status)
        {
            /* Allocate Buffer */
            pBuf = ChainsCommon_Osal_memAlloc(size, 32);
            UTILS_assert(pBuf != NULL);

            /* Get Virtual Address of the allocated buffer */
            pBufVirtAddr = (UInt32*)ChainsCommon_Osal_getVirtAddr((UInt32)pBuf);
            UTILS_assert(0 != pBufVirtAddr);

            /* Map the give address */
            pVirtAddr = (UInt32*)ChainsCommon_Osal_map((UInt32)pAddr, size);
            UTILS_assert(0 != pVirtAddr);

            for(i=0; i<size/4; i++)
            {
                if(pAddr != NULL)
                {
                    pBufVirtAddr[i] = pVirtAddr[i];
                }
                else
                {
                    pBufVirtAddr[i] = 0U;
                }
            }

            /* send response */
            NetworkCtrl_writeParams((UInt8*)pBufVirtAddr, size, 0);

            ChainsCommon_Osal_memFree(pBuf, size);
            ChainsCommon_Osal_unmap((UInt32)pVirtAddr, size);
        }
        else
        {
            /* send response */
            NetworkCtrl_writeParams(NULL, 0, (UInt32)-1);
        }
    }
    else
    {
        Vps_printf(" NETWORK_CTRL: %s: Insufficient parameters (%d bytes) specified !!!\n", cmd, prmSize);
    }
}

Void NetworkCtrl_cmdHandlerMemWr(char *cmd, UInt32 prmSize)
{
    Int32 status = 0;
    volatile UInt32 *pAddr, *pVirtAddr;
    UInt32 prm[2], value;

    memset((void*) prm, 0U, sizeof(prm));
    /* alloc tmp buffer for parameters */
    if(prmSize == sizeof(prm))
    {
        /* read parameters */
        NetworkCtrl_readParams((UInt8*)prm, sizeof(prm));

        pAddr = (volatile UInt32*)prm[0];
        value = prm[1];

        /* Check for errors */
        if (!
             (CHECK_ADDR(((UInt32)pAddr), NETWORK_MEM_RDWR_START_ADDR1,
                            NETWORK_MEM_RDWR_END_ADDR1) ||
              CHECK_ADDR(((UInt32)pAddr), NETWORK_MEM_RDWR_START_ADDR2,
                            NETWORK_MEM_RDWR_END_ADDR2))
           )
        {
            Vps_printf(" NetworkCtrl: Out of Range Address\n");
            status = -1;
        }

        if (0 == status)
        {
            /* TODO: Check for the valid range of pAddr */
            pVirtAddr = (UInt32*)ChainsCommon_Osal_map((UInt32)pAddr, 4);
            *pVirtAddr = value;
            ChainsCommon_Osal_unmap((UInt32)pAddr, 4);

            /* send response */
            NetworkCtrl_writeParams(NULL, 0, 0);
        }
        else
        {
            /* send response */
            NetworkCtrl_writeParams(NULL, 0, (UInt32)-1);
        }
    }
    else
    {
        Vps_printf(" NETWORK_CTRL: %s: Insufficient parameters (%d bytes) specified !!!\n", cmd, prmSize);
    }
}

UInt32 *NetworkCtrl_MapIssAddress(UInt32 *pAddr)
{
    UInt32 *pRetAddr = pAddr;

#if defined(TDA2PX_BUILD)
    UInt32 tempAddr;

    tempAddr = (UInt32)pAddr;
    if ((tempAddr & ISS_BASE_ADDR_MASK) == ISS_BASE_ADDR_ON_TDA3XX)
    {
        tempAddr = tempAddr & (~ISS_BASE_ADDR_MASK);
    #if defined(BUILD_M4)
        tempAddr |= ISS_BASE_ADDR_ON_TDA2PX_IPU;
    #else
        tempAddr |= ISS_BASE_ADDR_ON_TDA2PX;
    #endif
    }

    pRetAddr = (UInt32 *)tempAddr;
#endif

    return (pRetAddr);
}
