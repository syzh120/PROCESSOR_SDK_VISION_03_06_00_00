/*
 * Copyright (c) 2012-2014, Texas Instruments Incorporated
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
 */
/**
 *  @file       ti/sdo/fc/ecpy/ecpy.h
 *
 *  @brief      ECPY Definitions - High performance functional library for use
 *              with the EDMA3 DMA peripheral.
 *              Provides a comprehensive list of DMA operations an algorithm
 *              can perform on logical DMA channels it acquires through the
 *              IRES_EDMA3CHAN protocol.
 *
 *  @remark     ECPY library contains two sets of functions: direct and
 *              non-direct.
 *              The direct APIs are functions prefixed with 'ECPY_direct' and
 *              are faster due to less state maintanence, fewer checks and/or
 *              lack of PaRAM shadowing of the 1st transfer. As a result they
 *              are slightly harder and require the caller to ensure integrity
 *              of state, for example, to make sure each  ECPY_directStart call
 *              is matched with exactly one ECPY_directWait call. Another
 *              example is the need to remember to re-configure first transfer
 *              following a linked transfer or single 3D transfer.
 *
 *              The non-direct APIs are slightly easier to use and maintain
 *              state and persistence of 1st transfer's settings across
 *              transfers.
 *
 *              It is important to *not* mix and match direct and non-direct
 *              functions for any given channel, as this may result in
 *              unexpected behavior.
 */

/**
 *  @defgroup   ti_sdo_fc_ecpy_ECPY ECPY
 *
 *              The ECPY module provides a comprehensive list of DMA operations
 *              applications or algorithms can perform on logical DMA channels
 *              it acquires through the IRES_EDMA3CHAN protocol. Example of ECPY
 *              operations include channel configuration, DMA transfer
 *              scheduling, and DMA transfer synchronization.
 *
 *  @remark     For additional information, please refer to the
 *              "Using DMA with Framework Components for 'C64x+" document.
 */
#ifndef ti_sdo_fc_ecpy_ECPY_
#define ti_sdo_fc_ecpy_ECPY_


#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_sdo_fc_ecpy_ECPY */
/*@{*/

#define ti_sdo_fc_ires_NOPROTOCOLREV
#include <ti/sdo/fc/ires/edma3chan/ires_edma3Chan.h>

#define ECPY_GTNAME "ti.sdo.fc.ecpy"

/**
 * @brief       Name to pass to Diags_setMask() to enable logging for ECPY
 *              functions. For example,
 *                  Diags_setMask(ECPY_MODNAME"+EX1234567");
 *              turns on all Log statements in this module.
 *              Diags_setMask() must be called after initialization to take
 *              effect.
 */
#define ECPY_MODNAME "ti.sdo.fc.ecpy"


/**
 *  @brief  ECPY 16-bit param field structure. These values are passed to
 *          ECPY_configure16() to indicate the field of the
 *          ECPY_Params structure to be changed.
 */
typedef enum ECPY_ParamField16b {

    ECPY_PARAMFIELD_ELEMENTSIZE =  8,
    ECPY_PARAMFIELD_NUMELEMENTS = 10 ,
    ECPY_PARAMFIELD_ELEMENTINDEX_SRC = 16,
    ECPY_PARAMFIELD_ELEMENTINDEX_DST = 18,
    ECPY_PARAMFIELD_FRAMEINDEX_SRC =  24,
    ECPY_PARAMFIELD_FRAMEINDEX_DST =  26,
    ECPY_PARAMFIELD_NUMFRAMES = 28

} ECPY_ParamField16b;

/**
 *  @brief      ECPY 32-bit param field structure. These values are passed to
 *          ECPY_configure32() to indicate the field of the
 *          ECPY_Params structure to be changed.
 */
typedef enum ECPY_ParamField32b {

    ECPY_PARAMFIELD_SRCADDR = 4,
    ECPY_PARAMFIELD_DSTADDR = 12,
    ECPY_PARAMFIELD_ELEMENTINDEXES = 16,
    ECPY_PARAMFIELD_FRAMEINDEXES = 24

} ECPY_ParamField32b;

/**
 *  @brief      ECPY DMA Transfer Types:
 *
 *  Note that all transfers can be specified using the ECPY_2D2D transfer
 *  type, and providing element and frame indices for both source and
 *  destination. However, the other transfer types are provided to simplify
 *  configuration when applicable. For example, when using the ECPY_1D2D
 *  transfer type, you do not need to set the source element and frame
 *  indices in the ECPY_Params structure.
 */
typedef enum ECPY_TransferType {

    /**
     *  Only one element is copied from source to destination.
     *  The size of the element is specified in the elementSize field of
     *  ECPY_Params
     */
    ECPY_1D1D,

    /**
     *  After each element is copied to destination, the source
     *  and destination of the next element to copy is updated
     *  as follows:
     *  - src = src + element size
     *  - dst = dst + destination element index
     *
     *  After an entire frame is copied (the frame size specified by the
     *  numElements field of ECPY_Params), the source and destination of
     *  the next frame to copy are given by:
     *  - src = src + element size
     *  - dst = start of frame + destination frame index
     */
    ECPY_1D2D,

    /**
     *  This is similar to ECPY_1D2D, except that source and
     *  destination are updated after an element is copied,
     *  as follows:
     *  - src = src + source element index
     *  - dst = dst + element size
     *
     *  After an entire frame is copied by:
     *  - src = start of frame + source frame index
     *  - dst = dst + element size
     */
    ECPY_2D1D,

    /**
     *  This transfer type combines ECPY_1D2D and ECPY_2D1D,
     *  so that source and destination are updated after an
     *  element is copied by:
     *  - src = src + source element index
     *  - dst = dst + destination element index
     *
     *  After a frame is copied by:
     *  - src = start of frame + source frame index
     *  - dst = start of frame + destination frame index
     */
    ECPY_2D2D
} ECPY_TransferType;

/**
 *  @brief      Handle to "logical" ECPY Channel
 */
typedef struct ECPY_Obj *ECPY_Handle;


/**
 *  @brief  DMA transfer specific parameters.  Defines the configuration
 *          of a logical channel.
 */
typedef struct ECPY_Params {

    /** 1D1D, 1D2D, 2D1D or 2D2D */
    ECPY_TransferType transferType;

    /** Source Address of the DMA transfer */
    Void *         srcAddr;

    /** Destination Address of the DMA transfer */
    Void *         dstAddr;

    /** Number of consecutive bytes in each 1D transfer vector (ACNT)   */
    unsigned short elementSize;

    /** Number of 1D vectors in 2D transfers (BCNT) */
    unsigned short numElements;

    /** Number of 1D1D, 1D2D, 2D1D or 2D2D frames to transfer (CCNT) */
    unsigned short numFrames ;

    /**
     *  Offset in number of bytes from beginning of each 1D vector to the
     *  beginning of the next 1D vector.  (SBIDX)
     */
    short srcElementIndex;

    /**
     *  Offset in number of bytes from beginning of each 1D vector to the
     *  beginning of the next 1D vector.  (DBIDX)
     */
    short dstElementIndex;

    /**
     *  Offset in number of bytes from beginning of 1D vector of current
     *  (source) frame to the beginning of next frame's first 1D vector.
     *  (SCIDX): signed value between -32768 and 32767.
     */
    short srcFrameIndex;

    /**
     *  Offset in number of bytes from beginning of 1D vector of current
     *  (destination) frame to the beginning of next frame's first 1D vector.
     *  (DCIDX): signed value between -32768 and 32767.
     */
    short dstFrameIndex;

} ECPY_Params;


/**
 *  @brief      Configures the DMA transfer settings for the transfer=transferNo
 *              of the logical channel. Except for transferNo==1, the physical
 *              EDMA3 PaRAM associated with the transfer is modified. For
 *              transferNo==1 a "shadow" of the PaRAM registers gets configured,
 *              so that the configuration of 1st transfer remains persistent
 *              following ECPY_startEdma() calls.
 *
 *  @param[in]  handle      ECPY channel handle.
 *  @param[in]  params      DMA transfer specific parameters used to
 *                          configure this logical DMA channel.
 *  @param[in]  transferNo  Indicates the individual transfer to be
 *                          configured using the passed 'params'
 *
 *  @pre        channel must be in active state
 *  @pre        valid ECPY_Handle handle
 *  @pre        1 <= transferNo <= originally requested number of transfers
 *  @post       Intermediate transfers are programmed with TCCMODE set to Early
 *              (default mode when channel is created ) or Normal Completion
 *              depending on the most recently configured Transfer Completion
 *              mode.
 *
 *  @remarks    Both an inlined version and a non-inlined version of this
 *              function are supported. To use the inlined version, add the
 *              line \#define ECPY_CONFIGURE_INLINE or
 *              \#define ECPY_INLINE_ALL to the source file where this
 *              function is used. The \#define must go above the line,
 *              \#include <ecpy.h>. By default, this function will not be
 *              inlined. Another alternative is to define the macro in the
 *              build option of the file or of the project file.
 */
#if defined(ECPY_CONFIGURE_INLINE) || defined(ECPY_INLINE_ALL)
#include <ti/sdo/fc/ecpy/ecpy_configure.h>
#else
Void ECPY_configure(ECPY_Handle handle, ECPY_Params * restrict params,
    short transferNo);
#endif

/**
 *  @brief      Configure the DMA transfer settings of handle's 'transferNo'
 *              transfer. This function always directly configures the physical
 *              EDMA3 PaRAM associated with the transfer. Since no shadow is
 *              used for the 1st transfer, the configuration settings of the
 *              1st transfer gets lost following linked transfers or when the
 *              1st transfer is a 3D transfer (numFrames > 1).
 *
 *  @param[in]  handle      ECPY channel handle.
 *  @param[in]  params      DMA transfer specific parameters used to
 *                          configure this logical DMA channel.
 *  @param[in]  transferNo  Indicates the individual transfer to be
 *                          configured using the passed 'params'
 *
 *  @pre        channel must be in active state
 *  @pre        valid ECPY_Handle handle
 *  @pre        1 <= transferNo <= originally requested number of transfers
 *  @post       Intermediate transfers are programmed with TCCMODE set to Early
 *              (default mode when channel is created ) or Normal Completion
 *              depending on the most recently configured Transfer Completion
 *              mode.
 *
 *  @remarks    Both an inlined version and a non-inlined version of this
 *              function are supported. To use the inlined version, add the
 *              line \#define ECPY_DIRECTCONFIGURE_INLINE or
 *              \#define ECPY_INLINE_ALL to the source file where this
 *              function is used. The \#define must go above the line,
 *              \#include <ecpy.h>. By default, this function will not be
 *              inlined. Another alternative is to define the macro in the
 *              build option of the file or of the project file.
 */
#if defined(ECPY_DIRECTCONFIGURE_INLINE) || defined(ECPY_INLINE_ALL)
#include <ti/sdo/fc/ecpy/ecpy_directconfigure.h>
#else
Void ECPY_directConfigure(ECPY_Handle handle, ECPY_Params * restrict params,
    short transferNo);
#endif


/**
 *  @brief      Modify the 16-bit DMA transfer parameter, indicated by the
 *              parameter field id, fieldId, of the current channel settings.
 *
 *  @param[in]  handle      IRES_EDMA3CHAN channel handle.
 *  @param[in]  fieldId     Indicates which of the parameters is to be
 *                          modified.
 *  @param[in]  value       New value of the parameter to be modified.
 *  @param[in]  transferNo  Indicates which transfer the parameters correspond
 *                          to (same value that would be passed to
 *                          ECPY_configure()).
 *
 *  @pre        Algorithm instance must be in "active" state using IALG
 *              interface.
 *
 *  @pre        Channel must be in "active" state.
 *
 *  @pre        ECPY_configure() must have previously been called at least once
 *              since channel activation.
 *  @pre        1 <= transferNo <= originally requested number of transfers
 *
 *  @remarks    Both an inlined version and a non-inlined version of this
 *              function are supported. To use the inlined version, add the
 *              line \#define ECPY_CONFIGURE16_INLINE or
 *              \#define ECPY_INLINE_ALL to the source file where this
 *              function is used. The \#define must go above the line,
 *              \#include <ecpy.h>. By default, this function will not be
 *              inlined. Another alternative is to define the macro in the
 *              build option of the file or of the project file.
 *
 *  @remarks    Once a channel has been configured once with ECPY_configure(),
 *              ECPY_configure16() can be used to update any of the
 *              16-bit parameter fields, for example, the number of elements
 *              in a frame to be transferred.
 *
 */
#if defined(ECPY_CONFIGURE16_INLINE) || defined(ECPY_INLINE_ALL)
#include <ti/sdo/fc/ecpy/ecpy_configure16.h>
#else
Void ECPY_configure16(ECPY_Handle handle, ECPY_ParamField16b fieldId,
        unsigned short value, short transferNo);
#endif

/**
 *  @brief      Modify the 16-bit DMA transfer parameter, indicated by the
 *              parameter field id, fieldId, of the current channel settings.
 *              This function always directly configures the physical
 *              EDMA3 PaRAM's 16-bit half of the 32-bit registered associated
 *              with the transfer & field . No shadow is used.
 *
 *  @param[in]  handle      IRES_EDMA3CHAN channel handle.
 *  @param[in]  fieldId     Indicates which of the parameters is to be
 *                          modified.
 *  @param[in]  value       New value of the parameter to be modified.
 *  @param[in]  transferNo  Indicates which transfer the parameters correspond
 *                          to (same value that would be passed to
 *                          ECPY_directConfigure()).
 *
 *  @pre        Algorithm instance must be in "active" state using IALG
 *              interface.
 *
 *  @pre        Channel must be in "active" state.
 *  @pre        ECPY_directConfigure() must have been called at least once
 *              since channel activation.
 *  @pre        1 <= transferNo <= originally requested number of transfers
 *
 *  @remarks    Both an inlined version and a non-inlined version of this
 *              function are supported. To use the inlined version, add the
 *              line \#define ECPY_DIRECTCONFIGURE16_INLINE or
 *              \#define ECPY_INLINE_ALL to the source file where this
 *              function is used. The \#define must go above the line,
 *              \#include <ecpy.h>. By default, this function will not be
 *              inlined. Another alternative is to define the macro in the
 *              build option of the file or of the project file.
 *
 *  @remarks    Once a channel has been configured with ECPY_directConfigure(),
 *              ECPY_directConfigure16() can be used to update any of the
 *              16-bit parameter fields, for example, the number of elements
 *              in a frame to be transferred.
 *
*/
#if defined(ECPY_DIRECTCONFIGURE16_INLINE) || defined(ECPY_INLINE_ALL)
#include <ti/sdo/fc/ecpy/ecpy_directconfigure16.h>
#else
Void ECPY_directConfigure16(ECPY_Handle handle, ECPY_ParamField16b fieldId,
        unsigned short value, short transferNo);
#endif

/**
 *  @brief      Modify the 32-bit DMA transfer parameter, indicated by the
 *              parameter field id, fieldId, of the current channel settings.
 *
 *  @param[in]  handle      ECPY  channel handle.
 *  @param[in]  fieldId     Indicates which of the parameters is to be modified.
 *  @param[in]  value       New value of the parameter to be modified.
 *  @param[in]  transferNo  Indicates which transfer the parameters correspond
 *                          to (same value that would be passed to
 *                          ECPY_configure()).
 *
 *  @pre        @c handle must be a valid channel handle.
 *
 *  @pre        Algorithm instance must be in "active" state using IALG
 *              interface.
 *
 *  @pre        Channel must be in 'active' state.
 *
 *  @pre        ECPY_configure() must have previously been called at least once
 *              since channel activation.
 *  @pre        1 <= transferNo <= originally requested number of transfers
 *
 *  @remarks    Once a channel has been configured once with ECPY_configure(),
 *              ECPY_configure32() can be used to update any of the
 *              32-bit parameter fields, for example, the source address of
 *              the data to be transferred.
 *
 *  @remarks    Both an inlined version and a non-inlined version of this
 *              function are supported. To use the inlined version, add the
 *              line \#define ECPY_CONFIGURE32_INLINE or
 *              \#define ECPY_INLINE_ALL to the source file where this
 *              function is used. The \#define must go above the line,
 *              \#include <ecpy.h>. By default, this function will not be
 *              inlined. Another alternative is to define the macro in the
 *              build option of the file or of the project file.
 *
*/
#if defined(ECPY_CONFIGURE32_INLINE) || defined(ECPY_INLINE_ALL)
#include <ti/sdo/fc/ecpy/ecpy_configure32.h>
#else
Void ECPY_configure32(ECPY_Handle handle, ECPY_ParamField32b fieldId,
        unsigned int value, short transferNo);
#endif

/**
 *  @brief      Modify the 32-bit DMA transfer parameter, indicated by the
 *              parameter field id, fieldId, of the current channel settings.
 *
 *  @param[in]  handle      ECPY  channel handle.
 *  @param[in]  fieldId     Indicates which of the parameters is to be
 *                          modified.
 *  @param[in]  value       New value of the parameter to be modified.
 *  @param[in]  transferNo  Indicates which transfer the parameters correspond
 *                          to (same value that would be passed to
 *                          ECPY_configure()).
 *
 *  @pre        @c handle must be a valid channel handle.
 *
 *  @pre        Algorithm instance must be in "active" state using IALG
 *              interface.
 *
 *  @pre        Channel must be in 'active' state.
 *
 *  @pre        ECPY_directConfigure() must have previously been called at
 *              least once since channel activation.
 *  @pre        1 <= transferNo <= originally requested number of transfers
 *
 *  @remarks    Once a channel has been configured once with
 *              ECPY_directConfigure(), the ECPY_directConfigure32() functino
 *              can be called to update any of the 32-bit parameter fields,
 *              for example, the source address of the data to be transferred.
 *
 *  @remarks    Both an inlined version and a non-inlined version of this
 *              function are supported. To use the inlined version, add the
 *              line \#define ECPY_DIRECTCONFIGURE32_INLINE or
 *              \#define ECPY_INLINE_ALL to the source file where this
 *              function is used. The \#define must go above the line,
 *              \#include <ecpy.h>. By default, this function will not be
 *              inlined. Another alternative is to define the macro in the
 *              build option of the file or of the project file.
 *
*/
#if defined(ECPY_DIRECTCONFIGURE32_INLINE) || defined(ECPY_INLINE_ALL)
#include <ti/sdo/fc/ecpy/ecpy_directconfigure32.h>
#else
Void ECPY_directConfigure32(ECPY_Handle handle, ECPY_ParamField32b fieldId,
        unsigned int value, short transferNo);
#endif

/**
 *  @brief      Indicate that a given transfer will be the last in a sequence
 *              of linked transfers.
 *
 *              This API can be used to dynamically change the number of
 *              transfers in a linked transfers.
 *
 *  @param[in]  handle      ECPY channel handle.
 *  @param[in]  transferNo  Indicates the transfer number that will be the last
 *                          one of the set of linked transfers.
 *
 *  @pre        Valid channel handle.
 *  @pre        Channel must be in 'active' state.
 *  @pre        1 <= transferNo <= originally requested number of transfers
 *  @pre        ECPY_cnfigure() must have previously been called at least
 *              once since channel activation.
 *
 *  @remarks    This API can be used if a channel was created to transfer
 *              'numTransfers' linked transfers, but at some point, it will be
 *              used to transfer a different number of transfers.
 *
 *  @remarks    Both an inlined version and a non-inlined version of this
 *              function are supported. To use the inlined version, add the
 *              line \#define ECPY_SETFINAL_INLINE or
 *              \#define ECPY_INLINE_ALL to the source file where this
 *              function is used. The \#define must go above the line,
 *              \#include <ecpy.h>. By default, this function will not be
 *              inlined. Another alternative is to define the macro in the
 *              build option of the file or of the project file.
 *
 */
#if defined(ECPY_SETFINAL_INLINE) || defined(ECPY_INLINE_ALL)
#include <ti/sdo/fc/ecpy/ecpy_setfinal.h>
#else
Void ECPY_setFinal(ECPY_Handle handle, short transferNo);
#endif

/**
 *  @brief      Indicate that a given transfer will be the last in a sequence
 *              of linked transfers.
 *
 *              This API can be used to dynamically change the number of
 *              transfers in a linked transfers.
 *
 *  @param[in]  handle      ECPY channel handle.
 *  @param[in]  transferNo  Indicates the transfer number that will be the last
 *                          one of the set of linked transfers.
 *
 *  @pre        Valid channel handle.
 *  @pre        Channel must be in 'active' state.
 *  @pre        1 <= transferNo <= originally requested number of transfers
 *  @pre        ECPY_directConfigure() must have previously been called at
 *              least once since channel activation.
 *
 *  @remarks    This API can be used if a channel was created to transfer
 *              'numTransfers' linked transfers, but at some point, it will be
 *              used to transfer a different number of transfers.
 *
 *  @remarks    Both an inlined version and a non-inlined version of this
 *              function are supported. To use the inlined version, add the
 *              line \#define ECPY_DIRECTSETFINAL_INLINE or
 *              \#define ECPY_INLINE_ALL to the source file where this
 *              function is used. The \#define must go above the line,
 *              \#include <ecpy.h>. By default, this function will not be
 *              inlined. Another alternative is to define the macro in the
 *              build option of the file or of the project file.
 *
 */
#if defined(ECPY_DIRECTSETFINAL_INLINE) || defined(ECPY_INLINE_ALL)
#include <ti/sdo/fc/ecpy/ecpy_directsetfinal.h>
#else
Void ECPY_directSetFinal(ECPY_Handle handle, short transferNo);
#endif

/**
 *  @brief      Indicate the memory space that DMA transfers submitted to
 *              the channel associated with the handle will modify.
 *              This information can be used for channel to TC Queue mapping
 *              for avoiding known Silicon GEM lockup issues or for
 *              performance improvements.
 *
 *  @param[in]  handle  ECPY channel handle.
 *  @param[in]  mode    DMA destination description of type
 *                      IRES_EDMA3CHAN_DmaDestType.
 */
Void ECPY_setDestinationMemoryMode(ECPY_Handle handle, short mode);

/**
 *  @brief      Submit a single or linked transfer using the most recently
 *              configured transfer parameter settings.
 *
 *  @param[in]  handle  ECPY channel handle.
 *
 *  @pre        Valid channel handle.
 *  @pre        Channel must be in 'active' state.
 *
 *  @pre        Channel must be in 'configured' state.
 *  @pre        ECPY_configure() must be called at least once for each transfer
 *              that will be started.
 *
 *  @remarks    Most recent ECPY_configure(), ECPY_configure16 and
 *              ECPY_configure32 settings will be in effect for each transfer.
 *
 *  @pre        When the number of transfers assigned to the channel are > 1,
 *              this function will submit a set of linked EDMA transfers,
 *              ordered by the transferNo's of the channel.
 *              The final transfer of the linked set will be the transfer
 *              indicated by the most recent ECPY_setFinal() call.
 *              If no ECPY_setFinal has been previously called, then
 *              all transfers assigned to the channel will be linked together.
 *
 *  @post       handle->transferPending = TRUE
 *
 *  @remarks    Both an inlined version and a non-inlined version of this
 *              function are supported. To use the inlined version, add the
 *              line \#define ECPY_START_INLINE or
 *              \#define ECPY_INLINE_ALL to the source file where this
 *              function is used. The \#define must go above the line,
 *              \#include <ecpy.h>. By default, this function will not be
 *              inlined. Another alternative is to define the macro in the
 *              build option of the file or of the project file.
 *
 */
#if defined(ECPY_START_INLINE) || defined(ECPY_INLINE_ALL)
#include <ti/sdo/fc/ecpy/ecpy_start.h>
#else
Void ECPY_start(ECPY_Handle handle);
#endif


/**
 *  @brief      Submit a single or linked transfer using the most recently
 *              'direct' configured transfer parameter settings.
 *
 *  @param[in]  handle  ECPY channel handle.
 *
 *  @pre        Valid channel handle.
 *  @pre        Channel must be in 'active' state.
 *
 *  @pre        Channel must be in 'direct configured' state.
 *  @pre        ECPY_directConfigure() must be called at least once for each
 *              transfer that will be started.
 *  @pre        1st Transfer of the channel must always be re-configured via
 *              direct configure APIs following a (linked) ECPY_directStartEdma
 *              i.e. when the number of the most recent start > 1) or when the
 *              1st transfer of the previous start was a 3D transfer
 *              (numFrames > 1).
 *
 *  @remarks    Most recent ECPY_directConfigure(), ECPY_directConfigure16 and
 *              ECPY_directConfigure32 settings will always be in effect for
 *              each transfer w/transferNo > 1.
 *              Transfer settings of transferNo=1 will be only preserved if the
 *              most recent ECPY_directStartEdma resulted in a single
 *              (non-linked) transfer with  numFrames == 1.
 *
 *  @pre        When the number of transfers assigned to the channel are > 1,
 *              this function will submit a set of linked EDMA transfers,
 *              ordered by the transferNo's of the channel.
 *              The final transfer of the linked set will be the transfer
 *              indicated by the most recent ECPY_directSetFinal() call.
 *              If no ECPY_setFinal has been previously called, then
 *              all transfers assigned to the channel will be linked together.
 *
 *  @remarks    Both an inlined version and a non-inlined version of this
 *              function are supported. To use the inlined version, add the
 *              line \#define ECPY_DIRECTSTARTEDMA_INLINE or
 *              \#define ECPY_INLINE_ALL to the source file where this
 *              function is used. The \#define must go above the line,
 *              \#include <ecpy.h>. By default, this function will not be
 *              inlined. Another alternative is to define the macro in the
 *              build option of the file or of the project file.
 */
#if defined(ECPY_DIRECTSTARTEDMA_INLINE) || defined(ECPY_INLINE_ALL)
#include <ti/sdo/fc/ecpy/ecpy_directstartedma.h>
#else
Void ECPY_directStartEdma(ECPY_Handle handle);
#endif

/**
 *  @brief      ECPY_directStartQdma has not been implemented.
 */
Void ECPY_directStartQdma(ECPY_Handle handle);


/**
 *  @brief      Wait for all data transfers on a logical channel to complete.
 *
 *
 *  @param[in]  handle  ECPY channel handle.
 *
 *  @pre        Valid channel handle
 *  @pre        Channel must be in 'active' state.
 *  @pre        ECPY_wait can be called back to back or without having submitted
 *              transfers to the channel. For the case there is no pending
 *              transfer on the channel it will return immediately.
 *
 *  @post       ECPY_wait will reset channel handle's transferPending flag to 0
 *
 *  @remarks    This function will not return until all the previously submitted
 *              EDMA transfers on the channel have completed.
 *
 *  @remarks    Both an inlined version and a non-inlined version of this
 *              function are supported. To use the inlined version, add the
 *              line \#define ECPY_WAIT_INLINE or
 *              \#define ECPY_INLINE_ALL to the source file where this
 *              function is used. The \#define must go above the line,
 *              \#include <ecpy.h>. By default, this function will not be
 *              inlined. Another alternative is to define the macro in the
 *              build option of the file or of the project file.
 */
#if defined(ECPY_WAIT_INLINE) || defined(ECPY_INLINE_ALL)
#include <ti/sdo/fc/ecpy/ecpy_wait.h>
#else
Void ECPY_wait(ECPY_Handle handle);
#endif

/**
 *  @brief      Wait for all EDMA data transfers submitted to the logical
 *              channel via ECPY_directStartEdma to complete.
 *
 *
 *  @param[in]  handle  ECPY channel handle.
 *
 *  @pre        Valid channel handle
 *  @pre        Channel must be in 'active' state.
 *
 *  @pre        ECPY_directWait requires that a transfer has been submitted
 *              to the channel using ECPY_directStartEdma. Otherwise it will
 *              block indefinitely.
 *
 *  @pre        ECPY_directWait can not be called back to back or without
 *              having started EDMA transfers on the channel.
 *
 *  @remarks    ECPY_directWait will not maintain channel handle's
 *              transferPending state.
 *
 *  @remarks    This function will not return until all the data
 *              transfers on the given channel have completed.
 *
 *  @remarks    Both an inlined version and a non-inlined version of this
 *              function are supported. To use the inlined version, add the
 *              line \#define ECPY_DIRECTWAIT_INLINE or
 *              \#define ECPY_INLINE_ALL to the source file where this
 *              function is used. The \#define must go above the line,
 *              \#include <ecpy.h>. By default, this function will not be
 *              inlined. Another alternative is to define the macro in the
 *              build option of the file or of the project file.
 */
#if defined(ECPY_DIRECTWAIT_INLINE) || defined(ECPY_INLINE_ALL)
#include <ti/sdo/fc/ecpy/ecpy_directwait.h>
#else
Void ECPY_directWait(ECPY_Handle handle);
#endif

/**
 *  @brief      Activate the given channel.
 *
 *  @param[in]  handle  ECPY channel handle.
 *
 *  @pre        @c handle must be a valid channel handle.
 *
 *  @pre        Algorithm instance must be in "active" state using IALG
 *              interface.
 *
 *  @pre        @c handle must be a valid handle obtained by ECPY_createHandle.
 *
 *  @post       Channel is in 'active' state, any ECPY APIs can be called
 *              using this handle.
 */
Void ECPY_activate(ECPY_Handle handle);

/**
 *  @brief      Create an ECPY Handle using the supplied IRES_EDMA3CHAN handle
 *
 *  @param[in]  handle      IRES_EDMA3CHAN channel handle.
 *  @param[in]  alg         IALG handle.
 *
 *  @pre        @c handle must be a valid handle.
 *
 *  @post       Early Completion Mode is enabled for all Intermediate Transfers.
 *              Early Completion Transfer completion mode can be disabled if
 *              needed via the ECPY_setEarlyCompletionMode() API.
 *
 */
ECPY_Handle ECPY_createHandle(IRES_EDMA3CHAN2_Handle handle, IALG_Handle alg);

/**
 *  @brief      Delete ECPY_Handle
 *
 *  @param[in]  handle      ECPY channel handle.
 *
 *  @pre        @c handle must be a valid handle obtained by ECPY_createHandle.
 *
 */
Void ECPY_deleteHandle(ECPY_Handle handle);

/**
 *  @brief      Deactivates the given channel.
 *
 *  @param[in]  handle    ECPY  channel handle.
 *
 *  @pre        @c handle must be a valid channel handle.
 *
 *  @pre        Channel must be in 'active' state.
 *
 *  @pre        Algorithm instance must be in 'active' state using IALG
 *              interface
 *
 *  @post       Channel is in 'deactivated' state.
 */
Void ECPY_deactivate(ECPY_Handle handle);

/**
 *  @brief      Setting the TCCMODE (Early or Normal) affects only the
 *              'intermediate transfers' of the linked transfers submitted
 *              using this channel.
 *              All subsequent direct and non-direct ECPY_configure* calls
 *              using this ecpyHandle will program the OPT's TCCMODE to select
 *              Early or Normal completion mode based on the 'enabled' argument.
 *
 *              Selecting the Early Completion mode may lead to performance
 *              improvements by increasing the EDMA throughput of linked
 *              transfers by submitting each transfer request from the EDMA
 *              Channel Controller to the Transfer Controller without waiting
 *              for the completion of the previous transfer from the Transfer
 *              Controller.
 *
 *  @param[in]  handle  ECPY channel handle.
 *  @param[in]  enabled 1/TRUE  to set TCCMODE to 1 (Early Completion)
 *                      0/FALSE to set TCCMODE to 1 (Normal Completion)
 *
 *  @post       Channel Intermediate Transfer Completion Mode is set according
 *              to the 'enabled' parameter. The selected mode applies to all
 *              subsequent configure operations of the intermediate transfers.
 */
Void ECPY_setEarlyCompletionMode(ECPY_Handle handle, short enabled);

/**
 *  @brief              Initialize the ECPY module.  Called by framework.
 */
Void ECPY_init(Void);

/**
 *  @brief              Finalization of the ECPY module.
 */
Void ECPY_exit(Void);

/**
 *  @brief      Memory allocation function signature for module configuration.
 */
typedef Bool (ECPY_PersistentAllocFxn)(IALG_MemRec *memTab, Int numRecs);

/**
 *  @brief      Memory deallocation function signature for module configuration.
 */
typedef Void (ECPY_PersistentFreeFxn)(IALG_MemRec *memTab, Int numRecs);

/**
 *  @brief      Scratch Memory allocation function for all shared scratch
 *              ECPY handle state.
 */
typedef Bool (ECPY_ScratchAllocFxn)(IALG_Handle alg, Int scratchId,
                                    IALG_MemRec *memTab, Int numRecs);
/**
 *  @brief      Scratch Memory free function for all scratch allocated
 *              memory in ECPY Handle.
 */
typedef Void (ECPY_ScratchFreeFxn)(Int mutexId, Void *addr, UInt size);

/**
 *  @brief      Function, when supplied, returns the scratchId associated
 *              with the algorithm instance whose handle is passed.
 */
typedef Int  (ECPY_getScratchIdFxn)(IALG_Handle alg);


/**
 *  @brief      The module configuration structure for ECPY.
 *              It is set at design time by the system integrator to register
 *              customize memory allocation/free implementations.
 *
 *  @remarks    Typically, system integrators configure these settings using
 *              XDC config scripts.  System integrators that use that method
 *              of configuration can ignore this structure definition.  It's
 *              auto-generated during the config step by the XDC Tools.
 */
typedef struct ECPY_CfgParams {

    /**
     *  @brief      Memory allocation function for all ECPY memory requirements
     */
    ECPY_PersistentAllocFxn * allocFxn;

    /**
     *  @brief      Memory free function for all ECPY memory requirements
     */
    ECPY_PersistentFreeFxn * freeFxn;

    /**
     *  @brief      Scratch Memory allocation function for all shared scratch
     *              ECPY handle state.
     */
    ECPY_ScratchAllocFxn * scratchAllocFxn;

    /**
     *  @brief      Scratch Memory free function for all scratch allocated
     *              memory in ECPY Handle.
     */
    ECPY_ScratchFreeFxn * scratchFreeFxn;

    /**
     *  @brief      Function, when supplied, returns the scratchId associated
     *              with the algorithm instance whose handle is passed.
     */
    ECPY_getScratchIdFxn *getScratchIdFxn;
} ECPY_CfgParams;

/**
 *  @brief      Initialization parameters for the ECPY module
 */
extern __FAR__ ECPY_CfgParams ECPY_CFG_PARAMS;

/*@}*/

#ifdef __cplusplus
}
#endif /* extern "C" */


#endif /* ti_sdo_fc_ecpy_ECPY_ */
