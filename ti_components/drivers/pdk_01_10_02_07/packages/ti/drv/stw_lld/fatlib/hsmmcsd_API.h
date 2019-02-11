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
 *   Component:         fatlib
 *
 *   Filename:               hsmmcsd_API.h.
 *
 *   Description:           This file contain API functions to init the MMCSD
 ****device & FAT filesystem
 */
#ifndef HSMMCSD_API_H_
#define HSMMCSD_API_H_

/****************************************************************
 *  INCLUDE FILES
 ****************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif
#include <stdint.h>
#include <ti/drv/stw_lld/fatlib/fatfs/ff.h>
#include <ti/csl/soc.h>

void HSMMCSDFsMount(uint32_t driveNum, void *ptr);
void HSMMCSDFsUnMount(uint32_t driveNum);
void HSMMCSDFsProcessCmdLine(void);
int32_t HSMMCSDInit(MMC_INST_t num);
int32_t HSMMCSDDeInit(MMC_INST_t num);

#ifdef __cplusplus
}
#endif

#endif /* HSMMCSD_API_H_ */

