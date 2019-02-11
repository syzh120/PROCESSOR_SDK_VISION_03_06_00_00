/*
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
*/

#include "sgxRender2x4.h"

#define QUAD_VERTS(scale, Hoff, Voff) { \
       -1.0f + Hoff, -1.0f + Voff + scale, 0.0f, \
       -1.0f + Hoff, -1.0f + Voff, 0.0f, \
       -1.0f + Hoff + scale, -1.0f + Voff, 0.0f, \
       -1.0f + Hoff + scale, -1.0f + Voff + scale, 0.0f, \
}

static const GLfloat gTriangleVertices_toplefttop[] = QUAD_VERTS(0.5, 0.0, 1.5);

static const GLfloat gTriangleVertices_topleftbottom[] = QUAD_VERTS(0.5, 0.5, 1.0);

static const GLfloat gTriangleVertices_bottomlefttop[] = QUAD_VERTS(0.5, 0.0, 0.5);

static const GLfloat gTriangleVertices_bottomleftbottom[] = QUAD_VERTS(0.5, 0.5, 0.0);

static const GLfloat gTriangleVertices_bottomrighttop[] = QUAD_VERTS(0.5, 1.0, 0.5);

static const GLfloat gTriangleVertices_bottomrightbottom[] = QUAD_VERTS(0.5, 1.5, 0.0);

static const GLfloat gTriangleVertices_toprighttop[] = QUAD_VERTS(0.5, 1.0, 1.5);

static const GLfloat gTriangleVertices_toprightbottom[] = QUAD_VERTS(0.5, 1.5, 1.0);

int SgxRender2x4_setup(SgxRender2x4_Obj *pObj)
{
       SgxRender1x1_setup(&pObj->render1x1Obj);

       return 0;
}

void SgxRender2x4_renderFrame(SgxRender2x4_Obj *pObj, System_EglWindowObj *pEglWindowObj, GLuint texYuv[], UInt16 numTex )
{
       UTILS_assert(numTex==8);

       SgxRender1x1_renderFrame1x1(&pObj->render1x1Obj, pEglWindowObj, gTriangleVertices_toplefttop, texYuv[0]);
       SgxRender1x1_renderFrame1x1(&pObj->render1x1Obj, pEglWindowObj, gTriangleVertices_topleftbottom, texYuv[1]);
       SgxRender1x1_renderFrame1x1(&pObj->render1x1Obj, pEglWindowObj, gTriangleVertices_toprighttop, texYuv[2]);
       SgxRender1x1_renderFrame1x1(&pObj->render1x1Obj, pEglWindowObj, gTriangleVertices_toprightbottom, texYuv[3]);
       SgxRender1x1_renderFrame1x1(&pObj->render1x1Obj, pEglWindowObj, gTriangleVertices_bottomlefttop, texYuv[4]);
       SgxRender1x1_renderFrame1x1(&pObj->render1x1Obj, pEglWindowObj, gTriangleVertices_bottomleftbottom, texYuv[5]);
       SgxRender1x1_renderFrame1x1(&pObj->render1x1Obj, pEglWindowObj, gTriangleVertices_bottomrighttop, texYuv[6]);
       SgxRender1x1_renderFrame1x1(&pObj->render1x1Obj, pEglWindowObj, gTriangleVertices_bottomrightbottom, texYuv[7]);
}
