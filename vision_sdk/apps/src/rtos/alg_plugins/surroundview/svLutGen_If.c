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

#include "include/globalDefs.h"
#include "include/svGenerate_3D_LDCLUT.h"
#include "include/svGenerate_3D_GPULUT.h"
#include "include/svTransform.h"
#include "include/alglink_api/algorithmLink_geometricAlignment.h"
#include "include/alglink_api/algorithmLink_synthesis.h"
#include <ti/sysbios/hal/Cache.h>
#include <include/link_api/systemLink_common.h>

#define _align_4byte(A) ((Byte*)((((Word32)A+3)>>2)<<2))
#define _align_8byte(A) ((UInt8 *)((((Int32)A+7)>>3)<<3))

typedef enum
{
    LUT_TYP_LDC = 0,
    LUT_TYP_GPU = 1
}LUT_TYPE;

extern  short BRIEF_XYin[];
extern  unsigned short sinatanLUTin[];
extern  unsigned short tanasinLUTin[];
extern  unsigned int descriptorPattern[];

extern  uWord16 GAlignLUT[];
void Utils_sv3dGenLut(void *pPrm, LUT_TYPE lutType);
void Utils_sv2dUpdatePersMat(void *pPrm);
void Utils_sv3dGenCalMat(void *pPrm);
void svGenerate_2D_updatePersMat(svGAlignStruct *sv, uWord32 *inPitch);
void Utils_sv3dGenBlendTable(void *pPrm);

static Void lutGenHandler(UInt32 cmd, Void *pPrm)
{
    /* LDC LUT Generation */
    if (TDA3X_SV_3D_GEN_LDCLUT == cmd)
    {
        Utils_sv3dGenLut(pPrm, LUT_TYP_LDC);
    }

    /* GPU LUT Generation */
    if (TDA2X_SV_3D_GEN_GPULUT == cmd)
    {
        Utils_sv3dGenLut(pPrm, LUT_TYP_GPU);
    }

    /* Cal Mat Generation */
    if (TDA3X_SV_3D_GEN_CALMAT == cmd)
    {
        Utils_sv3dGenCalMat(pPrm);
    }

    /* Pers Mat Updation */
    if (SV_2D_UPDATE_PERSMAT == cmd)
    {
        Utils_sv2dUpdatePersMat(pPrm);
    }

    /* Synthesis Blend Table Generation */
    if (TDA3X_SV_3D_GEN_BLENDTABLE == cmd)
    {
        Utils_sv3dGenBlendTable(pPrm);
    }
}

void Utils_genSrvLutInit()
{
    SystemLink_registerHandler(lutGenHandler);
}

void Utils_genSrvLutDeInit()
{
    SystemLink_unregisterHandler(lutGenHandler);
}

static Word32 initGAlignRunPersistentMem(
                            svGAlignStruct *sv,
                            void *MemTabBasePtr)
{
    Word32 usedMemSize, tmp;
    Byte*  p_newMem;
    Byte* tempMemory;

    tempMemory = (Byte *)MemTabBasePtr;

    //Be careful about byte alignment.
    p_newMem = _align_4byte(tempMemory);

    //--------------------------------------------------------------
    //1st time call: estimate size of memory
    //2nd time call: assign memory
    //Assign memory for 32bit first, then 16bit, then 8bit etc
    //To do: Call p_newMem = _align_4byte(tempMemory) after each section is completed!!
    //--------------------------------------------------------------

    /*------------- 4bytes start---------------------------- */
    // uWord32      *descriptorPatternLUT;
    tmp = 8;
    if (tempMemory)sv->descriptorPatternLUT = (uWord32*)p_newMem;
    p_newMem += sizeof(uWord32)*tmp;

    //p_newMem = _align_4byte(p_newMem);
    // Word32       *persmat;
    tmp = MAX_INPUT_CAMERAS*9;
    if(tempMemory)sv->persmat = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    //LDC
    tmp = MAX_INPUT_CAMERAS;
    if (tempMemory)sv->ldc = (LensDistortionCorrection *)p_newMem;
    p_newMem += sizeof(LensDistortionCorrection)*tmp;


    p_newMem = _align_4byte(p_newMem);
    /*-------------4bytes end ------------------------------*/
    /*-------------2bytes start ------------------------------*/

    // uWord16      *sinatanLUT;
    tmp = 256;
    if(tempMemory)sv->sinatanLUT = (uWord16*)p_newMem;
    p_newMem += sizeof(uWord16)*tmp;

    // uWord16      *tanasinLUT;
    tmp = 320;
    if(tempMemory)sv->tanasinLUT = (uWord16*)p_newMem;
    p_newMem += sizeof(uWord16)*tmp;

    //uWord16       *overlapRegMarkPts; //16 element
    tmp = MAX_INPUT_CAMERAS*4; //maximal size for both RGB and YUV format
    if(tempMemory) sv->overlapRegMarkPts = (uWord16 *)p_newMem;
    p_newMem += sizeof(uWord16)*tmp;

    //uWord16       *seamMarkPts; //8 element
    tmp = MAX_INPUT_CAMERAS * 2; //maximal size for both RGB and YUV format
    if(tempMemory) sv->seamMarkPts = (uWord16 *)p_newMem;
    p_newMem += sizeof(uWord16)*tmp;

    // Word16 *BRIEF_XY;
    tmp = 1024;
    if(tempMemory)sv->BRIEF_XY = (Word16*)p_newMem;
    p_newMem += sizeof(Word16)*tmp;

    p_newMem = _align_4byte(p_newMem);
    /*-------------2bytes end ------------------------------*/


    //Calculate used memory size
    usedMemSize = (Word32) (p_newMem-tempMemory);

    return usedMemSize;
}

static Word32 initGAlignRunScratchMem(
                            svGAlignStruct* sv,
                            void *MemTabBasePtr)
{
    Word32 usedMemSize, tmp;
    Byte*  p_newMem;
    Byte* tempMemory;

    tempMemory = (Byte *)MemTabBasePtr;


    //Be careful about byte alignment.
    p_newMem = _align_8byte(tempMemory);

    //--------------------------------------------------------------
    //1st time call: estimate size of memory
    //2nd time call: assign memory
    //Assign memory for 4 bytes first, then 2 bytes, then 1 bytes etc
    //To do: Call p_newMem = _align_4byte(tempMemory) after each section is completed!!
    //--------------------------------------------------------------

    /*------------- 8bytes start---------------------------- */
    // double    *perscoor0_3reg3_float;
    tmp = sv->max_num_features*4;
    if(tempMemory)sv->perscoor0_3reg3_float = (double*)p_newMem;
    p_newMem += sizeof(double)*tmp;

    // double    *perscoor1_0reg0_float;
    tmp = sv->max_num_features*4;
    if(tempMemory)sv->perscoor1_0reg0_float = (double*)p_newMem;
    p_newMem += sizeof(double)*tmp;

    // double    *perscoor2_1reg1_float;
    tmp = sv->max_num_features*4;
    if(tempMemory)sv->perscoor2_1reg1_float = (double*)p_newMem;
    p_newMem += sizeof(double)*tmp;

    // double    *perscoor3_2reg2_float;
    tmp = sv->max_num_features*4;
    if(tempMemory)sv->perscoor3_2reg2_float = (double*)p_newMem;
    p_newMem += sizeof(double)*tmp;

    // double    *pers_mat0;
    tmp = 9;
    if(tempMemory)sv->pers_mat0 = (double*)p_newMem;
    p_newMem += sizeof(double)*tmp;

    // double    *pers_mat1;
    tmp = 9;
    if(tempMemory)sv->pers_mat1 = (double*)p_newMem;
    p_newMem += sizeof(double)*tmp;

    // double    *pers_mat2;
    tmp = 9;
    if(tempMemory)sv->pers_mat2 = (double*)p_newMem;
    p_newMem += sizeof(double)*tmp;

    // double    *pers_mat3;
    tmp = 9;
    if(tempMemory)sv->pers_mat3 = (double*)p_newMem;
    p_newMem += sizeof(double)*tmp;

    // double    *A_matrix;
    tmp = sv->max_num_features*16;
    if(tempMemory)sv->A_matrix = (double*)p_newMem;
    p_newMem += sizeof(double)*tmp;

    // double    *B_vector;
    tmp = sv->max_num_features*2;
    if(tempMemory)sv->B_vector = (double*)p_newMem;
    p_newMem += sizeof(double)*tmp;

    // double    *c_vector;
    tmp = 8;
    if(tempMemory)sv->c_vector = (double*)p_newMem;
    p_newMem += sizeof(double)*tmp;

    // double    *d_vector;
    tmp = 8;
    if(tempMemory)sv->d_vector = (double*)p_newMem;
    p_newMem += sizeof(double)*tmp;

    // double    *pers_matrix;
    tmp = 9;
    if(tempMemory)sv->pers_matrix = (double*)p_newMem;
    p_newMem += sizeof(double)*tmp;

    // double    *inv_pers_mat_float;
    tmp = 9;
    if(tempMemory)sv->inv_pers_mat_float = (double*)p_newMem;
    p_newMem += sizeof(double)*tmp;

    // u64    *fx2_col_buf;
    tmp = sv->SVOutDisplayWidth;
    if(tempMemory)sv->fx2_col_buf = (unsigned long long*)p_newMem;
    p_newMem += sizeof(unsigned long long)*tmp;

    // u64    *fy2_col_buf;
    tmp = sv->SVOutDisplayWidth;
    if(tempMemory)sv->fy2_col_buf = (unsigned long long*)p_newMem;
    p_newMem += sizeof(unsigned long long)*tmp;

    // s64    *fxfy_col_buf;
    tmp = sv->SVOutDisplayWidth;
    if(tempMemory)sv->fxfy_col_buf = (long long*)p_newMem;
    p_newMem += sizeof(long long)*tmp;

    p_newMem = _align_8byte(p_newMem);
    /*------------- 8bytes end------------------------------ */


    /*------------- 4bytes start---------------------------- */

    // Word32    *view0_reg3_feat;
    tmp = sv->max_num_features*3;
    if(tempMemory)sv->view0_reg3_feat = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    // Word32    *view3_reg3_feat;
    tmp = sv->max_num_features*3;
    if(tempMemory)sv->view3_reg3_feat = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;


    //Word32    *target_corner_loc_feat;
    tmp = sv->max_num_features * 4;
    if (tempMemory)sv->target_corner_loc_feat = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    // Word32    *view1_reg0_feat;
    tmp = sv->max_num_features*3;
    if(tempMemory)sv->view1_reg0_feat = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    // Word32    *view0_reg0_feat;
    tmp = sv->max_num_features*3;
    if(tempMemory)sv->view0_reg0_feat = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    // Word32    *view2_reg1_feat;
    tmp = sv->max_num_features*3;
    if(tempMemory)sv->view2_reg1_feat = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    // Word32    *view1_reg1_feat;
    tmp = sv->max_num_features*3;
    if(tempMemory)sv->view1_reg1_feat = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    // Word32    *view3_reg2_feat;
    tmp = sv->max_num_features*3;
    if(tempMemory)sv->view3_reg2_feat = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    // Word32    *view2_reg2_feat;
    tmp = sv->max_num_features*3;
    if(tempMemory)sv->view2_reg2_feat = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    // Word32    *perscoor0_3reg3;
    tmp = sv->max_num_features*4;
    if(tempMemory)sv->perscoor0_3reg3 = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    // Word32    *perscoor1_0reg0;
    tmp = sv->max_num_features*4;
    if(tempMemory)sv->perscoor1_0reg0 = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    // Word32    *perscoor2_1reg1;
    tmp = sv->max_num_features*4;
    if(tempMemory)sv->perscoor2_1reg1 = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    // Word32    *perscoor3_2reg2;
    tmp = sv->max_num_features*4;
    if(tempMemory)sv->perscoor3_2reg2 = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    // Word32    *euc_distance;
    tmp = sv->max_num_features;
    if(tempMemory)sv->euc_distance = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    // uWord32    *descriptor_A;
    tmp = sv->max_num_features*8;
    if(tempMemory)sv->descriptor_A = (uWord32*)p_newMem;
    p_newMem += sizeof(uWord32)*tmp;

    // uWord32    *descriptor_B;
    tmp = sv->max_num_features*8;
    if(tempMemory)sv->descriptor_B = (uWord32*)p_newMem;
    p_newMem += sizeof(uWord32)*tmp;



    // Word32    *target_corner_brief_dist;
    tmp = sv->max_num_features;
    if (tempMemory)sv->target_corner_brief_dist = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    // Word32    *orig_dist_mat;
    tmp = sv->max_num_features*sv->max_num_features;
    if(tempMemory)sv->orig_dist_mat = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    // Word32    *hor_dist_mat;
    tmp = sv->max_num_features*sv->max_num_features;
    if(tempMemory)sv->hor_dist_mat = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    // Word32    *ver_dist_mat;
    tmp = sv->max_num_features*sv->max_num_features;
    if(tempMemory)sv->ver_dist_mat = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    // Word32    *hor_index_matrix;
    tmp = sv->max_num_features*sv->max_num_features;
    if(tempMemory)sv->hor_index_matrix = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    // Word32    *ver_index_matrix;
    tmp = sv->max_num_features*sv->max_num_features;
    if(tempMemory)sv->ver_index_matrix = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    // Word32    *horq;
    tmp = sv->max_num_features*sv->max_num_features;
    if(tempMemory)sv->horq = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    // Word32    *verq;
    tmp = sv->max_num_features*sv->max_num_features;
    if(tempMemory)sv->verq = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    // Word32    *strmat;
    tmp = sv->max_num_features*sv->max_num_features;
    if(tempMemory)sv->strmat = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    // Word32    *match_pos_A;
    tmp = sv->max_num_features*2;
    if(tempMemory)sv->match_pos_A = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    // Word32    *match_scr_A;
    tmp = sv->max_num_features*2;
    if(tempMemory)sv->match_scr_A = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    // Word32    *match_pos_B;
    tmp = sv->max_num_features*2;
    if(tempMemory)sv->match_pos_B = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    // Word32    *match_scr_B;
    tmp = sv->max_num_features*2;
    if(tempMemory)sv->match_scr_B = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    // Word32    *ordmatvec;
    tmp = sv->max_num_features*12;
    if(tempMemory)sv->ordmatvec = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    // Word32    *inx;
    tmp = sv->max_num_features*4;
    if(tempMemory)sv->inx = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    // Word32    *featsubset_A;
    tmp = sv->max_num_features*4;
    if(tempMemory)sv->featsubset_A = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    // Word32    *featsubset_B;
    tmp = sv->max_num_features*4;
    if(tempMemory)sv->featsubset_B = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    // Word32    *modfeatsubset_B;
    tmp = sv->max_num_features*4;
    if(tempMemory)sv->modfeatsubset_B = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    // Word32    *modfeat_B;
    tmp = sv->max_num_features*4;
    if(tempMemory)sv->modfeat_B = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    // Word32    *pers_mat;
    tmp = 9;
    if(tempMemory)sv->pers_mat = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;

    // Word32    *chartFeatPoints;
    //x&y-coords (2) times # of feature points per chart (NUM_FEAT_POINTS_PER_CHART)  for each chart (MAX_NUM_VIEWS)
    tmp = 2*MAX_NUM_VIEWS*NUM_FEAT_POINTS_PER_CHART;
    if (tempMemory)sv->chartFeatPoints = (Word32*)p_newMem;
    p_newMem += sizeof(Word32)*tmp;



    p_newMem = _align_4byte(p_newMem);

    /*-------------4bytes end ------------------------------*/
    /*-------------2bytes start ------------------------------*/

    // uWord16    *GAlignLUT;
    tmp = (sv->SVOutDisplayWidth*sv->SVOutDisplayHeight*3)*1;
    if(tempMemory)sv->GAlignLUT = (uWord16*)p_newMem;
    p_newMem += sizeof(uWord16)*tmp;

    // uWord16    *GAlignLUT3D;
    tmp = (sv->SVOutDisplayWidth*sv->SVOutDisplayHeight*9)/(sv->subsampleratio * sv->subsampleratio );
    if(tempMemory)sv->GAlignLUT3D = (uWord16*)p_newMem;
    p_newMem += sizeof(uWord16)*tmp;

    // uWord16    *DMAPixelLevelLUT;
    tmp = sv->SVOutDisplayWidth*sv->SVOutDisplayHeight*2;
    if(tempMemory)sv->DMAPixelLevelLUT = (uWord16*)p_newMem;
    p_newMem += sizeof(uWord16)*tmp;

    // uWord16    *DMAPixelLevelLUT1;
    tmp = sv->SVOutDisplayWidth*sv->SVOutDisplayHeight*2;
    if(tempMemory)sv->DMAPixelLevelLUT1 = (uWord16*)p_newMem;
    p_newMem += sizeof(uWord16)*tmp;

    // uWord16    *DMAPixelLevelLUT_UV;
    tmp = sv->SVOutDisplayWidth*sv->SVOutDisplayHeight/2;
    if(tempMemory)sv->DMAPixelLevelLUT_UV = (uWord16*)p_newMem;
    p_newMem += sizeof(uWord16)*tmp;

    // uWord16    *DMAPixelLevelLUT1_UV;
    tmp = sv->SVOutDisplayWidth*sv->SVOutDisplayHeight/2;
    if(tempMemory)sv->DMAPixelLevelLUT1_UV = (uWord16*)p_newMem;
    p_newMem += sizeof(uWord16)*tmp;


    // uWord16    *InCamFrmDistortionCen;
    tmp = MAX_INPUT_CAMERAS*2;
    if(tempMemory)sv->InCamFrmDistortionCen = (uWord16*)p_newMem;
    p_newMem += sizeof(uWord16)*tmp;

    // uWord16    *OutDisplayFrmCen;
    tmp = MAX_INPUT_CAMERAS*2;
    if(tempMemory)sv->OutDisplayFrmCen = (uWord16*)p_newMem;
    p_newMem += sizeof(uWord16)*tmp;

    // Word16    *focalLength;
    tmp = MAX_INPUT_CAMERAS;
    if(tempMemory)sv->focalLength = (Word16*)p_newMem;
    p_newMem += sizeof(Word16)*tmp;

    // uWord16    *overlapping_area;
    //tmp = ((sv->SVOutDisplayHeight - (sv->SVOutDisplayHeight >> 3))>>1)*((sv->SVOutDisplayWidth - (sv->SVOutDisplayWidth >> 3))>>1)  >> 2;
    tmp = (sv->SVOutDisplayHeight - (sv->SVOutDisplayHeight >> 3))*(sv->SVOutDisplayWidth - (sv->SVOutDisplayWidth >> 3))  >> 2;
    if(tempMemory)sv->overlapping_area = (uWord16*)p_newMem;
    p_newMem += sizeof(uWord16)*tmp;

    // uWord16    *overlapping_area_Harris;
    tmp = (sv->SVOutDisplayHeight - (sv->SVOutDisplayHeight >> 3))*(sv->SVOutDisplayWidth - (sv->SVOutDisplayWidth >> 3))  >> 2;
    if(tempMemory)sv->overlapping_area_Harris = (uWord16*)p_newMem;
    p_newMem += sizeof(uWord16)*tmp;

    // uWord16    *blurred_overlapping_area_A;
    tmp = (sv->SVOutDisplayHeight - (sv->SVOutDisplayHeight >> 3))*(sv->SVOutDisplayWidth - (sv->SVOutDisplayWidth >> 3))  >> 2;
    if(tempMemory)sv->blurred_overlapping_area_A = (uWord16*)p_newMem;
    p_newMem += sizeof(uWord16)*tmp;

    // uWord16    *blurred_overlapping_area_B;
    tmp = (sv->SVOutDisplayHeight - (sv->SVOutDisplayHeight >> 3))*(sv->SVOutDisplayWidth - (sv->SVOutDisplayWidth >> 3))  >> 2;
    if(tempMemory)sv->blurred_overlapping_area_B = (uWord16*)p_newMem;
    p_newMem += sizeof(uWord16)*tmp;

    // uWord16    *DMA_LUT;
    tmp = (sv->SVOutDisplayWidth/sv->DMAblockSizeH)*(sv->SVOutDisplayHeight/sv->DMAblockSizeV)*12 + 3;
    if(tempMemory)sv->DMA_LUT = (uWord16*)p_newMem;
    p_newMem += sizeof(uWord16)*tmp;

    // uWord16    *DMA_LUT1;
    tmp = (sv->SVOutDisplayWidth/sv->DMAblockSizeH)*(sv->SVOutDisplayHeight/sv->DMAblockSizeV)*7 + 3;
    if(tempMemory)sv->DMA_LUT1 = (uWord16*)p_newMem;
    p_newMem += sizeof(uWord16)*tmp;

    // uWord16    *DMAtempMemory;
    tmp = sv->DMAblockSizeH*sv->DMAblockSizeV*4;
    if(tempMemory)sv->DMAtempMemory = (uWord16*)p_newMem;
    p_newMem += sizeof(uWord16)*tmp;

    // uWord16    *DMAtempMemory1;
    tmp = sv->DMAblockSizeH*sv->DMAblockSizeV*2;
    if(tempMemory)sv->DMAtempMemory1 = (uWord16*)p_newMem;
    p_newMem += sizeof(uWord16)*tmp;

    p_newMem = _align_4byte(p_newMem);

    /*-------------2bytes end ------------------------------*/
    /*-------------1bytes start ------------------------------*/

    p_newMem = _align_4byte(p_newMem);
    /*-------------1bytes end ------------------------------*/


    //Calculate used memory size
    usedMemSize = (Word32) (p_newMem-tempMemory);

    return usedMemSize;
}

void Utils_sv3dGenLut(void *pPrm, LUT_TYPE lutType)
{
    UInt32 cnt;
    svGAlignStruct svGalignObj;
    AlgorithmLink_lutGenPrm_3DSRV *pGAlignLdcLutPrm =
                                    (AlgorithmLink_lutGenPrm_3DSRV*)pPrm;
    Word16 focalLength[MAX_INPUT_CAMERAS];
    uWord16 InCamFrmDistortionCen[MAX_INPUT_CAMERAS * 2];
    LensDistortionCorrection ldc[MAX_INPUT_CAMERAS];
    uWord16 OutDisplayFrmCen[MAX_INPUT_CAMERAS * 2];
    uWord16 overlapRegMarkPts[MAX_INPUT_CAMERAS * 4];
    ldc_lensParameters *pLensPrm;

    UTILS_assert (NULL != pGAlignLdcLutPrm);
    UTILS_assert (NULL != pGAlignLdcLutPrm->calmat);

    memset(
        &svGalignObj,
        0x00,
        sizeof(svGAlignStruct));

    /* cache invalidate */
    Cache_inv(
            pGAlignLdcLutPrm,
            sizeof(AlgorithmLink_lutGenPrm_3DSRV),
            Cache_Type_ALLD,
            TRUE);

    Cache_inv(
            pGAlignLdcLutPrm->calmat,
            (pGAlignLdcLutPrm->calMatSize * pGAlignLdcLutPrm->numCameras),
            Cache_Type_ALLD,
            TRUE);

    Cache_inv(
            pGAlignLdcLutPrm->pLensPrm,
            sizeof(ldc_lensParameters),
            Cache_Type_ALLD,
            TRUE);

    pLensPrm = (ldc_lensParameters*)pGAlignLdcLutPrm->pLensPrm;

    if (LUT_TYP_LDC == lutType)
    {
        UTILS_assert (NULL != pGAlignLdcLutPrm->view2worldmesh);

        Cache_inv(
                pGAlignLdcLutPrm->view2worldmesh,
                pGAlignLdcLutPrm->v2wMeshSize,
                Cache_Type_ALLD,
                TRUE);
    }

    /* Local memory allocation - scratch */
    svGalignObj.focalLength = focalLength;
    svGalignObj.InCamFrmDistortionCen = InCamFrmDistortionCen;
    svGalignObj.ldc = ldc;
    svGalignObj.OutDisplayFrmCen = OutDisplayFrmCen;
    svGalignObj.overlapRegMarkPts = overlapRegMarkPts;

    /* Parameters passed from the Calibration use case */
    svGalignObj.calmat = pGAlignLdcLutPrm->calmat;
    svGalignObj.LDC3D_width = &pGAlignLdcLutPrm->LDC3DWidth[0U];
    svGalignObj.LDC3D_height = &pGAlignLdcLutPrm->LDC3DHeight[0U];
    svGalignObj.car_posx = &pGAlignLdcLutPrm->carPosx;
    svGalignObj.car_posy = &pGAlignLdcLutPrm->carPosy;
    svGalignObj.view2worldmesh[0U] = pGAlignLdcLutPrm->view2worldmesh;
    svGalignObj.numCameras = pGAlignLdcLutPrm->numCameras;
    svGalignObj.subsampleratio = pGAlignLdcLutPrm->subsampleratio;
    svGalignObj.SVOutDisplayWidth = pGAlignLdcLutPrm->SVOutDisplayWidth;
    svGalignObj.SVOutDisplayHeight = pGAlignLdcLutPrm->SVOutDisplayHeight;
    svGalignObj.SVInCamFrmWidth = pGAlignLdcLutPrm->SVInCamFrmWidth;
    svGalignObj.SVInCamFrmHeight = pGAlignLdcLutPrm->SVInCamFrmHeight;

    /* LDC LUT buffer addresses */
    for (cnt = 0U; cnt < svGalignObj.numCameras; cnt++)
    {
        svGalignObj.focalLength[cnt] = (Word16)pLensPrm->ldcLUT_focalLength;

        if (LUT_TYP_LDC == lutType)
        {
            /* LUT buffer */
            svGalignObj.LDCLUT3D[cnt] = pGAlignLdcLutPrm->LDCLUT3D[cnt];

            UTILS_assert (NULL != pGAlignLdcLutPrm->LDCLUT3D[cnt]);
        }

        LDC_Init(
                &svGalignObj.ldc[cnt],
                pLensPrm->ldcLUT_distortionCenters[2 * cnt],
                pLensPrm->ldcLUT_distortionCenters[2 * cnt + 1],
                pLensPrm->ldcLUT_focalLength,
                NULL,
                0U,
                0U,
                pLensPrm->ldcLUT_U2D_table,
                pLensPrm->ldcLUT_U2D_length,
                pLensPrm->ldcLUT_U2D_step);
    }

    if (LUT_TYP_LDC == lutType)
    {
        Vps_printf("LDC_LUT: Generating LDC LUT ...");

        svGalignObj.pLensPrm = pLensPrm;

        svSetFrameCenters_3D(
                    &svGalignObj);

        svGenerate_3D_LDCLUT(
                    &svGalignObj,
                    svGalignObj.calmat);

        /* Write back the computed LDC LUts */
        for(cnt = 0; cnt < svGalignObj.numCameras; cnt++)
        {
            Cache_wb(
                    svGalignObj.LDCLUT3D[cnt],
                    pGAlignLdcLutPrm->ldcLutSize,
                    Cache_Type_ALLD,
                    TRUE);
        }

        Vps_printf("LDC_LUT: Generating LDC LUT DONE");
    }

    if (LUT_TYP_GPU == lutType)
    {
        Vps_printf("GPU_LUT: Generating GPU LUT ...");

        svGalignObj.GAlignLUT3D = pGAlignLdcLutPrm->GPULUT3D;
        svGalignObj.GAlignLUT3D_XYZ = pGAlignLdcLutPrm->GPULUT3D_XYZ;
        svGalignObj.GAlignLUT3D_undist = pGAlignLdcLutPrm->GPULUT3D_undist;
        svGalignObj.enableAutoCalib = 0U;
        svGalignObj.autoPersmat = svGalignObj.calmat;
        svGalignObj.pLensPrm = pLensPrm;
        svGalignObj.offsetXleft = -400;
        svGalignObj.offsetXright = 400;
        svGalignObj.offsetYfront = 450;
        svGalignObj.offsetYback = -450;

        svSetFrameCenters_3D(
                    &svGalignObj);

        svGenerate_3D_GPULUT(
                    &svGalignObj,
                    svGalignObj.calmat,
                    1);

        /* Write back the computed LDC LUT */
        Cache_wb(
                svGalignObj.GAlignLUT3D,
                pGAlignLdcLutPrm->gpuLutSize,
                Cache_Type_ALLD,
                TRUE);

        Vps_printf("GPU_LUT: Generating GPU LUT DONE");
    }
}

void Utils_sv2dUpdatePersMat(void *pPrm)
{
    UInt32 cnt, memSize, j;
    svGAlignStruct svGalignObj;
    AlgorithmLink_update2DPersMatPrm *pUpdate2DPersMatPrm =
                                    (AlgorithmLink_update2DPersMatPrm*)pPrm;
    ldc_lensParameters *pLensPrm2D;

    UTILS_assert (NULL != pUpdate2DPersMatPrm);
    UTILS_assert (NULL != pUpdate2DPersMatPrm->persMatBuf);

    memset(
        &svGalignObj,
        0x00,
        sizeof(svGAlignStruct));

    /* cache invalidate */
    Cache_inv(
            pUpdate2DPersMatPrm,
            sizeof(AlgorithmLink_update2DPersMatPrm),
            Cache_Type_ALLD,
            TRUE);

    Cache_inv(
            pUpdate2DPersMatPrm->pLensPrm2D,
            sizeof(ldc_lensParameters),
            Cache_Type_ALLD,
            TRUE);

    pLensPrm2D = (ldc_lensParameters*)pUpdate2DPersMatPrm->pLensPrm2D;

    svGalignObj.SVInCamFrmHeight = pUpdate2DPersMatPrm->SVInCamFrmHeight;
    svGalignObj.SVInCamFrmWidth = pUpdate2DPersMatPrm->SVInCamFrmWidth;
    svGalignObj.SVOutDisplayHeight = pUpdate2DPersMatPrm->SVOutDisplayHeight;
    svGalignObj.SVOutDisplayWidth = pUpdate2DPersMatPrm->SVOutDisplayWidth;
    svGalignObj.numCameras = pUpdate2DPersMatPrm->numCameras;
    svGalignObj.numColorChannels = pUpdate2DPersMatPrm->numColorChannels;
    svGalignObj.ldcDownScaleFactor = pUpdate2DPersMatPrm->ldcDownScaleFactor;
    svGalignObj.ldcOutFrmWidth = pUpdate2DPersMatPrm->ldcOutFrmWidth;
    svGalignObj.ldcOutFrmHeight = pUpdate2DPersMatPrm->ldcOutFrmHeight;
    svGalignObj.DMAblockSizeV = pUpdate2DPersMatPrm->DMAblockSizeV;
    svGalignObj.DMAblockSizeH = pUpdate2DPersMatPrm->DMAblockSizeH;

    svGalignObj.svCarBoxParams.CarBoxCenter_x = \
                                    pUpdate2DPersMatPrm->SVOutDisplayWidth/2;
    svGalignObj.svCarBoxParams.CarBoxCenter_y = \
                                    pUpdate2DPersMatPrm->SVOutDisplayHeight/2;
    svGalignObj.svCarBoxParams.CarBox_height = pUpdate2DPersMatPrm->carBoxHeight;
    svGalignObj.svCarBoxParams.CarBox_width = pUpdate2DPersMatPrm->carBoxWidth;

    svGalignObj.saladbowlFocalLength = pUpdate2DPersMatPrm->saladbowlFocalLength;
    svGalignObj.defaultFocalLength = pUpdate2DPersMatPrm->defaultFocalLength;
    svGalignObj.downsamp_ratio = pUpdate2DPersMatPrm->downsampRatio;
    svGalignObj.max_num_features = pUpdate2DPersMatPrm->maxNumFeatures;
    svGalignObj.min_match_score = pUpdate2DPersMatPrm->minMatchScore;
    svGalignObj.max_BRIEF_score = pUpdate2DPersMatPrm->maxBRIEFScore;
    svGalignObj.min_distBW_feats = pUpdate2DPersMatPrm->minDistBWFeats;
    svGalignObj.outputMode = pUpdate2DPersMatPrm->outputMode;
    svGalignObj.subsampleratio = pUpdate2DPersMatPrm->subsampleRatio;
    svGalignObj.useDefaultPixelsPerCm = pUpdate2DPersMatPrm->useDefaultPixelsPerCm;
    svGalignObj.enablePixelsPerCm = pUpdate2DPersMatPrm->enablePixelsPerCm;

    memSize = initGAlignRunPersistentMem(
                        &svGalignObj,
                        pUpdate2DPersMatPrm->scratchBaseAddr);
    Vps_printf (" 2D Pers Mat Update Persistemt Mem Size = %d\n",memSize);
    UTILS_assert (memSize <= pUpdate2DPersMatPrm->srcatchMemSize);

    memSize = initGAlignRunScratchMem(
                        &svGalignObj,
                        pUpdate2DPersMatPrm->persistentBaseAddr);
    Vps_printf (" 2D Pers Mat Update Scratch Mem Size    = %d\n",memSize);
    UTILS_assert (memSize <= pUpdate2DPersMatPrm->persistentMemSize);

    // Convert CarBoxParams to internal seamMarkPts and overlapRegMarkPts
    svGalignObj.seamMarkPts[0] = 0;
    svGalignObj.seamMarkPts[1] = svGalignObj.SVOutDisplayWidth - 1;
    svGalignObj.seamMarkPts[2] = svGalignObj.SVOutDisplayHeight - 1;
    svGalignObj.seamMarkPts[3] = svGalignObj.SVOutDisplayWidth - 1;
    svGalignObj.seamMarkPts[4] = svGalignObj.SVOutDisplayHeight - 1;
    svGalignObj.seamMarkPts[5] = 0;
    svGalignObj.seamMarkPts[6] = 0;
    svGalignObj.seamMarkPts[7] = 0;

    svGalignObj.overlapRegMarkPts[0] = 0;
    svGalignObj.overlapRegMarkPts[1] = svGalignObj.svCarBoxParams.CarBoxCenter_x + (svGalignObj.svCarBoxParams.CarBox_width>>1);
    svGalignObj.overlapRegMarkPts[2] = svGalignObj.svCarBoxParams.CarBoxCenter_y - (svGalignObj.svCarBoxParams.CarBox_height>>1);
    svGalignObj.overlapRegMarkPts[3] = svGalignObj.SVOutDisplayWidth - 1;
    svGalignObj.overlapRegMarkPts[4] = svGalignObj.svCarBoxParams.CarBoxCenter_y + (svGalignObj.svCarBoxParams.CarBox_height>>1);
    svGalignObj.overlapRegMarkPts[5] = svGalignObj.svCarBoxParams.CarBoxCenter_x + (svGalignObj.svCarBoxParams.CarBox_width>>1);
    svGalignObj.overlapRegMarkPts[6] = svGalignObj.SVOutDisplayHeight - 1;
    svGalignObj.overlapRegMarkPts[7] = svGalignObj.SVOutDisplayWidth - 1;
    svGalignObj.overlapRegMarkPts[8] = svGalignObj.svCarBoxParams.CarBoxCenter_y + (svGalignObj.svCarBoxParams.CarBox_height>>1);
    svGalignObj.overlapRegMarkPts[9] = 0;
    svGalignObj.overlapRegMarkPts[10] = svGalignObj.SVOutDisplayHeight - 1;
    svGalignObj.overlapRegMarkPts[11] = svGalignObj.svCarBoxParams.CarBoxCenter_x - (svGalignObj.svCarBoxParams.CarBox_width>>1);
    svGalignObj.overlapRegMarkPts[12] = 0;
    svGalignObj.overlapRegMarkPts[13] = 0;
    svGalignObj.overlapRegMarkPts[14] = svGalignObj.svCarBoxParams.CarBoxCenter_y - (svGalignObj.svCarBoxParams.CarBox_height>>1);
    svGalignObj.overlapRegMarkPts[15] = svGalignObj.svCarBoxParams.CarBoxCenter_x - (svGalignObj.svCarBoxParams.CarBox_width>>1);

    for (j=0; j<svGalignObj.numCameras; j++)
    {
        svGalignObj.focalLength[j] = (Word16)pLensPrm2D->ldcLUT_focalLength;
    }


    for (j=0; j<1024; j++){
        svGalignObj.BRIEF_XY[j] = BRIEF_XYin[j];
    }

    for (j=0; j<256; j++){
        svGalignObj.sinatanLUT[j] = sinatanLUTin[j];
    }

    for (j=0; j<320; j++){
        svGalignObj.tanasinLUT[j] = tanasinLUTin[j];
    }

    for ( j=0; j<svGalignObj.SVOutDisplayHeight*svGalignObj.SVOutDisplayWidth*(1.25)*2; j++){
        svGalignObj.GAlignLUT[j] = GAlignLUT[j];
    }

    for (j = 0; j<8; j++){
        svGalignObj.descriptorPatternLUT[j] = descriptorPattern[j];
    }

    /* Pers Mat Updation for the 2D calibration */
    Vps_printf("2D_PERSMATUPDATE: Pers Mat Update for 2D started ..\n");

    Cache_inv(
            pUpdate2DPersMatPrm->persMatBuf,
            9 * 4 * pUpdate2DPersMatPrm->numCameras,
            Cache_Type_ALLD,
            TRUE);

    svGalignObj.persmat = pUpdate2DPersMatPrm->persMatBuf;

    for (cnt = 0U;cnt < svGalignObj.numCameras;cnt ++)
    {
        Cache_inv(
            pUpdate2DPersMatPrm->inImgPtr[cnt],
            (pUpdate2DPersMatPrm->imgPitch[0U] * pUpdate2DPersMatPrm->SVInCamFrmHeight * 3)/2,
            Cache_Type_ALLD,
            TRUE);

        svGalignObj.currFrm[cnt] = pUpdate2DPersMatPrm->inImgPtr[cnt];

        svGalignObj.focalLength[cnt] = (Word16)pLensPrm2D->ldcLUT_focalLength;

        LDC_Init(
                &svGalignObj.ldc[cnt],
                pLensPrm2D->ldcLUT_distortionCenters[2 * cnt],
                pLensPrm2D->ldcLUT_distortionCenters[2 * cnt + 1],
                pLensPrm2D->ldcLUT_focalLength,
                NULL,
                0U,
                0U,
                pLensPrm2D->ldcLUT_U2D_table,
                pLensPrm2D->ldcLUT_U2D_length,
                pLensPrm2D->ldcLUT_U2D_step);
    }

    svGenerate_2D_updatePersMat(
                        &svGalignObj,
                        pUpdate2DPersMatPrm->imgPitch);

    if (0 == svGalignObj.GAlign_Success)
    {
        Vps_printf("2D_PERSMATUPDATE: Pers Mat Update for 2D Failed\n");
    }
    else
    {
        Cache_wb(
                pUpdate2DPersMatPrm->persMatBuf,
                9 * 4 * pUpdate2DPersMatPrm->numCameras,
                Cache_Type_ALLD,
                TRUE);
    }

    pUpdate2DPersMatPrm->result = svGalignObj.GAlign_Success;

    Cache_wb(
            pUpdate2DPersMatPrm,
            sizeof(AlgorithmLink_update2DPersMatPrm),
            Cache_Type_ALLD,
            TRUE);

    Vps_printf("2D_PERSMATUPDATE: Pers Mat Update for 2D Done\n");
}
