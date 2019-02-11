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
#include <system_cfg.h>
#include <src/rtos/draw2d/draw2d_priv.h>


Int32 Draw2D_getFontProperty(Draw2D_FontPrm *pPrm, Draw2D_FontProperty *pProp)
{

    if(pProp==NULL)
        return SYSTEM_LINK_STATUS_EINVALID_PARAMS;

    #if defined(BUILD_M4_0) || defined(BUILD_M4_2) || defined(BUILD_A15)
    /* default */
    Draw2D_getFontProperty00(pProp); /* default */

    if(pPrm!=NULL)
    {
        if(pPrm->fontIdx==0)
            Draw2D_getFontProperty00(pProp);
        else
        if(pPrm->fontIdx==1)
            Draw2D_getFontProperty01(pProp);
        else
        if(pPrm->fontIdx==2)
            Draw2D_getFontProperty02(pProp);
        else
        if(pPrm->fontIdx==3)
            Draw2D_getFontProperty03(pProp);
        else
        if(pPrm->fontIdx==4)
            Draw2D_getFontProperty04(pProp);
        else
        if(pPrm->fontIdx==5)
            Draw2D_getFontProperty05(pProp);
        else
        if(pPrm->fontIdx==6)
            Draw2D_getFontProperty06(pProp);
        else
        if(pPrm->fontIdx==7)
            Draw2D_getFontProperty07(pProp);
        else
        if(pPrm->fontIdx==8)
            Draw2D_getFontProperty08(pProp);
        else
        if(pPrm->fontIdx==9)
            Draw2D_getFontProperty09(pProp);
        else
        if(pPrm->fontIdx==10)
            Draw2D_getFontProperty10(pProp);
        else
        if(pPrm->fontIdx==11)
            Draw2D_getFontProperty11(pProp);
        else
        if(pPrm->fontIdx==12)
            Draw2D_getFontProperty12(pProp);
        else
        if(pPrm->fontIdx==13)
            Draw2D_getFontProperty13(pProp);
        else
        if(pPrm->fontIdx==14)
            Draw2D_getFontProperty14(pProp);
    }
    #else
        #ifdef BUILD_DSP
        /* default */
        Draw2D_getFontProperty10(pProp); /* default */
        if(pPrm!=NULL)
        {
            #ifdef ALG_radarprocess
            if(pPrm->fontIdx==0)
                Draw2D_getFontProperty00(pProp);
            else
            if(pPrm->fontIdx==02)
                Draw2D_getFontProperty02(pProp);
            else
            #endif
            if(pPrm->fontIdx==10)
                Draw2D_getFontProperty10(pProp);
            else
            if(pPrm->fontIdx==11)
                Draw2D_getFontProperty11(pProp);
            else
            if(pPrm->fontIdx==12)
                Draw2D_getFontProperty12(pProp);
            else
            if(pPrm->fontIdx==13)
                Draw2D_getFontProperty13(pProp);
        }
        #else
        /* Not supported on this CPU */
        UTILS_assert(0);
        #endif
    #endif

    return SYSTEM_LINK_STATUS_SOK;
}

Int32 Draw2D_getBmpProperty(Draw2D_BmpPrm *pPrm, Draw2D_BmpProperty *pProp)
{
    if(pProp==NULL)
        return SYSTEM_LINK_STATUS_EINVALID_PARAMS;

    #if defined(BUILD_M4_0) || defined(BUILD_M4_2) || defined(BUILD_A15)
    /* default */
    Draw2D_getBmpProperty00(pProp); /* default */

    if(pPrm!=NULL)
    {
        if(pPrm->bmpIdx==DRAW2D_BMP_IDX_TI_LOGO)
            Draw2D_getBmpProperty00(pProp);
        else
        if(pPrm->bmpIdx==DRAW2D_BMP_IDX_TI_LOGO_1)
            Draw2D_getBmpProperty10(pProp);
        else
        if(pPrm->bmpIdx==DRAW2D_BMP_IDX_TI_LOGO_SMALL)
            Draw2D_getBmpProperty12(pProp);
        else
        #ifdef ALG_objectdetection
        if(pPrm->bmpIdx==DRAW2D_BMP_IDX_FRONT_CAM_ANALYTICS)
            Draw2D_getBmpProperty02(pProp);
        else
        #endif
        #ifdef ALG_denseopticalflow
        if(pPrm->bmpIdx==DRAW2D_BMP_IDX_OPTFLOW_LUT_0)
            Draw2D_getBmpProperty03(pProp);
        else
        if(pPrm->bmpIdx==DRAW2D_BMP_IDX_OPTFLOW_LUT_1)
            Draw2D_getBmpProperty04(pProp);
        else
        #endif
        #ifdef ALG_surroundview
        if(pPrm->bmpIdx==DRAW2D_BMP_IDX_SURROUND_VIEW)
            Draw2D_getBmpProperty01(pProp);
        else
        if(pPrm->bmpIdx==DRAW2D_BMP_IDX_JEEP_IMAGE)
            Draw2D_getBmpProperty06(pProp);
        else
        if(pPrm->bmpIdx==DRAW2D_BMP_IDX_JEEP_220_X_330)
            Draw2D_getBmpProperty08(pProp);
        else
        if(pPrm->bmpIdx==DRAW2D_BMP_IDX_SURROUND_VIEW_SMALL)
            Draw2D_getBmpProperty09(pProp);
        else
        if(pPrm->bmpIdx==DRAW2D_BMP_IDX_JEEP_IMAGE_TRUESCALE)
            Draw2D_getBmpProperty14(pProp);
        else
        if(pPrm->bmpIdx==DRAW2D_BMP_IDX_3DPERCEPTION_SFM_LOGO)
            Draw2D_getBmpProperty17(pProp);
        else
        if(pPrm->bmpIdx==DRAW2D_BMP_IDX_TDA2X)
            Draw2D_getBmpProperty18(pProp);
        else
        if(pPrm->bmpIdx==DRAW2D_BMP_IDX_TDA3X_SUV_348x480)
            Draw2D_getBmpProperty21(pProp);
        else
        if(pPrm->bmpIdx==DRAW2D_BMP_FORD_REARVIEW_CAMERA_LEFT)
            Draw2D_getBmpProperty22(pProp);
        else
        if(pPrm->bmpIdx==DRAW2D_BMP_FORD_REARVIEW_CAMERA_RIGHT)
            Draw2D_getBmpProperty23(pProp);
        else
        if(pPrm->bmpIdx==DRAW2D_BMP_FORD_TOPDOWN_REARVIEW_CAMERA_LEFT)
            Draw2D_getBmpProperty24(pProp);
        else
        if(pPrm->bmpIdx==DRAW2D_BMP_FORD_TOPDOWN_REARVIEW_CAMERA_RIGHT)
            Draw2D_getBmpProperty25(pProp);
        else
        if(pPrm->bmpIdx==DRAW2D_BMP_IDX_TDA3X)
            Draw2D_getBmpProperty32(pProp);
        else
        #endif
        #ifdef ALG_stereo_postprocessing
        if(pPrm->bmpIdx==DRAW2D_BMP_IDX_STEREO_COLORBAR_20x720)
            Draw2D_getBmpProperty07(pProp);
        else
        if(pPrm->bmpIdx==DRAW2D_BMP_IDX_STEREO_COLORBAR_35x450)
            Draw2D_getBmpProperty13(pProp);
        else
        #endif
        #ifdef ALG_clr
        if(pPrm->bmpIdx==DRAW2D_BMP_IDX_TL_RED)
            Draw2D_getBmpProperty15(pProp);
        else
        if(pPrm->bmpIdx==DRAW2D_BMP_IDX_TL_GREEN)
            Draw2D_getBmpProperty16(pProp);
        else
        #endif
        #ifdef ALG_rear_view_panorama
        if(pPrm->bmpIdx==DRAW2D_BMP_IDX_REAR_VIEW_PANORAMA)
            Draw2D_getBmpProperty19(pProp);
        else
        if(pPrm->bmpIdx==DRAW2D_BMP_IDX_CAR_IMAGE)
            Draw2D_getBmpProperty27(pProp);
        else
        if(pPrm->bmpIdx==DRAW2D_BMP_IDX_CAR2_IMAGE)
            Draw2D_getBmpProperty28(pProp);
        else
        if(pPrm->bmpIdx==DRAW2D_BMP_IDX_RSVP_CAR_IMAGE)
            Draw2D_getBmpProperty29(pProp);
        else
        #endif
        {
        }
    }
    #else
    /* Not supported on this CPU */
    UTILS_assert(0);
    #endif

    return SYSTEM_LINK_STATUS_SOK;
}

UInt32 Draw2D_getFontCharAddr(Draw2D_FontProperty *font, char c)
{
    if(font==NULL)
        return 0;

    if(c<' ' || c>'~')
        c = ' '; /* if out of bound draw 'space' char */

    c = c - ' ';

    return font->addr + c*font->width*font->bpp;
}

Int32 Draw2D_drawString_rot(Draw2D_Handle pCtx,
                        UInt32 startX,
                        UInt32 startY,
                        char *str,
                        Draw2D_FontPrm *pPrm,
                        UInt32 rotate)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    Draw2D_Obj *pObj = (Draw2D_Obj *)pCtx;
    UInt32 len, width, height, fontAddr, h, i, w, px, py;
    UInt16 *fontAddr16, color;
    Draw2D_FontProperty font;

    if(pObj==NULL || str==NULL)
        return SYSTEM_LINK_STATUS_EINVALID_PARAMS;

    Draw2D_getFontProperty(pPrm, &font);

    len = strlen(str);

    width = font.width*len;
    height = font.height;

    if(startX >= pObj->bufInfo.bufWidth)
        return 0;

    if(startY >= pObj->bufInfo.bufHeight)
        return 0;

    if(0 == rotate)
    {
        if((startX + width)> pObj->bufInfo.bufWidth)
        {
            width = pObj->bufInfo.bufWidth - startX;
        }

        if((startY + height)> pObj->bufInfo.bufHeight)
        {
            height = pObj->bufInfo.bufHeight - startY;
        }
    }
    else if(1 == rotate)
    {
        if((startX + height)> pObj->bufInfo.bufWidth)
        {
            height = pObj->bufInfo.bufWidth - startX;
        }

        if(startY < width/2)
        {
            width = startY*2;
        }
    }
    else if(2 == rotate)
    {
        if(startX < height)
        {
            height = startX;
        }

        if((startY + width/2) > pObj->bufInfo.bufHeight)
        {
            width = 2*(pObj->bufInfo.bufHeight - startY);
        }
    }


    len = width/font.width;

    /* draw 'len' char's from string 'str' */
    if(0 == rotate)
    {
        if(font.colorFormat==SYSTEM_DF_YUV420SP_UV)
        {
            for(i=0; i<len; i++)
            {
                px  = startX + i*font.width;
                py  = startY;

                Draw2D_drawCharYuv420SP(pCtx, px, py, str[i], &font);
            }
        }
        else
        {
            for(i=0; i<len; i++)
            {
                fontAddr = Draw2D_getFontCharAddr(&font, str[i]);
                px  = startX + i*font.width;
                py  = startY;

                /* draw font char */
                for(h=0; h<height; h++)
                {
                    fontAddr16 = (UInt16*)fontAddr;
                    for(w=0; w<font.width; w++)
                    {
                        /* Assume color format is 2 bytes per pixel */
                        color = *fontAddr16;
                        Draw2D_drawPixel(
                            pCtx,
                            px+w,
                            py+h,
                            color,
                            font.colorFormat
                            );
                        fontAddr16++;
                    }
                    fontAddr += font.lineOffset;
                }
            }
        }
    }
    else if(1 == rotate)
    {
        for(i=0; i<len; i++)
        {
            fontAddr = Draw2D_getFontCharAddr(&font, str[i]);
            px  = startX;
            py  = startY - i*font.width;

            /* draw font char */
            for(h=0; h<height; h++)
            {
                fontAddr16 = (UInt16*)fontAddr;
                for(w=0; w<font.width; w++)
                {
                    /* Assume color format is 2 bytes per pixel */
                    color = *fontAddr16;
                    Draw2D_drawPixel(
                        pCtx,
                        px+h,
                        py-w,
                        color,
                        font.colorFormat
                        );
                    fontAddr16++;
                }
                fontAddr += font.lineOffset;
            }
        }
    }
    else if(2 == rotate)
    {
        for(i=0; i<len; i++)
        {
            fontAddr = Draw2D_getFontCharAddr(&font, str[i]);
            px  = startX;
            py  = startY + i*font.width;

            /* draw font char */
            for(h=0; h<height; h++)
            {
                fontAddr16 = (UInt16*)fontAddr;
                for(w=0; w<font.width; w++)
                {
                    /* Assume color format is 2 bytes per pixel */
                    color = *fontAddr16;
                    Draw2D_drawPixel(
                        pCtx,
                        px-h,
                        py+w,
                        color,
                        font.colorFormat
                        );
                    fontAddr16++;
                }
                fontAddr += font.lineOffset;
            }
        }
    }

    return status;
}

Int32 Draw2D_drawString(Draw2D_Handle pCtx,
                        UInt32 startX,
                        UInt32 startY,
                        char *str,
                        Draw2D_FontPrm *pPrm)
{
    return Draw2D_drawString_rot(pCtx,
                          startX,
                          startY,
                          str,
                          pPrm,
                          0);
}

Int32 Draw2D_clearString(Draw2D_Handle pCtx,
                            UInt32 startX,
                            UInt32 startY,
                            UInt32 stringLength,
                            Draw2D_FontPrm *pPrm)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    char tmpString[80];
    UInt32 len, clearLen;
    Draw2D_FontProperty font;

    if(pCtx==NULL)
        return SYSTEM_LINK_STATUS_EINVALID_PARAMS;

    Draw2D_getFontProperty(pPrm, &font);

    len = sizeof(tmpString)-1;
    memset(tmpString, ' ', len);

    while(stringLength)
    {
        if(stringLength<len)
            clearLen = stringLength;
        else
            clearLen = len;

        tmpString[clearLen] = 0;
        Draw2D_drawString(pCtx, startX, startY, tmpString, pPrm);

        startX += clearLen*font.width;

        stringLength -= clearLen;
    }
    return status;
}

Int32 Draw2D_drawBmp(Draw2D_Handle pCtx,
                        UInt32 startX,
                        UInt32 startY,
                        Draw2D_BmpPrm *pPrm)
{
    return Draw2D_drawBmp_rot(pCtx,
                        startX,
                        startY,
                        pPrm,
                        0);
}

Int32 Draw2D_drawBmp_rot(Draw2D_Handle pCtx,
                        UInt32 startX,
                        UInt32 startY,
                        Draw2D_BmpPrm *pPrm,
                        UInt32 rotate)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    Draw2D_Obj *pObj = (Draw2D_Obj *)pCtx;
    UInt32 width, height, bmpAddr, h, w;
    UInt16 color, *bmpAddr16;
    Draw2D_BmpProperty bmp;

    if(pObj==NULL)
        return SYSTEM_LINK_STATUS_EINVALID_PARAMS;

    Draw2D_getBmpProperty(pPrm, &bmp);

    width = bmp.width;
    height = bmp.height;

    if (startX >= pObj->bufInfo.bufWidth)
        return 0;

    if (startY >= pObj->bufInfo.bufHeight)
        return 0;

    if (pObj->bufInfo.dataFormat != SYSTEM_DF_BGR16_565
         &&
        pObj->bufInfo.dataFormat != SYSTEM_DF_BGRA16_4444
        )
    {
        return 0;
    }

    if(0 == rotate)
    {
        if((startX + width)> pObj->bufInfo.bufWidth)
        {
            width = pObj->bufInfo.bufWidth - startX;
        }

        if((startY + height)> pObj->bufInfo.bufHeight)
        {
            height = pObj->bufInfo.bufHeight - startY;
        }
    }
    else if(1 == rotate)
    {
        if((startX + height)> pObj->bufInfo.bufWidth)
        {
            height = pObj->bufInfo.bufWidth - startX;
        }

        if(startY < width/2)
        {
            width = startY*2;
        }
    }
    else if(2 == rotate)
    {
        if(startX < height)
        {
            height = startX;
        }

        if((startY + width/2) > pObj->bufInfo.bufHeight)
        {
            width = 2*(pObj->bufInfo.bufHeight - startY);
        }
    }

    /* draw bitmap */
    bmpAddr = bmp.addr;

    if(0 == rotate)
    {
        /* draw bmp */
        for(h=0; h<height; h++)
        {
            bmpAddr16 = (UInt16*)bmpAddr;
            for(w=0; w<bmp.width; w++)
            {
                /* Assume color format is 2 bytes per pixel */
                color = *bmpAddr16;
                Draw2D_drawPixel(
                    pCtx,
                    startX+w,
                    startY+h,
                    color,
                    bmp.colorFormat
                    );
                bmpAddr16++;
            }
            bmpAddr += bmp.lineOffset;
        }
    }
    else if(1 == rotate)
    {
        /* draw bmp */
        for(h=0; h<height; h++)
        {
            bmpAddr16 = (UInt16*)bmpAddr;
            for(w=0; w<bmp.width; w++)
            {
                /* Assume color format is 2 bytes per pixel */
                color = *bmpAddr16;
                Draw2D_drawPixel(
                    pCtx,
                    startX+h,
                    startY-w,
                    color,
                    bmp.colorFormat
                    );
                bmpAddr16++;
            }
            bmpAddr += bmp.lineOffset;
        }
    }
    else if(2 == rotate)
    {
        /* draw bmp */
        for(h=0; h<height; h++)
        {
            bmpAddr16 = (UInt16*)bmpAddr;
            for(w=0; w<bmp.width; w++)
            {
                /* Assume color format is 2 bytes per pixel */
                color = *bmpAddr16;
                Draw2D_drawPixel(
                    pCtx,
                    startX-h,
                    startY+w,
                    color,
                    bmp.colorFormat
                    );
                bmpAddr16++;
            }
            bmpAddr += bmp.lineOffset;
        }
    }

    return status;
}
