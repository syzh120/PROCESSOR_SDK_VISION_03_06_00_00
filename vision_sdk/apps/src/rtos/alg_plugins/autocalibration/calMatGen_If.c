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

#include "include/svAutoDetectChart.h"
#include "include/svPoseEstimate.h"
#include "include/alglink_api/algorithmLink_geometricAlignment.h"
#include <ti/sysbios/hal/Cache.h>

#define _align_4byte(A) ((Byte*)((((Word32)A+3)>>2)<<2))
#define _align_8byte(A) ((UInt8 *)((((Int32)A+7)>>3)<<3))

static Word32 initACDetectRunPersistentMem(
                            svACDetectStruct* sv,
                            void *persistentBufAddr)
{
    Word32 usedMemSize, tmp, i, j;
    Byte*  p_newMem;
    Byte* tempMemory;

    tempMemory = (Byte *)persistentBufAddr;

    p_newMem = _align_8byte(tempMemory);

    tmp = NUM_PT_BOUNDARY;
    if(tempMemory) sv->svFPBoundaryPosStruct = \
            (SV_ACDetect_FPBoundaryPos *)p_newMem;
    p_newMem += sizeof(SV_ACDetect_FPBoundaryPos)*tmp;

    tmp = MAX_FP_ALL;
    if(tempMemory) sv->outCenter = (double *)p_newMem;
    p_newMem += sizeof(double)*tmp;

    tmp = NUM_PT_BOUNDARY;
    if (tempMemory) sv->boundX = (double *)p_newMem;
    p_newMem += sizeof(double)*tmp;

    tmp = NUM_PT_BOUNDARY;
    if (tempMemory) sv->boundY = (double *)p_newMem;
    p_newMem += sizeof(double)*tmp;

    tmp = NUM_PT_BOUNDARY;
    if (tempMemory) sv->fcBoundX = (double *)p_newMem;
    p_newMem += sizeof(double)*tmp;

    tmp = NUM_PT_BOUNDARY;
    if (tempMemory) sv->fcBoundY = (double *)p_newMem;
    p_newMem += sizeof(double)*tmp;

    tmp = MAX_FP_ALL * 2;
    if(tempMemory) sv->outCenter = (double*)p_newMem;
    p_newMem += sizeof(double)*tmp;


    p_newMem = _align_8byte(p_newMem);

    tmp = 8;
    for (j = 0; j < MAX_INPUT_CAMERAS; j++)
    {
        for (i = 0; i < FP_TO_DETECT; i++)
        {
            if (tempMemory) sv->finalCorners[j][i] = (Word32*)p_newMem;
            p_newMem += sizeof(Word32)*tmp;
        }
    }

    for (i = 0; i < MAX_FP_ALL; i++)
    {
        if(tempMemory) sv->candidCorners[i] = (Word32*) p_newMem;
        p_newMem += sizeof(Word32)*tmp;
    }

    //LDC
    tmp = MAX_INPUT_CAMERAS;
    if (tempMemory)sv->ldc = (LensDistortionCorrection *)p_newMem;
    p_newMem += sizeof(LensDistortionCorrection)*tmp;

    p_newMem = _align_4byte(p_newMem);

    tmp = MAX_FP_ALL * 2;
    if (tempMemory) sv->candidCenter = (Word16*)p_newMem;
    p_newMem += sizeof(Word16)*tmp;

    tmp = MAX_FP_ALL * 2;
    if (tempMemory) sv->intOutCenter = (Word16*)p_newMem;
    p_newMem += sizeof(Word16)*tmp;

    tmp = MAX_FP_ALL;
    if (tempMemory) sv->outCenterNum = (Word16*)p_newMem;
    p_newMem += sizeof(Word16)*tmp;


    tmp = (Word32) (sv->SVInCamFrmWidth*sv->SVInCamFrmHeight);
    if (tempMemory) sv->candFPx = (Word16*)p_newMem;
    p_newMem += sizeof(Word16)*tmp;

    tmp = (Word32) (sv->SVInCamFrmWidth*sv->SVInCamFrmHeight);
    if(tempMemory) sv->candFPy = (Word16*) p_newMem;
    p_newMem += sizeof(Word16)*tmp;

    tmp = (Word32)(sv->SVInCamFrmWidth*sv->SVInCamFrmHeight);
    if (tempMemory) sv->candFPId = (Word16*)p_newMem;
    p_newMem += sizeof(Word16)*tmp;

    p_newMem = _align_4byte(p_newMem);

    tmp = (Word32) (sv->SVInCamFrmWidth*sv->SVInCamFrmHeight);
    if(tempMemory) sv->bwLumaFrame = (Byte*) p_newMem;
    p_newMem += tmp;

    p_newMem = _align_4byte(p_newMem);

    tmp = sv->SVInCamFrmWidth;
    if (tempMemory) sv->IntegralRows = (uWord32 *)p_newMem;
    p_newMem += sizeof(uWord32)*tmp;

    tmp = sv->SVInCamFrmWidth * sv->SVInCamFrmHeight;
    if (tempMemory) sv->IntegralImg = (uWord32 *)p_newMem;
    p_newMem += sizeof(uWord32)*tmp;

    p_newMem = _align_4byte(p_newMem);

    usedMemSize = (Word32) (p_newMem-tempMemory);

    return usedMemSize;
}

static Word32 initACDetectRunScratchMem(
                            svACDetectStruct* sv,
                            void *scratchBufAddr)
{
    Word32 usedMemSize, tmp;
    Byte*  p_newMem;
    Byte* tempMemory;

    tempMemory = (Byte *)scratchBufAddr;

    p_newMem = _align_8byte(tempMemory);

    tmp = NUM_PT_BOUNDARY;
    if (tempMemory) sv->tempBoundX = (double *)p_newMem;
    p_newMem += sizeof(double)*tmp;

    tmp = NUM_PT_BOUNDARY;
    if (tempMemory) sv->tempBoundY = (double *)p_newMem;
    p_newMem += sizeof(double)*tmp;

    tmp = NUM_PT_BOUNDARY;
    if (tempMemory) sv->line1PtsX = (double *)p_newMem;
    p_newMem += sizeof(double)*tmp;

    tmp = NUM_PT_BOUNDARY;
    if (tempMemory) sv->line1PtsY = (double *)p_newMem;
    p_newMem += sizeof(double)*tmp;

    tmp = NUM_PT_BOUNDARY;
    if (tempMemory) sv->line2PtsX = (double *)p_newMem;
    p_newMem += sizeof(double)*tmp;

    tmp = NUM_PT_BOUNDARY;
    if (tempMemory) sv->line2PtsY = (double *)p_newMem;
    p_newMem += sizeof(double)*tmp;

    tmp = 8;
    if (tempMemory) sv->tempCorner = (double *)p_newMem;
    p_newMem += sizeof(double)*tmp;

    tmp = 8;
    if (tempMemory) sv->tempCorner1 = (double *)p_newMem;
    p_newMem += sizeof(double)*tmp;

    tmp = 8;
    if (tempMemory) sv->tempCorner2 = (double *)p_newMem;
    p_newMem += sizeof(double)*tmp;



    tmp = MAX_FP_ALL;
    if(tempMemory)sv->matchScore = (double*)p_newMem;
    p_newMem += sizeof(double)*tmp;

    p_newMem = _align_8byte(p_newMem);

    tmp = MAX_INPUT_CAMERAS;
    if(tempMemory)sv->focalLength = (Word16*)p_newMem;
    p_newMem += sizeof(Word16)*tmp;

    p_newMem = _align_4byte(p_newMem);

    p_newMem = _align_4byte(p_newMem);

    usedMemSize = (Word32) (p_newMem-tempMemory);

    return usedMemSize;
}

static Word32 initPEstimateRunPersistentMem(
                            svPEstimateStruct* sv,
                            void *persistentBufAddr)
{
    Word32 usedMemSize, tmp, i;
    Byte*  p_newMem;
    Byte* tempMemory;

    tempMemory = (Byte *)persistentBufAddr;

    p_newMem = _align_8byte(tempMemory);

    /*****************************************/
    /* For 2D perpective matrix              */
    /*****************************************/
    // pers_mat
    tmp = 9;
    if(tempMemory) sv->pers_mat0 = (double*)p_newMem;
    p_newMem += sizeof(double)*tmp;

    tmp = 9;
    if(tempMemory) sv->pers_mat1 = (double*)p_newMem;
    p_newMem += sizeof(double)*tmp;

    tmp = 9;
    if(tempMemory) sv->pers_mat2 = (double*)p_newMem;
    p_newMem += sizeof(double)*tmp;

    tmp = 9;
    if(tempMemory) sv->pers_mat3 = (double*)p_newMem;
    p_newMem += sizeof(double)*tmp;

    // perscoor
    tmp = 16;
    if(tempMemory) sv->perscoor0_3_float = (double*)p_newMem;
    p_newMem += sizeof(double)*tmp;

    tmp = 16;
    if(tempMemory) sv->perscoor1_0_float = (double*)p_newMem;
    p_newMem += sizeof(double)*tmp;

    tmp = 16;
    if(tempMemory) sv->perscoor2_1_float = (double*)p_newMem;
    p_newMem += sizeof(double)*tmp;

    tmp = 16;
    if(tempMemory) sv->perscoor3_2_float = (double*)p_newMem;
    p_newMem += sizeof(double)*tmp;

    // outperscoor
    tmp = 16;
    if(tempMemory) sv->outperscoor0_3_float = (double*)p_newMem;
    p_newMem += sizeof(double)*tmp;

    tmp = 16;
    if(tempMemory) sv->outperscoor1_0_float = (double*)p_newMem;
    p_newMem += sizeof(double)*tmp;

    tmp = 16;
    if(tempMemory) sv->outperscoor2_1_float = (double*)p_newMem;
    p_newMem += sizeof(double)*tmp;

    tmp = 16;
    if(tempMemory) sv->outperscoor3_2_float = (double*)p_newMem;
    p_newMem += sizeof(double)*tmp;
    /*****************************************/


    p_newMem = _align_8byte(p_newMem);

    // Camera instrinsics
    for (i = 0; i < sv->numCameras; i++) {
        if (tempMemory) sv->cip[i] = (CameraIntrinsicParams *)p_newMem;
        p_newMem += sizeof(CameraIntrinsicParams);
    }

    tmp = NUM_CHART_CORNERS;
    for (i = 0; i < sv->numCameras; i++) {
        if (tempMemory) sv->chartPoints[i] = (Point2D_f *)p_newMem;
        p_newMem += sizeof(Point2D_f) *tmp;
    }

    tmp = NUM_CHART_CORNERS;
    for (i = 0; i < sv->numCameras; i++) {
        if (tempMemory) sv->cornerPoints[i] = (Point2D_f *)p_newMem;
        p_newMem += sizeof(Point2D_f) *tmp;
    }


    tmp = sv->numCameras;
    if (tempMemory) sv->H_cg = (Matrix3D_f *)p_newMem;
    p_newMem += sizeof(Matrix3D_f) *tmp;

    tmp = sv->numCameras;
    if (tempMemory) sv->R_cg = (Matrix3D_f *)p_newMem;
    p_newMem += sizeof(Matrix3D_f) *tmp;

    tmp = sv->numCameras;
    if (tempMemory) sv->R_gc = (Matrix3D_f *)p_newMem;
    p_newMem += sizeof(Matrix3D_f) *tmp;

    tmp = sv->numCameras;
    if (tempMemory) sv->t_cg = (Point3D_f *)p_newMem;
    p_newMem += sizeof(Point3D_f) *tmp;

    tmp = sv->numCameras;
    if (tempMemory) sv->t_gc = (Point3D_f *)p_newMem;
    p_newMem += sizeof(Point3D_f) *tmp;


    /*****************************************/
    /* For 2D perpective matrix              */
    /*****************************************/
    // xx0, yy0
    tmp = 8;
    if(tempMemory) sv->xx0 = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    tmp = 8;
    if(tempMemory) sv->yy0 = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    tmp = 8;
    if(tempMemory) sv->ofxx0 = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    tmp = 8;
    if(tempMemory) sv->ofyy0 = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    // xx1, yy1
    tmp = 8;
    if(tempMemory) sv->xx1 = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    tmp = 8;
    if(tempMemory) sv->yy1 = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    tmp = 8;
    if(tempMemory) sv->ofxx1 = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    tmp = 8;
    if(tempMemory) sv->ofyy1 = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    // xx2, yy2
    tmp = 8;
    if(tempMemory) sv->xx2 = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    tmp = 8;
    if(tempMemory) sv->yy2 = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    tmp = 8;
    if(tempMemory) sv->ofxx2 = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    tmp = 8;
    if(tempMemory) sv->ofyy2 = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    // xx3, yy3
    tmp = 8;
    if(tempMemory) sv->xx3 = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    tmp = 8;
    if(tempMemory) sv->yy3 = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    tmp = 8;
    if(tempMemory) sv->ofxx3 = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    tmp = 8;
    if(tempMemory) sv->ofyy3 = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;
    /*****************************************/

    //LDC
    tmp = MAX_INPUT_CAMERAS;
    if (tempMemory)sv->ldc = (LensDistortionCorrection *)p_newMem;
    p_newMem += sizeof(LensDistortionCorrection)*tmp;

    p_newMem = _align_4byte(p_newMem);

    /*****************************************/
    /* For 2D perpective matrix              */
    /*****************************************/
    // 2-byte data
    // xx, yy
    tmp = 16;
    if(tempMemory) sv->xx = (Word16*) p_newMem;
    p_newMem += sizeof(Word16)*tmp;

    tmp = 16;
    if(tempMemory) sv->yy = (Word16*) p_newMem;
    p_newMem += sizeof(Word16)*tmp;

    // x0, y0
    tmp = 8;
    if(tempMemory) sv->x0 = (Word16*) p_newMem;
    p_newMem += sizeof(Word16)*tmp;

    tmp = 8;
    if(tempMemory) sv->y0 = (Word16*) p_newMem;
    p_newMem += sizeof(Word16)*tmp;

    // x1, y1
    tmp = 8;
    if(tempMemory) sv->x1 = (Word16*) p_newMem;
    p_newMem += sizeof(Word16)*tmp;

    tmp = 8;
    if(tempMemory) sv->y1 = (Word16*) p_newMem;
    p_newMem += sizeof(Word16)*tmp;

    // x2, y2
    tmp = 8;
    if(tempMemory) sv->x2 = (Word16*) p_newMem;
    p_newMem += sizeof(Word16)*tmp;

    tmp = 8;
    if(tempMemory) sv->y2 = (Word16*) p_newMem;
    p_newMem += sizeof(Word16)*tmp;

    // x3, y3
    tmp = 8;
    if(tempMemory) sv->x3 = (Word16*) p_newMem;
    p_newMem += sizeof(Word16)*tmp;

    tmp = 8;
    if(tempMemory) sv->y3 = (Word16*) p_newMem;
    p_newMem += sizeof(Word16)*tmp;
    /*****************************************/

    p_newMem = _align_4byte(p_newMem);

    p_newMem = _align_4byte(p_newMem);

    usedMemSize = (Word32) (p_newMem-tempMemory);

    return usedMemSize;
}

static Word32 initPEstimateRunScratchMem(
                        svPEstimateStruct* sv,
                        void *scratchBufAddr)
{
    Word32 usedMemSize, tmp, i;
    Byte*  p_newMem;
    Byte* tempMemory;

    tempMemory = (Byte *)scratchBufAddr;

    p_newMem = _align_8byte(tempMemory);

    /*****************************************/
    /* For 2D perpective matrix              */
    /*****************************************/
    // Flouble    *A_matrix;
    tmp = 8*16;
    if(tempMemory)sv->A_matrix = (double*)p_newMem;
    p_newMem += sizeof(double)*tmp;

    // Flouble    *B_vector;
    tmp = 8*2;
    if(tempMemory)sv->B_vector = (double*)p_newMem;
    p_newMem += sizeof(double)*tmp;

    // Flouble    *q_matrix;
    tmp = 16 * 16;
    if (tempMemory)sv->q_matrix = (double*)p_newMem;
    p_newMem += sizeof(double)*tmp;

    // Flouble    *r_matrix;
    tmp = 16 * 8;
    if (tempMemory)sv->r_matrix = (double*)p_newMem;
    p_newMem += sizeof(double)*tmp;

    // Flouble    *u_vector;
    tmp = 16;
    if (tempMemory)sv->u_vector = (double*)p_newMem;
    p_newMem += sizeof(double)*tmp;

    // Flouble    *x_vector;
    tmp = 8;
    if (tempMemory)sv->x_vector = (double*)p_newMem;
    p_newMem += sizeof(double)*tmp;

    // Flouble    *y_vector;
    tmp = 16;
    if (tempMemory)sv->y_vector = (double*)p_newMem;
    p_newMem += sizeof(double)*tmp;

    // Flouble    *pers_matrix;
    tmp = 9;
    if(tempMemory)sv->pers_matrix = (double*)p_newMem;
    p_newMem += sizeof(double)*tmp;

    // Flouble    *inv_pers_mat_float;
    tmp = 9;
    if(tempMemory)sv->inv_pers_mat_float = (double*)p_newMem;
    p_newMem += sizeof(double)*tmp;
    /*****************************************/

    p_newMem = _align_8byte(p_newMem);

    tmp = NUM_CORNERS_PER_CHART;
    for (i = 0; i < 4; i++) {
        if (tempMemory) sv->baseChartPoints[i] = (Point2D_f *)p_newMem;
        p_newMem += sizeof(Point2D_f)*tmp;
    }

    tmp = NUM_CHART_CORNERS;
    if (tempMemory) sv->normCornerPoint = (Point2D_f *)p_newMem;
    p_newMem += sizeof(Point2D_f)*tmp;

    tmp = NUM_CHART_CORNERS;
    if (tempMemory) sv->points1norm = (Point2D_f *)p_newMem;
    p_newMem += sizeof(Point2D_f)*tmp;

    tmp = NUM_CHART_CORNERS;
    if (tempMemory) sv->points2norm = (Point2D_f *)p_newMem;
    p_newMem += sizeof(Point2D_f)*tmp;

    // for SVD
    tmp = A_SIZE;
    if (tempMemory) sv->A = (Flouble *)p_newMem;
    p_newMem += sizeof(Flouble)*tmp;

    tmp = U_SIZE;
    if (tempMemory) sv->U = (Flouble *)p_newMem;
    p_newMem += sizeof(Flouble)*tmp;

    tmp = V_SIZE;
    if (tempMemory) sv->V = (Flouble *)p_newMem;
    p_newMem += sizeof(Flouble)*tmp;

    tmp = U_SIZE;
    if (tempMemory) sv->U1 = (Flouble *)p_newMem;
    p_newMem += sizeof(Flouble)*tmp;

    tmp = A_NROWS;
    if (tempMemory) sv->Diag = (Flouble *)p_newMem;
    p_newMem += sizeof(Flouble)*tmp;

    tmp = A_NROWS;
    if (tempMemory) sv->superDiag = (Flouble *)p_newMem;
    p_newMem += sizeof(Flouble)*tmp;

    // to solve H in estimateH_2d_DLT_SRV()
    tmp = A_NCOLS;
    if (tempMemory) sv->h = (Flouble *)p_newMem;
    p_newMem += sizeof(Flouble)*tmp;

    // Rotation and translation after DLT
    tmp = 9;
    if (tempMemory) sv->R_DLT = (Flouble *)p_newMem;
    p_newMem += sizeof(Flouble)*tmp;

    tmp = 3;
    if (tempMemory) sv->t_DLT = (Flouble *)p_newMem;
    p_newMem += sizeof(Flouble)*tmp;

    // for Levenberg-Marquardt
    tmp = NUM_CHART_CORNERS * 2 + 3;
    if (tempMemory) sv->xvec = (Flouble *)p_newMem;
    p_newMem += sizeof(Flouble)*tmp;

    tmp = NUM_CHART_CORNERS * 2 + 3;
    if (tempMemory) sv->fvec = (Flouble *)p_newMem;
    p_newMem += sizeof(Flouble)*tmp;


    tmp = (NUM_CHART_CORNERS * 2 + 3) * A_NCOLS;
    if (tempMemory) sv->Jacob = (Flouble *)p_newMem;
    p_newMem += sizeof(Flouble)*tmp;

    tmp = (NUM_CHART_CORNERS * 2 + 3) * A_NCOLS;
    if (tempMemory) sv->JacobT = (Flouble *)p_newMem;
    p_newMem += sizeof(Flouble)*tmp;

    tmp = A_NCOLS;
    if (tempMemory) sv->gammaIdentity = (Flouble *)p_newMem;
    p_newMem += sizeof(Flouble)*tmp;

    tmp = A_NCOLS;
    if (tempMemory) sv->bvec = (Flouble *)p_newMem;
    p_newMem += sizeof(Flouble)*tmp;

    tmp = (NUM_CHART_CORNERS * 2 + 3);
    if (tempMemory) sv->tempvec = (Flouble *)p_newMem;
    p_newMem += sizeof(Flouble)*tmp;

    tmp = A_NCOLS;
    if (tempMemory) sv->deltavec = (Flouble *)p_newMem;
    p_newMem += sizeof(Flouble)*tmp;

    // for QR decomposition
    tmp = A_NCOLS * A_NCOLS;
    if (tempMemory) sv->AInv = (Flouble *)p_newMem;
    p_newMem += sizeof(Flouble)*tmp;

    tmp = A_NCOLS * A_NCOLS;
    if (tempMemory) sv->Q = (Flouble *)p_newMem;
    p_newMem += sizeof(Flouble)*tmp;

    tmp = A_NCOLS * A_NCOLS;
    if (tempMemory) sv->R = (Flouble *)p_newMem;
    p_newMem += sizeof(Flouble)*tmp;

    tmp = A_NCOLS;
    if (tempMemory) sv->yvec = (Flouble *)p_newMem;
    p_newMem += sizeof(Flouble)*tmp;

    p_newMem = _align_4byte(p_newMem);

    /*****************************************/
    /* For 2D perpective matrix              */
    /*****************************************/
    // uWord16    *InCamFrmDistortionCen;
    tmp = MAX_INPUT_CAMERAS*2;
    if(tempMemory)sv->InCamFrmDistortionCen = (uWord16*)p_newMem;
    p_newMem += sizeof(uWord16)*tmp;

    // uWord16    *OutDisplayFrmCen;
    tmp = MAX_INPUT_CAMERAS*2;
    if(tempMemory)sv->OutDisplayFrmCen = (uWord16*)p_newMem;
    p_newMem += sizeof(uWord16)*tmp;
    /*****************************************/

    p_newMem = _align_4byte(p_newMem);
    p_newMem = _align_4byte(p_newMem);

    usedMemSize = (Word32) (p_newMem-tempMemory);

    return usedMemSize;
}

void Utils_sv3dGenCalMat(void *pPrm)
{
    UInt8   detectedPointNum[MAX_INPUT_CAMERAS];
    UInt8   bLeftChartOnly[MAX_INPUT_CAMERAS];

    Int32 retVal;
    UInt32 cnt;
    Word32 memSize;
    svACDetectStruct svACDetectObj;
    svPEstimateStruct svPEstimateObj;
    AlgorithmLink_calMatGenPrm_3DSRV *pCalMatGenPrm =
                                (AlgorithmLink_calMatGenPrm_3DSRV*)pPrm;
    void *inImgPtr[NUM_MAX_VIEWS][NUM_MAX_VIEWS];
    ldc_lensParameters *pLensPrm, *pLensPrm2D;

    UTILS_assert (NULL != pCalMatGenPrm);
    UTILS_assert (NULL != pCalMatGenPrm->inChartPosBuf);
    UTILS_assert (NULL != pCalMatGenPrm->persistentBaseAddr);
    UTILS_assert (NULL != pCalMatGenPrm->scratchBaseAddr);

    memset(
        &svACDetectObj,
        0x00,
        sizeof(svACDetectStruct));

    memset(
        &svPEstimateObj,
        0x00,
        sizeof(svPEstimateStruct));

    /* Invalidate the input structure and buffers */
    Cache_inv(
            pCalMatGenPrm,
            sizeof(AlgorithmLink_calMatGenPrm_3DSRV),
            Cache_Type_ALLD,
            TRUE);

    Cache_inv(
            pCalMatGenPrm->inChartPosBuf,
            pCalMatGenPrm->inChartPosSize,
            Cache_Type_ALLD,
            TRUE);

    Cache_inv(
            pCalMatGenPrm->pLensPrm,
            sizeof(ldc_lensParameters),
            Cache_Type_ALLD,
            TRUE);

    Cache_inv(
            pCalMatGenPrm->pLensPrm2D,
            sizeof(ldc_lensParameters),
            Cache_Type_ALLD,
            TRUE);

    pLensPrm = (ldc_lensParameters*)pCalMatGenPrm->pLensPrm;
    pLensPrm2D = (ldc_lensParameters*)pCalMatGenPrm->pLensPrm2D;

    /*************************************************************************
     *                         AUTO DETECT CHART
     *************************************************************************/
    Vps_printf("CAL_MAT: Generating Calibration Matrix ...");

    svACDetectObj.numCameras = pCalMatGenPrm->numCameras;
    svACDetectObj.SVInCamFrmWidth = pCalMatGenPrm->imgWidth;
    svACDetectObj.SVInCamFrmHeight = pCalMatGenPrm->imgHeight;
    svACDetectObj.enableSV_ACDetect = pCalMatGenPrm->binarizationMode;
    svACDetectObj.thresholdMode = pCalMatGenPrm->thresholdMode;
    svACDetectObj.windowMode = pCalMatGenPrm->windowMode;
    svACDetectObj.Ransac = pCalMatGenPrm->Ransac;
    svACDetectObj.SingleChartPose = pCalMatGenPrm->SingleChartPose;

    if (pCalMatGenPrm->is2mp == TRUE)
    {
        svACDetectObj.SVROIWidth = 1920;
        svACDetectObj.SVROIHeight = 1080;
        svACDetectObj.binarizeOffset = 80;
        svACDetectObj.borderOffset = 80;
        svACDetectObj.smallestCenter = 10;
        svACDetectObj.largestCenter = 50;
        svACDetectObj.maxWinWidth = 400;
        svACDetectObj.maxWinHeight = 400;
        svACDetectObj.maxBandLen = 400;
        svACDetectObj.minBandLen = 4;
        svACDetectObj.minSampleInCluster = 16;
        svACDetectObj.firstROITop = 300;
        svACDetectObj.firstROIBottom = 1050;
        svACDetectObj.firstROILeft = 50;
        svACDetectObj.firstROIRight = 900;
        svACDetectObj.secondROITop = 300;
        svACDetectObj.secondROIBottom = 1050;
        svACDetectObj.secondROILeft = 950;
        svACDetectObj.secondROIRight = 1870;
    }
    else
    {
        svACDetectObj.SVROIWidth = 1280;
        svACDetectObj.SVROIHeight = 720;
        svACDetectObj.binarizeOffset = 75;
        svACDetectObj.borderOffset = 50;
        svACDetectObj.smallestCenter = 2;
        svACDetectObj.largestCenter = 50;
        svACDetectObj.maxWinWidth = 180;
        svACDetectObj.maxWinHeight = 180;
        svACDetectObj.maxBandLen = 160;
        svACDetectObj.minBandLen = 2;
        svACDetectObj.minSampleInCluster = 4;
        svACDetectObj.firstROITop = 150;
        svACDetectObj.firstROIBottom = 670;
        svACDetectObj.firstROILeft = 100;
        svACDetectObj.firstROIRight = 600;
        svACDetectObj.secondROITop = 150;
        svACDetectObj.secondROIBottom = 670;
        svACDetectObj.secondROILeft = 700;
        svACDetectObj.secondROIRight = 1200;
    }

    memSize = initACDetectRunPersistentMem(
                        &svACDetectObj,
                        pCalMatGenPrm->persistentBaseAddr);
    Vps_printf (" Auto Detect Chart Persistemt Mem Size = %d\n",memSize);
    UTILS_assert (memSize <= pCalMatGenPrm->persistentMemSize);

    memSize = initACDetectRunScratchMem(
                        &svACDetectObj,
                        pCalMatGenPrm->scratchBaseAddr);
    Vps_printf (" Auto Detect Chart Scratch Mem Size    = %d\n",memSize);
    UTILS_assert (memSize <= pCalMatGenPrm->srcatchMemSize);

    for (cnt = 0U; cnt < svACDetectObj.numCameras; cnt++)
    {
        UTILS_assert (NULL != pCalMatGenPrm->inImgPtr[cnt]);

        Cache_inv(
                pCalMatGenPrm->inImgPtr[cnt],
                (pCalMatGenPrm->imgPitch[0U] * pCalMatGenPrm->imgHeight * 3)/2,
                Cache_Type_ALLD,
                TRUE);

        inImgPtr[0][cnt] = pCalMatGenPrm->inImgPtr[cnt];

        svACDetectObj.focalLength[cnt] = (Word16)pLensPrm->ldcLUT_focalLength;

        LDC_Init(
                &svACDetectObj.ldc[cnt],
                pLensPrm->ldcLUT_distortionCenters[2 * cnt],
                pLensPrm->ldcLUT_distortionCenters[2 * cnt + 1],
                pLensPrm->ldcLUT_focalLength,
                pLensPrm->ldcLUT_D2U_table,
                pLensPrm->ldcLUT_D2U_length,
                pLensPrm->ldcLUT_D2U_step,
                pLensPrm->ldcLUT_U2D_table,
                pLensPrm->ldcLUT_U2D_length,
                pLensPrm->ldcLUT_U2D_step);
    }

    retVal = svAutoDetectChart(
        &svACDetectObj,
        1U,                 // acDetectMode,0 - default,1 - calculate
        inImgPtr,
        &pCalMatGenPrm->imgPitch[0U],
        (Word32*)pCalMatGenPrm->cornerPointsBuf,
        detectedPointNum,
        bLeftChartOnly);

    if (ALGORITHM_PROCESS_OK == retVal)
    {
        /*************************************************************************
         *                          POSE ESTIMATE
         *************************************************************************/
        svPEstimateObj.numCameras = pCalMatGenPrm->numCameras;
        svPEstimateObj.SVInCamFrmWidth = pCalMatGenPrm->imgWidth;
        svPEstimateObj.SVInCamFrmHeight = pCalMatGenPrm->imgHeight;
        svPEstimateObj.Ransac = pCalMatGenPrm->PoseRansac;
        svPEstimateObj.SingleChartPose = pCalMatGenPrm->SingleChartPose;

        memSize = initPEstimateRunPersistentMem(
                        &svPEstimateObj,
                        pCalMatGenPrm->persistentBaseAddr);
        Vps_printf (" Pose Estimate Chart Persistemt Mem Size = %d\n",memSize);
        UTILS_assert (memSize <= pCalMatGenPrm->persistentMemSize);

        memSize = initPEstimateRunScratchMem(
                        &svPEstimateObj,
                        pCalMatGenPrm->scratchBaseAddr);
        Vps_printf (" Pose Estimate Chart Scratch Mem Size    = %d\n",memSize);
        UTILS_assert (memSize <= pCalMatGenPrm->srcatchMemSize);

        for (cnt = 0U; cnt < svPEstimateObj.numCameras; cnt++)
        {
            LDC_Init(
                    &svPEstimateObj.ldc[cnt],
                    pLensPrm->ldcLUT_distortionCenters[2 * cnt],
                    pLensPrm->ldcLUT_distortionCenters[2 * cnt + 1],
                    pLensPrm->ldcLUT_focalLength,
                    pLensPrm->ldcLUT_D2U_table,
                    pLensPrm->ldcLUT_D2U_length,
                    pLensPrm->ldcLUT_D2U_step,
                    NULL,
                    0U,
                    0U);
        }

        retVal = svPoseEstimate(
            &svPEstimateObj,
            1U,                 // pEstimateMode,0 - default,1 - calculate 
            (Word32*)pCalMatGenPrm->cornerPointsBuf,
            (Byte*)pCalMatGenPrm->inChartPosBuf,
            pCalMatGenPrm->calMatBuf,
            detectedPointNum,
            bLeftChartOnly);

        UTILS_assert ((ALGORITHM_PROCESS_OK == retVal) ||
                        (ALGORITHM_PROCESS_DISABLED == retVal));

        Vps_printf("CAL_MAT: Generating Calibration Matrix ...");

        /* Write Back the generated cal mat */
        Cache_wb(
                pCalMatGenPrm->calMatBuf,
                12 * 4 * pCalMatGenPrm->numCameras,
                Cache_Type_ALLD,
                TRUE);

        /*****************************************/
        /* For 2D perpective matrix              */
        /*****************************************/
        // Need to define pCalMatGenPrm->displayWidth and pCalMatGenPrm->displayHeight
        // for example, width = 880 and height = 1080
        svPEstimateObj.SVOutDisplayWidth = pCalMatGenPrm->displayWidth;
        svPEstimateObj.SVOutDisplayHeight = pCalMatGenPrm->displayHeight;
        /*****************************************/

        /*
         *  The Lens distortion parameters are different for 2D calibration.
         */
        for (cnt = 0U; cnt < svPEstimateObj.numCameras; cnt++)
        {
            LDC_Init(
                    &svPEstimateObj.ldc[cnt],
                    pLensPrm2D->ldcLUT_distortionCenters[2 * cnt],
                    pLensPrm2D->ldcLUT_distortionCenters[2 * cnt + 1],
                    pLensPrm2D->ldcLUT_focalLength,
                    pLensPrm2D->ldcLUT_D2U_table,
                    pLensPrm2D->ldcLUT_D2U_length,
                    pLensPrm2D->ldcLUT_D2U_step,
                    NULL,
                    0U,
                    0U);
        }

        retVal = svPoseEstimate_2D(
                    &svPEstimateObj,
                    1U,                 // pEstimateMode,0 - default,1 - calculate
                    (Word32*)pCalMatGenPrm->cornerPointsBuf,
                    (Byte*)pCalMatGenPrm->inChartPosBuf,
                    pCalMatGenPrm->persMatBuf);
        UTILS_assert ((ALGORITHM_PROCESS_OK == retVal) ||
                        (ALGORITHM_PROCESS_DISABLED == retVal));

        /*****************************************/
        /* For 2D perpective matrix              */
        /*****************************************/

        Vps_printf("CAL_MAT: Generating Perspective Matrix ...");

        Cache_wb(
                pCalMatGenPrm->persMatBuf,
                9 * 4 * pCalMatGenPrm->numCameras,
                Cache_Type_ALLD,
                TRUE);


        Cache_wb(
                pCalMatGenPrm->cornerPointsBuf,
                1024U,
                Cache_Type_ALLD,
                TRUE);

        pCalMatGenPrm->retStatus = 0;
    }
    else
    {
        pCalMatGenPrm->retStatus = -1;
        Vps_printf (" *********************************************\n");
        Vps_printf ("              Auto Detect FAILED ...\n");
        Vps_printf (" *********************************************\n");
    }
}
