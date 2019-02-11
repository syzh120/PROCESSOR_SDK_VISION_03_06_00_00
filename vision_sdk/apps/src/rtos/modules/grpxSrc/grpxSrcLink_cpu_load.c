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

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "grpxSrcLink_priv.h"
#ifdef TDA3XX_FAMILY_BUILD
#include <include/link_api/rtiLink.h>
#endif

#define RGB888_TO_RGB565(r,g,b)     ((((UInt32)(r>>3) & 0x1F) << 11) | (((UInt32)(g>>2) & 0x3F) << 5) | (((UInt32)(b>>3) & 0x1F)))

Void GrpxSrcLink_drawCpuLoadBar(
                    GrpxSrcLink_Obj *pObj,
                    UInt32 cpuLoadInt,
                    UInt32 cpuLoadFract,
                    UInt32 startX,
                    UInt32 startY,
                    UInt32 width,
                    UInt32 height,
                    UInt32 procId
                )
{
    Draw2D_RegionPrm region;
    UInt32 color[4];
    UInt32 barHeight[2];

    color[0] = RGB888_TO_RGB565(40, 40, 40);
    color[1] = RGB888_TO_RGB565(0, 160, 0);
    color[2] = RGB888_TO_RGB565(200, 0, 0);
    color[3] = RGB888_TO_RGB565(192, 192, 192);

    if(cpuLoadFract>=5)
        cpuLoadInt++;

    barHeight[0] = (height * (100 - cpuLoadInt))/100;

    if(barHeight[0] > height)
        barHeight[0] = height;

    barHeight[1] = height - barHeight[0];

    /* fill in in active load color */
    region.color  = color[0];
    region.colorFormat = SYSTEM_DF_BGR16_565;
    region.startX = startX;
    region.startY = startY;
    region.height = barHeight[0];
    region.width  = width;

    Draw2D_fillRegion(pObj->draw2DHndl,&region);

    /* fill active load color */
    region.color  = color[1];
    region.colorFormat = SYSTEM_DF_BGR16_565;
    region.startX = startX;
    region.startY = startY + barHeight[0];
    region.height = barHeight[1];
    region.width  = width;

    Draw2D_fillRegion(pObj->draw2DHndl,&region);

    if(SYSTEM_CORE_STATE_RTI_EXPIRED == System_getCoreState(procId))
    {
        /* fill in in RTI Expired load color */
        region.color  = color[2];
        region.colorFormat = SYSTEM_DF_BGR16_565;
        region.startX = startX;
        region.startY = startY;
        region.height = barHeight[0];
        region.width  = width;

        Draw2D_fillRegion(pObj->draw2DHndl,&region);
    }
    else if (SYSTEM_CORE_STATE_POWER_DOWN == System_getCoreState(procId))
    {
        /* fill in in powered down load color */
        region.color  = color[3];
        region.colorFormat = SYSTEM_DF_BGR16_565;
        region.startX = startX;
        region.startY = startY;
        region.height = barHeight[0];
        region.width  = width;

        Draw2D_fillRegion(pObj->draw2DHndl,&region);
    }
    else
    {
        ; /* Nothing to do here */
    }
}

/**
 *******************************************************************************
 * \brief Draw CPU load
 *
 * \param  pObj     [IN]  Grpx Src link instance handle
 * \param  x        [IN]  Start position X in pixels, of CPU load box on screen
 * \param  y        [IN]  Start position Y in pixels, of CPU load box on screen
 * \param  barWidth [IN]  Width of CPU load bar in pixels
 * \param  barHeight[IN]  Height of CPU load bar in pixels
 * \param  padX     [IN]  Space after a CPU load bar in X-direction, units of pixels
 * \param  padY     [IN]  Space after a CPU load name in Y-direction, units of pixels
 *
 * \return status   SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 GrpxSrcLink_drawCpuLoad(GrpxSrcLink_Obj *pObj,
                    UInt32 x, UInt32 y,
                    UInt32 barWidth,
                    UInt32 barHeight,
                    UInt32 padX,
                    UInt32 padY,
                    UInt32 fontIdx
                    )
{
    Draw2D_FontPrm fontPrm;
    UInt32 procId;
    Utils_SystemLoadStats *loadStats;
    char loadString[GRPX_SRC_LINK_STR_SZ];
    Draw2D_FontProperty fontProp;
    UInt32 startX, startY;

    fontPrm.fontIdx = fontIdx;

    Draw2D_getFontProperty(&fontPrm, &fontProp);

    /* CPU name start X, Y */
    startY =  y + fontProp.height + padY + barHeight + padY;
    startX =  x;

    for (procId = 0; procId < SYSTEM_PROC_MAX; procId++)
    {
            loadStats = &pObj->statsDisplayObj.systemLoadStats[procId];

            if(Bsp_platformIsTda3xxFamilyBuild()
                &&
                (procId == SYSTEM_PROC_A15_0
                    ||
                 procId == SYSTEM_PROC_EVE2
                    ||
                 procId == SYSTEM_PROC_EVE3
                    ||
                 procId == SYSTEM_PROC_IPU2
                )
              )
            {
                /* These CPUs dont exist in TDA3xx */
                continue;
            }

            if(BSP_PLATFORM_SOC_ID_TDA2EX == Bsp_platformGetSocId()
                &&
                (procId == SYSTEM_PROC_DSP2
                    ||
                 procId == SYSTEM_PROC_EVE1
                    ||
                 procId == SYSTEM_PROC_EVE2
                    ||
                 procId == SYSTEM_PROC_EVE3
                    ||
                 procId == SYSTEM_PROC_EVE4
                )
              )
            {
                /* These CPUs dont exist in TDA2Ex */
                continue;
            }

            if(BSP_PLATFORM_SOC_ID_TDA2PX == Bsp_platformGetSocId()
                &&
                (procId == SYSTEM_PROC_EVE3
                )
              )
            {
                /* These CPUs dont exist in TDA2Px */
                continue;
            }


            snprintf(loadString, GRPX_SRC_LINK_STR_SZ,
                          "%-4s\n",
                          System_getProcName(procId)
                          );

            if (SYSTEM_PROC_IPU1_0 == procId)
            {
               snprintf(loadString, GRPX_SRC_LINK_STR_SZ,
                          "%-4s\n",
                          "M4-0"
                          );
            }
            else if (SYSTEM_PROC_IPU2 == procId)
            {
               snprintf(loadString, GRPX_SRC_LINK_STR_SZ,
                          "%-4s\n",
                          "M4-2"
                          );
            }
            else if (SYSTEM_PROC_IPU1_1 == procId)
            {
#ifdef A15_TARGET_OS_LINUX
               /* In case of Linux build, VSDK do not use IPU1-1 and use the
                * same space in the GRPX for SGX load */
               snprintf(loadString, GRPX_SRC_LINK_STR_SZ,
                          "%-4s\n",
                          "SGX "
                          );
               System_linkControl(
                   SYSTEM_LINK_ID_SGXFRMCPY_0,
                   SYSTEM_COMMON_CMD_GET_SGX_LOAD,
                   loadStats,
                   sizeof(Utils_SystemLoadStats),
                   TRUE);
#else
               snprintf(loadString, GRPX_SRC_LINK_STR_SZ,
                          "%-4s\n",
                          "M4-1"
                          );
#endif
            }
            else if (SYSTEM_PROC_A15_0 == procId)
            {
               snprintf(loadString, GRPX_SRC_LINK_STR_SZ,
                          "%-4s\n",
                          "A15"
                          );
            }

            /*
            * Instead of EVE4, the loading of ISP is being displayed for TDA2px & TDA3x
            */
            else if ((SYSTEM_PROC_EVE4 == procId) &&
                     ((BSP_PLATFORM_SOC_ID_TDA2PX == Bsp_platformGetSocId()) ||
                      Bsp_platformIsTda3xxFamilyBuild()))
            {
#ifdef ISS_INCLUDE
               GrpxSrcLink_drawISPLoad(loadStats);
               snprintf(loadString, GRPX_SRC_LINK_STR_SZ,
                          "%-4s\n",
                          "ISP"
                          );
#else
               continue;
#endif
            }
            else
            {
                /*
                 * Avoid MISRA C Warnings
                 */
            }

            /* draw CPU name */
            Draw2D_clearString(pObj->draw2DHndl,
                      startX,
                      startY,
                      strlen(loadString),
                      &fontPrm
                      );

            Draw2D_drawString(pObj->draw2DHndl,
                      startX,
                      startY,
                      loadString,
                      &fontPrm
                      );

            GrpxSrcLink_drawCpuLoadBar
                (
                    pObj,
                    loadStats->totalLoadParams.integerValue, /* CPU load integer value */
                    loadStats->totalLoadParams.fractionalValue, /* CPU load integer value */
                    startX,
                    y + fontProp.height + padY,
                    barWidth,
                    barHeight,
                    procId
                );

            /* draw CPU load as text */
            snprintf(loadString, GRPX_SRC_LINK_STR_SZ,
                          "%02d.%d%%\n",
                          loadStats->totalLoadParams.integerValue,
                          loadStats->totalLoadParams.fractionalValue
                          );
            Draw2D_clearString(pObj->draw2DHndl,
                      startX,
                      y,
                      strlen(loadString),
                      &fontPrm
                      );

            Draw2D_drawString(pObj->draw2DHndl,
                      startX,
                      y,
                      loadString,
                      &fontPrm
                      );

           startX += fontProp.width*6 + padX;
    }
    return 0;
}

/**
 *******************************************************************************
 * \brief Draw ISP load
 *
 * \return status   None
 *
 *******************************************************************************
*/
void GrpxSrcLink_drawISPLoad(Utils_SystemLoadStats *loadStats)
{
#ifdef ISS_INCLUDE
    System_LinkStatistics *pLinkStats;
    Utils_LatencyStats   *localLinkstats;
    Utils_LinkStatistics *linkStats;

    pLinkStats = Utils_linkStatsGetLinkStatInst(SYSTEM_LINK_ID_ISSM2MISP_0);
    localLinkstats = &(pLinkStats->linkLatency);
    linkStats = &(pLinkStats->linkStats);

    uint64_t count64 = (uint64_t)localLinkstats->countLo & 0xFFFFFFFFU;
    uint64_t temp = (uint64_t)localLinkstats->countHi & 0xFFFFFFFFU;
    count64 = count64 | (temp << 32U);
    if(count64)
    {
        /* Latency calculation in us */
        uint64_t accLatency64 = (uint64_t)localLinkstats->accumulatedLatencyLo & 0xFFFFFFFFU;
        temp = (uint64_t)localLinkstats->accumulatedLatencyHi & 0xFFFFFFFFU;
        accLatency64 = accLatency64 | (temp << 32U);
        uint32_t latency = (uint32_t)(accLatency64/count64);

        uint32_t elaspedTime = (UInt32)Utils_getCurGlobalTimeInMsec() - linkStats->statsStartTime;
        uint32_t fps = Utils_calcFps(linkStats->newDataCmdCount, elaspedTime);

        float percent = ((float)latency/1000000.0)*(fps/100.0)*100.0;

        loadStats->totalLoadParams.integerValue = (uint32_t)percent;
        /* ISS load integer value */
        loadStats->totalLoadParams.fractionalValue = (uint32_t)((percent - (uint32_t)percent) * 100);
        /* ISS load fractional value */
    }
#endif
}



