/*
*
* Copyright (c) {2015 - 2017} Texas Instruments Incorporated
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


/**
 *  @file       report_utils.cpp
 *
 *  @brief      This is a temperary file. After migrating all the test
 benches to adopting to code size reporting method, functions in the 
 file can be moved to generic file
 *  @version 0.0 (Sep 2014) : Base version.
 */

#include <stdio.h>
#include <stdint.h>
#define TEST_PRINTF printf
#if !(HOST_EMULATION)
#define TEST_PRINTF printf
extern uint32_t  _bam_text_size;
extern uint32_t  _bam_neardata_size;
extern uint32_t  _bam_fardata_size;
extern uint32_t  _algo_fardata_size;
extern uint32_t  _algo_neardata_size;
extern uint32_t  _algo_text_size;
extern uint32_t  _starterware_fardata_size;
extern uint32_t  _starterware_neardata_size;
extern uint32_t  _starterware_text_size;
extern uint32_t  _rts_fardata_size;
extern uint32_t  _rts_neardata_size;
extern uint32_t  _rts_text_size;

extern uint32_t  _text_size;
#endif


void report_printAppletInfo(int8_t * name)
{
  TEST_PRINTF("\n\nTEST_REPORT_APPLET_NAME : %s Test application\n",name);
#if 0 //!(HOST_EMULATION)
    TEST_PRINTF("\nTEST_REPORT_TEXT_CONST : \n ");

    TEST_PRINTF("\n%-28s %25s %20s %20s  %s", \
            "Module", "Far data (DDR)", "Near data DMEM", "Program(.text)", "Comments");
    TEST_PRINTF("\n%-28s %25d %20d %20d  %s", name, &_algo_fardata_size, &_algo_neardata_size,  &_algo_text_size, "");
    TEST_PRINTF("\n%-28s %25d %20d %20d  %s", "BAM", &_bam_fardata_size, &_bam_neardata_size,  &_bam_text_size, "");
    TEST_PRINTF("\n%-28s %25d %20d %20d  %s", "Starterware", &_starterware_fardata_size, &_starterware_neardata_size,  &_starterware_text_size,"");
    TEST_PRINTF("\n%-28s %25d %20d %20d  %s\n", "rtsarp32_v200.lib", &_rts_fardata_size, &_rts_neardata_size,  &_rts_text_size,"");
#endif
}
