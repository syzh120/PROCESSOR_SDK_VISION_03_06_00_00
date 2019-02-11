/*
*
* Copyright (c) 2009-2017 Texas Instruments Incorporated
*
* All rights reserved not granted herein.
*
* Limited License.
*
* Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
* license under copyrights and patents it now or hereafter owns or controls to make,
* have made, use, import, offer to sell and sell ("Utilize") this software subject to the
* terms herein.  With respect to the foregoing patent license, such license is granted
* solely to the extent that any such patent is necessary to Utilize the software alone.
* The patent license shall not apply to any combinations which include this software,
* other than combinations with devices manufactured by or for TI ("TI Devices").
* No hardware patent is licensed hereunder.
*
* Redistributions must preserve existing copyright notices and reproduce this license
* (including the above copyright notice and the disclaimer and (if applicable) source
* code license limitations below) in the documentation and/or other materials provided
* with the distribution
*
* Redistribution and use in binary form, without modification, are permitted provided
* that the following conditions are met:
*
* *       No reverse engineering, decompilation, or disassembly of this software is
* permitted with respect to any software provided in binary form.
*
* *       any redistribution and use are licensed by TI for use only with TI Devices.
*
* *       Nothing shall obligate TI to provide you with source code for the software
* licensed and provided to you in object code.
*
* If software source code is provided to you, modification and redistribution of the
* source code are permitted provided that the following conditions are met:
*
* *       any redistribution and use of the source code, including any resulting derivative
* works, are licensed by TI for use only with TI Devices.
*
* *       any redistribution and use of any object code compiled from the source code
* and any resulting derivative works, are licensed by TI for use only with TI Devices.
*
* Neither the name of Texas Instruments Incorporated nor the names of its suppliers
*
* may be used to endorse or promote products derived from this software without
* specific prior written permission.
*
* DISCLAIMER.
*
* THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

/*                                                                          */
/*     @file : vcop_host.h                                                  */
/*                                                                          */
/*     @brief : This file contains macros required for adding host          */
/*     emulation support with minimal changes to existing test codes.       */
/*     Basically, this file defines the macros from vcop.h that will be     */
/*     called when the kernel init and vloops functions are called          */
/*     separately by a user.                                                */
/*                                                                          */
/*     Currently the vcop.h files doesn't define these functions in         */
/*     VCOP_HOST_EMULATION mode. This file is just a placeholder till this  */
/*     is included into vcop.h provided by the ARP32 compiler.              */
/*                                                                          */
/*  @version 1.0 (Sept 2013) : Base version.                                */
/*                                                                          */
/*==========================================================================*/

#ifndef _VCOP_HOST_H
#define _VCOP_HOST_H  1

#if VCOP_HOST_EMULATION || VCOP_7X_TRANSLATION

#define VCOP_SET_MEM_VIEW(VIEW)
#define ALIAS_128K_VIEW (0)
#define ibufla ((void*) 0x40050000)
#define ibufha ((void*) 0x40054000)
#define ibuflb ((void*) 0x40070000)
#define ibufhb ((void*) 0x40074000)
#define wbuf   ((void*) 0x40044000)
#define BUF_PING (0)
#define BUF_PONG (0)
#define WBUF_SYST (0)
#define IBUFHB_SYST (0)
#define IBUFLB_SYST (0)
#define IBUFHA_SYST (0)
#define IBUFLA_SYST (0)
#define VCOP_BUF_SWITCH_SET(w, hb, lb, ha, la)
#define VCOP_BUF_SWITCH_TOGGLE(f) f
#define VCOP_READ_BUF_SWITCH() (1)
#define VCOP_WRITE_BUF_SWITCH(v)
#define VCOP_WRITE_BUF_SWITCH_REG(v)
#define _vcop_vloop_done()

#endif

#endif /* _VCOP_HOST_H */
