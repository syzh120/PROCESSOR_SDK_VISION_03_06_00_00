/*
* Copyright (c) 2017, Texas Instruments Incorporated
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
* *  Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
* *  Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the distribution.
*
* *  Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
* PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
* CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
* EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
* OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
* WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
* OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
* EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/**
*  @file       ivision.h
*
*  @brief      This header defines all types, constants, and functions
*              shared by all implementations of the vision
*              algorithms.
*/
/**
 *  @defgroup   ti_xdais_IVISION   IVISION - Vision Algorithm Interface
 *
 *  This is the XDAIS IALG interface.
 */
/** @ingroup    ti_xdais_IVISION */
/*@{*/

#ifndef _TI_XDIAS_IVISION_ALG_
#define _TI_XDIAS_IVISION_ALG_


#include <ti/xdais/xdas.h>
#include <ti/xdais/ialg.h>

/**
*  @brief      Max plans supported in vsion algorithms
*              It can be used for multiple pyramid and also
*              for different channels- left open for user to
*              define
*/
#define IVISION_MAX_NUM_PLANES           (5)

/**
*  @brief      Max number of buffers that can be freed in
*              a process call
*/
#define   IVISION_MAX_NUM_FREE_BUFFERS  (30)

#define IVISION_CUSTOMFAILBASE  (IALG_CUSTOMFAILBASE + 1024) /**< Algorithm-specific failure code end.
                                   *
                                   *   @remarks This is 0xfffff800.
                                   */
#define IVISION_CUSTOMFAILEND (IALG_CUSTOMFAILEND)   /**< Algorithm-specific failure code base.
                                   *
                                   *   @remarks This is 0xffffff00.
                                   */

/**
*  @brief   This mem attribute is to indicate a memory area which is scratch and
*              doesn't demand algActivate and algDeactivate even it is shared with other
*              algorithm
*/

#define IVISION_CUSTOM_MEMATTRS_BASE (32)
typedef enum {

  IVISION_SCRATCH_NOCONTEXT = IVISION_CUSTOM_MEMATTRS_BASE
} IVISION_MemAttrs ;

typedef enum {
    IVISION_ERRORTYPE_NUM_INBUF_EXCEEDED = IALG_CUSTOMFAILBASE,      /**< Number of input buf provided
                                                   * is greater than expected from algorithm
                                                   */

    IVISION_ERRORTYPE_NUM_INBUF_LESS      /**< Number of input buf provided
                                                   * is lesser  than expected from algorithm
                                                   */
} IVISION_ErrorType;


typedef enum {
    IVISION_ACCESSMODE_CPU = 0,      /**< The algorithm <i>wrote</i> from the
                                       *   buffer using the CPU (via cache).
                                       */
    IVISION_ACCESSMODE_HWA = 1      /**< The algorithm <i>wrote</i> to the
                                       *   buffer using the HWA (eg : DMA).
                                       */
} IVISION_AccessMode;


typedef XDAS_Int32 (*ivisionCacheWriteBack)(XDAS_UInt32 addr, XDAS_UInt32 size);

typedef struct IVISION_Params {
    IALG_Params algParams;       /**< IALG Params */
    ivisionCacheWriteBack cacheWriteBack; /**< Function pointer for cache
                                          write back for cached based system.
                                          If the system is not using cache for
                                          data memory then the pointer can be
                                          filled with NULL. If the algorithm recives
                                          a input buffer with IVISION_AccessMode as
                                          @sa IVISION_ACCESSMODE_CPU and the
                                          @sa ivisionCacheWriteBack as NULL then
                                          the algorithm will return with NULL
                                          */
} IVISION_Params;



/**
*  @brief      Specifies a IVISION 2-dimensional point.
*/
typedef struct
{
  XDAS_Int32 x;  /**< Offset (in bytes) in x-direction */
  XDAS_Int32 y;  /**< Offset (in lines) in y-direction */
} IVISION_Point;

/**
*  @brief      Specifies a IVISION rectangle.
*/
typedef struct
{
  IVISION_Point topLeft;      /**< Top left corner of the retctangle */
  XDAS_UInt32 width;          /**< Width of the rectangle (in bytes)  */
  XDAS_UInt32 height;         /**< Height of the rectangle (in lines) */
} IVISION_Rect;

/**
*  @brief      Specifies a IVISION polygon.
*/
typedef struct
{
  XDAS_UInt32   numPoints;      /**< Number of points in the rectangle */
  IVISION_Point * points;       /**< Points of the polygon */
} IVISION_Polygon;


/**
*  @brief      A generic plane descriptor
*
*  @remarks    None
*/
typedef struct
{
  void *buf;                  /**< Pointer to the buffer           */
  XDAS_UInt32 width;          /**< Width of the buffer (in bytes)
                              * This feild can be viewd as pitch
                              * while precessing a ROI in the buffer
                              */
  XDAS_UInt32 height;         /**< Height of the buffer (in lines) */
  IVISION_Rect frameROI;      /**< Region of the interest for the current
                              * frame to be processed in the buffer.
                              * Dimensions need to be a
                              * multiple of internal block dimensions.
                              * Refer data sheet for block dimensions
                              * supported for the algorithm.
                              * This needs to be filled even if bit-0  of
                              * IVISION_InArgs#subFrameInfo is set to 1
                              */

  IVISION_Rect subFrameROI;   /**< Region of the intererst for the current
                              * sub frame to be processed in the buffer.
                              * Dimensions need to be a
                              * multiple of internal block dimenstions.
                              * Refer data sheet for block dimensions
                              * supported for the algorithm.
                              * This needs to be filled only if bit-0  of
                              * IVISION_InArgs#subFrameInfo is set to 1
                              */
  IVISION_Rect freeSubFrameROI;
                              /**< This ROI is portion of subFrameROI that
                              * can be freed after current slice process call.
                              * This field will be filled by the algorithm at
                              * end of each slice processing for all the input
                              * buffers (for all the output buffers this field
                              * needs to be ignored).
                              * This will be filled only if bit-0  of
                              * IVISION_InArgs#subFrameInfo is set to 1
                              */
  XDAS_Int32 planeType;       /**< Content of the buffer -
                              * for example Y component of NV12 */
  XDAS_Int32  accessMask;    /**< Mask filled by the algorithm for each output buffer,
                              *   declaring how the buffer was filled <b>by the
                              *   algorithm processor</b>.
                              *
                              *   @remarks  If the buffer was <b>not</b>
                              *             filled by the algorithm
                              *             processor (e.g., it was filled
                              *             via DMA or other hardware
                              *             accelerator that <i>doesn't</i>
                              *             write through the algorithm's
                              *             CPU), then will be set as
                              *             IVISION_AccessMode#IVISION_ACCESSMODE_HWA
                              *             otherwise it will be set to
                              *             IVISION_AccessMode#IVISION_ACCESSMODE_CPU.
                              *             All other values are reserved.
                              *
                              * @remarks  Algorithm will read this parameter
                              * from the input buffer and take necessary action
                              * based on the usage of each buffer by the
                              * algorithm.
                              * For case 1, if the algorithm is
                              * accessing a buffer using DMA and it was filled
                              * using CPU previously then the algorithm will
                              * use IVISION_Params#ivisionCacheWriteBack call-back function before
                              * using this buffer.
                              * Case 2. If algorithm is accessing a
                              * buffer using CPU and it was filled using
                              * CPU previously then it not call the
                              * IVISION_Params#ivisionCacheWriteBack call-back function.
                              *
                              *   @sa IVISION_Params
                              *   @sa IVISION_AccessMode
                              */
}IVISION_BufPlanes;


/**
*  @brief      A generic buffer descriptor
*
*  @remarks    None
*/

typedef struct
{
  XDAS_Int32 numPlanes;       /**< Number of image planes.
                              *
                              *   This must be in the range
                              *    0 - #IVISION_MAX_NUM_PLANES.
                              *    for NV12 this will be 2
                              *    for YUYV this will be 1
                              */
  IVISION_BufPlanes bufPlanes[IVISION_MAX_NUM_PLANES] ;
                             /**< Description of each planes      */
  XDAS_Int32 formatType;      /**< Format of the buffer data
                              *   for example NV12,BAYER,RGB,YUYV, etc
                              */
  XDAS_Int32 bufferId;        /**< Identifier to attach with the
                              *   input frames to be proccesd.
                              *
                              *   @remarks   This is useful when
                              *              algorithms requires
                              *              buffering and to support
                              *              buffer management.
                              *
                              *   @remarks   Zero (0) is <b>not</b> a
                              *              supported bufferId. This value
                              *              is reserved.
                              *
                              *   @sa IVISION_OutArgs::freeBufIDs.
                              */
  XDAS_UInt32 reserved[2];    /**< Reserved for later use */
} IVISION_BufDesc;


/**
*  @brief      Buffer descriptor list definition
*
*  @remarks    None
*/
typedef struct
{
  XDAS_UInt32 size;           /**< Size of this structure */
  XDAS_UInt32 numBufs;        /**< Number of elements of type IVISION_BufDesc in the list */
  IVISION_BufDesc **bufDesc; /**< Pointer to list of IVISION_BufDesc */
} IVISION_BufDescList;

/**
*  @brief      IVISION input buffer description list
*
*  @remarks    None
*/
typedef IVISION_BufDescList IVISION_InBufs;

/**
*  @brief      IVISION output buffer description list
*
*  @remarks    None
*/
typedef IVISION_BufDescList IVISION_OutBufs;

/**
*  @brief      IVISION input arguments to be passed in the algorithm process
*
*  @remarks    None
*/
typedef struct
{
  XDAS_UInt32 size;          /**< Size of this structure */
  XDAS_Int32  subFrameInfo;  /**< Sub Frame information - bit level information
                             * bit 0 - Sub frame processing enable (1) or disabled (0)
                             * bit 1 - First subframe of the picture (0/1)
                             * bit 2 - Last subframe of the picture (0/1)'
                             * bit 3 to 31 - reserved
                             */
} IVISION_InArgs;

/**
*  @brief      IVISION output arguments to be passed in the algorithm process
*
*  @remarks    None
*/
typedef struct
{
  XDAS_UInt32 size;           /**< Size of this structure */
  XDAS_Int32 inFreeBufIDs[IVISION_MAX_NUM_FREE_BUFFERS];  /**< This is an
                                                        *   array of bufferId's corresponding to the
                                                        *   input buffers that have been unlocked in the
                                                        *   current process call.
                                                        *
                                                        *   @remarks   The input buffers released by the
                                                        *              algorithm are indicated by
                                                        *              their non-zero ID (previously
                                                        *              provided via
                                                        *              IVISION_BufDesc#bufferId).
                                                        *
                                                        *   @remarks   A value of zero (0) indicates
                                                        *              an invalid ID.  The first zero
                                                        *              entry in array will indicate
                                                        *              end of valid inFreeBufIDs within
                                                        *              the array.  Hence the
                                                        *              application can stop searching
                                                        *              the array when it encounters the
                                                        *              first zero entry.
                                                        *
                                                        *   @remarks   If no input buffer was unlocked in
                                                        *              the process call,
                                                        *              @c inFreeBufIDs[0] will
                                                        *              have a value of zero.
                                                        *
                                                        *   @sa IVISION_BufDesc#bufferId
                                                        */
  XDAS_Int32 outFreeBufIDs[IVISION_MAX_NUM_FREE_BUFFERS];  /**< This is an
                                                        *   array of bufferId's corresponding to the
                                                        *   output buffers that have been unlocked in the
                                                        *   current process call.
                                                        *
                                                        *   @remarks   The output buffers released by the
                                                        *              algorithm are indicated by
                                                        *              their non-zero ID (previously
                                                        *              provided via
                                                        *              IVISION_BufDesc#bufferId).
                                                        *
                                                        *   @remarks   A value of zero (0) indicates
                                                        *              an invalid ID.  The first zero
                                                        *              entry in array will indicate
                                                        *              end of valid inFreeBufIDs within
                                                        *              the array.  Hence the
                                                        *              application can stop searching
                                                        *              the array when it encounters the
                                                        *              first zero entry.
                                                        *
                                                        *   @remarks   If no output buffer was unlocked in
                                                        *              the process call,
                                                        *              @c outFreeBufIDs[0] will
                                                        *              have a value of zero.
                                                        *
                                                        *   @sa IVISION_BufDesc#bufferId
                                                        */
  XDAS_UInt32 reserved[2];  /**< Reserved for later use */
} IVISION_OutArgs;


/**
 *  @brief      This must be the first field of all IVIDENC2
 *              instance objects
 */
typedef struct IVISION_Obj {
    struct IVISION_Fxns *fxns;
} IVISION_Obj;


/**
 *  @brief      Opaque handle to an IVISION objects.
 */
typedef struct IVISION_Obj  *IVISION_Handle;


typedef struct IVISION_Fxns {
  IALG_Fxns  ialg;  /**< XDAIS algorithm interface.
                    *
                    *   @sa      IALG_Fxns
                    */
  /**
  *  @brief      Vision algorithm Process call
  *
  *  @param[in]     handle          Handle to an algorithm instance.
  *  @param[in]     inBufs          Input video buffer descriptors.
  *  @param[in,out] outBufs         Output buffer descriptors.  The algorithm
  *                                 may modify the output buffer pointers.
  *  @param[in]     inArgs          Input arguments
  *  @param[out]    outArgs         Ouput results.
  *
  *  @retval     #IALG_EOK
  *  @retval     #IALG_EFAIL
  *
  */
  Int (*algProcess)(IVISION_Handle Handle, IVISION_InBufs *inBufs,
    IVISION_OutBufs *outBufs, IVISION_InArgs *inArgs,
    IVISION_OutArgs *outArgs);
  /**
  *  @brief      Vision algorithm Control call
  *
  *  @param[in]     handle          Handle to an algorithm instance.
  *  @param[in]     cmd             Command for the current control call.
  *                                 eg: set parameters, get parametrs, etc
  *  @param[in]     inParams        Input paramers for algorithms
  *  @param[out]    outParams       Input paramers for algorithms
  *
  *  @retval     #IALG_EOK
  *  @retval     #IALG_EFAIL
  *
  *  @remarks
  *   Algorithm will document the usage of
  *   each comamnd indetail. Application may choose to pass a pointer
  *   as NULL bassed on the the command
  *
  *  @remarks
  *   Example 1:
  *   Alg can define "ISP_CTRL_CMD_1" as the inParams
  *   will be read and also will update few parameters in
  *   the outparams.
  *   The updated parametrs will the specific to ISP_CTRL_CMD_1,
  *   this information will be decumnted in the algirthm spefic
  *   interface file ot the userguide
  *
  *  @code
  *    algControl((IALG_Handle)(&handle),ISP_CTRL_CMD_1,
  *   (const IALG_Params *)&createParams, (IALG_Params *)&outParams)
  *  @endcode
  *
  *  @remarks
  *   Example 2:
  *   Alg can define "ISP_CTRL_GET_PARAMS" as the
  *   inParams will not be read in this case and it will update the
  *   elements of the outParams. Algorithm still need to document
  *   the list of elements that will be upadted in the outParans
  *   for this control command
  *
  *  @code
  *   algControl((IALG_Handle)(&handle),
  *    ISP_CTRL_GET_PARAMS,NULL,(IALG_Params *)&outParams)
  *  @endcode
  *
  *  @remarks
  *   Example 3:
  *   Alg can define "ISP_CTRL_SET_PARAMS" as the
  *   inParams will be read in this case and it will not use
  *   outParams for any purpose
  *
  *  @code
  *    algControl((IALG_Handle)(&handle),
  *    ISP_CTRL_SET_PARAMS,(const IALG_Params *)&createParams, NULL);
  *  @endcode
  *
  */
  Int (*algControl)(IVISION_Handle Handle, IALG_Cmd cmd,
    const IALG_Params *inParams, IALG_Params *outParams);


} IVISION_Fxns;



/*@}*/
/* ti_xdais_IVISION */

#endif  /* _TI_XDIAS_IVISION_ALG_ */

/*==========================================================================*/
/*     END of the FILE                                                      */
/*==========================================================================*/

