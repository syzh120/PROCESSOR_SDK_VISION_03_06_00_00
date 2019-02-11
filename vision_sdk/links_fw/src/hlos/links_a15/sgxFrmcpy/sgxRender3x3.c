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

#include "sgxRender3x3.h"

#define QUAD_VERTS(scale, Hoff, Voff) { \
       -1.0f + Hoff, -1.0f + Voff + scale, 0.0f, \
       -1.0f + Hoff, -1.0f + Voff, 0.0f, \
       -1.0f + Hoff + scale, -1.0f + Voff, 0.0f, \
       -1.0f + Hoff + scale, -1.0f + Voff + scale, 0.0f, \
}

static const GLfloat verts_topleft[]   =       QUAD_VERTS(2.0f/3.0f, 0.0f, 4.0f/3.0f);

static const GLfloat verts_middleleft[] =      QUAD_VERTS(2.0f/3.0f, 0.0f, 2.0f/3.0f);

static const GLfloat verts_bottomleft[] =      QUAD_VERTS(2.0f/3.0f, 0.0f, 0.0f);

static const GLfloat verts_topmiddle[]         =       QUAD_VERTS(2.0f/3.0f, 2.0f/3.0f, 4.0f/3.0f);

static const GLfloat verts_middlemiddle[] = QUAD_VERTS(2.0f/3.0f, 2.0f/3.0f, 2.0f/3.0f);

static const GLfloat verts_bottommiddle[] = QUAD_VERTS(2.0f/3.0f, 2.0f/3.0f, 0.0);

static const GLfloat verts_topright[]  =       QUAD_VERTS(2.0f/3.0f, 4.0f/3.0f, 4.0f/3.0f);

static const GLfloat verts_middleright[] =     QUAD_VERTS(2.0f/3.0f, 4.0f/3.0f, 2.0f/3.0f);

static const GLfloat verts_bottomright[] =     QUAD_VERTS(2.0f/3.0f, 4.0f/3.0f, 0.0f);


static const GLfloat black_buffer_data[] =
{ //one heck of a buffer
	0.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f,
};

static const char gSgxRender3x3_vertexShader[] =
	"attribute vec4 vPosition;\n"
	"attribute vec4 vColor;\n"
	"varying vec4 fragColor;\n"
	"void main() {\n"
	"  fragColor = vColor;\n"
	"  gl_Position = vPosition;\n"
	"}\n";

static const char gSgxRender3x3_fragmentShader[] =
	"precision mediump float;\n"
	"varying vec4 fragColor;\n"
	"void main() {\n"
	"  gl_FragColor = fragColor;\n"
	"}\n";

int SgxRender3x3_setup(SgxRender3x3_Obj *pObj)
{
	if(SgxRender1x1_setup(&pObj->render1x1Obj) == -1)
	{
		return -1;
	}

	pObj->colorProgram = SgxRender1x1_createProgram(
						gSgxRender3x3_vertexShader,
						gSgxRender3x3_fragmentShader
					);
	if (pObj->colorProgram == 0)
	{
		return -1;
	}

	pObj->vPositionHandle = glGetAttribLocation(pObj->colorProgram, "vPosition");
	System_eglCheckGlError("glGetAttribLocation");

	pObj->vColorHandle = glGetAttribLocation(pObj->colorProgram, "vColor");
	System_eglCheckGlError("glGetAttribLocation");

       return 0;
}

void SgxRender3x3_renderFrame(SgxRender3x3_Obj *pObj, System_EglWindowObj *pEglWindowObj, GLuint texYuv[], UInt16 numTex )
{
       UTILS_assert(numTex==8);

	SgxRender1x1_renderFrame1x1(&pObj->render1x1Obj, pEglWindowObj, verts_topmiddle, texYuv[0]);
	SgxRender1x1_renderFrame1x1(&pObj->render1x1Obj, pEglWindowObj, verts_topright, texYuv[1]);
	SgxRender1x1_renderFrame1x1(&pObj->render1x1Obj, pEglWindowObj, verts_middleleft, texYuv[2]);
	SgxRender1x1_renderFrame1x1(&pObj->render1x1Obj, pEglWindowObj, verts_middlemiddle, texYuv[3]);
	SgxRender1x1_renderFrame1x1(&pObj->render1x1Obj, pEglWindowObj, verts_middleright, texYuv[4]);
	SgxRender1x1_renderFrame1x1(&pObj->render1x1Obj, pEglWindowObj, verts_bottomleft, texYuv[5]);
	SgxRender1x1_renderFrame1x1(&pObj->render1x1Obj, pEglWindowObj, verts_bottommiddle, texYuv[6]);
	SgxRender1x1_renderFrame1x1(&pObj->render1x1Obj, pEglWindowObj, verts_bottomright, texYuv[7]);

	glUseProgram(pObj->colorProgram);

	glVertexAttribPointer(pObj->vPositionHandle, 3, GL_FLOAT, GL_FALSE, 0, verts_topleft);
	System_eglCheckGlError("glVertexAttribPointer");
	glEnableVertexAttribArray(pObj->vPositionHandle);
	System_eglCheckGlError("glEnableVertexAttribArray");

	glVertexAttribPointer(pObj->vColorHandle, 3, GL_FLOAT, GL_FALSE, 0, black_buffer_data);
	System_eglCheckGlError("glVertexAttribPointer");
	glEnableVertexAttribArray(pObj->vColorHandle);
	System_eglCheckGlError("glEnableVertexAttribArray");

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	System_eglCheckGlError("glDrawArrays");

	glUseProgram(pObj->render1x1Obj.program);
}
