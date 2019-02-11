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

#include "sgxRender1x1.h"

static const char gSgxRender1x1_vertexShader[] =
    "attribute vec4 vPosition;\n"
    "attribute vec2 texCoords;\n"
    "varying vec2 yuvTexCoords;\n"
    "void main() {\n"
    "  yuvTexCoords = texCoords;\n"
    "  gl_Position = vPosition;\n"
    "}\n";

static const char gSgxRender1x1_fragmentShader[] =
   "#extension GL_OES_EGL_image_external : require\n"
   "precision mediump float;\n"
   "uniform samplerExternalOES yuvTexSampler;\n"
   "varying vec2 yuvTexCoords;\n"
   "void main() {\n"
   "  gl_FragColor = texture2D(yuvTexSampler, yuvTexCoords);\n"
   "}\n"
   ;

static const GLfloat gSgxRender1x1_triangleVertices_fullscreen[] = {
        -1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        1.0f, 1.0f, 0.0f
 };

static const GLfloat gSgxRender1x1_texCoords[] = {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f
};

GLuint SgxRender1x1_loadShader(GLenum shaderType, const char* pSource) {
   GLuint shader = glCreateShader(shaderType);
   if (shader) {
       glShaderSource(shader, 1, &pSource, NULL);
       glCompileShader(shader);
       GLint compiled = 0;
       glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
       if (!compiled) {
           GLint infoLen = 0;
           glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
           if (infoLen) {
               char* buf = (char*) malloc(infoLen);
               if (buf) {
                   glGetShaderInfoLog(shader, infoLen, NULL, buf);
                   fprintf(stderr, " GL: Could not compile shader %d:\n%s\n",
                       shaderType, buf);
                   free(buf);
               }
           } else {
               fprintf(stderr, " GL: Guessing at GL_INFO_LOG_LENGTH size\n");
               char* buf = (char*) malloc(0x1000);
               if (buf) {
                   glGetShaderInfoLog(shader, 0x1000, NULL, buf);
                   fprintf(stderr, " GL: Could not compile shader %d:\n%s\n",
                   shaderType, buf);
                   free(buf);
               }
           }
           glDeleteShader(shader);
           shader = 0;
       }
   }
   return shader;
}


GLuint SgxRender1x1_createProgram(const char* pVertexSource, const char* pFragmentSource) {
   GLuint vertexShader = SgxRender1x1_loadShader(GL_VERTEX_SHADER, pVertexSource);
   if (!vertexShader) {
       return 0;
   }

   GLuint pixelShader = SgxRender1x1_loadShader(GL_FRAGMENT_SHADER, pFragmentSource);
   if (!pixelShader) {
       return 0;
   }

   GLuint program = glCreateProgram();
   if (program) {
       glAttachShader(program, vertexShader);
       System_eglCheckGlError("glAttachShader");
       glAttachShader(program, pixelShader);
       System_eglCheckGlError("glAttachShader");
       glLinkProgram(program);
       GLint linkStatus = GL_FALSE;
       glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
       if (linkStatus != GL_TRUE) {
           GLint bufLength = 0;
           glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
           if (bufLength) {
               char* buf = (char*) malloc(bufLength);
               if (buf) {
                   glGetProgramInfoLog(program, bufLength, NULL, buf);
                   fprintf(stderr, " GL: Could not link program:\n%s\n", buf);
                   free(buf);
               }
           }
           glDeleteProgram(program);
           program = 0;
       }
   }
   return program;
}

int SgxRender1x1_setup(SgxRender1x1_Obj *pObj)
{
    pObj->program = SgxRender1x1_createProgram(
                        gSgxRender1x1_vertexShader,
                        gSgxRender1x1_fragmentShader
                     );
    if (pObj->program==0)
    {
       return -1;
    }

    pObj->vPositionHandle = glGetAttribLocation(pObj->program, "vPosition");
    System_eglCheckGlError("glGetAttribLocation");

    pObj->yuvTexSamplerHandle = glGetUniformLocation(pObj->program, "yuvTexSampler");
    System_eglCheckGlError("glGetUniformLocation");

    pObj->vTexHandle = glGetAttribLocation(pObj->program, "texCoords");
    System_eglCheckGlError("glGetAttribLocation");

#if defined (QNX_BUILD)
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    System_eglCheckGlError("glClearColor");
    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    System_eglCheckGlError("glClear");
#endif

    glUseProgram(pObj->program);
    System_eglCheckGlError("glUseProgram");

    return 0;
}

void SgxRender1x1_renderFrame1x1(SgxRender1x1_Obj *pObj, System_EglWindowObj *pEglWindowObj, const GLfloat *vertices, GLuint texYuv)
{
    glVertexAttribPointer(pObj->vPositionHandle, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    System_eglCheckGlError("glVertexAttribPointer");
    glEnableVertexAttribArray(pObj->vPositionHandle);
    System_eglCheckGlError("glEnableVertexAttribArray");

    glVertexAttribPointer(pObj->vTexHandle, 2, GL_FLOAT, GL_FALSE, 0, gSgxRender1x1_texCoords);
    System_eglCheckGlError("glVertexAttribPointer");
    glEnableVertexAttribArray(pObj->vTexHandle);
    System_eglCheckGlError("glEnableVertexAttribArray");

    glUniform1i(pObj->yuvTexSamplerHandle, 0);
    System_eglCheckGlError("glUniform1i");
    glBindTexture(GL_TEXTURE_EXTERNAL_OES, texYuv);
    System_eglCheckGlError("glBindTexture");

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    System_eglCheckGlError("glDrawArrays");
}

void SgxRender1x1_renderFrame(SgxRender1x1_Obj *pObj, System_EglWindowObj *pEglWindowObj, GLuint texYuv)
{
    SgxRender1x1_renderFrame1x1(pObj, pEglWindowObj, gSgxRender1x1_triangleVertices_fullscreen, texYuv);
}
