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



#ifndef DATA_VIS_H_
#define DATA_VIS_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */

#include <include/link_api/system.h>
#include <src/include/draw2d.h>

/*******************************************************************************
 *  Defines's
 *******************************************************************************
 */

#define DATA_VIS_DATA_BW_INVALID    (UInt32)(0xFFFFFFFFu)

/**
 *******************************************************************************
 * \brief Max number of modules to group together in one graph
 *******************************************************************************
 */
#define DATA_VIS_DATA_BW_GROUP_MAX  (16)

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */

/*******************************************************************************
 *  \brief Represents one sample point of Data BW
 *
 *         Stores average Data BW in MB/s for a sample dureation
 *         specfied in DataVis_DataBwPrm
 *******************************************************************************
 */
typedef struct {

    UInt64 timestamp;
    /**< In units of usecs */

    UInt32 dataBw[UTILS_STATCOLL_DATA_BW_MOD_MAX];
    /**< if value is DATA_VIS_DATA_BW_INVALID, value should be ignored
      *  else value is units of MB/s
      */
} DataVis_DataBwElement;

/*******************************************************************************
 *  \brief Create time arguments
 *
 *         Specifies max limits which are used for resource allocation
 *         These parameters cannot be changed dynamically.
 *         When parameters are updated dynamically they should not exceed
 *         values set in this structure
 *******************************************************************************
 */
typedef struct {

    UInt32 maxWinWidth;
    /**< Max possible width of drawing window */

    UInt32 maxWinHeight;
    /**< Max possible height of drawing window */

    UInt32 maxNumberOfSamples;
    /**< Max possible number of samples */

} DataVis_CreatePrm;

/*******************************************************************************
 *  \brief Drawing properties to use for visualization of a data element
 *******************************************************************************
 */
typedef struct {

    UInt32 numModules;

    Utils_StatCollDataBwModule moduleId[DATA_VIS_DATA_BW_GROUP_MAX];
    /**< ID of module */

    char dataBwModText[16];
    /**< Text to display for this data BW module */

    UInt32 color;
    /**< Color to use for drawing this data BW module graph
     *   Color format: RGB565
     */

} DataVis_DataBwModDrawProp;

/*******************************************************************************
 *  \brief Run-time arguments to control data visualization function
 *
 *         These parameters can be changed while data visualization is
 *         running
 *******************************************************************************
 */
typedef struct {

    UInt32 sampleDuration;
    /**< In units of msecs */
    UInt32 numOfSamples;
    /**<  Must be <= value specified in DataVis_CreatePrm */
    UInt32 drawRefreshRate;
    /**< In units of msecs */
    float yScaleMin;
    /**< just a number used to annotate the scale from min to max */
    float yScaleMax;
    /**< just a number used to annotate the scale from min to max */
    float yScaleMajorInc;
    /**< units by which to increment Scale */
    float yScaleMinorInc;
    /**< units by which to increment Scale */
    float xScaleMin;
    /**< just a number used to annotate the scale from min to max */
    float xScaleMax;
    /**< just a number used to annotate the scale from min to max */
    float xScaleMajorInc;
    /**< units by which to increment Scale */
    float xScaleMinorInc;
    /**< units by which to increment Scale */
    char  xScaleText[16];
    /**< Text to draw for scale in X-direction */
    char  yScaleText[16];
    /**< Text to draw for scale in Y-direction */
    UInt32 numDataBwMod;
    /**< Number of data BW modules that will be drawn */
    DataVis_DataBwModDrawProp dataBwModProp[UTILS_STATCOLL_DATA_BW_MOD_MAX];
    /**< Properties of data Bw module that would be used for drawing */
    UInt32 winWidth;
    /**< Must be <= value specified in DataVis_CreatePrm */
    UInt32 winHeight;
    /**< Must be <= value specified in DataVis_CreatePrm */
    UInt32 winPosX;
    /**< Position on window in display */
    UInt32 winPosY;
    /**< Position on window in display */
    Draw2D_Handle *pDraw2DHandle;
    /**< Handle of created and initialized drawing surface */
} DataVis_DataBwPrm;

/*******************************************************************************
 *  Function's
 *******************************************************************************
 */

/*******************************************************************************
 *  \brief Set default parameters
 *******************************************************************************
 */
Void DataVis_CreatePrm_Init(DataVis_CreatePrm *pPrm);

/*******************************************************************************
 *  \brief Set default parameters
 *******************************************************************************
 */
Void DataVis_DataBwPrm_Init(DataVis_DataBwPrm *pPrm);

/*******************************************************************************
 *  \brief Create resources for Data visualization
 *
 *         Called once during use-case startup
 *******************************************************************************
 */
Int32 DataVis_create(DataVis_CreatePrm *pPrm);

/*******************************************************************************
 *  \brief Free's resources allocated during create
 *
 *         Called once during use-case shutdown
 *******************************************************************************
 */
Int32 DataVis_delete();

/*******************************************************************************
 *  \brief Change drawing related parameters
 *
 *         Can be called multiple times while use-case is running
 *         Effect takes place, next time DataVis_drawDataBw() is called
 *         or next time when data collection is done
 *
 *         'resetDataCollector' is used to reset data collector thread
 *         'resetDraw' is used to reset drawing function
 *
 *******************************************************************************
 */
Int32 DataVis_setDataBwPrm(DataVis_DataBwPrm *pPrm, Bool resetDataCollector, Bool resetDraw);

/*******************************************************************************
 *  \brief Check if updated parameters should be used for drawing
 *
 *         Called DataVis_drawDataBw() to reset itself based on new parameters
 *         'pPrm' contains updated value only when return value is true
 *
 *******************************************************************************
 */
Bool DataVis_isPrmUpdatedForDataBwDraw(DataVis_DataBwPrm *pPrm);

/*******************************************************************************
 *  \brief Check if updated parameters should be used by data collection thread
 *
 *         Called data collection thread to reset itself based on new parameters
 *         'pPrm' contains updated value only when return value is true
 *
 *******************************************************************************
 */
Bool DataVis_isPrmUpdatedForDataBWCollector(DataVis_DataBwPrm *pPrm);

/*******************************************************************************
 *  \brief Draw Data BW visualization to screen
 *
 *         Should be called periodically, say once every 10ms
 *         by the drawing thread.
 *         Actual drawing takes a 'referesh rate' specified during
 *         DataVis_setDrawDataBwPrm()
 *
 *******************************************************************************
 */
Int32 DataVis_drawDataBw();

/*******************************************************************************
 *  \brief Write one element of data BW collected to shared memory
 *
 *         Called by the data collection thread.
 *
 *         API has no effect if DataVis_create() and DataVis_setDataBwPrm()
 *         are not called
 *
 *         If shared memory is full, the API internally reads one element to make
 *         space for new element
 *
 *******************************************************************************
 */
Int32 DataVis_writeDataBwData(DataVis_DataBwElement *pElem);

/*******************************************************************************
 *  \brief Read element's of data BW collected in shared memory for drawing
 *         purpose
 *
 *         Called by the DataVis_drawDataBw() internally
 *
 *******************************************************************************
 */
Int32 DataVis_readDataBwData(DataVis_DataBwElement *pElem, UInt32 *numElementsRead, UInt32 maxElementsToRead);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */


