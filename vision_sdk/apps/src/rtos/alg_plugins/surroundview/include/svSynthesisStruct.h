/*=======================================================================
 *
 *            Texas Instruments Internal Reference Software
 *
 *                           EP Systems Lab
 *                     Embedded Signal Processing
 *                             Imaging R&D
 *
 *         Copyright (c) 2013 Texas Instruments, Incorporated.
 *                        All Rights Reserved.
 *
 *
 *          FOR TI INTERNAL USE ONLY. NOT TO BE REDISTRIBUTED.
 *
 *                 TI Confidential - Maximum Restrictions
 *
 *
 *
 *=======================================================================
 *
 *  File: svSynthesisStruct.h
 *
 =======================================================================*/


#ifndef SV_SYNTH_STRUCT_INCLUDED_

#define SV_SYNTH_STRUCT_INCLUDED_

#include "../include/memRequestAlgo.h"
#include "../include/svCommonDefs.h"
#include "../include/globalDefs.h"

#ifndef PC_VERSION
#include <src/rtos/utils_common/include/utils_dma.h>

#define MAX_NUM_EDMA3_CH 9

typedef struct {
    unsigned int edmaChId;
    /**< EDMA CH ID that is used for this EDMA */

    unsigned int tccId;
    /**< EDMA TCC ID that is used for this EDMA */

    EDMA3_DRV_PaRAMRegs *pParamSet;
    /**< Pointer to physical area of PaRAM for this channel */
} EDMA3ChObj;
#endif

//Surround View Synthesis private structure: Contains all SV Synthesis input and output parameters.
//To be updated
typedef struct {

    //Word16        disableSV;
    Word16      disableSV_Synthesis;

    //Input frame size and output frame size
    Word16      SVInCamFrmHeight;
    Word16      SVInCamFrmWidth;
    Word16      SVOutDisplayHeight;
    Word16      SVOutDisplayWidth;

    //number of color channels
    Byte        numColorChannels;
    //number of cameras
    Byte        numCameras;
    //number of output parameters from photometric alignment, per camera, per color channel
    Byte        numParamsPAlignPerColorPerCam;

    //synthesis method
    Byte        method;     // stitch method option flag. 0: direct stitch; 1: linear blending
    Byte        blendlen;   // width of blending region

    Byte        outputMode; // 0: 2D or 1: 3D SRV or 2: 2D SRV with LDC or 3: 3D SRV with LDC

    // Subsample ratio for 3D SRV
    Byte        subsampleratio;

    // Overlay subsample ratio
    Byte overlaysampleratio;

    Word32      seam_offset; // Seam offlset from image corner. Positive for horizontal offset, negative for vertical offset
    // pointer to photometric LUT
    Byte        *PAlignLUT;
    // Added by Buyue, 12/3/2013
    Word32      **PAlignGain_RGB; //For YUV data, saves RGB gain after convert YUV to RGB; for RGB data, not used


    // pointer to geometric LUT and boundary information
#ifndef PC_VERSION
    uWord16     *restrict GAlignLUT;
    uWord32     *restrict GAlignViewLUT[MAX_INPUT_CAMERAS];
#else
    uWord16     *GAlignLUT;
#endif

    // 3D LDC SV pointers

    // Input to Synthesis block
    Word16     *LDC3D_width; // LDC width for 3D SRV with LDC
    Word16     *LDC3D_height; // LDC height for 3D SRV with LDC
    Word16     *car_posx; // Car position x in 3D SRV outpu with LDC
    Word16     *car_posy; // Car position y in 3D SRV outpu with LDC

    // 2D LDC SV pointers


    Byte     *BlendLUT;


    // Overlay and blending variables
    Byte     *overlaydata;
    Byte     *overlaytransparency;


    Byte        *L2memory; // For DMA

    uWord16     *DMALUT_blendregion; // For DMA
    uWord16     *DMALUT_singleviewregion; // For DMA

    AlgLink_MemRequests memRequestStruct;

    // pointers to input frames
#ifndef PC_VERSION
    Byte    *restrict currFrm[MAX_INPUT_CAMERAS];           // current input frames
    Byte    *restrict currFrm_UV[MAX_INPUT_CAMERAS];            // current input frames
#else
    Byte    *currFrm[MAX_INPUT_CAMERAS];            // current input frames
    Byte    *currFrm_UV[MAX_INPUT_CAMERAS];         // current input frames
#endif
    Byte    *prevFrm[MAX_INPUT_CAMERAS];            // previous input frames

    Word16 blockSizeV; //size of the statistics downsample factor
    Word16 blockSizeH;

    uWord16     *overlapRegMarkPts; //16 element
    uWord16     *seamMarkPts; //8 element
    //car box dimensions and center location
    SV_CarBox_ParamsStruct svCarBoxParams;

#ifndef PC_VERSION
// pointer to output frame
    Byte        *restrict outputFrm;

    // pointer to output statistic collection
    uWord16     *restrict outStatLUTPtr;

    EDMA3_DRV_Handle hEdma;
    // Handle to EDMA controller associated with this logical DMA channel

    EDMA3ChObj eDma3ChObj[MAX_NUM_EDMA3_CH];
    // EDMA3 Channel info
#else
    // pointer to output frame
    Byte        *outputFrm;

    // pointer to output statistic collection
    uWord16     *outStatLUTPtr;
#endif

    // Set to 1, if DSP need to create the car image, apply only for 2D SRV */
    Bool  enableCarOverlayInAlg;

    // Set to 1, if Syntesis LUT has been precalculated.
    uWord32 useSuppliedLUT;

    //Pointer to precalculated LUT
    Byte *synthLUTPtr;

    // Size of LUT in bytes
    uWord32 synthLUTSize;

    // Set to 1, if the LUT calculated on DSP needs to be saved
    uWord32 saveCalculatedLUT;

    Word16      ldcFrmWidth[MAX_INPUT_CAMERAS];
    Word16      ldcFrmHeight[MAX_INPUT_CAMERAS];
    Word16      carPosX;
    Word16      carPosY;
    Word16      carSizeX;
    Word16      carSizeY;
    UInt8       *pCarImage;
    UInt32      sizeOfCarImage;
    Word16      ldcPadX[MAX_INPUT_CAMERAS];
    Word16      ldcPadY[MAX_INPUT_CAMERAS];
    UInt8       dummyPad[32];
    uWord32     useUserBlendTable3DLDC;
    uWord32     chMap[MAX_INPUT_CAMERAS];

    uWord32     carBoxX[MAX_INPUT_CAMERAS];
    uWord32     carBoxY[MAX_INPUT_CAMERAS];
    uWord32     seamOriginX[MAX_INPUT_CAMERAS];
    uWord32     seamOriginY[MAX_INPUT_CAMERAS];

    uWord32     quadrantStartX[MAX_INPUT_CAMERAS];
    uWord32     quadrantEndX[MAX_INPUT_CAMERAS];
    uWord32     quadrantStartY[MAX_INPUT_CAMERAS];
    uWord32     quadrantEndY[MAX_INPUT_CAMERAS];

} svSynthStruct;

#endif
