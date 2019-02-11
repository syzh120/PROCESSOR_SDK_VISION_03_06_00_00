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
/*===================================================================================
Global 3D multi-camera calibration table.
Used as backup if read from QSPI/SD card fails.
===================================================================================*/
//int calmatin3d[] = {1072709114, -47050622, -1702840, -31873752, -754322669, 763480766, -34651473, -762695913, -754993857, -394059, 725788, -412584, -35385483, -471596883, 963984311, -1072704590, 43596127, -18048398, -31212730, -963647893, -472578044, 566860, 426144, -360036, -1072665248, 26191292, -40308651, 45272566, 853117390, -650432639, 16160626, -651480038, -853366334, 383264, -120996, 385006, 72566559, 636015978, -862055262, 1070870414, -18975155, 76144630, 29868977, -864896019, -635597534, -560092, 23885, 349034};

/*Golf cart 2016/05/20 */
int calmatin3d[] = {1073395266, 15205167, 19031721, -7953965, -555558412, 919044699, 22861605, -918889053, -555266466, -3341640, 4157423, -3748096, 110411709, -697091085, 808935993, -1069454613, -57677172, 77122642, -6616456, -813636530, -700238638, 4430388, 4148723, -2193664, -1071479959, 30650670, 63337734, -29212770, 629555406, -869333210, -61951819, -869225137, -627395333, 3539007, -1080908, 4030479, -21840318, 713040613, -802521258, 1073625427, 6909336, -13036810, -3493284, -802699437, -713103856, -4730009, -630386, 3336814};
