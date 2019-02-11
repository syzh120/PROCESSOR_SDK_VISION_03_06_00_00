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

#include <src/rtos/draw2d/draw2d_priv.h>


#define RGB565_TO_BGRA444(x)        ((((UInt32)(x>>1) & 0xF) << 0) | (((UInt32)(x>>7) & 0xF) << 4) | (((UInt32)(x>>12) & 0xF)<<8)| (((UInt32)(0xF) & 0xF)<<12))

Int32 Draw2D_create(Draw2D_Handle *pHndl)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    Draw2D_Obj *pObj;

    *pHndl = NULL;

    pObj = malloc(sizeof(*pObj));
    if(pObj==NULL)
        return SYSTEM_LINK_STATUS_EALLOC;

    memset(pObj, 0, sizeof(*pObj));

    *pHndl = pObj;

    return status;
}

Int32 Draw2D_delete(Draw2D_Handle pHndl)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    if(pHndl)
        free(pHndl);

    return status;
}

Int32 Draw2D_setBufInfo(Draw2D_Handle pHndl, Draw2D_BufInfo *pBufInfo)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    Draw2D_Obj *pObj = (Draw2D_Obj *)pHndl;

    if(pHndl==NULL || pBufInfo == NULL)
        return SYSTEM_LINK_STATUS_EINVALID_PARAMS;

    pObj->bufInfo = *pBufInfo;

    if(pObj->bufInfo.dataFormat==SYSTEM_DF_BGR16_565
        ||
       pObj->bufInfo.dataFormat==SYSTEM_DF_BGRA16_4444
        ||
       pObj->bufInfo.dataFormat==SYSTEM_DF_YUV422I_YUYV
        ||
       pObj->bufInfo.dataFormat==SYSTEM_DF_YUV420SP_UV
        )
    {

    }
    else
    {
        return SYSTEM_LINK_STATUS_EINVALID_PARAMS;
    }

    if(pObj->bufInfo.bufAddr[0] == (UInt32)NULL
        ||
       pObj->bufInfo.bufWidth == 0
        ||
       pObj->bufInfo.bufPitch[0] == 0
        ||
       pObj->bufInfo.bufHeight == 0
        )
    {
        return SYSTEM_LINK_STATUS_EINVALID_PARAMS;
    }

    if (pObj->bufInfo.dataFormat == SYSTEM_DF_YUV420SP_UV
         &&
        (pObj->bufInfo.bufAddr[1] == (UInt32)NULL
         ||
        pObj->bufInfo.bufPitch[1] == 0)
        )
    {
        return SYSTEM_LINK_STATUS_EINVALID_PARAMS;
    }

    return status;
}

Void Draw2D_updateBufAddr(Draw2D_Handle pHndl, UInt32 *bufAddr)
{
    Draw2D_Obj *pObj = (Draw2D_Obj *)pHndl;

    pObj->bufInfo.bufAddr[0] = bufAddr[0];
    pObj->bufInfo.bufAddr[1] = bufAddr[1];
    pObj->bufInfo.bufAddr[2] = bufAddr[2];

}

Int32 Draw2D_clearBuf(Draw2D_Handle pCtx)
{
    Int32 status;
    Draw2D_Obj *pObj = (Draw2D_Obj *)pCtx;

    if(pObj==NULL)
        return SYSTEM_LINK_STATUS_EINVALID_PARAMS;

    status = Draw2D_clearRegion(
                pCtx,
                0,
                0,
                pObj->bufInfo.bufWidth,
                pObj->bufInfo.bufHeight);

    return status;
}

Int32 Draw2D_clearRegion(Draw2D_Handle pCtx,
                            UInt32 startX,
                            UInt32 startY,
                            UInt32 width,
                            UInt32 height)
{
    Draw2D_RegionPrm regionPrm;
    Draw2D_Obj *pObj = (Draw2D_Obj *)pCtx;

    if(pObj==NULL)
        return SYSTEM_LINK_STATUS_EINVALID_PARAMS;

    regionPrm.startX = startX;
    regionPrm.startY = startY;
    regionPrm.width  = width;
    regionPrm.height = height;
    regionPrm.color  = pObj->bufInfo.transperentColor;
    regionPrm.colorFormat  = pObj->bufInfo.transperentColorFormat;

    return Draw2D_fillRegion(pCtx, &regionPrm);
}

Int32 Draw2D_fillRegion(Draw2D_Handle pCtx, Draw2D_RegionPrm *regionPrm)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    Draw2D_Obj *pObj = (Draw2D_Obj *)pCtx;
    UInt32 x, y;

    if(pObj==NULL)
        return SYSTEM_LINK_STATUS_EINVALID_PARAMS;

    if(regionPrm->startX >= pObj->bufInfo.bufWidth)
        return 0;

    if(regionPrm->startY >= pObj->bufInfo.bufHeight)
        return 0;

    if((regionPrm->startX + regionPrm->width)> pObj->bufInfo.bufWidth)
    {
        regionPrm->width = pObj->bufInfo.bufWidth - regionPrm->startX;
    }

    if((regionPrm->startY + regionPrm->height)> pObj->bufInfo.bufHeight)
    {
        regionPrm->height = pObj->bufInfo.bufHeight - regionPrm->startY;
    }

    for(x=regionPrm->startX; x< regionPrm->startX+regionPrm->width; x++)
    {
        for(y=regionPrm->startY; y< regionPrm->startY+regionPrm->height; y++)
        {
            Draw2D_drawPixel(
                pCtx,
                x,
                y,
                regionPrm->color,
                regionPrm->colorFormat
                );
        }
    }

    return status;
}

void Draw2D_drawCharYuv420SP(Draw2D_Handle pCtx, UInt32 px, UInt32 py, char value, Draw2D_FontProperty *pProp)
{
    Draw2D_Obj *pObj = (Draw2D_Obj *)pCtx;
    UInt32 addr, width, height, h;
    UInt8 *fontAddr;

    if(pCtx==NULL)
        return ;

    py = SystemUtils_floor(py, 2);
    px = SystemUtils_floor(px, 2);

    if(px >= pObj->bufInfo.bufWidth)
        return ;

    if(py >= pObj->bufInfo.bufHeight)
        return ;

    width = pProp->width;
    height= pProp->height;

    if( py+height >= pObj->bufInfo.bufHeight)
    {
        height = pObj->bufInfo.bufHeight-py;
    }
    if( px+width >= pObj->bufInfo.bufWidth)
    {
        width = pObj->bufInfo.bufWidth-px;
    }

    fontAddr = (UInt8*)Draw2D_getFontCharAddr(pProp, value);

    addr = pObj->bufInfo.bufAddr[0]
        + pObj->bufInfo.bufPitch[0]*py + px;

    for(h=0; h<height; h++)
    {
        memcpy((void*)addr, fontAddr, pProp->width);
        fontAddr += pProp->lineOffset;
        addr += pObj->bufInfo.bufPitch[0];
    }

    fontAddr = (UInt8*)Draw2D_getFontCharAddr(pProp, value);

    fontAddr += pProp->lineOffset*pProp->height;

    addr = pObj->bufInfo.bufAddr[1]
        + pObj->bufInfo.bufPitch[1]*py/2 + px;

    for(h=0; h<height/2; h++)
    {
        memcpy((void*)addr, fontAddr, pProp->width);
        fontAddr += pProp->lineOffset;
        addr += pObj->bufInfo.bufPitch[1];
    }
}

void Draw2D_drawPixel(Draw2D_Handle pCtx, UInt32 px, UInt32 py, UInt32 color, UInt32 colorFormat)
{
    Draw2D_Obj *pObj = (Draw2D_Obj *)pCtx;
    UInt32 addr;

    if(pCtx==NULL)
        return ;

    if(px >= pObj->bufInfo.bufWidth)
        return ;

    if(py >= pObj->bufInfo.bufHeight)
        return ;

    if(pObj->bufInfo.dataFormat==SYSTEM_DF_BGRA16_4444)
    {
        if(colorFormat==SYSTEM_DF_BGR16_565)
            color = RGB565_TO_BGRA444(color);

        addr = pObj->bufInfo.bufAddr[0]
            + pObj->bufInfo.bufPitch[0]*py + 2*px;

        *(UInt16*)addr = (color & 0xFFFF);
    }
    else
    if(pObj->bufInfo.dataFormat==SYSTEM_DF_BGR16_565)
    {
        /* color in BGR565 is represented as,
         * bit  0.. 4 = B
         * bit  5..10 = G
         * bit 11..15 = R
         * bit 16..23 = NOT USED
         * bit 24..31 = NOT USED
         */

        addr = pObj->bufInfo.bufAddr[0]
            + pObj->bufInfo.bufPitch[0]*py + 2*px;

        *(UInt16*)addr = (color & 0xFFFF);
    }
    else
    if(pObj->bufInfo.dataFormat==SYSTEM_DF_YUV422I_YUYV)
    {
        /* color in YUV422 is represented as,
         * bit  0.. 7 = Y
         * bit  8..15 = U
         * bit 16..23 = Y
         * bit 24..31 = V
         */

        /* x MUST be multiple of 2 */
        px = SystemUtils_floor(px, 2);

        addr = pObj->bufInfo.bufAddr[0]
            + pObj->bufInfo.bufPitch[0]*py + 2*px;

        *(UInt32*)addr = color;
    }
    else
    if(pObj->bufInfo.dataFormat==SYSTEM_DF_YUV420SP_UV)
    {
        /* color in YUV420 is represented as,
         * bit  0.. 7 = V
         * bit  8..15 = U
         * bit 16..23 = Y
         * bit 24..31 = NOT USED
         */

        /* x, y MUST be multiple of 2 */
        px = SystemUtils_floor(px, 2);
        py = SystemUtils_floor(py, 2);

        /* Put Y color */
        addr = pObj->bufInfo.bufAddr[0]
            + pObj->bufInfo.bufPitch[0]*py + px;

        *(UInt8*)addr = ((color & 0xFF0000) >> 16);

        addr = pObj->bufInfo.bufAddr[0]
            + pObj->bufInfo.bufPitch[0]*py + (px+1);

        *(UInt8*)addr = ((color & 0xFF0000) >> 16);

        addr = pObj->bufInfo.bufAddr[0]
            + pObj->bufInfo.bufPitch[0]*(py+1) + px;

        *(UInt8*)addr = ((color & 0xFF0000) >> 16);

        addr = pObj->bufInfo.bufAddr[0]
            + pObj->bufInfo.bufPitch[0]*(py+1) + (px+1);

        *(UInt8*)addr = ((color & 0xFF0000) >> 16);

        /* Put CbCr color */
        addr = pObj->bufInfo.bufAddr[1]
            + pObj->bufInfo.bufPitch[1]*py/2 + px;

        *(UInt16*)addr = ((color & 0xFF00) >> 8) | ((color & 0xFF) << 8);
    }
}


#define SIGN(x) ((x<0)?-1:((x>0)?1:0)) /* macro to return the sign of a
                                         number */

#define ABS(x)  (x<0?-x:x) /* macro to find abs of a value */

Int32 Draw2D_drawLine(Draw2D_Handle pCtx,
                        UInt32 x1,
                        UInt32 y1,
                        UInt32 x2,
                        UInt32 y2,
                        Draw2D_LinePrm *pPrm)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    Draw2D_Obj *pObj = (Draw2D_Obj *)pCtx;
    Int32 i,dx,dy,sdx,sdy,dxabs,dyabs,x,y,px,py;
    Int32 lineSize, k;
    UInt32 lineColor, lineColorFormat;

    if(pPrm==NULL)
    {
        lineSize  = 1;
        lineColor = 0xFFFFFFFF;
        lineColorFormat = SYSTEM_DF_BGR16_565;
    }
    else
    {
        lineSize  = pPrm->lineSize;
        lineColor = pPrm->lineColor;
        lineColorFormat = pPrm->lineColorFormat;
    }

    if(x1 > pObj->bufInfo.bufWidth)
        x1 = pObj->bufInfo.bufWidth;

    if(x2 > pObj->bufInfo.bufWidth)
        x2 = pObj->bufInfo.bufWidth;

    if(y1 >= pObj->bufInfo.bufHeight)
        y1 = pObj->bufInfo.bufHeight;

    if(y2 >= pObj->bufInfo.bufHeight)
        y2 = pObj->bufInfo.bufHeight;

    dx=x2-x1;      /* the horizontal distance of the line */
    dy=y2-y1;      /* the vertical distance of the line */
    dxabs=ABS(dx);
    dyabs=ABS(dy);
    sdx=SIGN(dx);
    sdy=SIGN(dy);
    x=dyabs>>1;
    y=dxabs>>1;
    px=x1;
    py=y1;

    if (dxabs>=dyabs) /* the line is more horizontal than vertical */
    {
        for(k=(-lineSize/2); k<(lineSize/2); k++)
        {
            Draw2D_drawPixel(pObj, px, py+k, lineColor, lineColorFormat);
        }
        for(i=0;i<dxabs;i++)
        {
            y+=dyabs;
            if (y>=dxabs)
            {
                y-=dxabs;
                py+=sdy;
            }
            px+=sdx;
            for(k=(-lineSize/2); k<(lineSize/2); k++)
            {
                Draw2D_drawPixel(pObj, px, py+k, lineColor, lineColorFormat);
            }
        }
    }
    else /* the line is more vertical than horizontal */
    {
        for(k=(-lineSize/2); k<(lineSize/2); k++)
        {
            Draw2D_drawPixel(pObj, px+k, py, lineColor, lineColorFormat);
        }
        for(i=0;i<dyabs;i++)
        {
            x+=dxabs;
            if (x>=dyabs)
            {
                x-=dyabs;
                px+=sdx;
            }
            py+=sdy;
            for(k=(-lineSize/2); k<(lineSize/2); k++)
            {
                Draw2D_drawPixel(pObj, px+k, py, lineColor, lineColorFormat);
            }
        }
    }

    return status;
}

Int32 Draw2D_drawHorizontalLine(Draw2D_Handle pCtx,
                                    UInt32 startX,
                                    UInt32 startY,
                                    UInt32 width,
                                    Draw2D_LinePrm * pPrm)
{
    Draw2D_Obj *pObj = (Draw2D_Obj *)pCtx;
    UInt32 lineSize, lineColor, lineColorFormat;
    Draw2D_RegionPrm regionPrm;

    if(pObj==NULL)
        return SYSTEM_LINK_STATUS_EINVALID_PARAMS;

    if(pPrm==NULL)
    {
        lineSize  = 2;
        lineColor = 0xFFFFFFFF;
        lineColorFormat = SYSTEM_DF_BGR16_565;
    }
    else
    {
        lineSize  = pPrm->lineSize;
        lineColor = pPrm->lineColor;
        lineColorFormat = pPrm->lineColorFormat;
    }

    regionPrm.startX = startX;
    regionPrm.startY = startY;
    regionPrm.width  = width;
    regionPrm.height = lineSize;
    regionPrm.color  = lineColor;
    regionPrm.colorFormat = lineColorFormat;

    return Draw2D_fillRegion(pCtx, &regionPrm);
}

Int32 Draw2D_drawVerticalLine(Draw2D_Handle pCtx,
                                    UInt32 startX,
                                    UInt32 startY,
                                    UInt32 height,
                                    Draw2D_LinePrm * pPrm)
{
    Draw2D_Obj *pObj = (Draw2D_Obj *)pCtx;
    UInt32 lineSize, lineColor, lineColorFormat;;
    Draw2D_RegionPrm regionPrm;

    if(pObj==NULL)
        return SYSTEM_LINK_STATUS_EINVALID_PARAMS;

    if(pPrm==NULL)
    {
        lineSize  = 2;
        lineColor = 0xFFFFFFFF;
        lineColorFormat = SYSTEM_DF_BGR16_565;
    }
    else
    {
        lineSize  = pPrm->lineSize;
        lineColor = pPrm->lineColor;
        lineColorFormat = pPrm->lineColorFormat;
    }

    regionPrm.startX = startX;
    regionPrm.startY = startY;
    regionPrm.width  = lineSize;
    regionPrm.height = height;
    regionPrm.color  = lineColor;
    regionPrm.colorFormat = lineColorFormat;

    return Draw2D_fillRegion(pCtx, &regionPrm);
}

Int32 Draw2D_drawRect(Draw2D_Handle pCtx,
                        UInt32 startX,
                        UInt32 startY,
                        UInt32 width,
                        UInt32 height,
                        Draw2D_LinePrm * pPrm)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    Draw2D_drawHorizontalLine(pCtx,startX,startY,width,pPrm);
    Draw2D_drawHorizontalLine(pCtx,startX,startY + height,width+pPrm->lineSize,pPrm);
    Draw2D_drawVerticalLine(pCtx,startX,startY,height,pPrm);
    Draw2D_drawVerticalLine(pCtx,startX + width,startY,height,pPrm);

    return status;
}
