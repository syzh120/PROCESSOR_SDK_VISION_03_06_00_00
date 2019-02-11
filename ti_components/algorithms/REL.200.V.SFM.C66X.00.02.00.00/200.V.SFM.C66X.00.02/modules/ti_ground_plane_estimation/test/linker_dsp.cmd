/*
* module name : Ground Plane Estimation
*
* module descripton : Generates ground plane information from sparse 3D points
*
*/
/*
 
Copyright (c) 2007-2017 Texas Instruments Incorporated
 
All rights reserved not granted herein.
 
Limited License.  
 
Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive license under copyrights and patents it now or hereafter owns or controls to make, have made, use, import, offer to sell and sell ("Utilize") this software subject to the terms herein.  With respect to the foregoing patent license, such license is granted  solely to the extent that any such patent is necessary to Utilize the software alone.  The patent license shall not apply to any combinations which include this software, other than combinations with devices manufactured by or for TI (“TI Devices”).  No hardware patent is licensed hereunder.
 
Redistributions must preserve existing copyright notices and reproduce this license (including the above copyright notice and the disclaimer and (if applicable) source code license limitations below) in the documentation and/or other materials provided with the distribution
 
Redistribution and use in binary form, without modification, are permitted provided that the following conditions are met:
 
*       No reverse engineering, decompilation, or disassembly of this software is permitted with respect to any software provided in binary form.
 
*       any redistribution and use are licensed by TI for use only with TI Devices.
 
*       Nothing shall obligate TI to provide you with source code for the software licensed and provided to you in object code.
 
If software source code is provided to you, modification and redistribution of the source code are permitted provided that the following conditions are met:
 
*       any redistribution and use of the source code, including any resulting derivative works, are licensed by TI for use only with TI Devices.
 
*       any redistribution and use of any object code compiled from the source code and any resulting derivative works, are licensed by TI for use only with TI Devices.
 
Neither the name of Texas Instruments Incorporated nor the names of its suppliers may be used to endorse or promote products derived from this software without specific prior written permission.
 
DISCLAIMER.
 
THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
*/
/* Linker for DSP1 instance, not DSP2 */

-stack 0x1800
-heap 0x3000000

MEMORY {
   L1P_SRAM                  : origin = 0x00E00000,  len = 0x8000
   L1D_SRAM                  : origin = 0x00F00000,  len = 0x4000     /* 16 KB SRAM  */
   L1D_CACHE                 : origin = 0x00F04000,  len = 0x4000     /* 16 KB cache */
   L2_SRAM                   : origin = 0x00800000,  len = 0x28000    /* SARAM in L2, = 256 + 32 - 128 = 160 KB*/ 
   L2_CACHE                  : origin = 0x00828000,  len = 0x20000    /* Cache for L2, which is configured as 128 KB*/
   DSP2_L2_SRAM              : origin = 0x40800000,  len = 0x48000
   SL2_SRAM                  : origin = 0x5B000000,  len = 0x40000
   EXT_MEM_CACHED_1          : origin = 0x80000000,  len = 0x06000000 /* For i/o buffers. This has to be non cached area of A15, and cached area of DSP*/
   EXT_MEM_NON_CACHED_1      : origin = 0x86000000,  len = 0x01000000 /* Researved for custom malloc of fast file i/o handles. Non Cached for DSP & A15*/
   EXT_MEM_NON_CACHED_2      : origin = 0x87000000,  len = 0x01000000 /* Researved for A15 states variables in fast file i/o operations Non Cached for DSP & A15*/
   EXT_MEM_NON_CACHED_3      : origin = 0x88000000,  len = 0x03000000 /* Hole */
   EXT_MEM_FAST_FILE_IO_CODE : origin = 0x8b000000,  len = 0x05000000 /* Fast File i/o Code of A15 is laying here */
   EXT_MEM_CACHED_2          : origin = 0x90000000,  len = 0x10000000 /* DSP Used cachable area */
}

SECTIONS
{
    .alg_lib_text {
      *ti_gpe_algo.lib (.text)
    } > EXT_MEM_CACHED_2
    
    .alg_lib_const {
      *ti_gpe_algo.lib (.const)
    } > EXT_MEM_CACHED_2    
    
    vectors   :> EXT_MEM_CACHED_2
    .cinit    :> EXT_MEM_CACHED_2
    .cio      :> EXT_MEM_CACHED_2
    .bss      :> EXT_MEM_CACHED_2
    .text     :> EXT_MEM_CACHED_2
    .stack    :> L2_SRAM
    .const    :> EXT_MEM_CACHED_2
    .far      :> EXT_MEM_CACHED_2
    .fardata  :> EXT_MEM_CACHED_2
    .neardata :> EXT_MEM_CACHED_2
    .rodata   :> EXT_MEM_CACHED_2
    .sysmem   :> EXT_MEM_CACHED_2
    .switch   :> EXT_MEM_CACHED_2
    .dmem1    :> L2_SRAM
    .dmem0    :> L1D_SRAM
    .fileioCached   :> EXT_MEM_CACHED_1
    .fileio    :> EXT_MEM_NON_CACHED_2
    .hostdata :> EXT_MEM_NON_CACHED_1
    .ddrnoncacheSect :> EXT_MEM_NON_CACHED_1
}


