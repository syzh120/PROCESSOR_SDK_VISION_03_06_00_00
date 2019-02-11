/*
 * Copyright (c) 2006-2012, Texas Instruments Incorporated
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
 *  @file       ti/xdais/dm/ividanalytics.h
 *
 *  @brief      This header defines all types, constants, and functions
 *              shared by all implementations of the video analytics
 *              algorithms.
 */
/**
 *  @defgroup   ti_xdais_dm_IVIDANALYTICS  IVIDANALYTICS - XDM Beta Video Analytics Interface
 *
 *  This is the XDM Beta Video Analytics Interface.
 */

#ifndef ti_xdais_dm_IVIDANALYTICS_
#define ti_xdais_dm_IVIDANALYTICS_

#include <ti/xdais/ialg.h>
#include <ti/xdais/xdas.h>
#include "xdm.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_xdais_dm_IVIDANALYTICS */
/*@{*/

#define IVIDANALYTICS_EOK       XDM_EOK        /**< @copydoc XDM_EOK */
#define IVIDANALYTICS_EFAIL     XDM_EFAIL      /**< @copydoc XDM_EFAIL */
#define IVIDANALYTICS_EUNSUPPORTED XDM_EUNSUPPORTED /**< @copydoc XDM_EUNSUPPORTED */

/* IVIDANALYTICS-specific control commands  */

/**
 *  @brief      Set a new rule.
 */
#define IVIDANALYTICS_SETRULE   	XDM_CLASSCMDBASE

/**
 *  @brief      Clear a rule.
 */
#define IVIDANALYTICS_CLEARRULE 	XDM_CLASSCMDBASE + 1

/**
 *  @brief       Maximum targets that can be detected per process() call.
 *
 *  @todo	This could be 64 if needed.  Need to understand the size of
 *              structs that use this and whether they're "too big".
 */
#define IVIDANALYTICS_MAXTARGETS 128

/**
 *  @brief      Maximum number of events that can be detected per process() call.
 *
 *  @todo	Need to understand the size of
 *              structs that use this and whether they're "too big".
 */
#define IVIDANALYTICS_MAXEVENTS 128
/**
 *  @brief      Access modes used to declare how the algorithm accessed buffers.
 *
 *  @remarks	The IVIDANALYTICS interface reserves bits 0-15.  Bits
 *              16-31 are available to the user.
 *
 *  @sa		IVIDANALYTICS_Mask::enableMask
 */
typedef enum {
    IVIDANALYTICS_MOTIONDETECT = 0,            /**< Motion detection, bit 0 */
    IVIDANALYTICS_OBJECTTRACKING = 1,          /**< Object tracking, bit 1 */

    IVIDANALYTICS_USERBASE = 16                /**< User supplied analysis
                                                *   begins at bit 16.
						*/
} IVIDANALYTICS_AnalysisMask;


/**
 *  @brief      Access modes used to declare how the algorithm accessed buffers.
 *
 *  @remarks	The IVIDANALYTICS interface reserves bits 0-15.  Bits
 *              16-31 are available to the user.
 *
 *  @sa		IVIDANALYTICS_DynamicParams::grid
 */
typedef struct IVIDANALYTICS_Grid {   /* a grid/block is put on top of a video frame. Some blocks are MD-enabled, the others are MD-disabled... */
    XDAS_Int32 blockHeight;              /**< Height of a block */
    XDAS_Int32 blockWidth;               /**< Width of a block */
    XDAS_Int32 numBlockHorizontal;       /**< Number of blocks per row */
    XDAS_Int32 numBlockVertical;         /**< Number of blocks per column */

    XDM1_SingleBufDesc enableMaskArray;  /**< Buffer containing an array
                                          *   representing the type of analysis to enable on each block
                                          *   in the grid.
					  *
					  *   @remarks	The array will be
					  *             numBlockHorizontal *
					  *             numBlockVertical.
					  *
					  *   @sa  IVIDANALYTICS_AnalysisMask
					  */
} IVIDANALYTICS_Grid;

/**
 *  @brief      Types of objects
 *
 *  @remarks	The IVIDANALYTICS interface reserves types 0-255.
 *              User-defined objects can be defined from 256 and larger.
 */
typedef enum {
    IVIDANALYTICS_OBJECTTYPE_VEHICLE = 0,      /**< Object is a vehicle */
    IVIDANALYTICS_OBJECTTYPE_HUMAN = 1,        /**< Object is a human */

    IVIDANALYTICS_OBJECTTYPE_USERBASE = 256    /**< User supplied objects
                                                *   begins at 256.
						*/
} IVIDANALYTICS_ObjectType;

/**
 *  @brief      Types of objects
 *
 *  @remarks	The IVIDANALYTICS interface reserves types 0-255.
 *              User-defined actions can be defined from 256 and larger.
 */
typedef enum {
    IVIDANALYTICS_ACTIONTYPE_LOITER = 0,       /**< Object is loitering */
    IVIDANALYTICS_ACTIONTYPE_ENTER = 1,        /**< Object enters */
    IVIDANALYTICS_ACTIONTYPE_EXIT = 2,         /**< Object exits */
    IVIDANALYTICS_ACTIONTYPE_APPEAR = 3,       /**< Object appears */
    IVIDANALYTICS_ACTIONTYPE_DISAPPEAR = 4,    /**< Object appears */
    IVIDANALYTICS_ACTIONTYPE_CROSSL2R = 5,     /**< Object crosses left to right */
    IVIDANALYTICS_ACTIONTYPE_CROSSR2L = 6,     /**< Object crosses right to left */
    IVIDANALYTICS_ACTIONTYPE_CROSSU2D = 7,     /**< Object crosses up to down */
    IVIDANALYTICS_ACTIONTYPE_CROSSD2U = 8,     /**< Object crosses down to up */

    IVIDANALYTICS_ACTIONTYPE_USERBASE = 256    /**< User supplied objects
                                                *   begins at 256.
						*/
} IVIDANALYTICS_ActionType;


/**
 *  @brief     Analytics rule.
 */
typedef struct IVIDANALYTICS_Rule{
    XDAS_Int32 size;            /**< @sizeField  */
    XDAS_Int32 id;   		/**< id associated with this rule. */

    IVIDANALYTICS_ObjectType objectType;  /**< Type of the object associated
                                           *   with this rule.
					   */
    IVIDANALYTICS_ActionType actionType;  /**< Type of action associated
                                           *   with this rule.
					   */
} IVIDANALYTICS_Rule;


/**
 *  @brief      This must be the first field of all IVIDANALYTICS
 *              instance objects.
 */
typedef struct IVIDANALYTICS_Obj {
    struct IVIDANALYTICS_Fxns *fxns;
} IVIDANALYTICS_Obj;


/**
 *  @brief      Opaque handle to an IVIDANALYTICS objects.
 */
typedef struct IVIDANALYTICS_Obj  *IVIDANALYTICS_Handle;


/**
 *  @brief      View state of the analytics engine.
 *
 *  @enumWarning
 *
 *  @todo       Need to further review and define.  Probably need hooks for
 *              user-defined states, in addition to some pre-defined ones.
 *
 *  @sa IVIDANALYTICS_OutArgs::viewState
 *  @sa IVIDANALYTICS_Status::viewState
 */
typedef enum {
    IVIDANALYTICS_VIEWSTATE_BAD = 0,
    IVIDANALYTICS_VIEWSTATE_GOOD = 1
} IVIDANALYTICS_ViewState;


/**
 *  @brief      Defines the creation time parameters for
 *              all IVIDANALYTICS instance objects.
 *
 *  @extensibleStruct
 */
typedef struct IVIDANALYTICS_Params {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 maxHeight;       /**< Maximum video height in pixels. */
    XDAS_Int32 maxWidth;        /**< Maximum video width in pixels. */
    XDAS_Int32 maxFrameRate;    /**< Maximum frame rate in fps * 1000.
                                 *   For example, if max frame rate is 30
                                 *   frames per second, set this field
                                 *   to 30000.
                                 */
    XDAS_Int32 dataEndianness;  /**< Endianness of output data.
                                 *
                                 *   @sa    XDM_DataFormat
                                 */
    XDAS_Int32 inputChromaFormat;/**< Chroma format for the input buffer.
                                 *
                                 *   @sa XDM_ChromaFormat
                                 */
    XDAS_Int32 maxRules;         /**<  Maximum number of rules allowed. */
}IVIDANALYTICS_Params;


/**
 *  @brief      This structure defines the algorithm parameters that can be
 *              modified after creation via control() calls.
 *
 *  @remarks    It is not necessary that a given implementation support all
 *              dynamic parameters to be configurable at run time.  If a
 *              particular algorithm does not support run-time updates to
 *              a parameter that the application is attempting to change
 *              at runtime, it may indicate this as an error.
 *
 *  @extensibleStruct
 *
 *  @sa         IVIDANALYTICS_Fxns::control()
 */
typedef struct IVIDANALYTICS_DynamicParams {
    XDAS_Int32 size;               /**< @sizeField */
    IVIDANALYTICS_Grid *grid;      /**< New overlay grid with analytics enable mask */
    XDM_Date      date;            /**< Set the current time. */

    /* Note, we've removed height & width - no way to change size at runtime - need to recreate the alg instance */

    IVIDANALYTICS_Rule rule;    /**< Rule associated with this command
                                 *   (if applicable).
				 */
} IVIDANALYTICS_DynamicParams;


/**
 *  @brief      Defines the input arguments for all IVIDANALYTICS instance
 *              process function.
 *
 *  @extensibleStruct
 *
 *  @sa         IVIDANALYTICS_Fxns::process()
 */
typedef struct IVIDANALYTICS_InArgs {
    XDAS_Int32    size;            /**< @sizeField */
    XDM_Date      date;            /**< Set the current time. */
}IVIDANALYTICS_InArgs;


/**
 *  @brief      Defines instance status parameters.
 *
 *  @extensibleStruct
 *
 *  @sa         IVIDANALYTICS_Fxns::control()
 */
typedef struct IVIDANALYTICS_Status {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 extendedError;   /**< @extendedErrorField */
    XDM1_BufDesc data;          /**< Buffer descriptors for data passing.
                                 *
                                 *   @remarks   If this field is not used,
                                 *              the application <b>must</b>
                                 *              set @c data.numBufs to 0.
                                 *
                                 *   @remarks   These buffers can be used as
                                 *              either input or output,
                                 *              depending on the command.
                                 *
                                 *   @remarks   The buffers will be provided
                                 *              by the application, and
                                 *              returned to the application
                                 *              upon return of the
                                 *              IVIDANALYTICS_Fxns.control()
                                 *              call.  The algorithm must
                                 *              not retain a pointer to this
                                 *              data.
                                 *
                                 *   @sa    #XDM_GETVERSION
                                 */
    XDM_AlgBufInfo bufInfo;     /**< Input and output buffer information.
                                 *
                                 *   @remarks   This field provides the
                                 *              application with the algorithm's
                                 *              buffer requirements.  The
                                 *              requirements may vary depending
                                 *              on the current configuration
                                 *              of the algorithm instance.
                                 *
                                 *   @sa        IVIDANALYTICS_Params
                                 *   @sa        XDM_AlgBufInfo
                                 *   @sa        IVIDANALYTICS_Fxns::control()
                                 */
    XDAS_Int32 viewState;       /**< @copydoc IVIDANALYTICS_ViewState
                                 *
                                 *   @sa IVIDANALYTICS_ViewState
                                 */
} IVIDANALYTICS_Status;


/**
 *  @brief      Defines the run time output arguments for
 *              all IVIDANALYTICS instance objects.
 *
 *  @extensibleStruct
 *
 *  @sa         IVIDDEC1_Fxns::process()
 */
typedef struct IVIDANALYTICS_OutArgs {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 numTargets;      /**< Number of targets detected */
    XDM_Rect targets[IVIDANALYTICS_MAXTARGETS]; /**< target locations.
                                 *
				 *   @remarks	If @c numTargets is zero,
				 *              the values in this array are
				 *              undefined.
				 */

    XDAS_Int32 numEvents;      /**< Number of events detected */

    XDAS_Int32 eventId[IVIDANALYTICS_MAXEVENTS];  /**< Zero-terminated array
                                 *  containing the ids of rules fired
                                 *  during the process() call.
				 *
				 *   @remarks	If @c numEvents is zero,
				 *              the values in this array are
				 *              undefined.
				 */

    XDAS_Int32 extendedError;   /**< @extendedErrorField */
    XDM_Date      date;            /**< Current time. */
} IVIDANALYTICS_OutArgs;


/**
 *  @brief      Defines the control commands for the IVIDANALYTICS module.
 *
 *  @remarks    This ID can be extended in IMOD interface for
 *              additional controls.
 *
 *  @sa         XDM_CmdId
 *
 *  @sa         IVIDANALYTICS_Fxns::control()
 */
typedef  IALG_Cmd IVIDANALYTICS_Cmd;


/**
 *  @brief      Defines all of the operations on IVIDANALYTICS objects.
 */
typedef struct IVIDANALYTICS_Fxns {
    IALG_Fxns   ialg;             /**< XDAIS algorithm interface.
                                   *
                                   *   @sa      IALG_Fxns
                                   */

/**
 *  @brief      Basic video decoding call.
 *
 *  @param[in]  handle          Handle to an algorithm instance.
 *  @param[in,out] inBufs       Input buffer descriptors.
 *  @param[in,out] outBufs      Output buffer descriptors.  The algorithm
 *                              may modify the output buffer pointers.
 *  @param[in]  inArgs          Input arguments.  This is a required
 *                              parameter.
 *  @param[out] outArgs         Ouput results.  This is a required parameter.
 *
 *  @remarks    process() is a blocking call.  When process() returns, the
 *              algorithm's processing is complete.
 *
 *  @pre        @c inBufs->numBufs will indicate the total number of input
 *              buffers supplied for input frame.
 *
 *  @pre        @c inArgs must not be NULL, and must point to a valid
 *              IVIDANALYTICS_InArgs structure.
 *
 *  @pre        @c outArgs must not be NULL, and must point to a valid
 *              IVIDANALYTICS_OutArgs structure.
 *
 *  @pre        @c inBufs must not be NULL, and must point to a valid
 *              XDM1_BufDesc structure.
 *
 *  @pre        @c inBufs->descs[0].buf must not be NULL, and must point to
 *              a valid buffer of data that is at least
 *              @c inBufs->descs[0].bufSize bytes in length.
 *
 *  @pre        @c outBufs must not be NULL, and must point to a valid
 *              XDM1_BufDesc structure.
 *
 *  @pre        @c outBufs->descs[0].buf must not be NULL, and must point to
 *              a valid buffer of data that is at least
 *              @c outBufs->descs[0].bufSize bytes in length.
 *
 *  @pre        The buffers in @c inBufs and @c outBufs are physically
 *              contiguous and owned by the calling application.
 *
 *  @post       The algorithm <b>must not</b> modify the contents of @c inArgs.
 *
 *  @post       The algorithm <b>must not</b> modify the contents of
 *              @c inBufs, with the exception of @c inBufs.bufDesc[].accessMask.
 *              That is, the data and buffers pointed to by these parameters
 *              must be treated as read-only.
 *
 *  @post       The algorithm <b>must</b> modify the contents of
 *              @c inBufs->descs[].accessMask and appropriately indicate the
 *              mode in which each of the buffers in @c inBufs were read.
 *              For example, if the algorithm only read from
 *              @c inBufs.descs[0].buf using the algorithm processor, it
 *              could utilize #XDM_SETACCESSMODE_READ to update the appropriate
 *              @c accessMask fields.
 *              The application <i>may</i> utilize these
 *              returned values to appropriately manage cache.
 *
 *  @post       The buffers in @c inBufs and @c outBufs are owned by the
 *              calling application.
 *
 *  @retval     IVIDANALYTICS_EOK       @copydoc IVIDANALYTICS_EOK
 *  @retval     IVIDANALYTICS_EFAIL     @copydoc IVIDANALYTICS_EFAIL
 *                                      See IVIDANALYTICS_Status#extendedError
 *                                      for more detailed further error
 *                                      conditions.
 *  @retval     IVIDANALYTICS_EUNSUPPORTED   @copydoc IVIDANALYTICS_EUNSUPPORTED
 */
    XDAS_Int32 (*process)(IVIDANALYTICS_Handle handle, XDM1_BufDesc *inBufs,
        XDM1_BufDesc *outBufs, IVIDANALYTICS_InArgs *inArgs,
        IVIDANALYTICS_OutArgs *outArgs);


/**
 *  @brief      Control behavior of an algorithm.
 *
 *  @param[in]  handle          Handle to an algorithm instance.
 *  @param[in]  id              Command id.  See #XDM_CmdId.
 *  @param[in]  params          Dynamic parameters.  This is a required
 *                              parameter.
 *  @param[out] status          Output results.  This is a required parameter.
 *
 *  @pre        @c handle must be a valid algorithm instance handle.
 *
 *  @pre        @c params must not be NULL, and must point to a valid
 *              IVIDANALYTICS_DynamicParams structure.
 *
 *  @pre        @c status must not be NULL, and must point to a valid
 *              IVIDANALYTICS_Status structure.
 *
 *  @pre        If a buffer is provided in the @c status->data field,
 *              it must be physically contiguous and owned by the calling
 *              application.
 *
 *  @post       The algorithm <b>must not</b> modify the contents of @c params.
 *              That is, the data pointed to by this parameter must be
 *              treated as read-only.
 *
 *  @post       If a buffer was provided in the @c status->data field,
 *              it is owned by the calling application.
 *
 *  @retval     IVIDANALYTICS_EOK       @copydoc IVIDANALYTICS_EOK
 *  @retval     IVIDANALYTICS_EFAIL     @copydoc IVIDANALYTICS_EFAIL
 *                                      See IVIDANALYTICS_Status#extendedError
 *                                      for more detailed further error
 *                                      conditions.
 *  @retval     IVIDANALYTICS_EUNSUPPORTED   @copydoc IVIDANALYTICS_EUNSUPPORTED
 */
    XDAS_Int32   (*control)(IVIDANALYTICS_Handle handle, IVIDANALYTICS_Cmd id,
            IVIDANALYTICS_DynamicParams *params, IVIDANALYTICS_Status *status);

} IVIDANALYTICS_Fxns;


/*@}*/

#ifdef __cplusplus
}
#endif

#endif
