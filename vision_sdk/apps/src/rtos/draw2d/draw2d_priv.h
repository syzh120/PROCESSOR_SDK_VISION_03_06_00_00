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

#ifndef _DRAW_2D_PRIV_H_
#define _DRAW_2D_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <src/include/draw2d.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

typedef struct {

    Draw2D_BufInfo bufInfo;

} Draw2D_Obj;


Int32 Draw2D_getFontProperty00(Draw2D_FontProperty *pProp);
Int32 Draw2D_getFontProperty01(Draw2D_FontProperty *pProp);
Int32 Draw2D_getFontProperty02(Draw2D_FontProperty *pProp);
Int32 Draw2D_getFontProperty03(Draw2D_FontProperty *pProp);
Int32 Draw2D_getFontProperty04(Draw2D_FontProperty *pProp);
Int32 Draw2D_getFontProperty05(Draw2D_FontProperty *pProp);
Int32 Draw2D_getFontProperty06(Draw2D_FontProperty *pProp);
Int32 Draw2D_getFontProperty07(Draw2D_FontProperty *pProp);
Int32 Draw2D_getFontProperty08(Draw2D_FontProperty *pProp);
Int32 Draw2D_getFontProperty09(Draw2D_FontProperty *pProp);
Int32 Draw2D_getFontProperty10(Draw2D_FontProperty *pProp);
Int32 Draw2D_getFontProperty11(Draw2D_FontProperty *pProp);
Int32 Draw2D_getFontProperty12(Draw2D_FontProperty *pProp);
Int32 Draw2D_getFontProperty13(Draw2D_FontProperty *pProp);
Int32 Draw2D_getFontProperty14(Draw2D_FontProperty *pProp);

Int32 Draw2D_getBmpProperty00(Draw2D_BmpProperty *pProp);
Int32 Draw2D_getBmpProperty01(Draw2D_BmpProperty *pProp);
Int32 Draw2D_getBmpProperty02(Draw2D_BmpProperty *pProp);
Int32 Draw2D_getBmpProperty03(Draw2D_BmpProperty *pProp);
Int32 Draw2D_getBmpProperty04(Draw2D_BmpProperty *pProp);
Int32 Draw2D_getBmpProperty06(Draw2D_BmpProperty *pProp);
Int32 Draw2D_getBmpProperty07(Draw2D_BmpProperty *pProp);
Int32 Draw2D_getBmpProperty08(Draw2D_BmpProperty *pProp);
Int32 Draw2D_getBmpProperty09(Draw2D_BmpProperty *pProp);
Int32 Draw2D_getBmpProperty10(Draw2D_BmpProperty *pProp);
Int32 Draw2D_getBmpProperty11(Draw2D_BmpProperty *pProp);
Int32 Draw2D_getBmpProperty12(Draw2D_BmpProperty *pProp);
Int32 Draw2D_getBmpProperty13(Draw2D_BmpProperty *pProp);
Int32 Draw2D_getBmpProperty14(Draw2D_BmpProperty *pProp);
Int32 Draw2D_getBmpProperty15(Draw2D_BmpProperty *pProp);
Int32 Draw2D_getBmpProperty16(Draw2D_BmpProperty *pProp);
Int32 Draw2D_getBmpProperty17(Draw2D_BmpProperty *pProp);
Int32 Draw2D_getBmpProperty18(Draw2D_BmpProperty *pProp);
Int32 Draw2D_getBmpProperty19(Draw2D_BmpProperty *pProp);
Int32 Draw2D_getBmpProperty20(Draw2D_BmpProperty *pProp);
Int32 Draw2D_getBmpProperty21(Draw2D_BmpProperty *pProp);
Int32 Draw2D_getBmpProperty22(Draw2D_BmpProperty *pProp);
Int32 Draw2D_getBmpProperty23(Draw2D_BmpProperty *pProp);
Int32 Draw2D_getBmpProperty24(Draw2D_BmpProperty *pProp);
Int32 Draw2D_getBmpProperty25(Draw2D_BmpProperty *pProp);
Int32 Draw2D_getBmpProperty27(Draw2D_BmpProperty *pProp);
Int32 Draw2D_getBmpProperty28(Draw2D_BmpProperty *pProp);
Int32 Draw2D_getBmpProperty29(Draw2D_BmpProperty *pProp);
Int32 Draw2D_getBmpProperty32(Draw2D_BmpProperty *pProp);

UInt32 Draw2D_getFontCharAddr(Draw2D_FontProperty *font, char c);

void Draw2D_drawCharYuv420SP(Draw2D_Handle pCtx,
                            UInt32 px,
                            UInt32 py,
                            char value,
                            Draw2D_FontProperty *pProp);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif  /* _DRAW_2D_H_ */

/* @} */

/* Nothing beyond this point */

