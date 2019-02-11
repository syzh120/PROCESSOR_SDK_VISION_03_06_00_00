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

/**
 *  \file ar0140_Gain_Table.h
 *
 *  \brief AR0140 Gain Table.
 *
 */

#ifndef AR0140_GAIN_TABLE_H_
#define AR0140_GAIN_TABLE_H_

/* AR0140 recommended setting */
#define AR0140_GAIN_TABLE                                                      \
{                                                                              \
    {1000,  0x00, 0x0},                                                        \
    {1062,  0x00, 0x1},                                                        \
    {1125,  0x00, 0x2},                                                        \
    {1187,  0x00, 0x3},                                                        \
    {1250,  0x00, 0x4},                                                        \
    {1312,  0x00, 0x5},                                                        \
    {1375,  0x00, 0x6},                                                        \
    {1250,  0x00, 0x7},                                                        \
    {1437,  0x00, 0x8},                                                        \
    {1562,  0x00, 0x9},                                                        \
    {1625,  0x00, 0xa},                                                        \
    {1687,  0x00, 0xb},                                                        \
    {1750,  0x00, 0xc},                                                        \
    {1812,  0x00, 0xd},                                                        \
    {1875,  0x00, 0xe},                                                        \
    {1937,  0x00, 0xf},                                                        \
                                                                               \
    {2000,  0x01, 0x0},                                                        \
    {2125,  0x01, 0x1},                                                        \
    {2250,  0x01, 0x2},                                                        \
    {2375,  0x01, 0x3},                                                        \
    {2500,  0x01, 0x4},                                                        \
    {2625,  0x01, 0x5},                                                        \
    {2750,  0x01, 0x6},                                                        \
    {2875,  0x01, 0x7},                                                        \
    {3000,  0x01, 0x8},                                                        \
    {3125,  0x01, 0x9},                                                        \
    {3250,  0x01, 0xa},                                                        \
    {3375,  0x01, 0xb},                                                        \
    {3500,  0x01, 0xc},                                                        \
    {3625,  0x01, 0xd},                                                        \
    {3750,  0x01, 0xe},                                                        \
    {3875,  0x01, 0xf},                                                        \
                                                                               \
    {4000,  0x02, 0x0},                                                        \
    {4250,  0x02, 0x1},                                                        \
    {4500,  0x02, 0x2},                                                        \
    {4750,  0x02, 0x3},                                                        \
    {5000,  0x02, 0x4},                                                        \
    {5250,  0x02, 0x5},                                                        \
    {5500,  0x02, 0x6},                                                        \
    {5750,  0x02, 0x7},                                                        \
    {6000,  0x02, 0x8},                                                        \
    {6250,  0x02, 0x9},                                                        \
    {6500,  0x02, 0xa},                                                        \
    {6750,  0x02, 0xb},                                                        \
    {7000,  0x02, 0xc},                                                        \
    {7250,  0x02, 0xd},                                                        \
    {7500,  0x02, 0xe},                                                        \
    {7750,  0x02, 0xf},                                                        \
                                                                               \
    {8000,  0x03, 0x0},                                                        \
    {8500,  0x03, 0x1},                                                        \
    {9000,  0x03, 0x2},                                                        \
    {9500,  0x03, 0x3},                                                        \
    {10000, 0x03, 0x4},                                                        \
    {10500, 0x03, 0x5},                                                        \
    {11000, 0x03, 0x6},                                                        \
    {11500, 0x03, 0x7},                                                        \
    {12000, 0x03, 0x8}                                                         \
}

#endif /* #ifndef AR0140_GAIN_TABLE_H_  */

