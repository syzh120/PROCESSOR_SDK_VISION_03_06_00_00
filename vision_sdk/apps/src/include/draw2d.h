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

/**
 *******************************************************************************
 *
 * \defgroup DRAW_2D_API Font and 2D Drawing API
 *
 * \brief  This module has the interface for drawing fonts and 2D primitives
 *         like lines
 *
 *         NOTE: This is limited demo API and not a comprehensive 2D drawing
 *               library
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file draw2d.h
 *
 * \brief Font and 2D Drawing API
 *
 * \version 0.0 (Oct 2013) : [KC] First version
 *
 *******************************************************************************
 */

#ifndef _DRAW_2D_H_
#define _DRAW_2D_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <include/link_api/system.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */


/**
 *******************************************************************************
 *
 * \brief Macro that converts RGB888 to RGB565
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */

#define RGB888_TO_RGB565(r,g,b)     ((((UInt32)(r>>3) & 0x1F) << 11) | (((UInt32)(g>>2) & 0x3F) << 5) | (((UInt32)(b>>3) & 0x1F)))
#define RGB888_TO_BGRA444(r,g,b,a)  ((((UInt32)(r>>4) & 0xF) << 0) | (((UInt32)(g>>4) & 0xF) << 4) | (((UInt32)(b>>4) & 0xF)<<8)| (((UInt32)(a>>4) & 0xF)<<12))

#define DRAW2D_TRANSPARENT_COLOR            (0x0000)
#define DRAW2D_TRANSPARENT_COLOR_FORMAT     (SYSTEM_DF_BGR16_565)

#define DRAW2D_BMP_IDX_TI_LOGO              (0) /* with transperency color
                                                 * as background */
#define DRAW2D_BMP_IDX_TI_LOGO_1            (1) /* with Black background */
#define DRAW2D_BMP_IDX_SURROUND_VIEW        (2)
#define DRAW2D_BMP_IDX_FRONT_CAM_ANALYTICS  (3)
#define DRAW2D_BMP_IDX_OPTFLOW_LUT_0        (4)
#define DRAW2D_BMP_IDX_OPTFLOW_LUT_1        (5)
#define DRAW2D_BMP_IDX_OPTFLOW_LUT_2        (6)
#define DRAW2D_BMP_IDX_JEEP_IMAGE           (7)
#define DRAW2D_BMP_IDX_STEREO_COLORBAR_20x720 (8)
#define DRAW2D_BMP_IDX_SURROUND_VIEW_SMALL  (10)
#define DRAW2D_BMP_IDX_TI_LOGO_SMALL        (11)
#define DRAW2D_BMP_IDX_JEEP_220_X_330       (12)
#define DRAW2D_BMP_IDX_STEREO_COLORBAR_35x450 (13)
#define DRAW2D_BMP_IDX_JEEP_IMAGE_TRUESCALE (14) /*jeep image with same scale (width/length) as toy jeep*/
#define DRAW2D_BMP_IDX_TL_RED               (15)
#define DRAW2D_BMP_IDX_TL_GREEN             (16)
#define DRAW2D_BMP_IDX_3DPERCEPTION_SFM_LOGO  (17)
#define DRAW2D_BMP_IDX_TDA2X                (18)
#define DRAW2D_BMP_IDX_TDA3X_SUV_348x480    (21)
#define DRAW2D_BMP_FORD_REARVIEW_CAMERA_LEFT          (22)
#define DRAW2D_BMP_FORD_REARVIEW_CAMERA_RIGHT         (23)
#define DRAW2D_BMP_FORD_TOPDOWN_REARVIEW_CAMERA_LEFT  (24)
#define DRAW2D_BMP_FORD_TOPDOWN_REARVIEW_CAMERA_RIGHT (25)
#define DRAW2D_BMP_IDX_REAR_VIEW_PANORAMA   (26)
#define DRAW2D_BMP_IDX_CAR_IMAGE            (27)
#define DRAW2D_BMP_IDX_CAR2_IMAGE           (28)
#define DRAW2D_BMP_IDX_RSVP_CAR_IMAGE       (29)
#define DRAW2D_BMP_IDX_TDA3X                (32)

/*
 *******************************************************************************
 *
 *  \brief  Font property
 *
 *******************************************************************************
 */
typedef struct {

    UInt32 width;
    /**< Width of a character of font in pixels */

    UInt32 height;
    /**< Height of a character of font in lines */

    UInt32 bpp;
    /**< bytes per pixel of the font in bytes */

    UInt32 addr;
    /**< memory address location of the font */

    UInt32 lineOffset;
    /**< line offset of the font in bytes */

    UInt32 num;
    /**< Number of characters in font */

    UInt32 colorFormat;
    /**<
     *   Currently below data formats are supported
     *   - SYSTEM_DF_BGR16_565
     */

} Draw2D_FontProperty;

/*
 *******************************************************************************
 *
 *  \brief  Font property
 *
 *******************************************************************************
 */
typedef struct {

    UInt32 width;
    /**< Width of a bitmap data in pixels */

    UInt32 height;
    /**< Height of a bitmap data in lines */

    UInt32 bpp;
    /**< bytes per pixel of the bitmap in bytes */

    UInt32 addr;
    /**< memory address location of the bitmap */

    UInt32 lineOffset;
    /**< line offset of the bitmap in bytes */

    UInt32 colorFormat;
    /**<
     *   Currently below data formats are supported
     *   - SYSTEM_DF_BGR16_565
     */

} Draw2D_BmpProperty;

/**
 *******************************************************************************
 *
 *  \brief  Buffer information into which font and 2d primitives will be draw
 *
 *******************************************************************************
 */
typedef struct
{
    UInt32 bufWidth;
    /**< Width of buffer in pixels */

    UInt32 bufHeight;
    /**< Height of buffer in lines */

    UInt32 bufPitch[SYSTEM_MAX_PLANES];
    /**< Pitch of buffer in Bytes */

    UInt32 bufAddr[SYSTEM_MAX_PLANES];
    /**< Address of buffer memory */

    UInt32 dataFormat;
    /**< Valid values of type System_VideoDataFormat
     *   Currently below data formats are supported
     *   - SYSTEM_DF_BGR16_565
     *   - SYSTEM_DF_YUV422I_YVYU
     *   - SYSTEM_DF_YUV420SP_UV
     *   - SYSTEM_DF_BGRA16_4444
     */

    UInt32 transperentColor;
    /**< Color used to represent transperent color
     *   Buffer will be filled with this color initially and when
     *   Draw2D_clearBuf() is called
     *
     *   Representation of color in this field depends on the data format
     *   ex, 16-bit value for RGB565 data format
     */

    UInt32 transperentColorFormat;
    /**<
     *   Currently below data formats are supported
     *   - SYSTEM_DF_BGR16_565
     */

} Draw2D_BufInfo;

/**
 *******************************************************************************
 *
 *  \brief Font parameters
 *
 *******************************************************************************
 */
typedef struct
{
    UInt32 fontIdx;
    /**< Font index is used to select the font to use for drawing.
     */

} Draw2D_FontPrm;

/**
 *******************************************************************************
 *
 *  \brief Bitmap parameters
 *
 *******************************************************************************
 */
typedef struct
{
    UInt32 bmpIdx;
    /**< Bitmap index is used to select the bitmap to use for drawing.
     */

} Draw2D_BmpPrm;

/**
 *******************************************************************************
 *
 *  \brief Line draw parameters
 *
 *******************************************************************************
 */
typedef struct
{
    UInt32 lineColor;
    /**< Color used to draw a line
     *
     *   Representation of color in this field depends on the data format
     *   set during Draw2D_setBufInfo()
     *
     *   ex, 16-bit value for RGB565 data format
     */

    UInt32 lineSize;
    /**< Size of line in pixels to draw
     */

    UInt32 lineColorFormat;
    /**<
     *   Currently below data formats are supported
     *   - SYSTEM_DF_BGR16_565
     *   - SYSTEM_DF_YUV422I_YVYU
     *   - SYSTEM_DF_YUV420SP_UV
     *   - SYSTEM_DF_BGRA16_4444
     */

} Draw2D_LinePrm;

/**
 *******************************************************************************
 *
 *  \brief Region Params
 *
 *******************************************************************************
 */
typedef struct
{
    UInt32 startX;
    /**< X Position where region starts */
    UInt32 startY;
    /**< Y position where region starts */
    UInt32 height;
    /**< Height of the region */
    UInt32 width;
    /**< Width of the region */
    UInt32 color;
    /**< Color to be filled in this region */
    UInt32 colorFormat;
    /**<
     *   Currently below data formats are supported
     *   - SYSTEM_DF_BGR16_565
     *   - SYSTEM_DF_YUV422I_YVYU
     *   - SYSTEM_DF_YUV420SP_UV
     *   - SYSTEM_DF_BGRA16_4444
     */
}Draw2D_RegionPrm;

/*******************************************************************************
 *  \brief Draw 2D object handle
 *******************************************************************************
 */
typedef void *Draw2D_Handle;


/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Create a context for drawing
 *
 *        MUST be called before calling any other Draw2D API
 *
 * \param  pHndl    [OUT] Created Draw 2D context
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Draw2D_create(Draw2D_Handle *pHndl);

/**
 *******************************************************************************
 *
 * \brief Delete a previously created drawing context
 *
 * \param  pHndl    [IN] Draw 2D context
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Draw2D_delete(Draw2D_Handle);


/**
 *******************************************************************************
 *
 * \brief Associated a drawing buffer with a drawing context
 *
 *        This API MUST be called after Draw2D_create() and before any drawing
 *        API
 *
 * \param  pHndl    [IN] Draw 2D context
 * \param  pBufInfo [IN] Buffer information
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Draw2D_setBufInfo(Draw2D_Handle pHndl, Draw2D_BufInfo *pBufInfo);

/**
 *******************************************************************************
 *
 * \brief Update drawing buffer
 *
 *        This API can be used to update the buffer address when needed
 *
 * \param  pHndl    [IN] Draw 2D context
 * \param  bufAddr  [IN] Array of buffer addresses
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Void Draw2D_updateBufAddr(Draw2D_Handle pHndl, UInt32 *bufAddr);

/**
 *******************************************************************************
 *
 * \brief Fill buffer with transperency color
 *
 * \param  pHndl    [IN] Draw 2D context
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Draw2D_clearBuf(Draw2D_Handle pCtx);

/**
 *******************************************************************************
 *
 * \brief Draw string of character into the drawing buffer
 *
 * \param  pHndl    [IN] Draw 2D context
 * \param  startX   [IN] X-position in the buffer
 * \param  startY   [IN] Y-position in the buffer
 * \param  str      [IN] Ascii string to draw
 * \param  pPrm     [IN] Font to use when drawing,
 *                       when set to NULL default properties used
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Draw2D_drawString(Draw2D_Handle pCtx,
                        UInt32 startX,
                        UInt32 startY,
                        char *str,
                        Draw2D_FontPrm *pPrm);

/**
 *******************************************************************************
 *
 * \brief Draw string of character into the drawing buffer
 *
 * \param  pHndl    [IN] Draw 2D context
 * \param  startX   [IN] X-position in the buffer
 * \param  startY   [IN] Y-position in the buffer
 * \param  str      [IN] Ascii string to draw
 * \param  pPrm     [IN] Font to use when drawing,
 *                       when set to NULL default properties used
 * \param  rotate   [IN] Set 1 to rotate
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Draw2D_drawString_rot(Draw2D_Handle pCtx,
                        UInt32 startX,
                        UInt32 startY,
                        char *str,
                        Draw2D_FontPrm *pPrm,
                        UInt32 rotate);

/**
 *******************************************************************************
 *
 * \brief Clear a area equal to stringLength in the drawing buffer
 *
 *        This is used to erase a string of previously written characters.
 *        Internal this draws the 'SPACE' stringLength times
 *
 * \param  pHndl        [IN] Draw 2D context
 * \param  startX       [IN] start X-position in the buffer
 * \param  startY       [IN] start Y-position in the buffer
 * \param  stringLength [IN] Length of string to clear
 * \param  pPrm         [IN] Font to use when drawing,
 *                       when set to NULL default properties used
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Draw2D_clearString(Draw2D_Handle pCtx,
                            UInt32 startX,
                            UInt32 startY,
                            UInt32 stringLength,
                            Draw2D_FontPrm *pPrm);


/**
 *******************************************************************************
 *
 * \brief Get properties of a given font
 *
 * \param  pPrm         [IN] Font to use when drawing,
 *                       when set to NULL default properties used
 * \param  pProp        [OUT] Font properties like width x height, bpp etc
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Draw2D_getFontProperty(Draw2D_FontPrm *pPrm, Draw2D_FontProperty *pProp);

/**
 *******************************************************************************
 *
 * \brief Get properties of a given bitmap
 *
 * \param  pPrm         [IN] Bitmap to use when drawing,
 *                       when set to NULL default properties used
 * \param  pProp        [OUT] Bitmap properties like width x height, bpp etc
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Draw2D_getBmpProperty(Draw2D_BmpPrm *pPrm, Draw2D_BmpProperty *pProp);

/**
 *******************************************************************************
 *
 * \brief Draw a line in the drawing buffer
 *
 *        Currently only horizontal or vertical lines can be drawn
 *        So make sure endX or endY  is equal to startX or startY
 *
 *        To clear a line, call the same API with color as transperency
 *        color in line properties
 *
 * \param  pHndl        [IN] Draw 2D context
 * \param  startX       [IN] start X-position in the buffer
 * \param  startY       [IN] start Y-position in the buffer
 * \param  endX         [IN] end X-position in the buffer
 * \param  endY         [IN] end Y-position in the buffer
 * \param  pPrm         [IN] Line properties to use when drawing,
 *                       when set to NULL default properties used
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Draw2D_drawLine(Draw2D_Handle pCtx,
                        UInt32 startX,
                        UInt32 startY,
                        UInt32 endX,
                        UInt32 endY,
                        Draw2D_LinePrm *pPrm);

/**
 *******************************************************************************
 *
 * \brief Draw a rectangle in the drawing buffer
 *
 *        Internally uses Draw2D_drawLine() 4 times to draw the rectangle
 *
 *        To clear a rectangle, call the same API with color as transperency
 *        color in line properties
 *
 * \param  pHndl        [IN] Draw 2D context
 * \param  startX       [IN] start X-position in the buffer
 * \param  startY       [IN] start Y-position in the buffer
 * \param  width        [IN] width of rectangle in pixels
 * \param  height       [IN] height of rectangle in lines
 * \param  pPrm         [IN] Line properties to use when drawing,
 *                       when set to NULL default properties used
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Draw2D_drawRect(Draw2D_Handle pCtx,
                        UInt32 startX,
                        UInt32 startY,
                        UInt32 width,
                        UInt32 height,
                        Draw2D_LinePrm *pPrm);

/**
 *******************************************************************************
 *
 * \brief Clear a region in the drawing buffer with transperency color
 *
 * \param  pHndl        [IN] Draw 2D context
 * \param  startX       [IN] start X-position in the buffer
 * \param  startY       [IN] start Y-position in the buffer
 * \param  width        [IN] width of region in pixels
 * \param  height       [IN] height of region in lines
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Draw2D_clearRegion(Draw2D_Handle pCtx,
                            UInt32 startX,
                            UInt32 startY,
                            UInt32 width,
                            UInt32 height);


/**
 *******************************************************************************
 *
 * \brief Draw a region in the drawing buffer with custom color
 *
 * \param  pHndl        [IN] Draw 2D context
 * \param  prm          [IN] Region Parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Draw2D_fillRegion(Draw2D_Handle pCtx, Draw2D_RegionPrm *prm);


/**
 *******************************************************************************
 *
 * \brief Draw pixel of a given color
 *
 *        Representation of color in this function depends on the data format
 *        set during Draw2D_setBufInfo()
 *
 *        ex, 16-bit value for RGB565 data format
 *
 * \param  pHndl        [IN] Draw 2D context
 * \param  px           [IN] X-position in the buffer
 * \param  py           [IN] Y-position in the buffer
 * \param  color        [IN] Color used to draw the pixel
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
void Draw2D_drawPixel(Draw2D_Handle pCtx, UInt32 px, UInt32 py, UInt32 color, UInt32 colorFormat);


/**
 *******************************************************************************
 *
 * \brief Draw a bitmap into the drawing buffer
 *
 * \param  pHndl    [IN] Draw 2D context
 * \param  startX   [IN] X-position in the buffer
 * \param  startY   [IN] Y-position in the buffer
 * \param  pPrm     [IN] Bitmap to use when drawing,
 *                       when set to NULL default properties used
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Draw2D_drawBmp(Draw2D_Handle pCtx,
                        UInt32 startX,
                        UInt32 startY,
                        Draw2D_BmpPrm *pPrm);

/**
 *******************************************************************************
 *
 * \brief Draw a bitmap into the drawing buffer
 *
 * \param  pHndl    [IN] Draw 2D context
 * \param  startX   [IN] X-position in the buffer
 * \param  startY   [IN] Y-position in the buffer
 * \param  pPrm     [IN] Bitmap to use when drawing,
 *                       when set to NULL default properties used
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Draw2D_drawBmp_rot(Draw2D_Handle pCtx,
                        UInt32 startX,
                        UInt32 startY,
                        Draw2D_BmpPrm *pPrm,
                        UInt32 rotate);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif  /* _DRAW_2D_H_ */

/* @} */

/* Nothing beyond this point */

