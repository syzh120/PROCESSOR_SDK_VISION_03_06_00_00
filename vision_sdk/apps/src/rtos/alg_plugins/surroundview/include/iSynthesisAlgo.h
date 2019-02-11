/*
 *******************************************************************************
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file iSynthesisAlgo.h
 *
 * \brief Interface file for Alg_Synthesis algorithm on DSP
 *
 *        This Alg_Synthesis algorithm is only for demonstrative purpose.
 *        It is NOT product quality.
 *
 * \version 0.0 (Oct 2013) : [PS, VA, IP] First version
 *
 *******************************************************************************
 */

#ifndef ISYNTHESISALGO_H_
#define ISYNTHESISALGO_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include <include/alglink_api/algorithmLink_synthesis.h>

#ifndef PC_VERSION
    #include <include/link_api/system.h>

#endif

#include "memRequestAlgo.h"
#include "svCommonDefs.h"

#ifndef PC_VERSION
    #include <include/link_api/system_common.h>
    #include <src/rtos/utils_common/include/utils_mem.h>
#endif

/*******************************************************************************
 *  Control Commands
 *******************************************************************************
 */
/**
 *******************************************************************************
 *   \brief Used to update the size of input frame. Requires an pointer to of
 *              type SV_Synthesis_ControlParams
 *******************************************************************************
*/
#define SV_SYNTHESIS_CMD_UPDATE_LDC_WIDTH_HEIGHT        (1U)

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Structure used an to update the input frame size. Expected to be
 *              used with command SV_SYNTHESIS_CMD_UPDATE_LDC_WIDTH_HEIGHT.
 *              Refer #SV_Synthesis_ControlParams
 *******************************************************************************
*/
typedef struct
{
    UInt32 width[ALGORITHM_LINK_SRV_SYNTHESIS_MAX_VIEWS];
    /**< Width of the input frame, in pixels */
    UInt32 height[ALGORITHM_LINK_SRV_SYNTHESIS_MAX_VIEWS];
    /**< Height of the input frame, in number of lines */
    UInt32 carPosX;
    /**< Car Image start x position */
    UInt32 carPosY;
    /**< Car Image start x position */
    UInt32 carSizeX;
    /**< Car Image Width */
    UInt32 carSizeY;
    /**< Car Image Height */
    UInt32 *carImgPtr;
    /**< Pointer to car Image */
    UInt32 sizeOfcarImg;
    /**< Size of the car image in bytes */
    UInt32 padX[ALGORITHM_LINK_SRV_SYNTHESIS_MAX_VIEWS];
    /**< Number of pixels to be ignored */
    UInt32 padY[ALGORITHM_LINK_SRV_SYNTHESIS_MAX_VIEWS];
    /**< Number of lines to be ignored */
    Int8 *userBlendTableAddr;
    /**< User Blend Table Address */
    UInt32 chMap[ALGORITHM_LINK_SRV_SYNTHESIS_MAX_VIEWS];
    /**< Synthesis Channel mapping */

    UInt32 quadrantStartX[ALGORITHM_LINK_SRV_SYNTHESIS_MAX_VIEWS];
    /**< Synthesis Quadrant StartX */
    UInt32 quadrantEndX[ALGORITHM_LINK_SRV_SYNTHESIS_MAX_VIEWS];
    /**< Synthesis Quadrant EndX */
    UInt32 quadrantStartY[ALGORITHM_LINK_SRV_SYNTHESIS_MAX_VIEWS];
    /**< Synthesis Quadrant StartY */
    UInt32 quadrantEndY[ALGORITHM_LINK_SRV_SYNTHESIS_MAX_VIEWS];
    /**< Synthesis Quadrant EndY */
}SV_Synthesis_InputFrameCfg;

/**
 *******************************************************************************
 *
 *   \brief Structure containing the synthesis create time parameters
 *
 *******************************************************************************
*/
typedef struct
{
    //Input frame size
    Word16      SVInCamFrmHeight;
    Word16      SVInCamFrmWidth;

    //output frame size
    Word16      SVOutDisplayHeight;
    Word16      SVOutDisplayWidth;

    //number of color channels
    Byte        numColorChannels;

    //number of cameras
    Byte        numCameras;

    //car box dimensions and center location
    SV_CarBox_ParamsStruct svCarBoxParams;

    // Block Size for Statitsics collection (Should be 8,16,32,64...)
    Word16 blockSizeV;
    Word16 blockSizeH;

    // Blending Length (add default value)
    Byte    blendlen;
    // Offset location for seam
    Word32  seam_offset;

    Byte        outputMode; // 0: 2D or 1: 3D SRV or 2: 2D SRV with LDC or 3: 3D SRV with LDC

    // Subsample ratio for 3D SRV
    Byte         subsampleratio;

    // Set to 1, if DSP need to create the car image, apply only for 2D SRV */
    Bool        enableCarOverlayInAlg;

    // Set to 1, if Syntesis LUT has been precalculated.
    UInt32      useSuppliedLUT;

    //Pointer to precalculated LUT
    Byte        *synthLUTPtr;

    //LUT size in bytes
    UInt32      synthLUTSize;

    // Set to 1, if the LUT calculated on DSP needs to be saved
    uWord32     saveCalculatedLUT;

    Word16       ldcFrmWidth[MAX_NUM_VIEWS];
    Word16       ldcFrmHeight[MAX_NUM_VIEWS];
    /* LDC Input Frame size for all four camera,
       Used for synthesis control */
    // Car position when car rendering is enabled
    Word16       carPosX;
    Word16       carPosY;
    uWord32      useUserBlendTable3DLDC;
} SV_Synthesis_CreationParamsStruct;



/**
 *******************************************************************************
 *
 *   \brief Structure containing the synthesis control parameters
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32  cmd;
    /**< Command */
    void *cmdArgs;
    /**< Its associated arguments */
} SV_Synthesis_ControlParams;

/**
 *******************************************************************************
 *
 *   \brief Structure containing LDC slice parameters
 *
 *******************************************************************************
*/
typedef struct
{
    uWord32 sliceX;
    /**< StartX of the slice */

    uWord32 sliceY;
    /**< StartY of the slice */

    uWord32 sliceW;
    /**< Width of the slice */

    uWord32 sliceH;
    /**< Height of the slice */

    uWord32 blockWidth;
    /**< Block width for the slice */

    uWord32 blockHeight;
    /**< Block height for the slice */

} SV_Synthesis_slicePrm;

/**
 *******************************************************************************
 *
 *   \brief Structure containing the array of Synthesis Process Parameters
 *
 *******************************************************************************
*/
typedef struct
{
    void *svHandle;
    /**< SV handle pointer */
    System_VideoFrameCompositeBuffer *pCompositeBuffer;
    /**< Input Composite Buffer address */
    System_VideoFrameBuffer *pVideoOutputBuffer;
    /**< Output Buffer Address */
    uWord32 *inPitch;
    /**< Input Pitch Array */
    uWord32 *outPitch;
    /**< Ouput Pitch Array */
    void *inGALUTPtr;
    /**< Input GA LUT address */
    uWord32 *inPAlignLUTPtr;
    /**< Input PA LUT address */
    void *outStatLUTPtr;
    /**< Ouput Status LUT address */
    void *outBlendLUTPtr;
    /**< Output Blend LUT address */
    uWord32 dataFormat;
    /**< Input Data Format */
    uWord32 synthesisMode;
    /**< Synthesis Mode */
}SV_Synthesis_ProcessPrm;

/**
 *******************************************************************************
 *
 *   \brief Structure containing the array of slice parameters
 *
 *******************************************************************************
*/
typedef struct
{
    uWord32  numSlices;
    /**< Num of slices */

    SV_Synthesis_slicePrm slice[ALGORITHM_LINK_SRV_SYNTHESIS_MAX_VIEWS];
    /**< Slice parameters */

} SV_Synthesis_ldcSliceListPrm;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */


 /**
 *******************************************************************************
 *
 * \brief Implementation of memory query for synthesis algo
 *
 * \return  void
 *
 *******************************************************************************
 */
void Alg_SynthesisMemQuery(
    SV_Synthesis_CreationParamsStruct *Synthesis_createParams,
    AlgLink_MemRequests *memPtr,
    Byte FirstTimeQuery);


 /**
 *******************************************************************************
 *
 * \brief Implementation of create for synthesis algo
 *
 * \param  pCreateParams    [IN] Creation parameters for synthesis Algorithm
 *                               and memory pointer
 *
 * \param   outBlendLUTPtr  [IN] Pointer for Blending LUT
 * \return  Handle to algorithm if creation is successful else return NULL
 *
 *******************************************************************************
 */
void *Alg_SynthesisCreate(SV_Synthesis_CreationParamsStruct *createParams, AlgLink_MemRequests *memPtr, uWord32 *outBlendLUTPtr);


/**
 *******************************************************************************
 *
 * \brief Implementation of Process for synthesis algo
 *
 *        Supported formats are SYSTEM_DF_YUV422I_YUYV, SYSTEM_DF_YUV420SP_UV
 *        It is assumed that the width of the image will
 *        be multiple of 4 and buffer pointers are 32-bit aligned.
 *
 * \param  algHandle    [IN] Algorithm object handle
 * \param  inPtr[]      [IN] Matrix of input pointers
 *                           First Index: Plane Index
 *                              Index 0 - Pointer to Y data in case of YUV420SP,
 *                                      - Single pointer for YUV422IL or RGB
 *                              Index 1 - Pointer to UV data in case of YUV420SP
 *                           Second Index: View ID Index
 *                              Index 0 - view ID 0
 *                              Index 1 - view ID 1 and so on.
 * \param  outPtr[]     [IN] Array of output pointers.
 *                              Index 0 - Pointer to Y data in case of YUV420SP,
 *                                      - Single pointer for YUV422IL or RGB
 *                              Index 1 - Pointer to UV data in case of YUV420SP
 * \param  width        [IN] width of input image
 * \param  height       [IN] height of output image
 * \param  inPitch[]    [IN] Array of pitch of input image (Address offset
 *                           b.n. two  consecutive lines, interms of bytes)
 *                           Indexing similar to array of input pointers
 *                           First Index
 * \param  outPitch[]   [IN] Array of pitch of output image (Address offset
 *                           b.n. two  consecutive lines, interms of bytes)
 *                           Indexing similar to array of input pointers
 * \param  inGALUTPtr[] [IN] Array of pointers for GA LUTs used.
 *                              Index 0 - Pointer to Single view LUT
 *                              Index 1 - Pointer to Dual view LUT1
 *                              Index 2 - Pointer to Dual view LUT2
 * \param  inPCLUTPtr    [IN] Pointer for Photometric Correction params
 * \param  outStatLUTPtr [IN] Pointer for statistics generated
 * \param  LDC3D_width, // LDC width for 3D SRV with LDC
 * \param  LDC_3Dheight, // LDC height for 3D SRV with LDC
 * \param  car_posx, // Car position x in 3D SRV outpu with LDC
 * \param  car_posy, // Car position y in 3D SRV outpu with LDC
 * \param  dataFormat    [IN] Different image data formats. Refer
 *                           System_VideoDataFormat. Assumption that input
 *                           image and output image will have same data format.
 * \param  synthesisMode [IN] 0 - Simple synthesis from one view
 *                            1 - Blending synthesis from two views
 *
 * \return  SYSTEM_LINK_SYNTHESIS_RPOCESS_OK on success
 *
 *******************************************************************************
 */
Int32 Alg_SynthesisProcess(SV_Synthesis_ProcessPrm *pTemp);

/**
 *******************************************************************************
 *
 * \brief Implementation of Control for synthesis algo
 *
 * \param  algHandle             [IN] Algorithm object handle
 * \param  pControlParams        [IN] Pointer to Control Params
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Alg_SynthesisControl(void                       *pAlgHandle,
                           SV_Synthesis_ControlParams *pControlParams);

/**
 *******************************************************************************
 *
 * \brief Implementation of Delete for synthesis algo
 *
 * \param  algHandle             [IN] Algorithm object handle
 * \param  memPtr                [IN] pointer to memory used by algo
 *
 * \return
 *
 * \notes:
 Framework would call this and the algorithm needs to populate AlgLink_MemRequests, like Memquery. But this time algorithm will give the pointers also, so that framework can free it up.
 That means algorithm need to keep an internal copy of AlgLink_MemRequests, during create, so that you can send it back to framework during delete.
 *******************************************************************************
 */
Int32 Alg_SynthesisDelete(void *pAlgHandle,
                          AlgLink_MemRequests *memPtr);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* Nothing beyond this point */
