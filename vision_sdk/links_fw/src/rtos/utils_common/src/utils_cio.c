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
 * \brief  This file has the implementataion for UART
 *
 * \version 0.0 (Jun 2013) : [NN] First version
 * \version 0.1 (Jul 2013) : [NN] Updates as per code review comments
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include <xdc/std.h>
#include <src/rtos/utils_common/include/utils.h>
#if defined(BUILD_DSP) || defined(BUILD_ARP32) || defined(BUILD_M4)
#include <file.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <include/link_api/system.h>
#endif

#if defined(BUILD_DSP) || defined(BUILD_ARP32) || defined(BUILD_M4)

#define VPS_LOG_BUF_MAX_SIZE    ((UInt32)1024U)

static char gVpsLog_buf[VPS_LOG_BUF_MAX_SIZE];
static UInt32 gVpsLog_bufIdx = 0;
static FILE *gpfid = NULL;

static int32_t VpsLog_open(const char *path, uint32_t flags, int32_t llv_fd);
static int32_t VpsLog_close(int32_t dev_fd);
static int32_t VpsLog_read(int32_t dev_fd, char *buf, uint32_t count);
static int32_t VpsLog_write(int32_t dev_fd, const char *buf, uint32_t count);
static off_t VpsLog_lseek(int32_t dev_fd, off_t offset, int32_t origin);
static int32_t VpsLog_unlink(const char *path);
static int32_t VpsLog_rename(const char *old_name, const char *new_name);

static int32_t VpsLog_open(const char *path, uint32_t flags, int32_t llv_fd)
{
    gVpsLog_bufIdx = 0;
    return 0;
}

static int32_t VpsLog_close(int32_t dev_fd)
{
    if(gVpsLog_bufIdx>0)
    {
        gVpsLog_buf[gVpsLog_bufIdx] = (char)0;
        gVpsLog_bufIdx++;
        Vps_printf(gVpsLog_buf);
        gVpsLog_bufIdx = 0;
    }
    return 0;
}

static int32_t VpsLog_read(int32_t dev_fd, char *buf, uint32_t count)
{
    return 0;
}

static int32_t VpsLog_write(int32_t dev_fd, const char *buf, uint32_t count)
{
    Bool flushBuf = FALSE;
    uint32_t i;

    for(i=0; i<count; i++)
    {
        /* MISRA.PTR.ARITH
         * MISRAC_2004_Rule_11.1
         * MISRAC_WAIVER:
         * Pointer is accessed as an array.
         * For loop makes sure that the array is never accessed out of bound
         */
        gVpsLog_buf[gVpsLog_bufIdx] = buf[i];
        gVpsLog_bufIdx++;
        /* MISRA.PTR.ARITH
         * MISRAC_2004_Rule_11.1
         * MISRAC_WAIVER:
         * Pointer is accessed as an array.
         * For loop makes sure that the array is never accessed out of bound
         */
        if(buf[i]==(char)'\n')
        {
            gVpsLog_buf[gVpsLog_bufIdx] = (char)0;
            gVpsLog_bufIdx++;
            flushBuf = (Bool)TRUE;
        }
        /* MISRA.PTR.ARITH
         * MISRAC_2004_Rule_11.1
         * MISRAC_WAIVER:
         * Pointer is accessed as an array.
         * For loop makes sure that the array is never accessed out of bound
         */
        if(buf[i]==(char)0)
        {
            flushBuf = (Bool)TRUE;
        }
        if(gVpsLog_bufIdx == (VPS_LOG_BUF_MAX_SIZE-1U))
        {
            gVpsLog_buf[gVpsLog_bufIdx] = (char)0;
            gVpsLog_bufIdx++;
            flushBuf = (Bool)TRUE;
        }
        if(flushBuf)
        {
            Vps_printf(gVpsLog_buf);
            gVpsLog_bufIdx = 0;
            flushBuf = FALSE;
        }
    }

    return (int32_t)count;
}

static off_t VpsLog_lseek(int32_t dev_fd, off_t offset, int32_t origin)
{
    return -(int32_t)1;
}

static int32_t VpsLog_unlink(const char *path)
{
    return 0;
}

static int32_t VpsLog_rename(const char *old_name, const char *new_name)
{
    return 0;
}

void Utils_cioInit(void)
{
    int32_t status;

    status = add_device("VpsLog",
                _SSA,
                VpsLog_open,
                VpsLog_close,
                VpsLog_read,
                VpsLog_write,
                VpsLog_lseek,
                VpsLog_unlink,
                VpsLog_rename);
    UTILS_assert(status>=0);

    /* MISRA.STDLIB.STDIO
     * MISRAC_2004 Rule_20.9
     * This function can use printf,fopen functions for debug purpose..
     */
    gpfid = fopen("VpsLog","w");
    UTILS_assert(gpfid!=NULL);

    /* MISRA.EXPANSION.UNSAFE
     * MISRA C 20.1, 20.5, 20.6, 20.7
     * MISRAC_WAIVER:
     * This is a requirement of this API and cannot be avoided
     */
    /* MISRA.STDLIB.STDIO
     * MISRAC_2004 Rule_20.9
     * This function can use printf,fopen functions for debug purpose..
     */
    freopen("VpsLog:", "w", stdout); /* redirect stdout to VpsLog */
    /* MISRA.EXPANSION.UNSAFE
     * MISRA C 20.1, 20.5, 20.6, 20.7
     * MISRAC_WAIVER:
     * This is a requirement of this API and cannot be avoided
     */
    /* MISRA.STDLIB.STDIO
     * MISRAC_2004 Rule_20.9
     * This function can use printf,fopen functions for debug purpose..
     */
    setvbuf(stdout, NULL, _IONBF, 0); /* turn off buffering for stdout */

    /* MISRA.STDLIB.STDIO
     * MISRAC_2004 Rule_20.9
     * This function can use printf,fopen functions for debug purpose..
     */
    printf(" UTILS: CIO: Init Done !!!\r\n");
}

void Utils_cioDeInit(void)
{
    if(gpfid != NULL)
    {
    /* MISRA.STDLIB.STDIO
     * MISRAC_2004 Rule_20.9
     * This function can use printf,fopen functions for debug purpose..
     */
        fclose(gpfid);
    }
}

#else
void Utils_cioInit(void)
{
    /* CIO add_device API NOT supported on A15 GCC tool chain */
}

void Utils_cioDeInit(void)
{
    /* CIO add_device API NOT supported on A15 GCC tool chain */
}
#endif
