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

#define RSVP_NUM_CAMERAS                        (4U)

#define RSVP_INPUT_WIDTH                        (1280)
#define RSVP_INPUT_HEIGHT                       (720)
#define RSVP_OUTPUT_WIDTH                       (1920)
#define RSVP_OUTPUT_HEIGHT                      (480)

#define REMAP_WIDTH                     736  //800 (check chains_common_rear_view_panorama.c)
#define REMAP_HEIGHT                    384

#define STEREO_OUTPUT_WIDTH             640
#define STEREO_OUTPUT_HEIGHT            360


#define RSVPCALMAT_FILE                         "CALMAT.BIN"
#define RSVPPERSMAT_FILE                        "RSVPPERSMAT.BIN"
#define RSVPCHARTPOS_FILE                       "RSVPCHARTPOS.BIN"
#define RSVP_FILENAME_LDCLUT                    "RSVP_LUT.BIN"


#define DEFAULT_BLENDING_LENGTH 40 // Has to be greater than 0 and less than 128

#define OVERLAP1_TOP1 (660) //650
#define OVERLAP1_TOP2 (820) //870
#define OVERLAP1_BOTTOM1 (660) //800
#define OVERLAP1_BOTTOM2 (820) //940

#define OVERLAP2_TOP1 (1040) //970
#define OVERLAP2_TOP2 (1320) //1205
#define OVERLAP2_BOTTOM1 (1040) //1050
#define OVERLAP2_BOTTOM2 (1320) //1225

//1-wall; 2-ground; 3-combined
#define SEAMDETECTIONMODE 3

#define WALLDISP_DELTA 6
#define MAXDISPARITY   64  // Maximum disparity range of stereo engine
#define TEMPORALWEIGHT 0.0

// Calculated based on stereo engine parameters
#define STEREO_OFFSETX 72
#define STEREO_OFFSETY 9


#define SEARCHSPACEWIDTH 128
#define SEARCHSPACESTEP 16


// LDC PARAMS
#define LDCSUBSAMPLEFACTOR 8

#define TEMPORALSMOOTHING_MINPIX 8
#define TEMPORALSMOOTHING_MAXPIX 1

#define VC_SCALE_HEIGHT 0.5
#define VC_SCALE_DEPTH 1.5
#define VC_WALL_DISTANCE 1500
#define VC_VF 1.33
#define VC_ROTX 50
#define VC_ROTY 0
#define VC_ROTZ 0

#define FOCAL_LENGTH 1310
